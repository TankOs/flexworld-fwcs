#include <FWCS/Controllers/Mouselook.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

using cs::ctrl::Mouselook;

cs::Entity create_correct_mouselook_entity() {
	cs::Entity ent;

	ent.create_property<sf::Vector2f>( "mlook_delta", sf::Vector2f{ 0.0f, 0.0f } );
	ent.create_property<float>( "mlook_angular_acceleration", 0.0f );
	ent.create_property<sf::Vector3f>( "angular_velocity", sf::Vector3f{ 0.0f, 0.0f, 0.0f } );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestMouselookController ) {
	BOOST_MESSAGE( "Testing mouselook controller..." );

	// Requirements.
	{
		const auto req = Mouselook::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 3 );
		BOOST_REQUIRE( req.get_property_requirement( 0 ) == cs::ControllerRequirements::PropertyRequirement( "mlook_delta", typeid( sf::Vector2f ).name(), true ) );
		BOOST_REQUIRE( req.get_property_requirement( 1 ) == cs::ControllerRequirements::PropertyRequirement( "mlook_angular_acceleration", typeid( float ).name(), true ) );
		BOOST_REQUIRE( req.get_property_requirement( 2 ) == cs::ControllerRequirements::PropertyRequirement( "angular_velocity", typeid( sf::Vector3f ).name(), true ) );
	}

	// Initial state.
	{
		cs::Entity ent{ create_correct_mouselook_entity() };
		Mouselook controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Execute.
	{
		cs::Entity ent{ create_correct_mouselook_entity() };
		Mouselook controller{ ent };

		auto* mlook_delta = ent.find_property<sf::Vector2f>( "mlook_delta" );
		auto* mlook_angular_acceleration = ent.find_property<float>( "mlook_angular_acceleration" );
		auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

		// No delta, no change.
		{
			*mlook_angular_acceleration = 12345.67f;

			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1234945 ) );

			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 0.0f }) );
		}

		// Delta reset.
		{
			*mlook_delta = sf::Vector2f{ 12.0f, 34.0f };

			controller.execute( sf::milliseconds( 1234945 ) );

			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );
		}

		// Accelerate.
		{
			*mlook_delta = sf::Vector2f{ 1.0f, 0.5f };
			*mlook_angular_acceleration = 50.0f;
			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 500 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 12.5f, 25.0f, 0.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );
		}

		// Accelerate, clamp deltas.
		{
			*mlook_delta = sf::Vector2f{ 500.0f, 1000.0f };
			*mlook_angular_acceleration = 10.0f;
			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 10.0f, 10.0f, 0.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );

			// Negative delta.
			*mlook_delta = sf::Vector2f{ -500.0f, -1000.0f };
			*mlook_angular_acceleration = 10.0f;
			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -10.0f, -10.0f, 0.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );
		}

		// Brake.
		{
			*mlook_delta = sf::Vector2f{ 0.0f, 0.0f };
			*mlook_angular_acceleration = 10.0f;
			*angular_velocity = sf::Vector3f{ 20.0f, 20.0f, 20.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 10.0f, 10.0f, 20.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 20.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 20.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );

			*mlook_delta = sf::Vector2f{ 0.0f, 0.0f };
			*mlook_angular_acceleration = 10.0f;
			*angular_velocity = sf::Vector3f{ -20.0f, -20.0f, 20.0f };

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ -10.0f, -10.0f, 20.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 20.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );

			controller.execute( sf::milliseconds( 1000 ) );
			BOOST_CHECK( *angular_velocity == (sf::Vector3f{ 0.0f, 0.0f, 20.0f }) );
			BOOST_CHECK( *mlook_delta == (sf::Vector2f{ 0.0f, 0.0f }) );
		}
	}
}
