#include <FWCS/Controllers/Drag.hpp>
#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

Drag::Drag() :
	Controller()
{
	listen_for<float>( "air_density" );
	listen_for<float>( "resistance_coeff" );
	listen_for<float>( "drag_area" );
	listen_for<sf::Vector3f>( "velocity" );
	listen_for<sf::Vector3f>( "force" );
}

void Drag::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<float>& air_density = *entity.find_property<float>( "air_density" );
	ConcreteProperty<float>& resistance_coeff = *entity.find_property<float>( "resistance_coeff" );
	ConcreteProperty<float>& drag_area = *entity.find_property<float>( "drag_area" );
	ConcreteProperty<sf::Vector3f>& velocity = *entity.find_property<sf::Vector3f>( "velocity" );
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );

	sf::Vector3f drag_force(
		(
			0.5f *
			air_density.get_value() *
			(velocity.get_value().x * velocity.get_value().x) *
			resistance_coeff.get_value() *
			drag_area.get_value()
		),
		(
			0.5f *
			air_density.get_value() *
			(velocity.get_value().y * velocity.get_value().y) *
			resistance_coeff.get_value() *
			drag_area.get_value()
		),
		(
			0.5f *
			air_density.get_value() *
			(velocity.get_value().z * velocity.get_value().z) *
			resistance_coeff.get_value() *
			drag_area.get_value()
		)
	);

	sf::Vector3f new_force = force.get_value();

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

	force.set_value( new_force );
}

}
}
