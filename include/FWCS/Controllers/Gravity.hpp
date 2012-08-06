#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctrl {

/** Gravity controller.
 * The gravity controller applies gravity to an entity's velocity. The amount
 * of gravity is fetched from an Environment property.
 *
 * Properties needed:
 *   * cs::prop::Moveable
 *   * cs::prop::Environment
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
