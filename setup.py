from setuptools import setup
from glob import glob
import os

package_name = 'human_detection'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    package_data={
    'human_detection': ['models/*.pt']
    },
    include_package_data=True,
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),

        ('share/' + package_name + '/models',
            glob(os.path.join(package_name, 'models', '*.pt'))),
    ],
    install_requires=['setuptools', 'opencv-python', 'numpy', 'ultralytics'],
    zip_safe=True,
    maintainer='rusanrod',
    maintainer_email='rsandovr@gmail.com',
    description='Human detection with YOLO pose estimation',
    license='TODO: License declaration',
    entry_points={
        'console_scripts': [
            'detector = human_detection.human_detector_node:main',
            'webcam_image = human_detection.webcam_image:main',
            'person_tracker = human_detection.person_tracker:main',
        ],
    },
)
