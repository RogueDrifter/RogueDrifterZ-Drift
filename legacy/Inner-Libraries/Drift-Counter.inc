
#if defined DriftCounter_included_
    #endinput
#endif

#define DriftCounter_included_
#define DRIFT_MAX_TEXTDRAWS 4
#define DRIFT_GIFT_BONUS 100
#define MAX_DRIFT_SMOKE 2

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static 
    TotalDriftingScore[MAX_PLAYERS],
    TotalDriftingCombo[MAX_PLAYERS],
    TotalDriftTimer[MAX_PLAYERS],
    TotalDriftCashCount[MAX_PLAYERS];

static  
    Text:RDZ_DriftTD[DRIFT_MAX_TEXTDRAWS], 
    PlayerText:RDZ_DriftPTD[MAX_PLAYERS][DRIFT_MAX_TEXTDRAWS],
    Text3D:RDZ_TextLabelCounter[MAX_VEHICLES],
    bool:TOGGLE_SMOKE[MAX_PLAYERS char];

static 
    Wheels_Smoke[MAX_VEHICLES][MAX_DRIFT_SMOKE],
    emptyVeh;

static DriftDrawingsFadeNormal(playerid)
{
    HideGlobalDriftDrawings(playerid);
    for(new x; x < DRIFT_MAX_TEXTDRAWS - 1; x++)
    {
        PlayerTextDrawHide(playerid, RDZ_DriftPTD[playerid][x]);
    }
    return 1;
}

static DriftDrawingsFadeToRed(playerid)
{
    HideGlobalDriftDrawings(playerid);
    for(new x; x < DRIFT_MAX_TEXTDRAWS - 1; x++)
    {
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][x], -13487566);
    }

    DriftDrawingsFadeNormal(playerid);

    ShowDriftingTextdraws(playerid);
    HideGlobalDriftDrawings(playerid);

    TotalDriftTimer[playerid] = SetTimerEx("FadeDriftDrawingRed", 2000, false, "i", playerid);
    return 1;
}

static CreateDriftSmoke(playerid)
{   
    new player_vid = GetPlayerVehicleID(playerid);

    DestroyDriftSmoke(player_vid);

    Wheels_Smoke[player_vid][0] = CreateDynamicObject( 18671, 197.1859, 378.6902, 90.7009, 0.0, 0.0, 0.0);
    Wheels_Smoke[player_vid][1] = CreateDynamicObject( 18671, 197.1859, 378.6902, 90.7009, 0.0, 0.0, 0.0);

    AttachDynamicObjectToVehicle( Wheels_Smoke[player_vid][0], player_vid, -0.899999, -1.400000, -2.2, 0.000000, 0.000000, 0.000000 );
    AttachDynamicObjectToVehicle( Wheels_Smoke[player_vid][1], player_vid, 0.900000, -1.500000, -2.2, 0.000000, 0.000000, 0.000000 );

    return 1;
}

static DestroyDriftSmoke(vehicleid)
{
    if(Wheels_Smoke[vehicleid][0] != INVALID_OBJECT_ID) DestroyDynamicObject(Wheels_Smoke[vehicleid][0]);
    if(Wheels_Smoke[vehicleid][1] != INVALID_OBJECT_ID) DestroyDynamicObject(Wheels_Smoke[vehicleid][1]);

    Wheels_Smoke[vehicleid][0] = INVALID_OBJECT_ID;
    Wheels_Smoke[vehicleid][1] = INVALID_OBJECT_ID;
    return 1;
}

public OnPlayerPause(playerid, time_in_seconds)
{
    DestroyDriftSmoke(GetPlayerVehicleID(playerid));
    return 1;
}

static ShowDriftingTextdraws(playerid)
{
    for(new x; x < DRIFT_MAX_TEXTDRAWS; x++)
    {
        TextDrawShowForPlayer(playerid, RDZ_DriftTD[x]);
        if(x < 3) PlayerTextDrawShow(playerid, RDZ_DriftPTD[playerid][x]);
    }
    return 1;
}

