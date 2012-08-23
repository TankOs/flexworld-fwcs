#include <FWCS/Controllers/Walk.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>
#include <FWCS/Math.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace cs {
namespace ctrl {

static const float RAD_90 = 90.0f * PI / 180.0f;

Walk::Walk() :
	Controller()
{
	listen_for<sf::Vector3f>( "forward_vector" );
	listen_for<sf::Vector3f>( "force" );
	listen_for<sf::Vector2f>( "walk_control_vector" );
	listen_for<float>( "walk_force" );
}

void Walk::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<sf::Vector3f>& forward_vector = *entity.find_property<sf::Vector3f>( "forward_vector" );
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );
	ConcreteProperty<sf::Vector2f>& control_vector = *entity.find_property<sf::Vector2f>( "walk_control_vector" );
	ConcreteProperty<float>& walk_force = *entity.find_property<float>( "walk_force" );

	sf::Vector3f new_force( force.get_value() );

	new_force.x += forward_vector.get_value().x * walk_force.get_value() * control_vector.get_value().y;
	new_force.z += forward_vector.get_value().z * walk_force.get_value() * control_vector.get_value().y;

	// Make strafe vector.
	sf::Vector2f strafe_vector(
		forward_vector.get_value().x * std::cos( RAD_90 ) - forward_vector.get_value().z * std::sin( RAD_90 ),
		forward_vector.get_value().x * std::sin( RAD_90 ) + forward_vector.get_value().z * std::cos( RAD_90 )
	);

	new_force.x += strafe_vector.x * walk_force.get_value() * control_vector.get_value().x;
	new_force.z += strafe_vector.y * walk_force.get_value() * control_vector.get_value().x;

	force.set_value( new_force );
}

}
}
