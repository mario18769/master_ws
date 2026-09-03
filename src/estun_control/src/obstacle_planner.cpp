#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "boost/thread.hpp"

#include <moveit_msgs/msg/attached_collision_object.hpp>
#include <moveit_msgs/msg/collision_object.hpp>
#include <moveit_msgs/msg/display_robot_state.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>

#include "geometric_shapes/shapes.h"
#include "geometric_shapes/mesh_operations.h"
#include "geometric_shapes/shape_operations.h"


class ObstaclePlanner : public rclcpp::Node {

    public:

        ObstaclePlanner() : Node("obstacle_planner"){} //Initialiserung: nach : kommt Initialisierungsliste

        void run();
        void plan();
        void setup_world();

    private:

        rclcpp::Node::SharedPtr _node;
        moveit::planning_interface::MoveGroupInterface *_move_group;

};

void ObstaclePlanner::plan(){

    bool tf_found = false;
    geometry_msgs::msg::TransformStamped t;

    auto tf_buffer {std::make_unique<tf2_ros::Buffer>(this->get_clock())}; //geschweifte Klammer als moderne Variablendeklaration statt =
    auto tf_listener {std::make_shared<tf2_ros::TransformListener>(*tf_buffer)}; //this->get_clock und *tf_buffer sind jeweils Argumente für das Initialisieren des Objekts


    moveit::planning_interface::MoveGroupInterface move_group(_node, "arm"); //arm ist ein name einer group aus der SRDF 
    
    _move_group = new moveit::planning_interface::MoveGroupInterface(_node, "arm");
    
    std::string fromFrameRel = move_group.getPlanningFrame().c_str();
    std::string toFrameRel = move_group.getEndEffectorLink().c_str();

    setup_world();

    RCLCPP_INFO(this->get_logger(),"Setup-World is done");

    sleep(3);
    //Transformation 
    while ( !tf_found ) {    
        try {
            t = tf_buffer->lookupTransform(fromFrameRel, toFrameRel, tf2::TimePointZero); //TimePointZero --> aktuellste Transformation zurückgeben
            tf_found = true;
        } catch (const tf2::TransformException & ex) {
            RCLCPP_INFO(this->get_logger(), "Could not transform %s to %s: %s Try again",toFrameRel.c_str(), fromFrameRel.c_str(), ex.what());
            sleep(1);
        }
    }

    geometry_msgs::msg::Pose target_pose;
    std::vector<geometry_msgs::msg::Pose> waypoints;

    target_pose.orientation.w = t.transform.rotation.w; 
    target_pose.orientation.x = t.transform.rotation.x; 
    target_pose.orientation.y = t.transform.rotation.y;
    target_pose.orientation.z = t.transform.rotation.z; 
    target_pose.position.x = t.transform.translation.x; 
    target_pose.position.y = t.transform.translation.y;
    target_pose.position.z = t.transform.translation.z;
    target_pose.position.x += 0.5;
    _move_group->setPoseTarget(target_pose); 

    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    bool success_plan = (_move_group->plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);

    RCLCPP_INFO(this->get_logger(),"Plan status: %i", success_plan);

    // bool success_move = ( _move_group->move() == moveit::core::MoveItErrorCode::SUCCESS);
     
    // RCLCPP_INFO(this->get_logger(),"Move status: %i", success_move);

    auto execute_result = _move_group->execute(my_plan);

    RCLCPP_INFO(this->get_logger(),"Execute result: %d",execute_result.val);
}

void ObstaclePlanner::run() {
    auto node = rclcpp::Node::make_shared("CartesianPlan");
    _node = node;
    std::thread cartesian_plan_t( &ObstaclePlanner::plan, this);
    rclcpp::spin(node);

    RCLCPP_INFO(this->get_logger(),"Node Run completed");
}

