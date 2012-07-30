#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Mass property.
 *
 * Mass is stored as kilograms [kg].
 */
class Mass : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		Mass();

		const std::string& get_id() const;

		/** Set mass.
		 * @param mass Velocity.
		 */
		void set_mass( float mass );

		/** Get mass.
		 * @return Velocity.
		 */
		float get_mass() const;

	private:
		float m_mass;
};

}
}
