#include <FWCS/Controllers/Jump.hpp>
#include <FWCS/Properties/Jump.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

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
		Entity entity( 0 );

		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Jump>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == false );

		entity.create_property<prop::Moveable>();
		BOOST_CHECK( controller.is_entity_interesting( entity ) == true );
	}

	// Runtime cache.
	{
		Entity entity( 0 );

		entity.create_property<prop::Moveable>();
		entity.create_property<prop::Jump>().set_active( true );

		ctrl::Jump controller;

		controller.add_entity( entity );
		BOOST_CHECK( controller.get_num_cached_entities() == 0 );

		controller.run( sf::milliseconds( 1 ) );
		BOOST_CHECK( controller.get_num_cached_entities() == 1 );

		controller.run( sf::milliseconds( 1 ) );
		BOOST_CHECK( controller.get_num_cached_entities() == 1 );

		controller.run( sf::milliseconds( 8 ) );
		BOOST_CHECK( controller.get_num_cached_entities() == 0 );

		controller.remove_entity( entity );

		// Manually remove.
		entity.find_property<prop::Jump>()->set_active( true );

		controller.add_entity( entity );
		BOOST_CHECK( controller.get_num_cached_entities() == 0 );

		controller.run( sf::milliseconds( 1 ) );
		BOOST_CHECK( controller.get_num_cached_entities() == 1 );

		controller.remove_entity( entity );
		BOOST_CHECK( controller.get_num_cached_entities() == 0 );
	}

	// Run.
	{
		Entity entity( 0 );

		prop::Moveable& moveable_property = entity.create_property<prop::Moveable>();
		prop::Jump& jump_property = entity.create_property<prop::Jump>();

		moveable_property.set_force( sf::Vector3f( 0, 0, 0 ) );
		jump_property.set_up_vector( sf::Vector3f( 0, 1, 0 ) );
		jump_property.set_force( 100 );

		ctrl::Jump controller;

		controller.add_entity( entity );
		controller.run( sf::milliseconds( 10 ) );

		BOOST_CHECK( moveable_property.get_force() == sf::Vector3f( 0, 100, 0 ) );
		BOOST_CHECK( controller.get_num_cached_entities() == 0 );
		BOOST_CHECK( jump_property.is_active() == false );
	}
}
