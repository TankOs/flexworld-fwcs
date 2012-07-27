#include <FWCS/Controller.hpp>
#include <FWCS/Entity.hpp>

#include <algorithm>
#include <cassert>

namespace cs {

Controller::Controller() {
}

Controller::~Controller() {
}

const std::vector<std::string>& Controller::get_required_properties() const {
	return m_required_properties;
}

std::size_t Controller::get_num_linked_entities() const {
	return m_entities.size();
}

bool Controller::is_entity_interesting( const Entity& entity ) const {
	assert( m_required_properties.size() != 0 );

	for( std::size_t prop_idx = 0; prop_idx < m_required_properties.size(); ++prop_idx ) {
		if( entity.has_property( m_required_properties[prop_idx] ) == false ) {
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
}

void Controller::remove_entity( const Entity& entity ) {
	EntityPtrArray::iterator ent_iter = std::lower_bound( m_entities.begin(), m_entities.end(), &entity );
	assert( ent_iter != m_entities.end() && *ent_iter == &entity );

	m_entities.erase( ent_iter );
}

bool Controller::is_entity_linked( const Entity& entity ) {
	return std::find( m_entities.begin(), m_entities.end(), &entity ) != m_entities.end();
}

void Controller::run( const sf::Time& delta ) {
	for( std::size_t ent_idx = 0; ent_idx < m_entities.size(); ++ent_idx ) {
		update_entity( *m_entities[ent_idx], delta );
	}
}

void Controller::listen_for( const std::string& property ) {
	assert( std::find( m_required_properties.begin(), m_required_properties.end(), property ) == m_required_properties.end() );
	assert( m_entities.size() == 0 );

	m_required_properties.push_back( property );
}

void Controller::update_entity( Entity& /*entity*/, const sf::Time& /*delta*/ ) {
}

}
