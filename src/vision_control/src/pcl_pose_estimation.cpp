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
#include <string>
#include <pcl/segmentation/extract_clusters.h>

//Custom Interfaces
#include "../robot_interfaces/robot_interfaces/msg/object_pose.hpp"


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

            pose_publisher_ = this->create_publisher<robot_interfaces::msg::ObjectPose>("/ObjectPose",10);

            // // Publisher for the filtered and downsampled point cloud
            // publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("filtered_pointcloud", 10);
        }
        void generate_cylinder_master();
        void processPointCloud();
        void clusterPointCloud();
        void getPointCloud(sensor_msgs::msg::PointCloud2 msg);
        std::vector<float> calculateCylinder(Eigen::Vector3f,Eigen::Vector3f,Eigen::Vector3f,float);

        rclcpp::Publisher<robot_interfaces::msg::ObjectPose>::SharedPtr pose_publisher_;

        
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

    //pcl::visualization::PCLVisualizer visu("Alignment");

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

    //visu.addPointCloud(output, ColorHandlerNormal(output, 0.0, 255.0, 0.0), "Probekoerper");
    //visu.addPointCloud(cloud, ColorHandlerNormal(cloud, 255.0, 0.0, 0.0), "Projektion");
    //visu.spin ();
}

void PointCloudProcessor::getPointCloud(sensor_msgs::msg::PointCloud2 msg){

    pcl::fromROSMsg(msg,scene_cloud);

        if (counter==0){
            
            RCLCPP_INFO(this->get_logger(),"RUN ProcessPointCloud");
            processPointCloud();
            counter=1;
        }

        // if (counter==0){
            
        //     RCLCPP_INFO(this->get_logger(),"RUN ClusterPointCloud");
        //     clusterPointCloud();
        //     counter=1;
        // }

}

void PointCloudProcessor::clusterPointCloud(){

  pcl::visualization::PCLVisualizer visu_cluster("Cluster_Scene");
  PointCloudN::Ptr scene_before_downsampling (new PointCloudN);

  // Creating the KdTree object for the search method of the extraction
  pcl::search::KdTree<PointClNormal>::Ptr tree (new pcl::search::KdTree<PointClNormal>);

  PointCloudN::Ptr scene (new PointCloudN);

  *scene_before_downsampling = scene_cloud;

  const float leaf = 0.005f;


  pcl::VoxelGrid<PointClNormal> grid_2;
  grid_2.setLeafSize (leaf, leaf, leaf);
  grid_2.setInputCloud (scene_before_downsampling);
  grid_2.filter (*scene);

  PointCloudN::Ptr scene_filtered (new PointCloudN);

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

  tree->setInputCloud (scene);

  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<PointClNormal> ec;
  ec.setClusterTolerance (0.02); // 2cm
  ec.setMinClusterSize (10);
  ec.setMaxClusterSize (25000);
  ec.setSearchMethod (tree);
  ec.setInputCloud (scene);
  ec.extract (cluster_indices);

  RCLCPP_INFO(this->get_logger(),"Extract Cluster Indizes succeded"); 
  RCLCPP_INFO(this->get_logger(),"Extract Cluster Indizes size: %i", cluster_indices.size()); 
  
  std::vector<pcl::PointCloud<PointClNormal>::Ptr> cluster_vec;

  int j = 0;

  RCLCPP_INFO(this->get_logger(),"Extract Cluster Indizes succeded");

  for (const auto& cluster : cluster_indices){

    RCLCPP_INFO(this->get_logger(),"Test For-Schleife 1"); 
    pcl::PointCloud<PointClNormal>::Ptr cloud_cluster (new pcl::PointCloud<PointClNormal>);
    
    for (const auto& idx : cluster.indices) {
      //RCLCPP_INFO(this->get_logger(),"Test For-Schleife 2"); 
      cloud_cluster->push_back((*scene)[idx]); //Scene Punktewolke wird nach Indizes des jeweiligen Clusters extrahiert
      //RCLCPP_INFO(this->get_logger(),"Extract into cloud_cluster erfolgreich"); 
    } 

    cloud_cluster->width = cloud_cluster->size ();
    cloud_cluster->height = 1;
    cloud_cluster->is_dense = true;

    std::cout << "PointCloud representing the Cluster: " << cloud_cluster->size () << " data points." << std::endl;

    auto cluster_copy = pcl::make_shared<pcl::PointCloud<PointClNormal>>(*cloud_cluster);

    RCLCPP_INFO(this->get_logger(),"Copy erfolgreich"); 

    cluster_vec.push_back(cluster_copy);

    

    RCLCPP_INFO(this->get_logger(),"Schleife erfolgreich"); 

    std::string visu_name = "cylinder_cloud_" + std::to_string(j); 

    double r = 0.0, g = 0.0, b = 0.0;

    if ((j % 2) == 0){r = 255.0; g = 0.0, b = 0.0;}

    if ((j % 3) == 0){r = 0.0; g = 255.0, b = 0.0;}

    else{r = 0.0; g = 0.0, b = 255.0;}

    visu_cluster.addPointCloud (cluster_vec[j], ColorHandlerNormal (cluster_vec[j], r, g, b), visu_name);

    RCLCPP_INFO(this->get_logger(),"Add to Visu erfolgreich"); 

    j++;
  }

  RCLCPP_INFO(this->get_logger(),"Visu start"); 
  
  visu_cluster.spin();
}

