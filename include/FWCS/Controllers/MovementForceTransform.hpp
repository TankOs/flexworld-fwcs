#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Movement force transform controller.
 * A force is being transformed to acceleration.
 *
 * Properties needed:
 *   * force (sf::Vector3f, in Newton): Force to transform
 *   * acceleration (sf::Vector3f, in m/s²): Resulting acceleration
 *   * mass (float, in kg): Mass
 */
class MovementForceTransform : public Controller {
	public:
		/** Ctor.
		 */
		MovementForceTransform();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
