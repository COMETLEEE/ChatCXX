#include "NetworkUtil.h"
#include "Logger.h"

#include "Listener.h"
#include "IocpEvent.h"

namespace networkcore
{
	LPFN_ACCEPTEX NetworkUtil::s_acceptEx = nullptr;
	LPFN_CONNECTEX NetworkUtil::s_connectEx = nullptr;
	LPFN_DISCONNECTEX NetworkUtil::s_disconnectEx = nullptr;

	void NetworkUtil::Initialize()
	{
		WSAData wsaData;

		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (result != 0)
		{
			Logger::WriteError(std::format("Failed to WSAStart. Error code - {}", result));
		}

		Logger::WriteLine(std::format("Winsock intialized. Version : {}.{}", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion)));
	
		GUID acceptExGuid = WSAID_ACCEPTEX;
		GUID connectExGuid = WSAID_CONNECTEX;
		GUID disconnExGuid = WSAID_DISCONNECTEX;

		SOCKET tempSocket = CreateSocket(ESocketType::TCP);
		DWORD dwBytes;

		if (SOCKET_ERROR == WSAIoctl(tempSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &acceptExGuid, sizeof(acceptExGuid)
			, &s_acceptEx, sizeof(s_acceptEx), &dwBytes, nullptr, nullptr))
		{
			Logger::WriteError(std::format("WSAIoctl for AcceptEx failed. Error - {}", WSAGetLastError()));
		}

		if (SOCKET_ERROR == WSAIoctl(tempSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &connectExGuid, sizeof(connectExGuid)
			, &s_connectEx, sizeof(s_connectEx), &dwBytes, nullptr, nullptr))
		{
			Logger::WriteError(std::format("WSAIoctl for ConnectEx failed. Error - {}", WSAGetLastError()));
		}

		if (SOCKET_ERROR == WSAIoctl(tempSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &disconnExGuid, sizeof(disconnExGuid)
			, &s_disconnectEx, sizeof(s_disconnectEx), &dwBytes, nullptr, nullptr))
		{
			Logger::WriteError(std::format("WSAIoctl for ConnectEx failed. Error - {}", WSAGetLastError()));
		}

		CloseSocket(tempSocket);
	}

	void NetworkUtil::Cleanup()
	{
		WSACleanup();
	}

	SOCKET NetworkUtil::CreateSocket(ESocketType socketType)
	{
		SOCKET retSocket = NULL;

		switch (socketType)
		{
			case ESocketType::TCP:
			{
				retSocket = ::WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, NULL, WSA_FLAG_OVERLAPPED);
			}
			break;

			case ESocketType::UDP:
			{
				retSocket = ::WSASocketW(AF_INET, SOCK_DGRAM, IPPROTO_UDP, nullptr, NULL, WSA_FLAG_OVERLAPPED);
			}
			break;
		}

		if (INVALID_SOCKET == retSocket)
		{
			Logger::WriteError("Invalid socket created.");
			ASSERT_MSG("Invalid socket created.");
		}

		return retSocket;
	}

	int NetworkUtil::CloseSocket(SOCKET& socket)
	{
		int ret = ::closesocket(socket);

		socket = INVALID_SOCKET;

		return ret;
	}

	int NetworkUtil::Listen(SOCKET socket, int backlog)
	{
		return ::listen(socket, backlog);
	}

	int NetworkUtil::Bind(SOCKET socket, sockaddr_in& address)
	{
		return ::bind(socket, reinterpret_cast<sockaddr*>(&address), sizeof(sockaddr));
	}

	int NetworkUtil::Accept(Listener* listener, AcceptEvent* acceptEvent, SOCKET listenSocket)
	{
		int result = s_acceptEx(listenSocket, listener->GetAcceptSocket(), listener->GetAcceptOutBuffer(), 0
			, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &listener->GetAcceptBytesReceived(), acceptEvent);

		if (result == FALSE && WSAGetLastError() != ERROR_IO_PENDING)
		{
			Logger::WriteError(std::format("Accept failed : %d", WSAGetLastError()));
		}

		return result;
	}
}