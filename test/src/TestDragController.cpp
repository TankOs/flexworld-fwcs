#include <FWCS/Controllers/Drag.hpp>
#include <FWCS/Properties/Drag.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Environment.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestDragController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		ctrl::Drag controller;
		Entity entity( 0 );

		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Drag>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Moveable>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Environment>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity( 0 );

		prop::Moveable& moveable_property = entity.create_property<prop::Moveable>();
		prop::Drag& drag_property = entity.create_property<prop::Drag>();
		prop::Environment& env_property = entity.create_property<prop::Environment>();

		moveable_property.set_mass( 10.0f );
		moveable_property.set_velocity( sf::Vector3f( 50.0f, 25.0f, 10.0f ) );
		moveable_property.set_force( sf::Vector3f( 2000000, 2000000, 2000000 ) );
		drag_property.set_area( 100.0f );
		drag_property.set_resistance_coeff( 5.0f );
		env_property.set_air_density( 2.0f );

		ctrl::Drag controller;

		controller.add_entity( entity );

		BOOST_CHECK( moveable_property.get_force() == sf::Vector3f( 2000000, 2000000, 2000000 ) );
		controller.run( sf::milliseconds( 123 ) );
		BOOST_CHECK( moveable_property.get_force() == sf::Vector3f( 750000, 1687500, 1950000 ) );
	}
}
