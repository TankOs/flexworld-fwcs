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

		std::unique_ptr<Executor> create_executor( Entity& entity );
		const ExecutorRequirements& get_requirements() const;

	private:
};

}

#include "ExecutorFactory.inl"
