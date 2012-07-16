#pragma once

#include <string>
#include <vector>

namespace cs {
class Entity;
}

namespace sf {
class Time;
}

namespace cs {

/** Controller baseclass.
 * A controller is responsible for update entities and their properties.
 * They are the logic in the component-based system.
 *
 * FWCS does not keep track of entity links anywhere, the controllers
 * themselves are instead responsible for that.
 *
 * Each controller is run everytime the component system is triggered.
 */
class Controller {
	public:
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
		 * @param entity Entity to add.
		 */
		void add_entity( Entity& entity );

		/** Remove entity from update queue.
		 * Called internally only.
		 * @param entity Entity to remove.
		 */
		void remove_entity( const Entity& entity );

		/** Run controller.
		 * @param delta Time to simulate.
		 */
		void run( const sf::Time& delta );

		/** Get required properties.
		 * @return Required properties.
		 * @see listen_for
		 */
		const std::vector<std::string>& get_required_properties() const;

		/** Get number of currently linked entities.
		 * @return Number of linked entities.
		 */
		std::size_t get_num_linked_entities() const;

	protected:
		/** Listen for entities with specific properties.
		 * Call this method from derived classes to setup the controller. Undefined
		 * behaviour if called multiple times.
		 * @param properties Properties an entity must have to be processed by this controller.
		 */
		void listen_for( const std::vector<std::string>& properties );

		/** Update entity.
		 * @param entity Entity.
		 * @param delta Time to simulate.
		 */
		virtual void update_entity( const Entity& entity, const sf::Time& delta );

	private:
		typedef std::vector<Entity*> EntityPtrArray; ///< Array of pointers to entities.

		std::vector<std::string> m_required_properties;
		EntityPtrArray m_entities;
};

}
