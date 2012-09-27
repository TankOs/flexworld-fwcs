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
std::unique_ptr<Executor> ExecutorFactory<T>::create_executor() {
	return std::move( std::unique_ptr<Executor>( new T{} ) );
}

}
