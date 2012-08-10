#include <FWCS/Properties/Thrust.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestThrustProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Thrust property;

		BOOST_CHECK( prop::Thrust::ID == "Thrust" );
		BOOST_CHECK( property.get_id() == prop::Thrust::ID );
		BOOST_CHECK( property.get_thrust() == sf::Vector3f( 0, 0, 0 ) );
	}

	// Basic properties.
	{
		prop::Thrust property;

		property.set_thrust( sf::Vector3f( 1, 2, 3 ) );

		BOOST_CHECK( property.get_thrust() == sf::Vector3f( 1, 2, 3 ) );
	}
}
