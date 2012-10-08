#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Math.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

#include <cmath>

using namespace cs;
using ctrl::Turn;

static const float TOLERANCE = 0.001f;

Entity create_correct_turn_entity() {
	Entity ent;

	ent.create_property<sf::Vector3f>( "turn_acceleration", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property<sf::Vector3f>( "turn_velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property<sf::Vector3f>( "rotation", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestTurnController ) {
	BOOST_MESSAGE( "RE-ENABLE TURN CONTROLLER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	BOOST_MESSAGE( "RE-ENABLE TURN CONTROLLER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	BOOST_MESSAGE( "RE-ENABLE TURN CONTROLLER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	BOOST_MESSAGE( "RE-ENABLE TURN CONTROLLER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	BOOST_MESSAGE( "RE-ENABLE TURN CONTROLLER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	BOOST_MESSAGE( "RE-ENABLE TURN CONTROLLER TEST!!!!!!!!!!!!!!!!!!!!!!!!!!" );
}

/*
BOOST_AUTO_TEST_CASE( TestTurnController ) {
	BOOST_MESSAGE( "Testing turn controller..." );

	// Requirements.
	{
		const auto& req = Turn::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 3 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "turn_acceleration", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ControllerRequirements::PropertyRequirement( "turn_velocity", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 2 ) == ControllerRequirements::PropertyRequirement( "rotation", typeid( sf::Vector3f ).name(), true ) );
	}

	// Initial state.
	{
		Entity ent = create_correct_turn_entity();
		Turn controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Execute.
	{
		Entity ent = create_correct_turn_entity();

		auto& turn_acceleration = *ent.find_property<sf::Vector3f>( "turn_acceleration" );
		auto& turn_velocity = *ent.find_property<sf::Vector3f>( "turn_velocity" );
		auto& rotation = *ent.find_property<sf::Vector3f>( "rotation" );

		turn_acceleration = sf::Vector3f( 1.0f, 2.0f, 3.0f );
		turn_velocity = sf::Vector3f( 10.0f, 20.0f, 30.0f );
		rotation = sf::Vector3f( 0.0f, 0.0f, 0.0f );

		Turn controller{ ent };

		controller.execute( sf::milliseconds( 500 ) );

		BOOST_CHECK( turn_acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( std::abs( turn_velocity.x - 10.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.y - 21.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( turn_velocity.z - 31.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation.x - 5.25f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation.y - 10.5f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation.z - 15.75f ) <= TOLERANCE );

		// Check forward vector with simple values.
		turn_acceleration = sf::Vector3f( 0.0f, 0.0f, 0.0f );
		turn_velocity = sf::Vector3f( 90.0f, 0.0f, 0.0f );
		rotation = sf::Vector3f( 0.0f, 0.0f, 0.0f );

		controller.execute( sf::milliseconds( 1000 ) );

		BOOST_CHECK( std::abs( rotation.x - 90.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation.y - 0.0f ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation.z - 0.0f ) <= TOLERANCE );
	}
}
*/
