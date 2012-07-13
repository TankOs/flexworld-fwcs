#include <FWCS/Properties/Position.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestPositionProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Position pos;

		BOOST_CHECK( pos.get_position() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	}
	
	// Basic properties.
	{
		prop::Position pos;

		pos.set_position( sf::Vector3f( 1.0f, 2.0f, 3.0f ) );

		BOOST_CHECK( pos.get_position() == sf::Vector3f( 1.0f, 2.0f, 3.0f ) );
	}
}
