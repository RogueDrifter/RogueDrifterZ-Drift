
#if defined RDZ_MONSTERKO_Included_
   #endinput
#endif

#define RDZ_MONSTERKO_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define MKO_EVENT_COLOR -1
#define MKO_VEHICLE_MODEL 557
#define MKO_MAX_PLAYER_COUNT 6
#define MKO_EVENT_ENTRY_CASH 2500
#define MKO_INTERIOR 16
#define MKO_RING_RANGE 43.000
#define MAX_MKO_CARS 6

#define PLAYER_MKO_WIN 0
#define PLAYER_MKO_DISQUALIFIED 1
#define PLAYER_MKO_COUNT 2

#define MKO_EVENT_TIME_LIMITER 0
#define MKO_EVENT_PLAYER_COUNT 1
#define MKO_EVENT_PLAYER_WIN 2
#define MKO_EVENT_NOWIN 3

enum E_PLAYER_MKO_EVENT_DATA
{
	bool:playerInEvent, 
	playerEventTimer
}

enum E_GENERAL_MKO_EVENT_DATA
{
	bool:mkoEventOn, 
	mkoPlayerCount, 
	mkoEventTimer, 
	mkoEventLimiter, 
	mkoVehicles[MAX_MKO_CARS]
}

static 
		mkoEvent[E_GENERAL_MKO_EVENT_DATA], 
		playerEvent[MAX_PLAYERS][E_PLAYER_MKO_EVENT_DATA];

CMD:joinmko(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(GetVehicleModel(vehicleid) != MKO_VEHICLE_MODEL || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendRDZMessage(playerid, MKO_EVENT_COLOR, "Monster-Knockout:[ You need to be driving the MKO vehicle! ]", MESSAGE_CASE_EMPTY);
	if(mkoEvent[mkoEventOn]) return SendRDZMessage(playerid, MKO_EVENT_COLOR, "Monster-Knockout:[ The event is already running! ]", MESSAGE_CASE_EMPTY);
	if(GetPlayerMoney(playerid) < MKO_EVENT_ENTRY_CASH) return SendRDZMessage(playerid, MKO_EVENT_COLOR, "Monster-Knockout:[ You don't have enough cash! ]", MESSAGE_CASE_EMPTY);
	if(mkoEvent[mkoPlayerCount] == MKO_MAX_PLAYER_COUNT) return SendRDZMessage(playerid, MKO_EVENT_COLOR, "Monster-Knockout:[ The event is full! ]", MESSAGE_CASE_EMPTY);
	if(IsPlayerOnDuty(playerid) || GetPlayerWantedLevel(playerid) > 0) return SendRDZMessage(playerid, MKO_EVENT_COLOR, "Monster-Knockout:[ Improper state for joining MKO! ]", MESSAGE_CASE_EMPTY);
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, -1715.5656, 4.6664, 3.6824)) return SendRDZMessage(playerid, MKO_EVENT_COLOR, "Monster-Knockout:[ You need to be near the MKO place! ]", MESSAGE_CASE_EMPTY);

	foreach(new i: Player)
	{
		if(i != playerid && GetPlayerVehicleID(i) == vehicleid) SetPlayerHealth(i, 0.000);
		if(i != playerid && GetPlayerSurfingVehicleID(i) == vehicleid) SetPlayerHealth(i, 0.000);
	}

	SetPlayerInterior(playerid, MKO_INTERIOR);
	SetVehicleHealth(vehicleid, 999.000);

	LinkVehicleToInterior(vehicleid, MKO_INTERIOR);
	GivePlayerMoney(playerid, -MKO_EVENT_ENTRY_CASH);
	playerEvent[playerid][playerInEvent] = true;

	playerEvent[playerid][playerEventTimer] = SetTimerEx("MkoPlayerChecker", 1000, true, "ii", playerid, vehicleid);
	TogglePlayerControllable(playerid, false);
	mkoEvent[mkoPlayerCount]++;
	SetCameraBehindPlayer(playerid);

	switch(mkoEvent[mkoPlayerCount])
	{
		case 1:
		{
			SetVehiclePos(vehicleid, -1367.3629, 1237.5704, 1040.2402);
			SetVehicleZAngle(vehicleid, 71.6116);
			mkoEvent[mkoEventTimer] = SetTimerEx("MkoEventStarter", 60*1000, false, "i", playerid);
			SendRDZMessage(INVALID_PLAYER_ID, MKO_EVENT_COLOR, "MONSTER KNOCKOUT(MKO) IS STARTING IN 60 SECONDS!", MESSAGE_CASE_EMPTY);
		}
		case 2:
		{
			SetVehiclePos(vehicleid, -1397.4910, 1211.3752, 1040.2384);
			SetVehicleZAngle(vehicleid, 1.0116 );
		}
		case 3:
		{
			SetVehiclePos(vehicleid, -1431.5348, 1244.7295, 1040.2384);
			SetVehicleZAngle(vehicleid, 274.9715 );
		}
		case 4:
		{
			SetVehiclePos(vehicleid, -1415.4478, 1278.3447, 1040.2402 );
			SetVehicleZAngle(vehicleid, 223.0341 );
		}
		case 5:
		{
			SetVehiclePos(vehicleid, -1376.7329, 1272.8196, 1040.2411);
			SetVehicleZAngle(vehicleid, 137.3712);
		}
		case 6:
		{
			SetVehiclePos(vehicleid, -1363.8658, 1245.0461, 1040.2648);
			SetVehicleZAngle(vehicleid, 83.2362 );
		}
	}
	return 1;
}

