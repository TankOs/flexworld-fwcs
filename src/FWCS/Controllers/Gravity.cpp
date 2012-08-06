#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Gravity::Gravity( float gravity ) :
	m_gravity( gravity )
{
	listen_for( "Moveable" );
}

void Gravity::set_gravity( float gravity ) {
	m_gravity = gravity;
}

float Gravity::get_gravity() const {
	return m_gravity;
}

void Gravity::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();

	moveable_property.set_force(
		sf::Vector3f(
			moveable_property.get_force().x,
			moveable_property.get_force().y + (
				moveable_property.get_mass() * m_gravity
			),
			moveable_property.get_force().z
		)
	);
}

}
}
