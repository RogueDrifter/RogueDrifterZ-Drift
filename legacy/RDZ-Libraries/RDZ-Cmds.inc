#if defined RDZ_CMDS_Included_
   #endinput
#endif

#define RDZ_CMDS_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define STATS_TYPE_DIALOG 1
#define STATS_TYPE_MESSAGES 0
#define BUBBLE_CHAT_DISTANCE 30.000
#define BUBBLE_CHAT_TIME 3*1000

static bool:gpsCP[MAX_PLAYERS char], 
	   bool:adminCloak[MAX_PLAYERS char],
	   bool:adminSpy[MAX_PLAYERS char];

hook OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(source == CLICK_SOURCE_SCOREBOARD)
	{
		if( (!IsPlayerSuperior(playerid, clickedplayerid) && IsPlayerADMIN(clickedplayerid)) && clickedplayerid != playerid) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to show player stats!", MESSAGE_CASE_SERVER);
		ShowStats(clickedplayerid, STATS_TYPE_MESSAGES, playerid);
	}
	return 1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	if(gpsCP{playerid})
	{
		DisablePlayerCheckpoint(playerid);
		gpsCP{playerid} = false;
	}
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)	
{
	if(gpsCP{playerid})
	{
		DisablePlayerCheckpoint(playerid);
		gpsCP{playerid} = false;
	}
	adminSpy{playerid} = false;
	adminCloak{playerid} = false;
	return 1;
}

forward resetKill(playerid);
public resetKill(playerid)
	return cmdKill{playerid} = false;

CMD:kill(playerid)
{
    if(!KillExceptions(playerid))
    {
		cmdKill{playerid} = true;
		SetTimerEx("resetKill", 2500, false, "i", playerid);
        SetPlayerHealth(playerid, 0.0);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Successfully killed, welcome to the afterlife", MESSAGE_CASE_DEATH);
    }
    return 1;
}
alias:kill("death", "killme", "suicide");

CMD:whisper(playerid, params[])
{
	new user, message[STRING_SIZE_LARGE];
	if(sscanf(params, "rs[128]", user, message))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to mention both the player's name/id and the message", MESSAGE_CASE_SERVER);
	}
	
	if(user == playerid || !IsPlayerConnected(user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid player id!", MESSAGE_CASE_SERVER);

	new string[STRING_SIZE_LARGE + MAX_PLAYER_NAME + STRING_SIZE_LARGE];
	format(string, sizeof string, ".: {A60CF2} %s(%d) Whispers: {CCCCCC}%s :.", Player_TempName[playerid], playerid, message);
	SendRDZMessage(user, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);

	format(string, sizeof string, ".: {A60CF2} Whispered %s(%d): {CCCCCC}%s :.", Player_TempName[user], user, message);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
	

	format(string, sizeof string, ".: {A60CF2} %s(%d) Whispered %s(%d): {CCCCCC}%s :.", Player_TempName[playerid], playerid, Player_TempName[user], user, message);
	foreach(new i: Player)
	{
		if(GetPlayerADMIN(i) == ADMIN_LEVEL_SEVEN)
		{
			if(adminSpy{i})
			{
				if(user != i && playerid != i)
					SendRDZMessage(i, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
			}
		}
	}
	return 1;
}
alias:whisper("pm", "w", "message");

CMD:bubble(playerid, params[])
{
	new message[STRING_SIZE_LARGE];
	if(sscanf(params, "s[128]", message))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to state the message", MESSAGE_CASE_SERVER);
	}

	new string[STRING_SIZE_LARGE + 50];
	format(string, sizeof string, "%s Says: (( %s ))", Player_TempName[playerid], message);
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	foreach(new i: Player)
	{
		if(IsPlayerInRangeOfPoint(i, 25.0, x, y, z))
		{
			SendRDZMessage(i, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_EMPTY);
		}
	}
	SetPlayerChatBubble(playerid, string, RDZ_OOC_CHAT_COLOR, BUBBLE_CHAT_DISTANCE, BUBBLE_CHAT_TIME);
	return 1;
}
alias:bubble("b");

CMD:carcolor(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Must be a driver to use this!", MESSAGE_CASE_SERVER);

	new col1, col2;
	if(sscanf(params, "ii", col1, col2))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Must state color 1 and 2 to use this! Ex. /carcolor 5 10", MESSAGE_CASE_SERVER);
	}
	if(col1 < 0 || col1 > 255 || col2 < 0 || col2 > 255) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Invalid color IDs!", MESSAGE_CASE_SERVER);

	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsCopVehicle(GetVehicleModel(vehicleid))) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Cannot color this vehicle!", MESSAGE_CASE_SERVER);

	ChangeVehicleColor(vehicleid, col1, col2);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Colors changed!", MESSAGE_CASE_SERVER);
	if(vehicleid == Player_TelecarID[playerid]) UpdateTelecarColors(playerid, col1, col2);
	return 1;
}
alias:carcolor("carcolour", "spray", "cc");

