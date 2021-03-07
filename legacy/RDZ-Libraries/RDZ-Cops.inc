#if defined RDZ_COPS_Included_
   #endinput
#endif

#define RDZ_COPS_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static bool:playerTazed[MAX_PLAYERS char], 
	   bool:playerDuty[MAX_PLAYERS char],
	   markerTimer[MAX_PLAYERS];

#define TAZE_TIME 10*1000
#define COP_COLOR 0x2641FEAA
#define BASIC_COP_SKIN 281
#define COP_RADIO_MESSAGE_COLOR 0x8D8DFF00

#define ARREST_RANGE 10.000

enum E_SKIN_LISTITEM
{
    E_SKIN_LISTITEM_MODEL
};

static const SKIN_LIST[][E_SKIN_LISTITEM] =
{
    {265},
    {266},
    {267},
    {280},
    {281},
    {282},
    {283},
    {284},
    {286},
    {310},
    {311},
    {300},
    {301},
    {302},
    {306},
    {307},
    {309},
    {246}
};

Dialog:DIALOG_COPSKINS(playerid, response, listitem, inputtext[]) 
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				SetPlayerSkin(playerid, 265);
			}
			case 1:
			{
				SetPlayerSkin(playerid,266 );
			}
			case 2:
			{
				SetPlayerSkin(playerid, 267);
			}
			case 3:
			{
				SetPlayerSkin(playerid, 280);
			}
			case 4:
			{
				SetPlayerSkin(playerid, 281);
			}
			case 5:
			{
				SetPlayerSkin(playerid, 282);
			}
			case 6:
			{
				SetPlayerSkin(playerid, 283);
			}
			case 7:
			{
				SetPlayerSkin(playerid, 284);
			}
			case 8:
			{
			SetPlayerSkin(playerid, 286);
			}
			case 9:
			{
				SetPlayerSkin(playerid, 310);
			}
			case 10:
			{
				SetPlayerSkin(playerid, 311);
			}
			case 11:
			{
				SetPlayerSkin(playerid, 300);
			}
			case 12:
			{
				SetPlayerSkin(playerid, 301);
			}
			case 13:
			{
				SetPlayerSkin(playerid,302 );
			}
			case 14:
			{
				SetPlayerSkin(playerid, 306);
			}
			case 15:
			{
				SetPlayerSkin(playerid, 307);
			}
			case 16:
			{
				SetPlayerSkin(playerid, 309);
			}
			case 17:
			{
				SetPlayerSkin(playerid, 246);
			}
		}
	}
	return 1;
}

stock SetDutyStats(playerid, bool:duty_case, bool:case_death = false)
{
	switch(duty_case)
	{
		case true:
		{
			markerTimer[playerid] = SetTimerEx("removeMarker", 1000, true, "i", playerid);
			ResetPlayerWeapons(playerid);
			GivePlayerWeapon(playerid, 23, 500);
			GivePlayerWeapon(playerid, 31, 500);
			GivePlayerWeapon(playerid, 34, 500);
			GivePlayerWeapon(playerid, 27, 500);
			GivePlayerWeapon(playerid, 28, 500);
			GivePlayerWeapon(playerid, 41, 1500);
			SetPlayerColor(playerid, COP_COLOR);
			SetPlayerArmour(playerid, 100);
			SetPlayerSkin(playerid, BASIC_COP_SKIN);
			ShowCopSkinDialog(playerid);
			foreach(new i: Player)
			{
				if(IsPlayerCop(i)) continue;
				SetPlayerMarkerForPlayer( i, playerid, ( GetPlayerColor( playerid ) & 0xFFFFFF00 ) );
			}

		}
		case false:
		{
			if(!case_death) ResetPlayerWeapons(playerid);
			KillTimer(markerTimer[playerid]);
			SetPlayerColor(playerid, GetOriginalColor(playerid));
			if(!case_death) SetPlayerSkin(playerid, GetOriginalSkin(playerid));
			foreach(new i: Player)
			{
				SetPlayerMarkerForPlayer( i, playerid, ( GetPlayerColor( playerid ) & GetOriginalColor(playerid) ) );
			}
		}
	}
	return	playerDuty{playerid} = duty_case;
}

