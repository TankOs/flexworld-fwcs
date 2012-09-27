#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controller.hpp>

namespace cs {

System::System()
{
}

System::~System() {
}

std::size_t System::get_num_factories() const {
	return m_factories.size();
}

}
