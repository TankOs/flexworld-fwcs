#include <FWCS/FirstPersonTurnConstraint.hpp>

#include <FWU/Math.hpp>
#include <FWU/Axis.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

using cs::FirstPersonTurnConstraint;

BOOST_AUTO_TEST_CASE( TestFirstPersonTurnConstraint ) {
	BOOST_MESSAGE( "Testing first person turn constraint..." );

	// Update rotation.
	{
		FirstPersonTurnConstraint constraint;

		util::FloatQuaternion rotation;
		util::FloatQuaternion expected_rotation;
		sf::Vector3f angular_velocity{ util::deg_to_rad( 5.0f ), util::deg_to_rad( 10.0f ), util::deg_to_rad( 15.0f ) };

		constraint.update_rotation( rotation, angular_velocity, sf::milliseconds( 3000 ) );

		expected_rotation =
			util::FloatQuaternion::from_angle_axis( util::deg_to_rad( 10.0f ) * 3.0f, util::axis::y ) *
			util::FloatQuaternion::from_angle_axis( util::deg_to_rad( 5.0f ) * 3.0f, util::axis::x )
		;

		BOOST_CHECK( rotation == expected_rotation );

		constraint.update_rotation( rotation, angular_velocity, sf::milliseconds( 3000 ) );

		expected_rotation =
			util::FloatQuaternion::from_angle_axis( util::deg_to_rad( 10.0f ) * 3.0f, util::axis::y ) *
			expected_rotation *
			util::FloatQuaternion::from_angle_axis( util::deg_to_rad( 5.0f ) * 3.0f, util::axis::x )
		;

		BOOST_CHECK( rotation == expected_rotation );
	}
}
