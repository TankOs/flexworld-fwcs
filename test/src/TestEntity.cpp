#include <FWCS/Entity.hpp>
#include <FWCS/Properties/Velocity.hpp>
#include <FWCS/Properties/Position.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestEntity ) {
	using namespace cs;

	// Initial state.
	{
		Entity ent( 1337 );

		BOOST_CHECK( ent.get_id() == 1337 );
		BOOST_CHECK( ent.get_num_properties() == 0 );
	}

	// Create properties.
	{
		Entity ent( 1337 );

		BOOST_CHECK( ent.has_property( prop::Velocity::ID ) == false );
		BOOST_CHECK_NO_THROW( ent.create_property<prop::Velocity>() );
		BOOST_CHECK( ent.has_property( prop::Velocity::ID ) != false );
		BOOST_CHECK( &ent.get_property<prop::Velocity>() != nullptr );
		BOOST_CHECK( ent.get_num_properties() == 1 );

		BOOST_CHECK( ent.has_property( prop::Position::ID ) == false );
		BOOST_CHECK_NO_THROW( ent.create_property<prop::Position>() );
		BOOST_CHECK( ent.has_property( prop::Position::ID ) != false );
		BOOST_CHECK( ent.has_property( prop::Velocity::ID ) != false );
		BOOST_CHECK( &ent.get_property<prop::Position>() != nullptr );
		BOOST_CHECK( ent.get_num_properties() == 2 );
	}
}
