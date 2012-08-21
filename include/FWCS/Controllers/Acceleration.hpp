#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Acceleration controller.
 * Applies acceleration to velocity, dependent on time.
 *
 * Properties needed:
 *   * acceleration (sf::Vector3f): Current acceleration
 *   * velocity (sf::Vector3f): Velocity to be changed
 */
class Acceleration : public Controller {
	public:
		/** Ctor.
		 */
		Acceleration();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
