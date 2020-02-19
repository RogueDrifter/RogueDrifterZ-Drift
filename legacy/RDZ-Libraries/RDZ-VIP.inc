#if defined VIP_SYS_Included_
   #endinput
#endif

#define VIP_SYS_Included_
#define VIP_LEVEL_ONE 1
#define VIP_LEVEL_TWO 2
#define VIP_LEVEL_THREE 3

#include <YSI_Coding\y_hooks>//Credits to Y_Less

hook OnPlayerSpawn(playerid)
{
   switch(GetPlayerVIP(playerid))
   {
      case VIP_LEVEL_ONE:
      {
         SetPlayerArmour(playerid, 30.00);
      }
      case VIP_LEVEL_TWO:
      {
         SetPlayerArmour(playerid, 60.00);
      }
      case VIP_LEVEL_THREE:
      {
         SetPlayerArmour(playerid, 100.00);
      }
   }
   return 1;
}

CMD:savehome(playerid)
{
	if(GetPlayerVIP(playerid) < VIP_LEVEL_TWO || GetPlayerWantedLevel(playerid) > 0 || GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0 || IsPlayerOnDuty(playerid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're not authorized to use this command!", MESSAGE_CASE_VIP);
	}
	
	UpdateVIPSaves(playerid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've updated your house coordinates!", MESSAGE_CASE_VIP);
	return 1;
}
alias:savehome("sh", "sethome");

CMD:gohome(playerid)
{
	if(GetPlayerVIP(playerid) < VIP_LEVEL_TWO || GetPlayerWantedLevel(playerid) > 0 || GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0 || IsPlayerOnDuty(playerid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're not authorized to use this command!", MESSAGE_CASE_VIP);
	}
	
	TeleportVIPSaves(playerid);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've teleported to your house coordinates!", MESSAGE_CASE_VIP);
	return 1;
}
alias:gohome("mh", "myhome");

CMD:makevip(playerid, params[])//Second rcon admin
{
	new 
        targetid,
		level;
	
	if(!IsPlayerRconAdmin(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're not authorized to use this command!", MESSAGE_CASE_ADMIN);

	if(sscanf(params, "ri", targetid, level))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Specify the target id or name with the admin level afterwards", MESSAGE_CASE_ADMIN);
    }

	if(level > 3 || level < 0 ) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Level can't go above 7 or below 1", MESSAGE_CASE_ADMIN);

	if(!IsPlayerConnected(targetid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_VIP);

	SetPlayerVIP(targetid, level);

	new vip_string[STRING_SIZE_LARGE];
	format(vip_string, sizeof vip_string, "Jarvis[BOT]: Admin %s has set player %s vip, level: %d", Player_TempName[playerid], Player_TempName[targetid], level);
	SendMessageToAdmins(vip_string);
	return 1;
}

stock SendMessageToVIPs(playerid, message[])
{
	message[0] = ' ';
	foreach(new i: Player)
	{
		if(!IsPlayerVIP(i)) continue;

		SendRDZMessage(i, RDZ_OOC_CHAT_COLOR, message, MESSAGE_CASE_VIPSCHAT, playerid);
	}
	return 1;
}