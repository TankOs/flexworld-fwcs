#pragma once

#include <FWCS/EntityObserver.hpp>
#include <FWCS/NonCopyable.hpp>
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
class Entity : public NonCopyable {
	public:
		/** Ctor.
		 * @param id ID.
		 */
		Entity( EntityID id );

		/** Dtor.
		 */
		virtual ~Entity();

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
		 * @return New property.
		 * @see find_property to check if a property of a given type already exists.
		 */
		template <class PropType>
		PropType& create_property();

		/** Find property.
		 * @tparam PropType Property type to find.
		 * @return Property of nullptr if not found.
		 */
		template <class PropType>
		PropType* find_property() const;

		/** Check if property, given by string ID, exists.
		 * @param property_id Property ID.
		 * @return true if exists.
		 */
		bool has_property( const std::string& property_id ) const;

		/** Check if entity has observer attached.
		 * @return true if observer attached.
		 */
		bool has_observer() const;

		/** Set observer.
		 * This method is used internally. Undefined behaviour if an observer has
		 * already been set.
		 * @param observer Observer (pointer is stored).
		 */
		void set_observer( EntityObserver& observer );

		/** Get observer.
		 * Undefined behaviour if no observer set.
		 * @return Observer.
		 * @see has_observer
		 */
		EntityObserver& get_observer() const;

	private:
		typedef std::map<const std::string, Property*> PropertyMap;

		PropertyMap m_properties;
		EntityObserver* m_observer;
		EntityID m_id;
};

}

#include "Entity.inl"
