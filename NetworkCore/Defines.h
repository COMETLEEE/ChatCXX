#pragma once

#ifdef NETWORKCORE_EXPORTS
#define NETWORKCORE_API __declspec(dllexport)
#else
#define NETWORKCORE_API __declspec(dllimport)
#endif
