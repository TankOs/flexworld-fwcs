#include <cassert>

namespace cs {

template <class PropType>
PropType& Entity::create_property() {
	assert( find_property<PropType>() == nullptr );

	PropType* new_property = new PropType;
	m_properties[PropType::ID] = new_property;

	if( m_observer ) {
		m_observer->on_property_create( *new_property, *this );
	}

	return *new_property;
}

template <class PropType>
PropType* Entity::find_property() const {
	PropertyMap::const_iterator prop_iter = m_properties.find( PropType::ID );

	if( prop_iter == m_properties.end() ) {
		return nullptr;
	}

	PropType* property = dynamic_cast<PropType*>( prop_iter->second );
	assert( property != nullptr );

	return property;
}

}
