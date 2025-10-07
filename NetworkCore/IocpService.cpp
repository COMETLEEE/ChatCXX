#include "IocpService.h"
#include "Session.h"
#include "Logger.h"

namespace networkcore
{
	IocpServicePtr IocpService::CreateIocpService(SessionFactoryFunc defaultSessionFactory
		, unsigned int concurrency)
	{
		auto iocpService = IocpServicePtr{new IocpService {defaultSessionFactory, concurrency}};

		return iocpService;
	}

	IocpService::IocpService(SessionFactoryFunc defaultSessionFactory, unsigned int concurrency) :
		_defaultSessionFactory(defaultSessionFactory)
		, _hardwareConcurrency(concurrency)
	{
		_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL
			, NULL, _hardwareConcurrency);

		StartIocp();

		if (NULL == _iocpHandle)
		{
			Logger::WriteLine(std::format("Failed to create iocp handle. Error code - {}"
				, GetLastError()));
		}
	}

	void IocpService::RegisterSessionIocp(const SessionPtr& session)
	{
		HANDLE result = CreateIoCompletionPort((HANDLE)session->GetSocket(), _iocpHandle
			, (ULONG_PTR)session.get(), 0);

		if (NULL == result)
		{
			Logger::WriteLine(std::format("Failed to register session socket. Error code - {}"
				, GetLastError()));
		}
	}

	IocpService::~IocpService()
	{
		StopIocp();

		CloseHandle(_iocpHandle);
	}

	SessionPtr IocpService::CreateSession()
	{
		return CreateSession(_defaultSessionFactory);
	}

	SessionPtr IocpService::CreateSession(SessionFactoryFunc sessionFactory)
	{
		SessionPtr session = sessionFactory();

		RegisterSessionIocp(session);

		return session;
	}

	void IocpService::StartIocp()
	{
		_iocpWorkers.reserve(_hardwareConcurrency);

		for (unsigned int i = 0; i < _hardwareConcurrency; ++i)
		{
			_iocpWorkers.emplace_back([this](std::stop_token st) { this->WorkerIocp(st); });
		}
	}

	void IocpService::StopIocp()
	{
		for (unsigned int i = 0 ; i < _hardwareConcurrency ; ++i)
		{
			_iocpWorkers[i].request_stop();
		}
	}

	void IocpService::WorkerIocp(std::stop_token st)
	{
		while (!st.stop_requested())
		{
			/*if (GetQueuedCompletionStatusEx())
			{

			}
			else
			{

			}*/
		}
	}
}
