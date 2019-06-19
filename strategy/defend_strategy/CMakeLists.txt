
##############################################################################
# Sections
##############################################################################


##############################################################################
# Sources
##############################################################################



##############################################################################
# Binaries
##############################################################################


add_executable(defend_strategy strategy_nodeHandle.cpp strategy.cpp FIRA_behavior.cpp FIRA_pathplan.cpp)
target_link_libraries(defend_strategy ${catkin_LIBRARIES} BaseNodeLib)
add_dependencies(defend_strategy fira_sim_generate_messages_cpp)
add_dependencies(defend_strategy ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(defend_strategy vision)
