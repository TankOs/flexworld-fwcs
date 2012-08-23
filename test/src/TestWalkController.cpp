#include <FWCS/Controllers/Walk.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestWalkController ) {
	using namespace cs;

	// Initial state.
	{
		ctrl::Walk controller;
	}

	// Interesting entities.
	{
		Entity entity;
		entity.create_property<sf::Vector3f>( "forward_vector" );
		entity.create_property<sf::Vector3f>( "force" );
		entity.create_property<sf::Vector3f>( "velocity" );
		entity.create_property<sf::Vector2f>( "walk_control_vector" );
		entity.create_property<float>( "walk_force" );
		entity.create_property<float>( "max_walk_velocity" );

		ctrl::Walk controller;
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		entity.create_property<sf::Vector3f>( "forward_vector", sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force" );
		entity.create_property<sf::Vector3f>( "velocity" );
		entity.create_property<sf::Vector2f>( "walk_control_vector" );
		entity.create_property<float>( "walk_force", 100.0f );
		entity.create_property<float>( "max_walk_velocity", 10.0f );

		ctrl::Walk controller;
		controller.add_entity( entity );

		controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( force.get_value() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );

		// WALKING TESTED BY ACCEPTANCE TEST.
	}
}
