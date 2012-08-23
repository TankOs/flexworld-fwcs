#include <FWCS/Math.hpp>
#include <cassert>
#include <cmath>

namespace cs {

float calc_length( const sf::Vector3f& v ) {
	return std::sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

void normalize( sf::Vector3f& v ) {
	float length = calc_length( v );
	assert( length > 0.0f );

	v.x /= length;
	v.y /= length;
	v.z /= length;
}

float calc_scalar_product( const sf::Vector3f& v0, const sf::Vector3f& v1 ) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

}
