cmake_minimum_required(VERSION 2.5)

project(px4vv C)

enable_testing()

find_program(VERIFY verify)
find_program(CBMC cbmc)
find_program(ASTYLE astyle)
find_program(SCANBUILD scan-build)

add_custom_command(OUTPUT cbmc-5-1-linux-64.tgz
	COMMAND wget http://www.cprover.org/cbmc/download/cbmc-5-1-linux-64.tgz)

add_custom_command(OUTPUT cbmc
	COMMAND tar xfz cbmc-5-1-linux-64.tgz
	DEPENDS cbmc-5-1-linux-64.tgz)

add_custom_target(cbmc_install
	sudo cp cbmc /usr/local/bin
	DEPENDS cbmc)

set(CBMC_ARGS
	-I${CMAKE_SOURCE_DIR}/include
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
	)

file(GLOB_RECURSE FORMAT_FILES src/*.c src/*.h)
add_custom_target(format COMMAND ${ASTYLE}
	--style=linux
	--indent=force-tab=8
	--indent-cases
	--indent-preprocessor
	--break-blocks=all
	--pad-oper
	--pad-header
	--unpad-paren
	--keep-one-line-blocks
	--keep-one-line-statements
	--align-pointer=name
	--align-reference=name
	--suffix=none
	--ignore-exclude-errors-x
	--lineend=linux
	--exclude=EASTL
	--add-brackets
	--max-code-length=120
	--preserve-date
	${FORMAT_FILES}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(include)

add_subdirectory(src/hal/arch/posix)

add_subdirectory(src/commander/fsm_main_state)
add_subdirectory(src/commander/fsm_arming_state)

add_test(NAME test_static_analysis
	COMMAND ${SCANBUILD} make
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

include(CPack)
