#include <YSI_Coding\y_hooks>//Credits to Y_Less
 
#define NT_DISTANCE 25.0 // Nametag render distance
 
new Text3D:cNametag[MAX_PLAYERS];
new cpnTimer[MAX_PLAYERS];

hook OnGameModeInit()
{
    ShowNameTags(0);
    // OnPlayerUpdate causes lag and OnPlayer(Take/Give)Damage doesn't work with it
    return 1;
}

static GetHealthDots(playerid)
{
    new
        dots[64], Float: HP;
 
    GetPlayerHealth(playerid, HP);
 
    if(HP >= 100)
        dots = "••••••••••";
    else if(HP >= 90)
        dots = "•••••••••{660000}•";
    else if(HP >= 80)
        dots = "••••••••{660000}••";
    else if(HP >= 70)
        dots = "•••••••{660000}•••";
    else if(HP >= 60)
        dots = "••••••{660000}••••";
    else if(HP >= 50)
        dots = "•••••{660000}•••••";
    else if(HP >= 40)
        dots = "••••{660000}••••••";
    else if(HP >= 30)
        dots = "•••{660000}•••••••";
    else if(HP >= 20)
        dots = "••{660000}••••••••";
    else if(HP >= 10)
        dots = "•{660000}•••••••••";
    else if(HP >= 0)
        dots = "{660000}••••••••••";
 
    return dots;
}

static GetArmorDots(playerid)
{
    new
        dots[64], Float: AR;
 
    GetPlayerArmour(playerid, AR);
 
    if(AR >= 100)
        dots = "••••••••••";
    else if(AR >= 90)
        dots = "•••••••••{666666}•";
    else if(AR >= 80)
        dots = "••••••••{666666}••";
    else if(AR >= 70)
        dots = "•••••••{666666}•••";
    else if(AR >= 60)
        dots = "••••••{666666}••••";
    else if(AR >= 50)
        dots = "•••••{666666}•••••";
    else if(AR >= 40)
        dots = "••••{666666}••••••";
    else if(AR >= 30)
        dots = "•••{666666}•••••••";
    else if(AR >= 20)
        dots = "••{666666}••••••••";
    else if(AR >= 10)
        dots = "•{666666}•••••••••";
    else if(AR >= 0)
        dots = "{666666}••••••••••";
 
    return dots;
}
 
hook OnPlayerConnect(playerid)
{
    cNametag[playerid] = CreateDynamic3DTextLabel("Loading nametag...", 0xFFFFFFFF, 0.0, 0.0, 0.1, NT_DISTANCE, .attachedplayer = playerid, .testlos = 1);
	cpnTimer[playerid] = SetTimerEx("UpdateNametag", 1000, true, "i", playerid); // So we're using a timer, change the interval to what you want
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsValidDynamic3DTextLabel(cNametag[playerid]))
	{
		DestroyDynamic3DTextLabel(cNametag[playerid]);
		cNametag[playerid] = Text3D:INVALID_3DTEXT_ID;
	}
	KillTimer(cpnTimer[playerid]);
    return 1;
}

forward UpdateNametag(playerid);
public UpdateNametag(playerid)
{
    new nametag[STRING_SIZE_LARGE*2], playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));
	if(!IsPlayerPaused(playerid))
	{
		format(nametag, sizeof(nametag), "{%06x}%s {FFFFFF}(%i)\n{FFFFFF}%s\n{FF0000}%s", GetPlayerColor(playerid) >>> 8, playername, playerid, GetArmorDots(playerid), GetHealthDots(playerid));
	}
	else
	{
		format(nametag, sizeof(nametag), "{%06x}%s {FFFFFF}(%i)\n{FFFFFF}%s\n{FF0000}%s\n{FF0000}||GAME PAUSED||", GetPlayerColor(playerid) >>> 8, playername, playerid, GetArmorDots(playerid), GetHealthDots(playerid));
	}
	UpdateDynamic3DTextLabelText(cNametag[playerid], 0xFFFFFFFF, nametag);
    return 1;
}