#if defined RDZ_JailSYS_Included_
   #endinput
#endif

#define RDZ_JailSYS_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static jailTimer[MAX_PLAYERS], 
		PlayerText:jailText[MAX_PLAYERS], 
		jailTicks[MAX_PLAYERS];

static Float:JailCellSpawns[][3] =
{
	{197.3941, 162.4637, 1003.0300}, 
	{194.3641, 175.6378, 1003.0234}, 
	{197.8117, 174.2043, 1003.0234}
};

static ReleasePlayer(playerid)
{
	SetPlayerWantedLevel(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
    SetPlayerPos(playerid, -1605.9817, 715.7421, 12.1354);
	ClearWanted(playerid);
	SetPlayerColor(playerid, GetOriginalColor(playerid));
	return 1;
}

static ForceJail(playerid)
{
	SetPlayerInterior(playerid, 3);
	new rand = random(sizeof(JailCellSpawns));
	SetPlayerPos(playerid, JailCellSpawns[rand][0], JailCellSpawns[rand][1], JailCellSpawns[rand][2]);
	PlayerTextDrawShow(playerid, jailText[playerid]);
	KillTimer(jailTimer[playerid]);
	jailTimer[playerid] = SetTimerEx("jailFunction", 1000, true, "i", playerid);
	return 1;
}

stock JailPlayer(playerid)
{
	if(IsPlayerInJail(playerid)) return 0;
	ResetPlayerWeapons(playerid);
	SetPlayerJailTime(playerid, GetNormalJailTime(GetPlayerWantedLevel(playerid)));
	SetPlayerJailed(playerid, 1);
	SetPlayerInterior(playerid, 3);
	new rand = random(sizeof(JailCellSpawns));
	SetPlayerPos(playerid, JailCellSpawns[rand][0], JailCellSpawns[rand][1], JailCellSpawns[rand][2]);
	PlayerTextDrawShow(playerid, jailText[playerid]);
	KillTimer(jailTimer[playerid]);
	jailTimer[playerid] = SetTimerEx("jailFunction", 1000, true, "i", playerid);
	return 1;
}

stock UnjailPlayer(playerid)
{
	if(!IsPlayerInJail(playerid)) return 0;
	SetPlayerJailed(playerid, 0);
	PlayerTextDrawHide(playerid, jailText[playerid]);
	ReleasePlayer(playerid);
	return 1;
}

forward jailFunction(playerid);
public jailFunction(playerid)
{
	new actual_ticks = GetPlayerJailTime(playerid);
	if(jailTicks[playerid] == 0)
	{
		if(actual_ticks == 0)
		{
			KillTimer( jailTimer[playerid] );
			UnjailPlayer(playerid);
			return 0;
		}
		else
		{
			SetPlayerJailTime(playerid, actual_ticks - 1);
			actual_ticks = GetPlayerJailTime(playerid);
			jailTicks[playerid] = 60;
		}
	}
	else jailTicks[playerid]--;
	
	SetPlayerHealth(playerid, 100.0);
	new string[STRING_SIZE_SMALL];
	
	FixZeros(actual_ticks, jailTicks[playerid], string, sizeof string);
	PlayerTextDrawSetString(playerid, jailText[playerid], string);
	
	PlayerTextDrawHide(playerid, jailText[playerid]);
	PlayerTextDrawShow(playerid, jailText[playerid]);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	jailText[playerid] = CreatePlayerTextDraw(playerid, 63.735778, 296.615112, "");
	PlayerTextDrawAlignment(playerid, jailText[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, jailText[playerid], 1521113650);
	PlayerTextDrawFont(playerid, jailText[playerid], 2);
	PlayerTextDrawLetterSize(playerid, jailText[playerid], 0.546665, 2.267848);
	PlayerTextDrawColor(playerid, jailText[playerid], 255);
	PlayerTextDrawSetOutline(playerid, jailText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, jailText[playerid], 1);
	PlayerTextDrawSetShadow(playerid, jailText[playerid], 0);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(IsPlayerInJail(playerid))
	{
		ForceJail(playerid);
	}
	return 1;
}