#include <FWCS/Properties/PositionLimit.hpp>

namespace cs {
namespace prop {

const std::string PositionLimit::ID = "PositionLimit";

PositionLimit::PositionLimit() :
	Property(),
	m_upper_limit( 0, 0, 0 ),
	m_lower_limit( 0, 0, 0 )
{
}

const std::string& PositionLimit::get_id() const {
	return ID;
}

const sf::Vector3f& PositionLimit::get_upper_limit() const {
	return m_upper_limit;
}

const sf::Vector3f& PositionLimit::get_lower_limit() const {
	return m_lower_limit;
}

void PositionLimit::set_upper_limit( const sf::Vector3f& upper_limit ) {
	m_upper_limit = upper_limit;
}

void PositionLimit::set_lower_limit( const sf::Vector3f& lower_limit ) {
	m_lower_limit = lower_limit;
}

}
}
