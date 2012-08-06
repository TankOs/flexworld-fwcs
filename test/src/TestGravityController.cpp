#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestGravityController ) {
	using namespace cs;

	// Initial state.
	{
		{
			ctrl::Gravity gravity_controller;

			BOOST_CHECK( gravity_controller.get_gravity() == -9.80665f );
		}
		{
			ctrl::Gravity gravity_controller( 123.45f );

			BOOST_CHECK( gravity_controller.get_gravity() == 123.45f );
		}
	}

	// Basic properties.
	{
		ctrl::Gravity gravity_controller;

		BOOST_CHECK( gravity_controller.get_gravity() == -9.80665f );
		gravity_controller.set_gravity( 1.2345f );
		BOOST_CHECK( gravity_controller.get_gravity() == 1.2345f );
	}

	// Interesting entity.
	{
		ctrl::Gravity gravity_controller;
		Entity entity( 0 );

		entity.create_property<prop::Moveable>();

		BOOST_CHECK( gravity_controller.is_entity_interesting( entity ) == true );
	}

	// Update with custom gravity.
	{
		ctrl::Gravity gravity_controller( -100.0f );
		Entity entity( 0 );

		entity.create_property<prop::Moveable>();
		entity.find_property<prop::Moveable>()->set_mass( 100.0f );

		gravity_controller.add_entity( entity );
		
		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_force() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		gravity_controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( entity.find_property<prop::Moveable>()->get_force() == sf::Vector3f( 0.0f, -10000.0f, 0.0f ) );
	}
}
