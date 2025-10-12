#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	class Logger
	{
	public:
		static void WriteLine(std::string_view log);

		static void WriteLine(std::wstring_view log);

		static void WriteError(std::string_view errLog);

		static void WriteError(std::wstring_view errLog);
	};
}
