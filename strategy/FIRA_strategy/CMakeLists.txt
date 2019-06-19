
##############################################################################
# Sections
##############################################################################


##############################################################################
# Sources
##############################################################################



##############################################################################
# Binaries
##############################################################################


add_executable(FIRA_strategy strategy_nodeHandle.cpp strategy.cpp FIRA_behavior.cpp FIRA_pathplan.cpp)
add_dependencies(FIRA_strategy ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(FIRA_strategy vision)
target_link_libraries(FIRA_strategy ${catkin_LIBRARIES} BaseNodeLib)
add_dependencies(FIRA_strategy fira_sim_generate_messages_cpp)
