#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Position limit property.
 */
class PositionLimit : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		PositionLimit();

		/** Get upper limit.
		 * @return Upper limit.
		 */
		const sf::Vector3f& get_upper_limit() const;

		/** Get lower limit.
		 * @return Lower limit.
		 */
		const sf::Vector3f& get_lower_limit() const;

		/** Set upper limit.
		 * @param upper_limit Upper limit.
		 */
		void set_upper_limit( const sf::Vector3f& upper_limit );

		/** Set lower limit.
		 * @param lower_limit Lower limit.
		 */
		void set_lower_limit( const sf::Vector3f& lower_limit );

		const std::string& get_id() const;

	private:
		sf::Vector3f m_upper_limit;
		sf::Vector3f m_lower_limit;
};

}
}
