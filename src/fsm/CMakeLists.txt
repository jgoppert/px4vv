add_library(fsm STATIC fsm.c)

add_definitions(-DCPROVER_IGNORE)
add_executable(test_fsm test_fsm.c)
target_link_libraries(test_fsm hal_posix fsm)
add_test(test_fsm test_fsm)
add_test(test_fsm ${CBMC} ${CBMC_ARGS}
	${CMAKE_CURRENT_SOURCE_DIR}/fsm.c
	${CMAKE_CURRENT_SOURCE_DIR}/test_fsm.c
	)
