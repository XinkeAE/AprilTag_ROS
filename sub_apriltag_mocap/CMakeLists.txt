cmake_minimum_required(VERSION 2.8.3)
project(sub_apriltag_and_mocap)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs)



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES sub_ssf_and_mocap
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)



## Declare a cpp executable
 add_executable(sub_apriltag_mocap_node sub_apriltag_mocap.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(sub_ssf_and_mocap_node sub_ssf_and_mocap_generate_messages_cpp)

## Specify libraries to link a library or executable target against
 target_link_libraries(sub_apriltag_mocap_node
   ${catkin_LIBRARIES}
 )


