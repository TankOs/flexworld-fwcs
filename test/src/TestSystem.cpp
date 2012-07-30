#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Properties/Position.hpp>
#include <FWCS/Properties/Velocity.hpp>
#include <FWCS/Controllers/Gravity.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestSystem ) {
	using namespace cs;

	// Initial state.
	{
		System sys;

		BOOST_CHECK( sys.get_num_controllers() == 0 );
		BOOST_CHECK( sys.get_num_entities() == 0 );
	}

	// Create and delete controllers.
	{
		System sys;

		Controller& controller = sys.create_controller<ctl::Gravity>();

		BOOST_CHECK( sys.get_num_controllers() == 1 );
		BOOST_CHECK( sys.find_controller<ctl::Gravity>() == &controller );

		sys.delete_controller<ctl::Gravity>();

		BOOST_CHECK( sys.get_num_controllers() == 0 );
		BOOST_CHECK( sys.find_controller<ctl::Gravity>() == nullptr );
	}

	// Create and delete entities.
	{
		System sys;

		Entity& entity = sys.create_entity( 1337 );

		BOOST_CHECK( sys.find_entity( 1337 ) == &entity );
		BOOST_CHECK( sys.get_num_entities() == 1 );
		BOOST_CHECK( entity.get_id() == 1337 );
		BOOST_REQUIRE( entity.has_observer() );
		BOOST_CHECK( &entity.get_observer() == static_cast<EntityObserver*>( &sys ) );

		Entity& second_entity = sys.create_entity( 2000 );

		BOOST_CHECK( sys.find_entity( 2000 ) == &second_entity );
		BOOST_CHECK( sys.get_num_entities() == 2 );
		BOOST_CHECK( second_entity.get_id() == 2000 );
		BOOST_REQUIRE( second_entity.has_observer() );
		BOOST_CHECK( &second_entity.get_observer() == static_cast<EntityObserver*>( &sys ) );

		// Delete.

		sys.delete_entity( 1337 );

		BOOST_CHECK( sys.get_num_entities() == 1 );
		BOOST_CHECK( sys.find_entity( 1337 ) == nullptr );

		sys.delete_entity( 2000 );

		BOOST_CHECK( sys.get_num_entities() == 0 );
		BOOST_CHECK( sys.find_entity( 2000 ) == nullptr );
	}

	// Automatic linking of entities to controllers.
	{
		// Multiple cases. For every case create 2 entities that have to be linked
		// and 2 that must not be linked.

		// Case: Controller exists before entities.
		{
			System sys;

			sys.create_controller<ctl::Gravity>();

			Entity& pos_entity0 = sys.create_entity( 0 );
			Entity& neg_entity0 = sys.create_entity( 1 );
			Entity& pos_entity1 = sys.create_entity( 2 );
			Entity& neg_entity1 = sys.create_entity( 3 );

			pos_entity0.create_property<prop::Velocity>();
			pos_entity1.create_property<prop::Velocity>();

			neg_entity0.create_property<prop::Position>();
			neg_entity1.create_property<prop::Position>();

			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( neg_entity1 ) == false );
		}

		// Case: Entities exist before controller.
		{
			System sys;

			Entity& pos_entity0 = sys.create_entity( 0 );
			Entity& neg_entity0 = sys.create_entity( 1 );
			Entity& pos_entity1 = sys.create_entity( 2 );
			Entity& neg_entity1 = sys.create_entity( 3 );

			pos_entity0.create_property<prop::Velocity>();
			pos_entity1.create_property<prop::Velocity>();

			neg_entity0.create_property<prop::Position>();
			neg_entity1.create_property<prop::Position>();

			sys.create_controller<ctl::Gravity>();

			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( neg_entity1 ) == false );
		}

		// Case: Mixed.
		{
			System sys;

			Entity& pos_entity0 = sys.create_entity( 0 );
			Entity& neg_entity0 = sys.create_entity( 1 );

			pos_entity0.create_property<prop::Velocity>();
			neg_entity0.create_property<prop::Position>();

			sys.create_controller<ctl::Gravity>();

			Entity& pos_entity1 = sys.create_entity( 2 );
			Entity& neg_entity1 = sys.create_entity( 3 );

			pos_entity1.create_property<prop::Velocity>();
			neg_entity1.create_property<prop::Position>();

			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ctl::Gravity>()->is_entity_linked( neg_entity1 ) == false );
		}
	}
}
