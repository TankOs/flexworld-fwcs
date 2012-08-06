#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Movement controller.
 * Applies velocity to position, dependent on time.
 *
 * Properties needed:
 *   * cs::prop::Moveable
 *   * cs::prop::Object
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
