#include <FWCS/Controller.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>
#include <set>
#include <cstdint>

static const sf::Time DELTA_T = sf::milliseconds( 12345 );

class ExampleController : public cs::Controller {
	public:
		ExampleController() :
			cs::Controller(),
			m_num_update_calls( 0 ),
			m_num_add_calls( 0 ),
			m_num_remove_calls( 0 )
		{
			listen_for<float>( "dummy_0" );
			listen_for<int32_t>( "dummy_1" );

			BOOST_REQUIRE( get_required_properties().size() == 2 );
			BOOST_CHECK( get_required_properties()[0].first == "dummy_0" );
			BOOST_CHECK( get_required_properties()[0].second == typeid( float ).name() );
			BOOST_CHECK( get_required_properties()[1].first == "dummy_1" );
			BOOST_CHECK( get_required_properties()[1].second == typeid( int32_t ).name() );
		}

		void update_entity( cs::Entity& entity, const sf::Time& delta ) {
			BOOST_CHECK( delta == DELTA_T );

			m_entities.insert( &entity );
			++m_num_update_calls;
		}

		void on_entity_add( cs::Entity& entity ) {
			m_entities.insert( &entity );
			++m_num_add_calls;
		}

		void on_entity_remove( cs::Entity& entity ) {
			m_entities.erase( &entity );
			++m_num_remove_calls;
		}

		std::size_t m_num_update_calls;
		std::size_t m_num_add_calls;
		std::size_t m_num_remove_calls;
		std::set<const cs::Entity*> m_entities;
};

BOOST_AUTO_TEST_CASE( TestController ) {
	using namespace cs;

	// Initial state.
	{
		Controller controller;

		BOOST_CHECK( controller.get_required_properties().size() == 0 );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
	}

	// Controller setup.
	{
		ExampleController controller;

		BOOST_REQUIRE( controller.get_required_properties().size() == 2 );
		BOOST_CHECK( controller.get_required_properties()[0].first == "dummy_0" );
		BOOST_CHECK( controller.get_required_properties()[0].second == typeid( float ).name() );
		BOOST_CHECK( controller.get_required_properties()[1].first == "dummy_1" );
		BOOST_CHECK( controller.get_required_properties()[1].second == typeid( int32_t ).name() );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
	}

	// Check interesting entities.
	{
		// No interesting entity.
		{
			Entity ent;
			ExampleController controller;

			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent;
			ent.create_property<float>( "dummy_0" );

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent;
			ent.create_property<int32_t>( "dummy_1" );

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent;
			ent.create_property<float>( "dummy_0" );
			ent.create_property<float>( "dummy_1" );

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// Interesting entity.
		{
			Entity ent;
			ent.create_property<float>( "dummy_0" );
			ent.create_property<int32_t>( "dummy_1" );

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == true );
		}
	}

	// Add and remove entities.
	{
		Entity ent0;
		ent0.create_property<float>( "dummy_0" );
		ent0.create_property<int32_t>( "dummy_1" );

		Entity ent1;
		ent1.create_property<float>( "dummy_0" );
		ent1.create_property<int32_t>( "dummy_1" );

		ExampleController controller;
		BOOST_REQUIRE( controller.is_entity_interesting( ent0 ) == true );
		BOOST_REQUIRE( controller.is_entity_interesting( ent1 ) == true );

		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == false );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == false );
		BOOST_CHECK( controller.m_num_add_calls == 0 );

		controller.add_entity( ent0 );
		BOOST_CHECK( controller.m_num_add_calls == 1 );
		BOOST_CHECK( controller.m_entities.find( &ent0 ) != controller.m_entities.end() );
		BOOST_CHECK( controller.get_num_linked_entities() == 1 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == true );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == false );

		controller.add_entity( ent1 );
		BOOST_CHECK( controller.m_num_add_calls == 2 );
		BOOST_CHECK( controller.m_entities.find( &ent1 ) != controller.m_entities.end() );
		BOOST_CHECK( controller.get_num_linked_entities() == 2 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == true );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == true );

		// Remove again.
		BOOST_CHECK( controller.m_num_remove_calls == 0 );

		controller.remove_entity( ent0 );
		BOOST_CHECK( controller.m_num_remove_calls == 1 );
		BOOST_CHECK( controller.m_entities.find( &ent0 ) == controller.m_entities.end() );
		BOOST_CHECK( controller.get_num_linked_entities() == 1 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == false );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == true );

		controller.remove_entity( ent1 );
		BOOST_CHECK( controller.m_num_remove_calls == 2 );
		BOOST_CHECK( controller.m_entities.size() == 0 );
		BOOST_CHECK( controller.m_entities.find( &ent1 ) == controller.m_entities.end() );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == false );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == false );
	}

	// Update entities.
	{
		Entity ent0;
		ent0.create_property<float>( "dummy_0" );
		ent0.create_property<int32_t>( "dummy_1" );

		Entity ent1;
		ent1.create_property<float>( "dummy_0" );
		ent1.create_property<int32_t>( "dummy_1" );

		ExampleController controller;
		controller.add_entity( ent0 );
		controller.add_entity( ent1 );

		controller.run( DELTA_T );

		BOOST_CHECK( controller.m_num_update_calls == 2 );
		BOOST_CHECK( controller.m_entities.find( &ent0 ) != controller.m_entities.end() );
		BOOST_CHECK( controller.m_entities.find( &ent1 ) != controller.m_entities.end() );
	}
}
