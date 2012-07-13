#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Velocity property.
 */
class Velocity : public Property {
	public:
		/** Ctor.
		 */
		Velocity();

		const std::string& get_id() const;

		/** Set velocity.
		 * @param velocity Velocity.
		 */
		void set_velocity( const sf::Vector3f& velocity );

		/** Get velocity.
		 * @return Velocity.
		 */
		const sf::Vector3f& get_velocity() const;

	private:
		sf::Vector3f m_velocity;
};

}
}
