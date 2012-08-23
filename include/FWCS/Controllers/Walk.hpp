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
 * When the control vector's length is zero, the controller will brake the
 * entity, again with walk_force. This also means that under certain
 * circumstances, for example when a very powerful wind is blowing, the
 * controller won't be able to completely stop the entity.
 *
 * Required properties:
 *   * forward_vector (sf::Vector3f): Walk direction.
 *   * control_vector (sf::Vector2f): Control vector (see class description).
 *   * force (sf::Vector3f, in Newton): Force to which walk force is added to.
 *   * walk_force (float, in Newton): Walk force.
 *   * max_walk_velocity (float, in m/s): Maximum velocity this controller can generate.
 *   * velocity (sf::Vector3f, in m/s): Current velocity
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
