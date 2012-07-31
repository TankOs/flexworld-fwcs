#include <FWCS/Properties/Object.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestObjectProperty ) {
	using namespace cs;

	// Initial state.
	{
		prop::Object object;

		BOOST_CHECK( prop::Object::ID == "Object" );
		BOOST_CHECK( object.get_id() == prop::Object::ID );
		BOOST_CHECK( object.get_position() == sf::Vector3f( 0.0f, 0.0f, 0.0f ) );
	}
	
	// Basic properties.
	{
		prop::Object object;

		object.set_position( sf::Vector3f( 1.0f, 2.0f, 3.0f ) );

		BOOST_CHECK( object.get_position() == sf::Vector3f( 1.0f, 2.0f, 3.0f ) );
	}
}
