#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>

namespace cs {
namespace ctrl {

Gravity::Gravity() :
	Controller()
{
	listen_for<sf::Vector3f>( "force" );
	listen_for<float>( "gravity" );
	listen_for<float>( "mass" );
}

void Gravity::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );
	ConcreteProperty<float>& gravity = *entity.find_property<float>( "gravity" );
	ConcreteProperty<float>& mass = *entity.find_property<float>( "mass" );

	force.set_value(
		sf::Vector3f(
			force.get_value().x,
			force.get_value().y + (
				mass.get_value() * gravity.get_value()
			),
			force.get_value().z
		)
	);
}

}
}
