#include "IocpService.h"
#include "Session.h"
#include "Logger.h"
#include "NetworkUtil.h"

#include "IocpEvent.h"
#include "IocpObject.h"
#include "Listener.h"

namespace networkcore
{
	IocpServicePtr IocpService::CreateIocpService(SessionFactoryFunc defaultSessionFactory
		, unsigned int concurrency)
	{
		auto iocpService = IocpServicePtr{new IocpService {defaultSessionFactory, concurrency}};

		return iocpService;
	}

	void IocpService::Listen(int listenPort)
	{
		_listenSocket = NetworkUtil::CreateSocket(ESocketType::TCP);
		_listenPort = listenPort;

		SOCKADDR_IN addr{};

		addr.sin_family = AF_INET;
		addr.sin_port = htons(_listenPort);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);

		NetworkUtil::Bind(_listenSocket, addr);
		NetworkUtil::Listen(_listenSocket, SOMAXCONN);

		::CreateIoCompletionPort((HANDLE)_listenSocket, _iocpHandle, (ULONG_PTR)_listenSocket, 0);

		for (int i = 0; i < _listenerCount; ++i)
		{
			/*Listener* listener = cnew Listener(this);

			listener->PostAccept()

			SOCKET acceptSocket = NetworkUtil::CreateSocket(ESocketType::TCP);

			listener->SetAcceptSocket(acceptSocket);

			AcceptEvent* acceptEvent = cnew AcceptEvent();

			NetworkUtil::Accept(listener, acceptEvent, _listenSocket);*/
		}
	}

	IocpService::IocpService(SessionFactoryFunc defaultSessionFactory, unsigned int concurrency) :
		_defaultSessionFactory(defaultSessionFactory)
		, _hardwareConcurrency(concurrency)
		, _listenSocket{INVALID_SOCKET}
		, _listenPort{INT_MAX}
		, _listenerCount{8}
	{
		NetworkUtil::Initialize();

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

		// 해당 세션 소켓을 IOCP 에 걸어둔다.

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

		NetworkUtil::CloseSocket(_listenSocket);

		NetworkUtil::Cleanup();
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

	// IOCP worker thread 에서는 I/O 만 진행
	// 로직 진행은 전용 싱글 스레드로 전부 이관되도록 디자인
	// Lock 최소화 디자인
	void IocpService::WorkerIocp(std::stop_token st)
	{
		DWORD numBytes;
		IocpObject* iocpObject;
		IocpEvent* iocpEvent;

		while (!st.stop_requested())
		{
			BOOL bOk = ::GetQueuedCompletionStatus(_iocpHandle, &numBytes, reinterpret_cast<ULONG_PTR*>(&iocpObject), reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), INFINITE);

			if (bOk)
			{
				iocpObject->Dispatch(iocpEvent, numBytes);
			}
			else
			{
				DWORD error = ::WSAGetLastError();

				switch (error)
				{
					case WAIT_TIMEOUT:
					break;

					default:
					{

					}
					break;
				}
			}
		}
	}
}
