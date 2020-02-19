#if defined Admin_SYS_Included_
   #endinput
#endif

#define Admin_SYS_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define ADMIN_LEVEL_RCON 1337

#define DEFAULT_AMMO_VALUE 100

static bool:RDZ_RconAdmin[MAX_PLAYERS char],
			staticVeh[MAX_PLAYERS];
			//CopLights[MAX_VEHICLES];

stock RestrictForAdmin(playerid, restrict_level)
{
	if(playerid > MAX_PLAYERS || playerid < 0) return 0;
	if(!IsPlayerConnected(playerid)) return 0;
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You may not use such a command.", MESSAGE_CASE_SERVER);
    printf("ID %d tried using a CMD restricted for admins level %d", playerid, restrict_level);
    return 1;
}

static RestrictForPlayer(playerid)
{
	if(playerid > MAX_PLAYERS || playerid < 0) return 0;
	if(!IsPlayerConnected(playerid)) return 0;
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You may not use such a command on this player.", MESSAGE_CASE_SERVER);
    return 1;
}

stock IsPlayerSuperior(playerid, targetid)
{
	if(playerid > MAX_PLAYERS || playerid < 0) return 0;
	if(targetid > MAX_PLAYERS || targetid < 0) return 0;
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) return 0;
    if(GetPlayerADMIN(playerid) < GetPlayerADMIN(targetid)) return 0;
    return 1;
}

CMD:gotoxyz(playerid, params[])
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN ) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
    new Float:x, Float:y, Float:z;
    if(sscanf(params, "fff", x, y, z)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Usage: /goto [x] [y] [z]", MESSAGE_CASE_SERVER);
    
    SetPlayerPos(playerid, x, y, z);
    return 1;
}

CMD:report(playerid, params[])
{
	new user, message[STRING_SIZE_MEDIUM];
	if(sscanf(params, "rs[80]", user, message))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to state player ID/name and report reason", MESSAGE_CASE_SERVER);
	}
	if(!IsPlayerConnected(user) || user == playerid) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid player ID!", MESSAGE_CASE_SERVER);

	new string[STRING_SIZE_LARGE*2];
	format(string, sizeof string, "Report from %s, reported player %s, reason: %s", Player_TempName[playerid], Player_TempName[user], message);
	SendMessageToAdmins(string);
	SendToAdminsReports(string);
	return 1;
}

CMD:setcop(playerid, params[])
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN ) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	new user, d_case, rank;
	if(sscanf(params, "rii", user, d_case, rank))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to state player ID/name and set type (1 for making cop and 0 for removing cop) and rank", MESSAGE_CASE_SERVER);
	}
	if(!IsPlayerConnected(user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid player ID!", MESSAGE_CASE_SERVER);
	if(d_case != 0 && d_case != 1 ) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid set ID!", MESSAGE_CASE_SERVER);
	if(rank < CADET_RANK_ID || rank > CHIEF_RANK_ID) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid rank ID!", MESSAGE_CASE_SERVER);
	SendRDZMessage(user, RDZ_OFFICIAL_COLOR, "Your cop stats have been changed by an admin, check your stats to find out more!", MESSAGE_CASE_JARVIS);
	if(playerid != user) SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Action taken, move on!", MESSAGE_CASE_JARVIS);
	if(d_case != 0) SetPlayerRank(user, rank);
	else SetPlayerRank(user, 0);
	
	ChangeCopStats(user, d_case);
	OnPlayerSpawnEx(user, CASE_REGISTER);
	return 1;
}

CMD:gainaccess(playerid)
{
	if(!IsPlayerLoggedIn(playerid)) return 0;
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof name);
	
	//Replace these with ur in-game name
	if(!strcmp(name, "Andy[RDZ]", true))
		RDZ_RconAdmin{playerid} = true,
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Welcome back boss, you've regained full access over the server", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:makeadmin(playerid, params[])//Second rcon admin
{
	new 
        targetid,
		level;
	
	if(!RDZ_RconAdmin{playerid}) return RestrictForAdmin(playerid, ADMIN_LEVEL_RCON);

	if(sscanf(params, "ri", targetid, level))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name with the admin level afterwards", MESSAGE_CASE_EMPTY);
    }

	if(level > 7 || level < 0 ) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Level can't go above 7 or below 1", MESSAGE_CASE_EMPTY);

	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);

	SetPlayerADMIN(targetid, level);

	new admin_string[STRING_SIZE_LARGE];
	format(admin_string, sizeof admin_string, "Admin %s has set player %s admin, level: %d!", Player_TempName[playerid], Player_TempName[targetid], level);
	SendMessageToAdmins(admin_string);
	return 1;
}

CMD:ban(playerid, params[])//Admin level 3
{
    new 
        targetid,
        ban_reason[MAX_BAN_REASON_LENGTH];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);

    if(sscanf(params, "rs[40]", targetid, ban_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }

	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
    if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);

    new ban_string[STRING_SIZE_LARGE];

    format(ban_string, sizeof ban_string, "%s Has banned %s, reason: %s", Player_TempName[playerid], Player_TempName[targetid], ban_reason);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, ban_string, MESSAGE_CASE_JANITOR);
    SetCauseOfBan(targetid, ban_reason);
    BanByName(targetid);

    SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "If you feel that you were wrongfully banned, you may appeal your ban at Roguedrifterz.forumotion.com", MESSAGE_CASE_JARVIS);
    BanEx(targetid, ban_reason);
	DCC_SendChannelMessage(Admin_Log, ban_string);
    return 1;
}

