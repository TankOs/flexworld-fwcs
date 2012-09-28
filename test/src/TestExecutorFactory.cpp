#include <FWCS/ExecutorFactory.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Executor.hpp>
#include <FWCS/ExecutorRequirements.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class DummyExecutor : public cs::Executor {
	public:
		DummyExecutor( cs::Entity& entity ) :
			cs::Executor( entity )
		{
		}

		static const cs::ExecutorRequirements& get_requirements() {
			static cs::ExecutorRequirements req =
				cs::ExecutorRequirements{}.require_property<float>(
					"velocity", true
				)
			;

			return req;
		}

		void execute( const sf::Time& ) {
		}
};

BOOST_AUTO_TEST_CASE( TestExecutorFactory ) {
	using namespace cs;

	// Initial state.
	{
		ExecutorFactory<DummyExecutor> factory;
	}

	// Create executor.
	{
		Entity entity;

		ExecutorFactory<DummyExecutor> factory;
		std::unique_ptr<const Executor> executor = factory.create_executor( entity );

		const auto* example_executor = dynamic_cast<const DummyExecutor*>( executor.get() );
		BOOST_REQUIRE( example_executor != nullptr );

		BOOST_CHECK( &executor->get_entity() == &entity );
	}

	// Check requirements.
	{
		ExecutorFactory<DummyExecutor> factory;
		const cs::ExecutorRequirements& req = factory.get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 1 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ExecutorRequirements::PropertyRequirement( "velocity", typeid( float ).name(), true ) );
	}
}
