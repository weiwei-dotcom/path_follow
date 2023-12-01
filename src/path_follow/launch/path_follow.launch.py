from launch import LaunchDescription
from launch_ros.actions import Node
import yaml

def load_param_from(path_param_file):
    with open(path_param_file, 'r') as f:
        params = yaml.safe_load(f)
    return params

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='path_follow',
            executable='path_follow',
            parameters=[load_param_from('/home/weiwei/Desktop/project/path_follow/src/path_follow/cdcr_config.yaml')]
        )])
    
# if __name__=='__main__':
#     params = load_param_from('/home/weiwei/Desktop/project/path_follow/src/path_follow/cdcr_config.yaml')
#     print(params)