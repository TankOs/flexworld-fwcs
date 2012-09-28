#include <utility>

namespace cs {

template <class T>
ExecutorFactory<T>::ExecutorFactory() :
	BaseExecutorFactory()
{
}

template <class T>
ExecutorFactory<T>::~ExecutorFactory() {
}

template <class T>
std::unique_ptr<Executor> ExecutorFactory<T>::create_executor( Entity& entity ) {
	return std::move( std::unique_ptr<Executor>( new T{ entity } ) );
}

template <class T>
const ExecutorRequirements& ExecutorFactory<T>::get_requirements() const {
	return T::get_requirements();
}

}
