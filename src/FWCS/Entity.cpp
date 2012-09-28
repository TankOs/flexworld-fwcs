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
	m_observer{ other.m_observer },
	m_id{ other.m_id }
{
	other.m_observer = nullptr;
	other.m_id = 0;
}

Entity& Entity::operator=( Entity&& other ) noexcept {
	m_properties = std::move( other.m_properties );
	m_observer = other.m_observer;
	m_id = other.m_id;

	other.m_properties.clear();
	other.m_observer = nullptr;
	other.m_id = 0;

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

void Entity::set_observer( EntityObserver& observer ) {
	assert( m_observer == nullptr );

	m_observer = &observer;
}

EntityObserver* Entity::get_observer() const {
	return m_observer;
}

bool Entity::has_property( const std::string& id, const std::string& type ) const {
	auto iter = m_properties.find( id );

	if( iter == std::end( m_properties ) ) {
		return false;
	}

	return iter->second->get_type_id() == type;
}

}
