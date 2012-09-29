#include <FWCS/ControllerRequirements.hpp>
#include <FWCS/Entity.hpp>

#include <cassert>

namespace cs {

std::size_t ControllerRequirements::get_num_requirements() const {
	return m_property_requirements.size();
}

bool ControllerRequirements::test( const Entity& entity ) const {
	// Test property requirements.
	for( const auto& prop_req : m_property_requirements ) {
		if( entity.has_property( prop_req.name, prop_req.type ) != prop_req.required ) {
			return false;
		}
	}

	return true;
}



ControllerRequirements::PropertyRequirement::PropertyRequirement(
	const std::string& name_,
	const std::string& type_,
	bool required_
) :
	name( name_ ),
	type( type_ ),
	required( required_ )
{
}

const ControllerRequirements::PropertyRequirement& ControllerRequirements::get_property_requirement( std::size_t index ) const {
	assert( index < m_property_requirements.size() );
	return m_property_requirements[index];
}

bool ControllerRequirements::PropertyRequirement::operator==( const PropertyRequirement& other ) const {
	return
		name == other.name &&
		type == other.type &&
		required == other.required
	;
}

}
