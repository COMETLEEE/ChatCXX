#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	class Listener;
	class AcceptEvent;

	enum class ESocketType
	{
		TCP,
		UDP
	};

	class NetworkUtil final
	{
	public:
		static void Initialize();
		static void Cleanup();

		static SOCKET CreateSocket(ESocketType socketType);
		static int CloseSocket(SOCKET& socket);

		static int Listen(SOCKET socket, int backlog);
		static int Bind(SOCKET socket, sockaddr_in& address);
		static int Accept(Listener* listener, AcceptEvent* acceptEvent, SOCKET listenSocket);

		static LPFN_ACCEPTEX s_acceptEx;
		static LPFN_CONNECTEX s_connectEx;
		static LPFN_DISCONNECTEX s_disconnectEx;
	};
}