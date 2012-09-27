#pragma once

#include <memory>

namespace cs {

class Executor;

/** Base class for executor factories.
 */
class BaseExecutorFactory {
	public:
		/** Dtor.
		 */
		virtual ~BaseExecutorFactory();

		/** Create executor.
		 */
		virtual std::unique_ptr<Executor> create_executor() = 0;

	protected:
		/** Ctor.
		 */
		BaseExecutorFactory();
};

}
