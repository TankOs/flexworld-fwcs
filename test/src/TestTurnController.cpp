#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Math.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

#include <cmath>

using namespace cs;
using ctrl::Turn;

static const float TOLERANCE = 0.001f;

Entity create_correct_turn_entity() {
	Entity ent;

	ent.create_property<sf::Vector3f>( "turn_acceleration", sf::Vector3f() );
	ent.create_property<sf::Vector3f>( "turn_velocity", sf::Vector3f() );
	ent.create_property<sf::Vector3f>( "forward", sf::Vector3f( 0.0f, 0.0f, 1.0f ) );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestTurnController ) {
	BOOST_MESSAGE( "Testing turn controller..." );

	// Requirements.
	{
		const auto& req = Turn::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 3 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "turn_acceleration", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ControllerRequirements::PropertyRequirement( "turn_velocity", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 2 ) == ControllerRequirements::PropertyRequirement( "forward", typeid( sf::Vector3f ).name(), true ) );
	}

	// Initial state.
	{
		Entity ent = create_correct_turn_entity();
		Turn controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Execute, no rotation. Results in const forward vector.
	{
		Entity ent = create_correct_turn_entity();

		auto& turn_acceleration = *ent.find_property<sf::Vector3f>( "turn_acceleration" );
		auto& turn_velocity = *ent.find_property<sf::Vector3f>( "turn_velocity" );
		auto& forward = *ent.find_property<sf::Vector3f>( "forward" );

		turn_acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
		turn_velocity = sf::Vector3f( 0.0f, 0.0f, 0.0f );
		forward = sf::Vector3f( 0.0f, 0.0f, 1.0f );

		Turn controller{ ent };

		controller.execute( sf::milliseconds( 500 ) );

		BOOST_CHECK( turn_acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( turn_velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( forward == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
	}

	// Accelerate.
	{
		static const auto ACCELERATION = sf::Vector3f( 1.0f, 2.0f, 3.0f );

		Entity ent = create_correct_turn_entity();

		auto& turn_acceleration = *ent.find_property<sf::Vector3f>( "turn_acceleration" );
		auto& turn_velocity = *ent.find_property<sf::Vector3f>( "turn_velocity" );

		turn_acceleration = ACCELERATION;
		turn_velocity = sf::Vector3f( 0.0f, 0.0f, 0.0f );

		Turn controller{ ent };

		controller.execute( sf::seconds( 0.5f ) );

		BOOST_CHECK( turn_acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) ); // Is reset.
		BOOST_CHECK( std::abs( turn_velocity.x - 1.0f * 0.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.y - 2.0f * 0.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.z - 3.0f * 0.5f ) <= TOLERANCE );

		// No accel, keep velocity.
		controller.execute( sf::seconds( 0.5f ) );

		BOOST_CHECK( turn_acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) ); // Is reset.
		BOOST_CHECK( std::abs( turn_velocity.x - 1.0f * 0.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.y - 2.0f * 0.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.z - 3.0f * 0.5f ) <= TOLERANCE );

		// Accelerate again a bit, accumulate velocities.
		turn_acceleration = ACCELERATION;
		controller.execute( sf::seconds( 1.5f ) );

		BOOST_CHECK( turn_acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) ); // Is reset.
		BOOST_CHECK( std::abs( turn_velocity.x - 1.0f * 2.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.y - 2.0f * 2.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.z - 3.0f * 2.0f ) <= TOLERANCE );
	}

	// Rotate forward vector.
	{
		// Y axis.
		{
			static const auto VELOCITY = sf::Vector3f( 0.0f, util::deg_to_rad( 90.0f ), 0.0f );
			static const auto FORWARD = sf::Vector3f( 1.0f, 0.0f, 0.0f );

			Entity ent = create_correct_turn_entity();

			auto& turn_acceleration = *ent.find_property<sf::Vector3f>( "turn_acceleration" );
			auto& turn_velocity = *ent.find_property<sf::Vector3f>( "turn_velocity" );
			auto& forward = *ent.find_property<sf::Vector3f>( "forward" );

			turn_acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
			turn_velocity = VELOCITY;
			forward = FORWARD;

			Turn controller{ ent };
			controller.execute( sf::seconds( 1.0f ) );

			BOOST_CHECK( std::abs( turn_velocity.x - VELOCITY.x ) <= TOLERANCE );
			BOOST_CHECK( std::abs( turn_velocity.y - VELOCITY.y ) <= TOLERANCE );
			BOOST_CHECK( std::abs( turn_velocity.z - VELOCITY.z ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.x - 0.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.y - 0.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.z - -1.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( util::calc_length( forward ) - 1.0f ) <= TOLERANCE );
		}

		// Z axis.
		{
			static const auto VELOCITY = sf::Vector3f( 0.0f, 0.0f, util::deg_to_rad( 90.0f ) );
			static const auto FORWARD = sf::Vector3f( 0.0f, 1.0f, 0.0f );

			Entity ent = create_correct_turn_entity();

			auto& turn_acceleration = *ent.find_property<sf::Vector3f>( "turn_acceleration" );
			auto& turn_velocity = *ent.find_property<sf::Vector3f>( "turn_velocity" );
			auto& forward = *ent.find_property<sf::Vector3f>( "forward" );

			turn_acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
			turn_velocity = VELOCITY;
			forward = FORWARD;

			Turn controller{ ent };
			controller.execute( sf::seconds( 1.0f ) );

			BOOST_CHECK( std::abs( turn_velocity.x - VELOCITY.x ) <= TOLERANCE );
			BOOST_CHECK( std::abs( turn_velocity.y - VELOCITY.y ) <= TOLERANCE );
			BOOST_CHECK( std::abs( turn_velocity.z - VELOCITY.z ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.x - -1.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.y - 0.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.z - 0.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( util::calc_length( forward ) - 1.0f ) <= TOLERANCE );
		}

		// X axis.
		{
			static const auto VELOCITY = sf::Vector3f( util::deg_to_rad( 90.0f ), 0.0f, 0.0f );
			static const auto FORWARD = sf::Vector3f( 0.0f, 0.0f, 1.0f );

			Entity ent = create_correct_turn_entity();

			auto& turn_acceleration = *ent.find_property<sf::Vector3f>( "turn_acceleration" );
			auto& turn_velocity = *ent.find_property<sf::Vector3f>( "turn_velocity" );
			auto& forward = *ent.find_property<sf::Vector3f>( "forward" );

			turn_acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
			turn_velocity = VELOCITY;
			forward = FORWARD;

			Turn controller{ ent };
			controller.execute( sf::seconds( 1.0f ) );

			BOOST_CHECK( std::abs( turn_velocity.x - VELOCITY.x ) <= TOLERANCE );
			BOOST_CHECK( std::abs( turn_velocity.y - VELOCITY.y ) <= TOLERANCE );
			BOOST_CHECK( std::abs( turn_velocity.z - VELOCITY.z ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.x - 0.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.y - -1.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( forward.z - 0.0f ) <= TOLERANCE );
			BOOST_CHECK( std::abs( util::calc_length( forward ) - 1.0f ) <= TOLERANCE );
		}
	}
}
