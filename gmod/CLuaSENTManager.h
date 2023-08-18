class CLuaSENTManager
{
public:
	~CLuaSENTManager();
	bool CreateEntity(const char*);
	void LoadScript(const char*);
	void LoadScripts();
	void ReloadSpecific(const char*);
};

extern CLuaSENTManager* gSENTManager;