forward MkoPlayerChecker(playerid, vehicleid);
public MkoPlayerChecker(playerid, vehicleid)
{
	if(!IsPlayerInRangeOfPoint(playerid, MKO_RING_RANGE, -1400.5134, 1244.4498, 1039.8672) && GetPlayerInterior(playerid) == MKO_INTERIOR) return SetVehicleHealth(GetPlayerVehicleID(playerid), 0);
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SetVehicleVirtualWorld(vehicleid, NORMAL_INTERIOR);
		LinkVehicleToInterior(vehicleid, NORMAL_VIRTUAL_WORLD);
		SetVehicleToRespawn(vehicleid);
		return SetPlayerHealth(playerid, 0.000);
	}
	
	if(mkoEvent[mkoPlayerCount] == 1 && mkoEvent[mkoEventOn])
	{
		EndMkoEvent(MKO_EVENT_PLAYER_WIN, playerid);
	}
	if(mkoEvent[mkoPlayerCount] == 1 && mkoEvent[mkoEventOn] && EVENT_IsPlayerPaused(playerid))
	{
		EndMkoForPlayer(playerid, MKO_EVENT_NOWIN);
	}
	return 1;
}


forward MkoEventStarter(playerid);
public MkoEventStarter(playerid)
{
	foreach(new i: Player)
	{
		if(playerEvent[i][playerInEvent])
			TogglePlayerControllable(i, true);
	}

	if(mkoEvent[mkoPlayerCount] <= 1)
	{
		EndMkoEvent(MKO_EVENT_PLAYER_COUNT, playerid);
	}
	else
	{
		SendRDZMessage(INVALID_PLAYER_ID, MKO_EVENT_COLOR, "MKO Event has kicked off!", MESSAGE_CASE_EMPTY);
		mkoEvent[mkoEventLimiter] = SetTimer("MkoEventLimiter", 30*60*1000, false);
		mkoEvent[mkoEventOn] = true;
	}
	return 1;
}

forward MkoEventLimiter();
public MkoEventLimiter()
{
	EndMkoEvent(MKO_EVENT_TIME_LIMITER);
	return 1;
}

