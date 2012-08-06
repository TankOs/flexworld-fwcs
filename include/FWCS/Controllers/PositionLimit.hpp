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
 *   * Object
 *   * PositionLimit
 *   * Moveable
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
