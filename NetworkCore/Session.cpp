#include "Session.h"

namespace networkcore
{
	Session::Session() :
		_iocpService{}
		, _socket{}
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

	void Session::SetSocket(SOCKET socket)
	{
		_socket = socket;
	}

	void Session::SetIocpService(IocpServicePtr iocpService)
	{
		_iocpService = iocpService;
	}

	IocpServicePtr Session::GetIocpService() const
	{
		return _iocpService;
	}
}
