#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Movement controller.
 * Applies velocity to position, dependent on time.
 *
 * Properties needed:
 *   * position (sf::Vector3f): Position that's being changed
 *   * velocity (sf::Vector3f, in m/s): Velocity
 */
class Movement : public Controller {
	public:
		/** Ctor.
		 */
		Movement();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