CMD:botban(playerid, params[])//Admin level 7
{
    new 
        targetid,
        ban_reason[MAX_BAN_REASON_LENGTH];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);

    if(sscanf(params, "rs[40]", targetid, ban_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }

	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
    if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);

    new ban_string[STRING_SIZE_LARGE];

    format(ban_string, sizeof ban_string, "Has banned %s, reason: %s", Player_TempName[targetid], ban_reason);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, ban_string, MESSAGE_CASE_JANITOR);
    SetCauseOfBan(targetid, ban_reason);
    BanByName(targetid);

    SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "If you feel that you were wrongfully banned, you may appeal your ban at Roguedrifterz.forumotion.com", MESSAGE_CASE_JARVIS);
	SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "Take a screenshot of this before you leave please.", MESSAGE_CASE_JARVIS);
	BanEx(targetid, ban_reason);
	DCC_SendChannelMessage(Admin_Log, ban_string);
    return 1;
}

CMD:mytime(playerid, params[])
{
	new hour;
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_TWO);
	if(sscanf(params, "i", hour))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state the time id (between 0 and 24", MESSAGE_CASE_JARVIS);
	}

	if(hour < 0 || hour > 24) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state the time id (between 0 and 24", MESSAGE_CASE_JARVIS); 
	
	SetPlayerTime(playerid, hour, 0);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "time id was set! note that the server's original time is id 0", MESSAGE_CASE_JARVIS); 
	return 1;
}

CMD:kick(playerid, params[])//Admin level 2
{
    new 
        targetid, 
        kick_reason[STRING_SIZE_SMALL];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_TWO) return RestrictForAdmin(playerid, ADMIN_LEVEL_TWO);

    if(sscanf(params, "rs[40]", targetid, kick_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
    if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);

    new kick_string[STRING_SIZE_LARGE];

    format(kick_string, sizeof kick_string, "%s Has kicked %s, reason: %s", Player_TempName[playerid], Player_TempName[targetid], kick_reason);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, kick_string, MESSAGE_CASE_JANITOR);
    IncreaseKickCount(targetid);

    SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "If you feel that you were wrongfully kicked, you may contact our admins at Roguedrifterz.forumotion.com", MESSAGE_CASE_JARVIS);
    Kick(targetid);
	DCC_SendChannelMessage(Admin_Log, kick_string);
    return 1;
}

CMD:goto(playerid, params[])//Admin level 
{
	new 
		targetid;
		
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_TWO) return RestrictForAdmin(playerid, ADMIN_LEVEL_TWO);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	
	new 
		target_interior = GetPlayerInterior(targetid),
		target_world = GetPlayerVirtualWorld(targetid), 
		player_interior = GetPlayerInterior(playerid), 
		player_world = GetPlayerVirtualWorld(playerid);
	
	if(target_interior == player_interior && player_world == target_world)
	{
		switch( GetPlayerState(playerid) )
		{
			case PLAYER_STATE_ONFOOT, PLAYER_STATE_PASSENGER:
			{
				SetPlayerPos(playerid, x + 3, y + 3, z + 2);
			}
			
			case PLAYER_STATE_DRIVER:
			{
				SetVehiclePos( GetPlayerVehicleID(playerid), x + 3, y + 3, z + 2);
			}
		}
	}
	else
	{
		SetPlayerInterior(playerid, target_interior);
		SetPlayerVirtualWorld(playerid, target_world);
		SetPlayerPos(playerid, x + 3, y + 3, z + 2);
	}
	
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've teleported successfully to the target!", MESSAGE_CASE_ADMIN);
	return 1;
}

CMD:get(playerid, params[])//Admin level 3
{
	new 
		targetid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	
	new 
		target_interior = GetPlayerInterior(targetid),
		target_world = GetPlayerVirtualWorld(targetid), 
		player_interior = GetPlayerInterior(playerid), 
		player_world = GetPlayerVirtualWorld(playerid);
		
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	
	if(target_interior == player_interior && player_world == target_world)
	{
		switch( GetPlayerState(targetid) )
		{
			case PLAYER_STATE_ONFOOT, PLAYER_STATE_PASSENGER:
			{
				SetPlayerPos(targetid, x + 3, y + 3, z + 2);
			}
			
			case PLAYER_STATE_DRIVER:
			{
				SetVehiclePos( GetPlayerVehicleID(targetid), x + 3, y + 3, z + 2);
			}
		}
	}
	else
	{
		SetPlayerInterior(targetid, player_interior);
		SetPlayerVirtualWorld(targetid, player_world);
		SetPlayerPos(targetid, x + 3, y + 3, z + 2);
	}
	
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've teleported the target to you successfully!", MESSAGE_CASE_ADMIN);
	SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "You've been teleported by an admin!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:slap(playerid, params[])//Admin level 3
{
	new 
		targetid,
		Float:damage;
		
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "rf", targetid, damage))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name and the damage to be done", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	
	new slap_string[STRING_SIZE_MEDIUM];
	
	SetPlayerPos(targetid, x, y, z+4);
	new Float:current_HP;
	GetPlayerHealth(targetid, current_HP);
	SetPlayerHealth(targetid, current_HP-damage);
	format(slap_string, sizeof slap_string, "Admin %s has slapped player %s with the damage of %0.1f", Player_TempName[playerid], Player_TempName[targetid], damage);
	SendMessageToAdmins(slap_string);
	return 1;
}

