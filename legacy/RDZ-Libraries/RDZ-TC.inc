#if defined RDZ_TeleCAR_Included_
   #endinput
#endif

#define RDZ_TeleCAR_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

hook OnVehicleSpawn(vehicleid)
{
	foreach(new i: Player)
	{
		if(IsValidVehicle(Player_TelecarID[i]))
		{
			SetTelecarComponents(i);
		}
	}
	return 1;
}

stock CreateTelecar(playerid, carmodel, type)
{
	switch(type)
	{
		case FIRST_TIME:
		{
			Player_TelecarID[playerid] = CreateVehicle(carmodel, -1638.8586, 1202.3535, 6.8591, 337.6853, -1, -1, -1);
			UpdateTelecarComponents(playerid, FIRST_TIME, carmodel);
		}
		case SECOND_TIME:
		{
			Player_TelecarID[playerid] = CreateVehicle(carmodel, GetTcarX(playerid), GetTcarY(playerid), GetTcarZ(playerid), GetTcarR(playerid), -1, -1, -1);
			SetTelecarComponents(playerid);
		}
	}
	return 1;
}

stock GetTCarID(playerid)
{
    if(!IsTelecarOwner(playerid)) return INVALID_VEHICLE_ID;
    return Player_TelecarID[playerid];
}

stock SellTelecar(playerid, model)
{
	if(model == ELEGY_MODEL) GivePlayerMoney(playerid, 600000/2);
	DestroyVehicle(Player_TelecarID[playerid]);
	Player_TelecarID[playerid] = INVALID_VEHICLE_ID;
	ResetTelecar(playerid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Telecar sold successfully!", MESSAGE_CASE_SERVER);
	return 1;
}

hook OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if(vehicleid == Player_TelecarID[playerid])
		SetTCVehiclePaintjob(playerid, paintjobid);
	return 1;
}

hook OnVehicleMod(playerid, vehicleid, componentid)
{
	UpdateTelecarComponents(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(IsValidVehicle(Player_TelecarID[playerid]))
	{
		DestroyVehicleNeon(Player_TelecarID[playerid]);
		DestroyVehicle(Player_TelecarID[playerid]);
		Player_TelecarID[playerid] = INVALID_VEHICLE_ID;
	}	
	return 1;
}

hook OnPlayerConnect(playerid)
{
	if(IsTelecarOwner(playerid))
	{
		if(!IsValidVehicle(Player_TelecarID[playerid])) CreateTelecar(playerid, GetTcarModel(playerid), SECOND_TIME);
	}
	return 1;
}

CMD:telecar(playerid)
{
	if(GetPlayerInterior(playerid) != 0 || GetPlayerWantedLevel(playerid) > 0 || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || IsPlayerOnDuty(playerid) || IsInCity(playerid))
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Improper state for teleporting to your car!", MESSAGE_CASE_SERVER);
	if(!IsTelecarOwner(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't own a telecar!", MESSAGE_CASE_SERVER);
	new driver_name[MAX_PLAYER_NAME];
	if(IsSeatTaken(Player_TelecarID[playerid], driver_name, sizeof(driver_name) ))
	{
		new string[STRING_SIZE_LARGE];
		format(string, sizeof string, "The telecar is being driven by %s, cannot teleport at the moment!", driver_name);
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
		return 0;
	}
	SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(Player_TelecarID[playerid]));
	PutPlayerInVehicle(playerid, Player_TelecarID[playerid], VEHICLE_SEAT_DRIVER);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(KEY_PRESSED(KEY_WALK))
	{
		if(IsTelecarOwner(playerid)) 
		{
			new Float:x, Float:y, Float:z;
			GetVehiclePos(Player_TelecarID[playerid], x, y, z);
			if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
			{
				new engine, lights, alarm, bonnet, boot, objective, doors;
				GetVehicleParamsEx(Player_TelecarID[playerid], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(Player_TelecarID[playerid], engine, lights, alarm, (doors) ? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON, bonnet, boot, objective);
			}
		}
	}
	return 1;
}

CMD:lock(playerid)
{
	if(!IsTelecarOwner(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't own a telecar!", MESSAGE_CASE_SERVER);
	new Float:x, Float:y, Float:z;
	GetVehiclePos(Player_TelecarID[playerid], x, y, z);
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're not close to your telecar!", MESSAGE_CASE_SERVER);
	new engine, lights, alarm, bonnet, boot, objective, doors;
	GetVehicleParamsEx(Player_TelecarID[playerid], engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(Player_TelecarID[playerid], engine, lights, alarm, (doors) ? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON, bonnet, boot, objective);
	new string[STRING_SIZE_LARGE];
	format(string, sizeof string, "Vehicle doors were successfully %s!", (!doors) ? "Locked" : "Unlocked");
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
	return 1;
}

static IsSeatTaken(vehicleid, driver_name[], size)
{
	foreach(new i: Player)
	{
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid)
		{
			GetPlayerName(i, driver_name, size);
			return 1;
		}
	}
	return 0;
}