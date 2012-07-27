#include <cassert>

namespace cs {

template <class ControllerType>
void System::create_controller( const ControllerType& tpl ) {
	assert( has_controller<ControllerType>() == false );

	m_controllers.push_back( new ControllerType( tpl ) );
}

template <class ControllerType>
bool System::has_controller() {
	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {
		if( dynamic_cast<ControllerType*>( m_controllers[controller_idx] ) != nullptr ) {
			return true;
		}
	}

	return false;
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
