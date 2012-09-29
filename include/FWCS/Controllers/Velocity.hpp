#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Velocity controller.
 * The velocity controller updates an entity's velocity by applying
 * acceleration. A maximum velocity can be set.
 *
 * Required properties:
 *   * velocity (sf::Vector3f, in+out): Velocity in m/s.
 *   * acceleration (sf::Vector3f, in): Acceleration.
 *
 * Optional properties:
 *   * max_velocity (float, in): Maximum velocity in m/s.
 */
class Velocity : public Controller {
	public:
		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Velocity( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		sf::Vector3f* m_velocity;
		sf::Vector3f* m_acceleration;
		float* m_max_velocity;
};

}
}