stock IsPlayerOnDuty(playerid)//Can't tag the function with bool: due to it being used before definition forcing reparse.
{
	return playerDuty{playerid};
}

stock ChangeCopStats(playerid, d_case)
{
	return (d_case == 1) ? MakePlayerCop(playerid) : RemovePlayerCop(playerid);
}

static MakePlayerCop(playerid)
{
	return SetPlayerJob(playerid, JOB_ID_COP);
}

static RemovePlayerCop(playerid)
{
	return SetPlayerJob(playerid, INVALID_JOB_ID);
}

stock bool:IsPlayerTazed(playerid)
{
	return playerTazed{playerid};
}

stock IsPlayerCop(playerid)//No tag cuz reparse 
{
	return (GetPlayerJob(playerid) == JOB_ID_COP);
}

stock SendRadioMessage(sender_id, message[])
{
	new sender_rank = GetPlayerRank(sender_id);

	new rank_name[20];
	GetRankNameFromID(sender_rank, rank_name, sizeof rank_name);

	new string[STRING_SIZE_LARGE*2];
	format(string, sizeof string, "[%s]%s: %s", rank_name, Player_TempName[sender_id], message);

	foreach(new i: Player)
	{
		if(!IsPlayerCop(i)) continue;
		SendRDZMessage(i, COP_RADIO_MESSAGE_COLOR, string, MESSAGE_CASE_EMPTY);

	}
	return 1;
}

stock ArrestPlayer(arresterID, arrestedID, exception = 0)
{
	if(arrestedID == arresterID) return 0;
	if(GetPlayerWantedLevel(arrestedID) == 0) return 0;
	if(IsPlayerInJail(arrestedID)) return 0;
	if(!IsPlayerTazed(arrestedID) && exception == 0) return 0;
	SetPlayerArrests(arresterID, GetPlayerArrests(arresterID) + 1);
	GivePlayerReps(arresterID, 1);
	SetPlayerRankByArrests(arresterID);
	return JailPlayer(arrestedID);
}

hook OnPlayerDisconnect(playerid, reason)
{
	KillTimer(markerTimer[playerid]);
	playerTazed{playerid} = false;
	playerDuty{playerid} = false;
	return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(weaponid == WEAPON_SILENCED)
	{
		if(IsPlayerCop(playerid))
		{
			if(IsPlayerConnected(hitid) && hittype == BULLET_HIT_TYPE_PLAYER)
			{
				if(GetPlayerWantedLevel(hitid) > 0)
				{
					if(!IsPlayerTazed(hitid))
					{
						playerTazed{hitid} = true;
						TogglePlayerControllable(hitid, false);
						GameTextForPlayer(hitid, "~r~TAZED!", 2500, 3);
						ApplyAnimation(hitid, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 0, 0, 1);
						SetTimerEx("untazePlayer", TAZE_TIME, false, "i", hitid);
					}
				}
			}
		}
	}
	if(hittype == BULLET_HIT_TYPE_PLAYER)
	{
		if(IsPlayerConnected(hitid))
		{
			if(IsPlayerCop(playerid) && IsPlayerCop(hitid) && !IsPlayerInEvent(playerid) && !IsPlayerInEvent(hitid)) return 0;
		}
	}
	return 1;
}

forward untazePlayer(playerid);
public untazePlayer(playerid)
{
	TogglePlayerControllable(playerid, true);
	ClearAnimations(playerid);
	return playerTazed{playerid} = false;
}

stock GetRankNameFromID(id, buf[], buf_size)
{
	new output[10 + 1];
	switch(id)
	{
		case CADET_RANK_ID:
		{
			output = "Cadet";
		}
		case OFFICER_RANK_ID:
		{
			output = "Officer";
		}
		case SERGEANT_RANK_ID:
		{
			output = "Sergeant";
		}
		case LIEUTENANT_RANK_ID:
		{
			output = "Lieutenant";
		}
		case CAPTAIN_RANK_ID:
		{
			output = "Captain";
		}
		case CHIEF_RANK_ID:
		{
			output = "Chief";
		}
	}
	return format(buf, buf_size, "%s", output);
}

