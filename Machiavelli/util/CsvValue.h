#pragma once
#include <string>

namespace util {
	template<char delum>
	class CsvValue : public std::string
	{
	};

	template<char delim>
	std::istream& operator>>(std::istream& is, CsvValue<delim>& output)
	{
		std::getline(is, output, ';');
		return is;
	}
}

