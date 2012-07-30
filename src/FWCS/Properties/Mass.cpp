#include <FWCS/Properties/Mass.hpp>

namespace cs {
namespace prop {

const std::string Mass::ID = "mass";

Mass::Mass() :
	Property(),
	m_mass( 0.0f )
{
}

const std::string& Mass::get_id() const {
	return Mass::ID;
}

void Mass::set_mass( float mass ) {
	m_mass = mass;
}

float Mass::get_mass() const {
	return m_mass;
}

}
}
