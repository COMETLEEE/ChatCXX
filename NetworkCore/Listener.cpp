#include "Listener.h"
#include "IocpService.h"
#include "Session.h"

namespace networkcore
{
	Listener::Listener(IocpServicePtr iocpService) 
		: _iocpService(iocpService)
	{

	}

	Listener::~Listener()
	{

	}

	void Listener::Dispatch(IocpEvent* iocpEvent, DWORD numBytes)
	{
		
		// ::CreateIoCompletionPort((HANDLE)_acceptSocket, _registeredIocpHandle);
		
		// Session 클래스의 소켓은 반드시 이 함수에서 할당한다
		SessionPtr session = _iocpService->CreateSession();

		session->SetSocket(_acceptSocket);

		// 다음 Accept 를 걸어둔다.
		PostAccept();
	}

	void Listener::PostAccept()
	{
	}

	void Listener::SetRegisteredIocpHandle(HANDLE iocpHandle)
	{
		_registeredIocpHandle = iocpHandle;
	}

	void Listener::SetAcceptSocket(SOCKET acceptSocket)
	{
		_acceptSocket = acceptSocket;
	}

	SOCKET Listener::GetAcceptSocket() const
	{
		return _acceptSocket;
	}

	char* Listener::GetAcceptOutBuffer()
	{
		return _acceptOutBuffer;
	}

	DWORD& Listener::GetAcceptBytesReceived()
	{
		return _acceptBytesReceived;
	}
}