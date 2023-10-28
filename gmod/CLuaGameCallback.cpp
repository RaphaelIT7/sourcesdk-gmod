#include "ILuaGameCallback.h"
#include "Colors.h"

Color server_msg(156, 241, 255, 200);
Color server_error(136, 221, 255, 255);
//Color client_msg(255, 241, 122, 200);
//Color client_error(255, 221, 102, 255);
//Color menu_msg(100, 220, 100, 200);
//Color menu_error(120, 220, 100, 255);

class CLuaGameCallback : public ILuaGameCallback
{
public:
	CLuaGameCallback( ) :
		lua( nullptr ),
		callback( nullptr )
	{ }

	~CLuaGameCallback( )
	{
		Reset( );
	}

	GarrysMod::Lua::ILuaObject *CreateLuaObject( )
	{
		return new CLuaObject();
	}

	void DestroyLuaObject( GarrysMod::Lua::ILuaObject *obj )
	{
		delete pObject;
	}

	void ErrorPrint( const char *error, bool print )
	{
		// Write into the lua_errors_server.txt if error logging is enabled.

		Color ErrorColor = server_error; // ToDo: Change this later and finish this function.
		ColorSpewMessage(SPEW_MESSAGE, &ErrorColor, "%s\n", error);
	}

	void Msg( const char *msg, bool useless )
	{
		MsgColour(msg, server_msg);
	}

	void MsgColour( const char *msg, const Color &color )
	{
		ColorSpewMessage(SPEW_MESSAGE, &color, "%s\n", msg);
	}

	void LuaError( const CLuaError *error )
	{
		
	}

	void InterfaceCreated( GarrysMod::Lua::ILuaInterface *iface )
	{
	}
};
