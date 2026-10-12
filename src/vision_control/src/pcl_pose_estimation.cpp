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
#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/features/range_image_border_extractor.h>

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
        std::vector<pcl::PointCloud<PointClNormal>::Ptr> clusterPointCloud();
        void filterPointCloud();
        void getPointCloud(sensor_msgs::msg::PointCloud2 msg);
        std::vector<float> calculateCylinder(Eigen::Vector3f,Eigen::Vector3f,Eigen::Vector3f,float,Eigen::Vector3f);
        void edgeDetection();

        rclcpp::Publisher<robot_interfaces::msg::ObjectPose>::SharedPtr pose_publisher_;

        
    private:

        pcl::PointCloud<PointClNormal>::Ptr output ;
        pcl::PointCloud<PointClNormal>::Ptr cloud;
        PointCloudN scene_cloud;
        PointCloudN::Ptr scene = std::make_shared<PointCloudN>();
        PointCloudN::Ptr scene_before_downsampling = std::make_shared<PointCloudN>();
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

std::vector<pcl::PointCloud<PointClNormal>::Ptr> PointCloudProcessor::clusterPointCloud(){

  //pcl::visualization::PCLVisualizer visu_cluster("Cluster_Scene");

  // Creating the KdTree object for the search method of the extraction
  pcl::search::KdTree<PointClNormal>::Ptr tree (new pcl::search::KdTree<PointClNormal>);

  tree->setInputCloud (scene);

  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<PointClNormal> ec;
  ec.setClusterTolerance (0.02); // 2cm
  ec.setMinClusterSize (500);
  ec.setMaxClusterSize (5000);
  ec.setSearchMethod (tree);
  ec.setInputCloud (scene);
  ec.extract (cluster_indices);

  //RCLCPP_INFO(this->get_logger(),"Extract Cluster Indizes succeded"); 
  //RCLCPP_INFO(this->get_logger(),"Extract Cluster Indizes size: %i", cluster_indices.size()); 
  
  std::vector<pcl::PointCloud<PointClNormal>::Ptr> cluster_vec;

  int j = 0;

  //RCLCPP_INFO(this->get_logger(),"Extract Cluster Indizes succeded");

  for (const auto& cluster : cluster_indices){

    //RCLCPP_INFO(this->get_logger(),"Test For-Schleife 1"); 
    pcl::PointCloud<PointClNormal>::Ptr cloud_cluster (new pcl::PointCloud<PointClNormal>);
    
    for (const auto& idx : cluster.indices) {
      //RCLCPP_INFO(this->get_logger(),"Test For-Schleife 2"); 
      cloud_cluster->push_back((*scene)[idx]); //Scene Punktewolke wird nach Indizes des jeweiligen Clusters extrahiert
      //RCLCPP_INFO(this->get_logger(),"Extract into cloud_cluster erfolgreich"); 
    } 

    //if (cloud_cluster->size () < 500){ RCLCPP_INFO(this->get_logger(),"Cluster verworfen"); j++; }

    //else{

      cloud_cluster->width = cloud_cluster->size ();
      cloud_cluster->height = 1;
      cloud_cluster->is_dense = true;

      std::cout << "PointCloud representing the Cluster: " << cloud_cluster->size () << " data points." << std::endl;

      auto cluster_copy = pcl::make_shared<pcl::PointCloud<PointClNormal>>(*cloud_cluster);

      //RCLCPP_INFO(this->get_logger(),"Copy erfolgreich"); 

      cluster_vec.push_back(cluster_copy);

      

      //RCLCPP_INFO(this->get_logger(),"Schleife erfolgreich"); 

      std::string visu_name = "clustered_cloud_" + std::to_string(j); 

      double r = 0.0, g = 0.0, b = 0.0;

      if ((j % 2) == 0){r = 255.0; g = 0.0, b = 0.0;}

      if ((j % 3) == 0){r = 0.0; g = 255.0, b = 0.0;}

      else{r = 0.0; g = 0.0, b = 255.0;}

      //visu_cluster.addPointCloud (cluster_vec[j], ColorHandlerNormal (cluster_vec[j], r, g, b), visu_name);

      //RCLCPP_INFO(this->get_logger(),"Add to Visu erfolgreich"); 

      std::cout << "Cluster-Vektor-Size: " << cluster_vec.size () << " Elements" << std::endl;

      j++;

    //}
  }

  //RCLCPP_INFO(this->get_logger(),"Visu start"); 
  
  //visu_cluster.spin();

  return cluster_vec;
}

