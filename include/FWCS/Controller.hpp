#pragma once

#include <string>
#include <vector>

namespace cs {
class Entity;
}

namespace sf {
class Time;
}

/** FlexWorld component system.
 */
namespace cs {

/** Controller baseclass.
 * A controller is responsible for updating entities and their properties.
 * They are the logic in the component-based system.
 *
 * FWCS does not keep track of entity links anywhere, the controllers
 * themselves are instead responsible for that.
 *
 * Each controller is run everytime the component system is triggered.
 */
class Controller {
	public:
		typedef std::pair<std::string, std::string> IdTypePair; ///< Pair of property ID/property type ID.
		typedef std::vector<IdTypePair> RequiredPropertyArray; ///< Array of property pairs.

		/** Ctor.
		 */
		Controller();

		/** Dtor.
		 */
		virtual ~Controller();

		/** Check if an entity is interesting for this controller.
		 * @param entity Entity.
		 * @return true if it's interesting.
		 */
		bool is_entity_interesting( const Entity& entity ) const;

		/** Add entity to update queue.
		 * Called internally only.
		 * @param entity Entity to add (pointer is stored).
		 */
		void add_entity( Entity& entity );

		/** Remove entity from update queue.
		 * Called internally only.
		 * @param entity Entity to remove.
		 */
		void remove_entity( Entity& entity );

		/** Check if an entity is linked.
		 * @param entity Entity.
		 * @return true if linked.
		 */
		bool is_entity_linked( const Entity& entity );

		/** Run controller.
		 * @param delta Time to simulate.
		 */
		void run( const sf::Time& delta );

		/** Get required properties.
		 * @return Required properties.
		 * @see listen_for
		 */
		const RequiredPropertyArray& get_required_properties() const;

		/** Get number of currently linked entities.
		 * @return Number of linked entities.
		 */
		std::size_t get_num_linked_entities() const;

	protected:
		/** Listen for entities with a specific property of a specific type.
		 * Call this method from derived classes to setup the controller. Call
		 * multiple times to concatenate required properties by an AND clause.
		 * Undefined behaviour if property has already been listened for or if
		 * called after entities have been added already.
		 * @tparam PT Type of the property the entity has to have.
		 * @param property Property an entity must have to be processed by this controller.
		 */
		template <class PT>
		void listen_for( const std::string& property );

		/** Update entity.
		 * @param entity Entity.
		 * @param delta Time to simulate.
		 */
		virtual void update_entity( Entity& entity, const sf::Time& delta );

		/** Called when entity is added.
		 * @param entity Added entity.
		 */
		virtual void on_entity_add( Entity& entity );

		/** Called when entity is removed.
		 * @param entity Added entity.
		 */
		virtual void on_entity_remove( Entity& entity );

	private:
		typedef std::vector<Entity*> EntityPtrArray;

		RequiredPropertyArray m_required_properties;
		EntityPtrArray m_entities;
};

}

#include "Controller.inl"
