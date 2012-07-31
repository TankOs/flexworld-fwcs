#include <FWCS/Controllers/Gravity.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Time.hpp>

namespace cs {
namespace ctl {

Gravity::Gravity( float gravity ) :
	m_gravity( gravity )
{
	listen_for( "Moveable" );
}

float Gravity::get_gravity() const {
	return m_gravity;
}

void Gravity::update_entity( Entity& entity, const sf::Time& delta ) {
}

}
}