static HideGlobalDriftDrawings(playerid)
{
    for(new x; x < DRIFT_MAX_TEXTDRAWS; x++)
    {
        TextDrawHideForPlayer(playerid, RDZ_DriftTD[x]);
    }
    return 1;
}

static CreateDriftLabel(playerid, vehicleid)
{
    new string[80];
    format(string, sizeof string, "%dX%d", TotalDriftingScore[playerid], TotalDriftingCombo[playerid]);

    RDZ_TextLabelCounter[vehicleid] = Create3DTextLabel(string, 0x11FF11FF, 0.0, 0.0, 0.0, 8.0, 0, 0);
    Attach3DTextLabelToVehicle( RDZ_TextLabelCounter[vehicleid], vehicleid, -0.499999, 0.0999999, 0.899999);
    return 1;
}

static DestroyDriftLabel(vehicleid)
{
    Delete3DTextLabel(RDZ_TextLabelCounter[vehicleid]);
    RDZ_TextLabelCounter[vehicleid] = Text3D:INVALID_3DTEXT_ID;
    return 1;
}

static UpdateDriftLabel(vehicleid, score, combo)
{
    new string[80];
    format(string, sizeof string, "%dX%d", score, combo);

    switch(combo)
    {
        case 0:
        {
            Update3DTextLabelText(  RDZ_TextLabelCounter[vehicleid], 0x5095FFFF, string);
        }
        case 1:
        {
            Update3DTextLabelText(  RDZ_TextLabelCounter[vehicleid], 0x11FF11FF, string);
        }
        case 2:
        {
            Update3DTextLabelText(  RDZ_TextLabelCounter[vehicleid], 0x789526FF, string);
        }
        case 3:
        {
            Update3DTextLabelText(  RDZ_TextLabelCounter[vehicleid], 0x328799FF, string);
        }
        case 4:
        {
            Update3DTextLabelText(  RDZ_TextLabelCounter[vehicleid], 0x63FCFFFF, string);
        }
        case 5:
        {
            Update3DTextLabelText(  RDZ_TextLabelCounter[vehicleid], 0x851765FF, string);
        }
    }
    return 1;
}

static UpdateChangingTextdraw(playerid)
{
    new 
        Update_String[30];

    format(Update_String, sizeof(Update_String), "%d", TotalDriftingScore[playerid]);
    PlayerTextDrawSetString(playerid, RDZ_DriftPTD[playerid][0], Update_String);

    format(Update_String, sizeof(Update_String), "X%d", TotalDriftingCombo[playerid]);
    PlayerTextDrawSetString(playerid, RDZ_DriftPTD[playerid][1], Update_String);

    format(Update_String, sizeof(Update_String), "$%d", TotalDriftCashCount[playerid]);
    PlayerTextDrawSetString(playerid, RDZ_DriftPTD[playerid][2], Update_String);
    return 1;
}

forward FadeDriftDrawingRed(playerid);
public FadeDriftDrawingRed(playerid)
{
    return DriftDrawingsFadeNormal(playerid);
}

public OnPlayerDriftStart(playerid)
{
    #if defined CHRISTMAS_MOD
        if(IsSnowManOn(playerid)) HideLogo(playerid, true);
        if(IsSnowOn(playerid)) DeleteSnow(playerid, true);
    #endif
    
    HideGeneralTDsForPlayer(playerid);
    HideMiscTDsForPlayer(playerid);
    KillTimer(TotalDriftTimer[playerid]);

    PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], 1118441471);
    PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], 1118441471);
    PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], 1118441471);

    TotalDriftingCombo[playerid] = 0;
    TotalDriftCashCount[playerid] = 0;
    TotalDriftingScore[playerid] = 0;
    

    if(!TOGGLE_SMOKE{playerid}) CreateDriftSmoke(playerid);
    CreateDriftLabel(playerid, GetPlayerVehicleID(playerid));
    return 1;
}

