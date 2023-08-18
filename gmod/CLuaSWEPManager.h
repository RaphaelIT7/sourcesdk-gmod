class CLuaSWEPManager
{
public:
	~CLuaSWEPManager();
	bool CreateEntity(const char*);
	void LoadScript(const char*);
	void LoadScripts();
	void ReloadSpecific(const char*);
};

extern CLuaSWEPManager* gSWEPManager;