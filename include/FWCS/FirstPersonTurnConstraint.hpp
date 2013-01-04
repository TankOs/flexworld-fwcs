#pragma once

#include <FWCS/Controllers/Turn.hpp>

namespace cs {

/** First person turn constraint.
 *
 * Limits rotations to the up (y) and right (x) axes. Useful for first person
 * cameras.
 */
class FirstPersonTurnConstraint : public ctrl::Turn::Constraint {
	public:
		void update_rotation(
			util::FloatQuaternion& rotation,
			const sf::Vector3f& angular_velocity,
			const sf::Time& sim_time
		);

	private:
};

}
