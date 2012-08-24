#pragma once

#include <SFML/System/Vector3.hpp>

namespace cs {

static const float PI = 3.14159265f; ///< PI.

/** Calculate a vector's length.
 * @param v Vector.
 * @return Length.
 */
float calc_length( const sf::Vector3f& v );

/** Normalize vector.
 * @param v Vector.
 */
void normalize( sf::Vector3f& v );

/** Calculate scalar product.
 * @param v0 Vector 0.
 * @param v1 Vector 1.
 * @return Scalar product.
 */
float calc_scalar_product( const sf::Vector3f& v0, const sf::Vector3f& v1 );

/** Calculate signum.
 * @param value Value.
 * @tparam T Value type.
 * @return -1 if negative, 0 if zero, 1 if positive.
 */
template <class T>
int calc_signum( T value );

}

#include "Math.inl"
