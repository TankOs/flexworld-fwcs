#include <FWCS/Properties/Jump.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestJumpProperty ) {
	using namespace cs::prop;

	// Initial state.
	{
		Jump property;

		BOOST_CHECK( Jump::ID == "Jump" );
		BOOST_CHECK( property.get_id() == Jump::ID );

		BOOST_CHECK( property.is_active() == false );
		BOOST_CHECK( property.get_up_vector() == sf::Vector3f( 0, 1, 0 ) );
		BOOST_CHECK( property.get_force() == 100.0f );
	}

	// Basic properties.
	{
		Jump property;

		property.set_active( true );
		property.set_up_vector( sf::Vector3f( 1, 2, 3 ) );
		property.set_force( 123.4f );

		BOOST_CHECK( property.is_active() == true );
		BOOST_CHECK( property.get_up_vector() == sf::Vector3f( 1, 2, 3 ) );
		BOOST_CHECK( property.get_force() == 123.4f );
	}
}
