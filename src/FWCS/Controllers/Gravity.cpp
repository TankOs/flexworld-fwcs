#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Environment.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Gravity::Gravity() :
	Controller()
{
	listen_for( "Moveable" );
	listen_for( "Environment" );
}

void Gravity::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();
	prop::Environment& environment_property = *entity.find_property<prop::Environment>();

	moveable_property.set_force(
		sf::Vector3f(
			moveable_property.get_force().x,
			moveable_property.get_force().y + (
				moveable_property.get_mass() * environment_property.get_gravity()
			),
			moveable_property.get_force().z
		)
	);
}

}
}
