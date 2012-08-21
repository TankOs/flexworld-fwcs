#include <FWCS/Controllers/MovementForceTransform.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

MovementForceTransform::MovementForceTransform() :
	Controller()
{
	listen_for<sf::Vector3f>( "force" );
	listen_for<sf::Vector3f>( "acceleration" );
	listen_for<float>( "mass" );
}

void MovementForceTransform::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );
	ConcreteProperty<sf::Vector3f>& acceleration = *entity.find_property<sf::Vector3f>( "acceleration" );
	ConcreteProperty<float>& mass = *entity.find_property<float>( "mass" );

	acceleration.set_value(
		sf::Vector3f(
			force.get_value().x / mass.get_value(),
			force.get_value().y / mass.get_value(),
			force.get_value().z / mass.get_value()
		)
	);
}

}
}
