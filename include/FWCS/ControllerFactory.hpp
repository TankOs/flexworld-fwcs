#pragma once

#include <FWCS/BaseControllerFactory.hpp>

namespace cs {

/** Factory for creating controllers of a specific type.
 * The factory creates controller objects of a specific type. It also redirects
 * the is_entity_interesting() call to the controller itself.
 * @tparam T Controller type.
 */
template <class T>
class ControllerFactory : public BaseControllerFactory {
	public:
		/** Ctor.
		 */
		ControllerFactory();

		/** Dtor.
		 */
		~ControllerFactory();

		std::unique_ptr<Controller> create_controller( Entity& entity );
		const ControllerRequirements& get_requirements() const;

	private:
};

}

#include "ControllerFactory.inl"
