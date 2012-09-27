#include "ExampleExecutor.hpp"

#include <FWCS/ExecutorFactory.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestExecutorFactory ) {
	using namespace cs;

	// Initial state.
	{
		ExecutorFactory<ExampleExecutor> factory;
	}

	// Create executor.
	{
		ExecutorFactory<ExampleExecutor> factory;
		ExampleExecutor executor = factory.create_executor();

		BOOST_CHECK( executor.last_sim_time == sf::Time::Zero );
		BOOST_CHECK( executor.num_execute_calls == 0 );
	}
}
