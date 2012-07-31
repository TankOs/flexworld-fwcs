#include "DummyProperties.hpp"

#include <FWCS/Entity.hpp>
#include <FWCS/EntityObserver.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Properties/Drag.hpp>

#include <boost/test/unit_test.hpp>

class ExampleEntityObserver : public cs::EntityObserver {
	public:
		ExampleEntityObserver() :
			cs::EntityObserver(),
			m_last_created_property_id( "" ),
			m_num_created_properties( 0 ),
			m_last_entity_id( 0 )
		{
		}

		void on_property_create( cs::Property& property, cs::Entity& entity ) {
			m_last_created_property_id = property.get_id();
			++m_num_created_properties;
			m_last_entity_id = entity.get_id();
		}

		/*
		void on_property_delete( cs::Entity& entity, cs::Property& property ) {
		}
		*/

		std::string m_last_created_property_id;
		std::size_t m_num_created_properties;
		uint32_t m_last_entity_id;
};


BOOST_AUTO_TEST_CASE( TestEntity ) {
	using namespace cs;

	// Initial state.
	{
		Entity ent( 1337 );

		BOOST_CHECK( ent.get_id() == 1337 );
		BOOST_CHECK( ent.get_num_properties() == 0 );
		BOOST_CHECK( ent.has_observer() == false );
	}

	// Create properties.
	{
		Entity ent( 1337 );

		DummyProperty0& dummy_property_0 = ent.create_property<DummyProperty0>();

		BOOST_CHECK( ent.find_property<DummyProperty0>() == &dummy_property_0 );
		BOOST_CHECK( ent.get_num_properties() == 1 );

		DummyProperty1& dummy_property_1 = ent.create_property<DummyProperty1>();

		BOOST_CHECK( ent.find_property<DummyProperty1>() == &dummy_property_1 );
		BOOST_CHECK( ent.get_num_properties() == 2 );
	}

	// Observer.
	{
		Entity ent( 1337 );
		ExampleEntityObserver observer;

		BOOST_CHECK( ent.has_observer() == false );
		ent.set_observer( observer );
		BOOST_REQUIRE( ent.has_observer() == true );
		BOOST_CHECK( &ent.get_observer() == &observer );

		ent.create_property<DummyProperty0>();

		BOOST_CHECK( observer.m_last_created_property_id == "DummyProperty0" );
		BOOST_CHECK( observer.m_num_created_properties == 1 );
		BOOST_CHECK( observer.m_last_entity_id == 1337 );
	}
}
