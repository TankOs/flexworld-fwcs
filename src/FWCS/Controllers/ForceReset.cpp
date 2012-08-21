#include <FWCS/Controllers/ForceReset.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

ForceReset::ForceReset() :
	Controller()
{
	listen_for<sf::Vector3f>( "force" );
}

void ForceReset::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );

	force.set_value( sf::Vector3f( 0, 0, 0 ) );
}

}
}
