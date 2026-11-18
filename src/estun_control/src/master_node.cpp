#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "rclcpp_action/rclcpp_action.hpp"
#include "../robot_interfaces/robot_interfaces/action/mtc_action.hpp"
#include <lifecycle_msgs/lifecycle_msgs/srv/get_state.hpp>
#include <lifecycle_msgs/lifecycle_msgs/srv/change_state.hpp>
#include <iostream>
#include "std_srvs/srv/empty.hpp"




class MasterNode {

    public:
        using MtcAction = robot_interfaces::action::MtcAction;
        using GoalHandleMtcAction = rclcpp_action::ClientGoalHandle<MtcAction>;

        MasterNode(const rclcpp::NodeOptions& options);
        rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();

    
        bool startPickandPlace();
        bool LcPCLRequest(int mtc_state);
        bool LcOpRequest(int op_state);
        void sendMtcGoal();
        void sendPclGoal();

        
    private:

        rclcpp::Node::SharedPtr node_;
        
        rclcpp::Client<lifecycle_msgs::srv::GetState>::SharedPtr client_lc_state_pcl;
        rclcpp::Client<lifecycle_msgs::srv::ChangeState>::SharedPtr client_lc_state_pcl_change;
        rclcpp::Client<lifecycle_msgs::srv::GetState>::SharedPtr client_lc_state_op;
        rclcpp::Client<lifecycle_msgs::srv::ChangeState>::SharedPtr client_lc_state_op_change;
        std::shared_ptr<rclcpp::Node> service_node;

        rclcpp_action::Client<MtcAction>::SharedPtr client_mtc;
        rclcpp_action::Client<MtcAction>::SharedPtr client_pcl;

};

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr MasterNode::getNodeBaseInterface() //Getter Funktion um Node-Base Interface in node_ zu bekommen --> zugriff von außerhalb der klasse auf den node_
{
  return node_->get_node_base_interface();
}

MasterNode::MasterNode(const rclcpp::NodeOptions& options): node_{ std::make_shared<rclcpp::Node>("master_node", options) }{

    client_mtc = rclcpp_action::create_client<MtcAction>(node_,"MtcAction");
    client_pcl = rclcpp_action::create_client<MtcAction>(node_,"PclAction");
    service_node = rclcpp::Node::make_shared("Service_Node_Get_Set_Lifecycle");

}

bool MasterNode::startPickandPlace(){

    //Starte ersten Node 

    bool PCLNode = false;
    bool OpNode = false;

    //sendMtcGoal();
    

    if(LcPCLRequest(1) == true){
        
        if(LcPCLRequest(3) == true){ PCLNode = true; std::cout << "Succes Transitioning into Active-State"<< std::endl; }
    };

    sendPclGoal();

    // if(LcOpRequest(1) == true){
    //     std::cout << "Succes Transitioning into Active-State"<< std::endl;
    //     if(LcOpRequest(3) == true){ MtcNode = true; }
    // };



    if(PCLNode == true && OpNode == true){return true;}
    
    return false;
}

