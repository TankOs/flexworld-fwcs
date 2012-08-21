#include <FWCS/Entity.hpp>
#include <FWCS/EntityObserver.hpp>

#include <SFML/System/Vector3.hpp>
#include <boost/test/unit_test.hpp>

class ExampleEntityObserver : public cs::EntityObserver {
	public:
		ExampleEntityObserver() :
			cs::EntityObserver(),
			m_last_created_property_id( "" ),
			m_num_created_properties( 0 ),
			m_last_entity( nullptr )
		{
		}

		void on_property_create( const std::string& id, cs::Entity& entity ) {
			m_last_created_property_id = id;
			++m_num_created_properties;
			m_last_entity = &entity;
		}

		std::string m_last_created_property_id;
		std::size_t m_num_created_properties;
		cs::Entity* m_last_entity;
};

BOOST_AUTO_TEST_CASE( TestEntity ) {
	using namespace cs;

	// Initial state.
	{
		Entity ent;

		BOOST_CHECK( ent.get_num_properties() == 0 );
		BOOST_CHECK( ent.has_observer() == false );
	}

	// Create properties (with initial values).
	{
		Entity ent;

		ConcreteProperty<int32_t>& init_int_property = ent.create_property<int32_t>( "int", 1 );
		ConcreteProperty<float>& init_float_property = ent.create_property<float>( "float", 2.0f );
		ConcreteProperty<std::string>& init_string_property = ent.create_property<std::string>( "string", "3" );
		ConcreteProperty<sf::Vector3f>& init_vec3_property = ent.create_property<sf::Vector3f>( "vec3", sf::Vector3f( 4, 5, 6 ) );

		BOOST_CHECK( ent.get_num_properties() == 4 );

		ConcreteProperty<int32_t>* int_property = ent.find_property<int32_t>( "int" );
		ConcreteProperty<float>* float_property = ent.find_property<float>( "float" );
		ConcreteProperty<std::string>* string_property = ent.find_property<std::string>( "string" );
		ConcreteProperty<sf::Vector3f>* vec3_property = ent.find_property<sf::Vector3f>( "vec3" );

		BOOST_CHECK( int_property != nullptr );
		BOOST_CHECK( float_property != nullptr );
		BOOST_CHECK( string_property != nullptr );
		BOOST_CHECK( vec3_property != nullptr );

		BOOST_CHECK( &init_int_property == int_property );
		BOOST_CHECK( &init_float_property == float_property );
		BOOST_CHECK( &init_string_property == string_property );
		BOOST_CHECK( &init_vec3_property == vec3_property );

		BOOST_CHECK( &init_int_property == ent.find_base_property( "int" ) );
		BOOST_CHECK( &init_float_property == ent.find_base_property( "float" ) );
		BOOST_CHECK( &init_string_property == ent.find_base_property( "string" ) );
		BOOST_CHECK( &init_vec3_property == ent.find_base_property( "vec3" ) );

		if( int_property != nullptr ) {
			BOOST_CHECK( int_property->get_value() == 1 );
		}
		if( float_property != nullptr ) {
			BOOST_CHECK( float_property->get_value() == 2.0f );
		}
		if( string_property != nullptr ) {
			BOOST_CHECK( string_property->get_value() == "3" );
		}
		if( vec3_property != nullptr ) {
			BOOST_CHECK( vec3_property->get_value() == sf::Vector3f( 4, 5, 6 ) );
		}
	}

	// Observer.
	{
		Entity ent;
		ExampleEntityObserver observer;

		BOOST_CHECK( ent.has_observer() == false );
		ent.set_observer( observer );
		BOOST_REQUIRE( ent.has_observer() == true );
		BOOST_CHECK( &ent.get_observer() == &observer );

		ent.create_property<float>( "foobar" );
		ent.create_property<float>( "foobar2" );

		BOOST_CHECK( observer.m_last_created_property_id == "foobar2" );
		BOOST_CHECK( observer.m_num_created_properties == 2 );
		BOOST_CHECK( observer.m_last_entity == &ent );
	}
}
