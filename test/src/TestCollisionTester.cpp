#include <FWCS/CollisionTester.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>

using cs::CollisionTester;

BOOST_AUTO_TEST_CASE( TestCollisionTester ) {
	BOOST_MESSAGE( "Testing collision tester..." );

	// Initial state.
	{
	}

	// AABB collision: No intersection.
	{
		bool collided_once = false;

		for( float z = -1.0f; z <= 1.0f; z += 2.0f ) {
			for( float y = -1.0f; y <= 1.0f; y += 2.0f ) {
				for( float x = -1.0f; x <= 1.0f; x += 2.0f ) {
					util::FloatCuboid subject_cuboid{ 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 10.0f };
					util::FloatCuboid object_cuboid{ x * 10.0f, y * 10.0f, z * 10.0f, 10.0f, 10.0f, 10.0f };
					sf::Vector3f forward_vector{ 1.0f, 0.0f, 0.0f };

					bool collided = CollisionTester::test_aabb( subject_cuboid, object_cuboid );
					collided_once = collided || collided_once;

					if( collided == true ) {
						std::stringstream sstr;
						sstr << "Collision detected for " << x << ", " << y << ", " << z << "!";

						BOOST_MESSAGE( sstr.str() );
					}
				}
			}
		}

		BOOST_CHECK( collided_once == false );
	}

	// AABB collision: Partial intersections.
	{
		bool collided_once = false;

		for( float z = -0.5f; z <= 0.5f; z += 1.0f ) {
			for( float y = -0.5f; y <= 0.5f; y += 1.0f ) {
				for( float x = -0.5f; x <= 0.5f; x += 1.0f ) {
					util::FloatCuboid subject_cuboid{ 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 10.0f };
					util::FloatCuboid object_cuboid{ x * 10.0f, y * 10.0f, z * 10.0f, 10.0f, 10.0f, 10.0f };
					sf::Vector3f forward_vector{ 1.0f, 0.0f, 0.0f };

					bool collided = CollisionTester::test_aabb( subject_cuboid, object_cuboid );
					collided_once = collided || collided_once;

					if( collided == false ) {
						std::stringstream sstr;
						sstr << "Collision NOT detected for " << x << ", " << y << ", " << z << "!";

						BOOST_MESSAGE( sstr.str() );
					}
				}
			}
		}

		BOOST_CHECK( collided_once == true );
	}
}
