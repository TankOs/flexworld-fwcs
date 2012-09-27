#pragma once

namespace sf {
class Time;
}

namespace cs {

/** Executor abstract baseclass.
 * The executor implements logic for entities. Each executor should be designed
 * to have one single task and only work on entities that meet specific
 * requirements, like a set of properties.
 *
 * An executor is created by the System class for every entity that is being
 * considered "interesting". That also means that executors should normally not
 * be heavy in memory-usage, as a lot of them could be created.
 *
 * On the other hand every executor should be designed to operate fast. For
 * example looking up properties in the execute() implementation should be
 * avoided. Instead pointers to the properties can be cached in member
 * variables.
 */
class Executor {
	public:
		/** Ctor.
		 */
		Executor();

		/** Dtor.
		 */
		virtual ~Executor();

		/** Execute.
		 * @param sim_time Simulation time.
		 */
		virtual void execute( const sf::Time& sim_time ) = 0;

	private:
};

}
