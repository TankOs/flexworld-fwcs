#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

namespace cs {
namespace ctrl {

ForceReset::ForceReset() :
	Controller()
{
	listen_for( "Moveable" );
}

void ForceReset::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();

	moveable_property.set_force( sf::Vector3f( 0, 0, 0 ) );
}

}
}
