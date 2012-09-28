#include "ExampleExecutor.hpp"

#include <FWCS/Entity.hpp>

#include <SFML/System/Vector3.hpp>

bool ExampleExecutor::is_entity_interesting( const cs::Entity& entity ) {
	return
		entity.find_property<float>( "example_float" ) != nullptr &&
		entity.find_property<sf::Vector3f>( "example_v3f" ) != nullptr
	;
}

ExampleExecutor::ExampleExecutor( cs::Entity& entity ) :
	Executor( entity ),
	last_sim_time{ sf::Time::Zero },
	num_execute_calls{ 0 }
{
}

void ExampleExecutor::execute( const sf::Time& sim_time ) {
	++num_execute_calls;
	last_sim_time = sim_time;
}
