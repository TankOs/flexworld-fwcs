#include <FWCS/Controllers/Walk.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>

using namespace cs;
using ctrl::Walk;

static const float TOLERANCE = 0.001f;

Entity create_correct_walk_entity() {
	Entity ent;

	ent.create_property<float>( "walk_forward_control", 0.0f );
	ent.create_property<float>( "walk_strafe_control", 0.0f );
	ent.create_property<float>( "walk_acceleration", 0.0f );
	ent.create_property<float>( "walk_max_velocity", 0.0f );

	ent.create_property<sf::Vector3f>( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property<sf::Vector3f>( "acceleration", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property<sf::Vector3f>( "forward", sf::Vector3f( 1.0f, 0.0f, 0.0f ) );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestWalkController ) {
	BOOST_MESSAGE( "Testing walk controller..." );

	// Initial state.
	{
		Entity ent = create_correct_walk_entity();
		Walk controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Requirements.
	{
		const auto& req = Walk::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 7 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "walk_acceleration", typeid( float ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ControllerRequirements::PropertyRequirement( "walk_max_velocity", typeid( float ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 2 ) == ControllerRequirements::PropertyRequirement( "walk_forward_control", typeid( float ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 3 ) == ControllerRequirements::PropertyRequirement( "walk_strafe_control", typeid( float ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 4 ) == ControllerRequirements::PropertyRequirement( "forward", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 5 ) == ControllerRequirements::PropertyRequirement( "acceleration", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 6 ) == ControllerRequirements::PropertyRequirement( "velocity", typeid( sf::Vector3f ).name(), true ) );
	}

	// Execute.
	{
		// Stand still.
		{
			Entity ent = create_correct_walk_entity();
			Walk controller{ ent };

			auto* walk_forward_control = ent.find_property<float>( "walk_forward_control" );
			auto* walk_strafe_control = ent.find_property<float>( "walk_strafe_control" );
			auto* walk_acceleration = ent.find_property<float>( "walk_acceleration" );
			auto* walk_max_velocity = ent.find_property<float>( "walk_max_velocity" );
			auto* acceleration = ent.find_property<sf::Vector3f>( "acceleration" );
			auto* velocity = ent.find_property<sf::Vector3f>( "acceleration" );

			*walk_acceleration = 12345.0f;
			*walk_max_velocity = 54321.0f;
			BOOST_CHECK( *walk_forward_control == 0.0f );
			BOOST_CHECK( *walk_strafe_control == 0.0f );

			controller.execute( sf::milliseconds( 10000 ) );

			BOOST_CHECK( *acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		}

		// Walk forward/backward.
		{
			Entity ent = create_correct_walk_entity();
			Walk controller{ ent };

			auto* walk_forward_control = ent.find_property<float>( "walk_forward_control" );
			auto* walk_strafe_control = ent.find_property<float>( "walk_strafe_control" );
			auto* walk_acceleration = ent.find_property<float>( "walk_acceleration" );
			auto* walk_max_velocity = ent.find_property<float>( "walk_max_velocity" );
			auto* forward = ent.find_property<sf::Vector3f>( "forward" );
			auto* acceleration = ent.find_property<sf::Vector3f>( "acceleration" );
			auto* velocity = ent.find_property<sf::Vector3f>( "velocity" );

			// Accelerate.
			{
				*walk_acceleration = 5.0f;
				*walk_max_velocity = 10.0f;
				*walk_forward_control = 1.0f;
				*walk_strafe_control = 0.0f;
				*forward = sf::Vector3f( 1.0f, 0.0f, 0.0f );
				*acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
				*velocity = sf::Vector3f( 0.0f, 0.0f, 0.0f );

				// Keep in mind we are simulating for 5 seconds here!
				controller.execute( sf::milliseconds( 5000 ) );

				BOOST_CHECK( std::abs( acceleration->x - 2.0f ) <= TOLERANCE );
				BOOST_CHECK( acceleration->y == 0.0f );
				BOOST_CHECK( acceleration->z == 0.0f );
				BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			}

			// Accelerate, half forward command.
			{
				*walk_acceleration = 100.0f;
				*walk_max_velocity = 10.0f;
				*walk_forward_control = 0.5f;
				*walk_strafe_control = 0.0f;
				*forward = sf::Vector3f( 1.0f, 0.0f, 0.0f );
				*acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
				*velocity = sf::Vector3f( 0.0f, 0.0f, 0.0f );

				controller.execute( sf::milliseconds( 1000 ) );

				BOOST_CHECK( std::abs( acceleration->x - 5.0f ) <= TOLERANCE );
				BOOST_CHECK( acceleration->y == 0.0f );
				BOOST_CHECK( acceleration->z == 0.0f );
				BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			}

			// Accelerate, half strafe command.
			{
				*walk_acceleration = 100.0f;
				*walk_max_velocity = 10.0f;
				*walk_forward_control = 0.0f;
				*walk_strafe_control = 0.5f;
				*forward = sf::Vector3f( 1.0f, 0.0f, 0.0f );
				*acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
				*velocity = sf::Vector3f( 0.0f, 0.0f, 0.0f );

				controller.execute( sf::milliseconds( 1000 ) );

				BOOST_CHECK( std::abs( acceleration->x ) <= TOLERANCE );
				BOOST_CHECK( acceleration->y == 0.0f );
				BOOST_CHECK( std::abs( acceleration->z - 5.0f ) <= TOLERANCE );
				BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			}

			// Slowdown.
			{
				*walk_acceleration = 20.0f;
				*walk_max_velocity = 10.0f;
				*walk_forward_control = 0.0f;
				*walk_strafe_control = 0.0f;
				*forward = sf::Vector3f( 1.0f, 0.0f, 0.0f );
				*acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
				*velocity = sf::Vector3f( 10.0f, 0.0f, 0.0f );

				controller.execute( sf::milliseconds( 500 ) );

				BOOST_CHECK( std::abs( acceleration->x + 20.0f ) <= TOLERANCE );
				BOOST_CHECK( acceleration->y == 0.0f );
				BOOST_CHECK( acceleration->z == 0.0f );
				BOOST_CHECK( *velocity == sf::Vector3f( 10.0f, 0.0f, 0.0f ) );
			}

			// Strafe.
			{
				*walk_acceleration = 5.0f;
				*walk_max_velocity = 10.0f;
				*walk_forward_control = 0.0f;
				*walk_strafe_control = 1.0f;
				*forward = sf::Vector3f( 1.0f, 0.0f, 0.0f );
				*acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
				*velocity = sf::Vector3f( 0.0f, 0.0f, 0.0f );

				controller.execute( sf::milliseconds( 2000 ) );

				BOOST_CHECK( std::abs( acceleration->x ) <= TOLERANCE );
				BOOST_CHECK( std::abs( acceleration->y ) <= TOLERANCE );
				BOOST_CHECK( std::abs( acceleration->z - 5.0f ) <= TOLERANCE );
				BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			}
		}
	}
}