static EndMkoEvent(reason, playerid = INVALID_PLAYER_ID)
{
	new vehicleid;
	switch(reason)
	{
		case MKO_EVENT_TIME_LIMITER:
		{
			SendRDZMessage(INVALID_PLAYER_ID, MKO_EVENT_COLOR, "MKO Has ended due to time limit!", MESSAGE_CASE_EMPTY);
			foreach(new i: Player)
			{
				if(playerEvent[i][playerInEvent])
				{
					vehicleid = GetPlayerVehicleID(i);
					SetVehiclePos(vehicleid, -1704.0430, 16.8573, 3.5547);
					LinkVehicleToInterior(vehicleid, NORMAL_INTERIOR);
					EndMkoForPlayer(i, PLAYER_MKO_DISQUALIFIED);
				}
			}
		}
		case MKO_EVENT_PLAYER_COUNT:
		{
			EndMkoForPlayer(playerid, PLAYER_MKO_COUNT);
			vehicleid = GetPlayerVehicleID(playerid);
			SetVehiclePos(vehicleid, -1704.0430, 16.8573, 3.5547);
			LinkVehicleToInterior(vehicleid, NORMAL_INTERIOR);
			SendRDZMessage(INVALID_PLAYER_ID, MKO_EVENT_COLOR, "MKO Has ended due to not enough players!", MESSAGE_CASE_EMPTY);
		}
		case MKO_EVENT_PLAYER_WIN:
		{
			new playerName[MAX_PLAYER_NAME], string[STRING_SIZE_MEDIUM];
			GetPlayerName(playerid, playerName, sizeof playerName);
			format(string, sizeof string, "Player %s has won MKO and earned $5000!", playerName);
			SendRDZMessage(INVALID_PLAYER_ID, MKO_EVENT_COLOR, string, MESSAGE_CASE_EMPTY);

			vehicleid = GetPlayerVehicleID(playerid);
			SetVehiclePos(vehicleid, -1704.0430, 16.8573, 3.5547);
			LinkVehicleToInterior(vehicleid, NORMAL_INTERIOR);
			EndMkoForPlayer(playerid, PLAYER_MKO_WIN);
		}
		case MKO_EVENT_NOWIN:
		{
			SendRDZMessage(INVALID_PLAYER_ID, MKO_EVENT_COLOR, "MKO Has ended due to no players!", MESSAGE_CASE_EMPTY);
		}
	}
	mkoEvent[mkoEventOn] = false;
	mkoEvent[mkoPlayerCount] = 0;
	KillTimer(mkoEvent[mkoEventTimer]);
	KillTimer(mkoEvent[mkoEventLimiter]);
	for(new i; i < MAX_MKO_CARS; i++)
	{
		SetVehicleVirtualWorld(mkoEvent[mkoVehicles][i], NORMAL_INTERIOR);
		LinkVehicleToInterior(mkoEvent[mkoVehicles][i], NORMAL_VIRTUAL_WORLD);
	}
	return 1;
}

static EndMkoForPlayer(playerid, reason)
{
	switch(reason)
	{
		case PLAYER_MKO_WIN://The last man standing
		{
			GivePlayerMoney(playerid, MKO_EVENT_ENTRY_CASH*2);
		}
		case PLAYER_MKO_DISQUALIFIED://A player who got out by death/disconnecting/time limit
		{
			if(mkoEvent[mkoPlayerCount] == 1)
			{
				EndMkoEvent(MKO_EVENT_NOWIN);
			} 
			else
				mkoEvent[mkoPlayerCount]--;
		}
		case PLAYER_MKO_COUNT:
		{
			GivePlayerMoney(playerid, MKO_EVENT_ENTRY_CASH);
		}
	}
	SetPlayerInterior(playerid, NORMAL_INTERIOR);
	playerEvent[playerid][playerInEvent]= false;
	KillTimer(playerEvent[playerid][playerEventTimer]);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(playerEvent[playerid][playerInEvent])
	{
		EndMkoForPlayer(playerid, PLAYER_MKO_DISQUALIFIED);
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(playerEvent[playerid][playerInEvent])
	{
		EndMkoForPlayer(playerid, PLAYER_MKO_DISQUALIFIED);
	}
	return 1;
}

hook OnGameModeInit()
{
	CreateDynamicObject(16773, -1696.35547, 22.39860, 4.81050, 0.00000, 0.00000, 314.91010);
	CreateDynamicPickup(1239, 0, -1715.5656, 4.6664, 3.6824);
	mkoEvent[mkoVehicles][0] =  CreateVehicle(557, -1713.7124, 20.3253, 3.9691, 223.4691, -1, -1, -1, 0);
	mkoEvent[mkoVehicles][1] =  CreateVehicle(557, -1710.2346, 24.0693, 3.8971, 221.4020, -1, -1, -1, 0);
	mkoEvent[mkoVehicles][2] =  CreateVehicle(557, -1705.8077, 27.6682, 3.9156, 223.8803, -1, -1, -1, 0);
	mkoEvent[mkoVehicles][3] =  CreateVehicle(557, -1690.9558, 14.0458, 3.9477, 46.1471, -1, -1, -1, 0);
	mkoEvent[mkoVehicles][4] =  CreateVehicle(557, -1693.6348, 10.5674, 3.9418, 49.4695, -1, -1, -1, 0);
	mkoEvent[mkoVehicles][5] =  CreateVehicle(557, -1697.1256, 7.1142, 3.9373, 49.0907, -1, -1, -1, 0);
	return 1;
}
stock IsPlayerInMKO(playerid)
	return playerEvent[playerid][playerInEvent];