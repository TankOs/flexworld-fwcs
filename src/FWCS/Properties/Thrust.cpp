#include <FWCS/Properties/Thrust.hpp>

namespace cs {
namespace prop {

const std::string Thrust::ID = "Thrust";

Thrust::Thrust() :
	m_thrust( 0, 0, 0 )
{
}

const std::string& Thrust::get_id() const {
	return ID;;
}

const sf::Vector3f& Thrust::get_thrust() const {
	return m_thrust;
}


}
}
