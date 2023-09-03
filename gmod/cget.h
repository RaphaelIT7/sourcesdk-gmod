class CGet
{
	~CGet();
	void* Analytics(); // ToDo: Get the correct return value
	IGMod_Audio* Analytics();
	const char* BuildName(); // ToDo: Get the correct return value
	IFileSystem* FileSystem();
	const char* FilterText(); // ToDo: Get the correct return value
	const char* GameDir();
	int GetClientCount();
	IGMHTML* HTML();
	void* Initialize();
	IIntroScreen* IntroScreen();
	bool IsDedicatedServer();
	ILuaConVars* LuaConVars();
	ILuaShared* LuaShared();
	IMaterialSystem* Materials();
	IMenuSystem* MenuSystem();
	IMotionSensor* MotionSensor();
	void* OnLoadFailed(const char*); // ToDo: Get the correct return value
	void* ResetRichPresense(); // ToDo: Get the correct return value
	void* ResetSteamAPIs(); // ToDo: Get the correct return value
	IResources* Resources();
	void RunSteamCallbacks();
	IServerAddons* ServerAddons(); // ToDo: Get the correct return value
	void SetMotionSensor(IMotionSensor*);
	void* ShutDown(); // ToDo: Get the correct return value
	void* SteamApps(); // ToDo: Get the correct return value
	ISteamApps* SteamApps();
	ISteamFriends* SteamFriends();
	ISteamGameServer* SteamGameServer();
	ISteamHTTP* SteamHTTP();
	ISteamNetworking* SteamNetworking();
	ISteamRemoteStorage* SteamRemoteStorage();
	ISteamUGC* SteamUGC();
	ISteamUser* SteamUser();
	ISteamUtils* SteamUtils();
	void* UpdateRichPresense(const char*); // ToDo: Get the correct return value
	int Version(); // ToDo: Get the correct return value
	const char* VersionStr(); // ToDo: Get the correct return value
	const char* VersionTimeStr(); // ToDo: Get the correct return value
}