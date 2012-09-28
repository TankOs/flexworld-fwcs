#include "ExampleExecutor.hpp"

#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class DummyExecutor : public cs::Executor {
	public:
		DummyExecutor( cs::Entity& entity ) :
			cs::Executor( entity )
		{
		}

		void execute( const sf::Time& ) {
		}
};

class FloatExecutor : public cs::Executor {
	public:
		FloatExecutor( cs::Entity& entity ) :
			cs::Executor( entity ),
			velocity( get_entity().find_property<float>( "velocity" ) ),
			last_velocity( get_entity().find_property<float>( "last_velocity" ) )
		{
			BOOST_REQUIRE( velocity != nullptr );

			if( last_velocity == nullptr ) {
				last_velocity = &get_entity().create_property<float>( "last_velocity" );
			}
		}

		~FloatExecutor() {
		}

		void execute( const sf::Time& sim_time ) {
		}

		float* velocity;
		float* last_velocity;
};

BOOST_AUTO_TEST_CASE( TestSystem ) {
	using namespace cs;

	// Initial state.
	{
		System system;

		BOOST_CHECK( system.get_num_factories() == 0 );
		//BOOST_CHECK( system.get_num_entities() == 0 );
	}

	// Create factories.
	{
		System system;

		BOOST_CHECK( system.get_num_factories() == 0 );
		BOOST_CHECK( system.has_factory<ExampleExecutor>() == false );
		BOOST_CHECK( system.has_factory<DummyExecutor>() == false );

		system.create_factory<ExampleExecutor>();
		BOOST_CHECK( system.get_num_factories() == 1 );
		BOOST_CHECK( system.has_factory<ExampleExecutor>() == true );
		BOOST_CHECK( system.has_factory<DummyExecutor>() == false );

		system.create_factory<DummyExecutor>();
		BOOST_CHECK( system.get_num_factories() == 2 );
		BOOST_CHECK( system.has_factory<ExampleExecutor>() == true );
		BOOST_CHECK( system.has_factory<DummyExecutor>() == true );
	}

	// Add entities. 
	{
		System system;

		auto& ent_one = system.create_entity();

		BOOST_CHECK( ent_one.get_id() == 0 );
		BOOST_CHECK( system.get_num_entities() == 1 );

		// Add another entity.
		auto& ent_two = system.create_entity();

		BOOST_CHECK( ent_two.get_id() == 1 );
		BOOST_CHECK( system.get_num_entities() == 2 );
	}

	// Find entities.
	{
		System system;

		auto& ent_one = system.create_entity();
		ent_one.create_property<float>( "1" ) = 0.0f;

		auto& ent_two = system.create_entity();
		ent_two.create_property<int>( "2" ) = 1;

		auto& ent_three = system.create_entity();
		ent_three.create_property<char>( "3" ) = 'a';

		Entity* ent = nullptr;

		BOOST_REQUIRE( ent = system.find_entity( ent_one.get_id() ) );
		BOOST_CHECK( ent->get_id() == 0 );
		BOOST_REQUIRE( ent->find_property<float>( "1" ) != nullptr );
		BOOST_CHECK( *ent->find_property<float>( "1" ) == 0.0f );

		BOOST_REQUIRE( ent = system.find_entity( ent_two.get_id() ) );
		BOOST_CHECK( ent->get_id() == 1 );
		BOOST_REQUIRE( ent->find_property<int>( "2" ) != nullptr );
		BOOST_CHECK( *ent->find_property<int>( "2" ) == 1 );

		BOOST_REQUIRE( ent = system.find_entity( ent_three.get_id() ) );
		BOOST_CHECK( ent->get_id() == 2 );
		BOOST_REQUIRE( ent->find_property<char>( "3" ) != nullptr );
		BOOST_CHECK( *ent->find_property<char>( "3" ) == 'a' );
	}

	// Remove entities.
	{
		// Remove first.
		{
			System system;

			system.create_entity();
			system.create_entity();
			system.create_entity();

			system.destroy_entity( 0 );

			BOOST_CHECK( system.get_num_entities() == 2 );
			BOOST_CHECK( system.find_entity( 0 ) == nullptr );
			BOOST_CHECK( system.find_entity( 1 ) != nullptr );
			BOOST_CHECK( system.find_entity( 2 ) != nullptr );
		}
		// Remove middle.
		{
			System system;

			system.create_entity();
			system.create_entity();
			system.create_entity();

			system.destroy_entity( 1 );

			BOOST_CHECK( system.get_num_entities() == 2 );
			BOOST_CHECK( system.find_entity( 0 ) != nullptr );
			BOOST_CHECK( system.find_entity( 1 ) == nullptr );
			BOOST_CHECK( system.find_entity( 2 ) != nullptr );
		}
		// Remove last.
		{
			System system;

			system.create_entity();
			system.create_entity();
			system.create_entity();

			system.destroy_entity( 2 );

			BOOST_CHECK( system.get_num_entities() == 2 );
			BOOST_CHECK( system.find_entity( 0 ) != nullptr );
			BOOST_CHECK( system.find_entity( 1 ) != nullptr );
			BOOST_CHECK( system.find_entity( 2 ) == nullptr );
		}
	}

	/*
	// Create executors and run simulation.
	{
		// Create entities, then factory.
		{
			System system;

			auto& float_entity = system.create_entity();
			float_entity.create_property<float>( "velocity" ) = 100.0f;

			system.create_factory<FloatExecutor>();

			BOOST_CHECK( float_entity.find_property<float>( "last_velocity" ) != nullptr );
		}
	}
	*/
}
