#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestForceResetController ) {
	using namespace cs;

	// Initial state.
	{
		ctrl::ForceReset controller;
	}

	// Interesting entities.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "force" );

		ctrl::ForceReset controller;

		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "force" );

		ConcreteProperty<sf::Vector3f>* force = entity.find_property<sf::Vector3f>( "force" );
		BOOST_REQUIRE( force != nullptr );

		force->set_value( sf::Vector3f( 1, 2, 3 ) );
		BOOST_CHECK( force->get_value() == sf::Vector3f( 1, 2, 3 ) );

		ctrl::ForceReset controller;

		controller.add_entity( entity );
		controller.run( sf::milliseconds( 1 ) );

		BOOST_CHECK( force->get_value() == sf::Vector3f( 0, 0, 0 ) );
	}
}
