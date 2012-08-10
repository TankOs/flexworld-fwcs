cmake_minimum_required( VERSION 2.8 )
project( FWCS )

find_package( SFML 2.0 COMPONENTS SYSTEM )

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
	${INC_DIR}/FWCS/Config.hpp
	${INC_DIR}/FWCS/Controller.hpp
	${INC_DIR}/FWCS/Controllers/Acceleration.hpp
	${INC_DIR}/FWCS/Controllers/Drag.hpp
	${INC_DIR}/FWCS/Controllers/ForceReset.hpp
	${INC_DIR}/FWCS/Controllers/Gravity.hpp
	${INC_DIR}/FWCS/Controllers/Movement.hpp
	${INC_DIR}/FWCS/Controllers/MovementForceTransform.hpp
	${INC_DIR}/FWCS/Controllers/PositionLimit.hpp
	${INC_DIR}/FWCS/Entity.hpp
	${INC_DIR}/FWCS/Entity.inl
	${INC_DIR}/FWCS/EntityObserver.hpp
	${INC_DIR}/FWCS/NonCopyable.hpp
	${INC_DIR}/FWCS/Properties/Drag.hpp
	${INC_DIR}/FWCS/Properties/Environment.hpp
	${INC_DIR}/FWCS/Properties/Moveable.hpp
	${INC_DIR}/FWCS/Properties/Object.hpp
	${INC_DIR}/FWCS/Properties/PositionLimit.hpp
	${INC_DIR}/FWCS/Properties/Thrust.hpp
	${INC_DIR}/FWCS/Property.hpp
	${INC_DIR}/FWCS/System.hpp
	${INC_DIR}/FWCS/System.inl
	${INC_DIR}/FWCS/Types.hpp
	${SRC_DIR}/FWCS/Controller.cpp
	${SRC_DIR}/FWCS/Controllers/Acceleration.cpp
	${SRC_DIR}/FWCS/Controllers/Drag.cpp
	${SRC_DIR}/FWCS/Controllers/ForceReset.cpp
	${SRC_DIR}/FWCS/Controllers/Gravity.cpp
	${SRC_DIR}/FWCS/Controllers/Movement.cpp
	${SRC_DIR}/FWCS/Controllers/MovementForceTransform.cpp
	${SRC_DIR}/FWCS/Controllers/PositionLimit.cpp
	${SRC_DIR}/FWCS/Entity.cpp
	${SRC_DIR}/FWCS/NonCopyable.cpp
	${SRC_DIR}/FWCS/Properties/Drag.cpp
	${SRC_DIR}/FWCS/Properties/Environment.cpp
	${SRC_DIR}/FWCS/Properties/Moveable.cpp
	${SRC_DIR}/FWCS/Properties/Object.cpp
	${SRC_DIR}/FWCS/Properties/PositionLimit.cpp
	${SRC_DIR}/FWCS/Properties/Thrust.cpp
	${SRC_DIR}/FWCS/Property.cpp
	${SRC_DIR}/FWCS/System.cpp
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

if( FWCS_BUILD_EXAMPLES )
	add_subdirectory( examples )
endif()

if( FWCS_BUILD_TEST )
	add_subdirectory( test )
endif()

if( FWCS_BUILD_DOCS )
	add_subdirectory( "doc/doxygen" )
endif()
