#include <iostream>

#include "..\NetworkCore\IocpService.h"
#include "..\NetworkCore\NetworkSystem.h"

#include "ClientSession.h"
using namespace chatserver;

int main()
{
	std::cout << "Start ChatServer" << '\n';

	networkcore::NetworkSystem::Initialize();

	auto iocpService = networkcore::IocpService::CreateIocpService([]() { return std::make_shared<ClientSession>(); });










	networkcore::NetworkSystem::Cleanup();

	return 0;
}