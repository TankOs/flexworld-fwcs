#pragma once

#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace prop {

/** Drag property.
 */
class Drag : public Property {
	public:
		static const std::string ID; ///< ID.

		/** Ctor.
		 */
		Drag();

		const std::string& get_id() const;

		/** Get area.
		 * @return Area (m²).
		 */
		float get_area() const;

		/** Get resistance coefficient.
		 * @return Resistance coefficient.
		 */
		float get_resistance_coeff() const;

		/** Set area.
		 * @param area Area (m²).
		 */
		void set_area( float area );

		/** Set resistance coefficient.
		 * @param resistence_coeff Resistance coefficient.
		 */
		void set_resistance_coeff( float resistence_coeff );

	private:
		float m_area;
		float m_resistance_coeff;
};

}
}
