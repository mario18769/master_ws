#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <algorithm>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <tf2_ros/transform_listener.h>
#if __has_include(<tf2_geometry_msgs/tf2_geometry_msgs.hpp>)
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#else
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#endif
#if __has_include(<tf2_eigen/tf2_eigen.hpp>)
#include <tf2_eigen/tf2_eigen.hpp>
#else
#include <tf2_eigen/tf2_eigen.h>
#endif
#include <tf2/LinearMath/Quaternion.h>
#include <std_msgs/msg/empty.hpp>
#include <std_msgs/msg/string.hpp>
#include <moveit_task_constructor_msgs/msg/solution.hpp>
#include "../robot_interfaces/robot_interfaces/msg/detach_msg.hpp"

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "../robot_interfaces/robot_interfaces/action/mtc_action.hpp"
#include "../robot_interfaces/robot_interfaces/msg/object_pose.hpp"


static const rclcpp::Logger LOGGER = rclcpp::get_logger("mtc_estun");
namespace mtc = moveit::task_constructor;

class MTCTaskNode
{
  public:

    using MtcAction = robot_interfaces::action::MtcAction;
    using GoalHandle = rclcpp_action::ServerGoalHandle<MtcAction>;

    MTCTaskNode(const rclcpp::NodeOptions& options);

    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();

    bool doTask();
    void setupPlanningScene();
    void getObjects(const std::shared_ptr<GoalHandle>);
    int testAttach();
    bool doHome();
    void execute(const std::shared_ptr<GoalHandle>);
    void ProbePose(geometry_msgs::msg::Pose, std::string);

  private:

  friend class MTCPubSub;

    std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    geometry_msgs::msg::TransformStamped tf_msg;
    std::string target_frame_;
    std::vector<robot_interfaces::msg::ObjectPose> msg_vector_new;

    rclcpp::Subscription<robot_interfaces::msg::ObjectPose>::SharedPtr object_pose_sub_;

    std::vector<rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr> attach_pub_;
    std::vector<rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr> detach_pub_;

    std::vector<std::string> attach_topics ={"/Probekoerper1/attach","/Probekoerper2/attach","/Probekoerper3/attach","/Probekoerper4/attach",
    "/Probekoerper5/attach","/Probekoerper6/attach","/Probekoerper7/attach","/Probekoerper8/attach"};

    std::vector<std::string> detach_topics = {"/Probekoerper1/detach","/Probekoerper2/detach","/Probekoerper3/detach","/Probekoerper4/detach",
    "/Probekoerper5/detach","/Probekoerper6/detach","/Probekoerper7/detach","/Probekoerper8/detach"};
    
    std::vector<std::string> pose_topics = {"/Probekoerper1/pose", "Probekoerper2/pose", "/Probekoerper3/pose", "/Probekoerper4/pose", 
    "/Probekoerper5/pose","/Probekoerper6/pose", "/Probekoerper7/pose","/Probekoerper8/pose"};

    std::vector<rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr> Probe_pose_;
    

  
  // Compose an MTC task from a series of stages.
  mtc::Task createGrabTask();
  mtc::Task createTranslateTask_1();
  mtc::Task createHomeTask();
  
  
  mtc::Task task_;
  rclcpp::Node::SharedPtr node_;
  std::string activeObject = "empty";
  std::string lastactiveObject = "empty";
  mtc::Stage* current_state_ptr = nullptr;
  std_msgs::msg::Empty empty_msg;
  rclcpp_action::Server<robot_interfaces::action::MtcAction>::SharedPtr server_mtc;

  struct pose_struct{

    std::string name = "empty";
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
  };

  std::vector<pose_struct> probe_pose_vec;

  bool end_task = false;
};

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr MTCTaskNode::getNodeBaseInterface() //Getter Funktion um Node-Base Interface in node_ zu bekommen --> zugriff von außerhalb der klasse auf den node_
{
  return node_->get_node_base_interface();
}

