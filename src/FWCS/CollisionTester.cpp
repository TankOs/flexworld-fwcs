#include <FWCS/CollisionTester.hpp>

#include <FWU/Math.hpp>
#include <cassert>

namespace cs {

bool CollisionTester::test_aabb(
	const util::FloatCuboid& subject_cuboid,
	const util::FloatCuboid& object_cuboid
) {
	float inner_left = std::max( subject_cuboid.x, object_cuboid.x );
	float inner_bottom = std::max( subject_cuboid.y, object_cuboid.y );
	float inner_back = std::max( subject_cuboid.z, object_cuboid.z );
	float inner_right = std::min( subject_cuboid.x + subject_cuboid.width, object_cuboid.x + subject_cuboid.width );
	float inner_top = std::min( subject_cuboid.y + subject_cuboid.height, object_cuboid.y + subject_cuboid.height );
	float inner_front = std::min( subject_cuboid.z + subject_cuboid.depth, object_cuboid.z + subject_cuboid.depth );

	return
		inner_left < inner_right &&
		inner_bottom < inner_top &&
		inner_back < inner_front
	;
}


}
