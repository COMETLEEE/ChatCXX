#pragma once
#include "Defines.h"

// This class is exported from the dll
class NETWORKCORE_API CNetworkCore {
public:
	CNetworkCore(void);
	// TODO: add your methods here.
};

extern NETWORKCORE_API int nNetworkCore;

NETWORKCORE_API int fnNetworkCore(void);
