#include <FWCS/Controller.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Properties/Velocity.hpp>
#include <FWCS/Properties/Position.hpp>

#include <boost/test/unit_test.hpp>

class ExampleController : public cs::Controller {
	public:
		ExampleController() :
			cs::Controller()
		{
			std::vector<std::string> props;

			props.push_back( "position" );
			props.push_back( "velocity" );

			listen_for( props );
		}
};

BOOST_AUTO_TEST_CASE( TestController ) {
	using namespace cs;

	// Initial state.
	{
		Controller controller;

		BOOST_CHECK( controller.get_required_properties().size() == 0 );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
	}

	// Controller setup.
	{
		ExampleController controller;

		BOOST_REQUIRE( controller.get_required_properties().size() == 2 );
		BOOST_CHECK( controller.get_required_properties()[0] == "position" );
		BOOST_CHECK( controller.get_required_properties()[1] == "velocity" );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
	}

	// Check interesting entities.
	{
		// No interesting entity.
		{
			Entity ent( 0 );
			ExampleController controller;

			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent( 0 );
			ent.create_property<prop::Velocity>();

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// No interesting entity.
		{
			Entity ent( 0 );
			ent.create_property<prop::Position>();

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == false );
		}

		// Interesting entity.
		{
			Entity ent( 0 );
			ent.create_property<prop::Velocity>();
			ent.create_property<prop::Position>();

			ExampleController controller;
			BOOST_CHECK( controller.is_entity_interesting( ent ) == true );
		}
	}

	// Add and remove entities.
	{
		Entity ent0( 0 );
		ent0.create_property<prop::Velocity>();
		ent0.create_property<prop::Position>();

		Entity ent1( 0 );
		ent1.create_property<prop::Velocity>();
		ent1.create_property<prop::Position>();

		ExampleController controller;
		BOOST_REQUIRE( controller.is_entity_interesting( ent0 ) == true );
		BOOST_REQUIRE( controller.is_entity_interesting( ent1 ) == true );

		controller.add_entity( ent0 );
		BOOST_CHECK( controller.get_num_linked_entities() == 1 );

		controller.add_entity( ent1 );
		BOOST_CHECK( controller.get_num_linked_entities() == 2 );

		// Remove again.
		controller.remove_entity( ent0 );
		BOOST_CHECK( controller.get_num_linked_entities() == 1 );

		controller.remove_entity( ent1 );
		BOOST_CHECK( controller.get_num_linked_entities() == 0 );
	}
}
