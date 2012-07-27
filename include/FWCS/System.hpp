#pragma once

#include <vector>
#include <cstring>

namespace cs {

class Controller;

/** System.
 * The System class is a manager and router for entities and controllers.
 *
 * Entities that get added to the system will be automatically linked to the
 * added controllers, depending on their properties. It doesn't matter in what
 * order components or entities are added.
 *
 * When the system is updated it will process all controllers and therefore all
 * linked entities.
 */
class System {
	public:
		/** Ctor.
		 */
		System();

		/** Dtor.
		 */
		~System();

		/** Get number of entities.
		 * @return Number of entities.
		 */
		std::size_t get_num_entities() const;

		/** Get number of controllers.
		 * @return Number of controllers.
		 */
		std::size_t get_num_controllers() const;

		/** Create a controller.
		 * Either specify a template controller as a parameter to directly
		 * initialize settings or just use the template argument to use defaults.
		 * Undefined behaviour if a controller of the same type has already been
		 * added.
		 * @param tpl Controller template (will be copied).
		 * @tparam ControllerType Controller type.
		 */
		template <class ControllerType>
		void create_controller( const ControllerType& tpl = ControllerType() );

		/** Check if system has a specific controller.
		 * @tparam ControllerType Controller type to check for.
		 */
		template <class ControllerType>
		bool has_controller();

		/** Delete controller.
		 * Undefined behaviour if controller hasn't been created.
		 * @tparam ControllerType Controller type of controller to delete.
		 */
		template <class ControllerType>
		void delete_controller();

	private:
		std::vector<Controller*> m_controllers;
};

}

#include "System.inl"
