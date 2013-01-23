#include <FWCS/Controllers/Move.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <iostream>

namespace cs {
namespace ctrl {

const ControllerRequirements& Move::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<sf::Vector3f>(
		"position", true
	).require_property<sf::Vector3f>(
		"velocity", true
	);

	return req;
}

Move::Move( Entity& entity ) :
	Controller( entity ),
	m_position{ entity.find_property<sf::Vector3f>( "position" ) },
	m_velocity{ entity.find_property<sf::Vector3f>( "velocity" ) }
{
	assert( m_position != nullptr );
	assert( m_velocity != nullptr );
}

void Move::execute( const sf::Time& sim_time ) {
	float seconds = sim_time.asSeconds();

	m_position->x += m_velocity->x * seconds;
	m_position->y += m_velocity->y * seconds;
	m_position->z += m_velocity->z * seconds;
}

}
}
