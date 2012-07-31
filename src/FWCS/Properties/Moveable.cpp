#include <FWCS/Properties/Moveable.hpp>

namespace cs {
namespace prop {

const std::string Moveable::ID = "Moveable";

Moveable::Moveable() :
	Property(),
	m_velocity( 0, 0, 0 ),
	m_acceleration( 0, 0, 0 ),
	m_force( 0, 0, 0 ),
	m_mass( 0 )
{
}

const std::string& Moveable::get_id() const {
	return ID;
}

const sf::Vector3f& Moveable::get_velocity() const {
	return m_velocity;
}

const sf::Vector3f& Moveable::get_acceleration() const {
	return m_acceleration;
}

const sf::Vector3f& Moveable::get_force() const {
	return m_force;
}

float Moveable::get_mass() const {
	return m_mass;
}

void Moveable::set_velocity( const sf::Vector3f& velocity ) {
	m_velocity = velocity;
}

void Moveable::set_acceleration( const sf::Vector3f& acceleration ) {
	m_acceleration = acceleration;
}

void Moveable::set_force( const sf::Vector3f& force ) {
	m_force = force;
}

void Moveable::set_mass( float mass ) {
	m_mass = mass;
}

}
}
