#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <iostream>

namespace cs {
namespace ctrl {

const ControllerRequirements& Turn::get_requirements() {
	static const auto req = ControllerRequirements(
	).require_property<util::FloatQuaternion>(
		"rotation", true
	).require_property<sf::Vector3f>(
		"angular_velocity", true
	).require_property<Constraint*>(
		"turn_constraint", true
	);

	return req;
}

Turn::Turn( Entity& entity ) :
	Controller( entity ),
	m_rotation{ entity.find_property<util::FloatQuaternion>( "rotation" ) },
	m_angular_velocity{ entity.find_property<sf::Vector3f>( "angular_velocity" ) },
	m_turn_constraint{ entity.find_property<Constraint*>( "turn_constraint" ) },
	m_forward_vector{ entity.find_property<sf::Vector3f>( "forward_vector" ) }
{
	assert( m_rotation != nullptr );
	assert( m_angular_velocity != nullptr );
	assert( m_turn_constraint != nullptr );

#ifndef NDEBUG
	std::cout << "Turn controller attached to entity #" << entity.get_id() << std::endl;
#endif
}

void Turn::execute( const sf::Time& sim_time ) {
	(*m_turn_constraint)->update_rotation( *m_rotation, *m_angular_velocity, sim_time );

	m_rotation->normalize();

	if( m_forward_vector != nullptr ) {
		static const sf::Vector3f DEFAULT_FORWARD_VECTOR{ 0.0f, 0.0f, -1.0f };
		*m_forward_vector = *m_rotation * DEFAULT_FORWARD_VECTOR;
		util::normalize( *m_forward_vector );
	}

}

Turn::Constraint::~Constraint() {
}

}
}
