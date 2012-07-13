#include <FWCS/Properties/Velocity.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestVelocityProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Velocity vel;

		BOOST_CHECK( vel.get_velocity() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	}
	
	// Basic properties.
	{
		prop::Velocity vel;

		vel.set_velocity( sf::Vector3f( 1.0f, 2.0f, 3.0f ) );

		BOOST_CHECK( vel.get_velocity() == sf::Vector3f( 1.0f, 2.0f, 3.0f ) );
	}
}