CMD:spy(playerid)
{
	if(GetPlayerADMIN(playerid) < 7) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

	adminSpy{playerid} = !adminSpy{playerid};

	new string[STRING_SIZE_LARGE];
	format(string, sizeof string, "Admin spy has been turned %s", (adminSpy{playerid}) ? "On" : "Off");
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:buylevel(playerid)
{
	new levelSTRING[STRING_SIZE_LARGE];
	new required_EXP = (GetPlayerLevel(playerid) +1) * 3 + 5;
	
	format(levelSTRING, sizeof levelSTRING, "Current level: %d \n Next level: %d \n Current EXP: %d \n Required EXP: %d \n Required cash: %d", GetPlayerLevel(playerid), GetPlayerLevel(playerid)+1, GetPlayerEXP(playerid), required_EXP, required_EXP*50000);
	Dialog_Show(playerid, DIALOG_BUY_LEVEL, DIALOG_STYLE_MSGBOX, "Upgrading levels", levelSTRING, "Buy", "Cancel");
	return 1;
}

CMD:stats(playerid, params[])
{
	new user, type;
	if(sscanf(params, "ri", user, type))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to mention the player's name/id and the method of showing stats (1 dialog 0 messages)", MESSAGE_CASE_SERVER);
	}
	
	if(!IsPlayerConnected(user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to show player stats!", MESSAGE_CASE_SERVER);

	if( (!IsPlayerSuperior(playerid, user) && IsPlayerADMIN(user)) && user != playerid) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to show player stats!", MESSAGE_CASE_SERVER);

	if(type != 1 && type != 0) 	return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "The stats type must be either 0 or 1!", MESSAGE_CASE_SERVER); 
	
	switch(type)
	{
		case STATS_TYPE_DIALOG: ShowStats(user, STATS_TYPE_DIALOG, playerid);
		case STATS_TYPE_MESSAGES: ShowStats(user, STATS_TYPE_MESSAGES, playerid);
	}
	return 1;
}

static KillExceptions(playerid)
{
    return (GetPlayerWantedLevel(playerid) > 0);
}

Dialog:DIALOG_BUY_LEVEL(playerid, response, listitem, inputtext[])
{
	new required_EXP = (GetPlayerLevel(playerid) +1) * 3 + 5;
	new required_cash = required_EXP*50000;

	switch(response)
	{
		case true:
		{
			if(GetPlayerMoney(playerid) < required_cash) return	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to process due to insufficient funds!", MESSAGE_CASE_JARVIS);
			if(GetPlayerEXP(playerid) < required_EXP) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to process due to insufficient EXP!", MESSAGE_CASE_JARVIS);
			
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Request processed!", MESSAGE_CASE_JARVIS);
			IncreasePlayerLevel(playerid, 1);
			GivePlayerEXP(playerid, -required_EXP);
			GivePlayerMoney(playerid, -required_cash);
		}
		
		case false:
		{
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Request cancelled!", MESSAGE_CASE_JARVIS);
		}
	}
	return 1;
}

static ShowStats(playerid, stats_type, targetid)
{
	if(!IsPlayerLoggedIn(playerid)) return 0;
	new statsString[STRING_SIZE_QUERY*6];
	new sex[15];
	sex = (GetPlayerSex(playerid) == PLAYER_GENDER_MALE) ? "Male" : "Female";
	
	new team[10];
	if(IsPlayerADMIN(playerid)) team = "Staff";
	else if(IsPlayerVIP(playerid)) team = "Donator";
	else team = "Civillian";

	new mute_stats[10];
	mute_stats = (IsPlayerMuted(playerid)) ? "Yes" : "No";

	new job[15], job_id;
	job_id = GetPlayerJob(playerid);

	job = (job_id == JOB_ID_COP) ? "Cop" : (job_id == JOB_ID_DRUGDEALER) ? "Drug dealer" : "None";
	new cop_rank[10];
	new next_rank;
	if(IsPlayerCop(playerid))
	{
		GetRankNameFromID(GetPlayerRank(playerid), cop_rank, sizeof cop_rank);
		new current = GetPlayerArrests(playerid);
		switch(GetPlayerRank(playerid))
		{
			case CADET_RANK_ID:
			{
				next_rank = OFFICER_ARRESTS - current;
			}
			case OFFICER_RANK_ID:
			{
				next_rank = SERGEANT_ARRESTS - current;
			}
			case SERGEANT_RANK_ID:
			{
				next_rank = LIEUTENANT_ARRESTS - current;
			}
			case LIEUTENANT_RANK_ID:
			{
				next_rank = CAPTAIN_ARRESTS - current;
			}
			case CAPTAIN_RANK_ID:
			{
				next_rank = 0;
			}
		}
	}
	switch(stats_type)
	{
		case STATS_TYPE_DIALOG:
		{
			format(statsString, sizeof statsString, "{00FF00}||| %s |||", Player_TempName[playerid]);

			format(statsString, sizeof statsString, "%s\n____________________________", statsString);
			format(statsString, sizeof statsString, "%s\n|Level:[%d] Sex:[%s] Cash:[$%d] Bank[$%d] VIP:[%d] Playing hours:[%d]|", statsString, GetPlayerLevel(playerid), sex, GetPlayerMoney(playerid), GetPlayerBankB(playerid), GetPlayerVIP(playerid), GetPlayingHours(playerid));
			format(statsString, sizeof statsString, "%s\n|Kills:[%d] Deaths:[%d] WantedLevel:[%d] Team:[%s] BestOD:[%d] Reputation:[%d]|", statsString, GetPlayerKills(playerid), GetPlayerDeaths(playerid), GetPlayerWantedLevel(playerid), team, GetPlayerBestRival(playerid), GetPlayerReps(playerid));
			format(statsString, sizeof statsString, "%s\n|Outdrift wins:[%d] Outdrift losses:[%d] Server ranking:[%d] Mute stats:[%s]|", statsString, GetPlayerODWon(playerid), GetPlayerODLost(playerid), GetPlayerID(playerid), mute_stats);
			if(!IsPlayerCop(playerid)) format(statsString, sizeof statsString, "%s\n|EXP:[%d] Arrested:[%d] Crimes:[%d] FuelCan:[%d]|", statsString, GetPlayerEXP(playerid), GetPlayerArrested(playerid), GetPlayerCrimes(playerid), GetPlayerFuelCan(playerid));
			else format(statsString, sizeof statsString, "%s\n|EXP:[%d] Arrested:[%d] Crimes:[%d] FuelCan:[%d] Arrests:[%d] Rank:[%s] Next rank:[%d]|", statsString, GetPlayerEXP(playerid), GetPlayerArrested(playerid), GetPlayerCrimes(playerid), GetPlayerFuelCan(playerid), GetPlayerArrests(playerid), cop_rank, next_rank);
			format(statsString, sizeof statsString, "%s\n____________________________", statsString);

			Dialog_Show(targetid, DIALOG_STATS, DIALOG_STYLE_MSGBOX, "RogueDrifterZ stats", statsString, "Ok", "");
		}
		case STATS_TYPE_MESSAGES:
		{
   			format(statsString, sizeof statsString, "{00FF00}||| %s |||{CCCCCC}", Player_TempName[playerid]);
			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);

			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, "____________________________", MESSAGE_CASE_EMPTY);
			format(statsString, sizeof statsString, "|Level:[%d] Sex:[%s] Cash:[$%d] Bank[$%d] VIP:[%d] Playing hours:[%d]|", GetPlayerLevel(playerid), sex, GetPlayerMoney(playerid), GetPlayerBankB(playerid), GetPlayerVIP(playerid), GetPlayingHours(playerid));
			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
			format(statsString, sizeof statsString, "|Kills:[%d] Deaths:[%d] WantedLevel:[%d] Team:[%s] BestOD:[%d] Reputation:[%d]|", GetPlayerKills(playerid), GetPlayerDeaths(playerid), GetPlayerWantedLevel(playerid), team, GetPlayerBestRival(playerid), GetPlayerReps(playerid));
			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
			format(statsString, sizeof statsString, "|Outdrift wins:[%d] Outdrift losses:[%d] Server ranking:[%d] Mute stats:[%s]|", GetPlayerODWon(playerid), GetPlayerODLost(playerid), GetPlayerID(playerid), mute_stats);
			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
			if(!IsPlayerCop(playerid)) format(statsString, sizeof statsString, "|EXP:[%d] Arrested:[%d] Crimes:[%d] FuelCan:[%d]|", GetPlayerEXP(playerid), GetPlayerArrested(playerid), GetPlayerCrimes(playerid), GetPlayerFuelCan(playerid));
			else format(statsString, sizeof statsString, "|EXP:[%d] Arrested:[%d] Crimes:[%d] FuelCan:[%d] Arrests:[%d] Rank:[%s] Next rank:[%d]|", GetPlayerEXP(playerid), GetPlayerArrested(playerid), GetPlayerCrimes(playerid), GetPlayerFuelCan(playerid), GetPlayerArrests(playerid), cop_rank, next_rank);
			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
			SendRDZMessage(targetid, RDZ_OOC_CHAT_COLOR, "____________________________", MESSAGE_CASE_EMPTY);
		}
	}
	return 1;
}

