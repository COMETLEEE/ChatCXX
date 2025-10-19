#include "Session.h"
#include "IocpEvent.h"

namespace networkcore
{
	void Session::SetSocket(SOCKET socket)
	{
		_socket = socket;
	}

	SOCKET Session::GetSocket() const
	{
		return _socket;
	}

	void Session::Dispatch(IocpEvent* iocpEvent, DWORD numBytes)
	{
		switch (iocpEvent->_type)
		{
			case EIocpEventType::Recv:
			{

			}
			break;

			case EIocpEventType::Send:
			{

			}
			break;

			case EIocpEventType::Disconnect:
			{

			}
			break;
		}
	}
}
