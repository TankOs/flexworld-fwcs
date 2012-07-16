#include <FWCS/Properties/Position.hpp>

namespace cs {
namespace prop {

const std::string Position::ID = "position";

Position::Position() :
	Property(),
	m_position( 0.0f, 0.0f, 0.0f )
{
}

const std::string& Position::get_id() const {
	return ID;
}

void Position::set_position( const sf::Vector3f& position ) {
	m_position = position;
}

const sf::Vector3f& Position::get_position() const {
	return m_position;
}

}
}