MTCTaskNode::MTCTaskNode(const rclcpp::NodeOptions& options): node_{ std::make_shared<rclcpp::Node>("mtc_node", options) }{

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(node_->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  target_frame_ = node_->declare_parameter<std::string>("world", "tcp");

  attach_pub_.resize(8);
  detach_pub_.resize(8);

  int i = 0;
  for (auto& iterator : attach_topics){

    attach_pub_[i] = node_->create_publisher<std_msgs::msg::Empty>(attach_topics[i],10);
    detach_pub_[i] = node_->create_publisher<std_msgs::msg::Empty>(detach_topics[i],10);
    i++;
  }

  Probe_pose_.resize(8);

  int j = 0;
  for (auto& iterator : pose_topics){

    Probe_pose_[j] = node_->create_subscription<geometry_msgs::msg::Pose>(iterator, 10, [this, iterator](geometry_msgs::msg::Pose msg) {
      this->ProbePose(msg, iterator);
    });

    j++;
  }

  auto handle_goal = [this](const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const MtcAction::Goal> goal){

    (void)uuid;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  };

  auto handle_cancel = [this](const std::shared_ptr<GoalHandle> goal_handle){

    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  };

  auto handle_accepted = [this](const std::shared_ptr<GoalHandle> goal_handle){
    // this needs to return quickly to avoid blocking the executor,
    // so we declare a lambda function to be called inside a new thread
    auto execute_in_thread = [this, goal_handle](){return this->getObjects(goal_handle);};
    std::thread{execute_in_thread}.detach();
  };

  server_mtc = rclcpp_action::create_server<MtcAction>(node_,"MtcAction",handle_goal,handle_cancel,handle_accepted);

}

void MTCTaskNode::execute(const std::shared_ptr<GoalHandle> goal_handle) {
    
  // rclcpp::Rate loop_rate(1);
  // const auto goal = goal_handle->get_goal();

  // auto feedback = std::make_shared<MtcAction::Feedback>();
  // auto & sequence = feedback->partial_sequence;
  // auto result = std::make_shared<MtcAction::Result>();

  // for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i) {
  //   // Check if there is a cancel request
  //   if (goal_handle->is_canceling()) {
  //     result->sequence = sequence;
  //     goal_handle->canceled(result);

  //     return;
  //   }

  //   // Publish feedback
  //   goal_handle->publish_feedback(feedback);

  //   loop_rate.sleep();
  // }

  // // Check if goal is done
  // if (rclcpp::ok()) {
  //   result->sequence = sequence;
  //   goal_handle->succeed(result);

  // }
}

void MTCTaskNode::setupPlanningScene(){

  { 
    moveit_msgs::msg::CollisionObject object;
    object.id = "Cylinder_0";
    object.header.frame_id = "world"; //Definiton des Objekts relativ zu diesem Frame
    object.primitives.resize(1);
    object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
    object.primitives[0].dimensions = { 0.2, 0.05 };

    geometry_msgs::msg::Pose pose;

    float roll_ = 1.57080;
    float pitch_ = 1.5708;
    float yaw_ = 0.0;

    tf2::Quaternion q1;
    q1.setRPY(roll_, pitch_, yaw_);
    pose.orientation.x = q1[0];
    pose.orientation.y = q1[1];
    pose.orientation.z = q1[2];
    pose.orientation.w = q1[3];
    pose.position.x = -0.5;
    pose.position.y = -0.8;
    pose.position.z = 0.8;
    object.pose = pose;

    moveit::planning_interface::PlanningSceneInterface psi;
    psi.applyCollisionObject(object);
  }
  { 
    moveit_msgs::msg::CollisionObject object;
    object.id = "Cylinder_1";
    object.header.frame_id = "world"; //Definiton des Objekts relativ zu diesem Frame
    object.primitives.resize(1);
    object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
    object.primitives[0].dimensions = { 0.2, 0.05 };

    geometry_msgs::msg::Pose pose;

    float roll_ = 0.0;
    float pitch_ = 0.0;
    float yaw_ = 0.0;

    tf2::Quaternion q1;
    q1.setRPY(roll_, pitch_, yaw_);
    pose.orientation.x = q1[0];
    pose.orientation.y = q1[1];
    pose.orientation.z = q1[2];
    pose.orientation.w = q1[3];
    pose.position.x = -0.8;
    pose.position.y = -0.9;
    pose.position.z = 0.8;
    object.pose = pose;

    moveit::planning_interface::PlanningSceneInterface psi;
    psi.applyCollisionObject(object);
  }
  { 
    moveit_msgs::msg::CollisionObject object;
    object.id = "Cylinder_2";
    object.header.frame_id = "world"; //Definiton des Objekts relativ zu diesem Frame
    object.primitives.resize(1);
    object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
    object.primitives[0].dimensions = { 0.2, 0.05 };

    geometry_msgs::msg::Pose pose;

    float roll_ = 0.0;
    float pitch_ = 0.0;
    float yaw_ = 0.0;

    tf2::Quaternion q1;
    q1.setRPY(roll_, pitch_, yaw_);
    pose.orientation.x = q1[0];
    pose.orientation.y = q1[1];
    pose.orientation.z = q1[2];
    pose.orientation.w = q1[3];
    pose.position.x = -0.901;
    pose.position.y = -0.9;
    pose.position.z = 0.8;
    object.pose = pose;

    moveit::planning_interface::PlanningSceneInterface psi;
    psi.applyCollisionObject(object);
  }

  { 
    moveit_msgs::msg::CollisionObject object;
    object.id = "Cylinder_3";
    object.header.frame_id = "world"; //Definiton des Objekts relativ zu diesem Frame
    object.primitives.resize(1);
    object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
    object.primitives[0].dimensions = { 0.2, 0.05 };

    geometry_msgs::msg::Pose pose;

    float roll_ = 0.0;
    float pitch_ = 0.0;
    float yaw_ = 0.0;

    tf2::Quaternion q1;
    q1.setRPY(roll_, pitch_, yaw_);
    pose.orientation.x = q1[0];
    pose.orientation.y = q1[1];
    pose.orientation.z = q1[2];
    pose.orientation.w = q1[3];
    pose.position.x = -0.901;
    pose.position.y = -1.001;
    pose.position.z = 0.8;
    object.pose = pose;

    moveit::planning_interface::PlanningSceneInterface psi;
    psi.applyCollisionObject(object);
  }
  { 
    moveit_msgs::msg::CollisionObject object;
    object.id = "Cylinder_4";
    object.header.frame_id = "world"; //Definiton des Objekts relativ zu diesem Frame
    object.primitives.resize(1);
    object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
    object.primitives[0].dimensions = { 0.2, 0.05 };

    geometry_msgs::msg::Pose pose;

    float roll_ = 0.0;
    float pitch_ = 0.0;
    float yaw_ = 0.0;

    tf2::Quaternion q1;
    q1.setRPY(roll_, pitch_, yaw_);
    pose.orientation.x = q1[0];
    pose.orientation.y = q1[1];
    pose.orientation.z = q1[2];
    pose.orientation.w = q1[3];
    pose.position.x = -0.8;
    pose.position.y = -1.001;
    pose.position.z = 0.8;
    object.pose = pose;

    moveit::planning_interface::PlanningSceneInterface psi;
    psi.applyCollisionObject(object);
  }
}

void MTCTaskNode::getObjects(const std::shared_ptr<GoalHandle> goal_handle){

  // std::cout << "Aufruf über Action erfolgreich"<< std::endl;

  // auto feedback = std::make_shared<MtcAction::Feedback>();

  // feedback->object_count_feedback = 1;

  // goal_handle->publish_feedback(feedback);

  // auto result = std::make_shared<MtcAction::Result>();

  // result->object_count_result = 2;

  // goal_handle->succeed(result);

  // return;

  int i = 0;
  moveit::planning_interface::PlanningSceneInterface psi;
  std::map<std::string, moveit_msgs::msg::CollisionObject> object_list = psi.getObjects();
  // std::cout << "Object-Count: "<< object_list.size() <<  std::endl;
  std::vector<std::string> object_ids;

  struct data{
    std::string name;
    float distance;
  };

  std::vector<data> objects; 

  for(auto& iterator : object_list){
    object_ids.push_back(iterator.first);
  }

  std::map<std::string, geometry_msgs::msg::Pose> object_pose = psi.getObjectPoses(object_ids);
  // std::cout << "Map-Size: "<< object_pose.size() <<  std::endl;

  for(auto& iterator : object_pose){

    geometry_msgs::msg::Pose cp = iterator.second;
    float pos_x = cp.position.x;
    float pos_y = cp.position.y;
    float distance = sqrt(pos_x*pos_x + pos_y * pos_y);

    if (iterator.first.starts_with("Cylinder") || iterator.first.starts_with("Cube") ) {

      struct data A =  {iterator.first , distance };
      objects.push_back(A);
      i++;
    }
    else{i++;}
  }

  //Feedback für Action Client MasterNode
  auto feedback = std::make_shared<MtcAction::Feedback>();

  feedback->object_count_feedback = objects.size();

  goal_handle->publish_feedback(feedback);

  // std::cout << "Sortieren"<< std::endl;
  sort(objects.begin(), objects.end(),[](struct data a, struct data b){return a.distance < b.distance;} );

  //  std::cout << "Starte Task"<< std::endl;

  int j = 0;

  activeObject = objects[j].name;

  bool task = doTask();

  while (task == false && j < objects.size()){
    // std::cout << "Objekt: " << j << " konnte nicht gegriffen werden, gehe zum nächsten Objekt über"<< std::endl;
    j++;
    if(j >= objects.size()){

      break;
    }
    lastactiveObject = activeObject;
    activeObject = objects[j].name;

    task = doTask();

    if(task == true && j < objects.size()){

      // std::cout << "Objekt: " <<j<< " erfolgreich gegriffen"<< std::endl;
      std::vector<std::string> removeObjects;
      removeObjects.push_back(activeObject);
      psi.removeCollisionObjects(removeObjects);
      objects.erase(objects.begin()+j);
      sort(objects.begin(), objects.end(),[](struct data a, struct data b){return a.distance < b.distance;} );
      j = 0;
      activeObject = objects[j].name;
    }
  }

  //Feedback für Action Client MasterNode
  auto result = std::make_shared<MtcAction::Result>();

  result->object_count_result = objects.size();
  result->success = task;

  goal_handle->succeed(result);

  //object_pose = psi.getObjectPoses(object_ids);
  // std::cout << "Map-Size: "<< object_pose.size() <<  std::endl;

  // std::cout << "Object Position X: " << object_pose["Cylinder_0"].position.x <<std::endl;
  // std::cout << "Object Position Y: " << object_pose["Cylinder_0"].position.y <<std::endl;
  // std::cout << "Object Position Z: " << object_pose["Cylinder_0"].position.z <<std::endl;
  // std::cout << "Object Orientation X: " << object_pose["Cylinder_0"].orientation.x <<std::endl;
  // std::cout << "Object Orientation Y: " << object_pose["Cylinder_0"].orientation.y <<std::endl;
  // std::cout << "Object Orientation Z: " << object_pose["Cylinder_0"].orientation.z <<std::endl;
  // std::cout << "Object Orientation W: " << object_pose["Cylinder_0"].orientation.w <<std::endl;

  // for(auto& iterator : objects){

  //   std::cout << iterator.name << " - " << iterator.distance << std::endl;
  // }
}

int MTCTaskNode::testAttach(){

  float tcp_x, tcp_y, tcp_z, threshold = 0.05;

  bool x_ = false, y_ = false, z_ = false;

  int i = 0;

  std::string name = "empty";

  tf_msg = tf_buffer_->lookupTransform("world", "tcp", tf2::TimePointZero);

  tcp_x = tf_msg.transform.translation.x;
  tcp_y = tf_msg.transform.translation.y;
  tcp_z = tf_msg.transform.translation.z;

  // std::cout<< "TCP_X: " << tcp_x << std::endl;
  // std::cout<< "TCP_Y: " << tcp_y << std::endl;
  // std::cout<< "TCP_Z: " << tcp_z << std::endl;

  // std::cout<< "Vector-Size: " << probe_pose_vec.size() << std::endl;
  // std::cout<< "Vector-First Element-Name: " << probe_pose_vec[0].name << std::endl;
  // std::cout<< "Vector-Element-X: " << probe_pose_vec[0].x << std::endl;

  for (auto& iterator : probe_pose_vec ){

    // std::cout<< "Iteration-Counter: " << i << std::endl;

    if (tcp_x <= (iterator.x + threshold) && tcp_x >= (iterator.x - threshold)){

      // std::cout<< "OK_X: " << std::endl;

      if (tcp_y <= (iterator.y + threshold) && tcp_y >= (iterator.y - threshold)){

        // std::cout<< "OK_Y: " << std::endl;

        if (tcp_z <= (iterator.z + threshold) && tcp_z >= (iterator.z - threshold)){

          // std::cout<< "OK_Z: " << std::endl;

          // std::string search = "/";

          //   std::size_t found = iterator.name.find(search);
          //   name = iterator.name.substr(1 + found);

          // std::cout<< "ITERATOR: " << i << std::endl;

          return i;
        }

        else { i++; continue;}
      }

      else{i++; continue;}
    }

    else{i++; continue;}

    i++;
  }

  i = 100;
  return i;
}

bool MTCTaskNode::doHome(){

    //Home Position Anfahren -----------------------------------------------------------------------------
    try
  {
    RCLCPP_INFO_STREAM(LOGGER, "try to create Home");
    task_ = createHomeTask();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return false;
  }
  try
  { RCLCPP_INFO_STREAM(LOGGER, "Task Create Home war erfolgreich, probiere nun task.init");
    task_.init();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Fehler bei Initialisierung");
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return false;
  }
  if (!task_.plan(5))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task planning failed");
    return false;
  }
  task_.introspection().publishSolution(*task_.solutions().front());

  auto result = task_.execute(*task_.solutions().front());  
    
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task execution failed");
    return false;
  }
  else{RCLCPP_INFO_STREAM(LOGGER, "Task execution HomeTask succeded");
    return true;
  }

  //------------------------------------------------------------------------------------------------------------------------------------------

}

