#include "CLuaEffectManager.h"
#include "CLuaSENTManager.h"
#include "CLuaSWEPManager.h"

class CLuaManager
{
public:
	~CLuaManager();
	bool CreateEntity(const char*);
	void ParseString(const char*);
	void RunScript(const char*, const char*, bool, const char*);
	void RunScriptsInFolder(const char*, const char*);
	bool ScriptExists(const char*, const char*);
	void Shutdown();
	void Startup();
};

extern CLuaManager* g_LuaManager;