#pragma once

#include <FWCS/Controller.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

/** Mouselook controller.
 * The mouselook controller transforms delta input values to angular velocity.
 * If the delta values are zero, the angular velocity will be changed towards
 * zero, too.
 *
 * After executing, the delta values will be reset to zero.
 *
 * Properties:
 *   * mlook_delta (sf::Vector2f, in/out): Delta values, clamped from -1.0 to 1.0.
 *   * mlook_angular_acceleration (float, in): Angular acceleration, in radians/s².
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
		sf::Vector2f* m_mlook_delta;
		const float* m_mlook_angular_acceleration;
		sf::Vector3f* m_angular_velocity;
};

}
}