public OnPlayerDriftUpdate(playerid, Float: drift_angle, Float: speed)
{
    if( (floatround(floatabs(floatsub(drift_angle, 3.0)) * 4 * (speed * 0.1)) / 10) + TotalDriftingScore[playerid] < 6000 )
    TotalDriftingScore[playerid] += floatround(floatabs(floatsub(drift_angle, 3.0)) * 4 * (speed * 0.1)) / 10;
    else
    {     
        GivePlayerDP(playerid,  TotalDriftingScore[playerid] * TotalDriftingCombo[playerid]);
        OnPlayerDriftUpdateEx(playerid, drift_angle, speed);

        GivePlayerMoney(playerid, TotalDriftCashCount[playerid]);

        TotalDriftingCombo[playerid] = 0;
        TotalDriftCashCount[playerid] = 0;
        TotalDriftingScore[playerid] = 0;
        SetPlayerScore(playerid, GetPlayerDriftScore(playerid));
    }
    
    if(1001 > TotalDriftingScore[playerid] > 0 )
    {   
        TotalDriftingCombo[playerid] = 0;

        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], -926365441); //1118441471
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], -926365441);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], -926365441);

    }
    else if(2001 > TotalDriftingScore[playerid] > 1000 )
    {
        TotalDriftingCombo[playerid] = 1;

        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], -1062596699);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], -1062596699);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], -1062596699);

    }
    else if( 3001 > TotalDriftingScore[playerid] > 2000)
    {
        TotalDriftingCombo[playerid] = 2;

        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], 1118441471);//-1230323291
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], 1118441471);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], 1118441471);

    }
    else if( 4001 > TotalDriftingScore[playerid] > 3000)
    {
        TotalDriftingCombo[playerid] = 3;

        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], -106259669);//-7300865
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], -106259669);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], -106259669);

    }
    else if( 5001 > TotalDriftingScore[playerid] > 4000)
    {
        TotalDriftingCombo[playerid] = 4;

        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], -262506241);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], -262506241);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], -262506241);

    }

    else if( 6001 > TotalDriftingScore[playerid] > 5000)
    {
        TotalDriftingCombo[playerid] = 5;

        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], -1768516046);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], -1768516046);
        PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], -1768516046);

    }

    TotalDriftCashCount[playerid] += TotalDriftingCombo[playerid];

    UpdateChangingTextdraw(playerid);

    DriftDrawingsFadeNormal(playerid);
    HideGlobalDriftDrawings(playerid);

    ShowDriftingTextdraws(playerid);
    UpdateDriftLabel(GetPlayerVehicleID(playerid), TotalDriftingScore[playerid], TotalDriftingCombo[playerid]);
    return 1;
}

forward deleteAddons();
public deleteAddons()
{
    foreach(new i: Vehicle)
    {
        if(IsVehicleEmpty(i))
        {
            DestroyDriftLabel(i);
            DestroyDriftSmoke(i);
        }
    }
    return 1;
}

