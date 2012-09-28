#include <FWCS/ExecutorRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <cassert>

namespace cs {

std::size_t ExecutorRequirements::get_num_requirements() const {
	return m_property_requirements.size();
}

bool ExecutorRequirements::test( const Entity& entity ) const {
	// Test property requirements.
	for( const auto& prop_req : m_property_requirements ) {
		if( entity.has_property( prop_req.name, prop_req.type ) != prop_req.required ) {
			return false;
		}
	}

	return true;
}



ExecutorRequirements::PropertyRequirement::PropertyRequirement(
	const std::string& name_,
	const std::string& type_,
	bool required_
) :
	name( name_ ),
	type( type_ ),
	required( required_ )
{
}

const ExecutorRequirements::PropertyRequirement& ExecutorRequirements::get_property_requirement( std::size_t index ) const {
	assert( index < m_property_requirements.size() );
	return m_property_requirements[index];
}

bool ExecutorRequirements::PropertyRequirement::operator==( const PropertyRequirement& other ) const {
	return
		name == other.name &&
		type == other.type &&
		required == other.required
	;
}

}
