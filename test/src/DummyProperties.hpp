#pragma once

#include <FWCS/Property.hpp>

class DummyProperty0 : public cs::Property {
	public:
		static const std::string ID;

		const std::string& get_id() const {
			return ID;
		}
};

class DummyProperty1 : public cs::Property {
	public:
		static const std::string ID;

		const std::string& get_id() const {
			return ID;
		}
};
