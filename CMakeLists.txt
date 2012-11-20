cmake_minimum_required( VERSION 2.8 )
project( FWCS )

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/extlibs/FWU/cmake" )

find_package( FWU REQUIRED )
find_package( SFML 2.0 REQUIRED COMPONENTS SYSTEM )

set( FWCS_BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries." )
set( FWCS_BUILD_TEST TRUE CACHE BOOL "Build test suite." )
set( FWCS_BUILD_EXAMPLES TRUE CACHE BOOL "Build examples." )
set( FWCS_BUILD_DOCS FALSE CACHE BOOL "Build Doxygen API documentation." )
set( FWCS_SKIP_INSTALL FALSE CACHE BOOL "Do not run install target (useful when including lib in projects)." )

if( FWCS_BUILD_SHARED_LIBS )
	set( LIB_TYPE SHARED )
else()
	set( LIB_TYPE STATIC )
endif()

if( CMAKE_COMPILER_IS_GNUCXX )
	if( NOT CMAKE_CXX_FLAGS )
		set( CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Wshadow -Wconversion -pedantic" CACHE STRING "C++ compiler flags." FORCE )
	endif()
endif()

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type." FORCE )
endif()

set( SRC_DIR "src" )
set( INC_DIR "include" )

set(
	SOURCES
	${INC_DIR}/FWCS/BaseControllerFactory.hpp
	${INC_DIR}/FWCS/Config.hpp
	${INC_DIR}/FWCS/Controller.hpp
	${INC_DIR}/FWCS/ControllerFactory.hpp
	${INC_DIR}/FWCS/ControllerFactory.inl
	${INC_DIR}/FWCS/ControllerRequirements.hpp
	${INC_DIR}/FWCS/ControllerRequirements.inl
	${INC_DIR}/FWCS/Controllers/Doc.hpp
	${INC_DIR}/FWCS/Controllers/Move.hpp
	${INC_DIR}/FWCS/Controllers/Walk.hpp
	${INC_DIR}/FWCS/Entity.hpp
	${INC_DIR}/FWCS/Entity.inl
	${INC_DIR}/FWCS/EntityObserver.hpp
	${INC_DIR}/FWCS/Property.hpp
	${INC_DIR}/FWCS/Property.inl
	${INC_DIR}/FWCS/System.hpp
	${INC_DIR}/FWCS/System.inl
	${INC_DIR}/FWCS/Types.hpp
	${SRC_DIR}/FWCS/BaseControllerFactory.cpp
	${SRC_DIR}/FWCS/Controller.cpp
	${SRC_DIR}/FWCS/ControllerRequirements.cpp
	${SRC_DIR}/FWCS/Controllers/Move.cpp
	${SRC_DIR}/FWCS/Controllers/Walk.cpp
	${SRC_DIR}/FWCS/Entity.cpp
	${SRC_DIR}/FWCS/EntityObserver.cpp
	${SRC_DIR}/FWCS/Property.cpp
	${SRC_DIR}/FWCS/System.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${FWU_INCLUDE_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )

add_library( fwcs ${LIB_TYPE} ${SOURCES} )

if( NOT FWCS_SKIP_INSTALL )
	install(
		TARGETS fwcs
		RUNTIME DESTINATION bin COMPONENT bin
		LIBRARY DESTINATION lib COMPONENT bin
		ARCHIVE DESTINATION lib COMPONENT dev
	)
endif()

if( FWCS_BUILD_TEST )
	add_subdirectory( test )
endif()

if( FWCS_BUILD_EXAMPLES )
	add_subdirectory( examples )
endif()

if( FWCS_BUILD_DOCS )
	add_subdirectory( "doc/doxygen" )
endif()
