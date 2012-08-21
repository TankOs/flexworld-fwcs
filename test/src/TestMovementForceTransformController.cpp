#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMovementForceTransformController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "force" );
		entity.create_property<sf::Vector3f>( "acceleration" );
		entity.create_property<float>( "mass" );

		ctrl::MovementForceTransform controller;
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;
		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force" );
		ConcreteProperty<sf::Vector3f>& acceleration = entity.create_property<sf::Vector3f>( "acceleration" );
		ConcreteProperty<float>& mass = entity.create_property<float>( "mass" );

		force.set_value( sf::Vector3f( 10, 20, 30 ) );
		mass.set_value( 10.0f );

		ctrl::MovementForceTransform controller;
		controller.add_entity( entity );

		BOOST_CHECK( acceleration.get_value() == sf::Vector3f( 0, 0, 0 ) );
		controller.run( sf::milliseconds( 1234 ) );
		BOOST_CHECK( acceleration.get_value() == sf::Vector3f( 1, 2, 3 ) );
	}
}
