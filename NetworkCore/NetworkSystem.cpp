#include "NetworkSystem.h"
#include "Logger.h"

namespace networkcore
{
	void NetworkSystem::Initialize()
	{
		WSAData wsaData;

		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (result != 0)
		{
			Logger::WriteError(std::format("Failed to WSAStart. Error code - {}", result));
		}

		Logger::WriteLine(std::format("Winsock intialized. Version : {}.{}", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion)));
	}

	void NetworkSystem::Cleanup()
	{
		WSACleanup();
	}
}