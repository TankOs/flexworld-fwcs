#include "DummyProperties.hpp"

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
			m_num_update_calls( 0 )
		{
			listen_for( "DummyProperty0" );
			listen_for( "DummyProperty1" );

			BOOST_REQUIRE( get_required_properties().size() == 2 );
			BOOST_CHECK( get_required_properties()[0] == "DummyProperty0" );
			BOOST_CHECK( get_required_properties()[1] == "DummyProperty1" );
		}

		void update_entity( cs::Entity& entity, const sf::Time& delta ) {
			BOOST_CHECK( delta == DELTA_T );

			if( m_entity_ids.find( entity.get_id() ) == m_entity_ids.end() ) {
				m_entity_ids.insert( entity.get_id() );
			}

			++m_num_update_calls;
		}

		std::size_t m_num_update_calls;
		std::set<uint32_t> m_entity_ids;
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
		BOOST_CHECK( controller.get_required_properties()[0] == "DummyProperty0" );
		BOOST_CHECK( controller.get_required_properties()[1] == "DummyProperty1" );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
	}

	// Check interesting entities.
	{
		// No interesting entity.
		{
			Entity ent( 0 );
			ExampleController controller;

			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent( 0 );
			ent.create_property<DummyProperty1>();

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent( 0 );
			ent.create_property<DummyProperty0>();

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// Interesting entity.
		{
			Entity ent( 0 );
			ent.create_property<DummyProperty1>();
			ent.create_property<DummyProperty0>();

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == true );
		}
	}

	// Add and remove entities.
	{
		Entity ent0( 0 );
		ent0.create_property<DummyProperty1>();
		ent0.create_property<DummyProperty0>();

		Entity ent1( 0 );
		ent1.create_property<DummyProperty1>();
		ent1.create_property<DummyProperty0>();

		ExampleController controller;
		BOOST_REQUIRE( controller.is_entity_interesting( ent0 ) == true );
		BOOST_REQUIRE( controller.is_entity_interesting( ent1 ) == true );

		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == false );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == false );

		controller.add_entity( ent0 );
		BOOST_CHECK( controller.get_num_linked_entities() == 1 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == true );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == false );

		controller.add_entity( ent1 );
		BOOST_CHECK( controller.get_num_linked_entities() == 2 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == true );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == true );

		// Remove again.
		controller.remove_entity( ent0 );
		BOOST_CHECK( controller.get_num_linked_entities() == 1 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == false );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == true );

		controller.remove_entity( ent1 );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
		BOOST_CHECK( controller.is_entity_linked( ent0 ) == false );
		BOOST_CHECK( controller.is_entity_linked( ent1 ) == false );
	}

	// Update entities.
	{
		Entity ent0( 0 );
		ent0.create_property<DummyProperty1>();
		ent0.create_property<DummyProperty0>();

		Entity ent1( 1 );
		ent1.create_property<DummyProperty1>();
		ent1.create_property<DummyProperty0>();

		ExampleController controller;
		controller.add_entity( ent0 );
		controller.add_entity( ent1 );

		controller.run( DELTA_T );

		BOOST_CHECK( controller.m_num_update_calls == 2 );
		BOOST_CHECK( controller.m_entity_ids.find( 0 ) != controller.m_entity_ids.end() );
		BOOST_CHECK( controller.m_entity_ids.find( 1 ) != controller.m_entity_ids.end() );
	}
}
