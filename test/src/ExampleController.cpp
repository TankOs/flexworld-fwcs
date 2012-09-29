#include "ExampleController.hpp"

#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

bool ExampleController::is_entity_interesting( const cs::Entity& entity ) {
	return
		entity.find_property<float>( "example_float" ) != nullptr &&
		entity.find_property<sf::Vector3f>( "example_v3f" ) != nullptr
	;
}

ExampleController::ExampleController( cs::Entity& entity ) :
	Controller( entity ),
	last_sim_time{ sf::Time::Zero },
	num_execute_calls{ 0 }
{
}

void ExampleController::execute( const sf::Time& sim_time ) {
	++num_execute_calls;
	last_sim_time = sim_time;
}
