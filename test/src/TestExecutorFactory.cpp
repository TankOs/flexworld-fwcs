#include "ExampleExecutor.hpp"

#include <FWCS/ExecutorFactory.hpp>
#include <FWCS/Entity.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestExecutorFactory ) {
	using namespace cs;

	// Initial state.
	{
		ExecutorFactory<ExampleExecutor> factory;
	}

	// Create executor.
	{
		Entity entity;

		ExecutorFactory<ExampleExecutor> factory;
		std::unique_ptr<Executor> executor = factory.create_executor( entity );

		const auto* example_executor = dynamic_cast<ExampleExecutor*>( executor.get() );
		BOOST_REQUIRE( example_executor != nullptr );

		BOOST_CHECK( &example_executor->get_entity() == &entity );
		BOOST_CHECK( example_executor->last_sim_time == sf::Time::Zero );
		BOOST_CHECK( example_executor->num_execute_calls == 0 );
	}
}
