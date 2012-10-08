#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Turn controller.
 * The turn controller processes angular acceleration and angular velocity. The
 * turn velocity contributes to the forward vector, which is rotated
 * accordingly.
 *
 * When the controller is done executing, it will reset the turn_acceleration
 * to zero.
 *
 * Required properties:
 *   * turn_acceleration (sf::Vector3f, in/out): Turn acceleration in degrees.
 *   * turn_velocity (sf::Vector3f, in/out): Turn velocity in degrees.
 *   * rotation (sf::Vector3f, in/out): Rotation in degrees.
 */
class Turn : public Controller {
	public:
		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Turn( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		sf::Vector3f* m_turn_acceleration;
		sf::Vector3f* m_turn_velocity;
		sf::Vector3f* m_rotation;
		sf::Vector3f* m_forward;
};

}
}
