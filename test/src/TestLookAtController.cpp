#include <FWCS/Controllers/LookAt.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Math.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

using cs::ctrl::LookAt;

static const float TOLERANCE = 0.0001f;

cs::Entity create_correct_look_at_entity() {
	cs::Entity ent;

	ent.create_property( "position", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "forward_vector", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "up_vector", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "angular_velocity", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "look_at_position", sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	ent.create_property( "look_at_acceleration", 0.0f );
	ent.create_property( "max_look_at_velocity", 0.0f );

	return std::move( ent );
}

BOOST_AUTO_TEST_CASE( TestLookAtController ) {
	BOOST_MESSAGE( "Testing look at controller..." );

	// Initial state.
	{
		cs::Entity ent = create_correct_look_at_entity();
		LookAt controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Requirements.
	{
		const auto req = LookAt::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 7 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == cs::ControllerRequirements::PropertyRequirement( "position", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == cs::ControllerRequirements::PropertyRequirement( "forward_vector", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 2 ) == cs::ControllerRequirements::PropertyRequirement( "up_vector", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 3 ) == cs::ControllerRequirements::PropertyRequirement( "angular_velocity", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 4 ) == cs::ControllerRequirements::PropertyRequirement( "look_at_position", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 5 ) == cs::ControllerRequirements::PropertyRequirement( "look_at_acceleration", typeid( float ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 6 ) == cs::ControllerRequirements::PropertyRequirement( "max_look_at_velocity", typeid( float ).name(), true ) );
	}

	// Execute.
	{
		cs::Entity ent = create_correct_look_at_entity();
		LookAt controller{ ent };

		auto* position = ent.find_property<sf::Vector3f>( "position" );
		auto* forward_vector = ent.find_property<sf::Vector3f>( "forward_vector" );
		auto* up_vector = ent.find_property<sf::Vector3f>( "up_vector" );
		auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );
		auto* look_at_position = ent.find_property<sf::Vector3f>( "look_at_position" );
		auto* look_at_acceleration = ent.find_property<float>( "look_at_acceleration" );
		auto* max_look_at_velocity = ent.find_property<float>( "max_look_at_velocity" );

		// Rotate in 2 steps.
		{
			*position = sf::Vector3f{ 0.0f, 0.0f, 0.0f };
			*forward_vector = sf::Vector3f{ 1.0f, 0.0f, 0.0f };
			*up_vector = sf::Vector3f{ 0.0f, 1.0f, 0.0f };
			*angular_velocity = sf::Vector3f{ 0.0f, 0.0f, 0.0f };
			*look_at_position = sf::Vector3f{ 0.0f, 0.0f, 1.0f };
			*look_at_acceleration = util::deg_to_rad( 45.0f );
			*max_look_at_velocity = util::deg_to_rad( 90.0f );

			controller.execute( sf::milliseconds( 1000 ) );

			BOOST_CHECK( *position == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *forward_vector == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *up_vector == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
			BOOST_CHECK( *look_at_position == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
			BOOST_CHECK( *look_at_acceleration = util::deg_to_rad( 45.0f ) );
			BOOST_CHECK( *max_look_at_velocity = util::deg_to_rad( 90.0f ) );

			BOOST_CHECK( std::abs( angular_velocity->x - util::deg_to_rad( 0.0f ) ) <= TOLERANCE );
			BOOST_CHECK( std::abs( angular_velocity->y - util::deg_to_rad( -45.0f ) ) <= TOLERANCE );
			BOOST_CHECK( std::abs( angular_velocity->z - util::deg_to_rad( 0.0f ) ) <= TOLERANCE );

			controller.execute( sf::milliseconds( 1000 ) );

			BOOST_CHECK( *position == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *forward_vector == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *up_vector == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
			BOOST_CHECK( *look_at_position == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
			BOOST_CHECK( *look_at_acceleration = util::deg_to_rad( 45.0f ) );
			BOOST_CHECK( *max_look_at_velocity = util::deg_to_rad( 90.0f ) );

			BOOST_CHECK( std::abs( angular_velocity->x - util::deg_to_rad( 0.0f ) ) <= TOLERANCE );
			BOOST_CHECK( std::abs( angular_velocity->y - util::deg_to_rad( -90.0f ) ) <= TOLERANCE );
			BOOST_CHECK( std::abs( angular_velocity->z - util::deg_to_rad( 0.0f ) ) <= TOLERANCE );

			controller.execute( sf::milliseconds( 1000 ) );

			BOOST_CHECK( *position == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *forward_vector == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
			BOOST_CHECK( *up_vector == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );
			BOOST_CHECK( *look_at_position == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
			BOOST_CHECK( *look_at_acceleration = util::deg_to_rad( 45.0f ) );
			BOOST_CHECK( *max_look_at_velocity = util::deg_to_rad( 90.0f ) );

			BOOST_CHECK( std::abs( angular_velocity->x - util::deg_to_rad( 0.0f ) ) <= TOLERANCE );
			BOOST_CHECK( std::abs( angular_velocity->y - util::deg_to_rad( -90.0f ) ) <= TOLERANCE );
			BOOST_CHECK( std::abs( angular_velocity->z - util::deg_to_rad( 0.0f ) ) <= TOLERANCE );
		}
	}
}
