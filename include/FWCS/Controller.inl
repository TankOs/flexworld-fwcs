#include <typeinfo>
#include <algorithm>
#include <cassert>

namespace cs {

template <class PT>
void Controller::listen_for( const std::string& property ) {
	assert( property.empty() == false );

	IdTypePair pair( property, typeid( PT ).name() );

	assert(
		std::find(
			m_required_properties.begin(),
			m_required_properties.end(),
			pair
		) == m_required_properties.end()
	);

	m_required_properties.push_back( pair );
}

}
