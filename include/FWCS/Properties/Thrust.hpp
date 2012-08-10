#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Thrust property.
 * The thrust is a force that's applied to an entity's total force.
 */
class Thrust : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		Thrust();

		const std::string& get_id() const;

		/** Get thrust.
		 * @return Thrust (in Newton).
		 */
		const sf::Vector3f& get_thrust() const;

	private:
		sf::Vector3f m_thrust;
};

}
}