public OnPlayerDriftEnd(playerid, reason, Float: distance, time)
{
    #if defined CHRISTMAS_MOD
        if(IsSnowManOn(playerid)) ShowLogo(playerid);
        if(IsSnowOn(playerid)) CreateSnow(playerid, true);
    #endif

    ShowGeneralTDsForPlayer(playerid);
    ShowMiscTDsForPlayer(playerid);
    switch(reason)
    {
        case DRIFT_END_REASON_TIMEOUT:
        {
            if(TotalDriftingCombo[playerid] != 0) GivePlayerDP(playerid, TotalDriftingScore[playerid] * TotalDriftingCombo[playerid]);
            else GivePlayerDP(playerid, TotalDriftingScore[playerid]);
            
            OnPlayerDriftEndEx(playerid);

            GivePlayerMoney(playerid, TotalDriftCashCount[playerid]);
            TotalDriftingScore[playerid] = 0;
            TotalDriftCashCount[playerid] = 0;
            TotalDriftingCombo[playerid] = 0;
            SetPlayerScore(playerid, GetPlayerDriftScore(playerid));
            HideGlobalDriftDrawings(playerid);
            DriftDrawingsFadeNormal(playerid);
        }
        case DRIFT_END_REASON_OTHER:
        {
            TotalDriftingScore[playerid] = 0;
            TotalDriftCashCount[playerid] = 0;
            TotalDriftingCombo[playerid] = 0;
            HideGlobalDriftDrawings(playerid);
            DriftDrawingsFadeNormal(playerid);
        }
        case DRIFT_END_REASON_DAMAGED:
        {
            TotalDriftingScore[playerid] = 0;
            TotalDriftCashCount[playerid] = 0;
            TotalDriftingCombo[playerid] = 0;
            HideGlobalDriftDrawings(playerid);
            DriftDrawingsFadeToRed(playerid);
        }
    }

    new vehicleid = GetPlayerVehicleID(playerid);

    UpdateChangingTextdraw(playerid);
    UpdateDriftLabel(GetPlayerVehicleID(playerid), TotalDriftingScore[playerid], TotalDriftingCombo[playerid]);
    DestroyDriftSmoke(vehicleid);
    DestroyDriftLabel(vehicleid);
    return 1;
}

