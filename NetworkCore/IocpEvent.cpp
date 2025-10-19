#include "IocpEvent.h"

namespace networkcore
{
	IocpEvent::IocpEvent(EIocpEventType type) :
		_type{type}
	{
		OVERLAPPED::hEvent = 0;
		OVERLAPPED::Internal = 0;
		OVERLAPPED::InternalHigh = 0;
		OVERLAPPED::Offset = 0;
		OVERLAPPED::OffsetHigh = 0;
	}
}