void PointCloudProcessor::processPointCloud(){

  pcl::visualization::PCLVisualizer visu_ransac("Cylinder-Segmentation");
 //Umrechnung der Koordinaten--------------------------------------------------------------------------------------------------------------------------

  Eigen::Affine3f transform_3 = Eigen::Affine3f::Identity();

  float phi_x = 0.263; //X und Y Achse sind vertauscht gegenüber SDF 
  float phi_y = 0.0;
  float phi_z = -1.57;
  
  transform_3.translation() << -0.3, 0.0, 1.2;

  // The same rotation matrix as before; theta radians around Z axis
  transform_3.rotate (Eigen::AngleAxisf (phi_x, Eigen::Vector3f::UnitX()));
  transform_3.rotate (Eigen::AngleAxisf (phi_y, Eigen::Vector3f::UnitY()));
  transform_3.rotate (Eigen::AngleAxisf (phi_z, Eigen::Vector3f::UnitZ()));

  Eigen::Matrix3f transform_rotation = transform_3.rotation();
  Eigen::Vector3f transform_translation = transform_3.translation();

  //pcl::transformPointCloud (*scene_before_downsampling, scene_cloud, transform_3);
  pcl::transformPointCloud (scene_cloud,*scene_before_downsampling, transform_3);
  visu_ransac.addPointCloud (scene_before_downsampling, ColorHandlerNormal (scene_before_downsampling, 255.0, 0.0, 0.0), "scene");
  //Aufruf der separaten Filterfunktion
  filterPointCloud();

  std::cout<<"Filtering abgeschlossen"<< std::endl;

  //Cluster returnde Vector mit einzelnen Clustern aus Scene
  std::vector<std::shared_ptr<PointCloudN>> cluster_vec = clusterPointCloud();

  std::cout<<"Vektor-Size: "<< cluster_vec.size() << " Elements" << std::endl;


  pcl::search::KdTree<PointClNormal>::Ptr tree (new pcl::search::KdTree<PointClNormal> ());

  float vx = 0, vy = 0 , vz = 0;
  int number_cylinders = 0;

  auto message = robot_interfaces::msg::ObjectPose();

  //For Schleife zum bestimmen der Cylinder im Cluster-vector ----------------------------------------------------------------------------------------------
 
  for(auto& cluster_count : cluster_vec){

    // Estimate normals for scene
    pcl::console::print_highlight ("Estimating scene normals...\n");
    pcl::NormalEstimationOMP<PointClNormal,PointClNormal> nest;

    nest.setSearchMethod (tree);
    nest.setKSearch(10);
    nest.setViewPoint(vx,vy,vz);
    nest.setInputCloud (cluster_count);
    nest.compute (*cluster_count);

    pcl::PointCloud<PointClNormal>::Ptr cloud_cylinder (new pcl::PointCloud<PointClNormal> ());
    pcl::PointCloud<PointClNormal>::Ptr cloud_circle_plane (new pcl::PointCloud<PointClNormal> ());
    pcl::PointCloud<PointClNormal>::Ptr scene_before (new pcl::PointCloud<PointClNormal> ());
    // std::vector<pcl::PointCloud<PointClNormal>::Ptr> object_vec;

    pcl::ModelCoefficients::Ptr coefficients_cylinder (new pcl::ModelCoefficients);
    pcl::ModelCoefficients::Ptr coefficients_circle (new pcl::ModelCoefficients);
    pcl::ModelCoefficients::Ptr coefficients_plane (new pcl::ModelCoefficients);

    pcl::PointIndices::Ptr inliers_cylinder (new pcl::PointIndices);
    pcl::PointIndices::Ptr inliers_circle (new pcl::PointIndices);
    pcl::PointIndices::Ptr inliers_plane (new pcl::PointIndices);
    pcl::PointIndices::Ptr cylinder_mantel(new pcl::PointIndices);

    pcl::ExtractIndices<PointClNormal> extract;
    pcl::ExtractIndices<PointClNormal> extract_2;

    // Create the segmentation object for cylinder segmentation and set all the parameters

    pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg;
    seg.setOptimizeCoefficients (true);
    seg.setModelType (pcl::SACMODEL_CYLINDER);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setNormalDistanceWeight (0.3);
    seg.setMaxIterations (10000);
    seg.setDistanceThreshold (0.008);
    seg.setRadiusLimits (0.048, 0.052);
    seg.setInputCloud (cluster_count);
    seg.setInputNormals (cluster_count);
    seg.segment (*inliers_cylinder, *coefficients_cylinder);

    if (inliers_cylinder->indices.size () <= 300) { std::cerr << "Cluster had no Cylinder in it" << std::endl;}
    
    else {
      //std::cerr << "Cylinder coefficients: " << *coefficients_cylinder << std::endl;

      float cyl_axis_point_x = coefficients_cylinder->values[0];
      float cyl_axis_point_y = coefficients_cylinder->values[1];
      float cyl_axis_point_z = coefficients_cylinder->values[2];

      float cyl_axis_x = coefficients_cylinder->values[3];
      float cyl_axis_y = coefficients_cylinder->values[4];
      float cyl_axis_z = coefficients_cylinder->values[5];

      //extrahiertes Objekt
      extract.setInputCloud (cluster_count);
      extract.setIndices (inliers_cylinder);
      extract.setNegative (false);
      extract.filter (*cloud_cylinder);
      extract.setNegative (true);
      extract.filter(*cluster_count);


      PointCloudN::Ptr cloud_cylinder_end (new PointCloudN); //Cloud für Stirnseite des Zylinders

      for (const auto& point : *cluster_count){

        float X = point.x;
        float Y = point.y;
        float Z = point.z;
        float radius_bb = 0.045;

        float t = ((X- cyl_axis_point_x) * cyl_axis_x + (Y - cyl_axis_point_y) * cyl_axis_y + (Z- cyl_axis_point_z) * cyl_axis_z)/(pow(cyl_axis_x,2)+pow(cyl_axis_y,2)+pow(cyl_axis_z,2));

        float distance = sqrt(pow(X-(cyl_axis_point_x+t*cyl_axis_x),2) + pow(Y-(cyl_axis_point_y+t*cyl_axis_y),2) + pow(Z-(cyl_axis_point_z+t*cyl_axis_z),2));

        if (distance <= radius_bb){

          cloud_cylinder_end->push_back(point);

        }
      }

      if (cloud_cylinder_end->points.empty() == true ) { std::cout << "Cloud is Cylinder_end is empty"<< std::endl;}
  
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

      pcl::MomentOfInertiaEstimation <PointClNormal> feature_extractor;
      feature_extractor.setInputCloud (cloud_cylinder);
      feature_extractor.compute ();
      std::vector <float> moment_of_inertia;
      std::vector <float> eccentricity;

      Eigen::Vector3f major_vector, middle_vector, minor_vector;
      Eigen::Vector3f mass_center;

      feature_extractor.getMomentOfInertia (moment_of_inertia);
      feature_extractor.getEccentricity (eccentricity);
      feature_extractor.getMassCenter (mass_center);
      feature_extractor.getEigenVectors (major_vector, middle_vector, minor_vector);

      //Aktuelle Cloud wird in Vektor gespeichert
      // auto cloud_copy = pcl::make_shared<pcl::PointCloud<PointClNormal>>(*cloud_cylinder);
      // object_vec.push_back(cloud_copy);

      Eigen::Vector3f koo_kreismittelp_world(cir_mid_x, cir_mid_y, cir_mid_z);
      Eigen::Vector3f koo_zylaxis_world(cyl_axis_x, cyl_axis_y, cyl_axis_z);
      Eigen::Vector3f koo_zylaxispoint_world(cyl_axis_point_x, cyl_axis_point_y, cyl_axis_point_z);
      Eigen::Vector3f koo_masscenter_world (mass_center (0), mass_center (1), mass_center (2));

      // RCLCPP_INFO(this->get_logger(),"X_Circle_mid: %f \n Y_Circle_mid: %f \n Z_Circle_mid: %f \n ", koo_kreismittelp_world[0], koo_kreismittelp_world[1] ,koo_kreismittelp_world[2]);
      // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_pt: %f \n Y_Cyl_axis_pt: %f \n Z_Cyl_axis_pt: %f \n ", koo_zylaxispoint_world[0], koo_zylaxispoint_world[1] ,koo_zylaxispoint_world[2]);
      // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_vec: %f \n Y_Cyl_axis_vec: %f \n Z_Cyl_axis_vec: %f \n ", koo_zylaxis_world[0], koo_zylaxis_world[1] ,koo_zylaxis_world[2]);
      // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_pt: %f \n Y_Cyl_axis_pt: %f \n Z_Cyl_axis_pt: %f \n ", cyl_axis_point_x, cyl_axis_point_y, cyl_axis_point_z);
      // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_vec: %f \n Y_Cyl_axis_vec: %f \n Z_Cyl_axis_vec: %f \n ", cyl_axis_x, cyl_axis_y, cyl_axis_z);

      //Point Cloud wird zur Visualisierung hinzugefügt

      std::string visu_name = "cylinder_cloud_" + std::to_string(number_cylinders); 

      std::cout << "Masscenter:" << std::endl;
      std::cout << koo_masscenter_world[0] << std::endl;
      std::cout << koo_masscenter_world[1] << std::endl;
      std::cout << koo_masscenter_world[2] << std::endl;

      pcl::PointXYZ y_axis (major_vector (0) + mass_center (0), major_vector (1) + mass_center (1), major_vector (2) + mass_center (2));

      RCLCPP_INFO(this->get_logger(),"Number Cylinder: %i", number_cylinders);
      visu_ransac.addPointCloud (cloud_cylinder, ColorHandlerNormal (cloud_cylinder, 0.0, 255.0, 0.0), visu_name);
      visu_ransac.addPointCloud (cloud_cylinder_end, ColorHandlerNormal (cloud_cylinder_end, 0.0, 0.0, 255.0), visu_name+"_");
      visu_ransac.addCoordinateSystem(0.2);


      RCLCPP_INFO(this->get_logger(),"Calculate Cylinder wird aufgerufen");

      std::vector<float> cylinder_position = calculateCylinder(koo_zylaxis_world,koo_zylaxispoint_world,koo_kreismittelp_world,cyl_radius, koo_masscenter_world);

       RCLCPP_INFO(this->get_logger(),"Message wird erstellt");

      message.object_type = "Cylinder";

      message.radius = cyl_radius;

      message.mid_x = cylinder_position[0];
      message.mid_y = cylinder_position[1];
      message.mid_z = cylinder_position[2];
      message.axis_x = cylinder_position[3];
      message.axis_y = cylinder_position[4];
      message.axis_z = cylinder_position[5];

      pose_publisher_->publish(message);

      number_cylinders++;
        
      
    } //Ende Else falls Cylinder gefunden wird
  }

  RCLCPP_INFO(this->get_logger(),"For_Schleife ist beendet");

  message.object_type = "END";
  
  pose_publisher_->publish(message);

  //Visualisierung-----------------------------------------------------------------------------------------------------------------------------
    
  visu_ransac.spin ();
  return;
}

