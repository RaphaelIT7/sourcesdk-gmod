#pragma once

#include "LuaInterface.h"
#include "CLuaManager.h"

extern ILuaInterface* g_Lua;

extern void GmodSetup(); // Always call this function!
extern void MakeLuaNULLEntity();

extern bool ConCommand_IsBlocked(const char*);
extern bool ConCommand_IsBlockedArg(const char*);