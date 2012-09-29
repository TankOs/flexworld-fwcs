#pragma once

#include <FWCS/Controller.hpp>

#include <SFML/System/Time.hpp>
#include <cstdint>

namespace cs {
class Entity;
}

class ExampleController : public cs::Controller {
	public:
		static bool is_entity_interesting( const cs::Entity& entity );

		ExampleController( cs::Entity& entity );
		void execute( const sf::Time& sim_time );

		sf::Time last_sim_time;
		std::size_t num_execute_calls;

	private:
};
