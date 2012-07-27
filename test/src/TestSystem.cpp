#include <FWCS/System.hpp>
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

	// Add and delete controllers.
	{
		System sys;

		sys.create_controller<ctl::Gravity>();

		BOOST_CHECK( sys.get_num_controllers() == 1 );
		BOOST_CHECK( sys.has_controller<ctl::Gravity>() == true );

		sys.delete_controller<ctl::Gravity>();

		BOOST_CHECK( sys.get_num_controllers() == 0 );
		BOOST_CHECK( sys.has_controller<ctl::Gravity>() == false );
	}
}
