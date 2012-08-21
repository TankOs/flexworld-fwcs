#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Jump controller.
 * The jump controller adds a constant force for a very short period of time.
 * It only operates on entities which have an activated jump property. If a
 * jump property activated more than once during the lifetime of the jump
 * action, the previous action is just continued (no jump while jumping).
 *
 * When the jump operation is completed, the controller will automatically
 * deactivate the jump property again.
 *
 * Required properties:
 *   * force (sf::Vector3f, in Newton): Force to which jump force gets added to
 *   * jump_vector (sf::Vector3f): Jump direction
 *   * jump_force (float, in Newton): Generated force along jump_vector
 *   * jump_active (bool): Set to true to jump
 */
class Jump : public Controller {
	public:
		/** Ctor.
		 */
		Jump();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
