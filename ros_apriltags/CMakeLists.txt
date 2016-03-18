cmake_minimum_required(VERSION 2.8.3)
project(ros_apriltags)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
				sensor_msgs
				cv_bridge
				roscpp
				std_msgs
				image_transport
				)


##cmake text from the apriltags library

set(POD_NAME ros_apriltags)
include(cmake/pods.cmake)
include(cmake/FindV4L2.cmake)

file(GLOB SOURCE_FILES "src/*.cc")
include_directories(AprilTags . /opt/local/include)
add_library(apriltags ${SOURCE_FILES})

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(apriltags ${OpenCV_LIBS}) #-pg) #-fopenmp)
pods_use_pkg_config_packages(apriltags eigen3)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(apriltags -L/opt/local/lib/) # MacPorts special treatment...
else (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  pods_use_pkg_config_packages(apriltags libv4l2)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

pods_use_pkg_config_packages(apriltags libv4l2)
pods_install_libraries(apriltags)

file(GLOB header_files "AprilTags/*.h")
pods_install_headers(${header_files} DESTINATION AprilTags/)

pods_install_pkg_config_file(apriltags
    LIBS -lapriltags
    REQUIRES eigen3 opencv2
    VERSION 1.0.0)

add_subdirectory(example)

## find v4l2
find_path(LIBV4L2_INCLUDE_DIR libv4l2.h)
if (NOT LIBV4L2_INCLUDE_DIR)
	message(STATUS "Could not find package V4L2. Try to install it")
	EXEC_PROGRAM("sudo apt-get install -y libv4l-dev")
	find_path(LIBV4L2_INCLUDE_DIR libv4l2.h)
endif (NOT LIBV4L2_INCLUDE_DIR)
include_directories(${LIBV4L2_INCLUDE_DIR}) 

find_library(LIBV4L2_LIBRARY v4l2)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
find_package(catkin REQUIRED COMPONENTS
				sensor_msgs
				cv_bridge
				roscpp
				std_msgs
				image_transport
				)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cv_bridge_example
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


include_directories( ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} Apriltags)

#add_executable(ros_apriltags_node example/apriltags_dema.cpp example/Serial.cpp)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(cv_bridge_example_node cv_bridge_example_generate_messages_cpp)

## Specify libraries to link a library or executable target against

#target_link_libraries(ros_apriltags_node
 #  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${LIBV4L2_LIBRARY}
#)


