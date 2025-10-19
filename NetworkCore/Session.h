#pragma once
#include "NetworkCoreMinimal.h"
#include "IocpObject.h"

namespace networkcore
{
	class NETWORKCORE_API Session : public IocpObject
	{
	public:
		void SetSocket(SOCKET socket);

		SOCKET GetSocket() const;

		void Dispatch(IocpEvent* iocpEvent, DWORD numBytes) override;

	private:
		SOCKET _socket;
	};
}
