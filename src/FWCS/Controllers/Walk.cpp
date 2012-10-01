#include <FWCS/Controllers/Walk.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Math.hpp>

#include <SFML/System/Time.hpp>
#include <cmath>
#include <cassert>
#include <iostream> // XXX 

namespace cs {
namespace ctrl {

const ControllerRequirements& Walk::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<float>(
		"walk_acceleration", true
	).require_property<float>(
		"walk_max_velocity", true
	).require_property<float>(
		"walk_forward_control", true
	).require_property<float>(
		"walk_strafe_control", true
	).require_property<sf::Vector3f>(
		"forward", true
	).require_property<sf::Vector3f>(
		"acceleration", true
	).require_property<sf::Vector3f>(
		"velocity", true
	);

	return req;
}

Walk::Walk( Entity& entity ) :
	Controller( entity ),
	m_forward{ entity.find_property<sf::Vector3f>( "forward" ) },
	m_acceleration{ entity.find_property<sf::Vector3f>( "acceleration" ) },
	m_velocity{ entity.find_property<sf::Vector3f>( "velocity" ) },
	m_walk_acceleration{ entity.find_property<float>( "walk_acceleration" ) },
	m_walk_max_velocity{ entity.find_property<float>( "walk_max_velocity" ) },
	m_walk_forward_control{ entity.find_property<float>( "walk_forward_control" ) },
	m_walk_strafe_control{ entity.find_property<float>( "walk_strafe_control" ) }
{
	assert( m_forward != nullptr );
	assert( m_acceleration != nullptr );
	assert( m_velocity != nullptr );
	assert( m_walk_acceleration != nullptr );
	assert( m_walk_max_velocity != nullptr );
	assert( m_walk_forward_control != nullptr );
	assert( m_walk_strafe_control != nullptr );
}

void Walk::execute( const sf::Time& sim_time ) {
	assert( m_forward->x != 0.0f || m_forward->y != 0.0f || m_forward->z != 0.0f );
	assert( *m_walk_forward_control >= -1.0f && *m_walk_forward_control <= 1.0f );
	assert( *m_walk_strafe_control >= -1.0f && *m_walk_strafe_control <= 1.0f );
	assert( calc_length( *m_forward ) <= 1.0f );

	// Calculate target velocity vector.
	sf::Vector3f target_velocity;

	if( *m_walk_forward_control == 0.0f && *m_walk_strafe_control == 0.0f ) {
		// No movement commanded, slowdown.

		if( m_velocity->x == 0.0f && m_velocity->y == 0.0f && m_velocity->z == 0.0f ) {
			// If there's no velocity, we don't need to slowdown. Just cancel.
			return;
		}

		// Target velocity is 0,0,0 = STOP.
		target_velocity.x = 0.0f;
		target_velocity.y = 0.0f;
		target_velocity.z = 0.0f;
	}
	else {
		// Calculate walk forward vector.
		sf::Vector3f walk_forward(
			m_forward->x * (*m_walk_forward_control),
			m_forward->y * (*m_walk_forward_control),
			m_forward->z * (*m_walk_forward_control)
		);

		// Add strafe component.
		static const float rad_90 = 90.0f * PI / 180.0f;

		walk_forward.x += (m_forward->x * std::cos( rad_90 ) - m_forward->z * std::sin( rad_90 )) * (*m_walk_strafe_control);
		walk_forward.z += (m_forward->x * std::sin( rad_90 ) + m_forward->z * std::cos( rad_90 )) * (*m_walk_strafe_control);

		normalize( walk_forward );

		// Target velocity is maximum possible velocity in the walk direction.
		target_velocity.x = walk_forward.x * (*m_walk_max_velocity);
		target_velocity.y = walk_forward.y * (*m_walk_max_velocity);
		target_velocity.z = walk_forward.z * (*m_walk_max_velocity);
	}

	// Calculate acceleration vector (direction and value needed as acceleration
	// to get to the target velocity).
	sf::Vector3f accel = sf::Vector3f(
		target_velocity.x - m_velocity->x,
		target_velocity.y - m_velocity->y,
		target_velocity.z - m_velocity->z
	);

	// Calculate length of acceleration vector to know how much we have to
	// accelerate to match the target velocity. This is of course limited by the
	// controller's maximum acceleration.
	float accel_diff = std::min( *m_walk_acceleration, calc_length( accel ) );

	if( accel_diff == 0.0f ) {
		// No action required.
		return;
	}

	// Calculate final acceleration vector.
	normalize( accel );
	accel.x *= accel_diff;
	accel.y *= accel_diff;
	accel.z *= accel_diff;

	// Accelerate! (We can't accelerate further than the controller's maximum acceleration.)
	m_acceleration->x = std::min( m_acceleration->x + accel.x, accel.x );
	m_acceleration->y = std::min( m_acceleration->y + accel.y, accel.y );
	m_acceleration->z = std::min( m_acceleration->z + accel.z, accel.z );
}

}
}
