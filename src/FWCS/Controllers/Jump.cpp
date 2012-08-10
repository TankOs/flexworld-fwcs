#include <FWCS/Controllers/Jump.hpp>
#include <FWCS/Properties/Jump.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Entity.hpp>

#include <cassert>

static const sf::Time JUMP_DURATION = sf::milliseconds( 10 );

namespace cs {
namespace ctrl {

Jump::Jump() :
	Controller()
{
	listen_for( "Jump" );
	listen_for( "Moveable" );
}

std::size_t Jump::get_num_cached_entities() const {
	return m_runtimes.size();
}

void Jump::on_entity_remove( Entity& entity ) {
	EntityRuntimeMap::iterator ent_iter = m_runtimes.find( &entity );

	if( ent_iter != m_runtimes.end() ) {
		m_runtimes.erase( ent_iter );
	}
}

void Jump::update_entity( Entity& entity, const sf::Time& delta ) {
	prop::Jump& jump_property = *entity.find_property<prop::Jump>();

	if( jump_property.is_active() == false ) {
		return;
	}

	EntityRuntimeMap::iterator runtime_iter = m_runtimes.find( &entity );

	if( runtime_iter == m_runtimes.end() ) {
		runtime_iter = m_runtimes.insert( std::pair<Entity*, sf::Time>( &entity, sf::Time::Zero ) ).first;
	}

	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();

	runtime_iter->second += delta;

	float applied_force = (
		runtime_iter->second <= JUMP_DURATION ?
		jump_property.get_force() :
		jump_property.get_force() * (JUMP_DURATION.asSeconds() / runtime_iter->second.asSeconds())
	);

	moveable_property.set_force(
		sf::Vector3f(
			moveable_property.get_force().x + jump_property.get_up_vector().x * applied_force,
			moveable_property.get_force().y + jump_property.get_up_vector().y * applied_force,
			moveable_property.get_force().z + jump_property.get_up_vector().z * applied_force
		)
	);

	// Remove from cache if runtime exceeded.
	if( runtime_iter->second >= JUMP_DURATION ) {
		jump_property.set_active( false );
		m_runtimes.erase( &entity );
	}
}

}
}