CMD:giverep(playerid, params[])//Admin level 7
{
	new 
		targetid, amount;
		
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	
	if(sscanf(params, "ri", targetid, amount))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name then the rep amount", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);

	GivePlayerReps(targetid, amount);
	if(targetid != playerid) SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "You've been given rep by an admin, /stats for more info!", MESSAGE_CASE_SERVER);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Action has been taken, move on!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:togcol(playerid, params[])//Admin level 7
{
	new 
		targetid, toggle;
		
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	
	if(sscanf(params, "ri", targetid, toggle))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name then the toggle (1 for true 0 for false)", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);

	DisableRemoteVehicleCollisions(targetid, (toggle == 1) ? true : false );
	if(targetid != playerid) SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "Your collision stats was changed!", MESSAGE_CASE_SERVER);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Action has been taken, move on!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:getip(playerid, params[])//Admin level 7
{
	new 
		targetid;
		
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	if(RDZ_RconAdmin{targetid} && playerid != targetid) return 0;
	new IP_String[STRING_SIZE_MEDIUM];

	format(IP_String, sizeof IP_String, "Player %s's IP is %s", Player_TempName[targetid], Player_IP[targetid]);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, IP_String, MESSAGE_CASE_ADMIN);
	return 1;
}

CMD:getgpci(playerid, params[])//Admin level 3
{
	new 
		targetid;
		
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	if(RDZ_RconAdmin{targetid} && playerid != targetid) return 0;
	new GPCI_String[STRING_SIZE_MEDIUM];

	format(GPCI_String, sizeof GPCI_String, "Player %s's GPCI ID is %s", Player_TempName[targetid], Player_GPCI[targetid]);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, GPCI_String, MESSAGE_CASE_ADMIN);
	return 1;
}

CMD:freeze(playerid, params[])//Admin level 3
{
	new 
		targetid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	
	new Freeze_String[STRING_SIZE_LARGE];
	
	format(Freeze_String, sizeof Freeze_String, "Admin %s has frozen player %s", Player_TempName[playerid], Player_TempName[targetid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Freeze_String, MESSAGE_CASE_JANITOR);
	TogglePlayerControllable(targetid, false);
	return 1;
}

CMD:unfreeze(playerid, params[])//Admin level 3
{
	new 
		targetid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	new Freeze_String[STRING_SIZE_LARGE];
	
	format(Freeze_String, sizeof Freeze_String, "Admin %s has unfrozen player %s", Player_TempName[playerid], Player_TempName[targetid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Freeze_String, MESSAGE_CASE_JANITOR);
	TogglePlayerControllable(targetid, true);
	return 1;
}

CMD:gotoveh(playerid, params[])//Admin level 3
{
	new 
		vehicleid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "i", vehicleid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsValidVehicle(vehicleid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid vehicle ID!", MESSAGE_CASE_EMPTY);
	
	new vehicle_world = GetVehicleVirtualWorld(vehicleid);
	if(GetPlayerVirtualWorld(playerid) != vehicle_world) SetPlayerVirtualWorld(playerid, vehicle_world);
	
	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehicleid, x, y, z);
	SetPlayerPos(playerid, x + 3, y + 3, z + 2);
	
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've teleported successfully to the vehicle!", MESSAGE_CASE_ADMIN);
	return 1;
}	

CMD:respawncars(playerid)//Level 7
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	GameTextForAll("Empty cars will respawn in 10 seconds...", 5000, 1);
    SetTimer("xrespawnEmpty_Cars", 10*1000, false);

	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, "All vehicles are being respawned by an [ADMIN]", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:respawncar(playerid, params[])//Level 4
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FOUR) return RestrictForAdmin(playerid, ADMIN_LEVEL_FOUR);

	new vehicleid;
	if(sscanf(params, "i", vehicleid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id", MESSAGE_CASE_EMPTY);
	}

	SetVehicleToRespawn(vehicleid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Car has been respawned!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:giveweapon(playerid, params[]) //level 5
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FIVE) return RestrictForAdmin(playerid, ADMIN_LEVEL_FIVE);

	new targetid, weaponid;
	if(sscanf(params, "ri", targetid, weaponid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id and the weapon id", MESSAGE_CASE_EMPTY);
	}
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);

	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player was given the weapon!", MESSAGE_CASE_SERVER);
	if(targetid != playerid) SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, "YOu've been given a weapon by an [ADMIN]", MESSAGE_CASE_SERVER);

	GivePlayerWeapon(targetid, weaponid, DEFAULT_AMMO_VALUE);
	return 1;
}
alias:giveweapon("givewep");

