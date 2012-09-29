#pragma once

#include <memory>

namespace cs {

class Controller;
class Entity;
class ControllerRequirements;

/** Base class for controller factories.
 */
class BaseControllerFactory {
	public:
		/** Dtor.
		 */
		virtual ~BaseControllerFactory();

		/** Create controller.
		 * @param entity Entity.
		 */
		virtual std::unique_ptr<Controller> create_controller( Entity& entity ) = 0;

		/** Get requirements.
		 * @return Requirements.
		 */
		virtual const ControllerRequirements& get_requirements() const = 0;

	protected:
		/** Ctor.
		 */
		BaseControllerFactory();
};

}
