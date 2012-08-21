#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controller.hpp>

namespace cs {

System::System()
{
}

System::~System() {
	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {
		delete m_controllers[controller_idx];
	}

	EntitySet::iterator ent_iter = m_entities.begin();
	EntitySet::iterator ent_iter_end = m_entities.end();
	
	for( ; ent_iter != ent_iter_end; ++ent_iter ) {
		delete *ent_iter;
	}
}

std::size_t System::get_num_entities() const {
	return m_entities.size();
}

std::size_t System::get_num_controllers() const {
	return m_controllers.size();
}

Entity& System::create_entity() {
	Entity* new_entity = new Entity;
	new_entity->set_observer( *this );

	m_entities.insert( new_entity );
	link_entity( *new_entity );

	return *new_entity;
}

void System::on_property_create( const std::string& /*id*/, Entity& entity ) {
	assert( m_entities.find( &entity ) != m_entities.end() );

	link_entity( entity );
}

void System::delete_entity( Entity& entity ) {
	EntitySet::iterator ent_iter = m_entities.find( &entity );
	assert( ent_iter != m_entities.end() );

	delete *ent_iter;
	m_entities.erase( ent_iter );
}

void System::link_entity( Entity& entity ) {
	assert( m_entities.find( &entity ) != m_entities.end() );

	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {
		Controller& controller = *m_controllers[controller_idx];

		// If already linked, check if the link is still valid.
		if( controller.is_entity_linked( entity ) ) {
			if( controller.is_entity_interesting( entity ) == false ) {
				controller.remove_entity( entity );
			}
		}
		else { // If not linked, check if a link makes sense.
			if( controller.is_entity_interesting( entity ) == true ) {
				controller.add_entity( entity );
			}
		}
	}
}

void System::run( const sf::Time& sim_time ) {
	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {
		m_controllers[controller_idx]->run( sim_time );
	}
}

}
