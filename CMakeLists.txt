cmake_minimum_required(VERSION 2.5)

enable_testing()

find_program(VERIFY verify)
find_program(CBMC cbmc)

project(px5 C)

set(CMAKE_C_FLAGS "-g")

include_directories(include)

add_library(hal_posix STATIC src/arch/posix/hal.c) 

set(API_SRC
	${CMAKE_SOURCE_DIR}/src/api.c
	${CMAKE_SOURCE_DIR}/src/commander.c
	)

add_library(api STATIC ${API_SRC})

set(TEST1_SRC
	${CMAKE_SOURCE_DIR}/test/test1.c
	)

add_executable(test1 ${TEST1_SRC})
target_link_libraries(test1 hal_posix api)

#add_test(test1_spin ${VERIFY} -I${CMAKE_SOURCE_DIR}/include
	#${CMAKE_SOURCE_DIR}/test/test1.c)

add_test(test1_run test1)
add_test(test1_cbmc ${CBMC}
	-I${CMAKE_SOURCE_DIR}/include
	${API_SRC}
	${TEST1_SRC}
	)

add_test(commander_cbmc ${CBMC}
	-I${CMAKE_SOURCE_DIR}/include
	--function command
	${CMAKE_SOURCE_DIR}/src/commander.c
	)
