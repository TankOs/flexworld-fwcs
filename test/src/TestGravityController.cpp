#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

/*
BOOST_AUTO_TEST_CASE( TestGravityController ) {
	using namespace cs;

	// Initial state.
	{
		{
			ctl::Gravity gravity_controller;

			BOOST_CHECK( gravity_controller.get_gravity() == 9.80665f );
		}
		{
			ctl::Gravity gravity_controller( 123.45f );

			BOOST_CHECK( gravity_controller.get_gravity() == 123.45f );
		}
	}

	// Interesting entity.
	{
		ctl::Gravity gravity_controller;
		Entity entity( 0 );

		entity.create_property<prop::Velocity>();
		entity.create_property<prop::Mass>();

		BOOST_CHECK( gravity_controller.is_entity_interesting( entity ) == true );
	}

	// Update with custom gravity.
	{
		ctl::Gravity gravity_controller( -100.0f );
		Entity entity( 0 );

		entity.create_property<prop::Velocity>();
		entity.create_property<prop::Mass>();

		gravity_controller.add_entity( entity );
		
		BOOST_CHECK( entity.find_property<prop::Velocity>()->get_velocity() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		gravity_controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( entity.find_property<prop::Velocity>()->get_velocity() == sf::Vector3f( 0.0f, -100.0f, 0.0f ) );
	}
}
*/
