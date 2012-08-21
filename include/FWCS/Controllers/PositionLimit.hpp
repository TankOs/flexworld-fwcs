#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Position limit controller.
 * Clamps an object's position to a lower and upper boundary.
 *
 * When a boundary is exceeded, the position will be clamped and velocity
 * reset.
 *
 * Properties needed:
 *   * position (sf::Vector3f): Current position
 *   * velocity (sf::Vector3f): Velocity
 *   * lower_position_limit (sf::Vector3f): Lower position limit
 *   * upper_position_limit (sf::Vector3f): Upper position limit
 */
class PositionLimit : public Controller {
	public:
		/** Ctor.
		 */
		PositionLimit();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