void PointCloudProcessor::filterPointCloud(){

  pcl::PointCloud<PointClNormal>::Ptr scene_before_filtering (new pcl::PointCloud<PointClNormal>());
  // Downsample
  pcl::console::print_highlight ("Downsampling...\n");

  const float leaf = 0.005f;
  pcl::VoxelGrid<PointClNormal> grid_2;
  grid_2.setLeafSize (leaf, leaf, leaf);
  grid_2.setInputCloud (scene_before_downsampling);
  grid_2.filter (*scene_before_filtering);

  //Punktewolke nach infiniten Punkten filtern
  pcl::PointCloud<PointClNormal>::iterator pcl_begin;
  pcl::PointCloud<PointClNormal>::iterator pcl_end;

  pcl_begin = scene_before_filtering-> begin();
  pcl_end = scene_before_filtering-> end();

  for (pcl::PointCloud<PointClNormal>::iterator count = pcl_begin; count<=pcl_end;){

    if (pcl::isFinite(*count)==false){

      RCLCPP_INFO(this->get_logger(),"is NOT finite"); 

      count = scene_before_filtering->erase(count);

      RCLCPP_INFO(this->get_logger(),"Removed Point from Cloud"); 
    } 

    else {
      count++;
    }
  }

  //Filtering der groben Dimensionen

  pcl::PointCloud<PointClNormal>::Ptr cloud_filtered_x(new pcl::PointCloud<PointClNormal>());
  pcl::PassThrough<PointClNormal> pass_x;
  pass_x.setInputCloud (scene_before_filtering);
  pass_x.setFilterFieldName ("x");
  pass_x.setFilterLimits (-0.8, 0.0);
  pass_x.filter (*cloud_filtered_x);

  if(cloud_filtered_x->points.empty()){ std::cout << "X ist leer"<< std::endl;}

  pcl::PointCloud<PointClNormal>::Ptr cloud_filtered_y(new pcl::PointCloud<PointClNormal>());
  pcl::PassThrough<PointClNormal> pass_y;
  pass_y.setInputCloud (cloud_filtered_x);
  pass_y.setFilterFieldName ("y");
  pass_y.setFilterLimits (-1.8, 0.0);
  pass_y.filter (*cloud_filtered_y);

  if(cloud_filtered_y->points.empty()){ std::cout << "Y ist leer"<< std::endl;}

  pcl::PassThrough<PointClNormal> pass_z;
  pass_z.setInputCloud (cloud_filtered_y);
  pass_z.setFilterFieldName ("z");
  pass_z.setFilterLimits (0.795, 1.0);
  pass_z.filter (*scene);

  if(scene->points.empty()){ std::cout << "Z ist leer"<< std::endl;}

  // pcl::visualization::PCLVisualizer visu_test("Cylinder-Segmentation");
  // visu_test.addPointCloud (scene, ColorHandlerNormal (scene, 0.0, 255.0, 0.0), "test");
  // visu_test.addCoordinateSystem(0.2);
  // visu_test.spin();

}

