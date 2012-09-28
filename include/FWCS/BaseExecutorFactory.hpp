#pragma once

#include <memory>

namespace cs {

class Executor;
class Entity;

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

	protected:
		/** Ctor.
		 */
		BaseExecutorFactory();
};

}
