#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controller.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class DummyController : public cs::Controller {
	public:
		DummyController( cs::Entity& entity ) :
			cs::Controller( entity )
		{
		}

		static const cs::ControllerRequirements& get_requirements() {
			static cs::ControllerRequirements req;
			return req;
		}

		void execute( const sf::Time& ) {
		}
};

class FloatController : public cs::Controller {
	public:
		FloatController( cs::Entity& entity ) :
			cs::Controller( entity ),
			velocity( get_entity().find_property<float>( "velocity" ) )
		{
			BOOST_REQUIRE( velocity != nullptr );
			*velocity = 0.0f;
		}

		~FloatController() {
		}

		static const cs::ControllerRequirements& get_requirements() {
			static cs::ControllerRequirements req = cs::ControllerRequirements().require_property<float>(
				"velocity", true
			);

			return req;
		}

		void execute( const sf::Time& sim_time ) {
			(*velocity) += static_cast<float>( sim_time.asMilliseconds() );
		}

		float* velocity;
};

class IntController : public cs::Controller {
	public:
		IntController( cs::Entity& entity ) :
			cs::Controller( entity ),
			integer( get_entity().find_property<int>( "integer" ) )
		{
			BOOST_REQUIRE( integer != nullptr );
			*integer = 0;
		}

		~IntController() {
		}

		static const cs::ControllerRequirements& get_requirements() {
			static cs::ControllerRequirements req = cs::ControllerRequirements().require_property<int>(
				"integer", true
			);

			return req;
		}

		void execute( const sf::Time& sim_time ) {
			(*integer) += sim_time.asMilliseconds();
		}

		int* integer;
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
		BOOST_CHECK( system.has_factory<FloatController>() == false );
		BOOST_CHECK( system.has_factory<DummyController>() == false );

		system.create_factory<FloatController>();
		BOOST_CHECK( system.get_num_factories() == 1 );
		BOOST_CHECK( system.has_factory<FloatController>() == true );
		BOOST_CHECK( system.has_factory<DummyController>() == false );

		system.create_factory<DummyController>();
		BOOST_CHECK( system.get_num_factories() == 2 );
		BOOST_CHECK( system.has_factory<FloatController>() == true );
		BOOST_CHECK( system.has_factory<DummyController>() == true );
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

	// Create controllers and run simulation.
	{
		// Create entities, then factory.
		{
			System system;

			auto& float_entity = system.create_entity();
			auto& int_entity = system.create_entity();

			float_entity.create_property<float>( "velocity" ) = 100.0f;
			int_entity.create_property<int>( "integer" ) = 50;

			system.create_factory<FloatController>();
			system.create_factory<IntController>();

			BOOST_CHECK( *float_entity.find_property<float>( "velocity" ) == 0.0f );
			BOOST_CHECK( *int_entity.find_property<int>( "integer" ) == 0 );
		}

		// Create factory, then entities.
		{
			System system;

			system.create_factory<FloatController>();
			system.create_factory<IntController>();

			auto& float_entity = system.create_entity();
			auto& int_entity = system.create_entity();

			float_entity.create_property<float>( "velocity", 100.0f );
			int_entity.create_property<int>( "integer", 50 );

			BOOST_CHECK( *float_entity.find_property<float>( "velocity" ) == 0.0f );
			BOOST_CHECK( *int_entity.find_property<int>( "integer" ) == 0 );
		}

		// Run simulation.
		{
			System system;

			auto& float_entity = system.create_entity();
			auto& int_entity = system.create_entity();

			float_entity.create_property<float>( "velocity", 100.0f );
			int_entity.create_property<int>( "integer", 50 );

			system.create_factory<FloatController>();
			system.create_factory<IntController>();

			system.run( sf::milliseconds( 1 ) );
			system.run( sf::milliseconds( 2 ) );
			system.run( sf::milliseconds( 3 ) );

			BOOST_CHECK( *float_entity.find_property<float>( "velocity" ) == 6.0f );
			BOOST_CHECK( *int_entity.find_property<int>( "integer" ) == 6 );
		}
	}
}
