#include <FWCS/Controller.hpp>

namespace cs {

Controller::Controller( Entity& entity ) :
	m_entity( entity )
{
}

Controller::~Controller() {
}

Entity& Controller::get_entity() {
	return m_entity;
}

const Entity& Controller::get_entity() const {
	return m_entity;
}

}
