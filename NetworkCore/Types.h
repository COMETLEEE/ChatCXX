#pragma once

namespace networkcore
{
	class IocpService;
	class Session;

	using IocpServicePtr = std::shared_ptr<IocpService>;
	using SessionPtr = std::shared_ptr<Session>;
	using SessionFactoryFunc = SessionPtr(*)();
}