CMD:spikes(playerid)
{
	if(!IsPlayerCop(playerid) || !IsPlayerOnDuty(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be a police officer!", MESSAGE_CASE_SERVER);
	new Float:x, Float:y, Float:z, Float:r;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, r);
	CreateStrip(x, y, z, r);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Spikes were set! Please make sure to delete them before leaving or getting off duty!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:delspikes(playerid)
{
	if(!IsPlayerCop(playerid) || !IsPlayerOnDuty(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be a police officer!", MESSAGE_CASE_SERVER);
	DeleteClosestStrip(playerid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "All nearby spikes were deleted!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:delallspikes(playerid)
{
	if(!IsPlayerCop(playerid) || !IsPlayerOnDuty(playerid) || GetPlayerRank(playerid) < CHIEF_RANK_ID) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be a police officer!", MESSAGE_CASE_SERVER);
	DeleteAllStrip();
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "All spikes were deleted!", MESSAGE_CASE_SERVER);
	return 1;
}

CMD:radio(playerid, params[])
{
	if(!IsPlayerCop(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be a police officer!", MESSAGE_CASE_SERVER);
	new message[STRING_SIZE_LARGE];
	if(sscanf(params, "s[128]", message))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to state the message!", MESSAGE_CASE_SERVER);
	}

	SendRadioMessage(playerid, message);
	return 1;
}
alias:radio("r");

CMD:arrest(playerid)
{
	if(!IsPlayerCop(playerid) || !IsPlayerOnDuty(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be a police officer!", MESSAGE_CASE_SERVER);
	new bool:arrest_happened;
	new bool:reset_arresthappened;
	new Float:x, Float:y, Float:z;
	new string[STRING_SIZE_LARGE];
	GetPlayerPos(playerid, x, y, z);
	foreach(new i: Player)
	{
		if(IsPlayerInRangeOfPoint(i, ARREST_RANGE, x, y, z))
		{
			if(ArrestPlayer(playerid, i))
			{
				SetPlayerArrested(i, GetPlayerArrested(i)+1);
				arrest_happened = true;
				reset_arresthappened = true;
				format(string, sizeof string, "Player %s was arrested by %s and sent to jail!", Player_TempName[i], Player_TempName[playerid]);
			}
		}
		if(reset_arresthappened)
			SendRDZMessage(i, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_COPS), reset_arresthappened = false;
	}
	if(arrest_happened)
	{
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've successfully arrested all of the nearby wanted players and gained reputation points!", MESSAGE_CASE_SERVER);
	}
	else SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "No wanted players around!", MESSAGE_CASE_JARVIS);
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(IsPlayerLoggedIn(playerid) && !IsPlayerInEvent(playerid))
    {
        if(killerid < MAX_PLAYERS && killerid >= 0 && killerid != INVALID_PLAYER_ID)
        {
            if(IsPlayerConnected(killerid) && IsPlayerLoggedIn(killerid) && !cmdKill{playerid}) 
            {
				if(IsPlayerCop(killerid))
				{
					if(GetPlayerWantedLevel(playerid) > 0)
					{
						if(IsPlayerOnDuty(killerid))
						{
							ArrestPlayer(killerid, playerid, 1);
							SetPlayerArrested(playerid, GetPlayerArrested(playerid)+1);
							SendRDZMessage(killerid, RDZ_OFFICIAL_COLOR, "You've successfully arrested the wanted player!", MESSAGE_CASE_SERVER);
							SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've been arrested and sent to jail!", MESSAGE_CASE_SERVER);
						}
					}
					else if(!IsPlayerSelfDefense(killerid))
					{
						new string[STRING_SIZE_LARGE];
						format(string, sizeof string, "Player %s has been removed from the RDZ PD due to killing an innocent civillian.", Player_TempName[killerid]);
						SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
						DisqualifyCop(killerid);
					}
				}
			}
		}
	}
	if(IsPlayerOnDuty(playerid))
		SetDutyStats(playerid, false, true);
	return 1;
}

#define HQ_RANGE 20.000
CMD:duty(playerid)
{
	if(IsPlayerInHQ(playerid, HQ_RANGE))
	{
		if(!IsPlayerCop(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be a police officer!", MESSAGE_CASE_SERVER);
		SetDutyStats(playerid, !playerDuty{playerid});
		new string[STRING_SIZE_LARGE];
		format(string, sizeof string, "Cop duty stats has been switched %s", (playerDuty{playerid}) ? "On" : "Off");
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
	}
	else return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Unable to, invalid position go to the HQ", MESSAGE_CASE_JARVIS);
	return 1;
}

forward removeMarker(playerid);
public removeMarker(playerid)
{
	foreach(new i: Player)
	{
		if(IsPlayerCop(i) || i == playerid) continue;
		SetPlayerMarkerForPlayer( i, playerid, ( GetPlayerColor( playerid ) & 0xFFFFFF00 ) );
	}
	return 1;
}

static IsPlayerInHQ(playerid, Float:range)
{
	if(IsPlayerInRangeOfPoint(playerid, range, 246.783996, 63.900199, 1003.640625) || IsPlayerInRangeOfPoint(playerid, range, 246.33, 111.07, 1003.22) || IsPlayerInRangeOfPoint(playerid, range, 288.745971, 169.350997, 1007.171875) || IsPlayerInRangeOfPoint(playerid, range, -500.9834, 286.2127, 2001.0950)) return 1;
	return 0;
}

stock IsCopVehicle(modelid)
{
	switch(modelid)
	{
		case 490, 528, 430, 476, 497, 596, 597, 598, 599, 523, 427: return 1;
	}
	return 0;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(IsCopVehicle(GetVehicleModel(vehicleid) ) )
		{
			if(IsPlayerCop(playerid))
			{
				if(!IsPlayerOnDuty(playerid)) RemovePlayerFromVehicle(playerid);
			}
			else if(GetPlayerWantedLevel(playerid) == 0)
			{ 
				SetPlayerWantedLevel(playerid, 1);
				SendPDReport(playerid, REPORT_TYPE_HIJACK, "Hijacking a police car");
				SetUserWanted(playerid, 1);
			}
		}
	}
	return 1;
}

stock SendPDReport(playerid, report_id, const report_name[])
{
	new string[STRING_SIZE_LARGE*2];
	format(string, sizeof string, "Heads up! Player %s has been reported for %s code %d, go get 'em!", Player_TempName[playerid], report_name, report_id);
	SetPlayerCrimes(playerid, GetPlayerCrimes(playerid)+1);
	GivePlayerReps(playerid, -1);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've lost -1 rep for doing a crime!", MESSAGE_CASE_SERVER);
	SetPlayerColor(playerid, RDZ_COLOR_WANTED);
	foreach(new i: Player)
	{
		if(IsPlayerCop(i))
		{
			SendRDZMessage(i, COP_RADIO_MESSAGE_COLOR, string, MESSAGE_CASE_COPS);
		}
	}
	return 1;
}

#define OFFICER_ARRESTS 50
#define SERGEANT_ARRESTS 150
#define LIEUTENANT_ARRESTS 250
#define CAPTAIN_ARRESTS 400
static SetPlayerRankByArrests(playerid)
{
	switch(GetPlayerArrests(playerid))
	{
		case OFFICER_ARRESTS:
		{
			SetPlayerRank(playerid, OFFICER_RANK_ID);
		}
		case SERGEANT_ARRESTS:
		{
			SetPlayerRank(playerid, SERGEANT_RANK_ID);
		}
		case LIEUTENANT_ARRESTS:
		{
			SetPlayerRank(playerid, LIEUTENANT_RANK_ID);
		}
		case CAPTAIN_ARRESTS:
		{
			SetPlayerRank(playerid, CAPTAIN_RANK_ID);
		}
	}
	return 1;
}

stock ShowCopSkinDialog(playerid)
{
	new string[sizeof(SKIN_LIST) *50];
	for (new i; i < sizeof(SKIN_LIST); i++)
	{
		format(string, sizeof string, "%s%i\n", string, SKIN_LIST[i][E_SKIN_LISTITEM_MODEL]);
	}
	Dialog_Show(playerid, DIALOG_COPSKINS, DIALOG_STYLE_PREVIEW_MODEL, "Cop Skins", string, "Choose", "Cancel");
	return 1;
}

stock DisqualifyCop(playerid)
{
	if(IsPlayerOnDuty(playerid))
	{
		SetDutyStats(playerid, false);
	}
	RemovePlayerCop(playerid);
	SetPlayerRank(playerid, CADET_RANK_ID);
	OnPlayerSpawnEx(playerid, CASE_REGISTER);
	return 1;
}