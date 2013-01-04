#pragma once

#include <FWCS/Controller.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

/** Mouselook controller.
 * The mouselook controller reads the control value and commands acceleration
 * to reach the maximum velocity limited by the control value.
 *
 * The controller differentiates between acceleration and deceleration, per
 * axis.
 *
 * The maximum length of the control vector is 1. If it's greater, it'll be
 * normalized. If not, the original value is kept.
 *
 * Properties:
 *   * mouselook_control (sf::Vector2f, in/out): Control (mapping: x->y axis, y->x axis).
 *   * max_mouselook_angular_velocity (float, in): Maximum angular velocity, in radians/s.
 *   * mouselook_angular_acceleration (float, in): Angular acceleration, in radians/s².
 *   * mouselook_angular_deceleration (float, in): Angular deceleration, in radians/s² (optional, defaults to mouselook_angular_acceleration).
 *   * angular_velocity (sf::Vector3f, in/out): Angular velocity, in radians/s.
 */
class Mouselook : public Controller {
	public:
		/** Get controller's requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Mouselook( Entity& entity );

		/** Execute.
		 * @param sim_time Simulation time.
		 */
		void execute( const sf::Time& sim_time );

	private:
		sf::Vector2f* m_mouselook_control;
		const float* m_max_mouselook_angular_velocity;
		const float* m_mouselook_angular_acceleration;
		const float* m_mouselook_angular_deceleration;
		sf::Vector3f* m_angular_velocity;
};

}
}
