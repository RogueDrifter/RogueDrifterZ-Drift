
#if defined DriftBattle_included_
    #endinput
#endif

#define DriftBattle_included_

#define RIVAL_END_REASON_EXIT_VEHICLE 0
#define RIVAL_END_REASON_DISCONNECT 1
#define RIVAL_END_REASON_TIME 2

#define OUTDRIFT_RIVAL_VIRTUALWORLD 100
#define MAX_RIVAL_TEXTDRAWS 4
#define MAX_PLAYER_RIVAL_TEXTDRAWS 2

#define CASE_END 0
#define CASE_EMPTY 1

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static 
    OD_JustRequested[MAX_PLAYERS],
    bool:IsPlayerInOD[MAX_PLAYERS char],
    MyODRival[MAX_PLAYERS],
    ODRivalCounts[MAX_PLAYERS],
    Text:RIVAL_TD[MAX_RIVAL_TEXTDRAWS],
    PlayerText:RIVAL_PTD[MAX_PLAYERS][MAX_PLAYER_RIVAL_TEXTDRAWS],
    RIVAL_Timer[MAX_PLAYERS],
    RivalPoints[MAX_PLAYERS],
    RivalMinutes[MAX_PLAYERS],
    RivalSeconds[MAX_PLAYERS],
    RivalBet[MAX_PLAYERS];

CMD:outdrift(playerid, params[])
{
    new 
        Opponent, Bet;

    if(sscanf(params, "ri", Opponent, Bet))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Hi, please do consider that you need to mention both the opponent's ID and the bet placed.", MESSAGE_CASE_EMPTY);
    }

    if(!IsPlayerConnected(Opponent))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You do know that you can't outdrift a nonexisting player right?", MESSAGE_CASE_EMPTY);
    }

    new 
        Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    if(!IsPlayerInRangeOfPoint(Opponent, 15.0, x, y, z))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Get closer to that player you're too far.", MESSAGE_CASE_EMPTY);
    }

    if(GetPlayerMoney(playerid) < Bet)
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Check your money first before placing such a high bet...", MESSAGE_CASE_EMPTY);
    }

    if(GetPlayerMoney(Opponent) < Bet)
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "They're too poor for this big of a bet...", MESSAGE_CASE_EMPTY);
    }

    if(GetPlayerReps(playerid) < 1)
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to at least have 1 reputation ponit...", MESSAGE_CASE_EMPTY);
    }

    if(GetPlayerReps(Opponent) < 1)
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "They don't have enough reputation points...", MESSAGE_CASE_EMPTY);
    }

    if(Bet < 500 || Bet > 25000)
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "The bet can't go below 500 or above 25,000", MESSAGE_CASE_EMPTY);
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || GetPlayerState(Opponent) != PLAYER_STATE_DRIVER
    || !IsModelACar(GetVehicleModel(GetPlayerVehicleID(playerid))) || !IsModelACar(GetVehicleModel(GetPlayerVehicleID(playerid))))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Sorry bud but a drift battle can't happen without driving actual cars", MESSAGE_CASE_EMPTY);
    }
    
    if(Opponent == playerid)
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Really? why not trying picking someone else other than yourself...", MESSAGE_CASE_EMPTY);
    }

    if(IsPlayerInOD{playerid} || IsPlayerInOD{Opponent})
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Both players need to not be engaged in another drift battle.", MESSAGE_CASE_EMPTY);
    }

    if(OD_JustRequested[playerid]+60 > gettime())
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Take a rest before another battle...", MESSAGE_CASE_EMPTY);
    }

    OD_JustRequested[playerid] = gettime();
    IsPlayerInOD{playerid} = true;
    IsPlayerInOD{Opponent} = true;
    MyODRival[Opponent] = playerid;
    MyODRival[playerid] = Opponent;
    RivalBet[playerid] = Bet;
    RivalBet[Opponent] = Bet;
    TogglePlayerControllable(playerid, false);

    new 
        OD_String[280];

    format(OD_String, sizeof(OD_String), 
        "{205030}You're being challenged by {FFFFFF}%s {205030} for an outdrift rival, COST : {FFFFFF}%d${205030}, \n\n{CCCCCC}Click 'Yes' to accept or 'No' to decline.", 
        Player_TempName[playerid], Bet);

    Dialog_Show(Opponent, DIALOG_DRIFT_RIVAL, DIALOG_STYLE_MSGBOX, "Outdrift Rival Challenge", OD_String, "Yes", "No");
    SetTimerEx("OD_TakingTooLong", 10*1000, false, "iii", playerid, Opponent, CASE_EMPTY);
    return 1;
}
alias:outdrift("od", "driftrival", "driftbattle");

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(IsPlayerInOD{playerid})
    {
        OnOutdriftRivalEnd(playerid, MyODRival[playerid], RIVAL_END_REASON_EXIT_VEHICLE, RivalBet[playerid]);
    }
    return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    if(IsPlayerInOD{playerid})
    {
        SetVehicleVirtualWorld(vehicleid, NORMAL_VIRTUAL_WORLD);
        OnOutdriftRivalEnd(playerid, MyODRival[playerid], RIVAL_END_REASON_EXIT_VEHICLE, RivalBet[playerid]);
    }
    return 1;
}

