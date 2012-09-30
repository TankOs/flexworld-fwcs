#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Move controller.
 * Update an entity's position by adding the current velocity to the position.
 *
 * Required properties:
 *   * position (sf::Vector3f, in/out): Move in m.
 *   * velocity (sf::Vector3f, in): Velocity in m/s.
 */
class Move : public Controller {
	public:
		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Move( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		sf::Vector3f* m_position;
		sf::Vector3f* m_velocity;
};

}
}
