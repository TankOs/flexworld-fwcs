#pragma once

#include <FWCS/Controller.hpp>

namespace cs {
namespace ctl {

/** Gravity controller.
 * The gravity controller applies gravity to an entity's velocity. The amount
 * of gravity is set in the controller and can be changed at any time.
 *
 * Gravitation is interpreted as m/s². The default value equals to the earth's
 * graviation of 9.80665 m/s².
 *
 * Properties needed:
 *   * cs::prop::Moveable
 */
class Gravity : public Controller {
	public:
		/** Ctor.
		 * @param gravity Initial gravity.
		 */
		Gravity( float gravity = 9.80665f );

		/** Set gravity.
		 * @param gravity Gravity.
		 */
		void set_gravity( float gravity );

		/** Get gravity.
		 * @return Gravity.
		 */
		float get_gravity() const;

	private:
		void update_entity( Entity& entity, const sf::Time& delta );

		float m_gravity;
};

}
}
