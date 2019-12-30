add_executable(killer main.cpp)
target_link_libraries(killer ${catkin_LIBRARIES})
add_dependencies(killer ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

find_package(OpenCV)
include_directories($ {} OpenCV_INCLUDE_DIRS)
target_link_libraries(killer ${OpenCV_LIBRARIES})
