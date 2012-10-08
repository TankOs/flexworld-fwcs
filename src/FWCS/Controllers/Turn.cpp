#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <cassert>

namespace cs {
namespace ctrl {

const ControllerRequirements& Turn::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<sf::Vector3f>(
		"turn_acceleration", true
	).require_property<sf::Vector3f>(
		"turn_velocity", true
	).require_property<sf::Vector3f>(
		"rotation", true
	).require_property<sf::Vector3f>(
		"forward", true
	);

	return req;
}

Turn::Turn( Entity& entity ) :
	Controller( entity ),
	m_turn_acceleration{ entity.find_property<sf::Vector3f>( "turn_acceleration" ) },
	m_turn_velocity{ entity.find_property<sf::Vector3f>( "turn_velocity" ) },
	m_rotation{ entity.find_property<sf::Vector3f>( "rotation" ) }
{
	assert( m_turn_acceleration != nullptr );
	assert( m_turn_velocity != nullptr );
	assert( m_rotation != nullptr );
}

void Turn::execute( const sf::Time& sim_time ) {
	float sim_seconds = sim_time.asSeconds();
	assert( sim_seconds > 0.0f );

	// Angular acceleration.
	m_turn_velocity->x += m_turn_acceleration->x * sim_seconds;
	m_turn_velocity->y += m_turn_acceleration->y * sim_seconds;
	m_turn_velocity->z += m_turn_acceleration->z * sim_seconds;

	// Reset turn acceleration.
	m_turn_acceleration->x = 0.0f;
	m_turn_acceleration->y = 0.0f;
	m_turn_acceleration->z = 0.0f;

	// Apply velocity.
	m_rotation->x += m_turn_velocity->x * sim_seconds;
	m_rotation->y += m_turn_velocity->y * sim_seconds;
	m_rotation->z += m_turn_velocity->z * sim_seconds;
}

}
}
