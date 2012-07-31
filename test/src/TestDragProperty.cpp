#include <FWCS/Properties/Drag.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestDragProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Drag drag;

		BOOST_CHECK( prop::Drag::ID == "Drag" );
		BOOST_CHECK( drag.get_id() == prop::Drag::ID );
		BOOST_CHECK( drag.get_area() == 0 );
		BOOST_CHECK( drag.get_resistance_coeff() == 0 );
	}
	
	// Basic properties.
	{
		prop::Drag drag;

		drag.set_area( 250 );
		drag.set_resistance_coeff( 500 );

		BOOST_CHECK( drag.get_area() == 250 );
		BOOST_CHECK( drag.get_resistance_coeff() == 500 );
	}
}
