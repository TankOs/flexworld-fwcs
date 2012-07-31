#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Moveable property.
 */
class Moveable : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		Moveable();

		const std::string& get_id() const;

		/** Get velocity.
		 * @return Velocity (m/s).
		 */
		const sf::Vector3f& get_velocity() const;

		/** Get acceleration.
		 * @return Acceleration (m/s²).
		 */
		const sf::Vector3f& get_acceleration() const;

		/** Get force.
		 * @return Force (Newton).
		 */
		const sf::Vector3f& get_force() const;

		/** Get mass.
		 * @return Mass (kg).
		 */
		float get_mass() const;

		/** Set velocity.
		 * @param velocity Velocity (m/s).
		 */
		void set_velocity( const sf::Vector3f& velocity );

		/** Set acceleration.
		 * @param acceleration Acceleration (m/s²).
		 */
		void set_acceleration( const sf::Vector3f& acceleration );

		/** Set force.
		 * @param force Force (Newton).
		 */
		void set_force( const sf::Vector3f& force );

		/** Set mass.
		 * @param mass Mass (kg).
		 */
		void set_mass( float mass );

	private:
		sf::Vector3f m_velocity;
		sf::Vector3f m_acceleration;
		sf::Vector3f m_force;
		float m_mass;
};

}
}
