#include <FWCS/TopDownTurnConstraint.hpp>

#include <FWU/Axis.hpp>
#include <SFML/System/Time.hpp>

namespace cs {

void TopDownTurnConstraint::update_rotation(
	util::FloatQuaternion& rotation,
	const sf::Vector3f& angular_velocity,
	const sf::Time& sim_time
) {
	util::FloatQuaternion rot_q = util::FloatQuaternion::from_angle_axis(
		angular_velocity.y * sim_time.asSeconds(),
		util::axis::y
	);

	rotation = rot_q * rotation;
}

}
