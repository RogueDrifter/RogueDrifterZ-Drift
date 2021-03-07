#if defined RDZ_SPAWN_Included_
   #endinput
#endif

#define RDZ_SPAWN_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define RANDOM_MESSAGE_COLOR 0xCC99FFFF
#define MAX_GENERAL_TDS 5
#define LIGHT_ID_SAFEZONE 0

static RMSG_Timer, 
	Text:General_TDS[MAX_GENERAL_TDS];
static  bool:IsPlayerInCity[MAX_PLAYERS char];
static IsVInCity[MAX_VEHICLES char];

static RandomMSG[][] =
{
    ".:No cheats, hacks, mods are allowed here, using them will cause in a instant ban!:.", 
	".:[RDZ]RogueDrifterZ Made by Andy[RDZ]:.", 
	".:Read /help, /rules to help you during your gameplay:.", 
	".:Spotted a cheater? /report to admins right away!:.", 
	".:You need to have at least 100 PlayingHours to get COP:.", 
	".:ONLY ENGLISH in the main chat, for other languages use /b, /w:.", 
	".:You can use /switchfuel to change your fuel indicator:.", 
	".:Use /refuel at fuel stations to refuel the car:.", 
	".:Use /getfuel to refill your gas can:.", 
	".:Use /refuel at fuel stations to refill your car:.", 
	".:Enjoying your time here?, Add us to your favorites! :.", 
	".:You can enter any shop by using L-ALT (LEFT ALT) button near the pickup:.", 
	".:A reputation system was installed here:.", 
	".:If you cheat you'll get caught and you'll be punished:.", 
	".:AFK players do not receieve paychecks/exp/playinghours:.", 
	".:Ask /Admins for help at any time we provide 24/7 support!:.", 
	".:Paychecks are served every 1 hour!:.", 
	".:Offical RogueDrifter Discord https://discord.gg/5tEuv2d:.", 
	".:Remember that after all this is a game and we here are more than members, we are a family:..", 
	".:Multiaccounting is not tolerated here and will result in a ban!:.", 
	".:Many things can be found using /gps while in a vehicle:.", 
	".:If you ever get banned take a screenshot and save game logs and make a ban appeal:.", 
	".:In order to repair press 2 to repair your vehicle and regain nos, ctrl to use nos!:.", 
	".:Weapons bought from ammunations are for self defense only!:.", 
	".:To change a car's color use /carcolor [id1] [id2] or /cc [id1] [id2]:.", 
	".: Vehicles can now be purchased from the RDZ Dealership and forever remain yours to keep or sell in future :.", 
    ".:Vip players gain 2x exp the normal players gain!:.", 
    ".: Make sure that you register on our forums: Roguedrifterz.forumotion.com :.", 
	".:This server supports both 0.3.7 and 0.3.DL versions of SAMP!:.", 
	".:We would love to hear your suggestions over our discord server:.", 
	".:No racism or flaming we are all a big family here:.", 
	".:Respect admins and staff members at all costs!:.", 
	".:The server has its own custom.img file you can download through the forum:.", 
	".:Use the /gps to help you find positions as you carry it everywhere:.", 
	".:Hope you enjoy playing on the RogueDrifterZ server one of the best drifting servers out there!:.", 
	".:Encountered a bug? report it to admins straight away!:.", 
	".:/myweather to set your own weather!:.", 
	".:Player's level give them special privilliges, /stats to check your level and /buylevel to increase your level:.", 
	".:You gain 1 Exp and 1 rep point every 1 paycheck!:."
};

forward SendMSG();
public SendMSG()
{
    new randMSG = random(sizeof(RandomMSG));
    SendRDZMessage(INVALID_PLAYER_ID, RANDOM_MESSAGE_COLOR, RandomMSG[randMSG], MESSAGE_CASE_NULL);
	return 1;
}

