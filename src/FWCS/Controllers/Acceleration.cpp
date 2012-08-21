#include <FWCS/Controllers/Acceleration.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Acceleration::Acceleration() :
	Controller()
{
	listen_for<sf::Vector3f>( "acceleration" );
	listen_for<sf::Vector3f>( "velocity" );
}

void Acceleration::update_entity( Entity& entity, const sf::Time& delta ) {
	ConcreteProperty<sf::Vector3f>& acceleration = *entity.find_property<sf::Vector3f>( "acceleration" );
	ConcreteProperty<sf::Vector3f>& velocity = *entity.find_property<sf::Vector3f>( "velocity" );

	velocity.set_value(
		sf::Vector3f(
			velocity.get_value().x + (acceleration.get_value().x * delta.asSeconds()),
			velocity.get_value().y + (acceleration.get_value().y * delta.asSeconds()),
			velocity.get_value().z + (acceleration.get_value().z * delta.asSeconds())
		)
	);
}

}
}
