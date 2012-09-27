cmake_minimum_required( VERSION 2.8 )

find_package( SFML 2.0 REQUIRED GRAPHICS WINDOW SYSTEM )

macro( build_example target sources )
	include_directories( ${PROJECT_SOURCE_DIR}/../include/ )
	include_directories( ${SFML_INCLUDE_DIR}/../include/ )

	add_executable( ${target} ${sources} )

	target_link_libraries( ${target} fwcs )
	target_link_libraries( ${target} ${SFML_GRAPHICS_LIBRARY} )
	target_link_libraries( ${target} ${SFML_WINDOW_LIBRARY} )
	target_link_libraries( ${target} ${SFML_SYSTEM_LIBRARY} )

	install(
		TARGETS ${target}
		DESTINATION share/FWCS/examples
	)
endmacro()

#build_example( runner Runner.cpp )

install(
	DIRECTORY data
	DESTINATION share/FWCS/examples
)
