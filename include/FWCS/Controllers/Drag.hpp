#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Drag controller.
 * The drag controller adds a counter force to an entity due to fluid drag
 * (air, water etc.).
 *
 * Properties needed:
 *   * cs::prop::Moveable
 *   * cs::prop::Environment
 *   * cs::prop::Drag
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
