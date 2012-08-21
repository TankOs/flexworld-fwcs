#include <FWCS/Controllers/Jump.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

static const sf::Time JUMP_DURATION = sf::milliseconds( 50 );

namespace cs {
namespace ctrl {

Jump::Jump() :
	Controller()
{
	listen_for<sf::Vector3f>( "force" );
	listen_for<sf::Vector3f>( "jump_vector" );
	listen_for<float>( "jump_force" );
	listen_for<bool>( "jump_active" );
}

void Jump::update_entity( Entity& entity, const sf::Time& delta ) {
	ConcreteProperty<bool>& jump_active = *entity.find_property<bool>( "jump_active" );

	if( !jump_active.get_value() ) {
		return;
	}

	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );
	ConcreteProperty<sf::Vector3f>& jump_vector = *entity.find_property<sf::Vector3f>( "jump_vector" );
	ConcreteProperty<float>& jump_force = *entity.find_property<float>( "jump_force" );

	ConcreteProperty<sf::Time>* runtime = entity.find_property<sf::Time>( "jump_runtime" );

	if( runtime == nullptr ) {
		runtime = &entity.create_property<sf::Time>( "jump_runtime" );
	}

	runtime->set_value( runtime->get_value() + delta );

	float applied_force = (
		runtime->get_value() <= JUMP_DURATION ?
		jump_force.get_value() :
		jump_force.get_value() * (JUMP_DURATION.asSeconds() / runtime->get_value().asSeconds())
	);

	force.set_value(
		sf::Vector3f(
			force.get_value().x + jump_vector.get_value().x * applied_force,
			force.get_value().y + jump_vector.get_value().y * applied_force,
			force.get_value().z + jump_vector.get_value().z * applied_force
		)
	);

	// Remove from cache if runtime exceeded.
	if( runtime->get_value() >= JUMP_DURATION ) {
		jump_active.set_value( false );
		runtime->set_value( sf::Time::Zero );
	}
}

}
}
