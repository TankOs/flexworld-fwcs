#pragma once

#include <FWCS/EntityObserver.hpp>
#include <FWCS/Types.hpp>

#include <vector>
#include <map>
#include <cstring>
#include <cstdint>

namespace cs {

class Controller;
class Entity;

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
		 * @param id ID (must be unique).
		 * @return New entity.
		 */
		Entity& create_entity( EntityID id );

		/** Find entity by ID.
		 * @param id ID.
		 * @return Found entity or nullptr if not found.
		 */
		Entity* find_entity( EntityID id ) const;

		/** Delete entity.
		 * @param id ID (must exist).
		 */
		void delete_entity( EntityID id );

	private:
		typedef std::vector<Controller*> ControllerPtrArray;
		typedef std::map<EntityID, Entity*> EntityMap;
		
		void link_entity( Entity& entity );

		void on_property_create( Property& property, Entity& entity );

		ControllerPtrArray m_controllers;
		EntityMap m_entities;
};

}

#include "System.inl"
