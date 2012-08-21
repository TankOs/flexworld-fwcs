#include <FWCS/Controllers/Movement.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Movement::Movement() :
	Controller()
{
	listen_for<sf::Vector3f>( "position" );
	listen_for<sf::Vector3f>( "velocity" );
}

void Movement::update_entity( Entity& entity, const sf::Time& delta ) {
	ConcreteProperty<sf::Vector3f>& position = *entity.find_property<sf::Vector3f>( "position" );
	ConcreteProperty<sf::Vector3f>& velocity = *entity.find_property<sf::Vector3f>( "velocity" );

	position.set_value(
		sf::Vector3f(
			position.get_value().x + (velocity.get_value().x * delta.asSeconds()),
			position.get_value().y + (velocity.get_value().y * delta.asSeconds()),
			position.get_value().z + (velocity.get_value().z * delta.asSeconds())
		)
	);
}

}
}