CMD:myweather(playerid, params[])
{
	new weatherid;
	if(sscanf(params, "i", weatherid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state the weather id (between 0 and 40", MESSAGE_CASE_JARVIS);
	}

	if(weatherid < 0 || weatherid > 40) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state the weather id (between 0 and 40", MESSAGE_CASE_JARVIS); 
	
	SetPlayerWeather(playerid, weatherid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "weather id was set! note that the server's original weather is id 5", MESSAGE_CASE_JARVIS); 
	return 1;
}

CMD:paycheck(playerid)
{
	SetPlayerSaver(playerid, (IsPlayerSaver(playerid)) ? 0 : 1);
	new string[STRING_SIZE_LARGE];
	format(string, sizeof string, "Your paycheck will now save %s", (IsPlayerSaver(playerid)) ? "in bank" : "on hand");
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
	return 1;
}

#if defined CHRISTMAS_MOD
CMD:christmas(playerid)
{
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Christmas CMDS:", MESSAGE_CASE_SERVER);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/snow, /snowman", MESSAGE_CASE_EMPTY);
	return 1;
}
alias:christmas("xmas", "xmashelp", "christmashelp", "santa", "santaclaus");
#endif

CMD:help(playerid)
{
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player CMDS:", MESSAGE_CASE_SERVER);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/stats, /report, /kill, /whisper, /bubble, /lights, /rules, /animlist, /stopanim, /plate", MESSAGE_CASE_EMPTY);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/buylevel, /admins, /ejectp, /nrc, /gps, /atm, /engine, /togsmoke, /lotto, /exitcity, /motel", MESSAGE_CASE_EMPTY);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/telecar, /lock, /outdrift, /switchfuel, /refuel, /paycheck, /outdrift, /entercity", MESSAGE_CASE_EMPTY);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/carcolor, /getfuel, /usecan, /ahelp, /cophelp, /viphelp, /myweather, /jointdm, /joinmko", MESSAGE_CASE_EMPTY);
	return 1;
}
alias:help("cmds");

