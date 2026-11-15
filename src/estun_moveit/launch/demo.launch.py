from moveit_configs_utils import MoveItConfigsBuilder
from launch.actions import ExecuteProcess, IncludeLaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration, Command
from launch.substitutions import PathJoinSubstitution
from launch.substitutions import PathSubstitution
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch import LaunchDescription
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
import launch_ros.actions
from controller_manager.launch_utils import generate_controllers_spawner_launch_description
import os
from launch_ros.parameter_descriptions import ParameterFile
from launch_ros.actions import LifecycleNode

from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    EmitEvent,
    ExecuteProcess,
    LogInfo,
    RegisterEventHandler,
    TimerAction
)
from launch.conditions import IfCondition
from launch.event_handlers import (
    OnExecutionComplete,
    OnProcessExit,
    OnProcessIO,
    OnProcessStart,
    OnShutdown
)
from launch.events import Shutdown
from launch.substitutions import (
    EnvironmentVariable,
    FindExecutable,
    LaunchConfiguration,
    LocalSubstitution,
    PythonExpression
)


def generate_launch_description():
   # moveit_config = MoveItConfigsBuilder("Estun", package_name="estun_moveit").to_moveit_configs()


    #use_sim_time = LaunchConfiguration('use_sim_time', default=True)
    ros_gz_sim_pkg_path = get_package_share_directory('ros_gz_sim')
    example_pkg_path = FindPackageShare('estun_moveit')
    gz_launch_path = PathJoinSubstitution([ros_gz_sim_pkg_path, 'launch', 'gz_sim.launch.py'])

    launch_ros.actions.SetParameter(name='use_sim_time', value=True)

    # Get URDF via xacro
    robot_description_content = Command(
        [PathJoinSubstitution([FindExecutable(name='xacro')]),
        ' ',
        PathJoinSubstitution([FindPackageShare('estun_moveit'),'urdf', 'estun.urdf.xacro']),]
    )

   
    robot_description = {'robot_description': robot_description_content}


    moveit_config = (
        MoveItConfigsBuilder("estun_er_hi", package_name="estun_moveit")
        .robot_description(file_path="urdf/estun.urdf.xacro")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .robot_description_semantic(file_path="urdf/estun.srdf")
        .planning_pipelines(pipelines=["ompl", "pilz_industrial_motion_planner"],default_planning_pipeline="ompl",)
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .to_moveit_configs()
    )

    run_move_group_node = Node(
        package='moveit_ros_move_group',
        executable='move_group',
        output='screen',
        parameters=[moveit_config.to_dict(),{"use_sim_time": True}, {"capabilities": "move_group/ExecuteTaskSolutionCapability"}],
    )

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description,{"use_sim_time": True}]
    )

    ros2_controller_file =PathJoinSubstitution([FindPackageShare("estun_moveit"),'config','ros2_controllers.yaml'])

    # controller_spawner = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=[
    #         "my_controller",
    #         # "hand_controller",
    #         # "joint_state_broadcaster",
    #         "--param-file",
    #         ros2_controller_file,
    #     ],
    # ),

    # controller_manager = Node(
    #     package="controller_manager",
    #     executable="ros2_control_node",
    #     name='controller_manager',
    #     output='screen',

    # ),

    # controller_spawner = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=[
    #          "arm_controller",
    #         # "--param-file",
    #         # "/home/mario/master_ws/src/estun_moveit/config/ros2_controllers.yaml",
    #     ]
    # ),

    # Get the path to the RViz configuration file
    rviz_config = PathJoinSubstitution([FindPackageShare('estun_description'), 'config', 'display.rviz'])

   
    # Launch RViz
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        output="log",
        arguments=["-d", rviz_config],
        parameters=[ {"use_sim_time": True},
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.planning_pipelines,
            moveit_config.joint_limits,],
    )

    gz_spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=['-topic', 'robot_description','-name', 'estun_er_hi', '-allow_renaming', 'true'],
    )

    gz_world = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(gz_launch_path),
        launch_arguments={'gz_args': ['-r -v 1 ',PathJoinSubstitution([example_pkg_path,'urdf','custom_world.sdf'])],}.items()
    )

    # Static TF

    static_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_transform_publisher",
        output="log",
        arguments=["--x", "-0.4", "--y", "-0.5", "--z", "2.500", "--roll", "0.0", "--pitch", "1.309", "--yaw", "-1.5708 ", "--frame-id", "world", "--child-frame-id", "Sensor/link_sensor/depth_camera1"],
    )

    load_joint_state_broadcaster = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active','joint_state_broadcaster'],
        output='screen'
    )

    ros_gz_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        parameters=[{'config_file': os.path.join(get_package_share_directory('estun_moveit'), 'config', 'ros_gz_bridge.yaml')},{"qos_overrides./tf_static.publisher.durability": "transient_local"},],
        output="screen",
    )

    load_arm_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active','arm_controller'],
        output='screen'
    )

    load_hand_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active','hand_controller'],
        output='screen'
    )

    obstacle_planner_node = Node(
        package="estun_control",
        executable="obstacle_planner",
        output="screen",
        parameters=[{"use_sim_time": True},
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
        ],
    )

    pose_estimation_node = Node(

        package="vision_control",
        executable="pcl_pose_estimation",
        output="screen",
    )

    mtc_node = Node(

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

    #für Mock-Hardware-System ohne Gazebo
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[ParameterFile(
            PathSubstitution(FindPackageShare("estun_moveit"))
            / "config"
            / "ros2_controllers.yaml",
        ),
    ],
        output="both",
        remappings=[("~/robot_description", "/robot_description"),],
    )

    return LaunchDescription([

        (gz_world),
        (robot_state_publisher_node),

        RegisterEventHandler(
            OnProcessIO(
                
                target_action=robot_state_publisher_node,
                on_stderr=lambda event: [LogInfo(msg='Robot initialized'.format(event.text.decode().strip())), ros_gz_bridge]
            )
        ), 

        RegisterEventHandler(
            OnProcessIO(
                
                target_action=robot_state_publisher_node,
                on_stderr=lambda event: [LogInfo(msg='Creating GZ->ROS Bridge: [/clock (gz.msgs.Clock) -> /clock (rosgraph_msgs/msg/Clock)] (Lazy 0)'.format(event.text.decode().strip())), gz_spawn_entity]
            )
        ),

        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=gz_spawn_entity,
                on_completion=[LogInfo(msg='Starte JSB \n'), load_joint_state_broadcaster]
            )
        ), 

        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=load_joint_state_broadcaster,
                on_completion=[LogInfo(msg='Starte Arm Controller \n'), load_arm_controller]
            )
        ),

        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=load_joint_state_broadcaster,
                on_completion=[LogInfo(msg='Starte Hand Controller \n'), load_hand_controller]
            )
        ),

        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=load_hand_controller,
                on_completion=[LogInfo(msg='Starte Move_group \n'), run_move_group_node]
            )
        ),

        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=load_hand_controller,
                on_completion=[LogInfo(msg='Starte Static TF \n'), static_tf]
            )
        ),           
        
        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=load_hand_controller,
                on_completion=[LogInfo(msg='Starte pcl_pose_estimation \n'), pose_estimation_node]
            )
        ),       

        RegisterEventHandler(
            OnProcessStart(
                
                target_action=pose_estimation_node,
                on_start=[obstacle_planner_node]
            )
        ),            
        

         RegisterEventHandler(
            OnProcessStart(
                
                target_action=obstacle_planner_node,
                on_start=[mtc_node]
            )
        ),

        RegisterEventHandler(
            OnProcessStart(
                
                target_action=mtc_node,
                on_start=[rviz_node]
            )
        ),         
    ])