hook OnGameModeInit()
{
	RMSG_Timer = SetTimer("SendMSG", 500000, true);

	General_TDS[0] = TextDrawCreate( 542.333374, 19.496398, "]RogueDrifterz]");
	TextDrawLetterSize(General_TDS[0], 0.179000, 1.168591);
	TextDrawAlignment(General_TDS[0], 1);
	TextDrawColor(General_TDS[0], 255);
	TextDrawSetShadow(General_TDS[0], 0);
	TextDrawSetOutline(General_TDS[0], 1);
	TextDrawBackgroundColor(General_TDS[0], -1768515841 );
	TextDrawFont(General_TDS[0], 2);
	TextDrawSetProportional(General_TDS[0], 1);

	General_TDS[1] = TextDrawCreate( 545.933374, 28.996398, "__RDZ");
	TextDrawLetterSize(General_TDS[1], 0.489999, 0.932148);
	TextDrawAlignment(General_TDS[1], 1);
	TextDrawColor(General_TDS[1], 255);
	TextDrawSetShadow(General_TDS[1], 0);
	TextDrawSetOutline(General_TDS[1], 1);
	TextDrawBackgroundColor(General_TDS[1], -1768515841 );
	TextDrawFont(General_TDS[1], 0);
	TextDrawSetProportional(General_TDS[1], 1);

	General_TDS[2] = TextDrawCreate( 547.000061, 28.807374, "[_________]");
	TextDrawLetterSize(General_TDS[2], 0.347666, 1.072963);
	TextDrawAlignment(General_TDS[2], 1);
	TextDrawColor(General_TDS[2], 255);
	TextDrawSetShadow(General_TDS[2], 0);
	TextDrawSetOutline(General_TDS[2], 1);
	TextDrawBackgroundColor(General_TDS[2], -1768515841 );
	TextDrawFont(General_TDS[2], 1);
	TextDrawSetProportional(General_TDS[2], 1);

	General_TDS[3] = TextDrawCreate(43.666660, 433.911041, "Roguedrifterz.forumotion.com");
	TextDrawLetterSize(General_TDS[3], 0.539999, 1.200000);
	TextDrawAlignment(General_TDS[3], 1);
	TextDrawColor(General_TDS[3], 255);
	TextDrawSetShadow(General_TDS[3], 0);
	TextDrawSetOutline(General_TDS[3], 1);
	TextDrawBackgroundColor(General_TDS[3], -1768515841 );
	TextDrawFont(General_TDS[3], 1);
	TextDrawSetProportional(General_TDS[3], 1);

	General_TDS[4] = TextDrawCreate(553.000061, 432.666595, "/HELP_/RULES");
	TextDrawLetterSize(General_TDS[4], 0.270666, 1.384294);
	TextDrawAlignment(General_TDS[4], 1);
	TextDrawColor(General_TDS[4], 255);
	TextDrawSetShadow(General_TDS[4], 0);
	TextDrawSetOutline(General_TDS[4] , 1);
	TextDrawBackgroundColor(General_TDS[4], -1768515841);
	TextDrawFont(General_TDS[4] , 2);
	TextDrawSetProportional(General_TDS[4], 1);

	CreateLights (LIGHT_TYPE_WHITE, LIGHT_ID_SAFEZONE, -2514.59473, -626.23242, 164.94130,   -69.00000, 25.00000, 4.00000);
	KeepLightsOn(LIGHT_ID_SAFEZONE, LIGHT_TYPE_WHITE, true);
	DanceLights(LIGHT_ID_SAFEZONE, LIGHT_TYPE_WHITE, true);  

	return 1;
}

hook OnGameModeExit()
{
	DestroyLights (LIGHT_ID_SAFEZONE, LIGHT_TYPE_WHITE);
	for( new x; x < MAX_GENERAL_TDS; x++ )
	{
		TextDrawDestroy(General_TDS[x]);
	}
	KillTimer(RMSG_Timer);
	return 1;
}

