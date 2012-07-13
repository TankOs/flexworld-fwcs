#include <cassert>

namespace cs {

template <class PropType>
void Entity::create_property() {
	assert( has_property<PropType>() == false );

	// Instantiate to get the ID.
	PropType property;

	m_properties[property.get_id()] = new PropType;
}

template <class PropType>
bool Entity::has_property() const {
	// Instantiate to get the ID.
	PropType property;

	return m_properties.find( property.get_id() ) != m_properties.end();
}

}
