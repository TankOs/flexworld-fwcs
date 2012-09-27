#pragma once

#include <FWCS/BaseExecutorFactory.hpp>
#include <FWCS/ExecutorFactory.hpp>

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

		/** Create factory.
		 * Undefined behaviour if a factory for the same executor type has already
		 * been created.
		 * @tparam T Executor type.
		 */
		template <class T>
		void create_factory();

	private:
		std::vector<std::unique_ptr<BaseExecutorFactory>> m_factories;
};

}

#include "System.inl"
