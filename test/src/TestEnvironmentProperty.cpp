#include <FWCS/Properties/Environment.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestEnvironmentProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Environment property;

		BOOST_CHECK( prop::Environment::ID == "Environment" );
		BOOST_CHECK( property.get_id() == prop::Environment::ID );
		BOOST_CHECK( property.get_air_density() == 1.275f );
		BOOST_CHECK( property.get_gravity() == -9.80665f );
	}
	
	// Basic properties.
	{
		prop::Environment property;

		property.set_air_density( 250 );
		property.set_gravity( 500 );

		BOOST_CHECK( property.get_air_density() == 250.0f );
		BOOST_CHECK( property.get_gravity() == 500.0f );
	}
}