hook OnGameModeInit() 
{
    RIVAL_TD[0] = TextDrawCreate(63.735778, 296.615112, "1st");
    TextDrawLetterSize(RIVAL_TD[0], 0.546665, 2.267848);
    TextDrawAlignment(RIVAL_TD[0], 1);
    TextDrawColor(RIVAL_TD[0], 255);
    TextDrawSetShadow(RIVAL_TD[0], 0);
    TextDrawSetOutline(RIVAL_TD[0], 1);
    TextDrawBackgroundColor(RIVAL_TD[0], 1521113650);
    TextDrawFont(RIVAL_TD[0], 2);
    TextDrawSetProportional(RIVAL_TD[0], 1);
    TextDrawSetShadow(RIVAL_TD[0], 0);

    RIVAL_TD[1] = TextDrawCreate(62.935821, 296.988922, "2nd");
    TextDrawLetterSize(RIVAL_TD[1], 0.575999, 2.211848);
    TextDrawAlignment(RIVAL_TD[1], 1);
    TextDrawColor(RIVAL_TD[1], 255);
    TextDrawSetShadow(RIVAL_TD[1], 0);
    TextDrawSetOutline(RIVAL_TD[1], 1);
    TextDrawBackgroundColor(RIVAL_TD[1], -13487566);
    TextDrawFont(RIVAL_TD[1], 2);
    TextDrawSetProportional(RIVAL_TD[1], 1);
    TextDrawSetShadow(RIVAL_TD[1], 0);

    RIVAL_TD[2] = TextDrawCreate(-46.566398, 298.000030, "----------------------------ssssssssssssssss");
    TextDrawLetterSize(RIVAL_TD[2], 0.165928, 0.052044);
    TextDrawAlignment(RIVAL_TD[2], 1);
    TextDrawColor(RIVAL_TD[2], -2139062017);
    TextDrawSetShadow(RIVAL_TD[2], 0);
    TextDrawSetOutline(RIVAL_TD[2], 1);
    TextDrawBackgroundColor(RIVAL_TD[2], -2139062017);
    TextDrawFont(RIVAL_TD[2], 2);
    TextDrawSetProportional(RIVAL_TD[2], 1);
    TextDrawSetShadow(RIVAL_TD[2], 0);

    RIVAL_TD[3] = TextDrawCreate(3.333039, 318.475128, "Rival_score:");
    TextDrawLetterSize(RIVAL_TD[3], 0.448830, 1.850967);
    TextDrawAlignment(RIVAL_TD[3], 1);
    TextDrawColor(RIVAL_TD[3], 255);
    TextDrawSetShadow(RIVAL_TD[3], 1);
    TextDrawSetOutline(RIVAL_TD[3], 1);
    TextDrawBackgroundColor(RIVAL_TD[3], -926365441);
    TextDrawFont(RIVAL_TD[3], 2);
    TextDrawSetProportional(RIVAL_TD[3], 1);
    TextDrawSetShadow(RIVAL_TD[3], 1);
    return 1;
}