bool MTCTaskNode::doTask(){


  detach_pub_[0]->publish(empty_msg);
  detach_pub_[1]->publish(empty_msg);
  detach_pub_[2]->publish(empty_msg);
  detach_pub_[3]->publish(empty_msg);
  detach_pub_[4]->publish(empty_msg);
  detach_pub_[5]->publish(empty_msg);
  detach_pub_[6]->publish(empty_msg);
  detach_pub_[7]->publish(empty_msg);
  
  //Anfahren des Objektes und schließen des Greifers-----------------------------------------------------------------------------
  try
  {
    RCLCPP_INFO_STREAM(LOGGER, "try to create GrabTask");
    task_ = createGrabTask();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return false;
  }
  try
  { RCLCPP_INFO_STREAM(LOGGER, "Task Create war erfolgreich, probiere nun task.init");
    task_.init();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Fehler bei Initialisierung");
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return false;
  }
  if (!task_.plan(5))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task planning failed");
    return false;
  }
  task_.introspection().publishSolution(*task_.solutions().front());

  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task execution failed");
    return false;
  }
  else{RCLCPP_INFO_STREAM(LOGGER, "Task execution GrabTask succeded");
  //return true;
  }
  //--------------------------------------------------------------------------------------------------------------------------------------

  //Call Gazbeo Attach Object

  int probekoerper_number = testAttach();

  if (probekoerper_number <= 7){

    attach_pub_[probekoerper_number]->publish(empty_msg);

    RCLCPP_INFO_STREAM(LOGGER, "Attached succesfully");
  }

  else { 
    RCLCPP_INFO_STREAM(LOGGER, "Could not be Attached"); 
    std::cout << "NUMBER: " <<  probekoerper_number << std::endl;
    
    return false;}

  //Anheben des Objektes und Absetzen auf Vermessungsstation -----------------------------------------------------------------------------
    try
  {
    RCLCPP_INFO_STREAM(LOGGER, "try to create TranslateTask_1");
    task_ = createTranslateTask_1();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return false;
  }
  try
  { RCLCPP_INFO_STREAM(LOGGER, "Task Create TranslateTask_1 war erfolgreich, probiere nun task.init");
    task_.init();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Fehler bei Initialisierung");
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return false;
  }
  if (!task_.plan(5))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task planning failed");
    return false;
  }
  task_.introspection().publishSolution(*task_.solutions().front());

    result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task execution failed");
    return false;
  }
  else{RCLCPP_INFO_STREAM(LOGGER, "Task execution GrabTask succeded");
    detach_pub_[probekoerper_number]->publish(empty_msg);
    return true;
  }

  detach_pub_[probekoerper_number]->publish(empty_msg);

  //------------------------------------------------------------------------------------------------------------------------------------------

  // //Execute kompletten Task
  // std::cout << "Solution Size" << task_.solutions().size() << std::endl;

  // moveit_task_constructor_msgs::msg::Solution msg;

  // (task_.solutions().front())->toMsg(msg);

  // auto id = msg.task_id;
  // auto sub_solutions_ = msg.sub_solution;
  // auto sub_trajectory_ = msg.sub_trajectory;

  // auto sub_sol_1 = sub_solutions_[0];
  // auto sub_traj_1 = sub_trajectory_[0];

  // moveit_task_constructor_msgs::msg::Solution sub_msg;

  // sub_msg.task_id = id;
  // sub_msg.sub_solution.push_back(sub_sol_1);
  // sub_msg.sub_trajectory.push_back(sub_traj_1);

  // moveit::task_constructor::SolutionBase BaseSolution;

  // BaseSolution.appendTo(sub_msg);

  // auto result = task_.execute(BaseSolution);

  return false;
}

