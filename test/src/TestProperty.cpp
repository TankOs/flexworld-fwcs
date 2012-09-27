#include <FWCS/Property.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestProperty ) {
	using namespace cs;

	// Initial state.
	{
		ConcreteProperty<float> float_property( 100.0f );

		BOOST_CHECK( float_property.data == 100.0f );
		BOOST_CHECK( float_property.get_type_id() == typeid( float ).name() );
	}
}
