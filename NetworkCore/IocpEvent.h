#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	enum class EIocpEventType : uint8_t
	{
		Accept,
		Connect,
		Disconnect,
		Recv,
		Send
	};

	class IocpEvent : public WSAOVERLAPPED
	{
		// WSAOVERLAPPED �� ����Ͽ� �� ��ü�� IOCP �� ���� ���
		// ���� �Լ� ���� ����

	public:
		IocpEvent(EIocpEventType type);
	
		EIocpEventType _type;
	};

	class AcceptEvent : public IocpEvent
	{
	public:
		AcceptEvent() : IocpEvent(EIocpEventType::Accept) { }
	};

	class ConnectEvent : public IocpEvent
	{
	public:
		ConnectEvent() : IocpEvent(EIocpEventType::Connect) { }
	};

	class DisconnectEvent : public IocpEvent
	{
	public:
		DisconnectEvent() : IocpEvent(EIocpEventType::Disconnect) {}
	};

	class RecvEvent : public IocpEvent
	{
	public:
		RecvEvent() : IocpEvent(EIocpEventType::Recv) {}
	};

	class SendEvent : public IocpEvent
	{
	public:
		SendEvent() : IocpEvent(EIocpEventType::Send) {}

		// TODO : ���� ����
	};
}
