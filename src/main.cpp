#include "SDK/amx/amx.h"

#ifndef WIN32
#ifndef __LINUX__
#define __LINUX__
#endif
#endif

#include "SDK/plugincommon.h"
#include "Core.h"

#define PLUGIN_NAME "longlong"
#define PLUGIN_AUTHOR "oukibt"

extern void *pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_AMX_NATIVES | SUPPORTS_VERSION;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = reinterpret_cast<logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);
	if (NULL == pAMXFunctions || NULL == logprintf) return false;
	logprintf("  %s by %s loaded.", PLUGIN_NAME, PLUGIN_AUTHOR);
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("  %s unloaded", PLUGIN_NAME);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	amx_Register(amx, NativeList, sizeof(NativeList) / sizeof(AMX_NATIVE_INFO));
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}