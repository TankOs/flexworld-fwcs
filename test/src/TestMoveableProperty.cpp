#include <FWCS/Properties/Moveable.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMoveableProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Moveable moveable;

		BOOST_CHECK( prop::Moveable::ID == "Moveable" );
		BOOST_CHECK( moveable.get_id() == prop::Moveable::ID );
		BOOST_CHECK( moveable.get_velocity() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( moveable.get_acceleration() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( moveable.get_force() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( moveable.get_mass() == 0.0f );
	}
	
	// Basic properties.
	{
		prop::Moveable moveable;

		moveable.set_velocity( sf::Vector3f( 1, 2, 3 ) );
		moveable.set_acceleration( sf::Vector3f( 10, 20, 30 ) );
		moveable.set_force( sf::Vector3f( 100, 200, 300 ) );
		moveable.set_mass( 123 );

		BOOST_CHECK( moveable.get_velocity() == sf::Vector3f( 1.0f, 2.0f, 3.0f ) );
		BOOST_CHECK( moveable.get_acceleration() == sf::Vector3f( 10.0f, 20.0f, 30.0f ) );
		BOOST_CHECK( moveable.get_force() == sf::Vector3f( 100.0f, 200.0f, 300.0f ) );
		BOOST_CHECK( moveable.get_mass() == 123.0f );
	}
}
