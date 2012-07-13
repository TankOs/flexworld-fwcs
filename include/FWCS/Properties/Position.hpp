#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Position property.
 */
class Position : public Property {
	public:
		/** Ctor.
		 */
		Position();

		const std::string& get_id() const;

		/** Set position.
		 * @param position Position.
		 */
		void set_position( const sf::Vector3f& position );

		/** Get position.
		 * @return Position.
		 */
		const sf::Vector3f& get_position() const;

	private:
		sf::Vector3f m_position;
};

}
}
