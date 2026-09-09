#include <rclcpp/rclcpp.hpp>
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
static const rclcpp::Logger LOGGER = rclcpp::get_logger("mtc_estun");
namespace mtc = moveit::task_constructor;

class MTCTaskNode
{
public:

  MTCTaskNode(const rclcpp::NodeOptions& options);

  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();

  void doTask();

  void setupPlanningScene();

private:
  // Compose an MTC task from a series of stages.
  mtc::Task createTask();
  mtc::Task task_;
  rclcpp::Node::SharedPtr node_;
};


rclcpp::node_interfaces::NodeBaseInterface::SharedPtr MTCTaskNode::getNodeBaseInterface() //Getter Funktion um Node-Base Interface in node_ zu bekommen
{
  return node_->get_node_base_interface();
}

MTCTaskNode::MTCTaskNode(const rclcpp::NodeOptions& options): node_{ std::make_shared<rclcpp::Node>("mtc_node", options) }{} //Initialisierung des Knotens --> : leitet Initialisierungsliste ein , MTCTaskNode = Konstruktor aus obiger Klasse
//nur im Konstruktor ist Zugriff auf Options möglich da dieses im Konstruktor der Klasse steht --> Zugriff unter Private Tag nicht möglich --> node_ mit Options im nachhinein initialisieren nicht möglich


void MTCTaskNode::setupPlanningScene()
{
  moveit_msgs::msg::CollisionObject object;
  object.id = "object";
  object.header.frame_id = "world"; //Definiton des Objekts relativ zu diesem Frame
  object.primitives.resize(1);
  object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
  object.primitives[0].dimensions = { 0.2, 0.05 };

  geometry_msgs::msg::Pose pose;
  pose.position.x = 0.5;
  pose.position.y = -0.25;
  object.pose = pose;

  moveit::planning_interface::PlanningSceneInterface psi;
  psi.applyCollisionObject(object);
}

void MTCTaskNode::doTask()
{


  try
  {
    task_ = createTask();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return;
  }

    try
  { RCLCPP_INFO_STREAM(LOGGER, "Task Create war erfolgreich, probiere nun task.init");
    task_.init();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Fehler bei Initialisierung");
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return;
  }

  if (!task_.plan(5))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());

  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task execution failed");
    return;
  }

  else{RCLCPP_ERROR_STREAM(LOGGER, "Task execution succeded");}

  return;
}


