#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Friction.
 * The controller implements static and sliding friction forces. Static
 * friction is applied when an object is generating force but not moving and
 * sliding friction when it's moving.
 *
 * Friction will only be calculated when an object is on the ground.
 *
 * The object's current negative up vector force is used as normal force
 * (jacking force).
 *
 * Required properties:
 *   * velocity (sf::Vector3f): Current velocity.
 *   * force (sf::Vector3f): Current force.
 *   * up_vector (sf::Vector3f): Normalized up vector (used for normal force).
 *   * static_friction_coeff (float): Static friction coefficient.
 *   * sliding_friction_coeff (float): Sliding friction coefficient.
 *   * on_ground (bool): true when on ground.
 */
class Friction : public Controller {
	public:
		/** Ctor.
		 */
		Friction();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
