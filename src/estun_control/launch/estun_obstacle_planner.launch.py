from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder
import launch_ros.actions

def generate_launch_description():
    moveit_config = MoveItConfigsBuilder("Estun", package_name="estun_moveit").to_moveit_configs()

    launch_ros.actions.SetParameter(name='use_sim_time', value=True)


    tutorial_node = Node(
        package="estun_control",
        executable="mtc_estun",
        output="screen",
        parameters=[
            {"use_sim_time": True},
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.planning_pipelines,
            moveit_config.joint_limits,
        ],
    )



    return LaunchDescription([tutorial_node])