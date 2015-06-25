add_library(fsm_arming_state STATIC fsm_arming_state.c)

add_executable(test_fsm_arming_state_auto_mission test_fsm_arming_state_auto_mission.c)
target_link_libraries(test_fsm_arming_state_auto_mission hal_posix fsm_arming_state)
add_test(test_run_fsm_arming_state_auto_mission test_fsm_arming_state_auto_mission)
add_test(test_cbmc_fsm_arming_state_auto_mission ${CBMC} ${CBMC_ARGS}
	${CMAKE_CURRENT_SOURCE_DIR}/fsm_arming_state.c
	${CMAKE_CURRENT_SOURCE_DIR}/test_fsm_arming_state_auto_mission.c
	)

add_executable(test_fsm_arming_state_intentional_failure test_fsm_arming_state_intentional_failure.c)
target_link_libraries(test_fsm_arming_state_intentional_failure hal_posix fsm_arming_state)
add_test(test_run_fsm_arming_state_intentional_failure test_fsm_arming_state_intentional_failure)
add_test(test_cbmc_fsm_arming_state_intentional_failure ${CBMC} ${CBMC_ARGS}
	${CMAKE_CURRENT_SOURCE_DIR}/fsm_arming_state.c
	${CMAKE_CURRENT_SOURCE_DIR}/test_fsm_arming_state_intentional_failure.c
	)

# spin doesn't work with enums
#add_test(fsm_arming_state_spin ${VERIFY}
	#-I${CMAKE_CURRENT_SOURCE_DIR}
	#${CMAKE_CURRENT_SOURCE_DIR}/fsm_arming_state.c
	#WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	#)
