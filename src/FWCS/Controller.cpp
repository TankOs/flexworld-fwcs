#include <FWCS/Controller.hpp>
#include <FWCS/Entity.hpp>

#include <algorithm>
#include <cassert>

namespace cs {

Controller::Controller() {
}

Controller::~Controller() {
}

const Controller::RequiredPropertyArray& Controller::get_required_properties() const {
	return m_required_properties;
}

std::size_t Controller::get_num_linked_entities() const {
	return m_entities.size();
}

bool Controller::is_entity_interesting( const Entity& entity ) const {
	assert( m_required_properties.size() != 0 );

	const Property* base_property = nullptr;
	const IdTypePair* pair = nullptr;

	for( std::size_t prop_idx = 0; prop_idx < m_required_properties.size(); ++prop_idx ) {
		pair = &m_required_properties[prop_idx];
		base_property = entity.find_base_property( pair->first );

		if( base_property == nullptr || base_property->get_type_id() != pair->second ) {
			return false;
		}
	}

	return true;
}

void Controller::add_entity( Entity& entity ) {
	assert( is_entity_interesting( entity ) == true );

	EntityPtrArray::iterator ent_iter = std::lower_bound( m_entities.begin(), m_entities.end(), &entity );
	assert( ent_iter == m_entities.end() || *ent_iter != &entity );

	m_entities.insert( ent_iter, &entity );

	on_entity_add( entity );
}

void Controller::remove_entity( Entity& entity ) {
	EntityPtrArray::iterator ent_iter = std::lower_bound( m_entities.begin(), m_entities.end(), &entity );
	assert( ent_iter != m_entities.end() && *ent_iter == &entity );

	m_entities.erase( ent_iter );

	on_entity_remove( entity );
}

bool Controller::is_entity_linked( const Entity& entity ) {
	return std::find( m_entities.begin(), m_entities.end(), &entity ) != m_entities.end();
}

void Controller::run( const sf::Time& delta ) {
	for( std::size_t ent_idx = 0; ent_idx < m_entities.size(); ++ent_idx ) {
		update_entity( *m_entities[ent_idx], delta );
	}
}

void Controller::update_entity( Entity& /*entity*/, const sf::Time& /*delta*/ ) {
}

void Controller::on_entity_add( Entity& /*entity*/ ) {
}

void Controller::on_entity_remove( Entity& /*entity*/ ) {
}

}
