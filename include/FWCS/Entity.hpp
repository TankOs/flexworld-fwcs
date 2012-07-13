#pragma once

#include <FWCS/Types.hpp>

#include <string>
#include <map>

namespace cs {

class Property;

/** Entity.
 * An entity is an object in the world that can have properties. Properties
 * reflect the state and type of an object. Depending on the chosen properties
 * FWCS will perform actions on the entity and properties.
 */
class Entity {
	public:
		/** Ctor.
		 * @param id ID.
		 */
		Entity( EntityID id );

		/** Dtor.
		 */
		~Entity();

		/** Get ID.
		 * @return ID.
		 */
		EntityID get_id() const;

		/** Get number of properties.
		 * @return Number of properties.
		 */
		std::size_t get_num_properties() const;

		/** Create property.
		 * Only one property of a type is allowed to exist. Undefined behaviour if
		 * you try to create the same property type twice.
		 * @tparam PropType Property type to instantiate.
		 * @see has_property to check if a property of a given type already exists.
		 */
		template <class PropType>
		void create_property();

		/** Check if a property exists.
		 * @tparam PropType Property type.
		 * @return true if exists.
		 */
		template <class PropType>
		bool has_property() const;

	private:
		typedef std::map<const std::string, Property*> PropertyMap;

		PropertyMap m_properties;
		EntityID m_id;
};

}

#include "Entity.inl"
