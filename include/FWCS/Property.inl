#include <typeinfo>

namespace cs {

template <class T>
ConcreteProperty<T>::ConcreteProperty( const T& initial_value ) :
	Property(),
	data{ initial_value }
{
}

template <class T>
const std::string& ConcreteProperty<T>::get_type_id() const {
	static std::string type_id = typeid( T ).name();

	return type_id;
}

}
