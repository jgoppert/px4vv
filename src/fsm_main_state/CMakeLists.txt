add_library(fsm_main_state STATIC
	fsm_main_state.c
	)

add_executable(test_fsm_main_state test_fsm_main_state.c)

target_link_libraries(test_fsm_main_state hal_posix fsm_main_state)

add_test(test_run_fsm_main test_fsm_main_state
	)

add_test(test_cbmc_fsm_main_state ${CBMC}
	-I${CMAKE_CURRENT_SOURCE_DIR}
	#--function fsm_main_state_update
	--bounds-check
	--arrays-uf-never 
	--div-by-zero-check
	--pointer-check
	--signed-overflow-check
	--unsigned-overflow-check
	--nan-check
	#--all-properties
	#--show-properties
	#--cover-assertions
	--beautify
	${CMAKE_CURRENT_SOURCE_DIR}/fsm_main_state.c
	${CMAKE_CURRENT_SOURCE_DIR}/test_fsm_main_state.c
	)

#add_test(fsm_main_state_spin ${VERIFY}
	#-I${CMAKE_CURRENT_SOURCE_DIR}
	#${CMAKE_CURRENT_SOURCE_DIR}/fsm_main_state.c
	#WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	#)




