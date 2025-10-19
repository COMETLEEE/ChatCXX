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
		
		// Session Ŭ������ ������ �ݵ�� �� �Լ����� �Ҵ��Ѵ�
		SessionPtr session = _iocpService->CreateSession();

		session->SetSocket(_acceptSocket);

		// ���� Accept �� �ɾ�д�.
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