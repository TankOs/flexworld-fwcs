#include <FWCS/Controllers/Acceleration.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestAccelerationController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		Entity entity;
		ctrl::Acceleration controller;

		entity.create_property<sf::Vector3f>( "acceleration" );
		entity.create_property<sf::Vector3f>( "velocity" );
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		ConcreteProperty<sf::Vector3f>& acceleration = entity.create_property<sf::Vector3f>( "acceleration" );
		ConcreteProperty<sf::Vector3f>& velocity = entity.create_property<sf::Vector3f>( "velocity" );

		acceleration.set_value( sf::Vector3f( 10, 20, 30 ) );

		ctrl::Acceleration controller;
		controller.add_entity( entity );

		BOOST_CHECK( velocity.get_value() == sf::Vector3f( 0, 0, 0 ) );
		controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( velocity.get_value() == sf::Vector3f( 10, 20, 30 ) );
	}
}
