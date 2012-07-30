#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>

namespace cs {

Entity::Entity( EntityID id ) :
	m_observer( nullptr ),
	m_id( id )
{
}

Entity::~Entity() {
	PropertyMap::iterator prop_iter = m_properties.begin();
	PropertyMap::iterator prop_iter_end = m_properties.end();
	
	for( ; prop_iter != prop_iter_end; ++prop_iter ) {
		delete prop_iter->second;
	}
}

EntityID Entity::get_id() const {
	return m_id;
}

std::size_t Entity::get_num_properties() const {
	return m_properties.size();
}

bool Entity::has_property( const std::string& property_id ) const {
	return m_properties.find( property_id ) != m_properties.end();
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

}
