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

	EntityMap::iterator ent_iter = m_entities.begin();
	EntityMap::iterator ent_iter_end = m_entities.end();
	
	for( ; ent_iter != ent_iter_end; ++ent_iter ) {
		delete ent_iter->second;
	}
}

std::size_t System::get_num_entities() const {
	return m_entities.size();
}

std::size_t System::get_num_controllers() const {
	return m_controllers.size();
}

Entity& System::create_entity( EntityID id ) {
	assert( m_entities.find( id ) == m_entities.end() );

	Entity* new_entity = new Entity( id );
	new_entity->set_observer( *this );

	m_entities[id] = new_entity;

	link_entity( *new_entity );

	return *new_entity;
}

void System::on_property_create( Property& /*property*/, Entity& entity ) {
	assert( find_entity( entity.get_id() ) == &entity );

	link_entity( entity );
}

Entity* System::find_entity( EntityID id ) const {
	EntityMap::const_iterator ent_iter = m_entities.find( id );

	return (ent_iter == m_entities.end() ? nullptr : ent_iter->second);
}

void System::delete_entity( EntityID id ) {
	assert( find_entity( id ) != nullptr );

	EntityMap::iterator ent_iter = m_entities.find( id );

	delete ent_iter->second;
	m_entities.erase( ent_iter );
}

void System::link_entity( Entity& entity ) {
	assert( find_entity( entity.get_id() ) == &entity );

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

}
