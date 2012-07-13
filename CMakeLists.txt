cmake_minimum_required( VERSION 2.8 )
project( FWCS )

find_package( SFML 2.0 COMPONENTS SYSTEM )

set( FWCS_BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries." )
set( FWCS_BUILD_TEST TRUE CACHE BOOL "Build test suite." )
set( FWCS_BUILD_EXAMPLES TRUE CACHE BOOL "Build examples." )
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
	${INC_DIR}/FWCS/Config.hpp
	${INC_DIR}/FWCS/Entity.hpp
	${INC_DIR}/FWCS/Entity.inl
	${INC_DIR}/FWCS/Properties/Position.hpp
	${INC_DIR}/FWCS/Properties/Velocity.hpp
	${INC_DIR}/FWCS/Property.hpp
	${INC_DIR}/FWCS/Types.hpp
	${SRC_DIR}/FWCS/Entity.cpp
	${SRC_DIR}/FWCS/Properties/Position.cpp
	${SRC_DIR}/FWCS/Properties/Velocity.cpp
	${SRC_DIR}/FWCS/Property.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )

add_library( fwcs ${LIB_TYPE} ${SOURCES} )

target_link_libraries( fwcs ${SFML_GRAPHICS_LIBRARY} )
target_link_libraries( fwcs ${SFML_WINDOW_LIBRARY} )
target_link_libraries( fwcs ${SFML_SYSTEM_LIBRARY} )

if( NOT FWCS_SKIP_INSTALL )
	install(
		TARGETS fwcs
		RUNTIME DESTINATION bin COMPONENT bin
		LIBRARY DESTINATION lib COMPONENT bin
		ARCHIVE DESTINATION lib COMPONENT dev
	)
endif()

#if( FWCS_BUILD_EXAMPLES )
#	add_subdirectory( examples )
#endif()

if( FWCS_BUILD_TEST )
	add_subdirectory( test )
endif()
