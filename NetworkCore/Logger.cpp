#include "Logger.h"

namespace networkcore
{
	void Logger::WriteLine(std::string_view log)
	{
		std::cout << log << '\n';
	}

	void Logger::WriteLine(std::wstring_view log)
	{
		std::wcout << log << '\n';
	}
}
