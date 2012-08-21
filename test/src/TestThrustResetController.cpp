#include <FWCS/Controllers/ThrustReset.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestThrustResetController ) {
	using namespace cs;

	// Initial state.
	{
		ctrl::ThrustReset controller;
	}

	// Interesting entities.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "thrust" );

		ctrl::ThrustReset controller;
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "thrust" );

		ConcreteProperty<sf::Vector3f>* thrust = entity.find_property<sf::Vector3f>( "thrust" );
		BOOST_REQUIRE( thrust != nullptr );

		thrust->set_value( sf::Vector3f( 1, 2, 3 ) );
		BOOST_CHECK( thrust->get_value() == sf::Vector3f( 1, 2, 3 ) );

		ctrl::ThrustReset controller;

		controller.add_entity( entity );
		controller.run( sf::milliseconds( 1 ) );

		BOOST_CHECK( thrust->get_value() == sf::Vector3f( 0, 0, 0 ) );
	}
}