hook OnPlayerAFK(playerid, time_in_seconds)
{
	if(!IsPlayerVIP(playerid) && !IsPlayerADMIN(playerid) && time_in_seconds >= 60*30)
	{
		if(time_in_seconds == 60*30)
		{
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're about to get kicked for being afk, better move it!", MESSAGE_CASE_SERVER);
		}
		else if(time_in_seconds == 60*30+3)
		{
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're about to get kicked for being afk, this is your last warning!", MESSAGE_CASE_SERVER);
		}
		else
		{
			new kick_afk_string[STRING_SIZE_LARGE];
			format(kick_afk_string, sizeof kick_afk_string, "Player %s was kicked, reason: Idle for too long.", Player_TempName[playerid]);
			SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, kick_afk_string, MESSAGE_CASE_SERVER);
			Kick(playerid);
		}
	}
	return 1;
}

stock OnPlayerSpawnEx(playerid, case_type)
{
	if(!IsPlayerInJail(playerid) && !IsPlayerInEvent(playerid))
	{
		switch(case_type)
		{
			case CASE_REGISTER:
			{
				if(!IsPlayerCop(playerid)) 
				{
					SetPlayerPos(playerid, -2539.0410, -610.9685, 132.7109); 
					SetPlayerFacingAngle(playerid, 262.5524);
				}
				else
				{
					SetPlayerPos(playerid, -1616.2546, 683.4163, 7.1875);
				}
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);

				SetCameraBehindPlayer(playerid);


			}
			case CASE_LOGIN:
			{
				SetPlayerPos(playerid, GetPlayerX(playerid), GetPlayerY(playerid), GetPlayerZ(playerid));
				SetPlayerFacingAngle(playerid, GetPlayerR(playerid));

				SetPlayerInterior(playerid, GetPlayerInt(playerid));
				SetPlayerVirtualWorld(playerid, GetPlayerWorld(playerid));
			}
		}
	}
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	IsPlayerInCity{playerid} = false;
	return 1;
}

hook OnPlayerConnect(playerid)
{
	for( new x; x < MAX_GENERAL_TDS; x++ )
	{
		TextDrawShowForPlayer( playerid, General_TDS[x] );
	}
	return 1;
}

hook OnPlayerPause(playerid, time_in_seconds)
{
	if(!IsPlayerVIP(playerid) && !IsPlayerADMIN(playerid))
	{
		if(time_in_seconds == 60*30)
		{
			new kick_afk_string[STRING_SIZE_LARGE];
			format(kick_afk_string, sizeof kick_afk_string, "Player %s was kicked, reason: Idle for too long.", Player_TempName[playerid]);
			SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, kick_afk_string, MESSAGE_CASE_SERVER);
			Kick(playerid);
		}
	}

	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
	SetPlayerSpawned(playerid, true);
	return 1;
}

hook OnPlayerDisconnect( playerid, reason )
{
	IsPlayerInCity{playerid} = false;
	for( new x; x < MAX_GENERAL_TDS; x++ )
	{
		TextDrawHideForPlayer( playerid, General_TDS[x] );
	}
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
    SetPlayerPos(playerid, 305.8891, 305.6985, 999.1484);
	SetPlayerInterior(playerid, 4);
	SetPlayerVirtualWorld(playerid, playerid);
	SetPlayerFacingAngle(playerid, 85.0351);
	SetPlayerCameraPos(playerid, 302.58, 305.86, 999.15);
	SetPlayerCameraLookAt(playerid, 305.8891, 305.6985, 999.1484);
    return 1;
}

hook OnPlayerText(playerid, text[])
{
	if(IsPlayerVIP(playerid) && !IsPlayerInEvent(playerid))
	{
		if(strgetfirstc(text) == '*' && strgetc(text, 1) == ' ')
		{
			SendMessageToVIPs(playerid, text);
			return 0;
		}
	}
	if(IsPlayerADMIN(playerid))
	{
		if(strgetfirstc(text) == '@' && strgetc(text, 1) == ' ' )
		{
			SendMessageToAdminsChat(playerid, text);
			return 0;
		}
	}
	return 1;
}

