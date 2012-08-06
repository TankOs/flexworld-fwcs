#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Environment property.
 */
class Environment : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		Environment();

		const std::string& get_id() const;

		/** Get gravity.
		 * @return Gravity (in m/s²).
		 */
		float get_gravity() const;

		/** Get air density.
		 * @return Air density (in kg/m³).
		 */
		float get_air_density() const;

		/** Set gravity.
		 * @param gravity Gravity (in m/s²).
		 */
		void set_gravity( float gravity );

		/** Set air density.
		 * @param air_density Air density (in kg/m³).
		 */
		void set_air_density( float air_density );

	private:
		float m_air_density;
		float m_gravity;
};

}
}
