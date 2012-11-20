#include <FWCS/TopDownTurnConstraint.hpp>

#include <FWU/Math.hpp>
#include <FWU/Axis.hpp>
#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

using cs::TopDownTurnConstraint;

BOOST_AUTO_TEST_CASE( TestTopDownTurnConstraint ) {
	BOOST_MESSAGE( "Testing top-down turn constraint..." );

	// Update rotation.
	{
		TopDownTurnConstraint constraint;

		util::FloatQuaternion rotation;
		sf::Vector3f angular_velocity{ util::deg_to_rad( 5.0f ), util::deg_to_rad( 10.0f ), util::deg_to_rad( 15.0f ) };

		constraint.update_rotation( rotation, angular_velocity, sf::milliseconds( 3000 ) );

		BOOST_CHECK(
			rotation == util::FloatQuaternion::from_angle_axis(
				util::deg_to_rad( 10.0f ) * 3.0f,
				sf::Vector3f( 0.0f, 1.0f, 0.0f )
			)
		);
	}

	// Update rotation, ignoring axes except y.
	{
		TopDownTurnConstraint constraint;

		util::FloatQuaternion source_rotation;
		source_rotation *= util::FloatQuaternion::from_angle_axis( util::deg_to_rad( 20.0f ), util::axis::x );
		source_rotation *= util::FloatQuaternion::from_angle_axis( util::deg_to_rad( 40.0f ), util::axis::z );

		util::FloatQuaternion rotation = source_rotation;
		sf::Vector3f angular_velocity{ util::deg_to_rad( 5.0f ), util::deg_to_rad( 10.0f ), util::deg_to_rad( 15.0f ) };

		constraint.update_rotation( rotation, angular_velocity, sf::milliseconds( 3000 ) );

		BOOST_CHECK(
			rotation == (
				util::FloatQuaternion::from_angle_axis(
					util::deg_to_rad( 10.0f ) * 3.0f,
					sf::Vector3f( 0.0f, 1.0f, 0.0f )
				) *
				source_rotation
			)
		);
	}
}
