#include <cassert>

namespace cs {

template <class PropType>
void Entity::create_property() {
	assert( has_property( PropType::ID ) == false );

	m_properties[PropType::ID] = new PropType;

	if( m_observer ) {
		m_observer->on_property_create( *m_properties[PropType::ID], *this );
	}
}

template <class PropType>
const PropType& Entity::get_property() const {
	PropertyMap::const_iterator prop_iter = m_properties.find( PropType::ID );
	assert( prop_iter != m_properties.end() );

	const PropType* property = dynamic_cast<const PropType*>( prop_iter->second );
	assert( property != nullptr );

	return *property;
}

template <class PropType>
PropType& Entity::get_property() {
	PropertyMap::iterator prop_iter = m_properties.find( PropType::ID );
	assert( prop_iter != m_properties.end() );

	PropType* property = dynamic_cast<PropType*>( prop_iter->second );
	assert( property != nullptr );

	return *property;
}

}
