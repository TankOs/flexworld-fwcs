#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Movement force transform controller.
 * A force is being transformed to acceleration.
 *
 * Properties needed:
 *   * cs::prop::Moveable
 */
class MovementForceTransform : public Controller {
	public:
		/** Ctor.
		 */
		MovementForceTransform();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
