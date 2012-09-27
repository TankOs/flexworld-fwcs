#pragma once

namespace cs {

/** Factory for creating executors of a specific type.
 * The factory creates executor objects of a specific type. It also redirects
 * the is_entity_interesting() call to the executor itself.
 * @tparam T Executor type.
 */
template <class T>
class ExecutorFactory {
	public:
		/** Ctor.
		 */
		ExecutorFactory();

		/** Dtor.
		 */
		~ExecutorFactory();

		/** Create a new executor.
		 * @return Executor (move).
		 */
		T create_executor() const;

	private:
};

}

#include "ExecutorFactory.inl"