CMD:recordrewind(playerid)
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN ) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	StartRecordingRewindSynced(playerid);

	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Recording has started! Dialog will be shown once complete!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:playrewind(playerid)
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN ) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	StartRewinding(playerid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Rewind playing request was sent!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:togglebar(playerid)
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN ) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
	switch(IsRewindBarShown(playerid))
	{
		case true:
		{
			HideTimeMachineSynced(playerid);
		}
		case false:
		{
			ShowTimeMachineSynced(playerid);
		}
	}
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Bar stats was switched!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:entercity(playerid)
{
	new pstate = GetPlayerState(playerid);
	new vehicleid = GetPlayerVehicleID(playerid);
	new success;
	if( GetPlayerWantedLevel(playerid) == 0 && !IsPlayerInCity{playerid} && pstate != PLAYER_STATE_PASSENGER)
	{
		if(IsPlayerInRangeOfPoint(playerid, 10.0, -2902.48535, 503.18011, 10.04199))
		{
			if(pstate == PLAYER_STATE_ONFOOT) SetPlayerPos(playerid, 791.4851, -2499.6560, 6.8036);
			else 
			{
				RemovePlayerFromVehicle(playerid);
				SetTimerEx("DelayVehicleTP", 3200, false, "ii", GetPlayerVehicleID(playerid), 0);
				SetTimerEx("DelayintroTP", 5000, false, "ii", playerid, 0);
			}
			success = 1;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 10.0, -2956.6553, 459.4370, 4.5733))
		{
			if(pstate == PLAYER_STATE_ONFOOT) SetPlayerPos(playerid, -797.7347, -7503.1196, 48.8095);
			else 
			{
				RemovePlayerFromVehicle(playerid);
				SetTimerEx("DelayVehicleTP", 3200, false, "ii", GetPlayerVehicleID(playerid), 1);
				SetTimerEx("DelayintroTP", 5000, false, "ii", playerid, 1);
			}
			success = 1;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 10.0, -2900.39624, 423.23120, 10.41740))
		{
			if(pstate == PLAYER_STATE_ONFOOT) SetPlayerPos(playerid, 2203.8540, -5274.8198, 11.5389);
			else 
			{
				RemovePlayerFromVehicle(playerid);
				SetTimerEx("DelayVehicleTP", 3200, false, "ii", GetPlayerVehicleID(playerid), 2);
				SetTimerEx("DelayintroTP", 5000, false, "ii", playerid, 2);
			}
			success = 1;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 10.0, -2992.88745, 471.33676, 8.07187))
		{
			if(pstate == PLAYER_STATE_ONFOOT) SetPlayerPos(playerid, -750.80, 491.00, 1376.70);
			else 
			{
				LinkVehicleToInterior(vehicleid, 1);
				RemovePlayerFromVehicle(playerid);
				SetTimerEx("DelayVehicleTP", 3200, false, "ii", vehicleid, 3);
				SetTimerEx("DelayintroTP", 5000, false, "ii", playerid, 3);
			}
			SetPlayerInterior(playerid, 1);
			success = 2;
		}
		if(success)
		{
			TogglePlayerControllable(playerid, false);
			IsPlayerInCity{playerid} = true;
			SetTimerEx("removeFreeze", 8000, false, "i", playerid);
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Use /exitcity to leave the place whenever", MESSAGE_CASE_SERVER);
			SetPlayerVirtualWorld(playerid, CITIES_WORLD);
			Streamer_Update(playerid);
			if(pstate == PLAYER_STATE_DRIVER)
			{
				new Float:x, Float:y, Float:z;
				foreach(new i: Player)
				{
					if(i != playerid && GetPlayerVehicleID(i) == vehicleid)
					{
						GetPlayerPos(i, x, y, z);
						SetPlayerPos(i, x, y, z+2);
					}
				}
			}
		}
	}
	if(!success) return 	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Must be near one of the city portals!", MESSAGE_CASE_SERVER);
	return 1;
}

forward removeFreeze(playerid);
public removeFreeze(playerid) return TogglePlayerControllable(playerid, true);

