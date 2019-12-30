
##############################################################################
# Sections
##############################################################################

file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.hpp)
#QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp)

##############################################################################
# Binaries
##############################################################################

add_executable(LC_method7 main.cpp NodeHandle.cpp Strategy.cpp)
target_link_libraries(LC_method7 ${catkin_LIBRARIES} BaseNodeLib)
add_dependencies(LC_method7 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(LC_method7 vision)
add_dependencies(LC_method7 imu_3d)
## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
