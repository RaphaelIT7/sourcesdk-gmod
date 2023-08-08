#include "tier0/icommandline.h"
#include "game/server/enginecallback.h"
#include "game/server/playerinfomanager.h"
#include <FactoryLoader.hpp>
#include "Interface.h"
#include "CLuaBase.h"
#include "edict.h"
#include <vector>

ILuaInterface* g_Lua;

void MakeLuaNULLEntity()
{

}

SourceSDK::FactoryLoader server_loader("server");

CGlobalVars* gpGlobals;
void GmodSetup()
{
	IPlayerInfoManager* player_info_manager = server_loader.GetInterface<IPlayerInfoManager>("PlayerInfoManager002");

	gpGlobals = player_info_manager->GetGlobalVars();
}

std::vector<const char*> s_BannedConvars = {
	"_restart",
	"alias",
	"askconnect_accept",
	"bind",
	"bind_mac",
	"bindtoggle",
	"buildcubemaps",
	"cef_credits",
	"cl_allowdownload",
	"cl_allowupload",
	"cl_chatfilters",
	"cl_downloadfilter",
	"cl_enable_loadingurl",
	"cl_logofile",
	"cl_mouseenable",
	"cl_software_cursor",
	"clear",
	"con_enable",
	"con_filter_dupe",
	"con_filter_enable",
	"con_filter_text",
	"con_filter_text_out",
	"con_logfile",
	"connect",
	"crosshair",
	"debug_dump",
	"echo",
	"ent_fire",
	"ent_setname",
	"exec",
	"exit",
	"gamemode_reload",
	"gamemode_reload_cl",
	"gameui_hide",
	"gameui_preventescapetoshow",
	"gameui_show_dialog",
	"gm_video",
	"hideconsole",
	"host_writeconfig",
	"hud_fastswitch",
	"incrementvar",
	"lightprobe",
	"log",
	"lookspring",
	"lookstrafe",
	"lservercfgfile",
	"lua_cookieclear",
	"lua_error_url",
	"lua_open",
	"lua_openscript",
	"lua_openscript_cl",
	"lua_redownload",
	"lua_reloadents",
	"lua_reloadents_cl",
	"lua_run",
	"lua_run_cl",
	"lua_showerrors_cl",
	"lua_showerrors_sv",
	"m_customaccel",
	"m_customaccel_exponent",
	"m_customaccel_scale",
	"m_forward",
	"m_mouseaccel1",
	"m_mouseaccel2",
	"m_mousespeed",
	"m_pitch",
	"m_side",
	"m_yaw",
	"mat_color_projection",
	"mat_crosshair_explorer",
	"mat_dxlevel",
	"mat_savechanges",
	"mat_setvideomode",
	"mat_texture_limit",
	"mat_viewportscale",
	"mat_viewportupscale",
	"menu_reload",
	"movie_fixwave",
	"mp_flashlight",
	"multvar",
	"name",
	"plugin_load",
	"quit",
	"quti",
	"r_aspect",
	"rcon_address",
	"rcon_password",
	"sensitivity",
	"servercfgfile",
	"snd_buildcache",
	"snd_ducktovolume",
	"snd_gain",
	"snd_gain_max",
	"snd_gain_min",
	"snd_mixahead",
	"snd_musicvolume",
	"snd_pitchquality",
	"suitvolume",
	"sv_cheats",
	"sv_logfilename_format",
	"sv_logsdir",
	"test_randomchance",
	"test_startscript",
	"toggle",
	"toggleconsole",
	"unbind",
	"unbind_mac",
	"unbindall",
	"voice_avggain",
	"voice_enable",
	"voice_fadeouttime",
	"voice_forcemicrecord",
	"voice_gain_downward_multiplier",
	"voice_gain_max",
	"voice_gain_rate",
	"voice_gain_target",
	"voice_inputfromfile",
	"voice_loopback",
	"voice_maxgain",
	"voice_modenable",
	"voice_overdrive",
	"voice_scale",
	"voice_recordtofile",
	"volume",
	"volume_sfx",
}
bool ConCommand_IsBlocked(const char*)
{
	// ToDo:
}

bool ConCommand_IsBlockedArg(const char*)
{
	// ToDo:
}

// Some engine functions

LUA_FUNCTION(engine_CloseServer)
{
	if (CommandLine()->CheckParm("-systemtest"))
	{
		Msg("engine.CloseServer called!\n");

		engine->ServerCommand("quit");
	}

	return 0;
}

LUA_FUNCTION(engine_LightStyle)
{
	int lightstyle = LUA->CheckNumber(1);
	const char* pattern = LUA->CheckString(2);

	engine->LightStyle(lightstyle, pattern);

	return 0;
}

LUA_FUNCTION(engine_TickCount)
{
	LUA->PushNumber(gpGlobals->tickcount);

	return 1;
}

LUA_FUNCTION(engine_AbsoluteFrameTime)
{
	LUA->PushNumber(gpGlobals->absoluteframetime);

	return 1;
}

LUA_FUNCTION(engine_TickInterval)
{
	LUA->PushNumber(gpGlobals->interval_per_tick);

	return 1;
}