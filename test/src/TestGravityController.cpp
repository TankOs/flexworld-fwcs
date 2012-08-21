#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestGravityController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		ctrl::Gravity gravity_controller;
		Entity entity;

		entity.create_property<sf::Vector3f>( "force" );
		entity.create_property<float>( "gravity" );
		entity.create_property<float>( "mass" );

		BOOST_CHECK( gravity_controller.is_entity_interesting( entity ) == true );
	}

	// Update with custom gravity.
	{
		ctrl::Gravity gravity_controller;
		Entity entity;

		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force" );
		ConcreteProperty<float>& gravity = entity.create_property<float>( "gravity" );
		ConcreteProperty<float>& mass = entity.create_property<float>( "mass" );

		mass.set_value( 100.0f );
		gravity.set_value( -100.0f );

		gravity_controller.add_entity( entity );
		
		BOOST_CHECK( force.get_value() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		gravity_controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( force.get_value() == sf::Vector3f( 0.0f, -10000.0f, 0.0f ) );
	}
}
