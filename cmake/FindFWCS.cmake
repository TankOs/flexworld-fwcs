#
# Find FWCS library.
#
# Input variables:
#   FWCS_ROOT              Additional library search directory.
#   FWCS_STATIC_LIBRARIES  Look for static libraries.
#
# Output variables:
#   FWCS_INCLUDE_DIR   Include directory.
#   FWCS_LIBRARY       Library.

cmake_minimum_required( VERSION 2.8 )

set( FWCS_FOUND FALSE )

if( FWCS_STATIC_LIBRARIES )
	set( FWCS_SUFFIX "-s" )
	add_definitions( -DFWCS_STATIC )
else()
	set( FWCS_SUFFIX "" )
endif()

find_path(
	FWCS_INCLUDE_DIR
	FWCS/Config.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${FWCS_ROOT}
)

find_library(
	FWCS_LIBRARY_RELEASE
	fwcs${FWCS_SUFFIX}
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWCS_ROOT}
)

find_library(
	FWCS_LIBRARY_DEBUG
	fwcs${FWCS_SUFFIX}-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWCS_ROOT}
)

if( FWCS_LIBRARY_RELEASE AND FWCS_LIBRARY_DEBUG )
	set( FWCS_LIBRARY debug ${FWCS_LIBRARY_DEBUG} optimized ${FWCS_LIBRARY_RELEASE} )
elseif( FWCS_LIBRARY_RELEASE )
	set( FWCS_LIBRARY ${FWCS_LIBRARY_RELEASE} )
elseif( FWCS_LIBRARY_DEBUG )
	set( FWCS_LIBRARY ${FWCS_LIBRARY_DEBUG} )
endif()

if( NOT FWCS_INCLUDE_DIR OR NOT FWCS_LIBRARY )
	message( FATAL_ERROR "FWCS not found." )
else()
	message( "FWCS found: ${FWCS_INCLUDE_DIR}" )
endif()