void MasterNode::sendMtcGoal(){

    if (!client_mtc->wait_for_action_server(std::chrono::milliseconds(500))) {
      RCLCPP_ERROR(node_->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = MtcAction::Goal();
    goal_msg.action = "start";

    RCLCPP_INFO(node_->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<MtcAction>::SendGoalOptions();

    send_goal_options.goal_response_callback = [this](const GoalHandleMtcAction::SharedPtr & goal_handle){

      if (!goal_handle) {
        RCLCPP_ERROR(node_->get_logger(), "Goal was rejected by server");
      } 
      else {
        RCLCPP_INFO(node_->get_logger(), "Goal accepted by server, waiting for result");
      }
    };

    send_goal_options.feedback_callback = [this](GoalHandleMtcAction::SharedPtr,const std::shared_ptr<const MtcAction::Feedback> feedback){
      RCLCPP_INFO(node_->get_logger(), "Feedback: %i", feedback->object_count_feedback);
    };


    send_goal_options.result_callback = [this](const GoalHandleMtcAction::WrappedResult & result)
    {
      switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            RCLCPP_ERROR(node_->get_logger(), "Goal successful %i", result.result->object_count_result);
          break;
        case rclcpp_action::ResultCode::ABORTED:
          RCLCPP_ERROR(node_->get_logger(), "Goal was aborted");
          return;
        case rclcpp_action::ResultCode::CANCELED:
          RCLCPP_ERROR(node_->get_logger(), "Goal was canceled");
          return;
        default:
          RCLCPP_ERROR(node_->get_logger(), "Unknown result code");
          return;
      }
    };

    client_mtc->async_send_goal(goal_msg, send_goal_options);
}

void MasterNode::sendPclGoal(){

    if (!client_pcl->wait_for_action_server(std::chrono::milliseconds(500))) {
      RCLCPP_ERROR(node_->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = MtcAction::Goal();
    goal_msg.action = "start";

    RCLCPP_INFO(node_->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<MtcAction>::SendGoalOptions();

    send_goal_options.goal_response_callback = [this](const GoalHandleMtcAction::SharedPtr & goal_handle){

      if (!goal_handle) {
        RCLCPP_ERROR(node_->get_logger(), "Goal was rejected by server");
      } 
      else {
        RCLCPP_INFO(node_->get_logger(), "Goal accepted by server, waiting for result");
      }
    };

    send_goal_options.feedback_callback = [this](GoalHandleMtcAction::SharedPtr,const std::shared_ptr<const MtcAction::Feedback> feedback){
      RCLCPP_INFO(node_->get_logger(), "Feedback: %i", feedback->object_count_feedback);
    };


    send_goal_options.result_callback = [this](const GoalHandleMtcAction::WrappedResult & result)
    {
      switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            RCLCPP_ERROR(node_->get_logger(), "Goal successful %i", result.result->object_count_result);
          break;
        case rclcpp_action::ResultCode::ABORTED:
          RCLCPP_ERROR(node_->get_logger(), "Goal was aborted");
          return;
        case rclcpp_action::ResultCode::CANCELED:
          RCLCPP_ERROR(node_->get_logger(), "Goal was canceled");
          return;
        default:
          RCLCPP_ERROR(node_->get_logger(), "Unknown result code");
          return;
      }
    };

    client_pcl->async_send_goal(goal_msg, send_goal_options);
}

bool MasterNode::LcPCLRequest(int mtc_state){

    //LifecycelMsg Aufbau:
    // uint8 TRANSITION_CREATE = 0
    // uint8 TRANSITION_CONFIGURE = 1
    // uint8 TRANSITION_CLEANUP = 2
    // uint8 TRANSITION_ACTIVATE = 3
    // uint8 TRANSITION_DEACTIVATE = 4

    client_lc_state_pcl = service_node->create_client<lifecycle_msgs::srv::GetState>("/pointcloud_processor/get_state");
    client_lc_state_pcl_change = service_node->create_client<lifecycle_msgs::srv::ChangeState>("/pointcloud_processor/change_state");

    auto request = std::make_shared<lifecycle_msgs::srv::GetState::Request>();
    auto request_change = std::make_shared<lifecycle_msgs::srv::ChangeState::Request>();

    //request->structure_needs_at_least_one_member = 0;

    while(!client_lc_state_pcl->wait_for_service(std::chrono::milliseconds(500))){
 
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("LcMtcRequest"), "Interrupted while waiting for the service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "service not available, waiting again...");
    }

    auto future_result = client_lc_state_pcl->async_send_request(request);

    std::cout << "Waiting for OP response"<< std::endl;

    if (rclcpp::spin_until_future_complete(service_node, future_result) == rclcpp::FutureReturnCode::SUCCESS){

        RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "Success, state: %s", future_result.get()->current_state.label.c_str());
    } 
    else {
        RCLCPP_ERROR(rclcpp::get_logger("LcMtcRequest"), "Failed to call service");
    }

    int fail_count = 0;
    while(fail_count < 3){

        request_change->transition.id = mtc_state;

        while(!client_lc_state_pcl_change->wait_for_service(std::chrono::milliseconds(500))){

            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("LcMtcRequest"), "Interrupted while waiting for the service. Exiting.");
                return false ;
            }
            RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "service not available, waiting again...");
        }

        auto future_result_change = client_lc_state_pcl_change->async_send_request(request_change);

        if (rclcpp::spin_until_future_complete(service_node, future_result_change) == rclcpp::FutureReturnCode::SUCCESS){

            //RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "Transition: %i", future_result_change.get()->success);
            RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "Success");
            return true;
        } 
        else {
            RCLCPP_ERROR(rclcpp::get_logger("LcMtcRequest"), "Failed to call service");
            fail_count++;
        }
    }
    if(fail_count == 3){std::cout << "State Change wasnt possible after 3 attempts"<< std::endl; return false;}
   
    return false;
}

