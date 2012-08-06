#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

namespace cs {
namespace ctrl {

MovementForceTransform::MovementForceTransform() :
	Controller()
{
	listen_for( "Moveable" );
}

void MovementForceTransform::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();

	moveable_property.set_acceleration(
		sf::Vector3f(
			moveable_property.get_force().x / moveable_property.get_mass(),
			moveable_property.get_force().y / moveable_property.get_mass(),
			moveable_property.get_force().z / moveable_property.get_mass()
		)
	);
}

}
}
