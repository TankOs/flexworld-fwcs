#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMovementForceTransformController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		Entity entity( 0 );
		ctrl::MovementForceTransform controller;

		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );
		entity.create_property<prop::Moveable>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity( 0 );
		entity.create_property<prop::Moveable>();
		entity.find_property<prop::Moveable>()->set_force( sf::Vector3f( 10, 20, 30 ) );
		entity.find_property<prop::Moveable>()->set_mass( 10.0f );

		ctrl::MovementForceTransform controller;
		controller.add_entity( entity );

		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_acceleration() == sf::Vector3f( 0, 0, 0 ) );
		controller.run( sf::milliseconds( 1234 ) );
		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_acceleration() == sf::Vector3f( 1, 2, 3 ) );
	}
}
