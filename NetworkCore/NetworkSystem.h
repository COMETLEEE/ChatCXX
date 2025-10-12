#pragma once
#include "NetworkCoreMinimal.h"

namespace networkcore
{
	class NetworkSystem final
	{
	public:
		NETWORKCORE_API static void Initialize();
		NETWORKCORE_API static void Cleanup();

	private:
		static LPFN_ACCEPTEX s_acceptEx;
		static LPFN_CONNECTEX s_connectEx;
		static LPFN_DISCONNECTEX s_disconnectEx;
	};
}