#include <utility>

namespace cs {

template <class T>
ControllerFactory<T>::ControllerFactory() :
	BaseControllerFactory()
{
}

template <class T>
ControllerFactory<T>::~ControllerFactory() {
}

template <class T>
std::unique_ptr<Controller> ControllerFactory<T>::create_controller( Entity& entity ) {
	return std::move( std::unique_ptr<Controller>( new T{ entity } ) );
}

template <class T>
const ControllerRequirements& ControllerFactory<T>::get_requirements() const {
	return T::get_requirements();
}

}
