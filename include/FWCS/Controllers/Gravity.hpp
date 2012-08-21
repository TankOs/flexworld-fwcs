#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Gravity controller.
 * The gravity controller applies gravity to an entity's velocity. The amount
 * of gravity is fetched from an Environment property.
 *
 * Properties needed:
 *   * force (sf::Vector3f, in Newton): Force to which gravity gets added
 *   * gravity (float, in m/s²): Gravity (acceleration)
 *   * mass (float, in kg): Mass
 */
class Gravity : public Controller {
	public:
		/** Ctor.
		 */
		Gravity();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
