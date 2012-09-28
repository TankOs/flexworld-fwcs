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

	}
}
