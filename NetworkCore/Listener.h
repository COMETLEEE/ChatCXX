#pragma once
#include "IocpObject.h"

namespace networkcore
{
	class Listener : public IocpObject
	{
	public:
		Listener(IocpServicePtr iocpService);

		virtual ~Listener();
		
		void Dispatch(IocpEvent* iocpEvent, DWORD numBytes) override;

		void PostAccept();

		void SetRegisteredIocpHandle(HANDLE iocpHandle);

		void SetAcceptSocket(SOCKET acceptSocket);

		SOCKET GetAcceptSocket() const;

		char* GetAcceptOutBuffer();

		DWORD& GetAcceptBytesReceived();

	private:
		IocpServicePtr _iocpService;

		HANDLE _registeredIocpHandle;

		SOCKET _acceptSocket;

		char _acceptOutBuffer[64];

		DWORD _acceptBytesReceived;
	};
}
