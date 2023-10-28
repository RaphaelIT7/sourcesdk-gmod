#include "ILuaGameCallback.h"

class CLuaGameCallback : public ILuaGameCallback
{
public:
	ILuaObject *CreateLuaObject();
	void DestroyLuaObject(ILuaObject* pObject);
	ErrorPrint(const char* error, bool print);
	void Msg(const char* msg, bool isServer);
	void MsgColour(const char* msg, const Color& color);
	void LuaError(const CLuaError* error);
	void InterfaceCreated(ILuaInterface* iface) {};
}