void ObstaclePlanner::setup_world(){

    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;


    //Obstacle in der Umgebung des Roboters
    moveit_msgs::msg::CollisionObject obstacle;
    obstacle.header.frame_id = _move_group->getPlanningFrame();
    obstacle.id = "table";
    shape_msgs::msg::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[primitive.BOX_X] = 0.1;
    primitive.dimensions[primitive.BOX_Y] = 1.5;
    primitive.dimensions[primitive.BOX_Z] = 0.3;
    geometry_msgs::msg::Pose bp;
    bp.orientation.w = 0.5;
    bp.position.x = 0.48;
    bp.position.y = 0.0;
    bp.position.z = 0.25;

    obstacle.primitives.push_back(primitive);
    obstacle.primitive_poses.push_back(bp);
    obstacle.operation = obstacle.ADD;
    if (planning_scene_interface.applyCollisionObject(obstacle) == true){

        RCLCPP_INFO(this->get_logger(),"Table succesfully added to planningscene");
    }

    else{RCLCPP_INFO(this->get_logger(),"Table NOT added to planningscene");}


    //Obstacle am Endeffektor des Roboters
    moveit_msgs::msg::CollisionObject grasping_object;
    grasping_object.id = "grasp";
    shape_msgs::msg::SolidPrimitive grasping_object_primitive;
    grasping_object_primitive.type = primitive.CYLINDER;
    grasping_object_primitive.dimensions.resize(2);
    grasping_object_primitive.dimensions[primitive.CYLINDER_HEIGHT] = 0.2;
    grasping_object_primitive.dimensions[primitive.CYLINDER_RADIUS] = 0.06;
    grasping_object.header.frame_id = _move_group->getEndEffectorLink();
    geometry_msgs::msg::Pose grab_pose;
    grab_pose.orientation.w = 1.0;
    grab_pose.orientation.x = 0;
    grab_pose.orientation.y = 1.0;
    grab_pose.orientation.z = 0;
    grab_pose.position.z = 0.0;
    grab_pose.position.x = -0.2;
    grasping_object.primitives.push_back(grasping_object_primitive);
    grasping_object.primitive_poses.push_back(grab_pose);
    grasping_object.operation = grasping_object.ADD;
    planning_scene_interface.applyCollisionObject(grasping_object);
    std::vector<std::string> connection_links;
    
    connection_links.push_back ( "endeffector_1" );

    _move_group->attachObject(grasping_object.id, "endeffector_1", connection_links);

    //Objekt aus STL als Collisions-Objekt einlesen

    moveit_msgs::msg::CollisionObject test_object; //Collisions Objekt wird angelegt
    test_object.header.frame_id = _move_group->getPlanningFrame();
    test_object.id = "test";
    shapes::Mesh* m = shapes::createMeshFromResource("package://estun_control/meshes/test_part.stl");
    
    //float scalefactor = 0.01;
    //m->scale(scalefactor,scalefactor,scalefactor);
    
    shape_msgs::msg::Mesh test_mesh; //message vom typ mesh wird angelegt
    shapes::ShapeMsg test_mesh_msg; //Hilfs-Variant-Typ, NICHT selbst eine sendbare ROS-Message – dient nur zur generischen Rückgabe von constructMsgFromShape
    
    
    
    if(shapes::constructMsgFromShape(m,test_mesh_msg)== false){

        RCLCPP_INFO(this->get_logger(),"Could not generate Mesh vom STL");

    }
    
    else{
        RCLCPP_INFO(this->get_logger(),"Mesh gerneration succesful");
    }
    //Mesh wird aus STL erzeugt und in MSG geschrieben
    test_mesh = boost::get<shape_msgs::msg::Mesh>(test_mesh_msg); //zur Laufzeit wird geprüft/extrahiert, dass im variant ein Mesh steckt --> test_mesh bekommt den konkreten Typ
    //statischer Typ von test_mesh_msg bleibt immer ShapeMsg (variant) --> Zugriff auf konkreten Inhalt braucht immer boost::get<Typ>


    geometry_msgs::msg::Pose test_pose;
    test_pose.orientation.w = 0;
    test_pose.position.z = 0;
    test_pose.position.x = 0.8;
    test_pose.position.y = 0;


    test_object.meshes.push_back(test_mesh);
    test_object.mesh_poses.push_back(test_pose);
    
    
    test_object.operation = test_object.ADD;
    
    
    moveit_msgs::msg::ObjectColor object_color;
    object_color.id = test_object.id;
    object_color.color.r = 1.0f; // Red component
    object_color.color.g = 0.0f;
    object_color.color.b = 0.0f;
    object_color.color.a = 1.0f; // Alpha (Opacity)

    if(planning_scene_interface.applyCollisionObject(test_object) == false){

        RCLCPP_INFO(this->get_logger(),"Could add Mesh to planningscene");

    }
    
    else{
        RCLCPP_INFO(this->get_logger(),"Mesh succesfully added to planningscene");
    }

    std::vector<moveit_msgs::msg::CollisionObject> collision_objects;  
    std::vector<moveit_msgs::msg::ObjectColor> object_colors = {object_color};
    collision_objects.push_back(test_object);  

    // Now, let's add the collision object into the world 
    planning_scene_interface.addCollisionObjects(collision_objects, object_colors);
    
    

}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  ObstaclePlanner cp;
  cp.run();
}