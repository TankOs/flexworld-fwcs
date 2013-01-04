#include <FWCS/Controllers/Mouselook.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Math.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

using cs::ctrl::Mouselook;

cs::Entity create_correct_mouselook_entity() {
	cs::Entity ent;

	ent.create_property( "mouselook_control", sf::Vector2f{ 0.0f, 0.0f } );
	ent.create_property( "max_mouselook_angular_velocity", 0.0f );
	ent.create_property( "mouselook_angular_acceleration", 0.0f );
	ent.create_property( "mouselook_angular_deceleration", 0.0f );
	ent.create_property( "angular_velocity", sf::Vector3f{ 0.0f, 0.0f, 0.0f } );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestMouselookController ) {
	BOOST_MESSAGE( "Testing mouselook controller..." );

	// Requirements.
	{
		const auto req = Mouselook::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 5 );
		BOOST_REQUIRE( req.get_property_requirement( 0 ) == cs::ControllerRequirements::PropertyRequirement( "mouselook_control", typeid( sf::Vector2f ).name(), true ) );
		BOOST_REQUIRE( req.get_property_requirement( 1 ) == cs::ControllerRequirements::PropertyRequirement( "max_mouselook_angular_velocity", typeid( float ).name(), true ) );
		BOOST_REQUIRE( req.get_property_requirement( 2 ) == cs::ControllerRequirements::PropertyRequirement( "mouselook_angular_acceleration", typeid( float ).name(), true ) );
		BOOST_REQUIRE( req.get_property_requirement( 3 ) == cs::ControllerRequirements::PropertyRequirement( "mouselook_angular_deceleration", typeid( float ).name(), true ) );
		BOOST_REQUIRE( req.get_property_requirement( 4 ) == cs::ControllerRequirements::PropertyRequirement( "angular_velocity", typeid( sf::Vector3f ).name(), true ) );
	}

	// Initial state.
	{
		cs::Entity ent{ create_correct_mouselook_entity() };
		Mouselook controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Execute.
	{
		// No velocity, no control -> no change.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 2354345.2345f;
			*mouselook_angular_acceleration = 12345.67f;

			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1234945 ) );

			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );
		}

		// Controller normalizes control vector.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );

			sf::Vector2f control{ 123.0f, 456.0f };
			*mouselook_control = control;

			controller.execute( sf::milliseconds( 321123 ) );

			util::normalize( control );
			BOOST_CHECK( *mouselook_control == control );
		}

		// Control x, pure acceleration.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* mouselook_angular_deceleration = ent.find_property<float>( "mouselook_angular_deceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 20.0f;
			*mouselook_angular_acceleration = 10.0f;
			*mouselook_angular_deceleration = 20.0f;

			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };
			*mouselook_control = sf::Vector2f{ 1.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 10.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 20.0f, 0.0f }) );

			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };
			*mouselook_control = sf::Vector2f{ -1.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -10.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -20.0f, 0.0f }) );
		}

		// Control y, pure acceleration.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* mouselook_angular_deceleration = ent.find_property<float>( "mouselook_angular_deceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 20.0f;
			*mouselook_angular_acceleration = 10.0f;
			*mouselook_angular_deceleration = 20.0f;

			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };
			*mouselook_control = sf::Vector2f{ 0.0f, 1.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 10.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 20.0f, 0.0f, 0.0f }) );

			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };
			*mouselook_control = sf::Vector2f{ 0.0f, -1.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -10.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -20.0f, 0.0f, 0.0f }) );
		}

		// Control x, pure deceleration.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* mouselook_angular_deceleration = ent.find_property<float>( "mouselook_angular_deceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 20.0f;
			*mouselook_angular_acceleration = 10.0f;
			*mouselook_angular_deceleration = 20.0f;
			*mouselook_control = sf::Vector2f{ 0.0f, 0.0f };

			*angular_velocity = sf::Vector3f{ 0.0f, 40.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			*angular_velocity = sf::Vector3f{ 0.0f, -40.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );
		}

		// Control y, pure deceleration.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* mouselook_angular_deceleration = ent.find_property<float>( "mouselook_angular_deceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 20.0f;
			*mouselook_angular_acceleration = 10.0f;
			*mouselook_angular_deceleration = 20.0f;
			*mouselook_control = sf::Vector2f{ 0.0f, 0.0f };

			*angular_velocity = sf::Vector3f{ 40.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			*angular_velocity = sf::Vector3f{ -40.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );
		}

		// Control x, deceleration and acceleration.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* mouselook_angular_deceleration = ent.find_property<float>( "mouselook_angular_deceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 20.0f;
			*mouselook_angular_acceleration = 10.0f;
			*mouselook_angular_deceleration = 20.0f;

			*mouselook_control = sf::Vector2f{ 1.0f, 0.0f };
			*angular_velocity = sf::Vector3f{ 0.0f, -40.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 10.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 20.0f, 0.0f }) );

			*mouselook_control = sf::Vector2f{ -1.0f, 0.0f };
			*angular_velocity = sf::Vector3f{ 0.0f, 40.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -10.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -20.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ -1.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, -20.0f, 0.0f }) );
		}

		// Control y, deceleration and acceleration.
		{
			cs::Entity ent{ create_correct_mouselook_entity() };
			Mouselook controller{ ent };

			auto* mouselook_control = ent.find_property<sf::Vector2f>( "mouselook_control" );
			auto* max_mouselook_angular_velocity = ent.find_property<float>( "max_mouselook_angular_velocity" );
			auto* mouselook_angular_acceleration = ent.find_property<float>( "mouselook_angular_acceleration" );
			auto* mouselook_angular_deceleration = ent.find_property<float>( "mouselook_angular_deceleration" );
			auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

			*max_mouselook_angular_velocity = 20.0f;
			*mouselook_angular_acceleration = 10.0f;
			*mouselook_angular_deceleration = 20.0f;

			*mouselook_control = sf::Vector2f{ 0.0f, 1.0f };
			*angular_velocity = sf::Vector3f{ -40.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 10.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, 1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 20.0f, 0.0f, 0.0f }) );

			*mouselook_control = sf::Vector2f{ 0.0f, -1.0f };
			*angular_velocity = sf::Vector3f{ 40.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -10.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -20.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *mouselook_control == (sf::Vector2f{ 0.0f, -1.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -20.0f, 0.0f, 0.0f }) );
		}
	}
}
