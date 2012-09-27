#include <cassert>

namespace cs {

template <class T>
T& Entity::create_property( const std::string& id, const T& initial_value ) {
	assert( m_properties.find( id ) == m_properties.end() );

	std::unique_ptr<ConcreteProperty<T>> property{ new ConcreteProperty<T>( initial_value ) };

	auto result = m_properties.insert(
		std::pair<const std::string, std::unique_ptr<Property>>(
			id,
			std::move( property )
		)
	);

	if( m_observer ) {
		m_observer->on_property_create( id, *this );
	}

	return reinterpret_cast<ConcreteProperty<T>*>( result.first->second.get() )->data;
}

template <class T>
T* Entity::find_property( const std::string& id ) {
	auto prop_iter = m_properties.find( id );

	if( prop_iter != std::end( m_properties ) ) {
#ifdef NDEBUG
		auto ptr = reinterpret_cast<ConcreteProperty<T>*>( prop_iter->second.get() );
#else
		auto ptr = dynamic_cast<ConcreteProperty<T>*>( prop_iter->second.get() );
#endif

		return &ptr->data;
	}
	else {
		return nullptr;
	}
}

template <class T>
const T* Entity::find_property( const std::string& id ) const {
	auto prop_iter = m_properties.find( id );

	if( prop_iter != std::end( m_properties ) ) {
#ifdef NDEBUG
		auto ptr = reinterpret_cast<const ConcreteProperty<T>*>( prop_iter->second.get() );
#else
		auto ptr = dynamic_cast<const ConcreteProperty<T>*>( prop_iter->second.get() );
#endif

		return &ptr->data;
	}
	else {
		return nullptr;
	}
}

}
