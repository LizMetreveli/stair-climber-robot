from setuptools import find_packages, setup

package_name = 'camera'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ml3',
    maintainer_email='ml3@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "camera_publisher = camera.camera_publisher:main",
            "qr_data = camera.qr_data:main",
            "qr_sub = camera.qr_sub:main",
            "traffic_light = camera.traffic_light:main",
            "traffic_sub = camera.traffic_sub:main"
        ],
    },
)
