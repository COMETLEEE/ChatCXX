#pragma once

#ifdef NETWORKCORE_EXPORTS
#define NETWORKCORE_API __declspec(dllexport)
#else
#define NETWORKCORE_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#	define ASSERT_MSG(msg) assert(msg && false)
#else // _DEBUG
#	define ASSERT_MSG(msg) __noop;
#endif // _DEBUG

#define cnew new
