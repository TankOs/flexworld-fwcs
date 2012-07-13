#include <FWCS/Entity.hpp>
#include <FWCS/Property.hpp>

namespace cs {

Entity::Entity( EntityID id ) :
	m_id( id )
{
}

Entity::~Entity() {
	PropertyMap::iterator prop_iter = m_properties.begin();
	PropertyMap::iterator prop_iter_end = m_properties.end();
	
	for( ; prop_iter != prop_iter_end; ++prop_iter ) {
		delete prop_iter->second;
	}
}

EntityID Entity::get_id() const {
	return m_id;
}

std::size_t Entity::get_num_properties() const {
	return m_properties.size();
}

}
