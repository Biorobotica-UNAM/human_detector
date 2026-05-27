from setuptools import setup, find_packages
from glob import glob
import os

package_name = 'human_detection'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(), 
    package_data={
    'human_detection': ['models/*.pt']
    },
    include_package_data=True,
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        
        ('share/' + package_name + '/models',
            glob(os.path.join('human_detection', 'models', '*.pt'))),
    ],
    install_requires=['setuptools', 'opencv-python', 'numpy', 'ultralytics', 'human_interfaces'],
    zip_safe=True,
    maintainer='rusanrod',
    maintainer_email='rsandovr@gmail.com',
    description='Human detection with YOLO pose estimation',
    license='MIT',
    entry_points={
        'console_scripts': [
            'detector = human_detection.human_detector_node:main',
            'webcam_image = human_detection.webcam_image:main',
            'person_tracker_pose = human_detection.person_tracker_pose:main',
            'person_tracker = human_detection.person_tracker:main',
            'pointing = human_detection.human_detector_node_pointing:main',
            'pointing_v2 = human_detection.human_detector_node_pointing_V2:main',
            'client = human_detection.pointing_client:main',
            'object_description = human_detection.object_description:main',
            'face_detect = human_detection.recog_face:main',
            'pose_detector = human_detection.pose_detector:main',
        ],
    },
)
