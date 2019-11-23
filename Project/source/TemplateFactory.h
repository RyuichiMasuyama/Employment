#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace DesignPattern {

	class TemplateFactory {
	private:
		std::unordered_map<std::string, int> m_parts;
	
	public:

	};

	class Parts {

	};

	class PartsID {
	private:
		std::string m_parts_id;

	public:
		PartsID(std::string _parts_id) :m_parts_id(m_parts_id) {};
	};
}
