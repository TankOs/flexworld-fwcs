#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

PositionLimit::PositionLimit() :
	Controller()
{
	listen_for<sf::Vector3f>( "position" );
	listen_for<sf::Vector3f>( "velocity" );
	listen_for<sf::Vector3f>( "lower_position_limit" );
	listen_for<sf::Vector3f>( "upper_position_limit" );
}

void PositionLimit::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector3f>& velocity = *entity.find_property<sf::Vector3f>( "velocity" );
	ConcreteProperty<sf::Vector3f>& position = *entity.find_property<sf::Vector3f>( "position" );
	ConcreteProperty<sf::Vector3f>& lower_limit = *entity.find_property<sf::Vector3f>( "lower_position_limit" );
	ConcreteProperty<sf::Vector3f>& upper_limit = *entity.find_property<sf::Vector3f>( "upper_position_limit" );

	sf::Vector3f new_position = position.get_value();
	sf::Vector3f new_velocity = velocity.get_value();
	bool do_set_position = false;

	if( position.get_value().x < lower_limit.get_value().x ) {
		new_position.x = lower_limit.get_value().x;
		new_velocity.x = 0;
		do_set_position = true;
	}

	if( position.get_value().y < lower_limit.get_value().y ) {
		new_position.y = lower_limit.get_value().y;
		new_velocity.y = 0;
		do_set_position = true;
	}

	if( position.get_value().z < lower_limit.get_value().z ) {
		new_position.z = lower_limit.get_value().z;
		new_velocity.z = 0;
		do_set_position = true;
	}

	// Upper limit.
	if( position.get_value().x > upper_limit.get_value().x ) {
		new_position.x = upper_limit.get_value().x;
		new_velocity.x = 0;
		do_set_position = true;
	}

	if( position.get_value().y > upper_limit.get_value().y ) {
		new_position.y = upper_limit.get_value().y;
		new_velocity.y = 0;
		do_set_position = true;
	}

	if( position.get_value().z > upper_limit.get_value().z ) {
		new_position.z = upper_limit.get_value().z;
		new_velocity.z = 0;
		do_set_position = true;
	}

	if( do_set_position ) {
		position.set_value( new_position );
		velocity.set_value( new_velocity );
	}
}

}
}
