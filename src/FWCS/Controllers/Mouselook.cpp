#include <FWCS/Controllers/Mouselook.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <cassert>

namespace cs {
namespace ctrl {

const ControllerRequirements& Mouselook::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<sf::Vector2f>(
		"mlook_delta", true
	).require_property<float>(
		"mlook_angular_acceleration", true
	).require_property<sf::Vector3f>(
		"angular_velocity", true
	);

	return req;
}

Mouselook::Mouselook( Entity& entity ) :
	Controller( entity ),
	m_mlook_delta{ entity.find_property<sf::Vector2f>( "mlook_delta" ) },
	m_mlook_angular_acceleration{ entity.find_property<float>( "mlook_angular_acceleration" ) },
	m_angular_velocity{ entity.find_property<sf::Vector3f>( "angular_velocity" ) }
{
	assert( m_mlook_delta != nullptr );
	assert( m_mlook_angular_acceleration != nullptr );
	assert( m_angular_velocity != nullptr );
}

void Mouselook::execute( const sf::Time& sim_time ) {
	float sim_seconds = sim_time.asSeconds();
	const float max_brake_velocity = *m_mlook_angular_acceleration * sim_seconds;

	// Clamp deltas.
	sf::Vector2f clamped_delta{
		std::min( 1.0f, std::max( -1.0f, m_mlook_delta->x ) ),
		std::min( 1.0f, std::max( -1.0f, m_mlook_delta->y ) )
	};

	// Accelerate.
	m_angular_velocity->x += sim_seconds * clamped_delta.y * *m_mlook_angular_acceleration;
	m_angular_velocity->y += sim_seconds * clamped_delta.x * *m_mlook_angular_acceleration;

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
	m_mlook_delta->x = 0.0f;
	m_mlook_delta->y = 0.0f;
}

}
}
