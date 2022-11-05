cmake_minimum_required(VERSION 3.0.2)
project(dino)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  message_runtime
  std_msgs
  roscpp
)


## Generate services in the 'srv' folder
 add_service_files(
   FILES
   Generate_Name.srv
 )

## Generate added messages and services with any dependencies listed here
   generate_messages(
   DEPENDENCIES
   roscpp
  std_msgs  # Or other packages containing msgs
 )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dino
#  CATKIN_DEPENDS message_generation message_runtime
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})


