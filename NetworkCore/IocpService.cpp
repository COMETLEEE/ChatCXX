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
			Logger::WriteError(std::format("Failed to create iocp handle. Error code - {}"
				, GetLastError()));
		}
	}

	void IocpService::RegisterSessionIocp(const SessionPtr& session)
	{
		HANDLE result = CreateIoCompletionPort((HANDLE)session->GetSocket(), _iocpHandle
			, (ULONG_PTR)session.get(), 0);

		if (NULL == result)
		{
			Logger::WriteError(std::format("Failed to register session socket. Error code - {}"
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
		DWORD numBytes;
		ULONG_PTR completionKey;
		LPOVERLAPPED lpOverlapped;

		while (!st.stop_requested())
		{
			BOOL bOk = GetQueuedCompletionStatus(_iocpHandle, &numBytes, &completionKey, &lpOverlapped, INFINITE);
			DWORD error = GetLastError();

			// Worker thread 에서는 I/O 만 진행하고 로직은 싱글 스레드로 전부 이관
			if (bOk)
			{

			}
			else
			{

			}
		}
	}
}
