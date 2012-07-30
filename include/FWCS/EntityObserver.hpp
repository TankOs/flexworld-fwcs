#pragma once

namespace cs {

class Entity;
class Property;

/** Entity observer interface.
 */
class EntityObserver {
	public:
		/** Called when property is created.
		 * @param property New property.
		 * @param entity Entity (this).
		 */
		virtual void on_property_create( cs::Property& property, cs::Entity& entity ) = 0;
};


}
