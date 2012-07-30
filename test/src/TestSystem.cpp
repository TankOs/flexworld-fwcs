#include <FWCS/System.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/Controllers/Gravity.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestSystem ) {
	using namespace cs;

	// Initial state.
	{
		System sys;

		BOOST_CHECK( sys.get_num_controllers() == 0 );
		BOOST_CHECK( sys.get_num_entities() == 0 );
	}

	// Create and delete controllers.
	{
		System sys;

		sys.create_controller<ctl::Gravity>();

		BOOST_CHECK( sys.get_num_controllers() == 1 );
		BOOST_CHECK( sys.has_controller<ctl::Gravity>() == true );

		sys.delete_controller<ctl::Gravity>();

		BOOST_CHECK( sys.get_num_controllers() == 0 );
		BOOST_CHECK( sys.has_controller<ctl::Gravity>() == false );
	}

	// Create and delete entities.
	{
		System sys;

		Entity& entity = sys.create_entity( 1337 );

		BOOST_CHECK( sys.find_entity( 1337 ) == &entity );
		BOOST_CHECK( entity.get_id() == 1337 );
		BOOST_REQUIRE( entity.has_observer() );
		BOOST_CHECK( &entity.get_observer() == static_cast<EntityObserver*>( &sys ) );
	}
}