CMD:motel(playerid)
{
	if(GetPlayerInterior(playerid) == MOTELROOM_INTERIOR && GetPlayerVirtualWorld(playerid) == playerid+MOTELROOM_VIRTUALWORLD)
	{
		SetPlayerPos(playerid, 2214.4973, -1150.5391, 1025.7969);
		SetPlayerInterior(playerid, 15);
		SetPlayerVirtualWorld(playerid, GetMotelVW(playerid));
	}
	return 1;
}

CMD:ahelp(playerid)
{
	if(IsPlayerADMIN(playerid))	
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Admin CMDS:", MESSAGE_CASE_SERVER);
		
     	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/spec , /specoff , /showrules , /cloak ", MESSAGE_CASE_EMPTY);

        if(GetPlayerADMIN(playerid) >= ADMIN_LEVEL_TWO) SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/goto , /kick , /getmute , /mute ", MESSAGE_CASE_EMPTY);

        if(GetPlayerADMIN(playerid) >= ADMIN_LEVEL_THREE) {
			SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/unmute , /ban , /get , /slap , /getgpci, /showrules, /bustip, /bustgpci", MESSAGE_CASE_EMPTY);
			SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/freeze , /unfreeze , /gotoveh , /getveh , /mytime, /jetpack, /cstats, /announce ", MESSAGE_CASE_EMPTY);
		}

        if(GetPlayerADMIN(playerid) >= ADMIN_LEVEL_FOUR) SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/cleardeaths , /clearchat , /respawncar ", MESSAGE_CASE_EMPTY);

        if(GetPlayerADMIN(playerid) >= ADMIN_LEVEL_FIVE) SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/setskin , /setworld , /setinterior , /giveweapon , /heallall , /armourall ", MESSAGE_CASE_EMPTY);

		if(GetPlayerADMIN(playerid) >= ADMIN_LEVEL_SIX) {
			SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/setcash , /setscore , /settime ", MESSAGE_CASE_EMPTY);
			SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/givecash , /givescore , /setweather ", MESSAGE_CASE_EMPTY);
		}

		if(GetPlayerADMIN(playerid) >= ADMIN_LEVEL_SEVEN) {
        SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/setwanted , /oban , /unban , /getip , /respawncars, /giveallcash, /bustgpci", MESSAGE_CASE_EMPTY);
		SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/getstats , /setcop , /giverep , /botban, /kickall, /giveallrep, /bustip ", MESSAGE_CASE_EMPTY);
		SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/pban, /unpban, /addmember, /delmember, /nameban, /rnameban, /car, /togcol ", MESSAGE_CASE_EMPTY);
		SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/playrewind, /recordrewind, /togglebar, /createhouse, /createshop, /gotoxyz", MESSAGE_CASE_EMPTY);
		}
	}
	else return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unauthorised cmd usage!", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:cophelp(playerid)
{
	if(IsPlayerCop(playerid)) 
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Cop CMDS:", MESSAGE_CASE_SERVER);
		SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/duty, /radio, /arrest", MESSAGE_CASE_EMPTY);
		SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, " /spikes, /delspikes, /delallspikes (chief only)", MESSAGE_CASE_EMPTY);
	}
	else return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unauthorised cmd usage!", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:viphelp(playerid)
{
	if(IsPlayerVIP(playerid)) 
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "VIP CMDS:", MESSAGE_CASE_SERVER);
		SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "/savehome , /gohome, /house ", MESSAGE_CASE_EMPTY);
	}
	else return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unauthorised cmd usage!", MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:cloak(playerid)
{
	if(!IsPlayerADMIN(playerid)) return RestrictForAdmin(playerid, ADMIN_LEVEL_ONE);

	adminCloak{playerid} = !adminCloak{playerid};

	new string[STRING_SIZE_LARGE];
	format(string, sizeof string, "Admin cloak has been turned %s", (adminCloak{playerid}) ? "On" : "Off");
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
	return 1;
}

