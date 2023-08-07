#include "CLuaManager.h"
#include "CLuaNetworkedVars.h"

CLuaManager::CLuaManager()
{
	// ToDo
}

bool CLuaManager::CreateEntity(const char* class)
{
	bool worked = gSWEPManager->CreateEntity(class)
	if (!worked)
	{
		return gSENTManager->CreateEntity(class);
	}

	return true;
}

void CLuaManager::ParseString(const char* str)
{
	// ToDo
}

void CLuaManager::RunScript(const char* folder, const char* path)
{
	// ToDo
}

void CLuaManager::RunScriptsInFolder(const char* folder, const char* path)
{
	// ToDo
}

bool CLuaManager::ScriptExists(const char* folder, const char* path)
{
	// ToDo
}

void CLuaManager::SendScriptsInFolder(const char* folder, const char* path)
{
	// ToDo
}


void CLuaManager::Shutdown()
{
	// ToDo

	// ShutdownLuaClasses(ILuaInterface *);

	// LuaShared();

	// delete g_LuaNetworkedVars;
}

void CLuaManager::Startup()
{
	// ToDo

	g_LuaNetworkedVars = new CLuaNetworkedVars();

	// Load lua_shared -withjit

	// set g_Lua and g_LuaCallback

	// set VERSION and VERSIONSTR

	// set BRANCH

	// GarrysMod::FileServ::Add("lua/sent.txt");

	// InitLuaLibraries(ILuaInterface *);
	// InitLuaClasses(ILuaInterface *);

	// set SERVER and CLIENT

	// MakeLuaNULLEntity(void);

	// some weird !UNKNOWN and includes/init.lua

	// gGM == nullptr -> Error ( We should have a gGM at this point! )

	// CLuaGamemode::LoadGamemode("base");

	// again some weird !UNKNOW thing -> includes/dev_server_test.lua
}