#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestPositionLimitController ) {
	using namespace cs;

	// Initial state.
	{
	}

	// Interesting entities.
	{
		ctrl::PositionLimit limit_controller;
		Entity entity;

		entity.create_property<sf::Vector3f>( "position" );
		entity.create_property<sf::Vector3f>( "velocity" );
		entity.create_property<sf::Vector3f>( "lower_position_limit" );
		entity.create_property<sf::Vector3f>( "upper_position_limit" );

		BOOST_CHECK( limit_controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity;

		ConcreteProperty<sf::Vector3f>& velocity = entity.create_property<sf::Vector3f>( "velocity" );
		ConcreteProperty<sf::Vector3f>& position = entity.create_property<sf::Vector3f>( "position" );
		ConcreteProperty<sf::Vector3f>& lower_limit = entity.create_property<sf::Vector3f>( "lower_position_limit" );
		ConcreteProperty<sf::Vector3f>& upper_limit = entity.create_property<sf::Vector3f>( "upper_position_limit" );

		upper_limit.set_value( sf::Vector3f( +1, +2, +3 ) );
		lower_limit.set_value( sf::Vector3f( -1, -2, -3 ) );

		ctrl::PositionLimit limit_controller;

		limit_controller.add_entity( entity );

		// Clamp lower X.
		{
			velocity.set_value( sf::Vector3f( 1, 2, 3 ) );
			position.set_value( sf::Vector3f( -9, -2, -3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( velocity.get_value() == sf::Vector3f( 0, 2, 3 ) );
			BOOST_CHECK( position.get_value() == sf::Vector3f( -1, -2, -3 ) );
		}
		// Clamp lower Y.
		{
			velocity.set_value( sf::Vector3f( 1, 2, 3 ) );
			position.set_value( sf::Vector3f( -1, -9, -3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( velocity.get_value() == sf::Vector3f( 1, 0, 3 ) );
			BOOST_CHECK( position.get_value() == sf::Vector3f( -1, -2, -3 ) );
		}
		// Clamp lower Z.
		{
			velocity.set_value( sf::Vector3f( 1, 2, 3 ) );
			position.set_value( sf::Vector3f( -1, -2, -9 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( velocity.get_value() == sf::Vector3f( 1, 2, 0 ) );
			BOOST_CHECK( position.get_value() == sf::Vector3f( -1, -2, -3 ) );
		}

		// Clamp upper X.
		{
			velocity.set_value( sf::Vector3f( 1, 2, 3 ) );
			position.set_value( sf::Vector3f( 9, 2, 3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( velocity.get_value() == sf::Vector3f( 0, 2, 3 ) );
			BOOST_CHECK( position.get_value() == sf::Vector3f( 1, 2, 3 ) );
		}
		// Clamp upper Y.
		{
			velocity.set_value( sf::Vector3f( 1, 2, 3 ) );
			position.set_value( sf::Vector3f( 1, 9, 3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( velocity.get_value() == sf::Vector3f( 1, 0, 3 ) );
			BOOST_CHECK( position.get_value() == sf::Vector3f( 1, 2, 3 ) );
		}
		// Clamp upper Z.
		{
			velocity.set_value( sf::Vector3f( 1, 2, 3 ) );
			position.set_value( sf::Vector3f( 1, 2, 9 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( velocity.get_value() == sf::Vector3f( 1, 2, 0 ) );
			BOOST_CHECK( position.get_value() == sf::Vector3f( 1, 2, 3 ) );
		}

	}
}