CMD:admins(playerid)
{
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Admins online:", MESSAGE_CASE_JARVIS);
	new string[STRING_SIZE_MEDIUM];
	new player_admin;
	new secondAdmin = GetPlayerADMIN(playerid);
	foreach(new i: Player)
	{
		player_admin = GetPlayerADMIN(i);
		if(player_admin < ADMIN_LEVEL_ONE) continue;

		if(secondAdmin != ADMIN_LEVEL_SEVEN)
		{
			if(adminCloak{i}) continue;
		}
		format(string, sizeof string, "Admin: %s, Level: %d", Player_TempName[i], player_admin);
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_EMPTY);
	}
	return 1;
}

CMD:ejectp(playerid, params[])
{
	new user;
	if(sscanf(params, "r", user))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to mention the player's name or ID", MESSAGE_CASE_SERVER);
	}

	if(GetPlayerVehicleID(user) == GetPlayerVehicleID(playerid) && playerid != user)
	{
		RemovePlayerFromVehicle(user);
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player ejected successfully!", MESSAGE_CASE_JARVIS);
		SendRDZMessage(user, RDZ_OFFICIAL_COLOR, "You've been ejected by the driver!", MESSAGE_CASE_SERVER);
	}
	else
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Error: Player invalid ID", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:nrc(playerid)
{
	if(GetPlayerWantedLevel(playerid) > 0 || IsPlayerOnDuty(playerid))
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to change colors while being in your state, try again later.", MESSAGE_CASE_JARVIS);

	new color = playerColors[random(sizeof(playerColors))];
	SetPlayerColor(playerid, color);

	SendRDZMessage(playerid, color, "Color changed! please don't spam the chat, this message has the same color as you", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:gps(playerid, params[])
{
	if(IsGPSOwner(playerid) || IsTempGPSOwner(playerid))
	{
		Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");
	}
	else
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have a GPS, buy one from a 24/7 shop", MESSAGE_CASE_SERVER);
	}
	return 1;
}

CMD:atm(playerid, params[])
{
	new amount, type;
	if(sscanf(params, "ii", type, amount))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Make sure to state the transaction type (0 for withdrawing, 1 for depositing) then the amount you'd like to withdraw", MESSAGE_CASE_SERVER),
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Example usage: /atm 0 900 (Will withdraw 900) or /atm 1 900 (will deposit 900)", MESSAGE_CASE_EMPTY);
	}

	if(!IsPlayerInRangeOfPoint(playerid, 7.0, -1981.96, 112.02, 27.68)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be near the ATM clsoe to the SF train station", MESSAGE_CASE_JARVIS);

	if(type != 0 && type != 1) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Make sure that type is between 0 and 1", MESSAGE_CASE_SERVER);

	switch(type)
	{
		case 0://withdraw
		{
			if(GetPlayerBankB(playerid) < amount) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough bank balance!", MESSAGE_CASE_SERVER);
			GivePlayerMoney(playerid, amount);
			IncreasePlayerBankB(playerid, -amount);
		}
		case 1://depositing
		{
			if(GetPlayerMoney(playerid) < amount) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough cash on hand!", MESSAGE_CASE_SERVER);
			GivePlayerMoney(playerid, -amount);
			IncreasePlayerBankB(playerid, amount);
		}
	}
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Transaction has been completed!", MESSAGE_CASE_JARVIS);
	return 1;
}

Dialog:DIALOG_STATS(playerid, response, listitem, inputtext[])
{
	if(response)
	{

	}
	return 1;
}

Dialog:DIALOG_GPZJOBS(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -52.9399, -231.0744, 6.7646, 3.0);//mechanic
			}
			case 1:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 1366.2434, -1275.1842, 13.5469, 3.0);//weaponsdealer
			}
			case 2:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2481.7710, -1331.9948, 28.3017, 3.0);//drugdealer
			}
			case 3:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2506.9092, 2120.2793, 10.8398, 3.0);//prostitute
			}
			case 4:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 1968.7668, 2295.8728, 16.4559, 3.0);//bodyguard
			}
			case 5:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 1154.2208, -1770.8203, 16.5992, 3.0);//busdriver
			}
			case 6:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2229.6880, -1721.5259, 13.5638, 3.0);//fighter
			}
			case 7:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}


