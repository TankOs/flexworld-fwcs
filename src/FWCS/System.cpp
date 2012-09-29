#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controller.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <algorithm>

namespace cs {

System::System() :
	m_next_entity_id{ 0 }
{
}

System::~System() {
}

std::size_t System::get_num_factories() const {
	return m_factories.size();
}

std::size_t System::get_num_entities() const {
	return m_entities.size();
}

Entity& System::create_entity() {
	// Create entity and set unique ID + observer.
	std::unique_ptr<Entity> ent( new Entity );

	ent->set_id( m_next_entity_id );
	ent->set_observer( *this );
	++m_next_entity_id;

	m_entities.emplace_back(
		std::move( ent ),
		std::vector<std::unique_ptr<Controller>>{}
	);

	return *m_entities.back().first;
}

Entity* System::find_entity( EntityID id ) {
	auto iter = std::lower_bound(
		std::begin( m_entities ),
		std::end( m_entities ),
		id,
		[]( const EntityControllersPair& pair, const EntityID other_id ) -> bool {
			return pair.first->get_id() < other_id;
		}
	);

	return
		(iter == std::end( m_entities )) ||
		(iter->first->get_id() != id) ?
		nullptr :
		iter->first.get()
	;
}

void System::destroy_entity( EntityID id ) {
	auto iter = std::lower_bound(
		std::begin( m_entities ),
		std::end( m_entities ),
		id,
		[]( const EntityControllersPair& pair, const EntityID other_id ) -> bool {
			return pair.first->get_id() < other_id;
		}
	);

	assert( iter != std::end( m_entities ) );
	assert( iter->first->get_id() == id );

	m_entities.erase( iter );
}

void System::create_factory_controllers( BaseControllerFactory& factory ) {
	// Iterate over all entities and check if they meet requirements. If so, just
	// add the controller, as the factory is new and controllers for it doesn't
	// exist, yet.
	const auto& req = factory.get_requirements();

	for( auto& pair : m_entities ) {
		if( req.test( *pair.first ) == true ) {
			// Test passed, create controller.
			pair.second.emplace_back( factory.create_controller( *pair.first ) );
		}
	}
}

void System::on_property_create( const std::string& id, Entity& entity ) {
	// When an entity creates a property, we have to re-create controllers for that
	// entity to make sure it's linked to the correct ones.
	auto iter = std::lower_bound(
		std::begin( m_entities ),
		std::end( m_entities ),
		entity.get_id(),
		[]( const EntityControllersPair& pair, const EntityID other_id ) -> bool {
			return pair.first->get_id() < other_id;
		}
	);

	assert( iter != std::end( m_entities ) );
	assert( iter->first->get_id() == entity.get_id() );

	// Clear first, then (re)create controllers.
	iter->second.clear();

	for( auto& factory : m_factories ) {
		if( factory->get_requirements().test( *iter->first ) == true ) {
			iter->second.emplace_back( std::move( factory->create_controller( *iter->first ) ) );
		}
	}
}

void System::run( const sf::Time& sim_time ) {
	std::size_t num_entities = m_entities.size();
	std::size_t num_controllers = 0;
	std::size_t controller_idx = 0;
	std::vector<std::unique_ptr<Controller>>* controller_array = nullptr;

	for( std::size_t entity_idx = 0; entity_idx < num_entities; ++entity_idx ) {
		controller_array = &m_entities[entity_idx].second;
		num_controllers = controller_array->size();

		for( controller_idx = 0; controller_idx < num_controllers; ++controller_idx ) {
			(*controller_array)[controller_idx]->execute( sim_time );
		}
	}
}

}
