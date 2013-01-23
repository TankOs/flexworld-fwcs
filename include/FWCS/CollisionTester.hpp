#pragma once

#include <FWU/Cuboid.hpp>
#include <SFML/System/Vector3.hpp>

namespace cs {

class CollisionResult;

/** Functions for testing for collisions.
 * The CollisionTester implements several algorithms/methods for collision
 * tests. When a collision is detected, this class also provides functions to
 * calculate the projection vector.
 */
class CollisionTester {
	public:
		CollisionTester() = delete; ///< Ctor.

		/** Test for AABB collision.
		 * The AABB collision test takes 2 cuboids and checks if they intersect.
		 * @param subject_cuboid Subject cuboid (collider).
		 * @param object_cuboid Object cuboid (collision object).
		 * @return true if collision detected, false otherwise.
		 */
		static bool test_aabb(
			const util::FloatCuboid& subject_cuboid,
			const util::FloatCuboid& object_cuboid
		);

	private:
};

}
