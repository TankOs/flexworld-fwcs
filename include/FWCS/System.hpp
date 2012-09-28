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
 * Important: Do not store pointers to entities. Memory may be moved when
 * entities are being added/removed. Instead store the entity's ID and look it
 * up on demand.
 */
class System {
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

		/** Create entity.
		 * Create a new entity with a system-wide unique ID.
		 * @return Entity.
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
		std::vector<std::unique_ptr<BaseExecutorFactory>> m_factories;
		std::vector<Entity> m_entities;

		EntityID m_next_entity_id;
};

}

#include "System.inl"
