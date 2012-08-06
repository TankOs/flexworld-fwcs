#include <FWCS/Properties/PositionLimit.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestPositionLimitProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::PositionLimit property;

		BOOST_CHECK( property.get_upper_limit() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( property.get_lower_limit() == sf::Vector3f( 0, 0, 0 ) );
	}

	// Basic properties.
	{
		prop::PositionLimit property;

		property.set_upper_limit( sf::Vector3f( +11, +22, +33 ) );
		property.set_lower_limit( sf::Vector3f( -11, -22, -33 ) );

		BOOST_CHECK( property.get_upper_limit() == sf::Vector3f( +11, +22, +33 ) );
		BOOST_CHECK( property.get_lower_limit() == sf::Vector3f( -11, -22, -33 ) );
	}
}
