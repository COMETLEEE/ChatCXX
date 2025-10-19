#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	class IocpEvent;

	class IocpObject
	{
	public:
		virtual void Dispatch(IocpEvent* iocpEvent, DWORD numBytes) = 0;

	protected:
		~IocpObject() = default;
	};
}