mtc::Task MTCTaskNode::createTranslateTask_1(){


  RCLCPP_INFO_STREAM(LOGGER, "CREATE TASK TranslateTask_1 STARTED");
  moveit::task_constructor::Task task;
  task.stages()->setName("demo task");
  task.loadRobotModel(node_);

  const auto& arm_group_name = "arm"; //Zuordung der Groups bestehend aus einer Kette von Links --> Definiert in srdf des Robotermodells
  const auto& hand_group_name = "hand"; //Name der Gruppe des Handeffektors
  const auto& hand_frame = "tcp"; //Link an Endeffectorgruppe als Bezug
  const auto& eef_name = "end_eff"; //Name des Endeffektors

  // Set task properties
  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);

  {
    //Generator Stage = CurrentState-----------------------------------------------------------------------------------------------------------------
      // Forward current_state on to grasp pose generator
    auto stage_state_current = std::make_unique<mtc::stages::CurrentState>("current"); //Speichert aktuelle Position des Roboters in einer CurrentStage
    //current_state_ptr = stage_state_current.get(); //Erzeugt einen Raw-pointer auf Objekt--> dieser beinträchtigt Eigentumsverwaltung des Smart-Pointers nicht, ermöglicht aber lese und schreibzugriff
    task.add(std::move(stage_state_current)); //Objekt wird an task übergeben --> nun ist task Eigentümer des Objekts auf das der Smartpointer gezeigt hat
  }

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setPlannerId("ompl","RRTConnectkConfigDefault");
  sampling_planner->setMaxVelocityScalingFactor(0.5);
  sampling_planner->setMaxAccelerationScalingFactor(0.5);

  auto interpolation_planner = std::make_shared<mtc::solvers::JointInterpolationPlanner>();
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>(); //Kartesian-Planner mit Spezifikationen wird Initialisiert
  
  cartesian_planner->setMaxVelocityScalingFactor(0.5);
  cartesian_planner->setMaxAccelerationScalingFactor(0.5);
  cartesian_planner->setStepSize(.01);

  { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    stage->allowCollisions(activeObject, task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(), true);
    task.add(std::move(stage));
  }

  { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    std::vector<std::string> allow_collision_list;
    stage->allowCollisions(activeObject, "Palettenwagen",true);
    task.add(std::move(stage));
  }

  { // Stage für Objekt zum Greifer des Roboters hinzufügen
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
    stage->attachObject(activeObject, hand_frame); //eigentlich hand_frame
    //attach_object_stage = stage.get();
    //place->insert(std::move(stage));
    task.add(std::move(stage));
  }

  { //Propagator-Stage
    auto stage = std::make_unique<mtc::stages::MoveTo>("close hand", interpolation_planner);
    stage->setGroup(hand_group_name);
    stage->setGoal("closed"); //position close aus SRDF
    task.add(std::move(stage));
  }

  //Substage: Propagator-Stage = MoveRelative
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift object", cartesian_planner);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "approach_object"); //Property MarkerNs ist teil von Stages
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.1, 0.3);
    // Set hand forward direction
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world"; //hand_frame als relativer Frame zu dem Bewegung ausgeführt wird
    vec.vector.y = 0.0;
    vec.vector.x = 0.0;
    vec.vector.z = 1.0;
    stage->setDirection(vec); //Gibt Bewegungsrichtung an
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  {
    //Connect Stage = Connect--------------------------------------------------------------------------------------------------------
    auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>("move to place",
    mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } }); //Vektor besteht aus Planning Group und dem Planner
    stage_move_to_pick->setTimeout(10.0);
    //stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT);
    stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });
    task.add(std::move(stage_move_to_pick));
    //mtc::Stage* attach_object_stage = nullptr;  // Forward attach_object_stage to place pose generator
  }


  //Serieller Container der mehrere Substages beinhaltet
  { //grasp ist Serieller Continer mit der Bezeichnung "Translate_1 object" ------------------------------------------------------------------------------------

    auto place = std::make_unique<mtc::SerialContainer>("move object");
    task.properties().exposeTo(place->properties(), { "eef", "group", "ik_frame" }); //task-properties vom parent-task einlesen
    place->properties().configureInitFrom(mtc::Stage::PARENT,{ "eef", "group", "ik_frame" }); // task-properties werden initialisiert

    //Substage: Connector-Stage = GenerateGraspPose
    {   
      auto stage = std::make_unique<mtc::stages::GeneratePose>("generate pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "grasp_pose");
      stage->setMonitoredStage(current_state_ptr); 

      geometry_msgs::msg::PoseStamped pose_stamped;
      geometry_msgs::msg::Pose pose;

      float roll_ = 3.14;
      float pitch_ = 0.0;
      float yaw_ = 0.0;

      tf2::Quaternion q1;
      q1.setRPY(roll_, pitch_, yaw_);
      pose.orientation.x = q1[0];
      pose.orientation.y = q1[1];
      pose.orientation.z = q1[2];
      pose.orientation.w = q1[3];

      pose.position.x = 1.5;
      pose.position.y = 0.8;
      pose.position.z = 1.0;

      pose_stamped.header.frame_id = "world";
      pose_stamped.pose = pose;
      stage->setPose(pose_stamped);

      Eigen::Isometry3d grasp_frame_transform = Eigen::Isometry3d::Identity();
      Eigen::Quaterniond q = Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX()) *
      Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY()) *
      Eigen::AngleAxisd(0, Eigen::Vector3d::UnitZ());
      grasp_frame_transform.linear() = q.matrix();

      std::cout << q.matrix() << std::endl;
      grasp_frame_transform.translation().y() = -0.0;
      
      // Compute IK
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK", std::move(stage));
      wrapper->setMaxIKSolutions(10);
      wrapper->setMinSolutionDistance(0.3);
      wrapper->setIKFrame(grasp_frame_transform, hand_frame); //eigentlich hand_frame
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      place->insert(std::move(wrapper));
    }

    {
      auto stage = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
      stage->setGroup(hand_group_name);
      stage->setGoal("open");
      place->insert(std::move(stage));
    }

    { //Kollisionen werden nach Ablegen des Objekts wieder erlaubt
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("forbid collision (hand,object)");
      stage->allowCollisions(activeObject, task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(), false);
      place->insert(std::move(stage));
    }

    { //Grasp-Objekt wird vom Greifer detached
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
      stage->detachObject(activeObject, hand_frame); 
      place->insert(std::move(stage));
    }

    task.add(std::move(place));
  }
  

  return(task);
}

