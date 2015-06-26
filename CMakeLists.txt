cmake_minimum_required(VERSION 2.5)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

project(px4vv C)

enable_testing()

option(COVERALLS "Turn on coveralls support" OFF)
option(COVERALLS_UPLOAD "Upload the generated coveralls json" ON)
option(DOWNLOAD_CBMC "Download CBMC" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
	${CMAKE_SOURCE_DIR}/cmake/coveralls-cmake/cmake)

if (COVERALLS)
	include(Coveralls)
	coveralls_turn_on_coverage()
endif()

# not using spin, modex doesn't support enum
#find_program(VERIFY verify)
find_program(ASTYLE astyle)
find_program(SCANBUILD scan-build)

if (DOWNLOAD_CBMC)
	set(CBMC_LINUX64_TARBALL cbmc-5-1-linux-64.tgz)
	add_custom_command(OUTPUT ${CBMC_LINUX64_TARBALL} 
		COMMAND wget http://www.cprover.org/cbmc/download/${CBMC_LINUX64_TARBALL})
	add_custom_command(OUTPUT cbmc
		COMMAND tar xfz ${CBMC_LINUX64_TARBALL}
		DEPENDS ${CBMC_LINUX64_TARBALL})
	add_custom_target(cbmc_bin ALL DEPENDS cbmc)
	set(CBMC ${CMAKE_BINARY_DIR}/cbmc)
else()
	find_program(CBMC cbmc)
endif()

set(CBMC_ARGS
	-I${CMAKE_SOURCE_DIR}/include
	#--function fsm_main_state_update
	--unwind 4
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

set(COV_SRCS
	${CMAKE_SOURCE_DIR}/src/commander/fsm_arming_state/fsm_arming_state.c
	${CMAKE_SOURCE_DIR}/src/commander/fsm_main_state/fsm_main_state.c
	)

# Setup the coveralls target and tell it to gather
# coverage data for all the lib sources.
if (COVERALLS)
	coveralls_setup(
		"${COV_SRCS}"
        ${COVERALLS_UPLOAD}                 
		"${CMAKE_SOURCE_DIR}/cmake/coveralls-cmake/cmake"
		)
endif()

add_subdirectory(src/hal/arch/posix)

add_subdirectory(src/fsm)
add_subdirectory(src/commander/fsm_main_state)
add_subdirectory(src/commander/fsm_arming_state)

add_test(NAME test_static_analysis
	COMMAND ${SCANBUILD} make
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

configure_file(cmake/travis.yml.cmake ${CMAKE_SOURCE_DIR}/.travis.yml)

set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT "james.goppert@gmail.com")
include(CPack)
