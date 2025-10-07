#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	class IocpService final
	{
	public:
		NETWORKCORE_API static IocpServicePtr CreateIocpService(SessionFactoryFunc defaultSessionFactory
			, unsigned int concurrency = std::jthread::hardware_concurrency());

		~IocpService();

	private:
		IocpService(SessionFactoryFunc defaultSessionFactory, unsigned int concurrency);

		SessionPtr CreateSession();

		SessionPtr CreateSession(SessionFactoryFunc sessionFactory);

		void RegisterSessionIocp(const SessionPtr& session);

		void StartIocp();

		void StopIocp();

		void WorkerIocp(std::stop_token st);

		SessionFactoryFunc _defaultSessionFactory;

		HANDLE _iocpHandle;

		std::vector<std::jthread> _iocpWorkers;

		const unsigned int _hardwareConcurrency;
	};
}