std::vector<float> PointCloudProcessor::calculateCylinder(Eigen::Vector3f zylaxis,Eigen::Vector3f zylaxispoint,Eigen::Vector3f circlepoint, float radius, Eigen::Vector3f mass_center ){

  //Koordinaten bereits in World-KYS konvertiert --> in processPointCloud()
  //Ebene aus Circle-Point und Cylinderachse als Normale wird mit Gerade aus Cylinderachse und Achsaufpunkt verschnitten --> exakter Mittenpunkt an Zylinderkopf

    std::cout<< "calculateCylinder wurde aufgerufen"<< std::endl;

    std::vector<float> cylinder_position{0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::vector<float> schnittpunkt_cylaxis_cyltop{0.0, 0.0, 0.0};
    std::vector<float> schnittpunkt_massaxis_cyltop{0.0, 0.0, 0.0};

    //Schnittpunkt Cylinderachse mit Ebene aus Cylinderstirnseite 
      float zaehler = 0;
      float nenner = 0;
      
      for (int i = 0; i <= 2; i++){
      
        zaehler += zylaxis[i]*(zylaxispoint[i]-circlepoint[i]);
        nenner += zylaxis[i]*zylaxis[i];
      }

      float t = -zaehler/nenner;

      //Mittelpunkt des Cylinders berechnen

      for (int i = 0; i <= 2; i++){

        schnittpunkt_cylaxis_cyltop[i] = zylaxispoint[i] + (t * zylaxis[i]);
      }

    //Schnittpunkt zwischen Massenschwerpunkt und Cylinderstirnseite

      float zaehler_2 = 0;
      float nenner_2 = 0;
      
      //Geradenaufpunkt ist hier das Massenzentrum
      for (int i = 0; i <= 2; i++){
      
        zaehler_2 += zylaxis[i]*(mass_center[i]-circlepoint[i]);
        nenner_2 += zylaxis[i]*zylaxis[i];
      }

      float t_2 = -zaehler_2/nenner_2;

      for (int i = 0; i <= 2; i++){

        schnittpunkt_massaxis_cyltop[i] = mass_center[i] + (t_2 * zylaxis[i]);
      }


    //Vektor zwischen Mittenpunkt am Zylinderkopf und dem Achsenaufpunkt liefert exakte Orienterirung X,Y,Z 
    for (int i = 0; i <= 2; i++){
    
      cylinder_position[3+i] =  mass_center[i] - schnittpunkt_massaxis_cyltop[i];
    }

    //Vektro wird auf 2* Cylinderradius normiert da Strecke von Mittelpunkt zur Stirnseite 2* Radius entspricht
    float koeff = sqrt((2*radius)*(2*radius)/(cylinder_position[3]*cylinder_position[3]+cylinder_position[4]*cylinder_position[4]+cylinder_position[5]*cylinder_position[5]));

    for (int i = 0; i <= 2; i++){

      //Mittelpunkt = schnittpunkt_cylaxis_cyltop + Normierter Vektor zwischen schnittpunkt_cylaxis_cyltop und Aufpunkt auf der Cylinderachse
    
      cylinder_position[i] = schnittpunkt_cylaxis_cyltop[i] + koeff * cylinder_position[3+i]; 
    }

    std::cout << "Cylinder-Position:" << std::endl;
    std::cout << cylinder_position[0] << std::endl;
    std::cout << cylinder_position[1] << std::endl;
    std::cout << cylinder_position[2] << std::endl;
    std::cout << cylinder_position[3] << std::endl;
    std::cout << cylinder_position[4] << std::endl;
    std::cout << cylinder_position[5] << std::endl;

    std::cout << "Schnittpunkt y-Koordinate:" << std::endl;
    std::cout << schnittpunkt_massaxis_cyltop[1] << std::endl;


  return cylinder_position; //Return der Calinderposition [0] bis [2] ist der Mittelpunkt auf Stirnseite , [3] bis [5] ist die Orientierung relativ zu Mittenpunkt auf Stirnseite
}

void PointCloudProcessor::edgeDetection(){

  float angular_resolution = 0.5f;
  pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;

  pcl::PointCloud<PointType>& point_cloud = *point_cloud_ptr;

  Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity ());

  scene_sensor_pose = Eigen::Affine3f (Eigen::Translation3f (point_cloud.sensor_origin_[0],point_cloud.sensor_origin_[1],point_cloud.sensor_origin_[2])) *Eigen::Affine3f (point_cloud.sensor_orientation_);
  
  bool setUnseenToMaxRange = false;

  float noise_level = 0.0;
  float min_range = 0.0f;
  int border_size = 1;

  pcl::RangeImage::Ptr range_image_ptr (new pcl::RangeImage);
  pcl::RangeImage& range_image = *range_image_ptr;   
  range_image.createFromPointCloud (point_cloud, angular_resolution, pcl::deg2rad (360.0f), pcl::deg2rad (180.0f),scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size);

  pcl::RangeImageBorderExtractor border_extractor (&range_image);
  pcl::PointCloud<pcl::BorderDescription> border_descriptions;
  border_extractor.compute (border_descriptions);
}

int main(int argc, char * argv[]) {

  pcl::console::setVerbosityLevel(pcl::console::L_ALWAYS);

  rclcpp::init(argc, argv);

  auto node_point_cloud_processor = std::make_shared<PointCloudProcessor>();
  
  node_point_cloud_processor->generate_cylinder_master();
  
  rclcpp::spin(node_point_cloud_processor);

  //rclcpp::shutdown();
  

  return 0;
}