#include <iostream>

#include "..\NetworkCore\IocpService.h"
#include "..\NetworkCore\NetworkUtil.h"

#include "ClientSession.h"
using namespace chatserver;

int main()
{
	std::cout << "Start ChatServer" << '\n';

	auto iocpService = networkcore::IocpService::CreateIocpService([]() { return std::make_shared<ClientSession>(); });

	iocpService->Listen(7777);

	return 0;
}