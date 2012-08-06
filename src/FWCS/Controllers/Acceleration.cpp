#include <FWCS/Controllers/Acceleration.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Acceleration::Acceleration() :
	Controller()
{
	listen_for( "Moveable" );
}

void Acceleration::update_entity( Entity& entity, const sf::Time& delta ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();

	moveable_property.set_velocity(
		sf::Vector3f(
			moveable_property.get_velocity().x + (moveable_property.get_acceleration().x * delta.asSeconds()),
			moveable_property.get_velocity().y + (moveable_property.get_acceleration().y * delta.asSeconds()),
			moveable_property.get_velocity().z + (moveable_property.get_acceleration().z * delta.asSeconds())
		)
	);
}

}
}
