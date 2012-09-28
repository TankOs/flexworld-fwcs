#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controller.hpp>

namespace cs {

bool less_than( const Entity& first, const Entity& second ) {
	return first.get_id() < second.get_id();
}

System::System() :
	m_next_entity_id{ 0 }
{
}

System::~System() {
}

std::size_t System::get_num_factories() const {
	return m_factories.size();
}

std::size_t System::get_num_entities() const {
	return m_entities.size();
}

Entity& System::create_entity() {
	// Create entity and set unique ID.
	Entity ent;

	ent.set_id( m_next_entity_id );
	++m_next_entity_id;

	m_entities.push_back( std::move( ent ) );

	return m_entities.back();
}

Entity* System::find_entity( EntityID id ) {
	auto iter = std::lower_bound(
		std::begin( m_entities ),
		std::end( m_entities ),
		id,
		[]( const Entity& ent, const EntityID other_id ) -> bool { return ent.get_id() < other_id; }
	);

	return
		(iter == std::end( m_entities )) ||
		(iter->get_id() != id) ?
		nullptr :
		&*iter;
}

void System::destroy_entity( EntityID id ) {
	auto iter = std::lower_bound(
		std::begin( m_entities ),
		std::end( m_entities ),
		id,
		[]( const Entity& ent, const EntityID other_id ) -> bool { return ent.get_id() < other_id; }
	);

	assert( iter != std::end( m_entities ) );
	assert( iter->get_id() == id );

	m_entities.erase( iter );
}

}
