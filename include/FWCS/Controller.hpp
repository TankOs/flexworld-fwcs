#pragma once

namespace cs {
class Entity;
}

namespace sf {
class Time;
}

namespace cs {

/** Controller abstract baseclass.
 * The controller implements logic for entities. Each controller should be designed
 * to have one single task and only work on entities that meet specific
 * requirements, like a set of properties.
 *
 * An controller is created by the System class for every entity that is being
 * considered "interesting". That also means that controllers should normally not
 * be heavy in memory-usage, as a lot of them could be created.
 *
 * On the other hand every controller should be designed to operate fast. For
 * example looking up properties in the execute() implementation should be
 * avoided. Instead pointers to the properties can be cached in member
 * variables.
 */
class Controller {
	public:
		/** Ctor.
		 * @param entity Entity (referenced).
		 */
		Controller( Entity& entity );

		/** Dtor.
		 */
		virtual ~Controller();

		/** Execute.
		 * @param sim_time Simulation time.
		 */
		virtual void execute( const sf::Time& sim_time ) = 0;

		/** Get entity.
		 * @return Entity.
		 */
		Entity& get_entity();

		/** Get entity.
		 * @return Entity.
		 */
		const Entity& get_entity() const;

	private:
		Entity& m_entity;
};

}
