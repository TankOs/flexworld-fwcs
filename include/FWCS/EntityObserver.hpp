#pragma once

#include <string>

namespace cs {

class Entity;
class Property;

/** Entity observer interface.
 * Used internally.
 */
class EntityObserver {
	public:
		/** Called when property is created.
		 * @param id Property ID.
		 * @param entity Entity (this).
		 */
		virtual void on_property_create( const std::string& id, cs::Entity& entity ) = 0;
};


}
