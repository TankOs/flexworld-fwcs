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
	${INC_DIR}/DummyProperties.hpp
	${SRC_DIR}/DummyProperties.cpp
	${SRC_DIR}/Test.cpp
	${SRC_DIR}/TestAccelerationController.cpp
	${SRC_DIR}/TestController.cpp
	${SRC_DIR}/TestDragProperty.cpp
	${SRC_DIR}/TestEntity.cpp
	${SRC_DIR}/TestForceResetController.cpp
	${SRC_DIR}/TestGravityController.cpp
	${SRC_DIR}/TestMoveableProperty.cpp
	${SRC_DIR}/TestMovementForceTransformController.cpp
	${SRC_DIR}/TestObjectProperty.cpp
	${SRC_DIR}/TestSystem.cpp
)

include_directories( ${PROJECT_SOURCE_DIR}/../include )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable( test ${SOURCES} )

target_link_libraries( test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries( test ${Boost_THREAD_LIBRARY} )
target_link_libraries( test fwcs )

add_custom_command(
	TARGET test
	COMMAND test
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