hook OnGameModeInit()
{
    Drift::EnableDetection();
    Drift::EnableDamageCheck();

    RDZ_DriftTD[0] = TextDrawCreate(563.332946, 323.701812, "SCORE");
    TextDrawLetterSize(RDZ_DriftTD[0], 0.448830, 1.850967);
    TextDrawAlignment(RDZ_DriftTD[0], 1);
    TextDrawColor(RDZ_DriftTD[0], 255);
    TextDrawSetShadow(RDZ_DriftTD[0], 1);
    TextDrawSetOutline(RDZ_DriftTD[0], 1);
    TextDrawBackgroundColor(RDZ_DriftTD[0], -926365441);
    TextDrawFont(RDZ_DriftTD[0], 2);
    TextDrawSetProportional(RDZ_DriftTD[0], 1);
    TextDrawSetShadow(RDZ_DriftTD[0], 1);

    RDZ_DriftTD[1] = TextDrawCreate(565.567199, 372.184051, "Cash");
    TextDrawLetterSize(RDZ_DriftTD[1], 0.486999, 1.712000);
    TextDrawAlignment(RDZ_DriftTD[1], 1);
    TextDrawColor(RDZ_DriftTD[1], 255);
    TextDrawSetShadow(RDZ_DriftTD[1], 0);
    TextDrawSetOutline(RDZ_DriftTD[1], 1);
    TextDrawBackgroundColor(RDZ_DriftTD[1], -926365441);
    TextDrawFont(RDZ_DriftTD[1], 2);
    TextDrawSetProportional(RDZ_DriftTD[1], 1);
    TextDrawSetShadow(RDZ_DriftTD[1], 0);

    RDZ_DriftTD[2] = TextDrawCreate(545.500000, 338.288970, "_-----------");//Over score
    TextDrawLetterSize(RDZ_DriftTD[2], 0.483999, 0.175108);
    TextDrawAlignment(RDZ_DriftTD[2], 1);
    TextDrawColor(RDZ_DriftTD[2], -926365441);
    TextDrawSetShadow(RDZ_DriftTD[2], 0);
    TextDrawSetOutline(RDZ_DriftTD[2], 1);
    TextDrawBackgroundColor(RDZ_DriftTD[2], -926365441);
    TextDrawFont(RDZ_DriftTD[2], 1);
    TextDrawSetProportional(RDZ_DriftTD[2], 1);
    TextDrawSetShadow(RDZ_DriftTD[2], 0);

    RDZ_DriftTD[3] = TextDrawCreate(546.000000, 386.000122, "_-----------");//Over cash
    TextDrawLetterSize(RDZ_DriftTD[3], 0.483999, 0.175108);
    TextDrawAlignment(RDZ_DriftTD[3], 1);
    TextDrawColor(RDZ_DriftTD[3], -926365441);
    TextDrawSetShadow(RDZ_DriftTD[3], 0);
    TextDrawSetOutline(RDZ_DriftTD[3], 1);
    TextDrawBackgroundColor(RDZ_DriftTD[3], -926365441);
    TextDrawFont(RDZ_DriftTD[3], 1);
    TextDrawSetProportional(RDZ_DriftTD[3], 1);
    TextDrawSetShadow(RDZ_DriftTD[3], 0);

    emptyVeh = SetTimer("deleteAddons", 5000, true);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    Drift::EnableDetection(playerid);
    Drift::EnableDamageCheck(playerid);

    RDZ_DriftPTD[playerid][0] = CreatePlayerTextDraw(playerid, 560.565917, 337.180938, "0");//Drift score
    PlayerTextDrawLetterSize(playerid, RDZ_DriftPTD[playerid][0], 0.667333, 2.086580);
    PlayerTextDrawAlignment(playerid, RDZ_DriftPTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, RDZ_DriftPTD[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, RDZ_DriftPTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, RDZ_DriftPTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][0], -974061569);
    PlayerTextDrawFont(playerid, RDZ_DriftPTD[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, RDZ_DriftPTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, RDZ_DriftPTD[playerid][0], 0);

    RDZ_DriftPTD[playerid][1] = CreatePlayerTextDraw(playerid, 578.333312, 353.215209, "X1");//Drift combo
    PlayerTextDrawLetterSize(playerid, RDZ_DriftPTD[playerid][1], 0.546665, 2.267848);
    PlayerTextDrawAlignment(playerid, RDZ_DriftPTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, RDZ_DriftPTD[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, RDZ_DriftPTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, RDZ_DriftPTD[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][1], -262506241);
    PlayerTextDrawFont(playerid, RDZ_DriftPTD[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, RDZ_DriftPTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, RDZ_DriftPTD[playerid][1], 0);

    RDZ_DriftPTD[playerid][2] = CreatePlayerTextDraw(playerid, 568.099975, 386.871093, "$1");//Drift cash
    PlayerTextDrawLetterSize(playerid, RDZ_DriftPTD[playerid][2], 0.460000, 1.928532);
    PlayerTextDrawAlignment(playerid, RDZ_DriftPTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, RDZ_DriftPTD[playerid][2], 255);
    PlayerTextDrawSetShadow(playerid, RDZ_DriftPTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, RDZ_DriftPTD[playerid][2], 1);
    PlayerTextDrawBackgroundColor(playerid, RDZ_DriftPTD[playerid][2], 1557292031);
    PlayerTextDrawFont(playerid, RDZ_DriftPTD[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, RDZ_DriftPTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, RDZ_DriftPTD[playerid][2], 0);

    return 1;
}

hook OnGameModeExit()
{
    KillTimer(emptyVeh);
    for(new x; x < DRIFT_MAX_TEXTDRAWS; x++)
    {
        TextDrawDestroy(RDZ_DriftTD[x]);
    }
    return 1;
}

stock GetPlayerCurrentDriftScore(playerid)
    return TotalDriftingScore[playerid];

stock GetPlayerCurrentDriftCombo(playerid)
    return TotalDriftingCombo[playerid];

stock GetPlayerCurrentTotalDrift(playerid)
    return TotalDriftingScore[playerid] * TotalDriftingCombo[playerid];

CMD:togsmoke(playerid)
{
    TOGGLE_SMOKE{playerid} = !TOGGLE_SMOKE{playerid};
    new string[STRING_SIZE_LARGE];
    format(string, sizeof string, "Drifting smoke turned %s!", (TOGGLE_SMOKE{playerid}) ? "off" : "on");
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    TOGGLE_SMOKE{playerid} = false;
    return 1;
}