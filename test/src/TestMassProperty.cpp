#include <FWCS/Properties/Mass.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMassProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Mass mass;

		BOOST_CHECK( prop::Mass::ID == "mass" );
		BOOST_CHECK( mass.get_id() == prop::Mass::ID );
		BOOST_CHECK( mass.get_mass() == 0.0f );
	}
	
	// Basic properties.
	{
		prop::Mass mass;

		mass.set_mass( 123.0f );

		BOOST_CHECK( mass.get_mass() == 123.0f );
	}
}
