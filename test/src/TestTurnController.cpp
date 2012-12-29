#include <FWCS/Controllers/Turn.hpp>
#include <FWCS/Entity.hpp>
#include <FWCS/ControllerRequirements.hpp>

#include <SFML/System/Time.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>

using namespace cs;
using ctrl::Turn;

static const float TOLERANCE = 0.0001f;

class DummyConstraint : public Turn::Constraint {
	public:
		DummyConstraint() :
			Turn::Constraint()
		{
		}

		void update_rotation( util::FloatQuaternion& rotation, const sf::Vector3f& angular_velocity, const sf::Time& sim_time ) {
			float sim_seconds = sim_time.asSeconds();

			rotation.set_w( angular_velocity.x * sim_seconds );
			rotation.set_x( angular_velocity.y * sim_seconds );
			rotation.set_y( angular_velocity.z * sim_seconds );
			rotation.set_z( angular_velocity.x * angular_velocity.y * angular_velocity.z * sim_seconds );
		}
};

Entity create_correct_turn_entity() {
	static DummyConstraint constraint;
	Entity ent;

	ent.create_property<util::FloatQuaternion>( "rotation" );
	ent.create_property<sf::Vector3f>( "angular_velocity" );
	ent.create_property<Turn::Constraint*>( "turn_constraint", &constraint );

	return std::move( ent );
}


BOOST_AUTO_TEST_CASE( TestTurnController ) {
	BOOST_MESSAGE( "Testing turn controller..." );

	// Initial state.
	{
		Entity ent = create_correct_turn_entity();
		Turn controller{ ent };

		BOOST_CHECK( &controller.get_entity() == &ent );
	}

	// Requirements.
	{
		Entity ent;
		const auto& req = Turn::get_requirements();

		BOOST_REQUIRE( req.get_num_requirements() == 3 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ControllerRequirements::PropertyRequirement( "rotation", typeid( util::FloatQuaternion ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ControllerRequirements::PropertyRequirement( "angular_velocity", typeid( sf::Vector3f ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 2 ) == ControllerRequirements::PropertyRequirement( "turn_constraint", typeid( Turn::Constraint* ).name(), true ) );
	}

	// Execute.
	{
		static const sf::Time SIM_TIME{ sf::milliseconds( 34738 ) };
		static const sf::Vector3f ANGULAR_VELOCITY{ 2.0f, 4.0f, 6.0f };
		static util::FloatQuaternion ROTATION{
			ANGULAR_VELOCITY.x * SIM_TIME.asSeconds(),
			sf::Vector3f(
				ANGULAR_VELOCITY.y * SIM_TIME.asSeconds(),
				ANGULAR_VELOCITY.z * SIM_TIME.asSeconds(),
				ANGULAR_VELOCITY.x * ANGULAR_VELOCITY.y * ANGULAR_VELOCITY.z * SIM_TIME.asSeconds()
			)
		};

		ROTATION.normalize();

		Entity ent = create_correct_turn_entity();
		Turn controller{ ent };

		auto* rotation = ent.find_property<util::FloatQuaternion>( "rotation" );
		auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );

		*rotation = util::FloatQuaternion{};
		*angular_velocity = ANGULAR_VELOCITY;

		controller.execute( SIM_TIME );

		BOOST_CHECK( std::abs( rotation->get_w() - ROTATION.get_w() ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation->get_x() - ROTATION.get_x() ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation->get_y() - ROTATION.get_y() ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation->get_z() - ROTATION.get_z() ) <= TOLERANCE );
		BOOST_CHECK( *angular_velocity == ANGULAR_VELOCITY );
	}

	// Execute and check updated forward vector.
	{
		static const sf::Time SIM_TIME{ sf::milliseconds( 1000 ) };
		static const sf::Vector3f ANGULAR_VELOCITY{ 0.0f, 180.0f, 0.0f };
		static util::FloatQuaternion ROTATION{
			ANGULAR_VELOCITY.x * SIM_TIME.asSeconds(),
			sf::Vector3f(
				ANGULAR_VELOCITY.y * SIM_TIME.asSeconds(),
				ANGULAR_VELOCITY.z * SIM_TIME.asSeconds(),
				ANGULAR_VELOCITY.x * ANGULAR_VELOCITY.y * ANGULAR_VELOCITY.z * SIM_TIME.asSeconds()
			)
		};
		static sf::Vector3f FORWARD_VECTOR = ROTATION * sf::Vector3f{ 1.0f, 0.0f, 0.0f };

		util::normalize( FORWARD_VECTOR );
		ROTATION.normalize();

		Entity ent = create_correct_turn_entity();
		ent.create_property<sf::Vector3f>( "forward_vector", sf::Vector3f{ 0.0f, 0.0f, 0.0f } );
		Turn controller{ ent };

		auto* rotation = ent.find_property<util::FloatQuaternion>( "rotation" );
		auto* angular_velocity = ent.find_property<sf::Vector3f>( "angular_velocity" );
		auto* forward_vector = ent.find_property<sf::Vector3f>( "forward_vector" );

		*rotation = util::FloatQuaternion{};
		*angular_velocity = ANGULAR_VELOCITY;

		controller.execute( SIM_TIME );

		BOOST_CHECK( std::abs( rotation->get_w() - ROTATION.get_w() ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation->get_x() - ROTATION.get_x() ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation->get_y() - ROTATION.get_y() ) <= TOLERANCE );
		BOOST_CHECK( std::abs( rotation->get_z() - ROTATION.get_z() ) <= TOLERANCE );
		BOOST_CHECK( *angular_velocity == ANGULAR_VELOCITY );
		BOOST_CHECK( std::abs( forward_vector->x - FORWARD_VECTOR.x ) <= TOLERANCE );
		BOOST_CHECK( std::abs( forward_vector->y - FORWARD_VECTOR.y ) <= TOLERANCE );
		BOOST_CHECK( std::abs( forward_vector->z - FORWARD_VECTOR.z ) <= TOLERANCE );
	}
}
