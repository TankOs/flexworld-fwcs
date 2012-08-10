#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Jump property.
 */
class Jump : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		Jump();

		const std::string& get_id() const;

		/** Check if jumping is active.
		 * @return true if active.
		 */
		bool is_active() const;

		/** Get up vector.
		 * @return Up vector.
		 */
		const sf::Vector3f& get_up_vector() const;

		/** Get force that's applied when jumping.
		 * @return force (in Newton).
		 */
		float get_force() const;

		/** Set active.
		 * @param active true to activate.
		 */
		void set_active( bool active );

		/** Set up vector.
		 * @param up_vector Up vector.
		 */
		void set_up_vector( const sf::Vector3f& up_vector );

		/** Set force.
		 * @param force Force (in Newton).
		 */
		void set_force( float force );

	private:
		sf::Vector3f m_up_vector;
		float m_force;
		bool m_active;
};

}
}
