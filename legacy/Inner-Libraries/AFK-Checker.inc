
#if defined rAFKCHECK_included_
	#endinput
#endif

#define rAFKCHECK_included_

#define RAFK_MAX_WAIT_TICKS 30
#define RAFK_MAX_WAIT_PAUSE 15

#define RAFK_MAX_AFK_RANGE 2.0

#include <YSI_Coding\y_hooks>//Credits to Y_Less

enum rAFK_PLAYER_DATA
{
	bool:rAfkPaused,
	bool:rAfkAFK,

	rAfkClickTicks,
	rAfkPTicks,
	rAfkWarnTicks,
	rAfkPauseT,

	Float:rAfkX,
	Float:rAfkY,
	Float:rAfkZ,

	rAfkPTimer
}

new 
	rAFK_Player[MAX_PLAYERS][rAFK_PLAYER_DATA];

#if defined OnPlayerPause
	forward OnPlayerPause(playerid, time_in_seconds);
#endif

#if defined OnPlayerAFK
	forward OnPlayerAFK(playerid, time_in_seconds);
#endif

#if defined OnPlayerResume
	forward OnPlayerResume(playerid);
#endif

#if defined OnPlayerReturn
	forward OnPlayerReturn(playerid);
#endif

hook OnPlayerSpawn(playerid)
{
	GetPlayerPos(playerid, rAFK_Player[playerid][rAfkX], rAFK_Player[playerid][rAfkY], rAFK_Player[playerid][rAfkZ]);
    return 1;
}

hook OnPlayerConnect(playerid)
{
	rAFK_Player[playerid][rAfkX] = -9999.0;
	rAFK_Player[playerid][rAfkPTimer]  = SetTimerEx("rAfk_PChecker", 1000, true, "i", playerid);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	rAFK_Player[playerid][rAfkClickTicks] = gettime();
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	KillTimer(rAFK_Player[playerid][rAfkPTimer]);

	rAFK_Player[playerid][rAfkPTimer] = 0;
	rAFK_Player[playerid][rAfkPTicks] = 0;
	rAFK_Player[playerid][rAfkWarnTicks] = 0;
	rAFK_Player[playerid][rAfkClickTicks] = 0;

	rAFK_Player[playerid][rAfkPaused] = false;
	rAFK_Player[playerid][rAfkAFK] = false;

	rAFK_Player[playerid][rAfkX] = 0.0;
	rAFK_Player[playerid][rAfkY] = 0.0;
	rAFK_Player[playerid][rAfkZ] = 0.0;
    return 1;
}

hook OnPlayerUpdate(playerid)
{
	rAFK_Player[playerid][rAfkPTicks] = gettime();
    return 1;
}

forward rAfk_PChecker(playerid);
public rAfk_PChecker(playerid)
{
	if(gettime() > (rAFK_Player[playerid][rAfkPTicks]+RAFK_MAX_WAIT_PAUSE) && rAFK_Player[playerid][rAfkX] != -9999.0)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_WASTED && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && GetPlayerState(playerid) != PLAYER_STATE_NONE)
		{
			rAFK_Player[playerid][rAfkPauseT]++;
			rAFK_Player[playerid][rAfkPaused] = true;

			#if defined OnPlayerPause
				OnPlayerPause(playerid, rAFK_Player[playerid][rAfkPauseT]);
			#endif
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, RAFK_MAX_AFK_RANGE, rAFK_Player[playerid][rAfkX], rAFK_Player[playerid][rAfkY], rAFK_Player[playerid][rAfkZ]) && !rAFK_Player[playerid][rAfkPaused])
	{
		if(rAFK_Player[playerid][rAfkX] != -9999.0 && GetPlayerState(playerid) != PLAYER_STATE_WASTED && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && GetPlayerState(playerid) != PLAYER_STATE_NONE)
		{
			if(rAFK_Player[playerid][rAfkWarnTicks] < RAFK_MAX_WAIT_TICKS)
			{
				rAFK_Player[playerid][rAfkWarnTicks]++;
			}
			else
			{
				rAFK_Player[playerid][rAfkWarnTicks]++;
				rAFK_Player[playerid][rAfkAFK] = true;
				#if defined OnPlayerAFK
					OnPlayerAFK(playerid, rAFK_Player[playerid][rAfkWarnTicks]);
				#endif
			}
		}
	}
	else
	{
		GetPlayerPos(playerid, rAFK_Player[playerid][rAfkX], rAFK_Player[playerid][rAfkY], rAFK_Player[playerid][rAfkZ]);
		rAFK_Player[playerid][rAfkWarnTicks] = 0;
	}

	if( (rAFK_Player[playerid][rAfkAFK] && rAFK_Player[playerid][rAfkWarnTicks] < RAFK_MAX_WAIT_TICKS) || (gettime() - rAFK_Player[playerid][rAfkClickTicks]) <= 1)
	{
		rAFK_Player[playerid][rAfkAFK] = false;
		#if defined OnPlayerReturn
			OnPlayerReturn(playerid);
		#endif
	}

	if(rAFK_Player[playerid][rAfkPaused] && gettime() < (rAFK_Player[playerid][rAfkPTicks]+5))
	{
		rAFK_Player[playerid][rAfkPauseT] = 0;
		rAFK_Player[playerid][rAfkPaused] = false;
		#if defined OnPlayerResume
			OnPlayerResume(playerid);
		#endif
	}
	return 1;
}

stock IsPlayerPaused(playerid) 
	return rAFK_Player[playerid][rAfkPaused];
	
stock bool:IsPlayerAFK(playerid) 
	return (rAFK_Player[playerid][rAfkWarnTicks] >= RAFK_MAX_WAIT_TICKS)

stock GetPlayerAFKTime(playerid)
	return rAFK_Player[playerid][rAfkWarnTicks];

stock GetPlayerPauseTime(playerid)
	return rAFK_Player[playerid][rAfkPauseT];