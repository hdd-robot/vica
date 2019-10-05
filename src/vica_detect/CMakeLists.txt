cmake_minimum_required(VERSION 2.8.3)
project(vica_detect)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries

find_package(catkin REQUIRED COMPONENTS
  OpenCV 
  roscpp
  std_msgs
  tensorflow_ros
  cv_bridge
  image_transport
  sensor_msgs  
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES vica_detect
#  CATKIN_DEPENDS roscpp std_msgs std_srv
#  DEPENDS system_lib
   CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs std_msgs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${tensorflow_ros_cpp_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/vica_detect.cpp
# )

## Add cmake target dependencies of the library
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable

## modifed hdd
add_executable(rgb_object_detect_node src/rgb_object_detect.cpp)


## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## modifed hdd
add_dependencies(rgb_object_detect_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})



## modified hdd 

## Specify libraries to link a library or executable target against
target_link_libraries(rgb_object_detect_node
   ${catkin_LIBRARIES}
   ${tensorflow_ros_cpp_LIBRARIES}
   opencv_imgproc 
   opencv_highgui
   opencv_core
 )
