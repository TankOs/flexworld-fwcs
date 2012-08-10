#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Time.hpp>
#include <map>

namespace cs {
namespace ctrl {

/** Jump controller.
 * The jump controller adds a constant force for a very short period of time.
 * It only operates on entities which have an activated jump property. If a
 * jump property activated more than once during the lifetime of the jump
 * action, the previous action is just continued (no jump while jumping).
 *
 * When the jump operation is completed, the controller will automatically
 * deactivate the jump property again.
 *
 * Required properties:
 *   * Moveable
 *   * Jump
 */
class Jump : public Controller {
	public:
		/** Ctor.
		 */
		Jump();

		/** Get number of cached entities.
		 * @return Number of cached entities.
		 */
		std::size_t get_num_cached_entities() const;

	private:
		typedef std::map<Entity*, sf::Time> EntityRuntimeMap;

		void on_entity_remove( Entity& entity );
		void update_entity( Entity& entity, const sf::Time& delta );

		EntityRuntimeMap m_runtimes;
};

}
}
