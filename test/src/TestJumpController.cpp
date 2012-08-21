#include <FWCS/Controllers/Jump.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestJumpController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entity.
	{
		ctrl::Jump controller;
		Entity entity;

		entity.create_property<sf::Vector3f>( "force" );
		entity.create_property<sf::Vector3f>( "jump_vector" );
		entity.create_property<float>( "jump_force" );
		entity.create_property<bool>( "jump_active" );

		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		ConcreteProperty<sf::Vector3f>& force = entity.create_property<sf::Vector3f>( "force" );
		ConcreteProperty<sf::Vector3f>& jump_vector = entity.create_property<sf::Vector3f>( "jump_vector" );
		ConcreteProperty<float>& jump_force = entity.create_property<float>( "jump_force" );
		ConcreteProperty<bool>& jump_active = entity.create_property<bool>( "jump_active" );

		force.set_value( sf::Vector3f( 0, 0, 0 ) );
		jump_vector.set_value( sf::Vector3f( 0, 1, 0 ) );
		jump_force.set_value( 100 );
		jump_active.set_value( true );

		ctrl::Jump controller;

		controller.add_entity( entity );
		controller.run( sf::milliseconds( 50 ) );

		BOOST_CHECK( force.get_value() == sf::Vector3f( 0, 100, 0 ) );
		BOOST_CHECK( jump_active.get_value() == false );
	}
}
