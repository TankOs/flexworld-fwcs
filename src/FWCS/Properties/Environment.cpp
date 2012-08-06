#include <FWCS/Properties/Environment.hpp>

namespace cs {
namespace prop {

const std::string Environment::ID = "Environment";

Environment::Environment() :
	Property(),
	m_air_density( 1.275f ),
	m_gravity( -9.80665f )
{
}

const std::string& Environment::get_id() const {
	return ID;
}

float Environment::get_gravity() const {
	return m_gravity;
}

float Environment::get_air_density() const {
	return m_air_density;
}

void Environment::set_gravity( float gravity ) {
	m_gravity = gravity;
}

void Environment::set_air_density( float air_density ) {
	m_air_density = air_density;
}

}
}
