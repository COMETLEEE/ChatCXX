#pragma once

namespace networkcore
{
	class IocpService;
	class Listener;
	class Session;

	using IocpServicePtr = std::shared_ptr<IocpService>;
	using ListenerPtr = std::shared_ptr<Listener>;
	using SessionPtr = std::shared_ptr<Session>;
	using SessionFactoryFunc = std::function<SessionPtr()>;
}
