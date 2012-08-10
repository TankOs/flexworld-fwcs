#include <FWCS/Controllers/ThrustReset.hpp>
#include <FWCS/Properties/Thrust.hpp>
#include <FWCS/Entity.hpp>

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
		Entity entity( 0 );

		entity.create_property<prop::Thrust>();

		ctrl::ThrustReset controller;

		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity( 0 );

		entity.create_property<prop::Thrust>();
		entity.find_property<prop::Thrust>()->set_thrust( sf::Vector3f( 1, 2, 3 ) );

		BOOST_CHECK( entity.find_property<prop::Thrust>()->get_thrust() == sf::Vector3f( 1, 2, 3 ) );

		ctrl::ThrustReset controller;

		controller.add_entity( entity );
		controller.run( sf::milliseconds( 1 ) );

		BOOST_CHECK( entity.find_property<prop::Thrust>()->get_thrust() == sf::Vector3f( 0, 0, 0 ) );
	}
}
