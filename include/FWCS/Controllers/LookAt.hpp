#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Look at a specific position.
 * The controller turns an entity to look at a specific position. Only x and y
 * axes for pitch and yaw are concerned. Make sure to use a compatible turn
 * constraint.
 *
 * Properties:
 *   * position (sf::Vector3f, in): Position.
 *   * forward_vector (sf::Vector3f, in): Forward vector (unit).
 *   * up_vector (sf::Vector3f, in): Up vector (unit).
 *   * angular_velocity (sf::Vector3f, in/out): Angular velocity, in radians.
 *   * look_at_position (sf::Vector3f, in): Position to look at.
 *   * look_at_acceleration (float, in): Angular acceleration, in radians.
 *   * max_look_at_velocity (float, in): Maximum angular velocity, in radians.
 */
class LookAt : public Controller {
	public:
		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		LookAt( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		const sf::Vector3f* m_position;
		const sf::Vector3f* m_forward_vector;
		const sf::Vector3f* m_up_vector;
		sf::Vector3f* m_angular_velocity;
		const sf::Vector3f* m_look_at_position;
		const float* m_look_at_acceleration;
		const float* m_max_look_at_velocity;
};

}
}
