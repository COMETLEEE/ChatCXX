#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	/// <summary>
	/// Entire system class for network in windows
	/// </summary>
	class IocpService final
	{
	public:
		NETWORKCORE_API static IocpServicePtr CreateIocpService(SessionFactoryFunc defaultSessionFactory
			, unsigned int concurrency = std::jthread::hardware_concurrency());

		NETWORKCORE_API void Listen(int port);

	public:
		~IocpService();

		SessionPtr CreateSession();

		SessionPtr CreateSession(SessionFactoryFunc sessionFactory);

	private:
		IocpService(SessionFactoryFunc defaultSessionFactory, unsigned int concurrency);

		void RegisterSessionIocp(const SessionPtr& session);

		void StartIocp();

		void StopIocp();

		void WorkerIocp(std::stop_token st);

		HANDLE _iocpHandle;

		std::vector<std::jthread> _iocpWorkers;

		SessionFactoryFunc _defaultSessionFactory;

		std::set<SessionPtr> _sessions;

		const unsigned int _hardwareConcurrency;

		SOCKET _listenSocket;

		int _listenPort;

		const int _listenerCount;
	};
}
