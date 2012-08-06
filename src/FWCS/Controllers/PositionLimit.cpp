#include <FWCS/Controllers/PositionLimit.hpp>
#include <FWCS/Properties/PositionLimit.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Object.hpp>
#include <FWCS/Entity.hpp>

namespace cs {
namespace ctrl {

PositionLimit::PositionLimit() :
	Controller()
{
	listen_for( "Moveable" );
	listen_for( "Object" );
	listen_for( "PositionLimit" );
}

void PositionLimit::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::PositionLimit& limit_property = *entity.find_property<prop::PositionLimit>();
	prop::Object& object_property = *entity.find_property<prop::Object>();
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();

	sf::Vector3f new_position = object_property.get_position();
	sf::Vector3f new_velocity = moveable_property.get_velocity();
	bool do_set_position = false;

	if( object_property.get_position().x < limit_property.get_lower_limit().x ) {
		new_position.x = limit_property.get_lower_limit().x;
		new_velocity.x = 0;
		do_set_position = true;
	}

	if( object_property.get_position().y < limit_property.get_lower_limit().y ) {
		new_position.y = limit_property.get_lower_limit().y;
		new_velocity.y = 0;
		do_set_position = true;
	}

	if( object_property.get_position().z < limit_property.get_lower_limit().z ) {
		new_position.z = limit_property.get_lower_limit().z;
		new_velocity.z = 0;
		do_set_position = true;
	}

	// Upper limit.
	if( object_property.get_position().x > limit_property.get_upper_limit().x ) {
		new_position.x = limit_property.get_upper_limit().x;
		new_velocity.x = 0;
		do_set_position = true;
	}

	if( object_property.get_position().y > limit_property.get_upper_limit().y ) {
		new_position.y = limit_property.get_upper_limit().y;
		new_velocity.y = 0;
		do_set_position = true;
	}

	if( object_property.get_position().z > limit_property.get_upper_limit().z ) {
		new_position.z = limit_property.get_upper_limit().z;
		new_velocity.z = 0;
		do_set_position = true;
	}

	if( do_set_position ) {
		object_property.set_position( new_position );
		moveable_property.set_velocity( new_velocity );
	}
}

}
}
