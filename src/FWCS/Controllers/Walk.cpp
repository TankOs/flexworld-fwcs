#include <FWCS/Controllers/Walk.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>
#include <FWCS/Math.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <iostream>// XXX 

namespace cs {
namespace ctrl {

static const float SIN_90 = std::sin( 90.0f * PI / 180.0f );
static const float COS_90 = std::cos( 90.0f * PI / 180.0f );

Walk::Walk() :
	Controller()
{
	listen_for<sf::Vector3f>( "forward_vector" );
	listen_for<sf::Vector3f>( "force" );
	listen_for<sf::Vector2f>( "walk_control_vector" );
	listen_for<sf::Vector3f>( "velocity" );
	listen_for<float>( "walk_force" );
	listen_for<float>( "max_walk_velocity" );
}

void Walk::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector2f>& control_vector = *entity.find_property<sf::Vector2f>( "walk_control_vector" );

	if( control_vector.get_value().x == 0.0f && control_vector.get_value().y == 0.0f ) {
		return;
	}

	ConcreteProperty<sf::Vector3f>& forward_vector = *entity.find_property<sf::Vector3f>( "forward_vector" );
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );
	ConcreteProperty<sf::Vector3f>& velocity = *entity.find_property<sf::Vector3f>( "velocity" );
	ConcreteProperty<float>& walk_force = *entity.find_property<float>( "walk_force" );
	ConcreteProperty<float>& max_walk_velocity = *entity.find_property<float>( "max_walk_velocity" );

	sf::Vector3f new_force( force.get_value() );

	// Calculate normalized walk vector (intended walk direction).
	sf::Vector3f forward_walk_vector(
		forward_vector.get_value().x * control_vector.get_value().y,
		forward_vector.get_value().y * control_vector.get_value().y,
		forward_vector.get_value().z * control_vector.get_value().y
	);

	sf::Vector3f sideward_walk_vector(
		(forward_vector.get_value().x * COS_90 + forward_vector.get_value().z * SIN_90) * -control_vector.get_value().x,
		(forward_vector.get_value().y) * control_vector.get_value().x,
		(forward_vector.get_value().x * -SIN_90 + forward_vector.get_value().z * COS_90) * -control_vector.get_value().x
	);

	sf::Vector3f walk_vector( forward_walk_vector + sideward_walk_vector );
	normalize( walk_vector );

	float current_velocity_value = std::max( 0.0f, calc_scalar_product( velocity.get_value(), walk_vector ) );
	float velocity_percentage = std::max( 0.0f, 1.0f - current_velocity_value / max_walk_velocity.get_value() );
	float applied_force = walk_force.get_value() * velocity_percentage;

	new_force += walk_vector * applied_force;

	force.set_value( new_force );
}

}
}
