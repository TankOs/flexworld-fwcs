#include <cassert>

namespace cs {

template <class ControllerType>
ControllerType& System::create_controller() {
	assert( find_controller<ControllerType>() == nullptr );

	ControllerType* controller = new ControllerType;
	m_controllers.push_back( controller );

	// Link all entities.
	EntityMap::iterator ent_iter = m_entities.begin();
	EntityMap::iterator ent_iter_end = m_entities.end();
	
	for( ; ent_iter != ent_iter_end; ++ent_iter ) {
		if( controller->is_entity_interesting( *ent_iter->second ) ) {
			controller->add_entity( *ent_iter->second );
		}
	}

	return *controller;
}

template <class ControllerType>
ControllerType* System::find_controller() const {
	ControllerType* controller = nullptr;

	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {
		controller = dynamic_cast<ControllerType*>( m_controllers[controller_idx] );

		if( controller != nullptr ) {
			return controller;
		}
	}

	return nullptr;
}

template <class ControllerType>
void System::delete_controller() {
	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {

		if( dynamic_cast<ControllerType*>( m_controllers[controller_idx] ) != nullptr ) {
			// Found, delete.
			delete m_controllers[controller_idx];
			m_controllers.erase( m_controllers.begin() + controller_idx );
			return;
		}

	}

	assert( false && "Controller not found." );
}

}
