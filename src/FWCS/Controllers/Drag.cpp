#include <FWCS/Controllers/Drag.hpp>
#include <FWCS/Properties/Moveable.hpp>
#include <FWCS/Properties/Drag.hpp>
#include <FWCS/Properties/Environment.hpp>
#include <FWCS/Entity.hpp>

namespace cs {
namespace ctrl {

Drag::Drag() :
	Controller()
{
	listen_for( "Moveable" );
	listen_for( "Environment" );
	listen_for( "Drag" );
}

void Drag::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	prop::Moveable& moveable_property = *entity.find_property<prop::Moveable>();
	prop::Drag& drag_property = *entity.find_property<prop::Drag>();
	prop::Environment& env_property = *entity.find_property<prop::Environment>();

	sf::Vector3f drag_force(
		(
			0.5f *
			env_property.get_air_density() *
			(moveable_property.get_velocity().x * moveable_property.get_velocity().x) *
			drag_property.get_resistance_coeff() *
			drag_property.get_area()
		),
		(
			0.5f *
			env_property.get_air_density() *
			(moveable_property.get_velocity().y * moveable_property.get_velocity().y) *
			drag_property.get_resistance_coeff() *
			drag_property.get_area()
		),
		(
			0.5f *
			env_property.get_air_density() *
			(moveable_property.get_velocity().z * moveable_property.get_velocity().z) *
			drag_property.get_resistance_coeff() *
			drag_property.get_area()
		)
	);

	sf::Vector3f new_force = moveable_property.get_force();

	if( new_force.x < 0.0f ) {
		new_force.x = std::min( 0.0f, new_force.x + drag_force.x );
	}
	else if( new_force.x > 0.0f ) {
		new_force.x = std::max( 0.0f, new_force.x - drag_force.x );
	}

	if( new_force.y < 0.0f ) {
		new_force.y = std::min( 0.0f, new_force.y + drag_force.y );
	}
	else if( new_force.y > 0.0f ) {
		new_force.y = std::max( 0.0f, new_force.y - drag_force.y );
	}

	if( new_force.z < 0.0f ) {
		new_force.z = std::min( 0.0f, new_force.z + drag_force.z );
	}
	else if( new_force.z > 0.0f ) {
		new_force.z = std::max( 0.0f, new_force.z - drag_force.z );
	}

	moveable_property.set_force( new_force );
}

}
}
