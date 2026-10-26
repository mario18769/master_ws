from moveit_configs_utils import MoveItConfigsBuilder
from launch.actions import ExecuteProcess, IncludeLaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration, Command
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch import LaunchDescription
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
import launch_ros.actions
from controller_manager.launch_utils import generate_controllers_spawner_launch_description
import os
from launch_ros.parameter_descriptions import ParameterFile

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
        MoveItConfigsBuilder("Estun", package_name="estun_moveit")
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
        arguments=['-topic', 'robot_description','-name', 'cart', '-allow_renaming', 'true'],
    )

    gz_world = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(gz_launch_path),
        launch_arguments={'gz_args': ['-r -v 1 ',PathJoinSubstitution([example_pkg_path,'urdf','custom_world.sdf'])],}.items()
    )

    # Static TF
    static_tf_2 = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_transform_publisher",
        output="log",
        arguments=["--frame-id", "world", "--child-frame-id", "base_link"],
    )

    static_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_transform_publisher",
        output="log",
        arguments=["--x", "-0.3", "--y", "-0.05", "--z", "2.1", "--roll", "0.0", "--pitch", "0.785", "--yaw", "-1.5707 ", "--frame-id", "world", "--child-frame-id", "Sensor/link_sensor/depth_camera1"],
    )

   

    load_joint_state_broadcaster = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active','joint_state_broadcaster'],
        output='screen'
    )

    gz_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        
        parameters=[{"qos_overrides./tf_static.publisher.durability": "transient_local"}],
        output="screen",
    )
    
    # config_gz_ros_bridge = os.path.join(get_package_share_directory('estun_moveit'), 'config', 'ros_gz_bridge.yaml')
    # bridge_config = {'config_file': config_gz_ros_bridge}

    ros_gz_bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        parameters=[{'config_file': os.path.join(get_package_share_directory('estun_moveit'), 'config', 'ros_gz_bridge.yaml')},{"qos_overrides./tf_static.publisher.durability": "transient_local"},],
        output="screen",
    )

   # {'config_file': os.path.join(get_package_share_directory('<my_gz_sim_pkg>'), 'config', 'ros_gz_bridge.yaml')},

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

    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        #parameters=[robot_controllers],
        output="both",
        remappings=[
            ("~/robot_description", "/robot_description"),
        ],
    )

    return LaunchDescription([


        (static_tf),
        (gz_world),
              
        RegisterEventHandler(
            OnProcessStart(
                
                target_action=static_tf,
                on_start=[LogInfo(msg='Starte ros_gz_bridge \n'), ros_gz_bridge]
            )
        ), 

        RegisterEventHandler(
            OnProcessStart(
                
                target_action=ros_gz_bridge,
                on_start=[LogInfo(msg='Starte joint_state_broadcaster_controller \n'), load_joint_state_broadcaster]
            )
        ),

        RegisterEventHandler(
            OnProcessStart(
                
                target_action= ros_gz_bridge,
                on_start=[LogInfo(msg='starting robot_state_publisher \n'), robot_state_publisher_node]
            )
        ),   
                    
        
                  
        RegisterEventHandler(
            OnProcessStart(
                
                target_action=robot_state_publisher_node,
                on_start=[LogInfo(msg='Starte gz_spawn_entity \n'), gz_spawn_entity]
            )
        ),           

                        
        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=gz_spawn_entity,
                on_completion=[LogInfo(msg='Starte joint_state_broadcaster_controller \n'), load_arm_controller]
            )
        ),

        RegisterEventHandler(
            OnExecutionComplete(
                
                target_action=load_arm_controller,
                on_completion=[LogInfo(msg='Starte joint_state_broadcaster_controller \n'), load_hand_controller]
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
                on_start=[LogInfo(msg='starte move_group_node \n'), run_move_group_node]
            )
        ),

        RegisterEventHandler(
            OnProcessStart(
                
                target_action=run_move_group_node,
                on_start=[LogInfo(msg='starte rviz2 \n'), rviz_node]
            )
        ),

        RegisterEventHandler(
            OnProcessStart(
                
                target_action=rviz_node,
                on_start=[LogInfo(msg='starte robstacle_planner \n'), obstacle_planner_node]
            )
        ),            
        

        # RegisterEventHandler(
        #     OnProcessStart(
                
        #         target_action= obstacle_planner_node,
        #         on_start=[LogInfo(msg='starte mtc_node'), mtc_node]
        #     )
        # ),       
    ])
