#pragma once

#include <memory>

namespace cs {

class Executor;
class Entity;
class ExecutorRequirements;

/** Base class for executor factories.
 */
class BaseExecutorFactory {
	public:
		/** Dtor.
		 */
		virtual ~BaseExecutorFactory();

		/** Create executor.
		 * @param entity Entity.
		 */
		virtual std::unique_ptr<Executor> create_executor( Entity& entity ) = 0;

		/** Get requirements.
		 * @return Requirements.
		 */
		virtual const ExecutorRequirements& get_requirements() const = 0;

	protected:
		/** Ctor.
		 */
		BaseExecutorFactory();
};

}
