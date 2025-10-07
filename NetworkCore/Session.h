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

		void SetIocpService(IocpServicePtr iocpService);

	private:
		IocpServicePtr _iocpService;

		SOCKET _socket;
	};
}