static VehicleNames[212][] = {
{"Landstalker"},{"Bravura"},{"Buffalo"},{"Linerunner"},{"Perrenial"},{"Sentinel"},{"Dumper"},
{"Firetruck"},{"Trashmaster"},{"Stretch"},{"Manana"},{"Infernus"},{"Voodoo"},{"Pony"},{"Mule"},
{"Cheetah"},{"Ambulance"},{"Leviathan"},{"Moonbeam"},{"Esperanto"},{"Taxi"},{"Washington"},
{"Bobcat"},{"Mr Whoopee"},{"BF Injection"},{"Hunter"},{"Premier"},{"Enforcer"},{"Securicar"},
{"Banshee"},{"Predator"},{"Bus"},{"Rhino"},{"Barracks"},{"Hotknife"},{"Trailer 1"},{"Previon"},
{"Coach"},{"Cabbie"},{"Stallion"},{"Rumpo"},{"RC Bandit"},{"Romero"},{"Packer"},{"Monster"},
{"Admiral"},{"Squalo"},{"Seasparrow"},{"Pizzaboy"},{"Tram"},{"Trailer 2"},{"Turismo"},
{"Speeder"},{"Reefer"},{"Tropic"},{"Flatbed"},{"Yankee"},{"Caddy"},{"Solair"},{"Berkley's RC Van"},
{"Skimmer"},{"PCJ-600"},{"Faggio"},{"Freeway"},{"RC Baron"},{"RC Raider"},{"Glendale"},{"Oceanic"},
{"Sanchez"},{"Sparrow"},{"Patriot"},{"Quad"},{"Coastguard"},{"Dinghy"},{"Hermes"},{"Sabre"},
{"Rustler"},{"ZR-350"},{"Walton"},{"Regina"},{"Comet"},{"BMX"},{"Burrito"},{"Camper"},{"Marquis"},
{"Baggage"},{"Dozer"},{"Maverick"},{"News Chopper"},{"Rancher"},{"FBI Rancher"},{"Virgo"},{"Greenwood"},
{"Jetmax"},{"Hotring"},{"Sandking"},{"Blista Compact"},{"Police Maverick"},{"Boxville"},{"Benson"},
{"Mesa"},{"RC Goblin"},{"Hotring Racer A"},{"Hotring Racer B"},{"Bloodring Banger"},{"Rancher"},
{"Super GT"},{"Elegant"},{"Journey"},{"Bike"},{"Mountain Bike"},{"Beagle"},{"Cropdust"},{"Stunt"},
{"Tanker"}, {"Roadtrain"},{"Nebula"},{"Majestic"},{"Buccaneer"},{"Shamal"},{"Hydra"},{"FCR-900"},
{"NRG-500"},{"HPV1000"},{"Cement Truck"},{"Tow Truck"},{"Fortune"},{"Cadrona"},{"FBI Truck"},
{"Willard"},{"Forklift"},{"Tractor"},{"Combine"},{"Feltzer"},{"Remington"},{"Slamvan"},
{"Blade"},{"Freight"},{"Streak"},{"Vortex"},{"Vincent"},{"Bullet"},{"Clover"},{"Sadler"},
{"Firetruck LA"},{"Hustler"},{"Intruder"},{"Primo"},{"Cargobob"},{"Tampa"},{"Sunrise"},{"Merit"},
{"Utility"},{"Nevada"},{"Yosemite"},{"Windsor"},{"Monster A"},{"Monster B"},{"Uranus"},{"Jester"},
{"Sultan"},{"Stratum"},{"Elegy"},{"Raindance"},{"RC Tiger"},{"Flash"},{"Tahoma"},{"Savanna"},
{"Bandito"},{"Freight Flat"},{"Streak Carriage"},{"Kart"},{"Mower"},{"Duneride"},{"Sweeper"},
{"Broadway"},{"Tornado"},{"AT-400"},{"DFT-30"},{"Huntley"},{"Stafford"},{"BF-400"},{"Newsvan"},
{"Tug"},{"Trailer 3"},{"Emperor"},{"Wayfarer"},{"Euros"},{"Hotdog"},{"Club"},{"Freight Carriage"},
{"Trailer 3"},{"Andromada"},{"Dodo"},{"RC Cam"},{"Launch"},{"Police Car (LSPD)"},{"Police Car (SFPD)"},
{"Police Car (LVPD)"},{"Police Ranger"},{"Picador"},{"S.W.A.T. Van"},{"Alpha"},{"Phoenix"},{"Glendale"},
{"Sadler"},{"Luggage Trailer A"},{"Luggage Trailer B"},{"Stair Trailer"},{"Boxville"},{"Farm Plow"},
{"Utility Trailer"}
};

static GetVehicleModelIDFromName(vname[])
{
	for(new i = 0; i < 211; i++)
	{
	if ( strfind(VehicleNames[i], vname, true) != -1 )
	return i + 400;
	}
	return -1;
}

CMD:car(playerid, params[]) //Level 7
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	new carName[STRING_SIZE_SMALL];
    if(sscanf(params, "s[40]", carName))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Type in the car name please!", MESSAGE_CASE_ADMIN);
    }
	if(IsValidVehicle(staticVeh[playerid])) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You already have a vehicle, use /delcar to do another one!", MESSAGE_CASE_ADMIN);
	new carModel = GetVehicleModelIDFromName(carName);
	if(carModel == -1)  return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid car name!", MESSAGE_CASE_ADMIN);
	if(carModel < 400 || carModel > 611) SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid car name!", MESSAGE_CASE_ADMIN);
	if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return 	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Your virtual world/interior need to be default!", MESSAGE_CASE_ADMIN);
	new Float:x, Float:y, Float:z, Float:r;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, r);

	staticVeh[playerid] = CreateVehicle(carModel, x, y+3.000, z+2.000, r, -1, -1, -1);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Vehicle created!", MESSAGE_CASE_ADMIN);
	return 1;
}

