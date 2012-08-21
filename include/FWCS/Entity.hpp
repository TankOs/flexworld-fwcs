#pragma once

#include <FWCS/EntityObserver.hpp>
#include <FWCS/NonCopyable.hpp>
#include <FWCS/Property.hpp>

#include <string>
#include <map>

namespace cs {

class Property;

/** Entity.
 * An entity is an object in the world that can have properties. Properties
 * reflect the state and type of an object. Depending on the chosen properties
 * FWCS will perform actions on the entity and properties through contollers.
 */
class Entity : public NonCopyable {
	public:
		/** Ctor.
		 */
		Entity();

		/** Dtor.
		 */
		virtual ~Entity();

		/** Get number of properties.
		 * @return Number of properties.
		 */
		std::size_t get_num_properties() const;

		/** Create property.
		 * Property IDs must be unique. Undefined behaviour if property with same
		 * ID already exists.
		 * @tparam T Type.
		 * @param id ID.
		 * @param initial_value Initial value.
		 * @return New property.
		 * @see find_property to check if a property of a given type already exists.
		 */
		template <class T>
		ConcreteProperty<T>& create_property( const std::string& id, const T& initial_value = T() );

		/** Find property.
		 * In debug mode, the type will be checked (via a dynamic cast). In release
		 * mode malformed type requests leads to undefined behaviour.
		 * @tparam Value type.
		 * @param id ID.
		 * @return Property, or nullptr if not found.
		 */
		template <class T>
		ConcreteProperty<T>* find_property( const std::string& id );

		/** Find base property.
		 * Used internally only.
		 * @param id ID.
		 * @return Property, or nullptr if not found.
		 */
		Property* find_base_property( const std::string& id );

		/** Find base property.
		 * Used internally only.
		 * @param id ID.
		 * @return Property, or nullptr if not found.
		 */
		const Property* find_base_property( const std::string& id ) const;

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
};

}

#include "Entity.inl"
