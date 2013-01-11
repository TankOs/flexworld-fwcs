#include <FWCS/Controllers/Mouselook.hpp>
#include <FWCS/Entity.hpp>

#include <FWU/Math.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <cassert>
#include <cmath>

namespace cs {
namespace ctrl {

const ControllerRequirements& Mouselook::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<sf::Vector2f>(
		"mouselook_control", true
	).require_property<float>(
		"max_mouselook_angular_velocity", true
	).require_property<float>(
		"mouselook_angular_acceleration", true
	).require_property<float>(
		"mouselook_angular_deceleration", true
	).require_property<sf::Vector3f>(
		"angular_velocity", true
	);

	return req;
}

Mouselook::Mouselook( Entity& entity ) :
	Controller( entity ),
	m_mouselook_control{ entity.find_property<sf::Vector2f>( "mouselook_control" ) },
	m_max_mouselook_angular_velocity{ entity.find_property<float>( "max_mouselook_angular_velocity" ) },
	m_mouselook_angular_acceleration{ entity.find_property<float>( "mouselook_angular_acceleration" ) },
	m_mouselook_angular_deceleration{ entity.find_property<float>( "mouselook_angular_deceleration" ) },
	m_angular_velocity{ entity.find_property<sf::Vector3f>( "angular_velocity" ) }
{
	assert( m_max_mouselook_angular_velocity != nullptr );
	assert( m_mouselook_control != nullptr );
	assert( m_mouselook_angular_acceleration != nullptr );
	assert( m_angular_velocity != nullptr );

#ifndef NDEBUG
	std::cout << "Mouselook controller attached to entity #" << entity.get_id() << std::endl;
#endif
}

void Mouselook::execute( const sf::Time& sim_time ) {
	float sim_seconds = sim_time.asSeconds();

	float control_length = util::length( *m_mouselook_control );

	if( control_length > 1.0f ) {
		util::normalize( *m_mouselook_control );
		control_length = 1.0f;
	}

	// Calculate velocity difference, i.e. velocity that we need to accelerate
	// to.
	sf::Vector2f target_velocity{
		(-m_mouselook_control->y * *m_max_mouselook_angular_velocity) - m_angular_velocity->x,
		(-m_mouselook_control->x * *m_max_mouselook_angular_velocity) - m_angular_velocity->y,
	};

	// Choose to accelerate or decelerate.
	sf::Vector2f acceleration{
		m_angular_velocity->x != 0.0f &&
		(util::sign( target_velocity.x ) != util::sign( m_angular_velocity->x ))
			? *m_mouselook_angular_deceleration
			: *m_mouselook_angular_acceleration ,
		m_angular_velocity->y != 0.0f &&
		(util::sign( target_velocity.y ) != util::sign( m_angular_velocity->y ))
			? *m_mouselook_angular_deceleration
			: *m_mouselook_angular_acceleration
	};

	// Calculate required acceleration that's needed, limited by maximum acceleration.
	sf::Vector2f target_acceleration{
		std::min( std::abs( target_velocity.x ) / sim_seconds, acceleration.x ) * util::sign( target_velocity.x ),
		std::min( std::abs( target_velocity.y ) / sim_seconds, acceleration.y ) * util::sign( target_velocity.y ),
	};

	// Apply acceleration.
	m_angular_velocity->x += target_acceleration.x * sim_seconds;
	m_angular_velocity->y += target_acceleration.y * sim_seconds;

	/*
	const float max_brake_velocity = (m_mouselook_angular_deceleration != nullptr ? *m_mouselook_angular_deceleration : *m_mouselook_angular_acceleration) * sim_seconds;

	// Clamp deltas.
	sf::Vector2f clamped_delta{
		std::min( 1.0f, std::max( -1.0f, m_mouselook_control->x ) ),
		std::min( 1.0f, std::max( -1.0f, m_mouselook_control->y ) )
	};

	// Accelerate.
	m_angular_velocity->x += sim_seconds * clamped_delta.y * *m_mouselook_angular_acceleration;
	m_angular_velocity->y += sim_seconds * clamped_delta.x * *m_mouselook_angular_acceleration;

	// Brake.
	if( clamped_delta.x == 0.0f ) {
		if( m_angular_velocity->y > 0.0f ) {
			m_angular_velocity->y -= std::min( m_angular_velocity->y, max_brake_velocity );
		}
		else {
			m_angular_velocity->y += std::min( -m_angular_velocity->y, max_brake_velocity );
		}
	}

	if( clamped_delta.y == 0.0f ) {
		if( m_angular_velocity->x > 0.0f ) {
			m_angular_velocity->x -= std::min( m_angular_velocity->x, max_brake_velocity );
		}
		else {
			m_angular_velocity->x += std::min( -m_angular_velocity->x, max_brake_velocity );
		}
	}


	// Reset delta.
	m_mouselook_control->x = 0.0f;
	m_mouselook_control->y = 0.0f;
	*/
}

}
}