CMD:delcar(playerid)
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	if(!IsValidVehicle(staticVeh[playerid])) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have a vehicle, use /car to create one!", MESSAGE_CASE_ADMIN);
	
	DestroyVehicle(staticVeh[playerid]);
	staticVeh[playerid] = INVALID_VEHICLE_ID;
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Vehicle deleted!", MESSAGE_CASE_ADMIN);
	return 1;
}

CMD:announce(playerid, params[]) // Level 3
{
    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE ) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);

    new message[STRING_SIZE_MEDIUM];
    if(sscanf(params, "s[80]", message))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Type in the message please!", MESSAGE_CASE_ADMIN);
    }

	GameTextForAll(message, 4000, 3);
	return 1;
}

CMD:showrules(playerid, params[]) //Level 3
{
    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE ) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
    new targetid;
    if(sscanf(params, "r", targetid))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "State the player's name/id afterwards!", MESSAGE_CASE_ADMIN);
    }
    if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player not connected!", MESSAGE_CASE_ADMIN);

    new rulesString[564];
    strcat(rulesString, "{FF3333}WARNING 18+ Server, Please Read The Following Message");
    strcat(rulesString, "\n{99FF00}contains language and themes not suitable for young players");
    strcat(rulesString, "\n{99FF00}No cheating, hacking or gameplay mods of any kind or shape");
    strcat(rulesString, "\n{99FF00}Always respect the server administrators no matter what");
    strcat(rulesString, "\n{99FF00}No abusing, flaming, trolling or any racist remarks");
    strcat(rulesString, "\n\n{CCCCCC}This drift server was originally made by RogueDrifter (Andy)");
    strcat(rulesString, "\n\n{CCCCCC}>>> {FFFFFF}Click 'Accept' to continue or 'Refuse' to quit.");
    Dialog_Show(targetid, DIALOG_RULES_CMD, DIALOG_STYLE_MSGBOX, "[RDZ] RULES", rulesString, "Accept", "Refuse");

    new string[STRING_SIZE_LARGE];
    format(string, sizeof string, "Player %s was shown rules by admin %s", Player_TempName[targetid], Player_TempName[playerid]);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
    return 1;
}

CMD:kickall(playerid, params[])//level 7
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	new string[STRING_SIZE_LARGE], kick_reason[STRING_SIZE_SMALL];
	if(sscanf(params, "s[40]", kick_reason))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the kick reason", MESSAGE_CASE_EMPTY);
	}

	format(string, sizeof string, "All players were kicked by admin %s, reason: %s",Player_TempName[playerid], kick_reason);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
	foreach(new i: Player)
	{
		if(i != playerid) Kick(i);
	}

	return 1;
}

CMD:giveallcash(playerid, params[]) //level 7
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	new money;
	if(sscanf(params, "i", money))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the money to give", MESSAGE_CASE_EMPTY);
	}

	foreach(new i: Player)
	{
		if(i != playerid) GivePlayerMoney(i, money);
	}

	new string[STRING_SIZE_LARGE];
	format(string, sizeof string, "All players were given $%d by Admin %s", money, Player_TempName[playerid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);

	return 1;
}

CMD:giveallrep(playerid, params[]) //level 7
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	new money;
	if(sscanf(params, "i", money))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the reps to give", MESSAGE_CASE_EMPTY);
	}

	foreach(new i: Player)
	{
		if(i != playerid) GivePlayerReps(i, money);
	}
	new string[STRING_SIZE_LARGE];
	format(string, sizeof string, "All players were given %d reputation points by Admin %s", money, Player_TempName[playerid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:healall(playerid) //level 5
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FIVE) return RestrictForAdmin(playerid, ADMIN_LEVEL_FIVE);

	foreach(new i: Player)
	{
		if(GetPlayerWantedLevel(i) > 0) continue;
		SetPlayerHealth(i, 100.000);
	}

	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, "All players were healed by an [ADMIN]", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:jetpack(playerid)// level 3
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);

	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
	{

        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);  
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Jetpack [DEACTIVATED]", MESSAGE_CASE_JARVIS);
	}
	else
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Jetpack [ACTIVATED]", MESSAGE_CASE_JARVIS);
	}
	return 1;
}

CMD:armourall(playerid) // level 5
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FIVE) return RestrictForAdmin(playerid, ADMIN_LEVEL_FIVE);

	foreach(new i: Player)
	{
		if(GetPlayerWantedLevel(i) > 0) continue;
		SetPlayerArmour(i, 100.000);
	}

	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, "All players got an armour by an [ADMIN]", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:pban(playerid, params[])//Admin level 7
{
	new 
        targetname[MAX_PLAYER_NAME],
        ban_reason[MAX_BAN_REASON_LENGTH];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

    if(sscanf(params, "s[24]s[40]", targetname, ban_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }
	
	if(!IsPlayerRegistered(targetname)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't registered!", MESSAGE_CASE_EMPTY);

	new gpcihash[STRING_SIZE_MEDIUM];
	GetGPCIFromDB(targetname, gpcihash, sizeof gpcihash);
	if(AddGpciBan(gpcihash))
	{
		new ban_string[STRING_SIZE_LARGE];

		format(ban_string, sizeof ban_string, "%s Has banned %s permanently, reason: %s", Player_TempName[playerid], targetname, ban_reason);
		SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, ban_string, MESSAGE_CASE_JANITOR);
	}
	else
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to ban this player permanently!", MESSAGE_CASE_ADMIN);
	}
	return 1;
}