hook OnGameModeExit()
{
    for(new x; x < MAX_RIVAL_TEXTDRAWS; x++)
    {
        TextDrawDestroy(RIVAL_TD[x]);
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    RIVAL_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 14.636219, 280.087890, "00:00");
    PlayerTextDrawLetterSize(playerid, RIVAL_PTD[playerid][0], 0.575999, 2.211848);
    PlayerTextDrawAlignment(playerid, RIVAL_PTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, RIVAL_PTD[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, RIVAL_PTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, RIVAL_PTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, RIVAL_PTD[playerid][0], -1263878631);
    PlayerTextDrawFont(playerid, RIVAL_PTD[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, RIVAL_PTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, RIVAL_PTD[playerid][0], 0);

    RIVAL_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 135.265853, 317.774322, "0");
    PlayerTextDrawLetterSize(playerid, RIVAL_PTD[playerid][1], 0.667333, 2.086580);
    PlayerTextDrawAlignment(playerid, RIVAL_PTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, RIVAL_PTD[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, RIVAL_PTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, RIVAL_PTD[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, RIVAL_PTD[playerid][1], -1061109505);
    PlayerTextDrawFont(playerid, RIVAL_PTD[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, RIVAL_PTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, RIVAL_PTD[playerid][1], 0);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    OD_JustRequested[playerid] = 0;

    if(IsPlayerInOD{playerid})
    {
        OnOutdriftRivalEnd(playerid, MyODRival[playerid], RIVAL_END_REASON_DISCONNECT, RivalBet[playerid]);
    }
    return 1;
}

Dialog:DIALOG_DRIFT_RIVAL(playerid, response, listitem, inputtext[])
{
    switch(response)
    {
        case true:
        {
            DisableRemoteVehicleCollisions(playerid, true);
            DisableRemoteVehicleCollisions(MyODRival[playerid], true);
            TogglePlayerControllable(playerid, false);
            ODRivalCounts[playerid] = 5;

            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Drifting rival is starting in 5 seconds...", MESSAGE_CASE_DRIFT);
            SendRDZMessage(MyODRival[playerid], RDZ_OFFICIAL_COLOR, "Drifting rival is starting in 5 seconds...", MESSAGE_CASE_DRIFT);
            
            RIVAL_Timer[playerid] = SetTimerEx("RivalsChecks", 1000, true, "ii", playerid, MyODRival[playerid]);
        }
        case false:
        {
            IsPlayerInOD{playerid} = false;
            IsPlayerInOD{ MyODRival[playerid] } = false;
            TogglePlayerControllable(MyODRival[playerid], true);
            SendRDZMessage(MyODRival[playerid], RDZ_OFFICIAL_COLOR, "The opponent has declined your rival offer.", MESSAGE_CASE_DRIFT);
        }
    }
    return 1;
}

public OnDialogPerformed(playerid, dialog[], response, success)
{
    if( (!IsPlayerConnected(MyODRival[playerid]) || GetPlayerState(MyODRival[playerid]) != PLAYER_STATE_DRIVER) && !strcmp(dialog, "DIALOG_DRIFT_RIVAL"))
    {
        OD_TakingTooLong(playerid, MyODRival[playerid], CASE_END);
        return 0;
    }
    return 1;
}

forward OD_TakingTooLong(playerid, rival_id, CASE_ID);
public OD_TakingTooLong(playerid, rival_id, CASE_ID)
{
    switch(CASE_ID)
    {
        case CASE_EMPTY:
        {
            if(Dialog_Opened(rival_id))
            {
                Dialog_Close(rival_id);
                
                IsPlayerInOD{playerid} = false;
                IsPlayerInOD{rival_id} = false;
                TogglePlayerControllable(playerid, true);
                SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "The opponent has taken too long to respond.", MESSAGE_CASE_DRIFT);
                SendRDZMessage(rival_id, RDZ_OFFICIAL_COLOR, "You have taken too long to respond.", MESSAGE_CASE_DRIFT);
            }
        }
        case CASE_END:
        {
            IsPlayerInOD{playerid} = false;
            IsPlayerInOD{rival_id} = false;
            TogglePlayerControllable(playerid, true);
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "The opponent has taken too long to respond.", MESSAGE_CASE_DRIFT);
            SendRDZMessage(rival_id, RDZ_OFFICIAL_COLOR, "You have taken too long to respond.", MESSAGE_CASE_DRIFT);
        }
    }
    return 1;
}

forward RivalsChecks(playerid, RivalID);
public RivalsChecks(playerid, RivalID)
{
    switch(ODRivalCounts[playerid])
    {
        case 1..5:
        {
            ODRivalCounts[playerid]--;
        }
        case 0:
        {
            UpdateRivalDrawings(playerid);
            UpdateRivalDrawings(RivalID);
            ODRivalCounts[playerid] = -1;

            SetPlayerVirtualWorld(playerid, OUTDRIFT_RIVAL_VIRTUALWORLD);
            SetPlayerVirtualWorld(RivalID, OUTDRIFT_RIVAL_VIRTUALWORLD);

            SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), OUTDRIFT_RIVAL_VIRTUALWORLD);
            SetVehicleVirtualWorld(GetPlayerVehicleID(RivalID), OUTDRIFT_RIVAL_VIRTUALWORLD);

            ShowRivalGlobalDrawings(playerid, true);
            ShowRivalGlobalDrawings(RivalID, true);
            ShowRivalPlayerDrawings(playerid, true);
            ShowRivalPlayerDrawings(RivalID, true);


            TextDrawHideForPlayer(playerid, RIVAL_TD[0]);
            TextDrawHideForPlayer(RivalID, RIVAL_TD[1]); 

            TextDrawHideForPlayer(playerid, RIVAL_TD[1]);
            TextDrawHideForPlayer(RivalID, RIVAL_TD[0]);   

            RivalMinutes[playerid] = 1;
            RivalSeconds[playerid] = 59;

            TogglePlayerControllable(RivalID, true);
            TogglePlayerControllable(playerid, true);
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Drifting rival has started, GO!", MESSAGE_CASE_DRIFT);
            SendRDZMessage(RivalID, RDZ_OFFICIAL_COLOR, "Drifting rival has started, GO!", MESSAGE_CASE_DRIFT);
        }
        case -1:
        {
            UpdateRivalTimer(playerid, RivalID);
            UpdateRivalRanking(playerid, RivalID);
        }
    }
    return 1;
}

