#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {

Entity::Entity() :
	m_observer( nullptr )
{
}

Entity::~Entity() {
	PropertyMap::iterator prop_iter = m_properties.begin();
	PropertyMap::iterator prop_iter_end = m_properties.end();
	
	for( ; prop_iter != prop_iter_end; ++prop_iter ) {
		delete prop_iter->second;
	}
}

std::size_t Entity::get_num_properties() const {
	return m_properties.size();
}

bool Entity::has_observer() const {
	return m_observer != nullptr;
}

void Entity::set_observer( EntityObserver& observer ) {
	assert( m_observer == nullptr );

	m_observer = &observer;
}

EntityObserver& Entity::get_observer() const {
	assert( m_observer != nullptr );

	return *m_observer;
}

Property* Entity::find_base_property( const std::string& id ) {
	PropertyMap::iterator prop_iter = m_properties.find( id );
	return prop_iter == m_properties.end() ? nullptr : prop_iter->second;
}

const Property* Entity::find_base_property( const std::string& id ) const {
	PropertyMap::const_iterator prop_iter = m_properties.find( id );
	return prop_iter == m_properties.end() ? nullptr : prop_iter->second;
}

}