CMD:unpban(playerid, params[])//Admin level 7
{
	new 
        targetname[MAX_PLAYER_NAME],
        ban_reason[MAX_BAN_REASON_LENGTH];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

    if(sscanf(params, "s[24]s[40]", targetname, ban_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }
	
	if(!IsPlayerRegistered(targetname)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't registered!", MESSAGE_CASE_EMPTY);

	new gpcihash[STRING_SIZE_MEDIUM];
	GetGPCIFromDB(targetname, gpcihash, sizeof gpcihash);
	if(DelGpciBan(gpcihash))
	{
		new ban_string[STRING_SIZE_LARGE];

		format(ban_string, sizeof ban_string, "%s Has removed %s's permanent ban, reason: %s", Player_TempName[playerid], targetname, ban_reason);
		SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, ban_string, MESSAGE_CASE_JANITOR);
	}
	else
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to ban this player permanently!", MESSAGE_CASE_ADMIN);
	}
	return 1;
}

CMD:nameban(playerid, params[])//Level 7
{
	new 
		name[MAX_PLAYER_NAME];
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	if(sscanf(params, "s[24]", name))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name", MESSAGE_CASE_EMPTY);
	}
	
	if(AddNameBan(name))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was added to the ban list!", MESSAGE_CASE_SERVER);
	}
	else SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was not added due to an error!", MESSAGE_CASE_SERVER);
	return 1;
}


CMD:rnameban(playerid, params[])//Level 7
{
	new 
		name[MAX_PLAYER_NAME];
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	if(sscanf(params, "s[24]", name))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name", MESSAGE_CASE_EMPTY);
	}
	
	if(DelNameBan(name))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was removed from the ban list!", MESSAGE_CASE_SERVER);
	}
	else SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was not removed due to an error!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:addmember(playerid, params[])//Level 7
{
	new 
		name[MAX_PLAYER_NAME];
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	if(sscanf(params, "s[24]", name))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name", MESSAGE_CASE_EMPTY);
	}
	
	if(AddRDZMember(name))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was added to the clan list!", MESSAGE_CASE_SERVER);
	}
	else SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was not added due to an error!", MESSAGE_CASE_SERVER);
	return 1;
}


CMD:delmember(playerid, params[])//Level 7
{
	new 
		name[MAX_PLAYER_NAME];
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	if(sscanf(params, "s[24]", name))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name", MESSAGE_CASE_EMPTY);
	}
	
	if(DelRDZMember(name))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was removed from the clan list!", MESSAGE_CASE_SERVER);
	}
	else SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Target was not removed due to an error!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:getveh(playerid, params[])//Admin level 3
{
	new 
		vehicleid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "i", vehicleid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsValidVehicle(vehicleid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid vehicle ID!", MESSAGE_CASE_EMPTY);
	
	new player_world = GetPlayerVirtualWorld(playerid);
	if(player_world != GetVehicleVirtualWorld(vehicleid)) SetVehicleVirtualWorld(vehicleid, player_world);
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(vehicleid, x + 3, y + 3, z + 2);
	
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've teleported the vehicle successfully!", MESSAGE_CASE_ADMIN);
	return 1;
}

CMD:oban(playerid, params[])//Admin level 7
{
	new 
        targetname[MAX_PLAYER_NAME],
        ban_reason[MAX_BAN_REASON_LENGTH];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

    if(sscanf(params, "s[24]s[40]", targetname, ban_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }
	
	if(!IsPlayerRegistered(targetname)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't registered!", MESSAGE_CASE_EMPTY);

	if(BanOfflineName(playerid, targetname, ban_reason))
	{
		new ban_string[STRING_SIZE_LARGE];

		format(ban_string, sizeof ban_string, "%s Has banned %s, reason: %s", Player_TempName[playerid], targetname, ban_reason);
		SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, ban_string, MESSAGE_CASE_JANITOR);
	}
	else
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to ban this offline player!", MESSAGE_CASE_ADMIN);
	}
	return 1;
}

CMD:unban(playerid, params[])//Admin level 7
{
	new 
        targetname[MAX_PLAYER_NAME],
        ban_reason[MAX_BAN_REASON_LENGTH];

    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

    if(sscanf(params, "s[24]s[40]", targetname, ban_reason))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target name along with the reason afterwards", MESSAGE_CASE_EMPTY);
    }
	
	if(!IsPlayerRegistered(targetname)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't registered!", MESSAGE_CASE_EMPTY);

	if(UnbanOfflineName(playerid, targetname, ban_reason))
	{
		new ban_string[STRING_SIZE_LARGE];

		format(ban_string, sizeof ban_string, "%s Has unbanned %s, reason: %s", Player_TempName[playerid], targetname, ban_reason);
		SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, ban_string, MESSAGE_CASE_JANITOR);
	}
	else
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to unban this offline player!", MESSAGE_CASE_ADMIN);
	}
	return 1;
}

CMD:mute(playerid, params[])//Admin level 2
{
	new 
		targetid, 
		reason[STRING_SIZE_SMALL];
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_TWO) return RestrictForAdmin(playerid, ADMIN_LEVEL_TWO);
	
	if(sscanf(params, "rs[40]", targetid, reason))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name with the reason", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player ID Invalid!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	
	new Mute_string[STRING_SIZE_LARGE];
	
	format(Mute_string, sizeof Mute_string, "Admin %s has muted player %s, reason: %s", Player_TempName[playerid], Player_TempName[targetid], reason);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Mute_string, MESSAGE_CASE_JANITOR);
	SetMuteCause(targetid, reason);
	MutePlayer(targetid, TARGET_BOOL_TRUE);
	return 1;
}

