add_library(fsm_arming_state STATIC fsm_arming_state.c)

add_executable(test_fsm_arming_state test_fsm_arming_state.c)
target_link_libraries(test_fsm_arming_state hal_posix fsm_arming_state)
add_test(test_run_fsm_arming_state test_fsm_arming_state)
add_test(test_cbmc_fsm_arming_state ${CBMC} ${CBMC_ARGS}
	${CMAKE_CURRENT_SOURCE_DIR}/fsm_arming_state.c
	${CMAKE_CURRENT_SOURCE_DIR}/test_fsm_arming_state.c
	)
