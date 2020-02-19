#if defined RDZ_KICKBAN_Included_
   #endinput
#endif

#define RDZ_KICKBAN_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define FIX_KICK 0
#define FIX_BAN 1
#define FIX_BANEX 2

static BANEX_REASON[MAX_PLAYERS][STRING_SIZE_MEDIUM];
stock RDZ_Kick(playerid)
{
    if(playerid < 0 || playerid > MAX_PLAYERS) return 0;
    if(!IsPlayerConnected(playerid)) return 0;
    MessUpSettings(playerid);
    SetTimerEx("kickban_FIX", KICKBAN_FIX_WAIT, false, "ii", playerid, FIX_KICK);
    return 1;
}

stock RDZ_Ban(playerid)
{
    if(playerid < 0 || playerid > MAX_PLAYERS) return 0;
    if(!IsPlayerConnected(playerid)) return 0;
    MessUpSettings(playerid);
    SetTimerEx("kickban_FIX", KICKBAN_FIX_WAIT, false, "ii", playerid, FIX_BAN);
    return 1;
}

stock RDZ_BanEx(playerid, const reason[])    
{
    if(playerid < 0 || playerid > MAX_PLAYERS) return 0;
    if(!IsPlayerConnected(playerid)) return 0;
    MessUpSettings(playerid);
    format(BANEX_REASON[playerid], STRING_SIZE_MEDIUM, "%s", reason);
    SetTimerEx("kickban_FIX", KICKBAN_FIX_WAIT, false, "ii", playerid, FIX_BANEX);
    return 1;
}

forward kickban_FIX(playerid, fix_type);
public kickban_FIX(playerid, fix_type)
{
    #if !defined RDZ_DEBUG_MODE
        switch(fix_type)
        {
            case FIX_KICK:
            {
                Kick(playerid);
            }
            case FIX_BAN:
            {
                Ban(playerid);
            }
            case FIX_BANEX:
            {
                BanEx(playerid, BANEX_REASON[playerid]);
            }
        }
    #endif
    return 1;
}

static MessUpSettings(playerid)
{
    SetPlayerWeather(playerid, 999);
    SetPlayerVirtualWorld(playerid, 999);
    SetPlayerInterior(playerid, 999);
    return 1;
}

#if defined _ALS_Kick
  #undef Kick
#else
	#define _ALS_Kick
#endif


#if defined _ALS_Ban
  #undef Ban
#else
	#define _ALS_Ban
#endif


#if defined _ALS_BanEx
  #undef BanEx
#else
	#define _ALS_BanEx
#endif

#define Kick RDZ_Kick 
#define Ban RDZ_Ban 
#define BanEx RDZ_BanEx