forward OnPlayerDriftUpdateEx(playerid, Float: drift_angle, Float: speed);
public OnPlayerDriftUpdateEx(playerid, Float: drift_angle, Float: speed)
{
    if(IsPlayerInOD{playerid})
    {
        RivalPoints[playerid] += GetPlayerCurrentTotalDrift(playerid);
        UpdateRivalDrawings(playerid);
    }
    return 1;
}

forward OnPlayerDriftEndEx(playerid);
public OnPlayerDriftEndEx(playerid)
{
    if(IsPlayerInOD{playerid})
    {
        RivalPoints[playerid] += GetPlayerCurrentTotalDrift(playerid);
        UpdateRivalDrawings(playerid);
    }
    return 1;
}

forward OnOutdriftRivalEnd(playerid, rival_id, end_reason, rival_bet);
public OnOutdriftRivalEnd(playerid, rival_id, end_reason, rival_bet)
{
    new 
        Rival_EndString[STRING_SIZE_LARGE],
        winnerid,
        loserid;
    OnPlayerDriftEndEx(playerid);
    OnPlayerDriftEndEx(rival_id);

    switch(end_reason)
    {
        case RIVAL_END_REASON_DISCONNECT, RIVAL_END_REASON_EXIT_VEHICLE:
        {
            format(Rival_EndString, sizeof(Rival_EndString), "Listen up! %s scoring %d has won over %s scoring %d disqualified in an outdrift rival!", 
            Player_TempName[rival_id], RivalPoints[rival_id], Player_TempName[playerid], RivalPoints[playerid]);

            SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Rival_EndString, MESSAGE_CASE_DRIFT);
            winnerid = rival_id;
            loserid = playerid;
        }
        case RIVAL_END_REASON_TIME:
        {
            if(RivalPoints[playerid] > RivalPoints[rival_id])
            {
                format(Rival_EndString, sizeof(Rival_EndString), "Listen up! %s scoring %d has won over %s scoring %d in an outdrift rival!", 
                Player_TempName[playerid], RivalPoints[playerid], Player_TempName[rival_id], RivalPoints[rival_id]);

                winnerid = playerid;
                loserid = rival_id;
            }

            if(RivalPoints[rival_id] > RivalPoints[playerid])
            {
                format(Rival_EndString, sizeof(Rival_EndString), "Listen up! %s scoring %d has won over %s scoring %d in an outdrift rival!", 
                Player_TempName[rival_id], RivalPoints[rival_id], Player_TempName[playerid], RivalPoints[playerid]);

                winnerid = rival_id;
                loserid = playerid;
            }

            if(RivalPoints[playerid] == RivalPoints[rival_id])
            {
                format(Rival_EndString, sizeof(Rival_EndString), "Listen up rare event! %s is tied in an outdrift rival with %s on a score of %d", 
                Player_TempName[rival_id], Player_TempName[playerid], RivalPoints[playerid]);
                winnerid = -1;
                loserid = -1;
            }

            SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Rival_EndString, MESSAGE_CASE_DRIFT);

            if(winnerid != -1 || loserid == -1) 
            {
                GivePlayerReps(winnerid, 1);
                GivePlayerReps(loserid, -1);

                GivePlayerMoney(winnerid, rival_bet);
                GivePlayerMoney(loserid, -rival_bet);
            }
        }
    }

    if(RivalPoints[playerid] > GetPlayerBestRival(playerid))
    {
        SetPlayerBestDP(playerid, RivalPoints[playerid]);
    }

    if(RivalPoints[rival_id] > GetPlayerBestRival(rival_id))
    {
        SetPlayerBestDP(rival_id,  RivalPoints[rival_id]);
    }
    
    IncreaseODWon(winnerid, 1);
    IncreaseODLost(loserid, 1);
    
    ResetRival(playerid);
    ResetRival(rival_id);
    return 1;
}