void PointCloudProcessor::processPointCloud(){

  pcl::visualization::PCLVisualizer visu_ransac("Cylinder-Segmentation");


  //Umrechnung der Koordinaten--------------------------------------------------------------------------------------------------------------------------

  Eigen::Affine3f transform_3 = Eigen::Affine3f::Identity();

  float phi_x = 0.263;
  float phi_y = 0.0;
  float phi_z = -1.57;
  
  transform_3.translation() << -0.3, 0.0, 1.2;

  // The same rotation matrix as before; theta radians around Z axis
  transform_3.rotate (Eigen::AngleAxisf (phi_x, Eigen::Vector3f::UnitX()));
  transform_3.rotate (Eigen::AngleAxisf (phi_y, Eigen::Vector3f::UnitY()));
  transform_3.rotate (Eigen::AngleAxisf (phi_z, Eigen::Vector3f::UnitZ()));

  Eigen::Matrix3f transform_rotation = transform_3.rotation();
  Eigen::Vector3f transform_translation = transform_3.translation();
  
  // Print the transformation
  printf ("\nTransformationsmatrix\n");
  std::cout << transform_3.matrix() << std::endl;



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
  

  //pcl::visualization::PCLVisualizer visu_2("Alignment_TEST");
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
 
    //Punktewolke nach infiniten Punkten filtern
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

  visu_ransac.addPointCloud (scene, ColorHandlerNormal (scene, 255.0, 0.0, 0.0), "scene");
  // visu_ransac.spin ();
  //visu_ransac.removeAllPointClouds();

  //Segemntierung von Cylinder und Kreisfläche-------------------------------------------------------------------------------------------------

  pcl::PointCloud<PointClNormal>::Ptr cloud_cylinder (new pcl::PointCloud<PointClNormal> ());
  pcl::PointCloud<PointClNormal>::Ptr cloud_circle_plane (new pcl::PointCloud<PointClNormal> ());
  pcl::PointCloud<PointClNormal>::Ptr scene_before (new pcl::PointCloud<PointClNormal> ());
  std::vector<pcl::PointCloud<PointClNormal>::Ptr> object_vec;
  
  bool empty_cyl_cloud = false;

  int number_cylinders = 0;

  for(; empty_cyl_cloud == false ; number_cylinders++){

  //for(int i = 0; i<1; i++){

    //RCLCPP_INFO(this->get_logger(),"DO-While wird ausgeführt");

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
    seg.setDistanceThreshold (0.01);
    seg.setRadiusLimits (0.048, 0.052);
    seg.setInputCloud (scene);
    seg.setInputNormals (scene);
    seg.segment (*inliers_cylinder, *coefficients_cylinder);

    auto distance = seg.getDistanceFromOrigin();
  
    //std::cerr << "Cylinder coefficients: " << *coefficients_cylinder << std::endl;

    float cyl_axis_point_x = coefficients_cylinder->values[0];
    float cyl_axis_point_y = coefficients_cylinder->values[1];
    float cyl_axis_point_z = coefficients_cylinder->values[2];

    float cyl_axis_x = coefficients_cylinder->values[3];
    float cyl_axis_y = coefficients_cylinder->values[4];
    float cyl_axis_z = coefficients_cylinder->values[5];

    //extrahiertes Objekt
    extract.setInputCloud (scene);
    extract.setIndices (inliers_cylinder);
    extract.setNegative (false);
    extract.filter (*cloud_cylinder);
    extract.setNegative (true);
    extract.filter(*scene);



    PointCloudN::Ptr cloud_cylinder_end (new PointCloudN); //Cloud für Stirnseite des Zylinders

    auto message = robot_interfaces::msg::ObjectPose();

    if ((cloud_cylinder->points.empty())){

      std::cerr << "Can't find any more the cylindrical component." << std::endl;
      empty_cyl_cloud = true;

      message.object_type = "END";

      pose_publisher_->publish(message);
    }

    else{

      //std::cerr << "Starte Punktesuche im Cylinder" << std::endl;

      int counter = 0;

      for (const auto& point : *scene){

        counter++;

        float X = point.x;
        float Y = point.y;
        float Z = point.z;
        float radius_bb = 0.045;

        float t = ((X- cyl_axis_point_x) * cyl_axis_x + (Y - cyl_axis_point_y) * cyl_axis_y + (Z- cyl_axis_point_z) * cyl_axis_z)/(pow(cyl_axis_x,2)+pow(cyl_axis_y,2)+pow(cyl_axis_z,2));

        //std::cerr << "Linearer Para t:"<< t << std::endl;

        //std::cerr << "X:"<< X << "Y:"<< Y << "Z:"<< Z << std::endl;

        float distance = sqrt(pow(X-(cyl_axis_point_x+t*cyl_axis_x),2) + pow(Y-(cyl_axis_point_y+t*cyl_axis_y),2) + pow(Z-(cyl_axis_point_z+t*cyl_axis_z),2));

        //std::cerr << "Distance:"<< distance << std::endl;

        if (distance <= radius_bb){

          //std::cerr << "Distance ist kleiner"<< std::endl;

          cloud_cylinder_end->push_back(point);

        }
      }


      //std::cerr << "Punktesuche Cylinder beendet" << std::endl;
      //std::cerr << "Counter" << counter<< std::endl;


      //Restliche Scene
      // PointCloudN::Ptr outliers_zylinder (new PointCloudN);
      // extract.setNegative (true);
      // extract.filter(*outliers_zylinder);

      pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg_2;

      seg_2.setOptimizeCoefficients (true);
      seg_2.setModelType (pcl::SACMODEL_CIRCLE3D);
      seg_2.setMethodType (pcl::SAC_RANSAC);
      seg_2.setNormalDistanceWeight (0.1);
      seg_2.setMaxIterations (10000);
      seg_2.setDistanceThreshold (0.002);
      seg_2.setEpsAngle(pcl::deg2rad (1.0));
      seg_2.setRadiusLimits (0.0, 0.045);
      seg_2.setAxis(Eigen::Vector3f (cyl_axis_x, cyl_axis_y, cyl_axis_z));
      seg_2.setInputCloud (cloud_cylinder_end);
      seg_2.setInputNormals (cloud_cylinder_end);
      seg_2.segment (*inliers_plane, *coefficients_circle);
      std::cerr << "Plane coefficients: " << *coefficients_circle << std::endl;

      float cir_mid_x = coefficients_circle->values[0];
      float cir_mid_y = coefficients_circle->values[1];
      float cir_mid_z = coefficients_circle->values[2];

      // extract_2.setInputCloud (cloud_cylinder);
      // extract_2.setIndices (inliers_plane);
      // extract_2.setNegative (false);
      // extract_2.filter (*cloud_circle_plane);

      //Scene enthält nur noch ungefilterte Objekte


       //*cloud_cylinder += *cloud_cylinder_end;

      //Aktuelle Cloud wird in Vektor gespeichertr
      auto cloud_copy = pcl::make_shared<pcl::PointCloud<PointClNormal>>(*cloud_cylinder);
      object_vec.push_back(cloud_copy);

      //std::cerr << "PointCloud representing Object_vec: " << object_vec[number_cylinders]->size() << " data points." << std::endl;

      //Transformation der Zylinder-Koordianten in das World Koordinatensystem

      //RCLCPP_INFO(this->get_logger(),"Cloud-Cylinder: %i",cloud_cylinder->points.empty());

      Eigen::Vector3f koo_kreismittelp_camera(cir_mid_x, cir_mid_y, cir_mid_z);
      Eigen::Vector3f koo_zylaxis_camera(cyl_axis_x, cyl_axis_y, cyl_axis_z);
      Eigen::Vector3f koo_zylaxis_point_camera(cyl_axis_point_x, cyl_axis_point_y, cyl_axis_point_z);

      Eigen::Vector3f koo_kreismittelp_world;
      Eigen::Vector3f koo_zylaxis_world;
      Eigen::Vector3f koo_zylaxispoint_world;

      koo_kreismittelp_world = transform_3.rotation() * koo_kreismittelp_camera + transform_3.translation();
      koo_zylaxis_world = transform_3.rotation() * koo_zylaxis_camera;
      koo_zylaxispoint_world = transform_3.rotation() * koo_zylaxis_point_camera + transform_3.translation();

      RCLCPP_INFO(this->get_logger(),"X_Circle_mid: %f \n Y_Circle_mid: %f \n Z_Circle_mid: %f \n ", koo_kreismittelp_world[0], koo_kreismittelp_world[1] ,koo_kreismittelp_world[2]);

      RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_pt: %f \n Y_Cyl_axis_pt: %f \n Z_Cyl_axis_pt: %f \n ", koo_zylaxispoint_world[0], koo_zylaxispoint_world[1] ,koo_zylaxispoint_world[2]);

      RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_vec: %f \n Y_Cyl_axis_vec: %f \n Z_Cyl_axis_vec: %f \n ", koo_zylaxis_world[0], koo_zylaxis_world[1] ,koo_zylaxis_world[2]);

      RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_pt: %f \n Y_Cyl_axis_pt: %f \n Z_Cyl_axis_pt: %f \n ", cyl_axis_point_x, cyl_axis_point_y, cyl_axis_point_z);

      RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_vec: %f \n Y_Cyl_axis_vec: %f \n Z_Cyl_axis_vec: %f \n ", cyl_axis_x, cyl_axis_y, cyl_axis_z);

      //Point Cloud wird zur Visualisierung hinzugefügt

      std::string visu_name = "cylinder_cloud_" + std::to_string(number_cylinders); 

      std::cout << "Transform-Matrix" << std::endl;
      std::cout << transform_3.matrix() << std::endl;
      std::cout << "Rotation-Block" << std::endl;
      std::cout << transform_3.rotation() << std::endl;
      std::cout << "Translation-Block" << std::endl;
      std::cout << transform_3.translation() << std::endl;
    
      visu_ransac.addPointCloud (object_vec[number_cylinders], ColorHandlerNormal (object_vec[number_cylinders], 0.0, 255.0, 0.0), visu_name);
      visu_ransac.addPointCloud (cloud_cylinder_end, ColorHandlerNormal (cloud_cylinder_end, 0.0, 0.0, 255.0), visu_name+"_");

      //ObjectPose Message für Publisher erstellen

      std::vector<float> cylinder_position = calculateCylinder(koo_zylaxis_world,koo_zylaxispoint_world,koo_kreismittelp_world,cyl_radius);

      message.object_type = "Cylinder";

      message.radius = cyl_radius;

      message.mid_x = cylinder_position[0];
      message.mid_y = cylinder_position[1];
      message.mid_z = cylinder_position[2];
      message.axis_x = cylinder_position[3];
      message.axis_y = cylinder_position[4];
      message.axis_z = cylinder_position[5];

      pose_publisher_->publish(message);
      
    }
  }

    //Visualisierung-----------------------------------------------------------------------------------------------------------------------------
    
    //visu_ransac.addPointCloud (object_vec[1], ColorHandlerNormal (object_vec[1], 0.0, 255.0, 0.0), "test_2");
    //visu_ransac.addCylinder(*coefficients_cylinder,"cylinder");
    visu_ransac.spin ();


//     // Estimate normals for scene
//   pcl::console::print_highlight ("Estimating object normals...\n");
//   pcl::NormalEstimationOMP<PointClNormal,PointClNormal> nest_object;

// //   pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
// //   nest_object.setSearchMethod (tree);

//   //nest_object.setRadiusSearch (0.01);
//   nest_object.setSearchMethod (tree);
//   nest_object.setKSearch(10);
//   nest_object.setInputCloud (object);
//   //nest_object.setSearchSurface (object);
//   nest_object.setViewPoint(vx,vy,vz);
//   nest_object.compute (*object);

//   int size_object_normal= object->size();

//   RCLCPP_INFO(this->get_logger(),"Size: %i", size_object_normal);


//     //pcl::flipNormalTowardsViewpoint (*object, vx, vy, vz, *object_normal);

//     visu_2.addPointCloud(object, ColorHandlerNormal(object, 255.0, 0.0, 0.0), "Projektion_object");
//     visu_2.addPointCloud(scene, ColorHandlerNormal(scene, 0.0, 255.0, 0.0), "Projektion_scene");
    
//     int level_obj = 5, level_scene = 10;
//     float scale = (0.0199999995529651642F);

//     visu_2.addPointCloudNormals<PointClNormal,PointClNormal>(scene, scene, level_scene, scale, "SceneNormal");
//     visu_2.addPointCloudNormals<PointClNormal,PointClNormal>(object, object, level_obj , scale , "ObjectNormal");
//     visu_2.spin();
  
//   // Estimate features
//   pcl::console::print_highlight ("Estimating features...\n");

//   FeatureEstimationT fest;
//   //fest.setRadiusSearch (0.010);
//   fest.setSearchMethod(tree);
//   fest.setKSearch(10);
//   fest.setInputCloud (object);
//   fest.setInputNormals (object);
//   fest.compute (*object_features);
//   fest.setInputCloud (scene);
//   fest.setInputNormals (scene);
//   fest.compute (*scene_features);

//   int feat_count_scene = scene_features->size();
//   int feat_count_object = object_features->size();


//   pcl::console::print_highlight ("Features Scene: %i\n Features Object: %i \n", feat_count_scene, feat_count_object);


//   pcl::SampleConsensusPrerejective<PointClNormal,PointClNormal,FeatureT> align_object;
//   align_object.setInputSource (object);
//   align_object.setSourceFeatures (object_features);
//   align_object.setInputTarget (scene);
//   align_object.setTargetFeatures (scene_features);

//   // align_object.setInputSource (scene);
//   // align_object.setSourceFeatures (scene_features);
//   // align_object.setInputTarget (object);
//   // align_object.setTargetFeatures (object_features);

//   align_object.setMaximumIterations (50000); // Number of RANSAC iterations
//   align_object.setNumberOfSamples (3); // Number of points to sample for generating/prerejecting a pose
//   align_object.setCorrespondenceRandomness (5); // Number of nearest features to use
//   align_object.setSimilarityThreshold (0.90f); // Polygonal edge length similarity threshold
//   align_object.setMaxCorrespondenceDistance (0.8f * leaf); // Inlier threshold
//   align_object.setInlierFraction (0.99f); // Required inlier fraction for accepting a pose hypothesis
//   {
//     pcl::ScopeTime t("Alignment");
//     align_object.align (*object_aligned);
//   }


  
//   if (align_object.hasConverged ())
//   {
//     // Print results
//     printf ("\n");
//     Eigen::Matrix4f transformation = align_object.getFinalTransformation ();
//     pcl::console::print_info ("    | %6.3f %6.3f %6.3f | \n", transformation (0,0), transformation (0,1), transformation (0,2));
//     pcl::console::print_info ("R = | %6.3f %6.3f %6.3f | \n", transformation (1,0), transformation (1,1), transformation (1,2));
//     pcl::console::print_info ("    | %6.3f %6.3f %6.3f | \n", transformation (2,0), transformation (2,1), transformation (2,2));
//     pcl::console::print_info ("\n");
//     pcl::console::print_info ("t = < %0.3f, %0.3f, %0.3f >\n", transformation (0,3), transformation (1,3), transformation (2,3));
//     pcl::console::print_info ("\n");
//     pcl::console::print_info ("Inliers: %i/%i\n", align_object.getInliers ().size (), object->size ());
    
//     // Show alignment
//     pcl::visualization::PCLVisualizer visu("TEST");
//     visu.addPointCloud (scene, ColorHandlerNormal (scene, 0.0, 255.0, 0.0), "scene");
//     visu.addPointCloud (object_aligned, ColorHandlerNormal (object_aligned, 255.0, 0.0, 0.0), "object_aligned");
//     visu.spin ();
//   }
//   else
//   {
//     pcl::console::print_error ("Alignment failed!\n");

//     rclcpp::shutdown();
//     return;
//   }

  return;
}

