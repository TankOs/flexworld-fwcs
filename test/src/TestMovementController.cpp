#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMovementController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		Entity entity( 0 );
		ctrl::Movement controller;

		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Moveable>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Object>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity( 0 );
		entity.create_property<prop::Moveable>();
		entity.create_property<prop::Object>();
		entity.find_property<prop::Moveable>()->set_velocity( sf::Vector3f( 10, 20, 30 ) );

		ctrl::Movement controller;
		controller.add_entity( entity );

		BOOST_CHECK( entity.find_property<prop::Object>()->get_position() == sf::Vector3f( 0, 0, 0 ) );
		controller.run( sf::milliseconds( 2000 ) );
		BOOST_CHECK( entity.find_property<prop::Object>()->get_position() == sf::Vector3f( 20, 40, 60 ) );
	}
}
