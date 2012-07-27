#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Properties/Velocity.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>
#include <iostream> // XXX 

namespace cs {
namespace ctl {

Gravity::Gravity( float gravity ) :
	m_gravity( gravity )
{
	listen_for( "velocity" );
}

float Gravity::get_gravity() const {
	return m_gravity;
}

void Gravity::update_entity( Entity& entity, const sf::Time& delta ) {
	prop::Velocity& velocity = entity.get_property<prop::Velocity>();

	velocity.set_velocity(
		sf::Vector3f(
			velocity.get_velocity().x,
			velocity.get_velocity().y + m_gravity * delta.asSeconds(),
			velocity.get_velocity().z
		)
	);
}

}
}
