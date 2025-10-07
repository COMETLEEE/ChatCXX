#include "Session.h"

namespace networkcore
{
	Session::Session()
	{
	}

	Session::~Session()
	{
		 int result = closesocket(_socket);
	}

	SOCKET Session::GetSocket() const
	{
		return _socket;
	}

	void Session::SetIocpService(IocpServicePtr iocpService)
	{
		_iocpService = iocpService;
	}
}
