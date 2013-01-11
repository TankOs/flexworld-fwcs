#include <FWCS/Controllers/LookAt.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Quaternion.hpp>
#include <FWU/Math.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <iostream>

namespace cs {
namespace ctrl {

const ControllerRequirements& LookAt::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<sf::Vector3f>(
		"position", true
	).require_property<sf::Vector3f>(
		"forward_vector", true
	).require_property<sf::Vector3f>(
		"up_vector", true
	).require_property<sf::Vector3f>(
		"angular_velocity", true
	).require_property<sf::Vector3f>(
		"look_at_position", true
	).require_property<float>(
		"look_at_acceleration", true
	).require_property<float>(
		"max_look_at_velocity", true
	);

	return req;
}

LookAt::LookAt( Entity& entity ) :
	Controller( entity ),
	m_position{ entity.find_property<sf::Vector3f>( "position" ) },
	m_forward_vector{ entity.find_property<sf::Vector3f>( "forward_vector" ) },
	m_up_vector{ entity.find_property<sf::Vector3f>( "up_vector" ) },
	m_angular_velocity{ entity.find_property<sf::Vector3f>( "angular_velocity" ) },
	m_look_at_position{ entity.find_property<sf::Vector3f>( "look_at_position" ) },
	m_look_at_acceleration{ entity.find_property<float>( "look_at_acceleration" ) },
	m_max_look_at_velocity{ entity.find_property<float>( "max_look_at_velocity" ) }
{
	assert( m_position != nullptr );
	assert( m_forward_vector != nullptr );
	assert( m_up_vector != nullptr );
	assert( m_angular_velocity != nullptr );
	assert( m_look_at_position != nullptr );
	assert( m_look_at_acceleration != nullptr );
	assert( m_max_look_at_velocity != nullptr );

#ifndef NDEBUG
	std::cout << "LookAt controller attached to entity #" << entity.get_id() << std::endl;
#endif
}

void LookAt::execute( const sf::Time& sim_time ) {
	float sim_seconds = sim_time.asSeconds();

	// Calculate look at forward unit vector.
	sf::Vector3f look_at_vector = *m_look_at_position - *m_position;
	util::normalize( look_at_vector );

	// If vectors are equal, there's nothing to do.
	if( *m_forward_vector == look_at_vector ) {
		return;
	}

	// Calculate rotation axis. If vectors are opposite, use up vector as
	// rotation axis.
	sf::Vector3f rot_axis = (
		*m_forward_vector == util::inverse( look_at_vector ) ?
		*m_up_vector :
		util::cross_product( *m_forward_vector, look_at_vector )
	);

	if( util::length( rot_axis ) == 0.0f ) {
		return;
	}

	util::normalize( rot_axis );

	// Calculate angle.
	float angle = std::acos( util::dot_product( *m_forward_vector, look_at_vector ) );

	// Convert to Euler angles.
	sf::Vector3f euler_angles = util::angle_axis_to_euler( angle, rot_axis );

	// Calculate target angular velocity vector.
	sf::Vector3f target_velocity{
		(euler_angles.x - m_angular_velocity->x) / sim_seconds,
		(euler_angles.y - m_angular_velocity->y) / sim_seconds,
		(euler_angles.z - m_angular_velocity->z) / sim_seconds
	};

	// If no velocity needed, cancel.
	if(
		target_velocity.x == 0.0f &&
		target_velocity.y == 0.0f &&
		target_velocity.z == 0.0f
	) {
		return;
	}

	// Calculate acceleration.
	sf::Vector3f acceleration = target_velocity;

	util::normalize( acceleration );
	acceleration *= std::min( util::length( target_velocity ), *m_look_at_acceleration );

	*m_angular_velocity += acceleration * sim_seconds;
}

}
}