mtc::Task MTCTaskNode::createGrabTask(){

  float offset_x = 0.0;
  float offset_y = 0.0;
  float offset_z = 0.0;

  moveit::task_constructor::Task task;
  task.stages()->setName("demo task");
  task.loadRobotModel(node_);

  const auto& arm_group_name = "arm"; //Zuordung der Groups bestehend aus einer Kette von Links --> Definiert in srdf des Robotermodells
  const auto& hand_group_name = "hand"; //Name der Gruppe des Handeffektors
  const auto& hand_frame = "tcp"; //Link an Endeffectorgruppe als Bezug
  const auto& eef_name = "end_eff"; //Name des Endeffektors

  std::string approach_frame = hand_frame;

  // Set task properties
  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);

  //Generator Stage = CurrentState-----------------------------------------------------------------------------------------------------------------
  // Forward current_state on to grasp pose generator
  auto stage_state_current = std::make_unique<mtc::stages::CurrentState>("current"); //Speichert aktuelle Position des Roboters in einer CurrentStage
  current_state_ptr = stage_state_current.get(); //Erzeugt einen Raw-pointer auf Objekt--> dieser beinträchtigt Eigentumsverwaltung des Smart-Pointers nicht, ermöglicht aber lese und schreibzugriff
  task.add(std::move(stage_state_current)); //Objekt wird an task übergeben --> nun ist task Eigentümer des Objekts auf das der Smartpointer gezeigt hat

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setPlannerId("ompl","RRTConnectkConfigDefault");
  sampling_planner->setMaxVelocityScalingFactor(0.5);
  sampling_planner->setMaxAccelerationScalingFactor(0.5);

  auto interpolation_planner = std::make_shared<mtc::solvers::JointInterpolationPlanner>();

  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>(); //Kartesian-Planner mit Spezifikationen wird Initialisiert
  cartesian_planner->setMaxVelocityScalingFactor(0.5);
  cartesian_planner->setMaxAccelerationScalingFactor(0.5);
  cartesian_planner->setStepSize(.01);
 
  { 
    //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    stage->allowCollisions(lastactiveObject, task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(), false);
    task.add(std::move(stage));
  }
 
  {
    //Propagator Stage = MoveTo ------------------------------------------------------------------------------------------------------------------------------
    auto stage_open_hand = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
    stage_open_hand->setGroup(hand_group_name);
    stage_open_hand->setGoal("open"); //Position wird in SRDF des Roboters definiert
    task.add(std::move(stage_open_hand));
  }

  // {
  //   auto stage_open_hand = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  //   stage_open_hand->setGroup(hand_group_name);
  //   stage_open_hand->setGoal("closed"); //Position wird in SRDF des Roboters definiert
  //   task.add(std::move(stage_open_hand));
  // }
  // {
  //   auto stage_open_hand = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  //   stage_open_hand->setGroup(hand_group_name);
  //   stage_open_hand->setGoal("open"); //Position wird in SRDF des Roboters definiert
  //   task.add(std::move(stage_open_hand));
  // }

  //Connect Stage = Connect--------------------------------------------------------------------------------------------------------
  auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>("move to pick",
  mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } }); //Vektor besteht aus Planning Group und dem Planner
  stage_move_to_pick->setTimeout(10.0);
  stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT);
  task.add(std::move(stage_move_to_pick));

  mtc::Stage* attach_object_stage = nullptr;  // Forward attach_object_stage to place pose generator

  //Serieller Container der mehrere Substages beinhaltet
  { //grasp ist Serieller Continer mit der Bezeichnung "pick object" ------------------------------------------------------------------------------------

    auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
    task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" }); //task-properties vom parent-task einlesen
    grasp->properties().configureInitFrom(mtc::Stage::PARENT,{ "eef", "group", "ik_frame" }); // task-properties werden initialisiert

    if(activeObject.starts_with("Cylinder")){ offset_z = 0.03;}

    //Substage: Propagator-Stage = MoveRelative
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach object", cartesian_planner);
      stage->properties().set("marker_ns", "approach_object"); //Property MarkerNs ist teil von Stages
      stage->properties().set("link", hand_frame);
      stage->setMarkerNS("approach_object");
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.1, 0.3);

      //if(activeObject.starts_with("Cube")){ approach_frame = "world";}

      // Set hand forward direction
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = approach_frame; //hand_frame als relativer Frame zu dem Bewegung ausgeführt wird
      vec.vector.y = -1.0;
      //vec.vector.x = 1.0;
      // vec.vector.z = -1.0;
      stage->setDirection(vec); //Gibt Bewegungsrichtung an
      grasp->insert(std::move(stage));
    }

    //Substage: Connector-Stage = GenerateGraspPose
    { 
      float roll = 0.0, pitch= 0.0, yaw=0.0 , anglediff = M_PI/12;
      Eigen::Vector3d axis = {0.0, 0.0, 1.0}; //Rotationsachse um das Objekt
      // Sample grasp pose
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "grasp_pose");
      stage->setEndEffector(eef_name);
      stage->setPreGraspPose("open");
      stage->setGraspPose("closed");
      stage->setRotationAxis(axis);

      if(activeObject.starts_with("Cube")){
        roll = -M_PI/2;
        anglediff = M_PI/2;
      }

      stage->setObject(activeObject);
      stage->setAngleDelta(anglediff); //Winkeldifferenz für Lösungen der Greifposition
      stage->setMonitoredStage(current_state_ptr);  // Hook into current state --> Grasp-Object Pose und Shape werden an IK-Solver weitergereicht

      Eigen::Isometry3d grasp_frame_transform = Eigen::Isometry3d::Identity();
      Eigen::Quaterniond q = 
      Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()) *
      Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY()) *
      Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ());
      grasp_frame_transform.linear() = q.matrix();

      std::cout << q.matrix() << std::endl;
      grasp_frame_transform.translation().x() = offset_x;
      grasp_frame_transform.translation().y() = offset_y;
      grasp_frame_transform.translation().z() = offset_z;
      
      // Compute IK
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK", std::move(stage));
      wrapper->setMaxIKSolutions(10);
      wrapper->setMinSolutionDistance(0.1);
      wrapper->setIKFrame(grasp_frame_transform, hand_frame); //eigentlich hand_frame
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      grasp->insert(std::move(wrapper));
    }

    // { 
    //   //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
    //   auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    //   stage->allowCollisions(activeObject, task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(), true);
    //   grasp->insert(std::move(stage));
    // }

    // { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
    //   auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    //   std::vector<std::string> allow_collision_list;
    //   stage->allowCollisions(activeObject, "Palettenwagen",true);
    //   grasp->insert(std::move(stage));
    // }

    task.add(std::move(grasp));
  }
  
  //Alle Stages werden in Task gespeichert
  return task;
}