CMD:unmute(playerid, params[])//Admin level 3
{
	new 
		targetid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	
	new Mute_string[STRING_SIZE_LARGE];
	
	format(Mute_string, sizeof Mute_string, "Admin %s has unmuted player %s", Player_TempName[playerid], Player_TempName[targetid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Mute_string, MESSAGE_CASE_JANITOR);
	MutePlayer(targetid, TARGET_BOOL_FALSE);
	return 1;
}

CMD:getmute(playerid, params[])//Admin level 2
{
	new 
		targetid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_TWO) return RestrictForAdmin(playerid, ADMIN_LEVEL_TWO);
	
	if(sscanf(params, "r", targetid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	
	new Mute_string[STRING_SIZE_LARGE];
	GetMuteCause(targetid);

	format(Mute_string, sizeof Mute_string, "Player %s was muted for %s", Player_TempName[targetid], Mute_StringReason[targetid]);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, Mute_string, MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:setwanted(playerid, params[])//Admin level 7
{
	new 
		targetid,
		wanted_level;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	
	if(sscanf(params, "rd", targetid, wanted_level))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name along with the wanted level", MESSAGE_CASE_EMPTY);
	}
	if (wanted_level > 6 || wanted_level < 0) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Wanted level is invalid make sure its between 0 and 6", MESSAGE_CASE_EMPTY);
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
	
	new Wanted_string[STRING_SIZE_LARGE];
	
	format(Wanted_string, sizeof Wanted_string, "Admin %s has set player %s wanted level to %d", Player_TempName[playerid], Player_TempName[targetid], wanted_level);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Wanted_string, MESSAGE_CASE_JANITOR);
	SetPlayerWantedLevel(targetid, wanted_level);
	SetUserWanted(targetid, wanted_level);
	if(GetPlayerWantedLevel(targetid) > 0 ) SetPlayerColor(targetid, RDZ_COLOR_WANTED);
	else SetPlayerColor(targetid, GetOriginalColor(targetid));
	return 1;
}

CMD:setweather(playerid, params[])//Admin level 6
{
	new 
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SIX) return RestrictForAdmin(playerid, ADMIN_LEVEL_SIX);
	
	if(sscanf(params, "d", featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	if (featureid > 30 || featureid < 0) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "The feature ID is invalid make sure its between 0 and 30", MESSAGE_CASE_EMPTY);
		
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set weather id to %d", Player_TempName[playerid], featureid);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SetWeather(featureid);
	return 1;
}

CMD:settime(playerid, params[])//Admin level 6
{
	new 
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SIX) return RestrictForAdmin(playerid, ADMIN_LEVEL_SIX);
	
	if(sscanf(params, "d", featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	if (featureid > 24 || featureid < 0) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "The feature ID is invalid make sure its between 0 and 30", MESSAGE_CASE_EMPTY);
		
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set the time to %d", Player_TempName[playerid], featureid);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SetWorldTime(featureid);
	return 1;
}

CMD:setskin(playerid, params[])//Admin level 5
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FIVE) return RestrictForAdmin(playerid, ADMIN_LEVEL_FIVE);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
		
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set the skin id of %s to %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SetPlayerSkin(targetid, featureid);
	UpdatePlayerSkin(targetid);
	return 1;
}

CMD:setworld(playerid, params[])//Admin level 5
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FIVE) return RestrictForAdmin(playerid, ADMIN_LEVEL_FIVE);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
			
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set the world id of %s to %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SetPlayerVirtualWorld(targetid, featureid);
	return 1;
}

CMD:setinterior(playerid, params[])//Admin level 5
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FIVE) return RestrictForAdmin(playerid, ADMIN_LEVEL_FIVE);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
			
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set the interior id of %s to %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SetPlayerInterior(targetid, featureid);
	return 1;
}
alias:setinterior("setint");

CMD:setcash(playerid, params[])//Admin level 6
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SIX) return RestrictForAdmin(playerid, ADMIN_LEVEL_SIX);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
			
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set the cash of %s to %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);	
	ResetPlayerMoney(targetid);
	GivePlayerMoney(targetid, featureid);
	return 1;
}

CMD:setscore(playerid, params[])//Admin level 6
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SIX) return RestrictForAdmin(playerid, ADMIN_LEVEL_SIX);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
			
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has set the score of %s to %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SetPlayerScore(targetid, featureid);
	UpdatePlayerDriftScore(playerid, featureid);
	return 1;
}

CMD:givecash(playerid, params[])//Admin level 6
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SIX) return RestrictForAdmin(playerid, ADMIN_LEVEL_SIX);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
			
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has given cash to %s amount %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);	
	GivePlayerMoney(targetid, featureid);
	return 1;
}

