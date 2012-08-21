#include <FWCS/Controllers/Drag.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestDragController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		ctrl::Drag controller;
		Entity entity;

		entity.create_property<float>( "air_density" );
		entity.create_property<float>( "resistance_coeff" );
		entity.create_property<float>( "drag_area" );
		entity.create_property<sf::Vector3f>( "velocity" );
		entity.create_property<sf::Vector3f>( "force" );
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		ConcreteProperty<float>& air_density = entity.create_property<float>( "air_density" );
		ConcreteProperty<float>& resistance_coeff = entity.create_property<float>( "resistance_coeff" );
		ConcreteProperty<float>& drag_area = entity.create_property<float>( "drag_area" );
		ConcreteProperty<sf::Vector3f>& velocity = entity.create_property<sf::Vector3f>( "velocity" );
		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force" );

		velocity.set_value( sf::Vector3f( 50.0f, 25.0f, 10.0f ) );
		force.set_value( sf::Vector3f( 2000000, 2000000, 2000000 ) );
		drag_area.set_value( 100.0f );
		resistance_coeff.set_value( 5.0f );
		air_density.set_value( 2.0f );

		ctrl::Drag controller;

		controller.add_entity( entity );

		BOOST_CHECK( force.get_value() == sf::Vector3f( 2000000, 2000000, 2000000 ) );
		controller.run( sf::milliseconds( 123 ) );
		BOOST_CHECK( force.get_value() == sf::Vector3f( 750000, 1687500, 1950000 ) );
	}
}
