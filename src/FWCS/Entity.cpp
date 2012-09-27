#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {

Entity::Entity() :
	m_observer( nullptr )
{
}

Entity::~Entity() {
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

}
