#include <iostream>

#include "..\NetworkCore\IocpService.h"
#include "..\NetworkCore\NetworkUtil.h"

#include "ServerSession.h"

using namespace chatclient;

int main()
{
	std::cout << "Start ChatClient" << '\n';

	auto iocpService = networkcore::IocpService::CreateIocpService([]() { return std::make_shared<ServerSession>(); }, 1);

	return 0;
}