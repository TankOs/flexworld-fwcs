#pragma once

#include <FWCS/BaseExecutorFactory.hpp>

namespace cs {

/** Factory for creating executors of a specific type.
 * The factory creates executor objects of a specific type. It also redirects
 * the is_entity_interesting() call to the executor itself.
 * @tparam T Executor type.
 */
template <class T>
class ExecutorFactory : public BaseExecutorFactory {
	public:
		/** Ctor.
		 */
		ExecutorFactory();

		/** Dtor.
		 */
		~ExecutorFactory();

		/** Create a new executor.
		 * @param entity Entity (referenced).
		 * @return Executor (move).
		 */
		std::unique_ptr<Executor> create_executor( Entity& entity );

	private:
};

}

#include "ExecutorFactory.inl"
