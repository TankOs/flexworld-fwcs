#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Thrust reset controller.
 * Resets an entity's thrust to zero.
 *
 * Properties needed:
 *   * thrust (sf::Vector3f, in Newton): Thrust to reset
 */
class ThrustReset : public Controller {
	public:
		/** Ctor.
		 */
		ThrustReset();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
