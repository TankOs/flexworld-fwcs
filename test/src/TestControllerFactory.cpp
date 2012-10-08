#include <FWCS/ControllerFactory.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controller.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>

class DummyController : public cs::Controller {
	public:
		DummyController( cs::Entity& entity ) :
			cs::Controller( entity )
		{
		}

		static const cs::ControllerRequirements& get_requirements() {
			static cs::ControllerRequirements req =
				cs::ControllerRequirements{}.require_property<float>(
					"velocity", true
				)
			;

			return req;
		}

		void execute( const sf::Time& ) {
		}
};

BOOST_AUTO_TEST_CASE( TestControllerFactory ) {
	BOOST_MESSAGE( "Testing controller factory..." );

	using namespace cs;

	// Initial state.
	{
		ControllerFactory<DummyController> factory;
	}

	// Create controller.
	{
		Entity entity;

		ControllerFactory<DummyController> factory;
		std::unique_ptr<const Controller> controller = factory.create_controller( entity );

		const auto* example_controller = dynamic_cast<const DummyController*>( controller.get() );
		BOOST_REQUIRE( example_controller != nullptr );

		BOOST_CHECK( &controller->get_entity() == &entity );
	}

	// Check requirements.
	{
		ControllerFactory<DummyController> factory;
		const cs::ControllerRequirements& req = factory.get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 1 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "velocity", typeid( float ).name(), true ) );
	}
}