bool MasterNode::LcOpRequest(int op_state){

    //LifecycelMsg Aufbau:
    // uint8 TRANSITION_CREATE = 0
    // uint8 TRANSITION_CONFIGURE = 1
    // uint8 TRANSITION_CLEANUP = 2
    // uint8 TRANSITION_ACTIVATE = 3
    // uint8 TRANSITION_DEACTIVATE = 4

    client_lc_state_op = service_node->create_client<lifecycle_msgs::srv::GetState>("/obstacle_planner/get_state");
    client_lc_state_op_change = service_node->create_client<lifecycle_msgs::srv::ChangeState>("/obstacle_planner/change_state");

    auto request = std::make_shared<lifecycle_msgs::srv::GetState::Request>();
    auto request_change = std::make_shared<lifecycle_msgs::srv::ChangeState::Request>();

    //request->structure_needs_at_least_one_member = 0;

    while(!client_lc_state_op->wait_for_service(std::chrono::milliseconds(500))){
 
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("LcMtcRequest"), "Interrupted while waiting for the service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "service not available, waiting again...");
    }

    auto future_result = client_lc_state_op->async_send_request(request);

    std::cout << "Waiting for OP response"<< std::endl;

    if (rclcpp::spin_until_future_complete(service_node, future_result) == rclcpp::FutureReturnCode::SUCCESS){

        RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "Success, state: %s", future_result.get()->current_state.label.c_str());
    } 
    else {
        RCLCPP_ERROR(rclcpp::get_logger("LcMtcRequest"), "Failed to call service");
    }

    int fail_count = 0;
    while(fail_count < 3){

        request_change->transition.id = op_state;

        while(!client_lc_state_op_change->wait_for_service(std::chrono::milliseconds(500))){

            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("LcOpRequest"), "Interrupted while waiting for the service. Exiting.");
                return false ;
            }
            RCLCPP_INFO(rclcpp::get_logger("LcOpRequest"), "service not available, waiting again...");
        }

        auto future_result_change = client_lc_state_op_change->async_send_request(request_change);

        if (rclcpp::spin_until_future_complete(service_node, future_result_change) == rclcpp::FutureReturnCode::SUCCESS){

            //RCLCPP_INFO(rclcpp::get_logger("LcMtcRequest"), "Transition: %i", future_result_change.get()->success);
            RCLCPP_INFO(rclcpp::get_logger("LcOpRequest"), "Success");
            return true;
        } 
        else {
            RCLCPP_ERROR(rclcpp::get_logger("LcOpRequest"), "Failed to call service");
            fail_count++;
        }
    }
    if(fail_count == 3){std::cout << "State Change wasnt possible after 3 attempts"<< std::endl; return false;}
   
    return false;
}

int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);

    rclcpp::executors::MultiThreadedExecutor executor;

    rclcpp::NodeOptions options;
    options.automatically_declare_parameters_from_overrides(true);

    auto master_node = std::make_shared<MasterNode>(options);


    auto spin_thread = std::make_unique<std::thread>([&executor, &master_node]() {
        executor.add_node(master_node->getNodeBaseInterface());
        executor.spin();
        executor.remove_node(master_node->getNodeBaseInterface());
    });

    master_node->startPickandPlace();
    spin_thread->join();

    rclcpp::shutdown();
    return 0;

}