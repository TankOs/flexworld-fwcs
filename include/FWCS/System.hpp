#pragma once

#include <FWCS/BaseExecutorFactory.hpp>
#include <FWCS/ExecutorFactory.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Types.hpp>

#include <memory>
#include <vector>
#include <cstdint>
#include <cassert>

namespace cs {

/** System.
 * The System class is a manager and router for entities and executors.
 *
 * Entities being added to the system are automatically linked to all matching
 * executors previously added to the system. Adding executor factories at any
 * time is also possible, also modifying entity properties after they have been
 * added.
 *
 * Running the system processes all executors.
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

		/** Get number of executor factories.
		 * @return Number of executor factories.
		 */
		std::size_t get_num_factories() const;

		/** Get number of entities.
		 * @return Number of entities.
		 */
		std::size_t get_num_entities() const;

		/** Create factory.
		 * Undefined behaviour if a factory for the same executor type has already
		 * been created.
		 * @tparam T Executor type.
		 */
		template <class T>
		void create_factory();

		/** Check if a specific factory exists.
		 * @tparam T Executor type.
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

	private:
		void on_property_create( const std::string& id, cs::Entity& entity );

		void create_factory_executors( BaseExecutorFactory& factory );

		typedef std::pair<
			std::unique_ptr<Entity>,
			std::vector<std::unique_ptr<Executor>>
		> EntityExecutorsPair;

		std::vector<std::unique_ptr<BaseExecutorFactory>> m_factories;
		std::vector<EntityExecutorsPair> m_entities;

		EntityID m_next_entity_id;
};

}

#include "System.inl"
