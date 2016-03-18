cmake_minimum_required (VERSION 2.6)

link_libraries(apriltags)

find_package(catkin REQUIRED COMPONENTS
				sensor_msgs
				cv_bridge
				roscpp
				std_msgs
				image_transport
				geometry_msgs
				)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cv_bridge_example
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)
file(GLOB SOURCE_FILES "src/*.cc")
include_directories(AprilTags . /opt/local/include)


find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(apriltags_demo apriltags_dema.cpp Serial.cpp)
pods_install_executables(apriltags_demo)

add_executable(imu imu.cpp Serial.cpp)
pods_install_executables(imu)

				
target_link_libraries(apriltags_demo
   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${LIBV4L2_LIBRARY}

 )
