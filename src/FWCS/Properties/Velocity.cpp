#include <FWCS/Properties/Velocity.hpp>

namespace cs {
namespace prop {

Velocity::Velocity() :
	Property(),
	m_velocity( 0.0f, 0.0f, 0.0f )
{
}

const std::string& Velocity::get_id() const {
	static const std::string ID = "velocity";
	return ID;
}

void Velocity::set_velocity( const sf::Vector3f& velocity ) {
	m_velocity = velocity;
}

const sf::Vector3f& Velocity::get_velocity() const {
	return m_velocity;
}

}
}