Dialog:DIALOG_GPZHIDEOUTS(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1978.8435, 501.4826, 29.1722, 3.0);//wangs hideout
			}
			case 1:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZSHOPS(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1658.2877, 1210.1606, 7.2500, 3.0);//rdz dealer
			}
			case 1:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1994.5275, 444.9895, 35.1719, 3.0);//24/7
			}
			case 2:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1992.5297, 202.6662, 27.6875, 3.0);//amumunation wangs
			}
			case 3:
			{
				gpsCP{playerid} = true;
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1659.3853, 302.4508, 7.3825, 3.0);//black market
			}
			case 4:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZRACES(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;//SF DOCKS RACE
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1530.5835, 458.8906, 7.2482, 3.0);
			}
			case 1:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZEVENTS(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;//DM
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1575.4401, 445.2654, 7.2412, 3.0);
			}
			case 1:
			{
				gpsCP{playerid} = true;//MKO
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1715.5656, 4.6664, 3.6824, 3.0);
			}
			case 2:
			{
				gpsCP{playerid} = true;//TDM
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1554.2957, 389.1695, 7.2260, 3.0);
			}
			case 3:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZMAIN(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				Dialog_Show(playerid, DIALOG_GPZJOBS, DIALOG_STYLE_LIST, "RogueDrifterZ Jobs", "MechanicJob\nWeaponDealerJob\nDrugDealerJob\nProstituteJob\nBodyguardJob\nBusdriverJob\nFighterJob\nBack", "Choose", "Cancel");
			}
			case 1:
			{
				Dialog_Show(playerid, DIALOG_GPZEVENTS, DIALOG_STYLE_LIST, "RogueDrifterZ Events", "DM Event\nMKO Event\nTDM Event\nBack", "Choose", "Cancel");
			}
			case 2:
			{
				Dialog_Show(playerid, DIALOG_GPZSHOPS, DIALOG_STYLE_LIST, "RogueDrifterZ Shops", "[RDZ]Dealer\n24/7\nAmmunation\nBlackMarket\nBack", "Choose", "Cancel");
			}
			case 3:
			{
				Dialog_Show(playerid, DIALOG_GPZHIDEOUTS, DIALOG_STYLE_LIST, "RogueDrifterZ Hideouts", "Wang's Hideout\nBack", "Ok", "Back");
			}
			case 4:
			{
				Dialog_Show(playerid, DIALOG_GPZRACES, DIALOG_STYLE_LIST, "RogueDrifterZ Races", "SF DOCKS\nBack", "Ok", "Back");
			}
			case 5:
			{
				Dialog_Show(playerid, DIALOG_GPZSIDE, DIALOG_STYLE_LIST, "RogueDrifterZ SideJobs", "Cars Collector\nBack", "Ok", "Back");
			}
			case 6:
			{
				Dialog_Show(playerid, DIALOG_GPZCITY, DIALOG_STYLE_LIST, "RogueDrifterZ Cities", "Liberty City\nIsland Hunt\nBV City\nMysterious Land\nBat land\nBack", "Ok", "Back");
			}
			case 7:
			{
				Dialog_Show(playerid, DIALOG_GPZTRACKS, DIALOG_STYLE_LIST, "RogueDrifterZ Tracks", "Track1\nTrack2\nBack", "Ok", "Back");
			}
			case 8:
			{
				gpsCP{playerid} = false;
				DisablePlayerCheckpoint(playerid);//disable gps
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZTRACKS(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;//sea track by vic
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -761.5813, 2931.0376, 33.2886, 3.0);
			}
			case 1:
			{
				gpsCP{playerid} = true;//island hunt
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -1455.7874, 1078.2522, 7.1875, 3.0);
			}
			case 2:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZCITY(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;//lib city
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -2989.6047, 472.7018, 4.9141, 3.0);
			}
			case 1:
			{
				gpsCP{playerid} = true;//island land
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -2956.6553, 459.4370, 4.5733, 3.0);
			}
			case 2:
			{
				gpsCP{playerid} = true;//island land
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 2900.1226, -808.6049, 11.0469, 3.0);
			}
			case 3:
			{
				gpsCP{playerid} = true;//mysterious land
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -2903.0625, 499.3619, 4.5707, 3.0 );
			}
			case 4:
			{
				gpsCP{playerid} = true;//bat land
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, -2899.8647, 424.6004, 4.5719 , 3.0);
			}
			case 5:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}

