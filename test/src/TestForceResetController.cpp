#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

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
		Entity entity( 0 );

		entity.create_property<prop::Moveable>();

		ctrl::ForceReset controller;

		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity( 0 );

		entity.create_property<prop::Moveable>();
		entity.find_property<prop::Moveable>()->set_force( sf::Vector3f( 1, 2, 3 ) );

		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_force() == sf::Vector3f( 1, 2, 3 ) );

		ctrl::ForceReset controller;

		controller.add_entity( entity );
		controller.run( sf::milliseconds( 1 ) );

		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_force() == sf::Vector3f( 0, 0, 0 ) );
	}
}
