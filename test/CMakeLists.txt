cmake_minimum_required( VERSION 2.8 )
project( FWCS-test )

find_package( Boost 1.46 REQUIRED thread unit_test_framework )

if( NOT Boost_USE_STATIC_LIBS )
	add_definitions( -DBOOST_TEST_DYN_LINK )
endif()

set( SRC_DIR "src" )
set( INC_DIR "src" )

set(
	SOURCES
	${SRC_DIR}/Test.cpp
	${SRC_DIR}/TestControllerFactory.cpp
	${SRC_DIR}/TestControllerRequirements.cpp
	${SRC_DIR}/TestEntity.cpp
	${SRC_DIR}/TestMoveController.cpp
	${SRC_DIR}/TestProperty.cpp
	${SRC_DIR}/TestSystem.cpp
	${SRC_DIR}/TestTopDownTurnConstraint.cpp
	${SRC_DIR}/TestTurnController.cpp
	${SRC_DIR}/TestWalkController.cpp
)

include_directories( ${PROJECT_SOURCE_DIR}/../include )
include_directories( ${FWU_INCLUDE_DIR} )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable( test ${SOURCES} )

target_link_libraries( test fwcs )
target_link_libraries( test ${FWU_LIBRARY} )
target_link_libraries( test ${SFML_SYSTEM_LIBRARY} )
target_link_libraries( test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries( test ${Boost_THREAD_LIBRARY} )

add_custom_command(
	TARGET test
	COMMAND test
	ARGUMENTS "--log_level=message"
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
