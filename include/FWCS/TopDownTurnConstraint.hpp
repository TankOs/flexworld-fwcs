#pragma once

#include <FWCS/Controllers/Turn.hpp>

namespace cs {

/** Top-down turn constraint.
 *
 * Limits rotations to the up axis (y). All other axes are ignored (NOT
 * reset!).
 */
class TopDownTurnConstraint : public ctrl::Turn::Constraint {
	public:
		void update_rotation(
			util::FloatQuaternion& rotation,
			const sf::Vector3f& angular_velocity,
			const sf::Time& sim_time
		);

	private:
};

}
