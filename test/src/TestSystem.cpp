#include "ExampleExecutor.hpp"

#include <FWCS/System.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class DummyExecutor : public cs::Executor {
	public:
		void execute( const sf::Time& ) {
		}
};

BOOST_AUTO_TEST_CASE( TestSystem ) {
	using namespace cs;

	// Initial state.
	{
		System system;

		BOOST_CHECK( system.get_num_factories() == 0 );
	}

	// Create factories.
	{
		System system;

		system.create_factory<ExampleExecutor>();
		BOOST_CHECK( system.get_num_factories() == 1 );

		system.create_factory<DummyExecutor>();
		BOOST_CHECK( system.get_num_factories() == 2 );
	}

	// Add entities. 
	{
	}
}
