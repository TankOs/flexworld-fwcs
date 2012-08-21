#pragma once

#include <FWCS/EntityObserver.hpp>

#include <vector>
#include <set>
#include <cstring>
#include <cstdint>

namespace cs {
class Controller;
class Entity;
}

namespace sf {
class Time;
}

namespace cs {

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
class System : public EntityObserver {
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
		 * Undefined behaviour if a controller of the same type has already been
		 * added.
		 * @tparam ControllerType Controller type.
		 * @return New controller.
		 */
		template <class ControllerType>
		ControllerType& create_controller();

		/** Find a controller.
		 * @tparam ControllerType Controller type to find.
		 * @return Controller or nullptr if not found.
		 */
		template <class ControllerType>
		ControllerType* find_controller() const;

		/** Delete controller.
		 * Undefined behaviour if controller hasn't been created.
		 * @tparam ControllerType Controller type of controller to delete.
		 */
		template <class ControllerType>
		void delete_controller();

		/** Create new entity.
		 * @return New entity.
		 */
		Entity& create_entity();

		/** Delete entity.
		 * @param entity Entity.
		 */
		void delete_entity( Entity& entity );

		/** Run system.
		 * Calls all controllers.
		 * @param sim_time Simulation time.
		 */
		void run( const sf::Time& sim_time );

	private:
		typedef std::vector<Controller*> ControllerPtrArray;
		typedef std::set<Entity*> EntitySet;
		
		void link_entity( Entity& entity );

		void on_property_create( const std::string& id, Entity& entity );

		ControllerPtrArray m_controllers;
		EntitySet m_entities;
};

}

#include "System.inl"
