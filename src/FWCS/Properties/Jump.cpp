#include <FWCS/Properties/Jump.hpp>

namespace cs {
namespace prop {

const std::string Jump::ID = "Jump";

Jump::Jump() :
	Property(),
	m_up_vector( 0, 1, 0 ),
	m_force( 100 )
{
}

const std::string& Jump::get_id() const {
	return ID;
}

bool Jump::is_active() const {
	return m_active;
}

const sf::Vector3f& Jump::get_up_vector() const {
	return m_up_vector;
}

float Jump::get_force() const {
	return m_force;
}

void Jump::set_active( bool active ) {
	m_active = active;
}

void Jump::set_up_vector( const sf::Vector3f& up_vector ) {
	m_up_vector = up_vector;
}

void Jump::set_force( float force ) {
	m_force = force;
}

}
}
