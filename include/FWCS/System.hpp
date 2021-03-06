#pragma once

#include <FWCS/BaseControllerFactory.hpp>
#include <FWCS/ControllerFactory.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Types.hpp>

#include <memory>
#include <vector>
#include <cstdint>
#include <cassert>

namespace sf {
class Time;
}

namespace cs {

/** System.
 * The System class is a manager and router for entities and controllers.
 *
 * Entities being added to the system are automatically linked to all matching
 * controllers previously added to the system. Adding controller factories at any
 * time is also possible, also modifying entity properties after they have been
 * added.
 *
 * Running the system processes all controllers.
 *
 * Pointers/references to entities are valid until the proper entity is
 * destroyed.
 */
class System : public EntityObserver {
	public:
		/** Ctor.
		 */
		System();

		/** Dtor.
		 */
		~System();

		/** Get number of controller factories.
		 * @return Number of controller factories.
		 */
		std::size_t get_num_factories() const;

		/** Get number of entities.
		 * @return Number of entities.
		 */
		std::size_t get_num_entities() const;

		/** Create factory.
		 * Undefined behaviour if a factory for the same controller type has already
		 * been created.
		 * @tparam T Controller type.
		 */
		template <class T>
		void create_factory();

		/** Check if a specific factory exists.
		 * @tparam T Controller type.
		 * @return true if factory exists.
		 */
		template <class T>
		bool has_factory() const;

		/** Create entity.
		 * Create a new entity with a system-wide unique ID.
		 * @return ID of newly created entity.
		 */
		Entity& create_entity();

		/** Find entity.
		 * Do NOT store the returned pointer anywhere. It may become invalid over
		 * time!
		 * @param id ID.
		 * @return Entity or nullptr if not found.
		 */
		Entity* find_entity( EntityID id );

		/** Destroy entity.
		 * Undefined behaviour if no entity with the given ID exists.
		 * @param id ID.
		 */
		void destroy_entity( EntityID id );

		/** Run simulation.
		 * @param sim_time Simulation time.
		 */
		void run( const sf::Time& sim_time );

	private:
		void on_property_create( const std::string& id, cs::Entity& entity );

		void create_factory_controllers( BaseControllerFactory& factory );

		typedef std::pair<
			std::unique_ptr<Entity>,
			std::vector<std::unique_ptr<Controller>>
		> EntityControllersPair;

		std::vector<std::unique_ptr<BaseControllerFactory>> m_factories;
		std::vector<EntityControllersPair> m_entities;

		EntityID m_next_entity_id;
};

}

#include "System.inl"
