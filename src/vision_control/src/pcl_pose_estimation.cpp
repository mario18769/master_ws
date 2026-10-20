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
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/common/intersections.h>

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
        std::vector<float> calculateCylinderEnd(pcl::PointCloud<PointClNormal>::Ptr,Eigen::Vector3f,Eigen::Vector3f);
        std::vector<float> calculateCube(std::vector<Eigen::Vector4f>,std::shared_ptr<PointCloudN>);
        std::vector<float> calculateCubeCenter(std::vector<Eigen::Vector4f>,std::shared_ptr<PointCloudN>);
        void edgeDetection(std::shared_ptr<PointCloudN>);
        

        rclcpp::Publisher<robot_interfaces::msg::ObjectPose>::SharedPtr pose_publisher_;

        
    private:

        pcl::PointCloud<PointClNormal>::Ptr output ;
        pcl::PointCloud<PointClNormal>::Ptr cloud;
        PointCloudN scene_cloud;
        PointCloudN::Ptr scene = std::make_shared<PointCloudN>();
        PointCloudN::Ptr scene_before_downsampling = std::make_shared<PointCloudN>();
        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
        PointCloudN::Ptr scene_edgeDetection = std::make_shared<PointCloudN>();
        
        float cyl_radius = 0.05;
        float cyl_height = 0.200;
        int pter =0;
           
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

      if (pter==0){
          
          RCLCPP_INFO(this->get_logger(),"RUN ProcessPointCloud");
          processPointCloud();
          pter=1;
      }

  // if (pter==0){
      
  //     RCLCPP_INFO(this->get_logger(),"RUN ClusterPointCloud");
  //     clusterPointCloud();
  //     pter=1;
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

  *scene_edgeDetection = scene_cloud;

  //edgeDetection();
  //std::cout<<"Edge-Detection abgeschlossen"<< std::endl;

  //pcl::transformPointCloud (*scene_before_downsampling, scene_cloud, transform_3);
  pcl::transformPointCloud (scene_cloud,*scene_before_downsampling, transform_3);
  
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

  pcl::PointCloud<PointClNormal>::Ptr copy_cloud (new pcl::PointCloud<PointClNormal> ());

  //For Schleife zum bestimmen der Cylinder im Cluster-vector ----------------------------------------------------------------------------------------------
  
  pcl::visualization::PCLVisualizer visu_ransac("Cylinder-Segmentation");

  for(auto& cluster_pt : cluster_vec){

    *copy_cloud = *cluster_pt;
    bool clusterempty = false;

    // Estimate normals for scene
    pcl::console::print_highlight ("Estimating scene normals...\n");
    pcl::NormalEstimationOMP<PointClNormal,PointClNormal> nest;

    nest.setSearchMethod (tree);
    nest.setKSearch(10);
    nest.setViewPoint(vx,vy,vz);
    nest.setInputCloud (cluster_pt);
    nest.compute (*cluster_pt);

    //Cylinder Pointer Objekte
    pcl::PointCloud<PointClNormal>::Ptr cloud_cylinder (new pcl::PointCloud<PointClNormal> ());
    pcl::PointIndices::Ptr inliers_cylinder (new pcl::PointIndices);
    pcl::PointIndices::Ptr inliers_circle_plane (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients_cylinder (new pcl::ModelCoefficients);
    pcl::ModelCoefficients::Ptr coefficients_circle (new pcl::ModelCoefficients);
    pcl::ExtractIndices<PointClNormal> extract;

    //Würfel Pointer Objekte

    //Erste Ebene
    pcl::PointCloud<PointClNormal>::Ptr cloud_cube (new pcl::PointCloud<PointClNormal> ());
    pcl::PointIndices::Ptr inliers_cube_plane (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients_plane (new pcl::ModelCoefficients);
    pcl::ExtractIndices<PointClNormal> extract_cube;

    //Erste rechtwinklige Ebene
    pcl::PointIndices::Ptr inliers_cube_plane_perpend (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients_plane_perpend (new pcl::ModelCoefficients);
    pcl::PointCloud<PointClNormal>::Ptr cloud_cube_perpend (new pcl::PointCloud<PointClNormal> ());

    // Create the segmentation object for cylinder segmentation and set all the parameters
    pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg;
    seg.setOptimizeCoefficients (true);
    seg.setModelType (pcl::SACMODEL_CYLINDER);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setNormalDistanceWeight (0.3);
    seg.setMaxIterations (10000);
    seg.setDistanceThreshold (0.008);
    seg.setRadiusLimits (0.048, 0.052);
    seg.setInputCloud (cluster_pt);
    seg.setInputNormals (cluster_pt);
    seg.segment (*inliers_cylinder, *coefficients_cylinder);

    //Cube Berechnung --------------------------------------------------------------------------------------------------------
    if (inliers_cylinder->indices.size () <= 300) { 
      
      std::cout << "Cluster had no Cylinder in it, Checking for Cubes" << std::endl;

      std::string visu_name = "plane_cloud_" + std::to_string(number_cylinders);
      
      pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg_cube;
      seg_cube.setOptimizeCoefficients (true);
      seg_cube.setModelType (pcl::SACMODEL_PLANE);
      seg_cube.setMethodType (pcl::SAC_RANSAC);
      seg_cube.setNormalDistanceWeight (0.3);
      seg_cube.setMaxIterations (10000);
      seg_cube.setDistanceThreshold (0.002);
      seg_cube.setInputCloud (cluster_pt);
      seg_cube.setInputNormals (cluster_pt);
      seg_cube.segment (*inliers_cube_plane, *coefficients_plane);
      
      // std::cout << "Axis Normal to Plane:" << std::endl;
      // std::cout << coefficients_plane->values[0]<< std::endl;
      // std::cout << coefficients_plane->values[1]<< std::endl;
      // std::cout << coefficients_plane->values[2]<< std::endl;

      Eigen::Vector3f plane_normal (coefficients_plane->values[0],coefficients_plane->values[1],coefficients_plane->values[2]);
      Eigen::Vector4f first_plane_coeff (0.0, 0.0, 0.0, 0.0);

      first_plane_coeff[0] = coefficients_plane->values[0];
      first_plane_coeff[1] = coefficients_plane->values[1];
      first_plane_coeff[2] = coefficients_plane->values[2];
      first_plane_coeff[3] = coefficients_plane->values[3];
      
      if (inliers_cube_plane->indices.size () <= 10) { std::cout << "Cluster had no Cube in it" << std::endl;}

      else{

        //edgeDetection(cluster_pt);

        std::vector<Eigen::Vector4f> cube_plane_vectors;

        cube_plane_vectors.push_back(first_plane_coeff);

        //extrahiertes Objekt
        extract_cube.setInputCloud (cluster_pt);
        extract_cube.setIndices (inliers_cube_plane);
        extract_cube.setNegative (false);
        extract_cube.filter (*cloud_cube); //gefundene Plane Points in cloud_cube schreiben
        extract_cube.setNegative (true); //Ausschneiden der gefundenen Plane aus gesamter Clusterwolke
        extract_cube.filter(*cluster_pt); 

        visu_ransac.addPointCloud (cloud_cube, ColorHandlerNormal (cloud_cube, 0.0, 255.0, 255.0), visu_name);

        //Suchen aller rechtwinkliger Seitenflächen in For-Schleife bis ClusterCloud leer ist
        
        for(int i = 0; clusterempty == false; i++){

          pcl::SACSegmentationFromNormals<PointClNormal, PointClNormal> seg_cube_perpend;
          seg_cube_perpend.setOptimizeCoefficients (true);
          seg_cube_perpend.setModelType (pcl::SACMODEL_PERPENDICULAR_PLANE);
          seg_cube_perpend.setMethodType (pcl::SAC_RANSAC);
          seg_cube_perpend.setAxis(plane_normal);
          seg_cube_perpend.setNormalDistanceWeight (0.3);
          seg_cube_perpend.setMaxIterations (10000);
          seg_cube_perpend.setDistanceThreshold (0.002);
          seg_cube_perpend.setInputCloud (cluster_pt);
          seg_cube_perpend.setInputNormals (cluster_pt);
          seg_cube_perpend.segment (*inliers_cube_plane_perpend, *coefficients_plane_perpend);

          if (inliers_cube_plane_perpend->indices.size () <= 10) { 
            std::cout << "Cluster had no/no more perpendicular Plane in it" << std::endl; 
            clusterempty = true;
            
          }

          else{
            std::cout << "Found perpendicular Plane with Number: " << i << std::endl;
            Eigen::Vector4f perpend_plane_coeff (coefficients_plane_perpend->values[0], coefficients_plane_perpend->values[1], coefficients_plane_perpend->values[2], coefficients_plane_perpend->values[3]);

            cube_plane_vectors.push_back(perpend_plane_coeff); //Neue Plane Vektor für Coeffizienten werden in übergeordneten Vektor des Würfels geschrieben

            plane_normal[0] = coefficients_plane_perpend->values[0];
            plane_normal[1] = coefficients_plane_perpend->values[1];
            plane_normal[2] = coefficients_plane_perpend->values[2];

            extract_cube.setInputCloud (cluster_pt);
            extract_cube.setIndices (inliers_cube_plane_perpend);
            extract_cube.setNegative (false);
            extract_cube.filter (*cloud_cube_perpend); 
            extract_cube.setNegative (true); //Ausschneiden der gefundenen Plane aus gesamter Clusterwolke
            extract_cube.filter(*cluster_pt); 
            
            visu_ransac.addPointCloud (cloud_cube_perpend, ColorHandlerNormal (cloud_cube_perpend, 0.0, 0.0, 255.0), "ClusterNumber_"+ std::to_string(number_cylinders)+ " / PerpendPlane Number: " + std::to_string(i));

            number_cylinders++;
            
          }
        }
        //Alle rechtwinklinge Planes wurden zur ersten Plane gefunden und in Vektor cube_plane_vektors geschrieben
        std::vector<float> cube_position = calculateCube(cube_plane_vectors, copy_cloud);
        std::cout << "Sending Message for Cube " << std::endl;
        message.object_type = "Cube";

        message.length = 0.1;
        message.mid_x = cube_position[0];
        message.mid_y = cube_position[1];
        message.mid_z = cube_position[2];
        message.q_x = cube_position[3];
        message.q_y = cube_position[4];
        message.q_z = cube_position[5];
        message.q_w = cube_position[6];

        pose_publisher_->publish(message);

        //Nachdem Würfel-Position und Orientierung berechnend wurde kann MSG an ObstaclePlanner geschickt werden
      }
    }
    
    //Zylinder wurde erkannt und weitere Verarbeitung erfolgt im Else-Zweig---------------------------------------------------
    else {
      std::cout << "Cylinder wurde erkannt"<< std::endl;

      float cyl_axis_point_x = coefficients_cylinder->values[0];
      float cyl_axis_point_y = coefficients_cylinder->values[1];
      float cyl_axis_point_z = coefficients_cylinder->values[2];

      float cyl_axis_x = coefficients_cylinder->values[3];
      float cyl_axis_y = coefficients_cylinder->values[4];
      float cyl_axis_z = coefficients_cylinder->values[5];

      Eigen::Vector3f koo_zylaxis_world(cyl_axis_x, cyl_axis_y, cyl_axis_z);
      Eigen::Vector3f koo_zylaxispoint_world(cyl_axis_point_x, cyl_axis_point_y, cyl_axis_point_z);

      //extrahiertes Objekt
      extract.setInputCloud (cluster_pt);
      extract.setIndices (inliers_cylinder);
      extract.setNegative (false);
      extract.filter (*cloud_cylinder); //Cloud mit Puntken der Cylinderwandung
      extract.setNegative (true);
      extract.filter(*cluster_pt); //Hier sind nur noch die Punkte der Stirnseiten des Cylinders enthalten


      PointCloudN::Ptr cloud_cylinder_end (new PointCloudN); //Cloud für Stirnseite des Zylinders
      std::cout << "Test_1"<< std::endl;
      int counter_cylinder_end = 0;
      for (const auto& point : *cluster_pt){

        float X = point.x;
        float Y = point.y;
        float Z = point.z;
        float radius_bb = 0.045;

        float t = ((X- cyl_axis_point_x) * cyl_axis_x + (Y - cyl_axis_point_y) * cyl_axis_y + (Z- cyl_axis_point_z) * cyl_axis_z)/(pow(cyl_axis_x,2)+pow(cyl_axis_y,2)+pow(cyl_axis_z,2));

        float distance = sqrt(pow(X-(cyl_axis_point_x+t*cyl_axis_x),2) + pow(Y-(cyl_axis_point_y+t*cyl_axis_y),2) + pow(Z-(cyl_axis_point_z+t*cyl_axis_z),2));

        if (distance <= radius_bb){

          cloud_cylinder_end->push_back(point);
          counter_cylinder_end++;
        }
      }

      std::cout << "Test_2"<< std::endl;
      std::cout << "Is empty: "<< cloud_cylinder_end->points.empty()<< std::endl;

      if (cloud_cylinder_end->points.empty() == true) { std::cout << "Cloud-Cylinder_End is empty"<< std::endl;}

      std::cout << "Starte Circle Search"<< std::endl;
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
      seg_2.segment (*inliers_circle_plane, *coefficients_circle);

      if(inliers_circle_plane->indices.empty() == true){

        std::cout << "Kein Circle in Cloud gefunden"<< std::endl;

        //Aufruf der Funktion zum Berechnen des Zylinderanfangs wenn keine Stirnseite gefunden wurde (parallele Lage zur Kamera)
        Eigen::Vector3f aufpunkt_ebene_eigen = {0.0, 0.0, 0.0};
        
        std::vector<float> aufpunkt_ebene = calculateCylinderEnd(cloud_cylinder, koo_zylaxis_world, koo_zylaxispoint_world);

        aufpunkt_ebene_eigen[0] = aufpunkt_ebene[0];
        aufpunkt_ebene_eigen[1] = aufpunkt_ebene[1];
        aufpunkt_ebene_eigen[2] = aufpunkt_ebene[2];

        //Massenzentrum berechnen
        pcl::MomentOfInertiaEstimation <PointClNormal> feature_extractor;
        feature_extractor.setInputCloud (cloud_cylinder);
        feature_extractor.compute ();
        Eigen::Vector3f mass_center;
        feature_extractor.getMassCenter (mass_center);
        Eigen::Vector3f koo_masscenter_world (mass_center (0), mass_center (1), mass_center (2));

        std::vector<float> cylinder_position = calculateCylinder(koo_zylaxis_world, koo_zylaxispoint_world, aufpunkt_ebene_eigen, cyl_radius,koo_masscenter_world);

        RCLCPP_INFO(this->get_logger(),"Cylinder-Message wird erstellt");

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
      }

      else{
        std::cout << "Circle in Cloud gefunden"<< std::endl;
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
        
        Eigen::Vector3f koo_masscenter_world (mass_center (0), mass_center (1), mass_center (2));

        // RCLCPP_INFO(this->get_logger(),"X_Circle_mid: %f \n Y_Circle_mid: %f \n Z_Circle_mid: %f \n ", koo_kreismittelp_world[0], koo_kreismittelp_world[1] ,koo_kreismittelp_world[2]);
        // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_pt: %f \n Y_Cyl_axis_pt: %f \n Z_Cyl_axis_pt: %f \n ", koo_zylaxispoint_world[0], koo_zylaxispoint_world[1] ,koo_zylaxispoint_world[2]);
        // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_vec: %f \n Y_Cyl_axis_vec: %f \n Z_Cyl_axis_vec: %f \n ", koo_zylaxis_world[0], koo_zylaxis_world[1] ,koo_zylaxis_world[2]);
        // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_pt: %f \n Y_Cyl_axis_pt: %f \n Z_Cyl_axis_pt: %f \n ", cyl_axis_point_x, cyl_axis_point_y, cyl_axis_point_z);
        // RCLCPP_INFO(this->get_logger(),"X_Cyl_axis_vec: %f \n Y_Cyl_axis_vec: %f \n Z_Cyl_axis_vec: %f \n ", cyl_axis_x, cyl_axis_y, cyl_axis_z);

        //Point Cloud wird zur Visualisierung hinzugefügt

        std::string visu_name = "cylinder_cloud_" + std::to_string(number_cylinders); 

        // std::cout << "Transformation:" << std::endl;
        // std::cout << transform_3.matrix() << std::endl;

        // std::cout << "Masscenter:" << std::endl;
        // std::cout << koo_masscenter_world[0] << std::endl;
        // std::cout << koo_masscenter_world[1] << std::endl;
        // std::cout << koo_masscenter_world[2] << std::endl;

        pcl::PointXYZ y_axis (major_vector (0) + mass_center (0), major_vector (1) + mass_center (1), major_vector (2) + mass_center (2));

        // RCLCPP_INFO(this->get_logger(),"Number Cylinder: %i", number_cylinders);

        visu_ransac.addPointCloud (scene_before_downsampling, ColorHandlerNormal (scene_before_downsampling, 50.0, 50.0, 50.0), "scene");
        visu_ransac.addPointCloud (cloud_cylinder, ColorHandlerNormal (cloud_cylinder, 0.0, 255.0, 0.0), visu_name);
        visu_ransac.addPointCloud (cloud_cylinder_end, ColorHandlerNormal (cloud_cylinder_end, 0.0, 0.0, 255.0), visu_name+"_");
        visu_ransac.addCoordinateSystem(0.2);

        // RCLCPP_INFO(this->get_logger(),"Calculate Cylinder wird aufgerufen");

        std::vector<float> cylinder_position = calculateCylinder(koo_zylaxis_world,koo_zylaxispoint_world,koo_kreismittelp_world,cyl_radius, koo_masscenter_world);

        RCLCPP_INFO(this->get_logger(),"Cylinder-Message wird erstellt");

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
      }
    } //Ende Else falls Cylinder gefunden wird
  }
  // RCLCPP_INFO(this->get_logger(),"For_Schleife ist beendet");
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

  for (pcl::PointCloud<PointClNormal>::iterator pt = pcl_begin; pt<=pcl_end;){

    if (pcl::isFinite(*pt)==false){

      RCLCPP_INFO(this->get_logger(),"is NOT finite"); 

      pt = scene_before_filtering->erase(pt);

      RCLCPP_INFO(this->get_logger(),"Removed Point from Cloud"); 
    } 

    else {
      pt++;
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

    //Schnittpunkt zwischen Gerade durch Massenschwerpunkt und Cylinderstirnseite

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

    // std::cout << "Cylinder-Position:" << std::endl;
    // std::cout << cylinder_position[0] << std::endl;
    // std::cout << cylinder_position[1] << std::endl;
    // std::cout << cylinder_position[2] << std::endl;
    // std::cout << cylinder_position[3] << std::endl;
    // std::cout << cylinder_position[4] << std::endl;
    // std::cout << cylinder_position[5] << std::endl;

    // std::cout << "Schnittpunkt y-Koordinate:" << std::endl;
    // std::cout << schnittpunkt_massaxis_cyltop[1] << std::endl;


  return cylinder_position; //Return der Calinderposition [0] bis [2] ist der Mittelpunkt auf Stirnseite , [3] bis [5] ist die Orientierung relativ zu Mittenpunkt auf Stirnseite
}

std::vector<float> PointCloudProcessor::calculateCylinderEnd(std::shared_ptr<PointCloudN> cyl_cloud, Eigen::Vector3f zylaxis, Eigen::Vector3f zylaxispoint){

  std::vector<float> aufpunkt_ebene_cylend = {0.0, 0.0, 0.0};

  auto compmax = [&](PointClNormal a, PointClNormal b){ return a.x < b.x;};
  //maxelement_x ist ein Iterator-Element, dieser ist ein vector<PointClNormal, ...> 
  auto maxelement_x = std::max_element(cyl_cloud->begin(),cyl_cloud->end(),compmax);

  float zaehler = 0.0;
  float nenner = sqrt(zylaxis[0]*zylaxis[0] + zylaxis[1]*zylaxis[1] + zylaxis[2]*zylaxis[2]);
  float distance= 0.0;
  int counter = 0;
  bool seitenflaeche = true;
  float distance_threshold = 0.002;
  int numberPointsnearPlane = 10;
  float d = 0;

  //Anzahl der Punkte die  in oder nahe der Ebene liegen wird in Counter geschrieben
  while(seitenflaeche){

    for (auto& pt : *cyl_cloud){

      zaehler = zylaxis[0]*(pt.x - maxelement_x[0].x) + zylaxis[1]*(pt.y - maxelement_x[0].y) + zylaxis[0]*(pt.z - maxelement_x[0].z);
      distance = abs(zaehler)/nenner;

      if (distance <= distance_threshold){ counter++;}

    }

    //Wenn mehr als die geforderte Anzahl an Punkte zur Ebene gehören ist diese Ebene die Seitenfläche
    if(counter >= numberPointsnearPlane){std::cout << "Seitenfläche wurde gefunden" << std::endl; seitenflaeche = false;
      
      //Ebene aus Normalenform in Koordinatenform transformieren --> Koeffizient d berechnen
      d = -1*(zylaxis[0] * maxelement_x[0].x + zylaxis[1] * maxelement_x[0].y + zylaxis[2] * maxelement_x[0].y);
      std::cout << "d: " << d << std::endl;
      //pcl::visualization::PCLVisualizer visu_test("Ebene");
      // visu_test.addPointCloud (cyl_cloud, ColorHandlerNormal (cube_cloud, 0.0, 255.0, 0.0), "test");
      // visu_test.addCoordinateSystem(0.2);

      pcl::ModelCoefficients::Ptr plane_coefficients (new pcl::ModelCoefficients);

      Eigen::Vector4f plane_new = {zylaxis[0],zylaxis[1],zylaxis[2],d};

      plane_coefficients->values.push_back(zylaxis[0]);
      plane_coefficients->values.push_back(zylaxis[1]);
      plane_coefficients->values.push_back(zylaxis[2]);
      plane_coefficients->values.push_back(d);

      //Berechnung eines Aufpunktes der gefundenen Ebene 
      aufpunkt_ebene_cylend[0] = (-d)/(zylaxis[0]+ zylaxis[1] + zylaxis[2]);
      aufpunkt_ebene_cylend[1] = aufpunkt_ebene_cylend[0];
      aufpunkt_ebene_cylend[2] = aufpunkt_ebene_cylend[0];

      // std::cout << "Count: "<< counter << std::endl;
      // std::cout << "Plane Coefficients 0: "<< plane_coefficients->values[0] << std::endl;
      // visu_test.addPlane(*plane_coefficients);
      // visu_test.spin();

    }
    //Falls nicht wird die Ebene hin zum Massenpunkt um einen gewissen Abstand verschoben
    else{  maxelement_x[0].x -= distance_threshold/4; }
  }

  return aufpunkt_ebene_cylend;
}

void PointCloudProcessor::edgeDetection(std::shared_ptr<PointCloudN> cloud_copy){

  float angular_resolution = 0.001f;
  pcl::PointCloud<pcl::PointWithViewpoint> far_ranges;
  pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::LASER_FRAME;

  pcl::PointCloud<PointClNormal>& point_cloud = *cloud_copy;

  Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity ());

  float phi_x = 0.263; //X und Y Achse sind vertauscht gegenüber SDF 
  float phi_y = 0.0;
  float phi_z = -1.57;
  
  scene_sensor_pose.translation() << -0.3, 0.0, 1.2;

  // The same rotation matrix as before; theta radians around Z axis
  scene_sensor_pose.rotate (Eigen::AngleAxisf (phi_x, Eigen::Vector3f::UnitX()));
  scene_sensor_pose.rotate (Eigen::AngleAxisf (phi_y, Eigen::Vector3f::UnitY()));
  scene_sensor_pose.rotate (Eigen::AngleAxisf (phi_z, Eigen::Vector3f::UnitZ()));


  Eigen::Matrix3f transform_rotation = scene_sensor_pose.rotation();
  Eigen::Vector3f transform_translation = scene_sensor_pose.translation();

  //scene_sensor_pose = Eigen::Affine3f (Eigen::Translation3f (point_cloud.sensor_origin_[0],point_cloud.sensor_origin_[1],point_cloud.sensor_origin_[2])) *Eigen::Affine3f (point_cloud.sensor_orientation_);
  
  bool setUnseenToMaxRange = false;

  float noise_level = 0.0;
  float min_range = -2.0f;
  int border_size = 1;

  std::cout<< "Sensor-Pose:"<< std::endl;
  std::cout<< scene_sensor_pose.matrix()<< std::endl;
  // std::cout<< point_cloud.sensor_origin_[1]<< std::endl;
  // std::cout<< point_cloud.sensor_origin_[2]<< std::endl;
  std::cout<< "PointCloud Size: "<< std::endl;
  std::cout<< point_cloud.size()<< std::endl;

  pcl::RangeImage::Ptr range_image_ptr (new pcl::RangeImage);
  pcl::RangeImage& range_image = *range_image_ptr;   
  range_image.createFromPointCloud (point_cloud, angular_resolution, pcl::deg2rad (360.0f), pcl::deg2rad (180.0f),scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size);
  //range_image.integrateFarRanges (far_ranges);

  RCLCPP_INFO(this->get_logger(),"RangeImage_size: %i" , (int)range_image.size()); 
  
  RCLCPP_INFO(this->get_logger(),"Test_1"); 

  pcl::PointCloud<pcl::PointWithRange>::Ptr border_points_ptr(new pcl::PointCloud<pcl::PointWithRange>), 
                                            veil_points_ptr(new pcl::PointCloud<pcl::PointWithRange>),
                                            shadow_points_ptr(new pcl::PointCloud<pcl::PointWithRange>);

  pcl::RangeImageBorderExtractor border_extractor (&range_image);
  pcl::PointCloud<pcl::BorderDescription> border_descriptions;
  
  border_extractor.compute (border_descriptions);

    pcl::PointCloud<pcl::PointWithRange>& border_points = *border_points_ptr,
                                        & veil_points = *veil_points_ptr,
                                        & shadow_points = *shadow_points_ptr;

  RCLCPP_INFO(this->get_logger(),"RangeImage_width: %i \n RangeImage_height: %i" ,range_image.width,range_image.height); 

  for (int y=0; y< (int)range_image.height; ++y)
  {
    for (int x=0; x< (int)range_image.width; ++x)
    {
      if (border_descriptions[y*range_image.width + x].traits[pcl::BORDER_TRAIT__OBSTACLE_BORDER]) {
        
        border_points.push_back (range_image[y*range_image.width + x]);
        std::cout<<"Border Points found:"<< std::endl;
        std::cout<< border_points.size() << std::endl;
      }
      //else{std::cout<<"No Border Points found:"<< std::endl;}

      if (border_descriptions[y*range_image.width + x].traits[pcl::BORDER_TRAIT__VEIL_POINT])
        veil_points.push_back (range_image[y*range_image.width + x]);
      if (border_descriptions[y*range_image.width + x].traits[pcl::BORDER_TRAIT__SHADOW_BORDER])
        shadow_points.push_back (range_image[y*range_image.width + x]);
    }
  }

  RCLCPP_INFO(this->get_logger(),"Start der Visu"); 
  pcl::visualization::PCLVisualizer viewer ("3D Viewer");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> border_points_color_handler (border_points_ptr, 0, 255, 0);
  viewer.addPointCloud<pcl::PointWithRange> (border_points_ptr, border_points_color_handler, "border points");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "border points");
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> veil_points_color_handler (veil_points_ptr, 255, 0, 0);
  viewer.addPointCloud<pcl::PointWithRange> (veil_points_ptr, veil_points_color_handler, "veil points");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "veil points");
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> shadow_points_color_handler (shadow_points_ptr, 0, 255, 255);
  viewer.addPointCloud<pcl::PointWithRange> (shadow_points_ptr, shadow_points_color_handler, "shadow points");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "shadow points");

  viewer.addPointCloud (cloud_copy, ColorHandlerNormal (cloud_copy, 255.0, 255.0, 255.0), "scene");

  viewer.spin();

  // pcl::visualization::RangeImageVisualizer* range_image_borders_widget = NULL;
  // range_image_borders_widget = pcl::visualization::RangeImageVisualizer::getRangeImageBordersWidget (range_image, -std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity (), false, border_descriptions, "Range image with borders");

  // while (!viewer.wasStopped ())
  // {
  //   range_image_borders_widget->spinOnce ();
  //   viewer.spinOnce ();
  //   pcl_sleep(0.01);
  // }
}

