#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMovementController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		Entity entity;
		ctrl::Movement controller;

		entity.create_property<sf::Vector3f>( "position" );
		entity.create_property<sf::Vector3f>( "velocity" );
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		ConcreteProperty<sf::Vector3f>& position = entity.create_property<sf::Vector3f>( "position" );
		ConcreteProperty<sf::Vector3f>& velocity = entity.create_property<sf::Vector3f>( "velocity" );

		velocity.set_value( sf::Vector3f( 10, 20, 30 ) );

		ctrl::Movement controller;
		controller.add_entity( entity );

		BOOST_CHECK( position.get_value() == sf::Vector3f( 0, 0, 0 ) );
		controller.run( sf::milliseconds( 2000 ) );
		BOOST_CHECK( position.get_value() == sf::Vector3f( 20, 40, 60 ) );
	}
}
