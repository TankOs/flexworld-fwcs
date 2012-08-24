#include <FWCS/Math.hpp>

#include <boost/test/unit_test.hpp>
#include <cmath>

BOOST_AUTO_TEST_CASE( TestMath ) {
	using namespace cs;

	// Vector length.
	{
		sf::Vector3f v;

		v = sf::Vector3f( 2.0f, 0.0f, 0.0f );
		BOOST_CHECK( calc_length( v ) == 2.0f );

		v = sf::Vector3f( -2.0f, 0.0f, 0.0f );
		BOOST_CHECK( calc_length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, 2.0f, 0.0f );
		BOOST_CHECK( calc_length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, -2.0f, 0.0f );
		BOOST_CHECK( calc_length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, 0.0f, 2.0f );
		BOOST_CHECK( calc_length( v ) == 2.0f );

		v = sf::Vector3f( 0.0f, 0.0f, -2.0f );
		BOOST_CHECK( calc_length( v ) == 2.0f );

		v = sf::Vector3f( 1.0f, 2.0f, 3.0f );
		BOOST_CHECK( calc_length( v ) == std::sqrt( 14.0f ) );

		v = sf::Vector3f( 0.0f, 0.0f, 0.0f );
		BOOST_CHECK( calc_length( v ) == std::sqrt( 0.0f ) );
	}

	// Normalize vector.
	{
		sf::Vector3f v;

		v = sf::Vector3f( 10.0f, 0.0f, 0.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector3f( 1.0f, 0.0f, 0.0f ) );

		v = sf::Vector3f( 0.0f, 10.0f, 0.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector3f( 0.0f, 1.0f, 0.0f ) );

		v = sf::Vector3f( 0.0f, 0.0f, 10.0f );
		normalize( v );
		BOOST_CHECK( v == sf::Vector3f( 0.0f, 0.0f, 1.0f ) );
	}

	// Scalar product.
	{
		sf::Vector3f v0( 10.0f, 5.0f, 5.0f );
		sf::Vector3f v1( 0.5f, 0.5f, 0.0f );

		float result = calc_scalar_product( v0, v1 );
		BOOST_CHECK( result == 7.5f );
	}

	// Sign.
	{
		BOOST_CHECK( calc_signum( -10 ) == -1 );
		BOOST_CHECK( calc_signum( 10 ) == 1 );
		BOOST_CHECK( calc_signum( 0 ) == 0 );
	}
}
