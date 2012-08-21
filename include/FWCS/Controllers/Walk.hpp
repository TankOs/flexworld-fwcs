#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Walk controller.
 * Simulates walking,
 *
 * The movement generally goes along the forward vector with a maximum force as
 * defined by walk_force. Entities can be moved in two directions, controlled
 * by the control vector (forward/backward, controlled by control vector's y
 * component, and strafing left/right, controlled by the x component).
 *
 * The control vector should be clamped to 0..1.
 *
 * Required properties:
 *   * forward_vector (sf::Vector3f): Walk direction
 *   * control_vector (sf::Vector2f): Control vector (see class description)
 *   * force (sf::Vector3f, in Newton): Force to which walk force is added to
 *   * walk_force (float, in Newton): Walk force
 */
class Walk : public Controller {
	public:
		/** Ctor.
		 */
		Walk();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
