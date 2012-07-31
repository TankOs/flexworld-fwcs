#include "DummyProperties.hpp"

#include <FWCS/System.hpp>
#include <FWCS/Controller.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class ExampleRunController : public cs::Controller {
	public:
		ExampleRunController() :
			cs::Controller(),
			m_num_update_calls( 0 )
		{
			listen_for( "DummyProperty1" );
		}

		void update_entity( cs::Entity& entity, const sf::Time& delta ) {
			BOOST_CHECK( entity.get_id() == 123 );
			BOOST_CHECK( delta == sf::milliseconds( 1000 ) );

			++m_num_update_calls;
		}

		std::size_t m_num_update_calls;
};

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

		Controller& controller = sys.create_controller<ExampleRunController>();

		BOOST_CHECK( sys.get_num_controllers() == 1 );
		BOOST_CHECK( sys.find_controller<ExampleRunController>() == &controller );

		sys.delete_controller<ExampleRunController>();

		BOOST_CHECK( sys.get_num_controllers() == 0 );
		BOOST_CHECK( sys.find_controller<ExampleRunController>() == nullptr );
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

			sys.create_controller<ExampleRunController>();

			Entity& pos_entity0 = sys.create_entity( 0 );
			Entity& neg_entity0 = sys.create_entity( 1 );
			Entity& pos_entity1 = sys.create_entity( 2 );
			Entity& neg_entity1 = sys.create_entity( 3 );

			pos_entity0.create_property<DummyProperty1>();
			pos_entity1.create_property<DummyProperty1>();

			neg_entity0.create_property<DummyProperty0>();
			neg_entity1.create_property<DummyProperty0>();

			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity1 ) == false );
		}

		// Case: Entities exist before controller.
		{
			System sys;

			Entity& pos_entity0 = sys.create_entity( 0 );
			Entity& neg_entity0 = sys.create_entity( 1 );
			Entity& pos_entity1 = sys.create_entity( 2 );
			Entity& neg_entity1 = sys.create_entity( 3 );

			pos_entity0.create_property<DummyProperty1>();
			pos_entity1.create_property<DummyProperty1>();

			neg_entity0.create_property<DummyProperty0>();
			neg_entity1.create_property<DummyProperty0>();

			sys.create_controller<ExampleRunController>();

			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity1 ) == false );
		}

		// Case: Mixed.
		{
			System sys;

			Entity& pos_entity0 = sys.create_entity( 0 );
			Entity& neg_entity0 = sys.create_entity( 1 );

			pos_entity0.create_property<DummyProperty1>();
			neg_entity0.create_property<DummyProperty0>();

			sys.create_controller<ExampleRunController>();

			Entity& pos_entity1 = sys.create_entity( 2 );
			Entity& neg_entity1 = sys.create_entity( 3 );

			pos_entity1.create_property<DummyProperty1>();
			neg_entity1.create_property<DummyProperty0>();

			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity1 ) == false );
		}
	}

	// Run controllers.
	{
		System sys;
		
		ExampleRunController& controller = sys.create_controller<ExampleRunController>();
		Entity& entity = sys.create_entity( 123 );

		entity.create_property<DummyProperty1>();

		sys.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( controller.m_num_update_calls == 1 );

		sys.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( controller.m_num_update_calls == 2 );
	}
}
