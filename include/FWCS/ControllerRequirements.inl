#include <typeinfo>

namespace cs {

template <class T>
ControllerRequirements& ControllerRequirements::require_property( const std::string& name, bool require ) {
	m_property_requirements.emplace_back(
		name,
		typeid( T ).name(),
		require
	);

	return *this;
}

}
