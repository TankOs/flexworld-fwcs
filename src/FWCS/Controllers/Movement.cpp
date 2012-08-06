#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Movement::Movement() :
	Controller()
{
	listen_for( "Moveable" );
	listen_for( "Object" );
}

void Movement::update_entity( Entity& entity, const sf::Time& delta ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();
	prop::Object& object_property = *entity.find_property<prop::Object>();

	object_property.set_position(
		sf::Vector3f(
			object_property.get_position().x + (moveable_property.get_velocity().x * delta.asSeconds()),
			object_property.get_position().y + (moveable_property.get_velocity().y * delta.asSeconds()),
			object_property.get_position().z + (moveable_property.get_velocity().z * delta.asSeconds())
		)
	);
}

}
}