CMD:exitcity(playerid)
{
	if(IsPlayerInCity{playerid})
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehiclePos(vehicleid, -2968.4380, 471.2759, 6.5744);
			SetVehicleVirtualWorld(vehicleid, NORMAL_VIRTUAL_WORLD);
			LinkVehicleToInterior(vehicleid, NORMAL_INTERIOR);
		}
		else { 
			SetPlayerPos(playerid, -2968.4380, 471.2759, 6.5744);
		}
		SetPlayerInterior(playerid, NORMAL_INTERIOR);
		SetPlayerVirtualWorld(playerid, NORMAL_VIRTUAL_WORLD);
		IsPlayerInCity{playerid} = false;
	}
	return 1;
}

forward DelayVehicleTP(vehicleid, handle);
public DelayVehicleTP(vehicleid, handle)
{	
	SetVehicleVirtualWorld(vehicleid, CITIES_WORLD);
	IsVInCity{vehicleid} = true;
	switch(handle)
	{
		case 0:
		{
			SetVehiclePos(vehicleid, 791.4851, -2499.6560, 6.8036);
		}
		case 1:
		{
			SetVehiclePos(vehicleid, -797.7347, -7503.1196, 48.8095);
		}
		case 2:
		{
			SetVehiclePos(vehicleid, 2203.8540, -5274.8198, 11.5389);
		}
		case 3:
		{
			SetVehiclePos(vehicleid, -750.80, 491.00, 1376.70);
		}
	}
	return 1;
}

forward DelayintroTP(playerid, handle);
public DelayintroTP(playerid, handle)
{
	switch(handle)
	{
		case 0:
		{
			SetPlayerPos(playerid, 791.4851, -2499.6560, 6.8036);
		}
		case 1:
		{
			SetPlayerPos(playerid, -797.7347, -7503.1196, 48.8095);
		}
		case 2:
		{
			SetPlayerPos(playerid, 2203.8540, -5274.8198, 11.5389);
		}
		case 3:
		{
			SetPlayerPos(playerid, -750.80, 491.00, 1376.70);
		}
	}
	return 1;
}

stock IsInCity(playerid)
	return IsPlayerInCity{playerid};
stock IsVehicleInCity(vehicleid)
	return IsVInCity{vehicleid};

hook OnVehicleSpawn(vehicleid)
{
	if(IsVehicleInCity(vehicleid))
	{
		LinkVehicleToInterior(vehicleid, 0);
		SetVehicleVirtualWorld(vehicleid, 0);
	}
	return 1;
}

