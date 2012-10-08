#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
class ControllerRequirements;
}

namespace cs {
namespace ctrl {

/** Accelerate controller.
 * The accelerate controller updates an entity's velocity by applying
 * acceleration. A maximum velocity can be set.
 *
 * After updating the velocity, the acceleration is reset to 0.
 *
 * Required properties:
 *   * velocity (sf::Vector3f, in/out): Accelerate in m/s.
 *   * acceleration (sf::Vector3f, in/out): Acceleration.
 *
 * Optional properties:
 *   * max_velocity (float, in): Maximum velocity in m/s.
 */
class Accelerate : public Controller {
	public:
		/** Get requirements.
		 * @return Requirements.
		 */
		static const ControllerRequirements& get_requirements();

		/** Ctor.
		 * @param entity Entity.
		 */
		Accelerate( Entity& entity );

		void execute( const sf::Time& sim_time );

	private:
		sf::Vector3f* m_velocity;
		sf::Vector3f* m_acceleration;
		const float* m_max_velocity;
};

}
}
