#include <FWCS/Executor.hpp>

namespace cs {

Executor::Executor( Entity& entity ) :
	m_entity( entity )
{
}

Executor::~Executor() {
}

Entity& Executor::get_entity() {
	return m_entity;
}

const Entity& Executor::get_entity() const {
	return m_entity;
}

}
