#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Force reset controller.
 * Resets an entity's force to zero.
 *
 * Properties needed:
 *   * Moveable
 */
class ForceReset : public Controller {
	public:
		/** Ctor.
		 */
		ForceReset();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
