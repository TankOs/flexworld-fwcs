#include <FWCS/Controllers/ThrustReset.hpp>
#include <FWCS/Properties/Thrust.hpp>
#include <FWCS/Entity.hpp>

namespace cs {
namespace ctrl {

ThrustReset::ThrustReset() :
	Controller()
{
	listen_for( "Thrust" );
}

void ThrustReset::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::Thrust& thrust_property = *entity.find_property<prop::Thrust>();

	thrust_property.set_thrust( sf::Vector3f( 0, 0, 0 ) );
}

}
}
