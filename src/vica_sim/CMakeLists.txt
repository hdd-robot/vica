cmake_minimum_required(VERSION 2.8.3)
project(vica_sim)
add_compile_options(-std=c++11)



## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  Qt5Core
)

find_package(Qt5Widgets CONFIG REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)




## Generate services in the 'srv' folder
add_service_files(
   FILES
   vica_sim_env_get_size.srv  
   vica_sim_env_init.srv                                             
   vica_sim_env_gui.srv       
   vica_sim_env_set_size.srv 
   vica_sim_env_stop.srv
   vica_sim_agent_add.srv
   vica_sim_agent_delete.srv
   vica_sim_agent_update.srv
   vica_sim_agent_get.srv
   vica_sim_agent_get_list.srv
   vica_sim_sim_get_target_pos.srv
   vica_sim_sim_set_target_pos.srv
   vica_sim_sim_get_robot_pos.srv
   vica_sim_sim_start_sim.srv
   vica_sim_sim_get_sim_result.srv
   vica_sim_sim_reset_sim.srv
)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )



###################################
## catkin specific configuration ##
###################################
catkin_package(
   INCLUDE_DIRS include
#  LIBRARIES vica_sim
   CATKIN_DEPENDS roscpp std_msgs message_runtime
#  DEPENDS system_lib 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  
  /home/ros/workspace_cpp/gAgent/src_agent
)

#HDD
LINK_DIRECTORIES(/home/ros/workspace_cpp/gAgent/src_agent/build)



add_executable(vica_sim src/vica_sim_node.cpp src/agent_model.cpp src/environment_model.cpp src/sma_img.cpp )


add_dependencies(vica_sim ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


set( LIBS_TO_LINK
    Qt5::Widgets
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    gagent
    config++
)

target_link_libraries(vica_sim
   ${catkin_LIBRARIES}
   ${LIBS_TO_LINK} 
 )




