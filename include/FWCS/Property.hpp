#pragma once

#include <string>

namespace cs {

/** Property.
 * Base class for properties with custom data.
 *
 * Properties are attached to entities. They can provide data and be writable.
 */
class Property {
	public:
		/** Dtor.
		 */
		virtual ~Property();

		/** Get property ID.
		 * @return ID.
		 */
		virtual const std::string& get_id() const = 0;

	private:
};

}