std::vector<float> PointCloudProcessor::calculateCylinder(Eigen::Vector3f zylaxis,Eigen::Vector3f zylaxispoint,Eigen::Vector3f circlepoint, float radius){

  //Koordinaten bereits in World-KYS konvertiert --> in processPointCloud()
  //Ebene aus Circle-Point und Cylinderachse als Normale wird mit Gerade aus Cylinderachse und Achsaufpunkt verschnitten --> exakter Mittenpunkt an Zylinderkopf

    std::cout<< "calculateCylinder wurde aufgerufen"<< std::endl;

    std::vector<float> cylinder_position{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::vector<float> schnittpunkt{0.0, 0.0, 0.0};

    float zaehler = 0;
    float nenner = 0;
   
    
    for (int i = 0; i <= 2; i++){
    
      zaehler += zylaxis[i]*(zylaxispoint[i]-circlepoint[i]);
      nenner += zylaxis[i]*zylaxis[i];
    }

    std::cout<< "Schleife_1 beendet"<< std::endl;

    std::cout<< "Zaehler: "<< zaehler <<"\n"<<"Nenner: " << nenner << std::endl;

    float t = -zaehler/nenner;

    //Mittelpunkt des Cylinders berechnen

    std::cout<< "t: "<< t << std::endl;

    std::cout<< "Eigenvektor_wert: "<< zylaxispoint[0] << std::endl;



    //Vektorlenge wird auf 2*Radius normiert für den Abstand von Stirnseite zu Mittelpunkt des Cylinders


    

    for (int i = 0; i <= 2; i++){

      // cylinder_position entspricht Schnittpunkt = Geradengleichung + Orientierungsvektor normiert auf Länge bis Mittelpunkt
    
      schnittpunkt[i] = zylaxispoint[i] + (t * zylaxis[i]);
    }

    std::cout<< "Schleife_2 beendet"<< std::endl;


    //Vektor zwischen Mittenpunkt am Zylinderkopf und dem Achsenaufpunkt liefert exakte Orienterirung X,Y,Z 
    for (int i = 0; i <= 2; i++){
    
      cylinder_position[3+i] = zylaxispoint[i]-schnittpunkt[i];
    }

    float koeff = sqrt((2*radius)*(2*radius)/(cylinder_position[3]*cylinder_position[3]+cylinder_position[4]*cylinder_position[4]+cylinder_position[5]*cylinder_position[5]));

    std::cout<< "Koeffizient: "<< koeff << std::endl;

    for (int i = 0; i <= 2; i++){

      //Mittelpunkt = Schnittpunkt + Normierter Vektor zwischen Schnittpunkt und Aufpunkt auf der Cylinderachse
    
      cylinder_position[i] = schnittpunkt[i] + koeff * cylinder_position[3+i]; 
    }


  return cylinder_position; //Return der Calinderposition [0] bis [2] ist der Mittelpunkt auf Stirnseite , [3] bis [5] ist die Orientierung relativ zu Mittenpunkt auf Stirnseite
}

int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);

    auto node_point_cloud_processor = std::make_shared<PointCloudProcessor>();
    
    node_point_cloud_processor->generate_cylinder_master();
    
    rclcpp::spin(node_point_cloud_processor);

    //rclcpp::shutdown();
    

    return 0;
}