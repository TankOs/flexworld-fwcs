#include <utility>

namespace cs {

template <class T>
ExecutorFactory<T>::ExecutorFactory() {
}

template <class T>
ExecutorFactory<T>::~ExecutorFactory() {
}

template <class T>
T ExecutorFactory<T>::create_executor() const {
	return std::move( T{} );
}

}
