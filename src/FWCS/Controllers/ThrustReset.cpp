#include <FWCS/Controllers/ThrustReset.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

ThrustReset::ThrustReset() :
	Controller()
{
	listen_for<sf::Vector3f>( "thrust" );
}

void ThrustReset::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector3f>& thrust_property = *entity.find_property<sf::Vector3f>( "thrust" );

	thrust_property.set_value( sf::Vector3f( 0, 0, 0 ) );
}

}
}
