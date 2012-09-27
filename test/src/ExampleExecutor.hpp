#pragma once

#include <FWCS/Executor.hpp>

#include <SFML/System/Time.hpp>
#include <cstdint>

namespace cs {
class Entity;
}

class ExampleExecutor : public cs::Executor {
	public:
		static bool is_entity_interesting( const cs::Entity& entity );

		ExampleExecutor();
		void execute( const sf::Time& sim_time );

		sf::Time last_sim_time;
		std::size_t num_execute_calls;

	private:
};
