#include <FWCS/Properties/Position.hpp>

namespace cs {
namespace prop {

Position::Position() :
	Property(),
	m_position( 0.0f, 0.0f, 0.0f )
{
}

const std::string& Position::get_id() const {
	static const std::string ID = "position";
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
