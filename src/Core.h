#ifndef CORE_H
#define CORE_H

#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#include <cstdlib>
#include <cstdint>
#include <string>

#ifdef __LINUX__
#include <cstring>
#endif

#define ZeroMemory(a,b) memset(a,0,b);

#define LONG_LONG_MAX_LEN 20

using logprintf_t = void(*)(const char* fmt, ...);
logprintf_t logprintf = nullptr;

#define NATIVE_DECLARE(func) cell AMX_NATIVE_CALL func(AMX* amx, cell* params)

namespace Utils
{
	inline void strval(const char* dest, long long& value) noexcept
	{
		int i;
		if (dest[0] == 45)
		{
			for (i = 1;; i++)
			{
				if (!(48 <= dest[i] && dest[i] <= 57)) break;
				value = (dest[i] - 48) + (value * 10);
			}
			value *= -1;
		}
		else for (i = 0;; i++)
		{
			if (!(48 <= dest[i] && dest[i] <= 57)) break;
			value = (dest[i] - 48) + (value * 10);
		}
	}
};

namespace Natives
{
	NATIVE_DECLARE(SetValueString)
	{
		cell* addr;
		char dest[LONG_LONG_MAX_LEN];
		ZeroMemory(dest, sizeof(dest));
		amx_GetAddr(amx, params[2], &addr);
		amx_GetString(dest, addr, NULL, LONG_LONG_MAX_LEN);

		long long value = 0;
		Utils::strval(dest, value);

		amx_GetAddr(amx, params[1], &addr);

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);

		return 1;
	}

	NATIVE_DECLARE(GetValueString)
	{
		cell* addr, *addrVal;
		amx_GetAddr(amx, params[1], &addrVal);
		amx_GetAddr(amx, params[2], &addr);
		amx_SetString(addr, std::to_string(static_cast<long long>(addrVal[0] + (static_cast<long long>(addrVal[1]) * 0x7FFFFFFF))).c_str(), NULL, NULL, LONG_LONG_MAX_LEN);
		return 1;
	}

	///////// CMP ///////////////////////////////////////////////////////////////////////////////////////////////

	NATIVE_DECLARE(CompareString)
	{
		cell* addr;
		char dest[LONG_LONG_MAX_LEN];
		amx_GetAddr(amx, params[2], &addr);
		amx_GetString(dest, addr, NULL, LONG_LONG_MAX_LEN);

		amx_GetAddr(amx, params[1], &addr);

		long long val1 = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));
		long long val2 = 0;

		Utils::strval(dest, val2);

		if (val1 >= val2) return (val1 < val2);
		return -1;
	}

	///////// ADD ///////////////////////////////////////////////////////////////////////////////////////////////

	// native lladd(value[stlonglong], value);
	NATIVE_DECLARE(Add)
	{
		cell* addr;

		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));

		value += params[2];

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);
		return 1;
	}

	// native lladd64(value[stlonglong], valuelow, valuehigh);
	NATIVE_DECLARE(Add64)
	{
		cell* addr;

		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));
		value += static_cast<long long>(params[2] + static_cast<long long>(params[3]) * 0x7FFFFFFF);

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);
		return 1;
	}

	// native lladdString(value[stlonglong], const value[]);
	NATIVE_DECLARE(AddString)
	{
		cell* addr;

		long long value = 0;

		char dest[LONG_LONG_MAX_LEN];
		amx_GetAddr(amx, params[2], &addr);
		amx_GetString(dest, addr, NULL, LONG_LONG_MAX_LEN);

		Utils::strval(dest, value);

		amx_GetAddr(amx, params[1], &addr);

		value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF)) + value;

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);

		return 1;
	}

	///////// SUB ///////////////////////////////////////////////////////////////////////////////////////////////

	// native llsub(value[stlonglong], value);
	NATIVE_DECLARE(Sub)
	{
		cell* addr;

		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));

		value -= params[2];

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);
		return 1;
	}

	// native llsub64(value[stlonglong], valuelow, valuehigh);
	NATIVE_DECLARE(Sub64)
	{
		cell* addr;

		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));
		value -= static_cast<long long>(params[2] + static_cast<long long>(params[3]) * 0x7FFFFFFF);

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);

		return 1;
	}

	// native llsubString(value[stlonglong], const value[]);
	NATIVE_DECLARE(SubString)
	{
		cell* addr;

		long long value = 0;

		char dest[LONG_LONG_MAX_LEN];
		amx_GetAddr(amx, params[2], &addr);
		amx_GetString(dest, addr, NULL, LONG_LONG_MAX_LEN);

		Utils::strval(dest, value);

		amx_GetAddr(amx, params[1], &addr);

		value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF)) - value;

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);

		return 1;
	}

	///////// MUL ///////////////////////////////////////////////////////////////////////////////////////////////

	NATIVE_DECLARE(Mul)
	{
		cell* addr;
		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));

		value *= static_cast<long long>(params[2]);

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);

		return 1;
	}

	// native llmul64(value[stlonglong], valuelow, valuehigh);
	NATIVE_DECLARE(Mul64)
	{
		cell* addr;
		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));

		long long mul = static_cast<long long>(
			params[2] + (static_cast<long long>(params[3]) * 0x7FFFFFFF)
			);

		value *= mul;

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);
		return 1;
	}

	// native llmulString(value[stlonglong], const value[]);
	NATIVE_DECLARE(MulString)
	{
		cell* addr;

		long long mul = 0;
		char dest[LONG_LONG_MAX_LEN];

		amx_GetAddr(amx, params[2], &addr);
		amx_GetString(dest, addr, NULL, LONG_LONG_MAX_LEN);

		Utils::strval(dest, mul);

		amx_GetAddr(amx, params[1], &addr);

		long long value = static_cast<long long>(addr[0] + (static_cast<long long>(addr[1]) * 0x7FFFFFFF));

		value *= mul;

		addr[0] = static_cast<cell>(value - static_cast<int>((value / 0x7FFFFFFF) * 0x7FFFFFFF));
		addr[1] = static_cast<cell>(value / 0x7FFFFFFF);

		return 1;
	}
};

AMX_NATIVE_INFO NativeList[] = {

	{ "llSetValueString", Natives::SetValueString },
	{ "llGetValueString", Natives::GetValueString },

	{ "llcmpString", Natives::CompareString },

	{ "lladd", Natives::Add },
	{ "lladd64", Natives::Add64 },
	{ "lladdString", Natives::AddString },

	{ "llsub", Natives::Sub },
	{ "llsub64", Natives::Sub64 },
	{ "llsubString", Natives::SubString },

	{ "llmul", Natives::Mul },
	{ "llmul64", Natives::Mul64 },
	{ "llmulString", Natives::MulString }
};

#endif