Dialog:DIALOG_GPZSIDE(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				gpsCP{playerid} = true;//cars collector
				DisablePlayerCheckpoint(playerid);
				SetPlayerCheckpoint(playerid, 1569.5016, -1199.4155, 19.7891, 3.0);
			}
			case 1:
			{
				Dialog_Show(playerid, DIALOG_GPZMAIN, DIALOG_STYLE_LIST, "RogueDrifterZ GPS", "Jobs\nMinigames\nShops\nHideouts\nRaces\nSideJobs\nCities\nTracks\nDisable GPS", "Choose", "Cancel");//back
			}
		}
	}
	return 1;
}

stock bool:IsPlayerUsingGPS(playerid)
	return (gpsCP{playerid});

#define CUSTOM_MAP_VW 696968
CMD:gotovice(playerid) 
{ 
	if(GetPlayerADMIN(playerid) == ADMIN_LEVEL_SEVEN)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
		{ 
			SetPlayerInterior(playerid, 0); 
			SetPlayerVirtualWorld(playerid, 696967); 
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),696967); 
			SetVehiclePos(GetPlayerVehicleID(playerid),5017.89203,834.71497,11.0); 
			SetVehicleZAngle(GetPlayerVehicleID(playerid), 180); 
			GameTextForPlayer(playerid, "~b~~h~Vice City", 3000, 3); 
		} 
		else 
		{ 
			SetPlayerInterior(playerid, 0); 
			SetPlayerVirtualWorld(playerid, 696967); 
			SetPlayerPos(playerid,5017.89203,834.71497,11.0); 
			SetPlayerFacingAngle(playerid, 180); 
			GameTextForPlayer(playerid, "~b~~h~Vice City", 3000, 3); 
		} 
	}
	return 1; 
} 
CMD:gotolib(playerid) 
{ 
	if(GetPlayerADMIN(playerid) == ADMIN_LEVEL_SEVEN)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
		{ 
			new pveh; 
			pveh = GetPlayerVehicleID(playerid); 
			SetPlayerInterior(playerid, 0); 
			SetPlayerVirtualWorld(playerid, CUSTOM_MAP_VW); 
			SetVehicleVirtualWorld(pveh,CUSTOM_MAP_VW); 
			SetVehiclePos(pveh,-5240.7021,-372.1064,15.6388); 
			SetVehicleZAngle(pveh, 180); 
			GameTextForPlayer(playerid, "~b~~h~Liberty City", 3000, 3); 
		} 
		else 
		{ 
			SetPlayerInterior(playerid, 0); 
			SetPlayerVirtualWorld(playerid, CUSTOM_MAP_VW); 
			SetPlayerPos(playerid,-5228.8399658,-404.5500488,18.2250004); 
			SetPlayerFacingAngle(playerid, 180); 
			GameTextForPlayer(playerid, "~b~~h~Liberty City", 3000, 3); 
		} 
	}
	return 1; 
}  