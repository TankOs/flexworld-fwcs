namespace cs {

template <class T>
void System::create_factory() {
#ifndef NDEBUG
	for( auto& factory : m_factories ) {
		auto downcasted_factory = dynamic_cast<ExecutorFactory<T>*>( factory.get() );
		assert( downcasted_factory == nullptr );
	}
#endif

	std::unique_ptr<BaseExecutorFactory> factory{ new ExecutorFactory<T>{} };

	m_factories.push_back( std::move( factory ) );
}

}
