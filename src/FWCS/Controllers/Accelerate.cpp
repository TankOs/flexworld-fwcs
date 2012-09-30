#include <FWCS/Controllers/Accelerate.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Math.hpp>

#include <SFML/System/Time.hpp>
#include <cassert>

namespace cs {
namespace ctrl {

const ControllerRequirements& Accelerate::get_requirements() {
	static const ControllerRequirements req = ControllerRequirements(
		).require_property<sf::Vector3f>(
			"velocity", true
		).require_property<sf::Vector3f>(
			"acceleration", true
		)
	;

	return req;
}

Accelerate::Accelerate( Entity& entity ) :
	Controller( entity ),
	m_velocity{ entity.find_property<sf::Vector3f>( "velocity" ) },
	m_acceleration{ entity.find_property<sf::Vector3f>( "acceleration" ) },
	m_max_velocity{ entity.find_property<float>( "max_velocity" ) }
{
	assert( m_velocity != nullptr );
	assert( m_acceleration != nullptr );
}

void Accelerate::execute( const sf::Time& sim_time ) {
	float seconds = sim_time.asSeconds();

	m_velocity->x += m_acceleration->x * seconds;
	m_velocity->y += m_acceleration->y * seconds;
	m_velocity->z += m_acceleration->z * seconds;

	if( m_max_velocity != nullptr ) {
		float abs_velocity = calc_length( *m_velocity );

		if( abs_velocity > *m_max_velocity ) {
			normalize( *m_velocity );

			m_velocity->x *= *m_max_velocity;
			m_velocity->y *= *m_max_velocity;
			m_velocity->z *= *m_max_velocity;
		}
	}
}

}
}
