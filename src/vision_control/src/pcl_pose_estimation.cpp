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
            subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>("/rgbd_camera/points", 10,
                std::bind(&PointCloudProcessor::getPointCloud, this, std::placeholders::_1));

            // // Publisher for the filtered and downsampled point cloud
            // publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("filtered_pointcloud", 10);
        }
        void generate_cylinder_master();
        void processPointCloud();
        void getPointCloud(sensor_msgs::msg::PointCloud2 msg);
        
    private:

        pcl::PointCloud<pcl::PointXYZ>::Ptr output ;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
        PointCloudN scene_cloud;

        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;

        double cyl_radius = 0.05;
        double cyl_height = 0.202;
        int counter =0;
           
};

void PointCloudProcessor::generate_cylinder_master(){

    const std::string meshFileName = "/home/mario/master_ws/src/estun_control/meshes/Probekoerper.stl";
    pcl::PolygonMesh testMesh;
    pcl::io::loadPolygonFileSTL( meshFileName, testMesh );   
    output.reset(new pcl::PointCloud<pcl::PointXYZ>());

    pcl::fromPCLPointCloud2(testMesh.cloud, *output);

    pcl::visualization::PCLVisualizer visu("Alignment");

    cloud.reset(new pcl::PointCloud<pcl::PointXYZ>());

    double dx= 0.002;
    int spaces_z = std::floor(cyl_height/dx);
    double spacing_z= cyl_height/spaces_z;
    pcl::PointXYZ pt;

    for(double current_height = 0.0; current_height < cyl_height; current_height += spacing_z ){

        for (double i=0; i<=cyl_radius;i+=dx){

            pt.x = i;
            pt.y = sqrt(std::pow(cyl_radius,2)-std::pow(i,2));
            pt.z = current_height;
            cloud->push_back(pt);

            double dy = 2*pt.y;
            int spaces_y = std::floor(dy/dx);
            double spacing = dy/spaces_y;

            //erstellt in +y/-y punkte an boden und deckel
            if(pt.z==0 || current_height== cyl_height || (current_height+spacing_z) > cyl_height){

                for (int i = 0; i<spaces_y;i++){

                    pt.y = pt.y-spacing;
                    cloud->push_back(pt);
                    RCLCPP_INFO(this->get_logger(),"Current:height= %f",current_height);
                }
            }

            pt.y = -pt.y;
            cloud->push_back(pt);

            //negatives x koordinate
            pt.x = -pt.x;
            cloud->push_back(pt);

            //erstellt in +y/-y punkte an boden und deckel
            if(pt.z==0 || current_height== cyl_height || (current_height+spacing_z) > cyl_height){

                for (int i = 0; i<spaces_y;i++){

                    pt.y = pt.y-spacing;
                    cloud->push_back(pt);
                }
            }
            pt.y = -pt.y;
            cloud->push_back(pt);
        }
    }

    visu.addPointCloud(output, ColorHandlerT(output, 0.0, 255.0, 0.0), "Probekoerper");
    visu.addPointCloud(cloud, ColorHandlerT(cloud, 255.0, 0.0, 0.0), "Projektion");
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
  PointCloudXYZ::Ptr object (new PointCloudXYZ);
  PointCloudXYZ::Ptr scene_ (new PointCloudXYZ);
  PointCloudN::Ptr object_aligned (new PointCloudN);

  PointCloudN::Ptr scene_before_downsampling (new PointCloudN);
  PointCloudN::Ptr scene (new PointCloudN);
  PointCloudN::Ptr object_normal (new PointCloudN);

  FeatureCloudT::Ptr object_features (new FeatureCloudT);
  FeatureCloudT::Ptr scene_features (new FeatureCloudT);

  object = cloud;
  *scene_before_downsampling = scene_cloud;

//   // Load object and scene
//   pcl::console::print_highlight ("Loading point clouds...\n");
//   if (pcl::io::loadPCDFile<PointNT> (, *object) < 0 || pcl::io::loadPCDFile<PointNT> (argv[2], *scene_before_downsampling) < 0)
//   {
//     pcl::console::print_error ("Error loading object/scene file!\n");
//     return;
//   }
  

pcl::visualization::PCLVisualizer visu_2("Alignment_TEST");


  // Downsample
  pcl::console::print_highlight ("Downsampling...\n");
//   pcl::VoxelGrid<PointXYZ> grid;
     const float leaf = 0.002f;
//   grid.setLeafSize (leaf, leaf, leaf);
//   grid.setInputCloud (object);
//   grid.filter (*object);

  pcl::VoxelGrid<PointClNormal> grid_2;
  grid_2.setLeafSize (leaf, leaf, leaf);
  grid_2.setInputCloud (scene_before_downsampling);
  grid_2.filter (*scene);

    visu_2.addPointCloud(object, ColorHandlerT(object, 255.0, 0.0, 0.0), "Projektion_object");
    visu_2.addPointCloud(scene_before_downsampling, ColorHandlerNormal(scene_before_downsampling, 0.0, 255.0, 0.0), "Projektion_scene");
    visu_2.spin ();
  
  // Estimate normals for scene
  pcl::console::print_highlight ("Estimating scene normals...\n");
  pcl::NormalEstimationOMP<PointClNormal,PointClNormal> nest;
  nest.setRadiusSearch (0.005);
  nest.setInputCloud (scene);
  nest.setSearchSurface (scene_before_downsampling);
  nest.compute (*scene);

    // Estimate normals for scene
  pcl::console::print_highlight ("Estimating object normals...\n");
  pcl::NormalEstimationOMP<PointXYZ,PointClNormal> nest_object;
  nest_object.setRadiusSearch (0.005);
  nest_object.setInputCloud (object);
  nest_object.setSearchSurface (object);
  nest_object.compute (*object_normal);
  
  // Estimate features
  pcl::console::print_highlight ("Estimating features...\n");

  FeatureEstimationT fest;
  fest.setRadiusSearch (0.025);
  fest.setInputCloud (object_normal);
  fest.setInputNormals (object_normal);
  fest.compute (*object_features);
  fest.setInputCloud (scene);
  fest.setInputNormals (scene);
  fest.compute (*scene_features);
  

  pcl::SampleConsensusPrerejective<PointClNormal,PointClNormal,FeatureT> align_object;
  align_object.setInputSource (object_normal);
  align_object.setSourceFeatures (object_features);
  align_object.setInputTarget (scene);
  align_object.setTargetFeatures (scene_features);
  align_object.setMaximumIterations (50000); // Number of RANSAC iterations
  align_object.setNumberOfSamples (3); // Number of points to sample for generating/prerejecting a pose
  align_object.setCorrespondenceRandomness (10); // Number of nearest features to use
  align_object.setSimilarityThreshold (0.5f); // Polygonal edge length similarity threshold
  align_object.setMaxCorrespondenceDistance (5.0f * leaf); // Inlier threshold
  align_object.setInlierFraction (0.10f); // Required inlier fraction for accepting a pose hypothesis
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
    visu.addPointCloud (object_aligned, ColorHandlerNormal (object_aligned, 0.0, 0.0, 255.0), "object_aligned");
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