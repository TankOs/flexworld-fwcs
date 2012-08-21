#include <cassert>

namespace cs {

template <class T>
ConcreteProperty<T>& Entity::create_property( const std::string& id, const T& initial_value ) {
	assert( m_properties.find( id ) == m_properties.end() );

	ConcreteProperty<T>* property = new ConcreteProperty<T>( initial_value );

	m_properties.insert(
		std::pair<const std::string, Property*>(
			id,
			property
		)
	);

	if( m_observer ) {
		m_observer->on_property_create( id, *this );
	}

	return *property;
}

template <class T>
ConcreteProperty<T>* Entity::find_property( const std::string& id ) {
	typename PropertyMap::iterator prop_iter = m_properties.find( id );


	if( prop_iter != m_properties.end() ) {
#ifdef NDEBUG
		ConcreteProperty<T>* ptr = reinterpret_cast<ConcreteProperty<T>*>( prop_iter->second );
#else
		ConcreteProperty<T>* ptr = dynamic_cast<ConcreteProperty<T>*>( prop_iter->second );
#endif

		return ptr;
	}
	else {
		return nullptr;
	}
}

}
