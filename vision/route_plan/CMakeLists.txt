add_executable(route_plan main.cpp route_plan.cpp nodehandle.cpp)
target_link_libraries(route_plan ${catkin_LIBRARIES})
add_dependencies(route_plan ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

find_package(OpenCV)
include_directories($ {} OpenCV_INCLUDE_DIRS)
target_link_libraries(route_plan ${OpenCV_LIBRARIES})
