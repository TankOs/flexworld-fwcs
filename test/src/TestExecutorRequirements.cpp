#include <FWCS/ExecutorRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestExecutorRequirements ) {
	using namespace cs;

	// Initial state.
	{
		ExecutorRequirements req;

		BOOST_CHECK( req.get_num_requirements() == 0 );
	}

	// Add property requirements.
	{
		ExecutorRequirements req;

		req.require_property<float>( "required", true );
		req.require_property<char>( "not_required", false );

		BOOST_CHECK( req.get_num_requirements() == 2 );
		BOOST_CHECK( req.get_property_requirement( 0 ) == ExecutorRequirements::PropertyRequirement( "required", typeid( float ).name(), true ) );
		BOOST_CHECK( req.get_property_requirement( 1 ) == ExecutorRequirements::PropertyRequirement( "not_required", typeid( char ).name(), false ) );
	}

	// Test for interesting entity.
	{
		// Empty requirement catches all.
		{
			ExecutorRequirements req;

			Entity ent;
			BOOST_CHECK( req.test( ent ) == true );

			ent.create_property<float>( "whatever" );
			BOOST_CHECK( req.test( ent ) == true );
		}

		// Require properties, mismatching types.
		{
			Entity ent;
			ent.create_property<float>( "int" );
			ent.create_property<int>( "float" );

			ExecutorRequirements req;
			req.require_property<float>( "float", true );
			req.require_property<int>( "int", true );

			BOOST_CHECK( req.test( ent ) == false );
		}

		// Disallow properties, mismatching types.
		{
			Entity ent;
			ent.create_property<float>( "int" );
			ent.create_property<int>( "float" );

			ExecutorRequirements req;
			req.require_property<float>( "float", false );
			req.require_property<int>( "int", false );

			BOOST_CHECK( req.test( ent ) == true );
		}

		// Required and not allowed properties.
		{
			ExecutorRequirements req;
			req.require_property<std::string>( "required0", true );
			req.require_property<float>( "required1", true );
			req.require_property<int>( "disallowed0", false );
			req.require_property<uint32_t>( "disallowed1", false );

			Entity ent;
			BOOST_CHECK( req.test( ent ) == false );

			ent.create_property<std::string>( "required0" );
			BOOST_CHECK( req.test( ent ) == false );

			ent.create_property<float>( "required1" );
			BOOST_CHECK( req.test( ent ) == true );

			ent.create_property<int>( "disallowed0" );
			BOOST_CHECK( req.test( ent ) == false );

			ent.create_property<uint32_t>( "disallowed1" );
			BOOST_CHECK( req.test( ent ) == false );
		}
	}
}
