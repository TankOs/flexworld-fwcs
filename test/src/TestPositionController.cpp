#include <FWCS/Controllers/Position.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>

using namespace cs;
using ctrl::Position;

static const float TOLERANCE = 0.0001f;

Entity create_correct_position_entity() {
	Entity ent;

	ent.create_property( "position", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );

	return std::move( ent );
}


BOOST_AUTO_TEST_CASE( TestPositionController ) {
	// Initial state.
	{
		Entity ent = create_correct_position_entity();
		Position controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Requirements.
	{
		Entity ent;
		const auto& req = Position::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 2 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "position", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ControllerRequirements::PropertyRequirement( "velocity", typeid( sf::Vector3f ).name(), true ) );
	}

	// Execute.
	{
		static const sf::Vector3f POSITION = sf::Vector3f( 0.5f, 5.0f, 50.0f );
		static const sf::Vector3f VELOCITY = sf::Vector3f( 1.0f, 10.0f, 100.0f );

		Entity ent = create_correct_position_entity();
		Position controller{ ent };

		auto* position = ent.find_property<sf::Vector3f>( "position" );
		auto* velocity = ent.find_property<sf::Vector3f>( "velocity" );

		BOOST_CHECK( *position == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		*velocity = VELOCITY;

		controller.execute( sf::milliseconds( 500 ) );

		BOOST_CHECK( std::abs( position->x - POSITION.x ) <= TOLERANCE );
		BOOST_CHECK( std::abs( position->y - POSITION.y ) <= TOLERANCE );
		BOOST_CHECK( std::abs( position->z - POSITION.z ) <= TOLERANCE );
		BOOST_CHECK( *velocity == VELOCITY );
	}
}