CMD:givescore(playerid, params[])//Admin level 6
{
	new 
		targetid,
		featureid;
	
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SIX) return RestrictForAdmin(playerid, ADMIN_LEVEL_SIX);
	
	if(sscanf(params, "rd", targetid, featureid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the player id or name along with the feature id you want to set please", MESSAGE_CASE_EMPTY);
	}
	
	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_EMPTY);
	if(!IsPlayerSuperior(playerid, targetid)) return RestrictForPlayer(playerid);
			
	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has given score to %s amount %d", Player_TempName[playerid], Player_TempName[targetid], featureid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	SendRDZMessage(targetid, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);	
	SetPlayerScore(targetid, GetPlayerScore(targetid) + featureid);
	return 1;
}

CMD:cleardeaths(playerid) //Level 4
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FOUR) return RestrictForAdmin(playerid, ADMIN_LEVEL_FOUR);

	for(new i; i < 6; i++)
	{
		SendDeathMessage(202, 202, 202);
	}

	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has cleared the death window!", Player_TempName[playerid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:clearchat(playerid)// Level 4
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_FOUR) return RestrictForAdmin(playerid, ADMIN_LEVEL_FOUR);

	for(new i; i < 20; i++)
	{
		SendClientMessageToAll(-1, " ");
	}

	new Feature_string[STRING_SIZE_LARGE];
	
	format(Feature_string, sizeof Feature_string, "Admin %s has cleared the chat window!", Player_TempName[playerid]);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Feature_string, MESSAGE_CASE_JARVIS);
	return 1;
}

/*CMD:coplightson(playerid)
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	
	new vehicleid = GetPlayerVehicleID(playerid);
	if(GetVehicleModel(vehicleid) != ELEGY_MODEL) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Get in an elegy first!", MESSAGE_CASE_EMPTY); 

	if(IsValidObject(CopLights[vehicleid])) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Object already created here", MESSAGE_CASE_EMPTY);
	CopLights[vehicleid] = CreateObject(18646,0,0,0,0,0,0);
	AttachObjectToVehicle(CopLights[vehicleid], vehicleid, -0.5, -0.2, 0.8, 2.0, 2.0, 3.0);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Object has been created!", MESSAGE_CASE_EMPTY);
	return 1;
}

CMD:coplightsoff(playerid)
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	new vehicleid = GetPlayerVehicleID(playerid);
	if(GetVehicleModel(vehicleid) != ELEGY_MODEL) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Get in an elegy first!", MESSAGE_CASE_EMPTY); 
	if(!IsValidObject(CopLights[vehicleid])) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Object already destroyed here", MESSAGE_CASE_EMPTY);
	DestroyObject(CopLights[vehicleid]);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Object has been destroyed!", MESSAGE_CASE_EMPTY);
	return 1;
}*/

hook OnPlayerStateChange(playerid, newstate, oldstate)	
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		foreach(new i: Player)
		{
			if(!IsValidVehicle(staticVeh[i])) continue;
			if(GetPlayerVehicleID(playerid) == staticVeh[i] && GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN)
				RemovePlayerFromVehicle(playerid);
		}
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(IsValidVehicle(staticVeh[playerid])) 	DestroyVehicle(staticVeh[playerid]),
	staticVeh[playerid] = INVALID_VEHICLE_ID;
	RDZ_RconAdmin{playerid} = false;
	return 1;
}

stock IsPlayerRconAdmin(playerid)
	return RDZ_RconAdmin{playerid};

stock SendMessageToAdmins(message[])
{
	foreach(new i: Player)
	{
		if(!IsPlayerADMIN(i)) continue;

		SendRDZMessage(i, RDZ_OFFICIAL_COLOR, message, MESSAGE_CASE_ADMIN);
	}
	return 1;
}

stock SendMessageToAdminsChat(playerid, message[])
{
	message[0] = ' ';
	foreach(new i: Player)
	{
		if(!IsPlayerADMIN(i)) continue;

		SendRDZMessage(i, RDZ_OOC_CHAT_COLOR, message, MESSAGE_CASE_ADMINSCHAT, playerid);
	}
	return 1;
}

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(GetPlayerADMIN(playerid) > 5)
	{
		switch(GetPlayerState(playerid))
		{
			case PLAYER_STATE_ONFOOT:
			{
				SetPlayerPos(playerid, fX, fY, fZ);
			}
			case PLAYER_STATE_DRIVER:
			{
				SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
			}
		}
	}
	return 1;
}

forward xrespawnEmpty_Cars();
public xrespawnEmpty_Cars()
{
    foreach(new x: Vehicle)
    {
		if(x < 500)
		{

			if(IsVehicleEmpty(x))
				SetVehicleToRespawn(x);
		}
		else 
		{
			SetTimerEx("xrespawnEmpty_CarsDelay", 1000, false, "i", x);
			break;
		}
    }
    return 1;
}

forward xrespawnEmpty_CarsDelay(carid);
public xrespawnEmpty_CarsDelay(carid)
{
	for(new x=carid; x<MAX_VEHICLES; x++)
	{
		if(!IsValidVehicle(x)) continue;
		if(IsVehicleEmpty(x))
			SetVehicleToRespawn(x);
	}
	return 1;
}

Dialog:DIALOG_RULES_CMD(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        new string[STRING_SIZE_LARGE];
        format(string, sizeof string, "Player %s was kicked, reason: Refusing to follow rules", Player_TempName[playerid]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
        Kick(playerid);
    }
    else
    {
        new string[STRING_SIZE_LARGE];
        format(string, sizeof string, "Player %s was has accepted to follow the rules!", Player_TempName[playerid]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
    }
    return 1;
} 