std::vector<float> PointCloudProcessor::calculateCube(std::vector<Eigen::Vector4f> cube_planes, std::shared_ptr<PointCloudN> cube_cloud){

  //Prüfung wie viele Flächen hat der Würfel

  std::vector<float> cube_position {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //Ersten 3 Werte sind der Mittelpunkt danach Quarternion
  
  if (cube_planes.size() < 2){ std::cout << "Error: Würfel hat weniger als zwei Seiten" << std::endl;}
  if (cube_planes.size() > 3){ std::cout << "Error: Würfel hat mehr als 3 Seiten" << std::endl;}

  if (cube_planes.size() == 2){

    std::cout << "Würfel hat 2 Seiten" << std::endl;

    auto compmax = [&](PointClNormal a, PointClNormal b){ return a.x < b.x;};


    //maxelement_x ist ein Iterator-Element, dieser ist ein vector<PointClNormal, ...> 
    auto maxelement_x = std::max_element(cube_cloud->begin(),cube_cloud->end(),compmax);


    // std::cout << "Max Point in X" << std::endl;
    // std::cout << "X: " << maxelement_x[0].x << std::endl;
    // std::cout << "Y: " << maxelement_x[0].y << std::endl;
    // std::cout << "Z: " << maxelement_x[0].z << std::endl;

    //Berechnung des orthogonalen Vektors zu den zwei Ebenennormalen --> Vektorprodukt

    //Ebenen in Koeffizientenform werden in Vektor zum extrahieren des Normalenvektors geschrieben
    Eigen::Vector3f e1 = {cube_planes[0][0],cube_planes[0][1],cube_planes[0][2]};
    Eigen::Vector3f e2 = {cube_planes[1][0],cube_planes[1][1],cube_planes[1][2]};

    //  std::cout << "e1[0]: "<< e1[0] << std::endl;
    //  std::cout << "e1[1]: "<< e1[1] << std::endl;
    //  std::cout << "e1[2]: "<< e1[2] << std::endl;
    //  std::cout << "e2[0]: "<< e2[0] << std::endl;
    //  std::cout << "e2[1]: "<< e2[1] << std::endl;
    //  std::cout << "e2[2]: "<< e2[2] << std::endl;
    //Berechnung des Normalenvektors in Ausdehnungsrichtung des Würfels über das Vektorprodukt
    Eigen::Vector3f e3 = {0.0, 0.0, 0.0};

    e3[0] = e1[1]*e2[2] - e1[2]*e2[1];
    e3[1] = e1[2]*e2[0] - e1[0]*e2[2];
    e3[2] = e1[0]*e2[1] - e1[1]*e2[0];

    // std::cout << "e3[0]: "<< e3[0] << std::endl;
    // std::cout << "e3[1]: "<< e3[1] << std::endl;
    // std::cout << "e3[2]: "<< e3[2] << std::endl;

    //Berechnung des Abstandes Punkt zur Ebene 

    float zaehler = 0.0;
    float nenner = sqrt(e3[0]*e3[0]+e3[1]*e3[1]+e3[2]*e3[2]);
    float distance= 0.0;
    int counter = 0;
    bool seitenflaeche = true;
    float distance_threshold = 0.002;
    int numberPointsnearPlane = 10;
    float d = 0;

    //Anzahl der Punkte die  in oder nahe der Ebene liegen wird in Counter geschrieben
    while(seitenflaeche){

      for (auto& pt : *cube_cloud){

        zaehler = e3[0]*(pt.x - maxelement_x[0].x) + e3[1]*(pt.y - maxelement_x[0].y) + e3[0]*(pt.z - maxelement_x[0].z);
        distance = abs(zaehler)/nenner;

        if (distance <= distance_threshold){ counter++;}

      }

      //Wenn mehr als die geforderte Anzahl an Punkte zur Ebene gehören ist diese Ebene die Seitenfläche
      if(counter >= numberPointsnearPlane){std::cout << "Seitenfläche wurde gefunden" << std::endl; seitenflaeche = false;
        
        //Ebene aus Normalenform in Koordinatenform transformieren --> Koeffizient d berechnen
        d = -1*(e3[0] * maxelement_x[0].x + e3[1] * maxelement_x[0].y + e3[2] * maxelement_x[0].y);
        std::cout << "d: " << d << std::endl;
        pcl::visualization::PCLVisualizer visu_test("Ebene");
        visu_test.addPointCloud (cube_cloud, ColorHandlerNormal (cube_cloud, 0.0, 255.0, 0.0), "test");
        visu_test.addCoordinateSystem(0.2);

        pcl::ModelCoefficients::Ptr plane_coefficients (new pcl::ModelCoefficients);

        Eigen::Vector4f plane_new = {e3[0],e3[1],e3[2],d};

        plane_coefficients->values.push_back(e3[0]);
        plane_coefficients->values.push_back(e3[1]);
        plane_coefficients->values.push_back(e3[2]);
        plane_coefficients->values.push_back(d);
        // std::cout << "Count: "<< counter << std::endl;
        // std::cout << "Plane Coefficients 0: "<< plane_coefficients->values[0] << std::endl;
        visu_test.addPlane(*plane_coefficients);
        visu_test.spin();

        cube_planes.push_back(plane_new);
        cube_position = calculateCubeCenter(cube_planes,cube_cloud);
      }

      //Falls nicht wird die Ebene hin zum Massenpunkt um einen gewissen Abstand verschoben
      else{
        
        // std::cout << "Ebene wird versetzt" << std::endl;
        // std::cout << "Count: "<< counter << std::endl;

        maxelement_x[0].x -= distance_threshold/4;
      
      }
    }
  }

  if (cube_planes.size() == 3){

    std::cout << "Würfel hat 3 Seiten" << std::endl;
    cube_position = calculateCubeCenter(cube_planes,cube_cloud);
  }

return cube_position;
}

std::vector<float> PointCloudProcessor::calculateCubeCenter(std::vector<Eigen::Vector4f> cube_planes, std::shared_ptr<PointCloudN> cube_cloud){

  pcl::MomentOfInertiaEstimation <PointClNormal> feature_extractor;
  Eigen::Vector3d eckpunkt = {0.0,0.0,0.0};
  std::vector<float> cubeCenter = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //X,Y,Z des Mittelpunkes + X,Y,Z,W des Quarternions

  float kantenlaenge = 0.1;

  std::vector<Eigen::Vector4d> cube_planes_double;
  // std::cout << "Vor Konversion" << std::endl;
  //Konversion von Float in Double für PlaneIntersection
  for(int i = 0; i<=3;i++){

    Eigen::Vector4d cube_plane_double = {0.0, 0.0, 0.0, 0.0};

    for(int j = 0; j<=3;j++){

      cube_plane_double[j]=(static_cast<double>(cube_planes[i][j]));
    }
    cube_planes_double.push_back(cube_plane_double);
  }
  
  // std::cout << "Nach Konversion" << std::endl;
  bool intersects_plane_plane = pcl::threePlanesIntersection(cube_planes_double[0],cube_planes_double[1],cube_planes_double[2],eckpunkt,0.002);
  // std::cout<<"Cube Corner" << std::endl;
  // std::cout<<"X" << eckpunkt[0]<< std::endl;
  // std::cout<<"Y" << eckpunkt[1]<< std::endl;
  // std::cout<<"Z" << eckpunkt[2]<< std::endl;

  //Massenzentrum der Punktewolke bestimmen
  feature_extractor.setInputCloud (cube_cloud);
  feature_extractor.compute ();
  Eigen::Vector3f mass_center;
  feature_extractor.getMassCenter (mass_center);

  //In folgender For Schleife wird getestet ob Ebenennormalen in Richtung des Massenschwerpunktes zeigen und ggf. die Richtung geflipt
  for (int i = 0; i<=2; i++){ //Schleife für jeden Eigenvector in Vector cube_planes

    float zaehler = 0.0;
    float nenner = sqrt(cube_planes[i][0]*cube_planes[i][0]+cube_planes[i][1]*cube_planes[i][1]+cube_planes[i][2]*cube_planes[i][2]);
    float distance = 0.0;

    //Ausrichtung der Ebenennormalen von e1, e2 und e3 hin zum Zentrum und Skalierung von auf halbe Würfelkantenlänge
    for (int j = 0; j<=2; j++){ //Schleife für jedes Element des Eigenvektors

      zaehler += cube_planes[i][j]*(mass_center(j) - eckpunkt[j]);
    }

    distance = zaehler/nenner;

    if(distance < 0){ //Flip der Normalenrichtung falls distance negativ ist

      cube_planes[i][0] = cube_planes[i][0]*(-1);
      cube_planes[i][1] = cube_planes[i][1]*(-1);
      cube_planes[i][2] = cube_planes[i][2]*(-1);
    }

    //std::cout<<"Distance: " << distance<< std::endl;

    //Normierung des Eigenvektors auf die halbe Kantenlänge des Würfels
    float koeff = sqrt((kantenlaenge/2)*(kantenlaenge/2)/( cube_planes[i][0]*cube_planes[i][0] + cube_planes[i][1]*cube_planes[i][1] + cube_planes[i][2]*cube_planes[i][2] ));

    cube_planes[i][0] = cube_planes[i][0] * koeff;
    cube_planes[i][1] = cube_planes[i][1] * koeff;
    cube_planes[i][2] = cube_planes[i][2] * koeff;
  }

  //Berechnung des Würfelmittelpunkts über Eckpunkt und normierte Normalenvektoren
  for (int i = 0; i<=2; i++){
    
    cubeCenter[i]= (eckpunkt[i] + cube_planes[0][i] + cube_planes[1][i] + cube_planes[2][i]); //Erste iteration: X-Wert des Mittelpunktes = X-Eckpunkt + X- Normalenvektoren
  }

  //Rechtshandsystem über Vektorprodukt berechnen, notwendig zum umrechnen in Quarternions (bei Flip zu Massenmittelpunkt ist Rechtshandsystem nicht mehr gegeben)
  cube_planes[2][0] =  cube_planes[0][1]*cube_planes[1][2] - cube_planes[0][2]*cube_planes[1][1]; //cube_planes 0 ist immer X-Achse, cube_planes 1 immer Y-Achse --> cube_planes 2 ergibt Z Achse
  cube_planes[2][1] = cube_planes[0][2]*cube_planes[1][0] - cube_planes[0][0]*cube_planes[1][2];
  cube_planes[2][2] = cube_planes[0][0]*cube_planes[1][1] - cube_planes[0][1]*cube_planes[1][0];

  // std::cout<<"Cube-Center" << std::endl;
  // std::cout<<"X" << cubeCenter[0]<< std::endl;
  // std::cout<<"Y" << cubeCenter[1]<< std::endl;
  // std::cout<<"Z" << cubeCenter[2]<< std::endl;

  // std::cout<<"Pane_0 X: " << cube_planes[0][0]<< std::endl;
  // std::cout<<"Pane_1 X: " << cube_planes[1][0]<< std::endl;
  // std::cout<<"Pane_2 X: " << cube_planes[2][0]<< std::endl;

  Eigen::Vector3f x_axis = {cube_planes[0][0],cube_planes[0][1],cube_planes[0][2]};
  Eigen::Vector3f y_axis = {cube_planes[1][0],cube_planes[1][1],cube_planes[1][2]};
  Eigen::Vector3f z_axis = {cube_planes[2][0],cube_planes[2][1],cube_planes[2][2]}; 

  Eigen::Vector3f x_axis_norm = x_axis.normalized();

  // z orthogonal zu x machen (Gram-Schmidt) und normieren
  Eigen::Vector3f y_axis_norm = y_axis.normalized(); //(y_axis - y_axis.dot(x_axis_norm) * x_axis_norm).normalized();

  // Vektorprodukt berechnen
  Eigen::Vector3f z_axis_norm = z_axis.normalized();//x_axis_norm.cross(y_axis_norm);

  Eigen::Matrix3f rotation_matrix;
  rotation_matrix.col(0) = x_axis_norm;
  rotation_matrix.col(1) = y_axis_norm;
  rotation_matrix.col(2) = z_axis_norm;

  Eigen::Quaternionf q(rotation_matrix);
  q.normalize();

  cubeCenter[3]= q.x();
  cubeCenter[4]= q.y();
  cubeCenter[5]= q.z();
  cubeCenter[6]= q.w();

  std::cout<<"Cube-Orientation" << std::endl;
  std::cout<<"QX: " << cubeCenter[3]<< std::endl;
  std::cout<<"QY: " << cubeCenter[4]<< std::endl;
  std::cout<<"QZ: " << cubeCenter[5]<< std::endl;
  std::cout<<"QW: " << cubeCenter[6]<< std::endl;

  return cubeCenter;
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