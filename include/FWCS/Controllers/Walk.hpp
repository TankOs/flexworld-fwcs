#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Walk controller.
 * Simulates walking/strafing of a human.
 *
 * At first a maximum acceleration must be set. The direction of walking is
 * determined by the forward_vector property. The maximum velocity this
 * controller can accelerate to is stored in walk_max_velocity. The entity can
 * either be commanded forward/backward using walk_forward_control or sidewards
 * using walk_strafe_control.
 *
 * If both walk_forward_control and walk_strafe_control are zero, the
 * controller will try to slowdown the velocity to zero by applying maximum
 * acceleration into the counter-direction of the current's velocity.
 *
 * Required properties:
 *   * walk_acceleration (float, in): Walk acceleration.
 *   * walk_max_velocity (float, in): Maximum walk velocity.
 *   * walk_forward_control (float, in): Forward control, 0..1.
 *   * walk_strafe_control (float, in): Strafe control, 0..1.
 *   * forward_vector (sf::Vector3f, in): Walk direction.
 *   * velocity (sf::Vector3f, in/out): Velocity.
 */
class Walk : public Controller {
	public:
		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Walk( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		const sf::Vector3f* m_forward_vector;
		sf::Vector3f* m_velocity;

		const float* m_walk_acceleration;
		const float* m_walk_max_velocity;
		const float* m_walk_forward_control;
		const float* m_walk_strafe_control;
};

}
}
