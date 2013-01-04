#include <FWCS/FirstPersonTurnConstraint.hpp>

#include <FWU/Axis.hpp>
#include <SFML/System/Time.hpp>

namespace cs {

void FirstPersonTurnConstraint::update_rotation(
	util::FloatQuaternion& rotation,
	const sf::Vector3f& angular_velocity,
	const sf::Time& sim_time
) {
	float sim_seconds = sim_time.asSeconds();

	rotation =
		util::FloatQuaternion::from_angle_axis( angular_velocity.y * sim_seconds, util::axis::y ) *
		rotation *
		util::FloatQuaternion::from_angle_axis( angular_velocity.x * sim_seconds, util::axis::x )
	;
}

}