stock IsPlayerInDriftRival(playerid)
    return (IsPlayerInOD{playerid});

static UpdateRivalRanking(playerid, otherid)
{
    if(RivalPoints[playerid] > RivalPoints[otherid])
    {
        TextDrawHideForPlayer(otherid, RIVAL_TD[0]);
        TextDrawHideForPlayer(playerid, RIVAL_TD[1]);  

        TextDrawShowForPlayer(playerid, RIVAL_TD[0]);
        TextDrawShowForPlayer(otherid, RIVAL_TD[1]);
    }

    else if(RivalPoints[otherid] > RivalPoints[playerid])
    {
        TextDrawHideForPlayer(playerid, RIVAL_TD[0]);
        TextDrawHideForPlayer(otherid, RIVAL_TD[1]);  

        TextDrawShowForPlayer(otherid, RIVAL_TD[0]);
        TextDrawShowForPlayer(playerid, RIVAL_TD[1]);
    }
    else if(RivalPoints[playerid] == RivalPoints[otherid])
    {
        TextDrawHideForPlayer(playerid, RIVAL_TD[0]);
        TextDrawHideForPlayer(otherid, RIVAL_TD[1]); 

        TextDrawHideForPlayer(playerid, RIVAL_TD[1]);
        TextDrawHideForPlayer(otherid, RIVAL_TD[0]);   
    }
    return 1;
}

static UpdateRivalTimer(playerid, otherid)
{
    new 
        Rival_String[STRING_SIZE_MEDIUM];
    
    if(RivalSeconds[playerid] > 0)
    {
        RivalSeconds[playerid]--;
    }
    else if(RivalSeconds[playerid] == 0)
    {
        if(RivalMinutes[playerid] != 0) RivalMinutes[playerid]--,
        RivalSeconds[playerid] = 59;

        else OnOutdriftRivalEnd(playerid, otherid, RIVAL_END_REASON_TIME, RivalBet[otherid]);
    }

    if(RivalSeconds[playerid] >= 10)
    {
        format(Rival_String, sizeof(Rival_String), "0%d:%d", RivalMinutes[playerid], RivalSeconds[playerid]);
    }
    else if(RivalSeconds[playerid] < 10)
    {
        format(Rival_String, sizeof(Rival_String), "0%d:0%d", RivalMinutes[playerid], RivalSeconds[playerid]);
    }

    PlayerTextDrawSetString(playerid, RIVAL_PTD[playerid][0], Rival_String);
    PlayerTextDrawSetString(otherid, RIVAL_PTD[playerid][0], Rival_String);
    return 1;
}

static ShowRivalGlobalDrawings(playerid, bool:toggle)
{
    switch(toggle)
    {
        case true:
        {
            for(new x; x < MAX_RIVAL_TEXTDRAWS; x++)
            {
                TextDrawShowForPlayer(playerid, RIVAL_TD[x]);
            }
        }
        case false:
        {
            for(new x; x < MAX_RIVAL_TEXTDRAWS; x++)
            {
                TextDrawHideForPlayer(playerid, RIVAL_TD[x]);
            }
        }
    }
    return 1;
}

static ShowRivalPlayerDrawings(playerid, bool:toggle)
{
    switch(toggle)
    {
        case true:
        {
            for(new x; x < MAX_PLAYER_RIVAL_TEXTDRAWS; x++)
            {
                PlayerTextDrawShow(playerid, RIVAL_PTD[playerid][x]);
            }
        }
        case false:
        {
            for(new x; x < MAX_PLAYER_RIVAL_TEXTDRAWS; x++)
            {
                PlayerTextDrawHide(playerid, RIVAL_PTD[playerid][x]);
            }
        }
    }
    return 1;
}

static ResetRival(playerid)
{
    IsPlayerInOD{playerid} = false;
    ODRivalCounts[playerid] = 0;
    RivalPoints[playerid] = 0;
    RivalBet[playerid] = 0;
    MyODRival[playerid] = 0;
    ShowRivalGlobalDrawings(playerid, false);
    ShowRivalPlayerDrawings(playerid, false);
    DisableRemoteVehicleCollisions(playerid, false);
    SetPlayerVirtualWorld(playerid, 0);
    SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), 0);

    KillTimer(RIVAL_Timer[playerid]);
    return 1;
}

static UpdateRivalDrawings(playerid)
{
    new 
        Update_String[STRING_SIZE_SMALL];

    format(Update_String, sizeof(Update_String), "%d", RivalPoints[playerid]);
    PlayerTextDrawSetString(playerid, RIVAL_PTD[playerid][1], Update_String);
    return 1;
}
