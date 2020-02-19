
#if defined RDZ_ReservedSys_Included_
   #endinput
#endif

#define RDZ_ReservedSys_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static Owner_Process[MAX_PLAYERS][MAX_PLAYER_NAME];

#define DEFAULT_ROTATION 0.0

CMD:createhouse(playerid, params[])
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

    new target_name[MAX_PLAYER_NAME];

    if(sscanf(params, "s[24]", target_name))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to mention the player's name", MESSAGE_CASE_SERVER);
	}

    if(!IsPlayerRegistered(target_name))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to mention a registered player!", MESSAGE_CASE_SERVER);
    }

    if(IsPlayerAlreadyOwner(target_name))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player already has a house!", MESSAGE_CASE_SERVER);
    }
    format(Owner_Process[playerid], MAX_PLAYER_NAME, "%s", target_name);

    Dialog_Show(playerid, DIALOG_ENTRY_HOUSES, DIALOG_STYLE_TABLIST, "RogueDrifterZ houses",
    "House 1\tInterior 3\tLarge/2 story/3 bedrooms\n\
    House 2\tInterior 2\tMedium/1 story/1 bedroom\n\
    House 3\tInterior 1\tSmall/1 story/1 bedroom,\n\
    House 4\tInterior 5\tThe large mansion you get at the end of LV Storyline Section,\n\
    House 5\tInterior 2\tBig Smoke's Crack Palace, 	Crack Laboratory.",
    "Choose", "Cancel");

    return 1;
}


Dialog:DIALOG_ENTRY_HOUSES(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, DIALOG_HOUSE_ONE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ houses", "{FFFFFF}You've picked house #1, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 1:
            {
                Dialog_Show(playerid, DIALOG_HOUSE_TWO, DIALOG_STYLE_MSGBOX, "RogueDrifterZ houses", "{FFFFFF}You've picked house #2, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 2:
            {
                Dialog_Show(playerid, DIALOG_HOUSE_THREE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ houses", "{FFFFFF}You've picked house #3, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 3:
            {
                Dialog_Show(playerid, DIALOG_HOUSE_FOUR, DIALOG_STYLE_MSGBOX, "RogueDrifterZ houses", "{FFFFFF}You've picked house #4, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 4:
            {
                Dialog_Show(playerid, DIALOG_HOUSE_FIVE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ houses", "{FFFFFF}You've picked house #5, please make sure you got the right one!", "Accept", "Cancel");
            }
        }
	}
	return 1;
}

Dialog:DIALOG_HOUSE_ONE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddHouse(Owner_Process[playerid], x, y, z, r, 235.508994, 1189.169897, 1080.339966, DEFAULT_ROTATION, 3, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "House was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_HOUSE_TWO(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddHouse(Owner_Process[playerid], x, y, z, r, 225.756989, 1240.000000, 1082.149902, DEFAULT_ROTATION, 2, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "House was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_HOUSE_THREE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddHouse(Owner_Process[playerid], x, y, z, r, 223.043991, 1289.259888, 1082.199951, DEFAULT_ROTATION, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "House was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_HOUSE_FOUR(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddHouse(Owner_Process[playerid], x, y, z, r, 1299.14, -794.77, 1084.00, DEFAULT_ROTATION, 5, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "House was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}


Dialog:DIALOG_HOUSE_FIVE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddHouse(Owner_Process[playerid], x, y, z, r, 2541.6536, -1304.0980, 1025.0703, DEFAULT_ROTATION, 2, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "House was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

CMD:house(playerid)
{
    if(!IsPlayerAlreadyOwner(Player_TempName[playerid]))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have a house!", MESSAGE_CASE_SERVER);
    }

    if(GetPlayerInterior(playerid) != 0 || GetPlayerWantedLevel(playerid) > 0 || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || IsPlayerOnDuty(playerid) || IsInCity(playerid))
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Improper state for teleporting to your house!", MESSAGE_CASE_SERVER);
    
    ReservedTeleport(playerid);
    return 1;
}
alias:house("home");