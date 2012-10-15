#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Quaternion.hpp>
#include <FWU/Math.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <cmath>

namespace cs {
namespace ctrl {

#ifndef NDEBUG
	static const float TOLERANCE = 0.001f;
#endif

const ControllerRequirements& Turn::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<sf::Vector3f>(
		"turn_acceleration", true
	).require_property<sf::Vector3f>(
		"turn_velocity", true
	).require_property<sf::Vector3f>(
		"forward", true
	);

	return req;
}

Turn::Turn( Entity& entity ) :
	Controller( entity ),
	m_turn_acceleration{ entity.find_property<sf::Vector3f>( "turn_acceleration" ) },
	m_turn_velocity{ entity.find_property<sf::Vector3f>( "turn_velocity" ) },
	m_forward{ entity.find_property<sf::Vector3f>( "forward" ) }
{
	assert( m_turn_acceleration != nullptr );
	assert( m_turn_velocity != nullptr );
	assert( m_forward != nullptr );
}

void Turn::execute( const sf::Time& sim_time ) {
	float sim_seconds = sim_time.asSeconds();
	assert( sim_seconds > 0.0f );
	assert( std::abs( util::calc_length( *m_forward ) - 1.0f ) <= TOLERANCE );

	// Accelerate.
	m_turn_velocity->x += m_turn_acceleration->x * sim_seconds;
	m_turn_velocity->y += m_turn_acceleration->y * sim_seconds;
	m_turn_velocity->z += m_turn_acceleration->z * sim_seconds;

	// Make quaternion.
	util::FloatQuaternion quat =
		util::FloatQuaternion::from_angle_axis( m_turn_velocity->x * sim_seconds, sf::Vector3f( 1.0f, 0.0f, 0.0f ) ) *
		util::FloatQuaternion::from_angle_axis( m_turn_velocity->y * sim_seconds, sf::Vector3f( 0.0f, 1.0f, 0.0f ) ) *
		util::FloatQuaternion::from_angle_axis( m_turn_velocity->z * sim_seconds, sf::Vector3f( 0.0f, 0.0f, 1.0f ) )
	;

	// Rotate vector.
	*m_forward = quat * (*m_forward);
	util::normalize( *m_forward );

	// Reset acceleration.
	m_turn_acceleration->x = 0.0f;
	m_turn_acceleration->y = 0.0f;
	m_turn_acceleration->z = 0.0f;
}

}
}
