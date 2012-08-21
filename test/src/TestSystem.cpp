#include <FWCS/System.hpp>
#include <FWCS/Controller.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class ExampleRunController : public cs::Controller {
	public:
		ExampleRunController() :
			cs::Controller(),
			m_num_update_calls( 0 ),
			m_last_updated_entity( nullptr )
		{
			listen_for<float>( "dummy_0" );
		}

		void update_entity( cs::Entity& entity, const sf::Time& delta ) {
			BOOST_CHECK( delta == sf::milliseconds( 1000 ) );

			m_last_updated_entity = &entity;
			++m_num_update_calls;
		}

		std::size_t m_num_update_calls;
		const cs::Entity* m_last_updated_entity;
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

		Entity& entity = sys.create_entity();

		BOOST_CHECK( sys.get_num_entities() == 1 );
		BOOST_REQUIRE( entity.has_observer() );
		BOOST_CHECK( &entity.get_observer() == static_cast<EntityObserver*>( &sys ) );

		Entity& second_entity = sys.create_entity();

		BOOST_CHECK( sys.get_num_entities() == 2 );
		BOOST_REQUIRE( second_entity.has_observer() );
		BOOST_CHECK( &second_entity.get_observer() == static_cast<EntityObserver*>( &sys ) );

		// Delete.

		sys.delete_entity( entity );

		BOOST_CHECK( sys.get_num_entities() == 1 );

		sys.delete_entity( second_entity );

		BOOST_CHECK( sys.get_num_entities() == 0 );
	}

	// Automatic linking of entities to controllers.
	{
		// Multiple cases. For every case create 2 entities that have to be linked
		// and 2 that must not be linked.

		// Case: Controller exists before entities.
		{
			System sys;

			sys.create_controller<ExampleRunController>();

			Entity& pos_entity0 = sys.create_entity();
			Entity& neg_entity0 = sys.create_entity();
			Entity& pos_entity1 = sys.create_entity();
			Entity& neg_entity1 = sys.create_entity();

			pos_entity0.create_property<float>( "dummy_0" );
			pos_entity1.create_property<float>( "dummy_0" );

			neg_entity0.create_property<int32_t>( "dummy_1" );
			neg_entity1.create_property<int32_t>( "dummy_1" );

			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity1 ) == false );
		}

		// Case: Entities exist before controller.
		{
			System sys;

			Entity& pos_entity0 = sys.create_entity();
			Entity& neg_entity0 = sys.create_entity();
			Entity& pos_entity1 = sys.create_entity();
			Entity& neg_entity1 = sys.create_entity();

			pos_entity0.create_property<float>( "dummy_0" );
			pos_entity1.create_property<float>( "dummy_0" );

			neg_entity0.create_property<int32_t>( "dummy_1" );
			neg_entity1.create_property<int32_t>( "dummy_1" );

			sys.create_controller<ExampleRunController>();

			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity0 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity0 ) == false );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( pos_entity1 ) == true );
			BOOST_CHECK( sys.find_controller<ExampleRunController>()->is_entity_linked( neg_entity1 ) == false );
		}

		// Case: Mixed.
		{
			System sys;

			Entity& pos_entity0 = sys.create_entity();
			Entity& neg_entity0 = sys.create_entity();

			pos_entity0.create_property<float>( "dummy_0" );
			neg_entity0.create_property<int32_t>( "dummy_1" );

			sys.create_controller<ExampleRunController>();

			Entity& pos_entity1 = sys.create_entity();
			Entity& neg_entity1 = sys.create_entity();

			pos_entity1.create_property<float>( "dummy_0" );
			neg_entity1.create_property<int32_t>( "dummy_1" );

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
		Entity& entity = sys.create_entity();

		entity.create_property<float>( "dummy_0" );

		sys.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( controller.m_num_update_calls == 1 );
		BOOST_CHECK( controller.m_last_updated_entity = &entity );

		sys.run( sf::milliseconds( 1000 ) );
		BOOST_CHECK( controller.m_num_update_calls == 2 );
		BOOST_CHECK( controller.m_last_updated_entity = &entity );
	}
}
