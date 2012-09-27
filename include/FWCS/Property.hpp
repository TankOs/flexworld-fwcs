#pragma once

#include <string>

namespace cs {

/** Property.
 * Baseclass for concrete properties with a specific type. Used internally.
 */
class Property {
	public:
		/** Dtor.
		 */
		virtual ~Property();

		/** Get type ID.
		 * This value is compiler-dependent!
		 * @return Type ID.
		 */
		virtual const std::string& get_type_id() const = 0;
};

/** Concrete property, i.e. fixed value type.
 * @tparam T Value type.
 */
template <class T>
class ConcreteProperty : public Property {
	public:
		/** Ctor.
		 * @param initial_value Initial value.
		 */
		ConcreteProperty( const T& initial_value = T() );

		const std::string& get_type_id() const;

		T data; ///< Data.

	private:
};

}

#include "Property.inl"