CMD:stopani(playerid, params[])
{
	if(GetPVarInt(playerid, "UsingAnim") == 1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Your animations were cleared!", MESSAGE_CASE_EMPTY);
			ClearAnimations(playerid);
			SetPlayerSkin(playerid, GetPlayerSkin(playerid));
			DeletePVar(playerid, "UsingAnim");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
	else SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You are currently not using any animation", MESSAGE_CASE_EMPTY);
	return 1;
}
alias:stopani("stopanim");

CMD:animlist(playerid, params[])
{
	new str[1500];
	strcat(str, "/handsup, /dance, /rap, /wank, /strip, /sexy, /bj, /cell, /lean, /piss, /robman\n");
	strcat(str, "/greet, /injured, /hitch, /bitchslap, /cpr, /gsign, /gift, /getup, /follow\n");
	strcat(str, "/sit, /stand, /slapped, /slapass, /drunk, /gwalk, /walk, /celebrate, /win /checkout\n");
	strcat(str, "/yes, /deal, /thankyou, /invite1, /scratch, /bomb, /getarrested, /laugh \n");
	strcat(str, "/crossarms, /lay, /cover, /vomit, /eat, /wave, /crack, /smoke,  /lookout\n");
	strcat(str, "/chat, /fucku, /taichi, /chairsit, /relax, /bat /nod, /cry /chant, /carsmoke, /aim\n");
	strcat(str, "/gang1, /bed, /carsit, /stretch, /angry, /kiss, /exhausted, /ghand, /benddown\n");
	strcat(str, "/basket, /akick, /box, /cockgun, /bar, /lay, /liftup, /putdown, /joint\n");
	Dialog_Show(playerid, DIALOG_SHOW_INFO, DIALOG_STYLE_MSGBOX, "{FFFFFF}Animation List", str, "Ok", "Cancel");
    return 1;
}
alias:animlist("anims");

CMD:handsup(playerid, params[])
{
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:carry(playerid, params[])
{
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:dance(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /dance [1-4]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
    return 1;
}

CMD:rap(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /rap [1-3]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "RAPPING", "RAP_A_Loop", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "RAPPING", "RAP_B_Loop", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "RAPPING", "RAP_C_Loop", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:wank(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /wank [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "PAULNMAC", "wank_in", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "PAULNMAC", "wank_loop", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:strip(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /strip [1-7]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_A", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_B", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_C", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_D", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "5", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_E", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "6", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_F", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "7", true) == 0)
	{
		ApplyAnimation(playerid, "STRIP", "strip_G", 4.0, 1, 1, 1, 1, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}
CMD:sexy(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /strip [1-8]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKING_IDLEW", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKING_IDLEP", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKINGW", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKINGP", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "5", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKEDW", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "6", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKEDP", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "7", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKING_ENDW", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "8", true) == 0)
	{
		ApplyAnimation(playerid, "SNM", "SPANKING_ENDP", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:bj(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /bj [1-4]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:cell(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /cell [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:lean(playerid, params[])
{
	ApplyAnimation(playerid, "GANGS", "leanIDLE", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:piss(playerid, params[])
{
	SetPlayerSpecialAction(playerid, 68);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:follow(playerid, params[])
{
	ApplyAnimation(playerid, "WUZI", "Wuzi_follow", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:greet(playerid, params[])
{
	ApplyAnimation(playerid, "WUZI", "Wuzi_Greet_Wuzi", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:stand(playerid, params[])
{
	ApplyAnimation(playerid, "WUZI", "Wuzi_stand_loop", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:hitch(playerid, params[])
{
	ApplyAnimation(playerid, "MISC", "Hiker_Pose", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:bitchslap(playerid, params[])
{
	ApplyAnimation(playerid, "MISC", "bitchslap", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:cpr(playerid, params[])
{
	ApplyAnimation(playerid, "MEDIC", "CPR", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:gsign(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /gsign [1-5]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "GHANDS", "gsign1", 4.0, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "GHANDS", "gsign2", 4.0, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "GHANDS", "gsign3", 4.0, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "GHANDS", "gsign4", 4.0, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "5", true) == 0)
	{
		ApplyAnimation(playerid, "GHANDS", "gsign5", 4.0, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:gift(playerid, params[])
{
	ApplyAnimation(playerid, "KISSING", "gift_give", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:chairsit(playerid, params[])
{
	ApplyAnimation(playerid, "PED", "SEAT_idle", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:injured(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /injured [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:slapped(playerid, params[])
{
	ApplyAnimation(playerid, "SWEET", "ho_ass_slapped", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:slapass(playerid, params[])
{
	ApplyAnimation(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:drunk(playerid, params[])
{
	ApplyAnimation(playerid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 1, 1);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:skate(playerid, params[])
{
	ApplyAnimation(playerid, "SKATE", "skate_run", 4.1, 1, 1, 1, 1, 1);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:gwalk(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /gwalk [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:limp(playerid, params[])
{
	ApplyAnimation(playerid, "PED", "WALK_old", 4.1, 1, 1, 1, 1, 1);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:eatsit(playerid, params[])
{
    ApplyAnimation(playerid, "FOOD", "FF_Sit_Loop", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:win(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /win [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "CASINO", "cards_win", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "CASINO", "Roulette_win", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:celebrate(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /celebrate [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "benchpress", "gym_bp_celebrate", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "GYMNASIUM", "gym_tread_celebrate", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:yes(playerid, params[])
{
	ApplyAnimation(playerid, "CLOTHES", "CLO_Buy", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:deal(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /deal [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 3.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "DEALER", "DRUGS_BUY", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:thankyou(playerid, params[])
{
	ApplyAnimation(playerid, "FOOD", "SHP_Thank", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:invite1(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /invite1 [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "Invite_Yes", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "Invite_No", 4.1, 0, 1, 1, 1, 1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:scratch(playerid, params[])
{
	ApplyAnimation(playerid, "MISC", "Scratchballs_01", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:bomb(playerid, params[])
{
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0); // Place Bomb
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:getarrested(playerid, params[])
{
	ApplyAnimation(playerid, "ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1); // Gun Arrest
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:laugh(playerid, params[])
{
	ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0); // Laugh
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:lookout(playerid, params[])
{
	ApplyAnimation(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0); // Rob Lookout
	SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:robman(playerid, params[])
{
	ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0); // Rob
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:crossarms(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /crossarms [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "DEALER", "DEALER_IDLE", 4.0, 0, 1, 1, 1, -1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "DEALER", "DEALER_IDLE", 4.0, 0, 1, 1, 1, -1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_01", 4.0, 0, 1, 1, 1, -1);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:vomit(playerid, params[])
{
	ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:eat(playerid, params[])
{
	ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0); // Eat Burger
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:wave(playerid, params[])
{
	ApplyAnimation(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0); // Wave
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:smoke(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /smoke [1-2]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:gro(playerid, params[])
{
	ApplyAnimation(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:sit(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /sit [1-3]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "BEACH", "ParkSit_W_loop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "BAR", "dnk_stndF_loop", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:chat(playerid, params[])
{
	ApplyAnimation(playerid, "PED", "IDLE_CHAT", 4.1, 1, 1, 1, 1, 1);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:fucku(playerid, params[])
{
	ApplyAnimation(playerid, "PED", "fucku", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:taichi(playerid, params[])
{
	ApplyAnimation(playerid, "PARK", "Tai_Chi_Loop", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:relax(playerid, params[])
{
	ApplyAnimation(playerid, "BEACH", "Lay_Bac_Loop", 4.0, 1, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:bat(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /bat [1-5]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "BASEBALL", "Bat_IDLE", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "BASEBALL", "Bat_M", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "BASEBALL", "BAT_PART", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "CRACK", "Bbalbat_Idle_01", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "5", true) == 0)
	{
		ApplyAnimation(playerid, "CRACK", "Bbalbat_Idle_02", 4.0, 1, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:nod(playerid, params[])
{
	ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_nod", 4.0, 0, 0, 0, 0, 0);
	SetPVarInt(playerid, "UsingAnim", 1);
	return 1;
}

CMD:gang(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /gang [1-7]", MESSAGE_CASE_EMPTY);
		return 1;
	}
	if(strcmp(choice, "1", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "2", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "3", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "4", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "5", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "6", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	if(strcmp(choice, "7", true) == 0)
	{
		ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0);
		SetPVarInt(playerid, "UsingAnim", 1);
	}
	return 1;
}

CMD:cry(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /cry [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "GRAVEYARD", "mrnF_loop", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "GRAVEYARD", "mrnM_loop", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:bed(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /bed [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "INT_HOUSE", "BED_In_L", 4.1, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "INT_HOUSE", "BED_In_R", 4.1, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "3", true) == 0)
    {
        ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_L", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "4", true) == 0)
    {
        ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_R", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:kiss(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /kiss [1-6]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "3", true) == 0)
    {
        ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "4", true) == 0)
    {
        ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "5", true) == 0)
    {
        ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "6", true) == 0)
    {
        ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:carsit(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /carsit [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "CAR", "Tap_hand", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "LOWRIDER", "Sit_relaxed", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:walk(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /walk [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "ped", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "ped", "WALK_player", 4.1, 1, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:stretch(playerid, params[])
{
    ApplyAnimation(playerid, "PLAYIDLES", "stretch", 4.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:chant(playerid, params[])
{
    ApplyAnimation(playerid, "RIOT", "RIOT_CHANT", 4.0, 1, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:angry(playerid, params[])
{
    ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY", 4.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:crack(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /crack [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "CRACK", "crckidle2", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:ghand(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /ghand [1-5]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign1LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "3", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "4", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign3LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "5", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign4LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "6", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign5LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:exhausted(playerid, params[])
{
    ApplyAnimation(playerid, "FAT", "IDLE_tired", 4.0, 1, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:carsmoke(playerid, params[])
{
    ApplyAnimation(playerid, "PED", "Smoke_in_car", 4.0, 1, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:getup(playerid, params[])
{
    ApplyAnimation(playerid, "PED", "getup", 4.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:basket(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /basket [1-6]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_def_loop", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_idleloop", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "3", true) == 0)
    {
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_pickup", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "4", true) == 0)
    {
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_Jump_Shot", 4.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "5", true) == 0)
    {
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_Dnk", 4.1, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "6", true) == 0)
    {
        ApplyAnimation(playerid, "BSKTBALL", "BBALL_run", 4.1, 1, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:akick(playerid, params[])
{
    ApplyAnimation(playerid, "FIGHT_E", "FightKick", 4.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:box(playerid, params[])
{
    ApplyAnimation(playerid, "GYMNASIUM", "gym_shadowbox", 4.1, 1, 1, 1, 1, 1);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:cockgun(playerid, params[])
{
    ApplyAnimation(playerid, "SILENCED", "Silence_reload", 3.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:bar(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {   
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /bar [1-4]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "BAR", "Barcustom_get", 3.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.0, 0, 1, 1, 1, 1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "BAR", "Barcustom_order", 3.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "3", true) == 0)
    {
        ApplyAnimation(playerid, "BAR", "Barserve_give", 3.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "4", true) == 0)
    {
        ApplyAnimation(playerid, "BAR", "Barserve_glass", 3.0, 0, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:lay(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /lay [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "BEACH", "bather", 4.0, 1, 0, 0, 0, 0); // Lay down
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "BEACH", "SitnWait_loop_W", 4.0, 1, 0, 0, 0, 0); // Lay down
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}
CMD:liftup(playerid, params[])
{
    ApplyAnimation(playerid, "CARRY", "liftup", 3.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:putdown(playerid, params[])
{
    ApplyAnimation(playerid, "CARRY", "putdwn", 3.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:joint(playerid, params[])
{
    ApplyAnimation(playerid, "GANGS", "smkcig_prtl", 4.0, 0, 1, 1, 1, 1);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}
CMD:benddown(playerid, params[])
{
    ApplyAnimation(playerid, "BAR", "Barserve_bottle", 4.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}
CMD:shakehead(playerid, params[])
{
    ApplyAnimation(playerid, "MISC", "plyr_shkhead", 3.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

CMD:aim(playerid, params[])
{
    new choice[32];
    if(sscanf(params, "s[32]", choice))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "USAGE: /aim [1-2]", MESSAGE_CASE_EMPTY);
        return 1;
    }
    if(strcmp(choice, "1", true) == 0)
    {
        ApplyAnimation(playerid, "PED", "gang_gunstand", 4.0, 1, 0, 0, 0, 0);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    if(strcmp(choice, "2", true) == 0)
    {
        ApplyAnimation(playerid, "SHOP", "SHP_Gun_Aim", 4.0, 0, 1, 1, 1, -1);
        SetPVarInt(playerid, "UsingAnim", 1);
    }
    return 1;
}

CMD:checkout(playerid, params[])
{
    ApplyAnimation(playerid, "GRAFFITI", "graffiti_Chkout", 4.0, 0, 0, 0, 0, 0);
    SetPVarInt(playerid, "UsingAnim", 1);
    return 1;
}

stock HideGeneralTDsForPlayer(playerid)
{
	for( new x; x < MAX_GENERAL_TDS; x++ )
	{
		TextDrawHideForPlayer( playerid, General_TDS[x] );
	}
	return 1;
}

stock ShowGeneralTDsForPlayer(playerid)
{
	for( new x; x < MAX_GENERAL_TDS; x++ )
	{
		TextDrawShowForPlayer( playerid, General_TDS[x] );
	}
	return 1;
}