mtc::Task MTCTaskNode::createTask(){

    RCLCPP_ERROR_STREAM(LOGGER, "CREATE TASK STARTED");
    moveit::task_constructor::Task task;
    task.stages()->setName("demo task");
    task.loadRobotModel(node_);

    const auto& arm_group_name = "arm"; //Zuordung der Groups bestehend aus einer Kette von Links --> Definiert in srdf des Robotermodells
    const auto& hand_group_name = "hand"; //Name der Gruppe des Handeffektors
    const auto& hand_frame = "estun_hand"; //Link an Endeffectorgruppe als Bezug
    const auto& eef_name = "end_eff"; //Name des Endeffektors


    // Set task properties
    task.setProperty("group", arm_group_name);
    task.setProperty("eef", eef_name);
    task.setProperty("ik_frame", hand_frame);

    RCLCPP_INFO_STREAM(LOGGER, "zuweisung der Gruppen erfolgreich");

    //Generator Stage = CurrentState-----------------------------------------------------------------------------------------------------------------
    mtc::Stage* current_state_ptr = nullptr;  // Forward current_state on to grasp pose generator
    auto stage_state_current = std::make_unique<mtc::stages::CurrentState>("current"); //Speichert aktuelle Position des Roboters in einer CurrentStage
    current_state_ptr = stage_state_current.get(); //Erzeugt einen Raw-pointer auf Objekt--> dieser beinträchtigt Eigentumsverwaltung des Smart-Pointers nicht, ermöglicht aber lese und schreibzugriff
    task.add(std::move(stage_state_current)); //Objekt wird an task übergeben --> nun ist task Eigentümer des Objekts auf das der Smartpointer gezeigt hat

    auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
    auto interpolation_planner = std::make_shared<mtc::solvers::JointInterpolationPlanner>();

    auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>(); //Kartesian-Planner mit Spezifikationen wird Initialisiert
    cartesian_planner->setMaxVelocityScalingFactor(1.0);
    cartesian_planner->setMaxAccelerationScalingFactor(1.0);
    cartesian_planner->setStepSize(.01);

    RCLCPP_INFO_STREAM(LOGGER, "WAR ERFOLGREICH");

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

        RCLCPP_INFO_STREAM(LOGGER, "Erste Connector Stage");

        //Substage: Propagator-Stage = MoveRelative
        {
            auto stage =
            std::make_unique<mtc::stages::MoveRelative>("approach object", cartesian_planner);
            stage->properties().set("marker_ns", "approach_object");
            stage->properties().set("link", hand_frame);
            stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
            stage->setMinMaxDistance(0.1, 0.15);

            // Set hand forward direction
            geometry_msgs::msg::Vector3Stamped vec;
            vec.header.frame_id = hand_frame; //hand_frame als relativer Frame zu dem Bewegung ausgeführt wird
            vec.vector.z = 1.0;
            stage->setDirection(vec);
            grasp->insert(std::move(stage));

            RCLCPP_INFO_STREAM(LOGGER, "Erste Substage");
        }

        //Substage: Connector-Stage = GenerateGraspPose
        {
            // Sample grasp pose
            auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
            stage->properties().configureInitFrom(mtc::Stage::PARENT);
            stage->properties().set("marker_ns", "grasp_pose");
            stage->setPreGraspPose("open");
            stage->setObject("object");
            stage->setAngleDelta(M_PI / 12); //Winkeldifferenz für Lösungen der Greifposition
            stage->setMonitoredStage(current_state_ptr);  // Hook into current state --> Grasp-Object Pose und Shape werden an IK-Solver weitergereicht
            
            Eigen::Isometry3d grasp_frame_transform;
            Eigen::Quaterniond q = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitX()) *
            Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitY()) *
            Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d::UnitZ());
            grasp_frame_transform.linear() = q.matrix();
            grasp_frame_transform.translation().z() = 0.1;

            // Compute IK
            auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK", std::move(stage));
            wrapper->setMaxIKSolutions(8);
            wrapper->setMinSolutionDistance(1.0);
            wrapper->setIKFrame(grasp_frame_transform, "endeffector_1");
            wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
            wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
            grasp->insert(std::move(wrapper));

             RCLCPP_INFO_STREAM(LOGGER, "Zweite Substage");
        }

        { //Collision zwischen Greifer und Object erlauben durch Modifizierung der Planning-Scene
            auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
            stage->allowCollisions("object", task.getRobotModel()
                ->getJointModelGroup(hand_group_name)
                ->getLinkModelNamesWithCollisionGeometry(), true);
            grasp->insert(std::move(stage));

             RCLCPP_INFO_STREAM(LOGGER, "Dritte Substage");
        }

        // { //Propagator-Stage
        //     auto stage = std::make_unique<mtc::stages::MoveTo>("close hand", interpolation_planner);
        //     stage->setGroup(hand_group_name);
        //     stage->setGoal("close"); //position close aus SRDF
        //     grasp->insert(std::move(stage));
        // }

        { // Stage für Objekt zum Greifer des Roboters hinzufügen
            auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
            stage->attachObject("object", hand_frame);
            attach_object_stage = stage.get();
            grasp->insert(std::move(stage));

             RCLCPP_INFO_STREAM(LOGGER, "Vierte Substage");
        }

        { //Objekt relativ Bewegen
            auto stage = std::make_unique<mtc::stages::MoveRelative>("lift object", cartesian_planner);
            stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
            stage->setMinMaxDistance(0.1, 0.3);
            stage->setIKFrame(hand_frame);
            stage->properties().set("marker_ns", "lift_object");

            // Set upward direction
            geometry_msgs::msg::Vector3Stamped vec;
            vec.header.frame_id = "world"; //Bewegung relativ zum World Frame definieren
            vec.vector.z = 1.0;
            stage->setDirection(vec);
            grasp->insert(std::move(stage));
        }

      task.add(std::move(grasp));
      RCLCPP_INFO_STREAM(LOGGER, "GRASP-Task abgeschlossen");
    }//---------------------------------------------------------------------------------------------------------------------------


   

    // { //Connector-Stage zwischen Grasp-Task und Place-Task
    //     auto stage_move_to_place = std::make_unique<mtc::stages::Connect>("move to place",
    //         mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner },
    //             { hand_group_name, sampling_planner } });
    //     stage_move_to_place->setTimeout(5.0);
    //     stage_move_to_place->properties().configureInitFrom(mtc::Stage::PARENT);
    //     task.add(std::move(stage_move_to_place));

    //     RCLCPP_INFO_STREAM(LOGGER, "Connector-Stage zwischen Grasp und Place");
    // }

    //Serieller Container für Place-Task

    {
        auto place = std::make_unique<mtc::SerialContainer>("place object");
        task.properties().exposeTo(place->properties(), { "eef", "group", "ik_frame" });
        place->properties().configureInitFrom(mtc::Stage::PARENT,{ "eef", "group", "ik_frame" });

        { //Substages im Seriellen Conatiner
            //hier wird Pose im gegensatz zum Grasp-Task über setPose erzeugt
            
            // Sample place pose
            auto stage = std::make_unique<mtc::stages::GeneratePlacePose>("generate place pose");
            stage->properties().configureInitFrom(mtc::Stage::PARENT);
            stage->properties().set("marker_ns", "place_pose");
            stage->setObject("object");

            geometry_msgs::msg::PoseStamped target_pose_msg;
            target_pose_msg.header.frame_id = "object";
            target_pose_msg.pose.position.y = 0.5;
            target_pose_msg.pose.orientation.w = 1.0;
            stage->setPose(target_pose_msg);
            stage->setMonitoredStage(attach_object_stage);  //Raw-Pointer aus Grasp-Task wird MonitoredStage übergeben
            //damit ist die Lage des Objekts im Greifer positioniert ist

            // Compute IK
            auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place pose IK", std::move(stage));
            wrapper->setMaxIKSolutions(2);
            wrapper->setMinSolutionDistance(1.0);
            wrapper->setIKFrame("object");
            wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
            wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
            place->insert(std::move(wrapper));

            RCLCPP_INFO_STREAM(LOGGER, "Erste Place-Substage");
        }

        {
            auto stage = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
            stage->setGroup(hand_group_name);
            stage->setGoal("open");
            place->insert(std::move(stage));
        }

        { //Kollisionen werden nach Ablegen des Objekts wieder erlaubt
            auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("forbid collision (hand,object)");
            stage->allowCollisions("object", task.getRobotModel()
                ->getJointModelGroup(hand_group_name)
                ->getLinkModelNamesWithCollisionGeometry(), false);
            place->insert(std::move(stage));

            RCLCPP_INFO_STREAM(LOGGER, "Zweite Place-Substage");
        }

        { //Grasp-Objekt wird vom Greifer detached
            auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
            stage->detachObject("object", hand_frame);
            place->insert(std::move(stage));

            RCLCPP_INFO_STREAM(LOGGER, "Dritte Place-Substage");
        }

        { //Freifahren des Roboters
            auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
            stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
            stage->setMinMaxDistance(0.1, 0.3);
            stage->setIKFrame(hand_frame);
            stage->properties().set("marker_ns", "retreat");

            // Set retreat direction
            geometry_msgs::msg::Vector3Stamped vec;
            vec.header.frame_id = "world";
            vec.vector.x = -0.5;
            stage->setDirection(vec);
            place->insert(std::move(stage));

            RCLCPP_INFO_STREAM(LOGGER, "Vierte Place-Substage");
        }

      //task.add(std::move(place));

      RCLCPP_INFO_STREAM(LOGGER, "Place-Task abgeshlossen");
    }

    // { //Home Positon wird angefahren
    //     auto stage = std::make_unique<mtc::stages::MoveTo>("return home", interpolation_planner);
    //     stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    //     stage->setGoal("ready");
    //     task.add(std::move(stage));
    // }

    //Alle Stages werden in Task gespeichert
    RCLCPP_INFO_STREAM(LOGGER, "Create Task Successful");
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

    mtc_task_node->setupPlanningScene();
    mtc_task_node->doTask();

    spin_thread->join();
    rclcpp::shutdown();
    return 0;
}