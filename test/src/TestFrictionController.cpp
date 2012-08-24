#include <FWCS/Controllers/Friction.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestFrictionController ) {
	using namespace cs;

	// Initial state.
	{
		ctrl::Friction controller;
	}

	// Interesting entities.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "force" );
		entity.create_property<sf::Vector3f>( "velocity" );
		entity.create_property<sf::Vector3f>( "up_vector" );
		entity.create_property<float>( "static_friction_coeff" );
		entity.create_property<float>( "sliding_friction_coeff" );
		entity.create_property<bool>( "on_ground" );

		ctrl::Friction controller;
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		static const float STATIC_FRICTION_COEFF = 100.0f;
		static const float SLIDING_FRICTION_COEFF = 50.0f;
		static const float NORMAL_FORCE = 10.0f;
		static const float INITIAL_MOVEMENT_FORCE = STATIC_FRICTION_COEFF * NORMAL_FORCE + 100.0f;

		Entity entity;
		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force", sf::Vector3f( 0.0f, -NORMAL_FORCE, 0.0f ) );
		ConcreteProperty<sf::Vector3f>& velocity = entity.create_property<sf::Vector3f>( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		entity.create_property<sf::Vector3f>( "up_vector", sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
		entity.create_property<float>( "static_friction_coeff", STATIC_FRICTION_COEFF );
		entity.create_property<float>( "sliding_friction_coeff", SLIDING_FRICTION_COEFF );
		ConcreteProperty<bool>& on_ground = entity.create_property<bool>( "on_ground", true );

		ctrl::Friction controller;
		controller.add_entity( entity );

		// Static friction.

		// Below maximum static friction force.
		for( float next_force = 0.0f; next_force <= STATIC_FRICTION_COEFF * NORMAL_FORCE; next_force += 0.1f ) {
			force.set_value( sf::Vector3f( next_force, -NORMAL_FORCE, 0.0f ) );

			controller.run( sf::milliseconds( 12345 ) );

			BOOST_CHECK( force.get_value() == sf::Vector3f( 0.0f, -NORMAL_FORCE, 0.0f ) );
		}

		// Above maximum static friction force.
		force.set_value( sf::Vector3f( INITIAL_MOVEMENT_FORCE, -NORMAL_FORCE, 0.0f ) );
		controller.run( sf::milliseconds( 12345 ) );
		BOOST_CHECK( force.get_value().x == 100.0f );

		// Sliding friction.
		velocity.set_value( sf::Vector3f( 1.0f, 0.0f, 0.0f ) );

		for( float next_force = 0.0f; next_force <= SLIDING_FRICTION_COEFF * NORMAL_FORCE * 10.0f; next_force += 0.1f ) {
			force.set_value( sf::Vector3f( next_force, -NORMAL_FORCE, 0.0f ) );

			controller.run( sf::milliseconds( 12345 ) );

			BOOST_CHECK(
				force.get_value() == sf::Vector3f(
					next_force - (SLIDING_FRICTION_COEFF * NORMAL_FORCE),
					-NORMAL_FORCE,
					0.0f
				)
			);
		}
	}
}
