#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Properties/PositionLimit.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Entity.hpp>

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
		Entity entity( 0 );

		entity.create_property<prop::Moveable>();
		BOOST_CHECK( limit_controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Object>();
		BOOST_CHECK( limit_controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::PositionLimit>();
		BOOST_CHECK( limit_controller.is_entity_interesting( entity ) == true );
	}

	// Run.
	{
		Entity entity( 0 );

		prop::Moveable& moveable_property = entity.create_property<prop::Moveable>();
		prop::Object& object_property = entity.create_property<prop::Object>();
		prop::PositionLimit& limit_property = entity.create_property<prop::PositionLimit>();

		limit_property.set_upper_limit( sf::Vector3f( +1, +2, +3 ) );
		limit_property.set_lower_limit( sf::Vector3f( -1, -2, -3 ) );

		ctrl::PositionLimit limit_controller;

		limit_controller.add_entity( entity );

		// Clamp lower X.
		{
			moveable_property.set_velocity( sf::Vector3f( 1, 2, 3 ) );
			object_property.set_position( sf::Vector3f( -9, -2, -3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( moveable_property.get_velocity() == sf::Vector3f( 0, 2, 3 ) );
			BOOST_CHECK( object_property.get_position() == sf::Vector3f( -1, -2, -3 ) );
		}
		// Clamp lower Y.
		{
			moveable_property.set_velocity( sf::Vector3f( 1, 2, 3 ) );
			object_property.set_position( sf::Vector3f( -1, -9, -3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( moveable_property.get_velocity() == sf::Vector3f( 1, 0, 3 ) );
			BOOST_CHECK( object_property.get_position() == sf::Vector3f( -1, -2, -3 ) );
		}
		// Clamp lower Z.
		{
			moveable_property.set_velocity( sf::Vector3f( 1, 2, 3 ) );
			object_property.set_position( sf::Vector3f( -1, -2, -9 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( moveable_property.get_velocity() == sf::Vector3f( 1, 2, 0 ) );
			BOOST_CHECK( object_property.get_position() == sf::Vector3f( -1, -2, -3 ) );
		}

		// Clamp upper X.
		{
			moveable_property.set_velocity( sf::Vector3f( 1, 2, 3 ) );
			object_property.set_position( sf::Vector3f( 9, 2, 3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( moveable_property.get_velocity() == sf::Vector3f( 0, 2, 3 ) );
			BOOST_CHECK( object_property.get_position() == sf::Vector3f( 1, 2, 3 ) );
		}
		// Clamp upper Y.
		{
			moveable_property.set_velocity( sf::Vector3f( 1, 2, 3 ) );
			object_property.set_position( sf::Vector3f( 1, 9, 3 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( moveable_property.get_velocity() == sf::Vector3f( 1, 0, 3 ) );
			BOOST_CHECK( object_property.get_position() == sf::Vector3f( 1, 2, 3 ) );
		}
		// Clamp upper Z.
		{
			moveable_property.set_velocity( sf::Vector3f( 1, 2, 3 ) );
			object_property.set_position( sf::Vector3f( 1, 2, 9 ) );

			limit_controller.run( sf::milliseconds( 123 ) );

			BOOST_CHECK( moveable_property.get_velocity() == sf::Vector3f( 1, 2, 0 ) );
			BOOST_CHECK( object_property.get_position() == sf::Vector3f( 1, 2, 3 ) );
		}

	}
}
