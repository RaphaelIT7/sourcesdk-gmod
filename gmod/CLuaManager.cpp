#include "CLuaManager.h"
#include "CLuaNetworkedVars.h"
#include "tier0/icommandline.h"
#include "CLuaBase.h"

CLuaManager::CLuaManager()
{
	g_LuaManager = this;
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

void CLuaManager::SendScriptsInFolder(const char* reload, const char* folder)
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

	RunScriptsInFolder("!RELOAD", "autorun");
	SendScriptsInFolder("!RELOAD_CL", "matproxy");
	SendScriptsInFolder("!RELOAD_CL", "postprocess");
	SendScriptsInFolder("!RELOAD_CL", "vgui");
	SendScriptsInFolder("", "skins"); // ???
	SendScriptsInFolder("!RELOAD", "autorun");
	SendScriptsInFolder("!RELOAD_CL", "autorun/client");
	RunScriptsInFolder("!RELOAD_SV", "autorun/");
	RunScriptsInFolder("!RELOAD_SV", "autorun/server/sensorbones");

	if (CommandLine()->CheckParm("-systemtest"))
	{
		g_Lua->FindAndRunScript("includes/dev_server_test.lua", true, true, "!UNKNOWN", true); // Propably another function is used.
		// spawn one bot
	}
}

CLuaManager* g_LuaManager;