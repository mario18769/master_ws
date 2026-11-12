#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <algorithm>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
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


static const rclcpp::Logger LOGGER = rclcpp::get_logger("mtc_estun");
namespace mtc = moveit::task_constructor;

class MTCTaskNode
{
public:

  MTCTaskNode(const rclcpp::NodeOptions& options);

  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();

  bool doTask();

  void setupPlanningScene();

  void getObjects();



private:
  
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr attach_pub_;
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr detach_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr test_pub_;
  // Compose an MTC task from a series of stages.
  mtc::Task createGrabTask();
  mtc::Task createTranslateTask_1();
  mtc::Task task_;
  rclcpp::Node::SharedPtr node_;
  std::string activeObject = "empty";
  mtc::Stage* current_state_ptr = nullptr;
  bool end_task = false;
};

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr MTCTaskNode::getNodeBaseInterface() //Getter Funktion um Node-Base Interface in node_ zu bekommen --> zugriff von außerhalb der klasse auf den node_
{
  return node_->get_node_base_interface();
}

MTCTaskNode::MTCTaskNode(const rclcpp::NodeOptions& options): node_{ std::make_shared<rclcpp::Node>("mtc_node", options) }{

  attach_pub_ = node_->create_publisher<std_msgs::msg::Empty>("/Probekoerper1/attach",10);
  detach_pub_ = node_->create_publisher<std_msgs::msg::Empty>("/Probekoerper1/detach",10);
  test_pub_ = node_->create_publisher<std_msgs::msg::String>("/Probekoerper1/test",10);
} //Initialisierung des Knotens --> : leitet Initialisierungsliste ein , MTCTaskNode = Konstruktor aus obiger Klasse
//nur im Konstruktor ist Zugriff auf Options möglich da dieses im Konstruktor der Klasse steht --> Zugriff unter Private Tag nicht möglich --> node_ mit Options im nachhinein initialisieren nicht möglich


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

void MTCTaskNode::getObjects(){

  std::cout << "TEST_1"<< std::endl;
  int i = 0;
  moveit::planning_interface::PlanningSceneInterface psi;
  std::map<std::string, moveit_msgs::msg::CollisionObject> object_list = psi.getObjects();
  std::cout << "Object-Count: "<< object_list.size() <<  std::endl;
  std::vector<std::string> object_ids;

  // object_ids.push_back("Cylinder_0");
  // object_ids.push_back("Test");

  struct data{
    std::string name;
    float distance;
  };

  std::vector<data> objects; 

  for(auto& iterator : object_list){
    object_ids.push_back(iterator.first);
  }

  std::map<std::string, geometry_msgs::msg::Pose> object_pose = psi.getObjectPoses(object_ids);
  std::cout << "Map-Size: "<< object_pose.size() <<  std::endl;

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

  std::cout << "Sortieren"<< std::endl;
  sort(objects.begin(), objects.end(),[](struct data a, struct data b){return a.distance < b.distance;} );

 std::cout << "Starte Task"<< std::endl;

 int j = 0;
 int count_while = 0;
 activeObject = objects[j].name;

 bool task = doTask();

  // while(objects.size() >= 1){
  //   #bool task = doTask();
    

  //   if (task == false && j < objects.size()){
  //     std::cout << "Objekt: " << j << " konnte nicht gegriffen werden, gehe zum nächsten Objekt über"<< std::endl;
  //     j++;
  //     if(j >= objects.size()){

  //       std::cout << "Liste abarbeiten nicht möglich"<< std::endl;
  //       std::cout << "Object-Size: "<< objects.size() << std::endl;
  //       break;
  //     }
  //     activeObject = objects[j].name;
  //   }

  //   if(task == true && j < objects.size()){

  //     std::cout << "Objekt: " <<j<< " erfolgreich gegriffen"<< std::endl;
  //     std::vector<std::string> removeObjects;
  //     removeObjects.push_back(activeObject);
  //     psi.removeCollisionObjects(removeObjects);
  //     objects.erase(objects.begin()+j);
  //     sort(objects.begin(), objects.end(),[](struct data a, struct data b){return a.distance < b.distance;} );
  //     j = 0;
  //     activeObject = objects[j].name;
  //   }

  //   count_while++;
  // }
  std::cout << "Ende Abarbeitung der Objekliste"<< std::endl;
  std::cout << "Anzahl übriger Elemente: "<< objects.size() <<std::endl;


  // end_task = true;
  // doTask();

  object_pose = psi.getObjectPoses(object_ids);
  std::cout << "Map-Size: "<< object_pose.size() <<  std::endl;

  std::cout << "Object Position X: " << object_pose["Cylinder_0"].position.x <<std::endl;
  std::cout << "Object Position Y: " << object_pose["Cylinder_0"].position.y <<std::endl;
  std::cout << "Object Position Z: " << object_pose["Cylinder_0"].position.z <<std::endl;

  std::cout << "Object Orientation X: " << object_pose["Cylinder_0"].orientation.x <<std::endl;
  std::cout << "Object Orientation Y: " << object_pose["Cylinder_0"].orientation.y <<std::endl;
  std::cout << "Object Orientation Z: " << object_pose["Cylinder_0"].orientation.z <<std::endl;
  std::cout << "Object Orientation W: " << object_pose["Cylinder_0"].orientation.w <<std::endl;

  
  for(auto& iterator : objects){

    std::cout << iterator.name << " - " << iterator.distance << std::endl;
  }
}

