#include <FWCS/Properties/Drag.hpp>

namespace cs {
namespace prop {

const std::string Drag::ID = "Drag";

Drag::Drag() :
	Property(),
	m_area( 0 ),
	m_resistance_coeff( 0 )
{
}

const std::string& Drag::get_id() const {
	return ID;
}

float Drag::get_area() const {
	return m_area;
}

void Drag::set_area( float area ) {
	m_area = area;
}

float Drag::get_resistance_coeff() const {
	return m_resistance_coeff;
}

void Drag::set_resistance_coeff( float resistence_coeff ) {
	m_resistance_coeff = resistence_coeff;
}

}
}