mtc::Task MTCTaskNode::createHomeTask(){

  moveit::task_constructor::Task task;
  task.stages()->setName("demo task");
  task.loadRobotModel(node_);

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setPlannerId("ompl","RRTConnectkConfigDefault");
  sampling_planner->setMaxVelocityScalingFactor(0.3);
  sampling_planner->setMaxAccelerationScalingFactor(0.3);

  {//Home Positon wird angefahren
    auto stage = std::make_unique<mtc::stages::MoveTo>("return home", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setGoal("home");
    task.add(std::move(stage));
  }
  return task;
  
}

void MTCTaskNode::ProbePose(geometry_msgs::msg::Pose msg, std::string topic){

  probe_pose_vec.resize(8); //Anzahl der Topics bzw. Anzahl der Körper die in Gazebo Pose unter einem Topic veröffentlichen

  int i = 0;

  if (msg.position.x == 0 && msg.position.y == 0){return;}

  else{

    if(topic == pose_topics[0]){ i = 0;}
    else if(topic == pose_topics[1]){ i = 1;}
    else if(topic == pose_topics[2]){ i = 2;}
    else if(topic == pose_topics[3]){ i = 3;}
    else if(topic == pose_topics[4]){ i = 4;}
    else if(topic == pose_topics[5]){ i = 5;}
    else if(topic == pose_topics[6]){ i = 6;}
    else if(topic == pose_topics[7]){ i = 7;}

    pose_struct PoseProbe;

    PoseProbe.name = topic;
    PoseProbe.x = msg.position.x;
    PoseProbe.y = msg.position.y;
    PoseProbe.z = msg.position.z;

    probe_pose_vec[i] = PoseProbe;
    //std::cout<< "Posen-Name: " << PoseProbe.name << " / X: " << PoseProbe.x << " / Y: " << PoseProbe.y << " / Z: " << PoseProbe.z << std::endl;
  }
}

int main(int argc, char** argv){

    rclcpp::init(argc, argv);

    rclcpp::executors::MultiThreadedExecutor executor;

    rclcpp::NodeOptions options;
    options.automatically_declare_parameters_from_overrides(true);

    auto mtc_task_node = std::make_shared<MTCTaskNode>(options);

    auto spin_thread = std::make_unique<std::thread>([&executor, &mtc_task_node]() {
      executor.add_node(mtc_task_node->getNodeBaseInterface());
      executor.spin();
      executor.remove_node(mtc_task_node->getNodeBaseInterface());
    });

    spin_thread->join();
    rclcpp::shutdown();
    return 0;
}

// class MTCPubSub : public rclcpp_lifecycle::LifecycleNode {

//   public: MTCPubSub(MTCTaskNode& MTCfriend) : LifecycleNode("MTCPubSub_Node"), MTCfriend_(MTCfriend) {}

//   rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state){


//     return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
//   }

//   rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state){

//      //MTCfriend_.getObjects();

//     return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
//   }

//   rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state){

    
//     return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
//   }

//   rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State & previous_state){

//     int i = 0;
//     for (auto& iterator : topics){

//       Probe_pose_[i].reset();
//       i++;
//     }

//     return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
//   }

//     rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State & previous_state){

//       int i = 0;
//       for (auto& iterator : topics){

//       Probe_pose_[i].reset();
//       i++;
//     }
      
//     return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
//   }

//   protected:

//   private:

//   MTCTaskNode& MTCfriend_;


  

  
//   void ProbePose(geometry_msgs::msg::Pose, std::string);
// };


