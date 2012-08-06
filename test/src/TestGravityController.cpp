#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Environment.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestGravityController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		ctrl::Gravity gravity_controller;
		Entity entity( 0 );

		BOOST_CHECK( gravity_controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Moveable>();
		BOOST_CHECK( gravity_controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Environment>();
		BOOST_CHECK( gravity_controller.is_entity_interesting( entity ) == true );
	}

	// Update with custom gravity.
	{
		ctrl::Gravity gravity_controller;
		Entity entity( 0 );

		prop::Moveable& moveable_property = entity.create_property<prop::Moveable>();
		prop::Environment& environment_property = entity.create_property<prop::Environment>();

		moveable_property.set_mass( 100.0f );
		environment_property.set_gravity( -100.0f );

		gravity_controller.add_entity( entity );
		
		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_force() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		gravity_controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_force() == sf::Vector3f( 0.0f, -10000.0f, 0.0f ) );
	}
}
