
#include "NetworkCore.h"

// This is an example of an exported variable
NETWORKCORE_API int nNetworkCore=0;

// This is an example of an exported function.
NETWORKCORE_API int fnNetworkCore(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CNetworkCore::CNetworkCore()
{
    return;
}
