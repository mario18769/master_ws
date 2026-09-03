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



def generate_launch_description():
   # moveit_config = MoveItConfigsBuilder("Estun", package_name="estun_moveit").to_moveit_configs()

    ld = LaunchDescription()
    #use_sim_time = LaunchConfiguration('use_sim_time', default=True)
    ros_gz_sim_pkg_path = get_package_share_directory('ros_gz_sim')
    example_pkg_path = FindPackageShare('estun_moveit')
    gz_launch_path = PathJoinSubstitution([ros_gz_sim_pkg_path, 'launch', 'gz_sim.launch.py'])

    # Get URDF via xacro
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]),
            ' ',
            PathJoinSubstitution(
                [FindPackageShare('estun_moveit'),
                 'config', 'Estun.urdf.xacro']
            ),
        ]
    )

    robot_description = {'robot_description': robot_description_content}

    moveit_config = (
    MoveItConfigsBuilder("Estun", package_name="estun_moveit")
    
    .robot_description(file_path="config/Estun.urdf.xacro")
    .robot_description_kinematics(file_path="config/kinematics.yaml")
    .robot_description_semantic(file_path="config/Estun.srdf")
    .planning_pipelines(
        pipelines=["ompl", "pilz_industrial_motion_planner"],
        default_planning_pipeline="ompl",
    )
    .trajectory_execution(file_path="config/moveit_controllers.yaml")
    .to_moveit_configs()
)

    run_move_group_node = Node(
    package='moveit_ros_move_group',
    executable='move_group',
    output='screen',
    parameters=[moveit_config.to_dict(),{"use_sim_time": True},],
)

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description,{"use_sim_time": True}]
    )

    # Get the path to the RViz configuration file

    rviz_config = PathJoinSubstitution(
        [FindPackageShare('Estun_description'), 'config', 'display.rviz'])

    # Launch RViz
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        output="log",
        arguments=["-d", rviz_config],
        parameters=[
            {"use_sim_time": True},
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.planning_pipelines,
            moveit_config.joint_limits,
    ],
)

    gz_spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=['-topic', 'robot_description',
                   '-name', 'cart', '-allow_renaming', 'true'],
    )

    gz_world = IncludeLaunchDescription(
    PythonLaunchDescriptionSource(gz_launch_path),
    launch_arguments={
        'gz_args': [
            '-r -v 1 ',
            PathJoinSubstitution([
                example_pkg_path,
                'config',
                'custom_world.sdf'
            ])
        ],
    }.items()
)

    # Static TF
    static_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_transform_publisher",
        output="log",
        arguments=["--frame-id", "world", "--child-frame-id", "base_link"],
    )

    load_joint_state_broadcaster = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
                'joint_state_broadcaster'],
        output='screen'
    )

    gz_bridge = Node(
     package="ros_gz_bridge",
     executable="parameter_bridge",
     arguments=['/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock'],
     parameters=[{
         "qos_overrides./tf_static.publisher.durability": "transient_local"
     }],
     output="screen",
 )

#     controller_path = PathJoinSubstitution([FindPackageShare("estun_moveit"), "config"])
#     control_node = Node(
#     package="controller_manager",
#     executable="ros2_control_node",
#     parameters=[controller_path / "ros2_controllers.yaml"],
#     output="both",
# )

    #ld.add_action(load_joint_state_broadcaster)
    ld.add_action(run_move_group_node)
    ld.add_action(static_tf)
    ld.add_action(robot_state_publisher_node)
    ld.add_action(rviz_node)
    
    ld.add_action(gz_bridge)
    ld.add_action(gz_world)
    ld.add_action(gz_spawn_entity)
    #ld.add_action(control_node)

    return ld
