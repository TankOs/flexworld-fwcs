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
		entity.create_property<sf::Vector2f>( "control_vector" );
		entity.create_property<float>( "walk_force" );

		ctrl::Walk controller;
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		entity.create_property<sf::Vector3f>( "forward_vector", sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force" );
		ConcreteProperty<sf::Vector2f>& control_vector = entity.create_property<sf::Vector2f>( "control_vector" );
		entity.create_property<float>( "walk_force", 100.0f );

		ctrl::Walk controller;
		controller.add_entity( entity );

		controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( force.get_value() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );

		force.set_value( sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		control_vector.set_value( sf::Vector2f( 0.0f, 1.0f ) );
		controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( force.get_value() == sf::Vector3f( 100.0f, 0.0f, 0.0f ) );

		force.set_value( sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		control_vector.set_value( sf::Vector2f( 0.0f, 0.5f ) );
		controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( force.get_value() == sf::Vector3f( 50.0f, 0.0f, 0.0f ) );

		force.set_value( sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		control_vector.set_value( sf::Vector2f( 1.0f, 0.0f ) );
		controller.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( force.get_value().x >= -0.001f && force.get_value().x <= 0.001f );
		BOOST_CHECK( force.get_value().y == 0.0f );
		BOOST_CHECK( force.get_value().z >= 99.999f && force.get_value().z <= 100.001f );
	}
}
