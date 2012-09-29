#pragma once

#include <vector>
#include <utility>
#include <string>
#include <cstdint>

namespace cs {

class Entity;

/** Controller requirements.
 * Collection of requirements an entity must meet to be interesting for an
 * controller.
 */
class ControllerRequirements {
	public:
		/** Property requirement.
		 */
		struct PropertyRequirement {
			/** Ctor.
			 * @param name_ Name of property.
			 * @param type_ Property C++ data type ID (platform-specific).
			 * @param required_ true if required, false if not allowed (exclusion).
			 */
			PropertyRequirement(
				const std::string& name_,
				const std::string& type_,
				bool required_
			);

			/** Check equality.
			 * @param other Other property requirement.
			 * @return true if equal.
			 */
			bool operator==( const PropertyRequirement& other ) const;

			std::string name; ///< Name of property (ID).
			std::string type; ///< Property C++ data type ID (platform-specific).
			bool required; ///< true if required, false if not allowed (exclusion).
		};

		/** Get number of requirements.
		 * @return Number of requirements.
		 */
		std::size_t get_num_requirements() const;

		/** Require or disallow property.
		 * @param name Property name.
		 * @param require true to require, false to disallow (exclusion).
		 * @tparam T Property data type.
		 * @return *this
		 */
		template <class T>
		ControllerRequirements& require_property( const std::string& name, bool require );

		/** Get property requirement.
		 * Undefined behaviour if index is invalid.
		 * @param index Property requirement index.
		 * @return Property requirement.
		 */
		const PropertyRequirement& get_property_requirement( std::size_t index ) const;

		/** Test requirements on an entity.
		 * @param entity Entity.
		 * @return true if all requirements met.
		 */
		bool test( const Entity& entity ) const;

	private:

		std::vector<PropertyRequirement> m_property_requirements;
};

}

#include "ControllerRequirements.inl"
