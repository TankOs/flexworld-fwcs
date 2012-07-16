#include <cassert>

namespace cs {

template <class PropType>
void Entity::create_property() {
	assert( has_property( PropType::ID ) == false );

	m_properties[PropType::ID] = new PropType;
}

template <class PropType>
const Property& Entity::get_property() const {
	PropertyMap::const_iterator prop_iter = m_properties.find( PropType::ID );

	assert( prop_iter != m_properties.end() );

	return *(prop_iter->second);
}

}
