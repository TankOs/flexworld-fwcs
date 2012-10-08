#include <FWCS/Controllers/Accelerate.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Math.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>

using namespace cs;
using cs::ctrl::Accelerate;

static const float TOLERANCE = 0.0001f;

Entity create_correct_entity() {
	Entity ent;

	ent.create_property( "velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "acceleration", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestAccelerateController ) {
	BOOST_MESSAGE( "Testing accelerate controller..." );

	// Initial state.
	{
		Entity ent = create_correct_entity();
		Accelerate controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Requirements.
	{
		const auto& req = Accelerate::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 2 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "velocity", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ControllerRequirements::PropertyRequirement( "acceleration", typeid( sf::Vector3f ).name(), true ) );
	}

	// Execute without maximum velocity.
	{
		static const sf::Vector3f ACCELERATION = sf::Vector3f( 10.0f, 100.0f, 1000.0f );
		static const sf::Vector3f VELOCITY = sf::Vector3f( 25.0f, 250.0f, 2500.0f );

		Entity ent = create_correct_entity();
		Accelerate controller{ ent };

		sf::Vector3f* velocity = ent.find_property<sf::Vector3f>( "velocity" );
		sf::Vector3f* acceleration = ent.find_property<sf::Vector3f>( "acceleration" );

		*acceleration = ACCELERATION;
		BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );

		controller.execute( sf::milliseconds( 2500 ) );

		BOOST_CHECK( *acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( std::abs( velocity->x - VELOCITY.x ) <= TOLERANCE );
		BOOST_CHECK( std::abs( velocity->y - VELOCITY.y ) <= TOLERANCE );
		BOOST_CHECK( std::abs( velocity->z - VELOCITY.z ) <= TOLERANCE );
	}

	// Execute with maximum velocity.
	{
		static const float MAX_VELOCITY = 100.0f;
		static const sf::Vector3f ACCELERATION = sf::Vector3f( 10.0f, 100.0f, 1000.0f );

		sf::Vector3f VELOCITY = ACCELERATION;
		util::normalize( VELOCITY );
		VELOCITY.x *= MAX_VELOCITY;
		VELOCITY.y *= MAX_VELOCITY;
		VELOCITY.z *= MAX_VELOCITY;

		Entity ent = create_correct_entity();
		ent.create_property( "max_velocity", MAX_VELOCITY );

		Accelerate controller{ ent };

		sf::Vector3f* velocity = ent.find_property<sf::Vector3f>( "velocity" );
		sf::Vector3f* acceleration = ent.find_property<sf::Vector3f>( "acceleration" );
		float* max_velocity = ent.find_property<float>( "max_velocity" );

		*acceleration = ACCELERATION;
		BOOST_CHECK( *velocity == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( *max_velocity == MAX_VELOCITY );

		controller.execute( sf::milliseconds( 2500 ) );

		BOOST_CHECK( *acceleration == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( std::abs( velocity->x - VELOCITY.x ) <= TOLERANCE );
		BOOST_CHECK( std::abs( velocity->y - VELOCITY.y ) <= TOLERANCE );
		BOOST_CHECK( std::abs( velocity->z - VELOCITY.z ) <= TOLERANCE );
	}
}
