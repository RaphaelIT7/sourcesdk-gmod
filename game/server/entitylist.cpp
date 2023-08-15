//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "entitylist.h"
#include "utlvector.h"
#include "igamesystem.h"
#include "collisionutils.h"
#include "UtlSortVector.h"
#include "tier0/vprof.h"
#include "mapentities.h"
#include "client.h"
#include "globalstate.h"
#include "datacache/imdlcache.h"

#ifdef HL2_DLL
#include "npc_playercompanion.h"
#endif // HL2_DLL

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static CUtlVector<IServerNetworkable*> g_DeleteList;

CGlobalEntityList gEntList;
CBaseEntityList *g_pEntityList = &gEntList;

CGlobalEntityList::CGlobalEntityList()
{
	m_iHighestEnt = m_iNumEnts = m_iNumEdicts = 0;
	m_bClearingEntities = false;
}

void CGlobalEntityList::OnAddEntity(IHandleEntity* pEnt, CBaseHandle handle)
{
	int i = handle.GetEntryIndex();

	// record current list details
	m_iNumEnts++;
	if (i > m_iHighestEnt)
		m_iHighestEnt = i;

	// If it's a CBaseEntity, notify the listeners.
	CBaseEntity* pBaseEnt = static_cast<IServerUnknown*>(pEnt)->GetBaseEntity();
	if (pBaseEnt->edict())
		m_iNumEdicts++;

	// NOTE: Must be a CBaseEntity on server
	Assert(pBaseEnt);
	//DevMsg(2,"Created %s\n", pBaseEnt->GetClassname() );
	for (i = m_entityListeners.Count() - 1; i >= 0; i--)
	{
		m_entityListeners[i]->OnEntityCreated(pBaseEnt);
	}
}

//static bool g_fInCleanupDelete;
void CGlobalEntityList::OnRemoveEntity(IHandleEntity* pEnt, CBaseHandle handle)
{
#ifdef DBGFLAG_ASSERT
	//if (!g_fInCleanupDelete)
	//{
		int i;
		for (i = 0; i < g_DeleteList.Count(); i++)
		{
			if (g_DeleteList[i]->GetEntityHandle() == pEnt)
			{
				g_DeleteList.FastRemove(i);
				Msg("ERROR: Entity being destroyed but previously threaded on g_DeleteList\n");
				break;
			}
		}
	//}
#endif

	CBaseEntity* pBaseEnt = static_cast<IServerUnknown*>(pEnt)->GetBaseEntity();
	if (pBaseEnt->edict())
		m_iNumEdicts--;

	m_iNumEnts--;
}