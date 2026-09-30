#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/io/vtk_lib_io.h>
#include <pcl_msgs/msg/polygon_mesh.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/project_inliers.h>
#include <Eigen/Core>
#include <pcl/point_cloud.h>
#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/sample_consensus/sac_model_sphere.h>
#include <pcl/sample_consensus/sac_model_cylinder.h>


typedef pcl::PointXYZ PointXYZ;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointXYZ> ColorHandlerT;


// Types
typedef pcl::Normal PointNT;
typedef pcl::PointNormal PointClNormal;
typedef pcl::PointCloud<PointXYZ> PointCloudXYZ;
typedef pcl::PointCloud<PointClNormal> PointCloudN;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::FPFHEstimationOMP<PointClNormal,PointClNormal,FeatureT> FeatureEstimationT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointClNormal> ColorHandlerNormal;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;

class PointCloudProcessor : public rclcpp::Node{

    public:
        PointCloudProcessor() : Node("pointcloud_processor")
        {
            // Subscribe to the point cloud data from RealSense
            subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>("/depthpoints", 10,
                std::bind(&PointCloudProcessor::getPointCloud, this, std::placeholders::_1));

            // // Publisher for the filtered and downsampled point cloud
            // publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("filtered_pointcloud", 10);
        }
        void generate_cylinder_master();
        void processPointCloud();
        void getPointCloud(sensor_msgs::msg::PointCloud2 msg);
        
    private:

        pcl::PointCloud<PointClNormal>::Ptr output ;
        pcl::PointCloud<PointClNormal>::Ptr cloud;
        PointCloudN scene_cloud;

        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;

        float cyl_radius = 0.05;
        float cyl_height = 0.200;
        int counter =0;
           
};

void PointCloudProcessor::generate_cylinder_master(){

    const std::string meshFileName = "/home/mario/master_ws/src/estun_control/meshes/Probekoerper.stl";
    pcl::PolygonMesh testMesh;
    pcl::io::loadPolygonFileSTL( meshFileName, testMesh );   
    output.reset(new pcl::PointCloud<PointClNormal>());

    pcl::fromPCLPointCloud2(testMesh.cloud, *output);

    pcl::visualization::PCLVisualizer visu("Alignment");

    cloud.reset(new pcl::PointCloud<PointClNormal>());

    float dx= 0.005;
    //float spaces_z = (cyl_height/dx);
    int spaces_z = cyl_height/dx;

    float spacing_z= cyl_height/spaces_z;
    //float spacing_z = 0.005;
    PointClNormal pt;

    for(int j = 0; j <= spaces_z; j++ ){
      
      pt.z = j * spacing_z;

      float current_height = j * spacing_z;

        for (float i=0; i<=cyl_radius;i+=dx){

            pt.x = i;
            pt.y = sqrt(std::pow(cyl_radius,2)-std::pow(i,2));
            
            cloud->push_back(pt);

            float dy = 2*pt.y;
            int spaces_y = std::floor(dy/dx);
            float spacing = dy/spaces_y;

            //erstellt in +y/-y punkte an boden und deckel
            if(j == spaces_z || j == 0){

                for (int i = 0; i<spaces_y;i++){

                    pt.y = pt.y-spacing;
                    cloud->push_back(pt);
                    
                }
            }

            pt.y = -pt.y;
            cloud->push_back(pt);

            //negatives x koordinate
            pt.x = -pt.x;
            cloud->push_back(pt);

            //erstellt in +y/-y punkte an boden und deckel
            if(j == spaces_z || j == 0){

                for (int i = 0; i<spaces_y;i++){

                    pt.y = pt.y-spacing;
                    cloud->push_back(pt);
                }
            }
            pt.y = -pt.y;
            cloud->push_back(pt);

        }
    }

    visu.addPointCloud(output, ColorHandlerNormal(output, 0.0, 255.0, 0.0), "Probekoerper");
    visu.addPointCloud(cloud, ColorHandlerNormal(cloud, 255.0, 0.0, 0.0), "Projektion");
    visu.spin ();
}
void PointCloudProcessor::getPointCloud(sensor_msgs::msg::PointCloud2 msg){

    pcl::fromROSMsg(msg,scene_cloud);

        if (counter==0){
            
            RCLCPP_INFO(this->get_logger(),"RUN ProcessPointCloud");
            processPointCloud();
            counter=1;
        }

}

