#include <FWCS/Properties/Object.hpp>

namespace cs {
namespace prop {

const std::string Object::ID = "Object";

Object::Object() :
	Property(),
	m_position( 0, 0, 0 )
{
}

const std::string& Object::get_id() const {
	return ID;
}

void Object::set_position( const sf::Vector3f& position ) {
	m_position = position;
}

const sf::Vector3f& Object::get_position() const {
	return m_position;
}

}
}
