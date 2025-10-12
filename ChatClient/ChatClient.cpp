#include <iostream>

#include "..\NetworkCore\IocpService.h"
#include "..\NetworkCore\NetworkSystem.h"

#include "ServerSession.h"

using namespace chatclient;

int main()
{
	std::cout << "Start ChatClient" << '\n';

	networkcore::NetworkSystem::Initialize();

	auto iocpService = networkcore::IocpService::CreateIocpService([]() { return std::make_shared<ServerSession>(); }, 1);
	








	networkcore::NetworkSystem::Cleanup();

	return 0;
}