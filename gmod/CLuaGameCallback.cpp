#include "ILuaGameCallback.h"

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
		return callback->CreateLuaObject( );
	}

	void DestroyLuaObject( GarrysMod::Lua::ILuaObject *obj )
	{
		callback->DestroyLuaObject( obj );
	}

	void ErrorPrint( const char *error, bool print )
	{
		callback->ErrorPrint( error, print );
	}

	void Msg( const char *msg, bool useless )
	{
		callback->Msg( msg, useless );
	}

	void MsgColour( const char *msg, const Color &color )
	{
		callback->MsgColour( msg, color );
	}

	void LuaError( const CLuaError *error )
	{
		const std::string &error_str = runtime ? runtime_error : error->message;

		common::ParsedError parsed_error;
		if( entered_hook || !common::ParseError( error_str, parsed_error ) )
			return callback->LuaError( error );

		const int32_t funcs = LuaHelpers::PushHookRun( lua, "LuaError" );
		if( funcs == 0 )
			return callback->LuaError( error );

		lua->PushBool( runtime );
		lua->PushString( error_str.c_str( ) );

		lua->PushString( parsed_error.source_file.c_str( ) );
		lua->PushNumber( parsed_error.source_line );
		lua->PushString( parsed_error.error_string.c_str( ) );

		if( runtime )
		{
			runtime_stack.Push( );
			runtime_stack.Free( );
		}
		else
			PushStackTable( lua );

		runtime = false;

		const auto source_addon = FindWorkshopAddonFromFile( parsed_error.source_file );
		if( source_addon == nullptr )
		{
			lua->PushNil( );
			lua->PushNil( );
		}
		else
		{
			lua->PushString( source_addon->title.c_str( ) );
			lua->PushString( std::to_string( source_addon->wsid ).c_str( ) );
		}

		entered_hook = true;
		const bool call_success = LuaHelpers::CallHookRun( lua, 8, 1 );
		entered_hook = false;
		if( !call_success )
			return callback->LuaError( error );

		const bool proceed = !lua->IsType( -1, GarrysMod::Lua::Type::BOOL ) || !lua->GetBool( -1 );
		lua->Pop( 1 );
		if( proceed )
			return callback->LuaError( error );
	}

	void InterfaceCreated( GarrysMod::Lua::ILuaInterface *iface )
	{
		callback->InterfaceCreated( iface );
	}

	void SetLua( GarrysMod::Lua::ILuaInterface *iface )
	{
		lua = static_cast<GarrysMod::Lua::CLuaInterface *>( iface );
		callback = lua->GetLuaGameCallback( );
	}

	void Detour( )
	{
		lua->SetLuaGameCallback( this );
	}

	void Reset( )
	{
		lua->SetLuaGameCallback( callback );
	}

private:
	GarrysMod::Lua::CLuaInterface *lua;
	GarrysMod::Lua::ILuaGameCallback *callback;
	bool entered_hook = false;
};
