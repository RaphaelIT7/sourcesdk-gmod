class CLuaEffectManager
{
public:
	~CLuaEffectManager();
	void LoadScript(const char*);
	void LoadScripts();
	void ReloadSpecific(const char*);
};

extern CLuaEffectManager* gEffectManager;