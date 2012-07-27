#include <FWCS/System.hpp>
#include <FWCS/Controller.hpp>

namespace cs {

System::System()
{
}

System::~System() {
	for( std::size_t controller_idx = 0; controller_idx < m_controllers.size(); ++controller_idx ) {
		delete m_controllers[controller_idx];
	}
}

std::size_t System::get_num_entities() const {
	return 0;
}

std::size_t System::get_num_controllers() const {
	return m_controllers.size();
}

}