bool MTCTaskNode::doTask(){

  // std_msgs::msg::Empty detach;
  // detach_pub_->publish(detach);
  // std_msgs::msg::String test;
  // test.data = "Hello";
  // test_pub_->publish(test);
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
  //return true;
  }
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
}

mtc::Task MTCTaskNode::createTranslateTask_1(){

  // std_msgs::msg::Empty detach;
  // std_msgs::msg::Empty attach;

  // RCLCPP_INFO_STREAM(LOGGER, "sending Detach Message");

  // detach_pub_->publish(detach);

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
  auto interpolation_planner = std::make_shared<mtc::solvers::JointInterpolationPlanner>();
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>(); //Kartesian-Planner mit Spezifikationen wird Initialisiert
  cartesian_planner->setMaxVelocityScalingFactor(1.0);
  cartesian_planner->setMaxAccelerationScalingFactor(1.0);
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
    RCLCPP_INFO_STREAM(LOGGER, "Vierte Substage");
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
    //vec.vector.y = -1.0;
    //vec.vector.x = 1.0;
    vec.vector.z = 1.0;
    stage->setDirection(vec); //Gibt Bewegungsrichtung an
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  {
    //Connect Stage = Connect--------------------------------------------------------------------------------------------------------
    auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>("move to place",
    mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } }); //Vektor besteht aus Planning Group und dem Planner
    stage_move_to_pick->setTimeout(5.0);
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

      float roll_ = 1.5708;
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

    // {
    //   auto stage = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
    //   stage->setGroup(hand_group_name);
    //   stage->setGoal("open");
    //   place->insert(std::move(stage));
    // }

    // { //Kollisionen werden nach Ablegen des Objekts wieder erlaubt
    //   auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("forbid collision (hand,object)");
    //   stage->allowCollisions(activeObject, task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(), false);
    //   place->insert(std::move(stage));
    // }

    task.add(std::move(place));
  }
  

  return(task);
}

