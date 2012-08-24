#include <FWCS/Controllers/Friction.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>
#include <FWCS/Math.hpp>

#include <SFML/System/Vector3.hpp>
#include <cmath>
#include <iostream> // XXX 

namespace cs {
namespace ctrl {

Friction::Friction() :
	Controller()
{
	listen_for<sf::Vector3f>( "velocity" );
	listen_for<sf::Vector3f>( "force" );
	listen_for<sf::Vector3f>( "up_vector" );
	listen_for<float>( "static_friction_coeff" );
	listen_for<float>( "sliding_friction_coeff" );
	listen_for<bool>( "on_ground" );
}

void Friction::update_entity( Entity& entity, const sf::Time& /*delta*/ ) {
	ConcreteProperty<bool>& on_ground = *entity.find_property<bool>( "on_ground" );

	// Ignore if not on ground.
	if( on_ground.get_value() == false ) {
		return;
	}

	ConcreteProperty<sf::Vector3f>& velocity = *entity.find_property<sf::Vector3f>( "velocity" );
	ConcreteProperty<sf::Vector3f>& force = *entity.find_property<sf::Vector3f>( "force" );
	ConcreteProperty<sf::Vector3f>& up_vector = *entity.find_property<sf::Vector3f>( "up_vector" );
	ConcreteProperty<float>& static_friction_coeff = *entity.find_property<float>( "static_friction_coeff" );
	ConcreteProperty<float>& sliding_friction_coeff = *entity.find_property<float>( "sliding_friction_coeff" );

	sf::Vector3f new_force( force.get_value() );

	// Calculate normal force.
	sf::Vector3f negative_up_vector( up_vector.get_value().x, -up_vector.get_value().y, up_vector.get_value().z );
	float normal_force_value = calc_scalar_product( new_force, negative_up_vector );

	// Static friction.
	if( velocity.get_value().x == 0.0f && velocity.get_value().y == 0.0f && velocity.get_value().z == 0.0f ) {
		// Calculate movement force (force without normal force).
		sf::Vector3f normalized_movement_force( new_force - (negative_up_vector * normal_force_value ) );
		float movement_force_value = calc_length( normalized_movement_force );

		if( movement_force_value == 0.0f ) {
			return;
		}

		normalize( normalized_movement_force );

		float max_static_friction_force = static_friction_coeff.get_value() * normal_force_value;
		float static_friction_force = std::min( max_static_friction_force, movement_force_value );

		// Apply counter force.
		new_force -= (normalized_movement_force * static_friction_force);
	}
	else { // Sliding friction.
		// If there are no forces applied in movement direction, check if can go
		// into rest state.
		sf::Vector3f movement_force( new_force - (negative_up_vector * normal_force_value ) );

		ConcreteProperty<sf::Vector3f>* last_velocity = entity.find_property<sf::Vector3f>( "friction_last_velocity" );

		if( last_velocity == nullptr ) {
			last_velocity = &entity.create_property<sf::Vector3f>( "friction_last_velocity", velocity.get_value() );
		}

		if(
			movement_force.x == 0.0f &&
			movement_force.y == 0.0f &&
			movement_force.z == 0.0f &&
			(
				calc_signum( last_velocity->get_value().x ) != calc_signum( velocity.get_value().x ) ||
				calc_signum( last_velocity->get_value().y ) != calc_signum( velocity.get_value().y ) ||
				calc_signum( last_velocity->get_value().z ) != calc_signum( velocity.get_value().z )
			)
		) {
			velocity.set_value( sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		}
		else {
			// Calculate normalized velocity vector.
			sf::Vector3f normalized_velocity( velocity.get_value() );
			normalize( normalized_velocity );

			float sliding_friction_force = sliding_friction_coeff.get_value() * normal_force_value;

			new_force -= (normalized_velocity * sliding_friction_force );
		}

		last_velocity->set_value( velocity.get_value() );
	}

	force.set_value( new_force );
}

}
}
