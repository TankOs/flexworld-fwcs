#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {

Entity::Entity() :
	m_observer( nullptr ),
	m_id( 0 )
{
}

Entity::~Entity() {
}

Entity::Entity( Entity&& other ) noexcept :
	m_properties{ std::move( other.m_properties ) },
	m_observer{ std::move( other.m_observer ) },
	m_id{ std::move( other.m_id ) }
{
}

Entity& Entity::operator=( Entity&& other ) noexcept {
	m_properties = std::move( other.m_properties );
	m_observer = std::move( other.m_observer );
	m_id = std::move( other.m_id );

	return *this;
}

void Entity::set_id( EntityID id ) {
	m_id = id;
}

EntityID Entity::get_id() const {
	return m_id;
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