mtc::Task MTCTaskNode::createGrabTask(){
  
  
  // std_msgs::msg::Empty detach;
  // std_msgs::msg::Empty attach;

  // RCLCPP_INFO_STREAM(LOGGER, "sending Detach Message");

  // detach_pub_->publish(detach);

  RCLCPP_INFO_STREAM(LOGGER, "CREATE GrabTASK STARTED");
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

  //Generator Stage = CurrentState-----------------------------------------------------------------------------------------------------------------
    // Forward current_state on to grasp pose generator
  auto stage_state_current = std::make_unique<mtc::stages::CurrentState>("current"); //Speichert aktuelle Position des Roboters in einer CurrentStage
  current_state_ptr = stage_state_current.get(); //Erzeugt einen Raw-pointer auf Objekt--> dieser beinträchtigt Eigentumsverwaltung des Smart-Pointers nicht, ermöglicht aber lese und schreibzugriff
  task.add(std::move(stage_state_current)); //Objekt wird an task übergeben --> nun ist task Eigentümer des Objekts auf das der Smartpointer gezeigt hat

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  auto interpolation_planner = std::make_shared<mtc::solvers::JointInterpolationPlanner>();

  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>(); //Kartesian-Planner mit Spezifikationen wird Initialisiert
  cartesian_planner->setMaxVelocityScalingFactor(1.0);
  cartesian_planner->setMaxAccelerationScalingFactor(1.0);
  cartesian_planner->setStepSize(.01);

  // //Propagator Stage = MoveTo ------------------------------------------------------------------------------------------------------------------------------
  // auto stage_open_hand = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  // stage_open_hand->setGroup(hand_group_name);
  // stage_open_hand->setGoal("open"); //Position wird in SRDF des Roboters definiert
  // task.add(std::move(stage_open_hand));

  //Connect Stage = Connect--------------------------------------------------------------------------------------------------------
  auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>("move to pick",
  mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } }); //Vektor besteht aus Planning Group und dem Planner
  stage_move_to_pick->setTimeout(5.0);
  stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT);
  task.add(std::move(stage_move_to_pick));

  mtc::Stage* attach_object_stage = nullptr;  // Forward attach_object_stage to place pose generator

  //Serieller Container der mehrere Substages beinhaltet
  { //grasp ist Serieller Continer mit der Bezeichnung "pick object" ------------------------------------------------------------------------------------

    auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
    task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" }); //task-properties vom parent-task einlesen
    grasp->properties().configureInitFrom(mtc::Stage::PARENT,{ "eef", "group", "ik_frame" }); // task-properties werden initialisiert

    //Substage: Propagator-Stage = MoveRelative
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach object", cartesian_planner);
      stage->properties().set("marker_ns", "approach_object"); //Property MarkerNs ist teil von Stages
      stage->properties().set("link", hand_frame);
      stage->setMarkerNS("approach_object");
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.1, 0.3);

      // Set hand forward direction
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame; //hand_frame als relativer Frame zu dem Bewegung ausgeführt wird
      vec.vector.y = -1.0;
      //vec.vector.x = 1.0;
      // vec.vector.z = -1.0;
      stage->setDirection(vec); //Gibt Bewegungsrichtung an
      grasp->insert(std::move(stage));
    }

    //Substage: Connector-Stage = GenerateGraspPose
    {   
      Eigen::Vector3d axis = {0.0, 0.0, 1.0}; //Rotationsachse um das Objekt
      // Sample grasp pose
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "grasp_pose");
      stage->setEndEffector(eef_name);
      stage->setPreGraspPose("open");
      stage->setGraspPose("closed");
      //stage->setRotationAxis(axis);
      stage->setObject(activeObject);
      stage->setAngleDelta(M_PI /24); //Winkeldifferenz für Lösungen der Greifposition
      stage->setMonitoredStage(current_state_ptr);  // Hook into current state --> Grasp-Object Pose und Shape werden an IK-Solver weitergereicht

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
      wrapper->setMinSolutionDistance(0.1);
      wrapper->setIKFrame(grasp_frame_transform, hand_frame); //eigentlich hand_frame
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      grasp->insert(std::move(wrapper));
    }

    { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
      stage->allowCollisions(activeObject, task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(), true);
      grasp->insert(std::move(stage));
    }

    // { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
    //     auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    //     stage->allowCollisions("Palettenwagen", task.getRobotModel()
    //         ->getJointModelGroup(hand_group_name)
    //         ->getLinkModelNamesWithCollisionGeometry(), true);
    //     grasp->insert(std::move(stage));

    //      RCLCPP_INFO_STREAM(LOGGER, "Dritte Substage");
    // }

    { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
      std::vector<std::string> allow_collision_list;
      stage->allowCollisions(activeObject, "Palettenwagen",true);
      grasp->insert(std::move(stage));
    }

    // { //Propagator-Stage
    //   auto stage = std::make_unique<mtc::stages::MoveTo>("close hand", sampling_planner);
    //   stage->setGroup(hand_group_name);
    //   stage->setGoal("closed"); //position close aus SRDF
    //   grasp->insert(std::move(stage));
    // }

    // { // Stage für Objekt zum Greifer des Roboters hinzufügen
    //     auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
    //     stage->attachObject(activeObject, hand_frame); //eigentlich hand_frame
    //     attach_object_stage = stage.get();
    //     grasp->insert(std::move(stage));
    //     RCLCPP_INFO_STREAM(LOGGER, "Vierte Substage");
    // }

    // { //Objekt relativ Bewegen
    //     auto stage = std::make_unique<mtc::stages::MoveRelative>("lift object", cartesian_planner);
    //     stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group"});
    //     stage->setMinMaxDistance(0.2, 0.5);
    //     stage->setIKFrame(hand_frame); //eigentlich hand_frame
    //     stage->properties().set("marker_ns", "lift_object");

    //     // Set upward direction
    //     geometry_msgs::msg::Vector3Stamped vec;
    //     vec.header.frame_id = "world"; //Bewegung relativ zum World Frame definieren
    //     vec.vector.z = 1.0;
    //     stage->setDirection(vec);
    //     grasp->insert(std::move(stage));
    // }

    task.add(std::move(grasp));
    RCLCPP_INFO_STREAM(LOGGER, "GRASP-Task abgeschlossen");
  }
  
      //---------------------------------------------------------------------------------------------------------------------------

      // { //Connector-Stage zwischen Grasp-Task und Place-Task
      //     auto stage_move_to_place = std::make_unique<mtc::stages::Connect>("move to place", mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner }});
      //     stage_move_to_place->setTimeout(5.0);
      //     stage_move_to_place->properties().configureInitFrom(mtc::Stage::PARENT);
      //     task.add(std::move(stage_move_to_place));

      //     RCLCPP_INFO_STREAM(LOGGER, "Connector-Stage zwischen Grasp und Place");
      // }

      // //Serieller Container für Place-Task
      // {
      //     auto place = std::make_unique<mtc::SerialContainer>("place object");
      //     task.properties().exposeTo(place->properties(), { "eef", "group", "ik_frame" });
      //     place->properties().configureInitFrom(mtc::Stage::PARENT,{ "eef", "group", "ik_frame" });

      //     { //Substages im Seriellen Conatiner
      //       //hier wird Pose im gegensatz zum Grasp-Task über setPose erzeugt

      //       {
      //         auto stage = std::make_unique<mtc::stages::MoveRelative>("approach object pose", cartesian_planner);
      //         stage->properties().set("marker_ns", "approach_object"); //Property MarkerNs ist teil von Stages
      //         stage->properties().set("link", hand_frame);
      //         stage->setMarkerNS("approach_object_pose");
      //         stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      //         stage->setMinMaxDistance(0.2, 0.5);

      //         // Set hand forward direction
      //         geometry_msgs::msg::Vector3Stamped vec;
      //         vec.header.frame_id = "world"; //hand_frame als relativer Frame zu dem Bewegung ausgeführt wird
      //         //vec.vector.y = -1.0;
      //         //vec.vector.x = 1.0;
      //         vec.vector.z = -1.0;
      //         stage->setDirection(vec); //Gibt Bewegungsrichtung an
      //         place->insert(std::move(stage));
      //       }
            
      //       // // Sample place pose
      //       // auto stage = std::make_unique<mtc::stages::GeneratePlacePose>("generate place pose");
      //       // stage->properties().configureInitFrom(mtc::Stage::PARENT);
      //       // stage->properties().set("marker_ns", "place_pose");
      //       // stage->setObject(activeObject);

      //       // geometry_msgs::msg::PoseStamped pose_stamped;
      //       // geometry_msgs::msg::Pose pose;

      //       // float roll_ = 0.0;
      //       // float pitch_ = 0.0;
      //       // float yaw_ = 0.0;

      //       // tf2::Quaternion q1;
      //       // q1.setRPY(roll_, pitch_, yaw_);
      //       // pose.orientation.x = q1[0];
      //       // pose.orientation.y = q1[1];
      //       // pose.orientation.z = q1[2];
      //       // pose.orientation.w = q1[3];

      //       // pose.position.x = 1.0;
      //       // pose.position.y = 1.0;
      //       // pose.position.z = 0.5;

      //       // pose_stamped.header.frame_id = "world";
      //       // pose_stamped.pose = pose;
      //       // stage->setPose(pose_stamped);

      //       auto stage = std::make_unique<mtc::stages::GeneratePose>("generate pose placing");
      //         stage->properties().configureInitFrom(mtc::Stage::PARENT);
      //         stage->properties().set("marker_ns", "place_pose");
      //         stage->setMonitoredStage(current_state_ptr); 

      //           geometry_msgs::msg::PoseStamped pose_stamped;
      //             geometry_msgs::msg::Pose pose;

      //             float roll_ = 0.0;
      //             float pitch_ = 0.0;
      //             float yaw_ = 0.0;

      //             tf2::Quaternion q1;
      //             q1.setRPY(roll_, pitch_, yaw_);
      //             pose.orientation.x = q1[0];
      //             pose.orientation.y = q1[1];
      //             pose.orientation.z = q1[2];
      //             pose.orientation.w = q1[3];

      //             pose.position.x = 1.0;
      //             pose.position.y = 1.0;
      //             pose.position.z = 1.0;

      //             pose_stamped.header.frame_id = "world";
      //             pose_stamped.pose = pose;
      //             stage->setPose(pose_stamped);

      //       stage->setMonitoredStage(attach_object_stage);  //Raw-Pointer aus Grasp-Task wird MonitoredStage übergeben
      //       //damit ist die Lage des Objekts im Greifer positioniert ist

      //       Eigen::Isometry3d place_frame_transform;
      //       Eigen::Quaterniond q = Eigen::AngleAxisd(0, Eigen::Vector3d::UnitX()) *
      //       Eigen::AngleAxisd(0, Eigen::Vector3d::UnitY()) *
      //       Eigen::AngleAxisd(0, Eigen::Vector3d::UnitZ());
      //       place_frame_transform.linear() = q.matrix();
      //       place_frame_transform.translation().x() = 0.0;

      //       // Compute IK
      //       auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place pose IK", std::move(stage));
      //       wrapper->setMaxIKSolutions(10);
      //       wrapper->setMinSolutionDistance(0.1);
      //       wrapper->setIKFrame(place_frame_transform, hand_frame);
      //       wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      //       wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      //       place->insert(std::move(wrapper));
      //       RCLCPP_INFO_STREAM(LOGGER, "Erste Place-Substage");
      //     }

      //     {
      //         auto stage = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
      //         stage->setGroup(hand_group_name);
      //         stage->setGoal("open");
      //         place->insert(std::move(stage));
      //     }

      //     { //Kollisionen werden nach Ablegen des Objekts wieder erlaubt
      //         auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("forbid collision (hand,object)");
      //         stage->allowCollisions(activeObject, task.getRobotModel()
      //             ->getJointModelGroup(hand_group_name)
      //             ->getLinkModelNamesWithCollisionGeometry(), false);
      //         place->insert(std::move(stage));

      //         RCLCPP_INFO_STREAM(LOGGER, "Zweite Place-Substage");
      //     }

      //     { //Grasp-Objekt wird vom Greifer detached
      //         auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
      //         stage->detachObject(activeObject, hand_frame); 
      //         place->insert(std::move(stage));

      //         RCLCPP_INFO_STREAM(LOGGER, "Dritte Place-Substage");
      //     }

      //     { //Freifahren des Roboters
      //         auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
      //         stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      //         stage->setMinMaxDistance(0.1, 0.5);
      //         stage->setIKFrame(hand_frame);
      //         stage->properties().set("marker_ns", "retreat");

      //         // Set retreat direction
      //         geometry_msgs::msg::Vector3Stamped vec;
      //         vec.header.frame_id = hand_frame;
      //         vec.vector.y = 1.0;
      //         stage->setDirection(vec);
      //         place->insert(std::move(stage));

      //         RCLCPP_INFO_STREAM(LOGGER, "Vierte Place-Substage");
      //     }

      //   task.add(std::move(place)); 

      //   RCLCPP_INFO_STREAM(LOGGER, "Place-Task abgeshlossen");
        
      // }
    

    

      // {//Home Positon wird angefahren
      //   auto stage = std::make_unique<mtc::stages::MoveTo>("return home", sampling_planner);
      //   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      //   stage->setGoal("home");
      //   task.add(std::move(stage));
      // }
      
    

  //Alle Stages werden in Task gespeichert
  return task;
}

int main(int argc, char** argv){

    rclcpp::init(argc, argv);
  
    rclcpp::NodeOptions options;
    options.automatically_declare_parameters_from_overrides(true);

    auto mtc_task_node = std::make_shared<MTCTaskNode>(options);

    rclcpp::executors::MultiThreadedExecutor executor;

    auto spin_thread = std::make_unique<std::thread>([&executor, &mtc_task_node]() {
        executor.add_node(mtc_task_node->getNodeBaseInterface());
        executor.spin();
        executor.remove_node(mtc_task_node->getNodeBaseInterface());
    });

    //mtc_task_node->setupPlanningScene();
    //mtc_task_node->doTask();
    mtc_task_node->getObjects();
    spin_thread->join();
    rclcpp::shutdown();
    return 0;
}