#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Drag controller.
 * The drag controller adds a counter force to an entity due to fluid drag
 * (air, water etc.).
 *
 * Properties needed:
 *   * air_density (float, in kg/cm³): Air density
 *   * resistance_coeff (float): Resistance coefficient
 *   * drag_area (float, m²): Drag-receiving area
 *   * velocity (sf::Vector3f, in m/s): Current velocity
 *   * force (sf::Vector3f, in Newton): Force; drag force will be added.
 */
class Drag : public Controller {
	public:
		/** Ctor.
		 */
		Drag();

	private:
		void update_entity( Entity& entity, const sf::Time& delta );
};

}
}