void PointCloudProcessor::processPointCloud(){

// Point clouds
  PointCloudN::Ptr object (new PointCloudN);
  PointCloudN::Ptr scene_ (new PointCloudN);
  PointCloudN::Ptr object_aligned (new PointCloudN);

  PointCloudN::Ptr scene_before_downsampling (new PointCloudN);
  PointCloudN::Ptr scene (new PointCloudN);
  PointCloudN::Ptr object_normal (new PointCloudN);

  PointCloudN::Ptr final (new PointCloudN);


  FeatureCloudT::Ptr object_features (new FeatureCloudT);
  FeatureCloudT::Ptr scene_features (new FeatureCloudT);

  object = cloud;
  *scene_before_downsampling = scene_cloud;



  Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
  //float theta = M_PI/4;
  float theta_y = -0.262;
  float theta_z = -1.57;

  // Define a translation of 2.5 meters on the x axis.
  transform_2.translation() << 0.5, 0.0, -0.2;

  // The same rotation matrix as before; theta radians around Z axis
  transform_2.rotate (Eigen::AngleAxisf (theta_y, Eigen::Vector3f::UnitY()));
  transform_2.rotate (Eigen::AngleAxisf (theta_z, Eigen::Vector3f::UnitZ()));

  // Print the transformation
  printf ("\nMethod #2: using an Affine3f\n");
  std::cout << transform_2.matrix() << std::endl;

  // Executing the transformation
  //pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
  // You can either apply transform_1 or transform_2; they are the same

    pcl::PassThrough<PointClNormal> pass_obj;
    pass_obj.setInputCloud (object);
    pass_obj.setFilterFieldName ("z");
    pass_obj.setFilterLimits (0.01, 0.19);
    pass_obj.filter (*object);
    pass_obj.setInputCloud (object);
    pass_obj.setFilterFieldName ("y");
    pass_obj.setFilterLimits (-0.1, -0.04);
    pass_obj.filter (*object);

  pcl::transformPointCloud (*object, *object, transform_2);
  

pcl::visualization::PCLVisualizer visu_2("Alignment_TEST");
float vx = 0, vy = 0 , vz = 0;

  // Downsample
    pcl::console::print_highlight ("Downsampling...\n");
//   pcl::VoxelGrid<PointXYZ> grid;
     const float leaf = 0.005f;
//   grid.setLeafSize (leaf, leaf, leaf);
//   grid.setInputCloud (object);
//   grid.filter (*object);

    pcl::VoxelGrid<PointClNormal> grid_2;
    grid_2.setLeafSize (leaf, leaf, leaf);
    grid_2.setInputCloud (scene_before_downsampling);
    grid_2.filter (*scene);

  

    pcl::PointCloud<PointClNormal>::iterator pcl_begin;
    pcl::PointCloud<PointClNormal>::iterator pcl_end;

    pcl_begin = scene->begin();
    pcl_end = scene->end();


    for (pcl::PointCloud<PointClNormal>::iterator count = pcl_begin; count<=pcl_end;){

      if (pcl::isFinite(*count)==false){

        RCLCPP_INFO(this->get_logger(),"is NOT finite"); 

        count = scene->erase(count);

        RCLCPP_INFO(this->get_logger(),"Removed Point from Cloud"); 
      } 

      else {count++;}
    }

    // pcl::SampleConsensusModelCylinder<PointClNormal, PointClNormal>::Ptr model_p (new pcl::SampleConsensusModelCylinder<PointClNormal, PointClNormal> (scene));

    // model_p->setInputNormals();

    // std::vector<int> inliers;

    // pcl::RandomSampleConsensus<PointClNormal> ransac (model_p);
    // ransac.setDistanceThreshold (.01);
    // ransac.computeModel();
    // ransac.getInliers(inliers);

    // pcl::copyPointCloud (*scene, inliers, *final);

    // pcl::visualization::PCLVisualizer visu_ransac("TEST");
    // visu_ransac.addPointCloud (final, ColorHandlerNormal (final, 0.0, 255.0, 0.0), "scene");
    // visu_ransac.spin ();

    // for (PointClNormal pt : *scene){

    //   if (pcl::isFinite(pt)==false){

    //     RCLCPP_INFO(this->get_logger(),"Finite Points in Cloud !!!"); 
    //   } 
    // }


  pcl::search::KdTree<PointClNormal>::Ptr tree (new pcl::search::KdTree<PointClNormal> ());
  //pcl::search::KdTree<PointXYZ>::Ptr tree_xyz (new pcl::search::KdTree<PointXYZ> ());
    
  // Estimate normals for scene
  pcl::console::print_highlight ("Estimating scene normals...\n");
  pcl::NormalEstimationOMP<PointClNormal,PointClNormal> nest;
  //nest.setRadiusSearch (0.005);
  nest.setSearchMethod (tree);
  nest.setKSearch(10);
  nest.setViewPoint(vx,vy,vz);
  nest.setInputCloud (scene);
  //nest.setSearchSurface (scene_before_downsampling);
  nest.compute (*scene);














  pcl::ModelCoefficients::Ptr coefficients_cylinder (new pcl::ModelCoefficients);
  pcl::ModelCoefficients::Ptr coefficients_circle (new pcl::ModelCoefficients);
  pcl::ModelCoefficients::Ptr coefficients_plane (new pcl::ModelCoefficients);

  pcl::PointIndices::Ptr inliers_cylinder (new pcl::PointIndices);
  pcl::PointIndices::Ptr inliers_circle (new pcl::PointIndices);
  pcl::PointIndices::Ptr inliers_plane (new pcl::PointIndices);

  pcl::ExtractIndices<PointClNormal> extract;
  pcl::ExtractIndices<PointClNormal> extract_2;

  // Create the segmentation object for cylinder segmentation and set all the parameters

  pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg;
  seg.setOptimizeCoefficients (true);
  seg.setModelType (pcl::SACMODEL_CYLINDER);
  seg.setMethodType (pcl::SAC_RANSAC);
  seg.setNormalDistanceWeight (0.1);
  seg.setMaxIterations (10000);
  seg.setDistanceThreshold (0.05);
  seg.setRadiusLimits (0, 0.1);
  seg.setInputCloud (scene);
  seg.setInputNormals (scene);

  // pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg_2;
  // seg_2.setOptimizeCoefficients (true);
  // seg_2.setModelType (pcl::SACMODEL_CIRCLE3D);
  // seg_2.setMethodType (pcl::SAC_RANSAC);
  // seg_2.setNormalDistanceWeight (0.1);
  // seg_2.setMaxIterations (10000);
  // seg_2.setDistanceThreshold (0.05);
  // seg_2.setRadiusLimits (0, 0.1);
  // seg_2.setInputCloud (scene);
  // seg_2.setInputNormals (scene);

  // // Obtain the cylinder inliers and coefficients
  // seg_2.segment (*inliers_circle, *coefficients_circle);
  // std::cerr << "Circle coefficients: " << *coefficients_circle << std::endl;

  seg.segment (*inliers_cylinder, *coefficients_cylinder);
  std::cerr << "Cylinder coefficients: " << *coefficients_cylinder << std::endl;

  Eigen::Vector3f cyl_axis = seg.getAxis();

    float x = cyl_axis[0];
    float y = cyl_axis[1];
    float z = cyl_axis[2];

    RCLCPP_INFO(this->get_logger(),"Axis X: %f \n Axis Y: %f \n Axis Z: %f \n ", x, y ,z);

  // Write the cylinder inliers to disk
  extract.setInputCloud (scene);
  extract.setIndices (inliers_cylinder);
  extract.setNegative (false);

  pcl::PointCloud<PointClNormal>::Ptr cloud_cylinder (new pcl::PointCloud<PointClNormal> ());
  
  extract.filter (*cloud_cylinder);

  PointCloudN::Ptr outliers_zylinder (new PointCloudN);
  extract.setNegative (true);
  extract.filter(*outliers_zylinder);


  pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg_2;

  seg_2.setOptimizeCoefficients (true);
  seg_2.setModelType (pcl::SACMODEL_CIRCLE3D);
  seg_2.setMethodType (pcl::SAC_RANSAC);
  seg_2.setNormalDistanceWeight (0.1);
  seg_2.setMaxIterations (10000);
  seg_2.setDistanceThreshold (0.05);
  seg_2.setEpsAngle(pcl::deg2rad (1.0));
  seg_2.setRadiusLimits (0, 0.1);
  seg_2.setAxis(Eigen::Vector3f (-0.259936, 0.0, 0.9656));
  seg_2.setInputCloud (outliers_zylinder);
  seg_2.setInputNormals (outliers_zylinder);

  seg_2.segment (*inliers_plane, *coefficients_plane);
  std::cerr << "Plane coefficients: " << *coefficients_plane << std::endl;

  extract_2.setInputCloud (outliers_zylinder);
  extract_2.setIndices (inliers_plane);
  extract_2.setNegative (false);

  
  pcl::PointCloud<PointClNormal>::Ptr cloud_plane (new pcl::PointCloud<PointClNormal> ());

  //pcl::PointCloud<PointClNormal>::Ptr cloud_circle (new pcl::PointCloud<PointClNormal> ());

  
  extract_2.filter (*cloud_plane);
  //extract_2.filter(*cloud_circle);

    pcl::visualization::PCLVisualizer visu_ransac("TEST");
    visu_ransac.addPointCloud (cloud_cylinder, ColorHandlerNormal (cloud_cylinder, 0.0, 255.0, 0.0), "cloud_cylinder");
    visu_ransac.addPointCloud (cloud_plane, ColorHandlerNormal (cloud_plane, 0.0, 0.0, 255.0), "cloud_plane");
    //visu_ransac.addPointCloud (cloud_circle, ColorHandlerNormal (cloud_circle, 255.0, 0.0, 0.0), "cloud_circle");
    visu_ransac.spin ();

  if (cloud_cylinder->points.empty ()) 
    std::cerr << "Can't find the cylindrical component." << std::endl;
  else
  {
	  std::cerr << "PointCloud representing the cylindrical component: " << cloud_cylinder->size () << " data points." << std::endl;
	  //writer.write ("table_scene_mug_stereo_textured_cylinder.pcd", *cloud_cylinder, false);
  }

//Umrechnung der Koordinaten

  Eigen::Affine3f transform_3 = Eigen::Affine3f::Identity();

  Eigen::Affine3f transform_3_inv = Eigen::Affine3f::Identity();

  float phi_x = 0.263;
  float phi_y = 0.0;
  float phi_z = -1.57;
  

  // Define a translation of 2.5 meters on the x axis.
  transform_3.translation() << -0.3, 0.0, 1.2;

  // The same rotation matrix as before; theta radians around Z axis
  transform_3.rotate (Eigen::AngleAxisf (phi_x, Eigen::Vector3f::UnitX()));
  transform_3.rotate (Eigen::AngleAxisf (phi_y, Eigen::Vector3f::UnitY()));
  transform_3.rotate (Eigen::AngleAxisf (phi_z, Eigen::Vector3f::UnitZ()));
  
  // Print the transformation
  printf ("\nTransformationsmatrix\n");
  std::cout << transform_3.matrix() << std::endl;

  // std::vector<float> koo_kreismittelp_camera = {0.8184, -0.0981, 0.0058};
  // std::vector<float> koo_kreismittelp_world;

  Eigen::Vector3f koo_kreismittelp_camera(0.818403, -0.098142, 0.00582787);
  Eigen::Vector3f koo_zylaxispoint_camera(0.866483, -0.10008, 0.-0.14109);
  //Eigen::Vector3f koo_kreismittelp_camera(-0.4, -0.8, 0.994);
  Eigen::Vector3f koo_kreismittelp_world;
  Eigen::Vector3f koo_zylaxispoint_world;

  koo_kreismittelp_world = transform_3 * koo_kreismittelp_camera;
  koo_zylaxispoint_world = transform_3 * koo_zylaxispoint_camera;

  RCLCPP_INFO(this->get_logger(),"X: %f \n Y: %f \n Z: %f \n ", koo_kreismittelp_world[0], koo_kreismittelp_world[1] ,koo_kreismittelp_world[2]);

  RCLCPP_INFO(this->get_logger(),"X_Cyl: %f \n Y_Cyl: %f \n Z_Cyl: %f \n ", koo_zylaxispoint_world[0], koo_zylaxispoint_world[1] ,koo_zylaxispoint_world[2]);































    // Estimate normals for scene
  pcl::console::print_highlight ("Estimating object normals...\n");
  pcl::NormalEstimationOMP<PointClNormal,PointClNormal> nest_object;

//   pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
//   nest_object.setSearchMethod (tree);

  //nest_object.setRadiusSearch (0.01);
  nest_object.setSearchMethod (tree);
  nest_object.setKSearch(10);
  nest_object.setInputCloud (object);
  //nest_object.setSearchSurface (object);
  nest_object.setViewPoint(vx,vy,vz);
  nest_object.compute (*object);

  int size_object_normal= object->size();

  RCLCPP_INFO(this->get_logger(),"Size: %i", size_object_normal);


    //pcl::flipNormalTowardsViewpoint (*object, vx, vy, vz, *object_normal);

    visu_2.addPointCloud(object, ColorHandlerNormal(object, 255.0, 0.0, 0.0), "Projektion_object");
    visu_2.addPointCloud(scene, ColorHandlerNormal(scene, 0.0, 255.0, 0.0), "Projektion_scene");
    
    int level_obj = 5, level_scene = 10;
    float scale = (0.0199999995529651642F);

    visu_2.addPointCloudNormals<PointClNormal,PointClNormal>(scene, scene, level_scene, scale, "SceneNormal");
    visu_2.addPointCloudNormals<PointClNormal,PointClNormal>(object, object, level_obj , scale , "ObjectNormal");
    visu_2.spin();
  
  // Estimate features
  pcl::console::print_highlight ("Estimating features...\n");

  FeatureEstimationT fest;
  //fest.setRadiusSearch (0.010);
  fest.setSearchMethod(tree);
  fest.setKSearch(10);
  fest.setInputCloud (object);
  fest.setInputNormals (object);
  fest.compute (*object_features);
  fest.setInputCloud (scene);
  fest.setInputNormals (scene);
  fest.compute (*scene_features);

  int feat_count_scene = scene_features->size();
  int feat_count_object = object_features->size();


  pcl::console::print_highlight ("Features Scene: %i\n Features Object: %i \n", feat_count_scene, feat_count_object);


  pcl::SampleConsensusPrerejective<PointClNormal,PointClNormal,FeatureT> align_object;
  align_object.setInputSource (object);
  align_object.setSourceFeatures (object_features);
  align_object.setInputTarget (scene);
  align_object.setTargetFeatures (scene_features);

  // align_object.setInputSource (scene);
  // align_object.setSourceFeatures (scene_features);
  // align_object.setInputTarget (object);
  // align_object.setTargetFeatures (object_features);

  align_object.setMaximumIterations (50000); // Number of RANSAC iterations
  align_object.setNumberOfSamples (3); // Number of points to sample for generating/prerejecting a pose
  align_object.setCorrespondenceRandomness (5); // Number of nearest features to use
  align_object.setSimilarityThreshold (0.90f); // Polygonal edge length similarity threshold
  align_object.setMaxCorrespondenceDistance (0.8f * leaf); // Inlier threshold
  align_object.setInlierFraction (0.99f); // Required inlier fraction for accepting a pose hypothesis
  {
    pcl::ScopeTime t("Alignment");
    align_object.align (*object_aligned);
  }


  
  if (align_object.hasConverged ())
  {
    // Print results
    printf ("\n");
    Eigen::Matrix4f transformation = align_object.getFinalTransformation ();
    pcl::console::print_info ("    | %6.3f %6.3f %6.3f | \n", transformation (0,0), transformation (0,1), transformation (0,2));
    pcl::console::print_info ("R = | %6.3f %6.3f %6.3f | \n", transformation (1,0), transformation (1,1), transformation (1,2));
    pcl::console::print_info ("    | %6.3f %6.3f %6.3f | \n", transformation (2,0), transformation (2,1), transformation (2,2));
    pcl::console::print_info ("\n");
    pcl::console::print_info ("t = < %0.3f, %0.3f, %0.3f >\n", transformation (0,3), transformation (1,3), transformation (2,3));
    pcl::console::print_info ("\n");
    pcl::console::print_info ("Inliers: %i/%i\n", align_object.getInliers ().size (), object->size ());
    
    // Show alignment
    pcl::visualization::PCLVisualizer visu("TEST");
    visu.addPointCloud (scene, ColorHandlerNormal (scene, 0.0, 255.0, 0.0), "scene");
    visu.addPointCloud (object_aligned, ColorHandlerNormal (object_aligned, 255.0, 0.0, 0.0), "object_aligned");
    visu.spin ();
  }
  else
  {
    pcl::console::print_error ("Alignment failed!\n");

    rclcpp::shutdown();
    return;
  }

  return;
}


int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);

    auto node_point_cloud_processor = std::make_shared<PointCloudProcessor>();
    
    node_point_cloud_processor->generate_cylinder_master();
    
    rclcpp::spin(node_point_cloud_processor);

    //rclcpp::shutdown();
    

    return 0;
}