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

	void Logger::WriteError(std::string_view errLog)
	{
		std::cerr << errLog << '\n';
	}

	void Logger::WriteError(std::wstring_view errLog)
	{
		std::wcerr << errLog << '\n';
	}
}
