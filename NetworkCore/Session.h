#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	class NETWORKCORE_API Session
	{
	public:
		Session();

		virtual ~Session();

		SOCKET GetSocket() const;

		void SetSocket(SOCKET socket);

		void SetIocpService(IocpServicePtr iocpService);

		IocpServicePtr GetIocpService() const;

	private:
		IocpServicePtr _iocpService;

		SOCKET _socket;
	};
}
