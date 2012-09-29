namespace cs {

template <class T>
void System::create_factory() {
	assert( has_factory<T>() == false );

	std::unique_ptr<BaseControllerFactory> factory{ new ControllerFactory<T>{} };
	m_factories.push_back( std::move( factory ) );

	create_factory_controllers( *m_factories.back() );
}

template <class T>
bool System::has_factory() const {
	for( const auto& factory : m_factories ) {
		const auto* downcasted_factory = dynamic_cast<const ControllerFactory<T>*>( factory.get() );

		if( downcasted_factory != nullptr ) {
			return true;
		}
	}

	return false;
}

}
