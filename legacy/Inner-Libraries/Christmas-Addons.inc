
#if defined ChristmasAddons_included_
    #endinput
#endif

#define ChristmasAddons_included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define MAX_SNOW_OBJECTS    8
#define UPDATE_INTERVAL     1000
#define MAX_TEXTDRAW_SNOWMAN 20
#define MAX_TREE_SPACES 30
#define MAX_TREE_OBJECTS 10
#define TREE_LABEL_DD 50.000

forward LoadTextdraws();
forward AddMouthOptions();
forward AddEyesOptions();
forward DestroyTextdraws();
forward UpdateSnow(playerid);

static bool:snowOn[MAX_PLAYERS char], 
        snowObject[MAX_PLAYERS][MAX_SNOW_OBJECTS], 
        updateTimer[MAX_PLAYERS char],
        bool:snowMan[MAX_PLAYERS char],
        Text:SnowmanTextdraw[MAX_TEXTDRAW_SNOWMAN],
        treeObjects[MAX_TREE_OBJECTS][MAX_TREE_SPACES],
        bool:areTreesIDsShown,
        Text3D:s_treeLabel[MAX_TREE_SPACES];

static ExtractObjectModelFromID(id)
{
    new modelid;

    switch(id)
    {
        case 0: modelid = 19076;
        case 1, 8: modelid = 19054;
        case 2, 5: modelid = 19058;
        case 3: modelid = 19056;
        case 4, 7: modelid = 19057;
        case 6: modelid = 19055;
        case 9: modelid = 3526;
    }
    return modelid;
}

hook OnGameModeInit()
{
    LoadTextdraws();
    foreach(new i: Player)
    {
        if(snowOn{i})
        {
            for(new j = 0; j < MAX_SNOW_OBJECTS; j++) DestroyDynamicObject(snowObject[i][j]);
            KillTimer(updateTimer{i});
            }
    }
    return 1;
}
 
hook OnGameModeExit()
{
    DestroyTextdraws();
    return 1;
}
 
hook OnPlayerDisconnect(playerid, reason)
{
    if(snowOn{playerid})
    {
        for(new i = 0; i < MAX_SNOW_OBJECTS; i++) DestroyDynamicObject(snowObject[playerid][i]);
		snowOn{playerid} = false;
		KillTimer(updateTimer{playerid});
    }
    return 1;
}
 
hook OnPlayerConnect(playerid)
{
	CreateSnow(playerid);
	ShowLogo(playerid);
    return 1;
}
 
public UpdateSnow(playerid)
{
    if(!snowOn{playerid} || Drift_IsPlayerDrifting(playerid) || GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0 ) return 0;
    new Float:pPos[3];
    GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
    for(new i = 0; i < MAX_SNOW_OBJECTS; i++) SetDynamicObjectPos(snowObject[playerid][i], pPos[0] + random(25), pPos[1] + random(25), pPos[2] - 5);
    return 1;
}

CMD:snow(playerid)
{
    if(snowOn{playerid})
        DeleteSnow(playerid);
    else
        CreateSnow(playerid);
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Snow state changed!", MESSAGE_CASE_SERVER);
    return 1;
}

CMD:snowman(playerid,params[])
{
    if(!snowMan{playerid}) 
		ShowLogo(playerid);
	else 
		HideLogo(playerid);
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Snow Man state changed!", MESSAGE_CASE_SERVER);
    return 1;
}

CMD:treedataprint(playerid)
{
    new pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, sizeof pName);
    if(!strcmp(pName, "Andy[RDZ]", true))
    {
        new string[STRING_SIZE_QUERY], Float:x, Float:y, Float:z, ObjectModel;
        
        for(new i; i < MAX_TREE_SPACES; i++)
        {
            if(!IsValidDynamicObject(treeObjects[0][i])) continue;
            else
            {
                printf("Tree ID: %d:", i);
                for(new a; a < MAX_TREE_OBJECTS; a++)
                {
                    GetDynamicObjectPos(treeObjects[a][i], x, y, z);
                    ObjectModel = ExtractObjectModelFromID(a);
                    format(string, sizeof string, "CreateDynamicObject(%d, %f, %f, %f, 0.000, 0.000, 0.000)", ObjectModel, x, y, z);
                    print(string);
                }
                print("______________________");
            }
        }
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree data printed!", MESSAGE_CASE_SERVER);
    }
    return 1;
}

CMD:toggletreeid(playerid)
{
    new pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, sizeof pName);
    if(!strcmp(pName, "Andy[RDZ]", true))
    {
        new Float:x, Float:y, Float:z, string[15];
        if(!areTreesIDsShown)
        {
            for(new i; i < MAX_TREE_SPACES; i++)
            {
                if(!IsValidDynamicObject(treeObjects[0][i])) continue;
                else 
                {
                    GetDynamicObjectPos(treeObjects[0][i], x, y, z);
                    format(string, sizeof string, "TREE ID: %d", i);
                    s_treeLabel[i] = CreateDynamic3DTextLabel(string, 0x00FF00FF, x, y, z, TREE_LABEL_DD);
                }
            }
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree labels created", MESSAGE_CASE_NULL);
        }
        else
        {
            for(new i; i < MAX_TREE_SPACES; i++)
            {
                if(!IsValidDynamicObject(treeObjects[0][i])) continue;
                else 
                {
                    DestroyDynamic3DTextLabel(s_treeLabel[i]);
                    s_treeLabel[i] = Text3D:INVALID_3DTEXT_ID;
                }
            }
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree labels destroyed", MESSAGE_CASE_NULL);
        }
    }
    areTreesIDsShown = !areTreesIDsShown;
    return 1;
}

CMD:treedata(playerid)
{
    new pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, sizeof pName);
    if(!strcmp(pName, "Andy[RDZ]", true))
    {
        new TreeString[50];
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree data:", MESSAGE_CASE_NULL);
        for(new i; i < MAX_TREE_SPACES; i++)
        {
            format(TreeString, sizeof TreeString, "Tree id %d is %s", i, (IsValidDynamicObject(treeObjects[0][i]) ? "Taken" : "Empty"));
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, TreeString, MESSAGE_CASE_NULL);
        }
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "__________________", MESSAGE_CASE_NULL);
    }
    return 1;
}

CMD:createtree(playerid)
{
    new pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, sizeof pName);
    if(!strcmp(pName, "Andy[RDZ]", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        
        for(new i; i < MAX_TREE_SPACES; i++)
        {
            if(IsValidDynamicObject(treeObjects[0][i])) continue;
            else 
            {
                treeObjects[0][i] = CreateDynamicObject(19076, x, y, z-1.0, 0.0, 0.0, 0.0);
                treeObjects[1][i] = CreateDynamicObject(19054, x, y+1.0, z-0.4, 0.0, 0.0, 0.0);
                treeObjects[2][i] = CreateDynamicObject(19058, x+1.0, y, z-0.4, 0.0, 0.0, 0.0);
                treeObjects[3][i] = CreateDynamicObject(19056, x, y-1.0, z-0.4, 0.0, 0.0, 0.0);
                treeObjects[4][i] = CreateDynamicObject(19057, x-1.0, y, z-0.4, 0.0, 0.0, 0.0);
                treeObjects[5][i] = CreateDynamicObject(19058, x-1.5, y+1.5, z-1.0, 0.0, 0.0, 0.0);
                treeObjects[6][i] = CreateDynamicObject(19055, x+1.5, y-1.5, z-1.0, 0.0, 0.0, 0.0);
                treeObjects[7][i] = CreateDynamicObject(19057, x+1.5, y+1.5, z-1.0, 0.0, 0.0, 0.0);
                treeObjects[8][i] = CreateDynamicObject(19054, x-1.5, y-1.5, z-1.0, 0.0, 0.0, 0.0);
                treeObjects[9][i] = CreateDynamicObject(3526, x, y, z-1.0, 0.0, 0.0, 0.0);
                break;
            }
        }
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree created", MESSAGE_CASE_SERVER);
        SetPlayerPos(playerid, x+2.0, y+1.5, z);
    }
    return 1;
}

CMD:destroytree(playerid, params[])
{
    new pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, sizeof pName);
    if(!strcmp(pName, "Andy[RDZ]", true))
    {
        new id;
        if(sscanf(params, "i", id))
        {
            return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please make sure to mention the tree ID", MESSAGE_CASE_SERVER);
        }
        if(id < 0 || id > MAX_TREE_SPACES ) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree ID needs to be between 0 and 9", MESSAGE_CASE_SERVER);
        for(new i; i < MAX_TREE_OBJECTS; i++) 
        {
            DestroyDynamicObject(treeObjects[i][id]);
            treeObjects[i][id] = INVALID_OBJECT_ID;
        }
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Tree destroyed", MESSAGE_CASE_SERVER);
    }
    return 1;
}

public DestroyTextdraws(  )
{
    for(new i; i < MAX_TEXTDRAW_SNOWMAN; i++)
    {
        TextDrawHideForAll(SnowmanTextdraw[i]);
        TextDrawDestroy(SnowmanTextdraw[i]);
    }
    return 1;
}

public AddEyesOptions(   )
{
    TextDrawBackgroundColor(SnowmanTextdraw[11], 255);
    TextDrawFont(SnowmanTextdraw[11], 1);
    TextDrawLetterSize(SnowmanTextdraw[11], 0.400000, 1.500000);
    TextDrawColor(SnowmanTextdraw[11], 255);
    TextDrawSetOutline(SnowmanTextdraw[11], 0);
    TextDrawSetProportional(SnowmanTextdraw[11], 0);
    TextDrawSetShadow(SnowmanTextdraw[11], 0);
    return 1;
}

public AddMouthOptions(    )
{
    TextDrawBackgroundColor(SnowmanTextdraw[1], 255);
    TextDrawFont(SnowmanTextdraw[1], 1);
    TextDrawColor(SnowmanTextdraw[1], -1);
    TextDrawSetOutline(SnowmanTextdraw[1], 0);
    TextDrawSetProportional(SnowmanTextdraw[1], 1);
    TextDrawSetShadow(SnowmanTextdraw[1], 1);
    TextDrawUseBox(SnowmanTextdraw[1], 1);
    TextDrawBoxColor(SnowmanTextdraw[1], -1);
    TextDrawTextSize(SnowmanTextdraw[1], 504.000000, 0.000000);
    return 1;
}

public LoadTextdraws(  )
{
 
    // Create the textdraws:
    SnowmanTextdraw[0] = TextDrawCreate(501.000000, 402.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[0], 255);
    TextDrawFont(SnowmanTextdraw[0], 1);
    TextDrawLetterSize(SnowmanTextdraw[0], 0.899999, 3.000000);
    TextDrawColor(SnowmanTextdraw[0], -1);
    TextDrawSetOutline(SnowmanTextdraw[0], 0);
    TextDrawSetProportional(SnowmanTextdraw[0], 1);
    TextDrawSetShadow(SnowmanTextdraw[0], 0);

    SnowmanTextdraw[1] = TextDrawCreate(521.000000, 412.000000, "~n~");
    TextDrawBackgroundColor(SnowmanTextdraw[1], 255);
    TextDrawFont(SnowmanTextdraw[1], 1);
    TextDrawLetterSize(SnowmanTextdraw[1], 2.099999, 0.499999);
    TextDrawColor(SnowmanTextdraw[1], -1);
    TextDrawSetOutline(SnowmanTextdraw[1], 0);
    TextDrawSetProportional(SnowmanTextdraw[1], 1);
    TextDrawSetShadow(SnowmanTextdraw[1], 1);
    TextDrawUseBox(SnowmanTextdraw[1], 1);
    TextDrawBoxColor(SnowmanTextdraw[1], -1);
    TextDrawTextSize(SnowmanTextdraw[1], 504.000000, 0.000000);

    SnowmanTextdraw[2] = TextDrawCreate(496.000000, 412.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[2], 255);
    TextDrawFont(SnowmanTextdraw[2], 1);
    TextDrawLetterSize(SnowmanTextdraw[2], 1.329998, 4.899999);
    TextDrawColor(SnowmanTextdraw[2], -1);
    TextDrawSetOutline(SnowmanTextdraw[2], 0);
    TextDrawSetProportional(SnowmanTextdraw[2], 1);
    TextDrawSetShadow(SnowmanTextdraw[2], 0);

    SnowmanTextdraw[3] = TextDrawCreate(527.000000, 429.000000, "~n~");
    TextDrawBackgroundColor(SnowmanTextdraw[3], 255);
    TextDrawFont(SnowmanTextdraw[3], 1);
    TextDrawLetterSize(SnowmanTextdraw[3], 2.099999, 1.400000);
    TextDrawColor(SnowmanTextdraw[3], -1);
    TextDrawSetOutline(SnowmanTextdraw[3], 0);
    TextDrawSetProportional(SnowmanTextdraw[3], 1);
    TextDrawSetShadow(SnowmanTextdraw[3], 1);
    TextDrawUseBox(SnowmanTextdraw[3], 1);
    TextDrawBoxColor(SnowmanTextdraw[3], -1);
    TextDrawTextSize(SnowmanTextdraw[3], 501.000000, -2.000000);

    SnowmanTextdraw[4] = TextDrawCreate(511.000000, 418.000000, ":");
    TextDrawBackgroundColor(SnowmanTextdraw[4], 255);
    TextDrawFont(SnowmanTextdraw[4], 1);
    TextDrawLetterSize(SnowmanTextdraw[4], 0.469999, 1.500000);
    TextDrawColor(SnowmanTextdraw[4], 255);
    TextDrawSetOutline(SnowmanTextdraw[4], 0);
    TextDrawSetProportional(SnowmanTextdraw[4], 1);
    TextDrawSetShadow(SnowmanTextdraw[4], 0);

    SnowmanTextdraw[5] = TextDrawCreate(550.000000, 427.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[5], 255);
    TextDrawFont(SnowmanTextdraw[5], 1);
    TextDrawLetterSize(SnowmanTextdraw[5], 2.029999, 4.899999);
    TextDrawColor(SnowmanTextdraw[5], -1);
    TextDrawSetOutline(SnowmanTextdraw[5], 0);
    TextDrawSetProportional(SnowmanTextdraw[5], 1);
    TextDrawSetShadow(SnowmanTextdraw[5], 0);

    SnowmanTextdraw[6] = TextDrawCreate(512.000000, 432.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[6], -1);
    TextDrawFont(SnowmanTextdraw[6], 1);
    TextDrawLetterSize(SnowmanTextdraw[6], 2.029999, 4.899999);
    TextDrawColor(SnowmanTextdraw[6], -1);
    TextDrawSetOutline(SnowmanTextdraw[6], 0);
    TextDrawSetProportional(SnowmanTextdraw[6], 1);
    TextDrawSetShadow(SnowmanTextdraw[6], -2);

    SnowmanTextdraw[7] = TextDrawCreate(553.000000, 433.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[7], 20);
    TextDrawFont(SnowmanTextdraw[7], 1);
    TextDrawLetterSize(SnowmanTextdraw[7], 2.029999, 4.899999);
    TextDrawColor(SnowmanTextdraw[7], -1);
    TextDrawSetOutline(SnowmanTextdraw[7], 0);
    TextDrawSetProportional(SnowmanTextdraw[7], 1);
    TextDrawSetShadow(SnowmanTextdraw[7], 0);

    SnowmanTextdraw[8] = TextDrawCreate(573.000000, 427.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[8], -1);
    TextDrawFont(SnowmanTextdraw[8], 1);
    TextDrawLetterSize(SnowmanTextdraw[8], 3.789998, 4.899999);
    TextDrawColor(SnowmanTextdraw[8], -1);
    TextDrawSetOutline(SnowmanTextdraw[8], 0);
    TextDrawSetProportional(SnowmanTextdraw[8], 1);
    TextDrawSetShadow(SnowmanTextdraw[8], 4);

    SnowmanTextdraw[9] = TextDrawCreate(500.000000, 405.000000, "O");
    TextDrawBackgroundColor(SnowmanTextdraw[9], 255);
    TextDrawFont(SnowmanTextdraw[9], 1);
    TextDrawLetterSize(SnowmanTextdraw[9], 0.949999, 0.799998);
    TextDrawColor(SnowmanTextdraw[9], 255);
    TextDrawSetOutline(SnowmanTextdraw[9], 1);
    TextDrawSetProportional(SnowmanTextdraw[9], 1);

    SnowmanTextdraw[10] = TextDrawCreate(527.000000, 406.000000, "~n~");
    TextDrawBackgroundColor(SnowmanTextdraw[10], 255);
    TextDrawFont(SnowmanTextdraw[10], 1);
    TextDrawLetterSize(SnowmanTextdraw[10], 0.500000, 0.099999);
    TextDrawColor(SnowmanTextdraw[10], -1);
    TextDrawSetOutline(SnowmanTextdraw[10], 0);
    TextDrawSetProportional(SnowmanTextdraw[10], 1);
    TextDrawSetShadow(SnowmanTextdraw[10], 1);
    TextDrawUseBox(SnowmanTextdraw[10], 1);
    TextDrawBoxColor(SnowmanTextdraw[10], 255);
    TextDrawTextSize(SnowmanTextdraw[10], 498.000000, 0.000000);



    SnowmanTextdraw[12] = TextDrawCreate(511.000000, 428.000000, ":");
    TextDrawBackgroundColor(SnowmanTextdraw[12], 255);
    TextDrawFont(SnowmanTextdraw[12], 1);
    TextDrawLetterSize(SnowmanTextdraw[12], 0.469999, 1.500000);
    TextDrawColor(SnowmanTextdraw[12], 255);
    TextDrawSetOutline(SnowmanTextdraw[12], 0);
    TextDrawSetProportional(SnowmanTextdraw[12], 1);
    TextDrawSetShadow(SnowmanTextdraw[12], 0);

    SnowmanTextdraw[13] = TextDrawCreate(512.000000, 420.000000, "/");
    TextDrawBackgroundColor(SnowmanTextdraw[13], 255);
    TextDrawFont(SnowmanTextdraw[13], 1);
    TextDrawLetterSize(SnowmanTextdraw[13], 0.449998, -0.399998);
    TextDrawColor(SnowmanTextdraw[13], -15466241);
    TextDrawSetOutline(SnowmanTextdraw[13], 0);
    TextDrawSetProportional(SnowmanTextdraw[13], 1);
    TextDrawSetShadow(SnowmanTextdraw[13], 0);

    SnowmanTextdraw[14] = TextDrawCreate(530.000000, 380.000000, ".     ~n~  .  .    .      . ~n~ .   .   .     . .  .~n~     .    . ~n~ .    .       .       . ~n~    .    .     .  . ~n~ .  .   ");
    TextDrawBackgroundColor(SnowmanTextdraw[14], -206);
    TextDrawFont(SnowmanTextdraw[14], 1);
    TextDrawLetterSize(SnowmanTextdraw[14], 0.330000, 0.999998);
    TextDrawColor(SnowmanTextdraw[14], -1);
    TextDrawSetOutline(SnowmanTextdraw[14], 0);
    TextDrawSetProportional(SnowmanTextdraw[14], 1);
    TextDrawSetShadow(SnowmanTextdraw[14], 10);

    SnowmanTextdraw[15] = TextDrawCreate(576.000000, 482.000000, ".     ~n~  .  .    .      . ~n~ .   .   .     . .  .~n~     .    . ~n~ .    .       .       . ~n~    .    .     .  . ~n~ .  .   ");
    TextDrawBackgroundColor(SnowmanTextdraw[15], -206);
    TextDrawFont(SnowmanTextdraw[15], 1);
    TextDrawLetterSize(SnowmanTextdraw[15], 0.330000, -1.000000);
    TextDrawColor(SnowmanTextdraw[15], -1);
    TextDrawSetOutline(SnowmanTextdraw[15], 0);
    TextDrawSetProportional(SnowmanTextdraw[15], 1);
    TextDrawSetShadow(SnowmanTextdraw[15], -60);

    SnowmanTextdraw[16] = TextDrawCreate(526.000000, 422.000000, "Happy new year!");
    TextDrawBackgroundColor(SnowmanTextdraw[16], -1);
    TextDrawFont(SnowmanTextdraw[16], 1);
    TextDrawLetterSize(SnowmanTextdraw[16], 0.430000, 2.000000);
    TextDrawColor(SnowmanTextdraw[16], -1);
    TextDrawSetOutline(SnowmanTextdraw[16], 0);
    TextDrawSetProportional(SnowmanTextdraw[16], 1);
    TextDrawSetShadow(SnowmanTextdraw[16], 0);

    SnowmanTextdraw[17] = TextDrawCreate(505.000000, 419.000000, "/");
    TextDrawBackgroundColor(SnowmanTextdraw[17], 255);
    TextDrawFont(SnowmanTextdraw[17], 1);
    TextDrawLetterSize(SnowmanTextdraw[17], -0.889999, 1.299998);
    TextDrawColor(SnowmanTextdraw[17], -1656160001);
    TextDrawSetOutline(SnowmanTextdraw[17], 0);
    TextDrawSetProportional(SnowmanTextdraw[17], 1);
    TextDrawSetShadow(SnowmanTextdraw[17], 0);

    SnowmanTextdraw[18] = TextDrawCreate(498.000000, 410.000000, "/");
    TextDrawBackgroundColor(SnowmanTextdraw[18], 255);
    TextDrawFont(SnowmanTextdraw[18], 1);
    TextDrawLetterSize(SnowmanTextdraw[18], -0.889999, 1.299998);
    TextDrawColor(SnowmanTextdraw[18], -1656160001);
    TextDrawSetOutline(SnowmanTextdraw[18], 0);
    TextDrawSetProportional(SnowmanTextdraw[18], 1);
    TextDrawSetShadow(SnowmanTextdraw[18], 0);

    SnowmanTextdraw[19] = TextDrawCreate(528.000000, 424.000000, "Happy new year!");
    TextDrawBackgroundColor(SnowmanTextdraw[19], -1);
    TextDrawFont(SnowmanTextdraw[19], 1);
    TextDrawLetterSize(SnowmanTextdraw[19], 0.409999, 1.700000);
    TextDrawColor(SnowmanTextdraw[19], 50);
    TextDrawSetOutline(SnowmanTextdraw[19], 0);
    TextDrawSetProportional(SnowmanTextdraw[19], 1);
    TextDrawSetShadow(SnowmanTextdraw[19], 0);

    SnowmanTextdraw[11] = TextDrawCreate(508.000000, 405.000000, "..");
    TextDrawBackgroundColor(SnowmanTextdraw[11], 255);
    TextDrawFont(SnowmanTextdraw[11], 1);
    TextDrawLetterSize(SnowmanTextdraw[11], 0.400000, 1.500000);
    TextDrawColor(SnowmanTextdraw[11], 255);
    TextDrawSetOutline(SnowmanTextdraw[11], 0);
    TextDrawSetProportional(SnowmanTextdraw[11], 0);
    TextDrawSetShadow(SnowmanTextdraw[11], 0);

    foreach(new i: Player)
    {
        HideLogo( i );
    }
    return 1;
}
 
stock ShowLogo( playerid )
{
    for(new i; i < MAX_TEXTDRAW_SNOWMAN; i++)
    {
        TextDrawShowForPlayer(playerid, SnowmanTextdraw[i]);
    }
    snowMan{playerid} = true;
    return 1;
}

stock HideLogo( playerid, bool:Drifting = false)
{
    for(new i; i < MAX_TEXTDRAW_SNOWMAN; i++)
    {
        TextDrawHideForPlayer(playerid, SnowmanTextdraw[i]);
    }
    if(!Drifting) snowMan{playerid} = false;
    return 1;
}
 
stock CreateSnow(playerid, bool:Drifting = false)
{
        if(snowOn{playerid} && !Drifting) return 0;
        new Float:pPos[3];
        GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
        for(new i; i < MAX_SNOW_OBJECTS; i++) snowObject[playerid][i] = CreateDynamicObject(18864, pPos[0] + random(25), pPos[1] + random (25), pPos[2] - 5, random(100), random(100), random(100), -1, -1, playerid);
        snowOn{playerid} = true;
        updateTimer{playerid} = SetTimerEx("UpdateSnow", UPDATE_INTERVAL, true, "i", playerid);
        return 1;
}
 
stock DeleteSnow(playerid, bool:Drifting = false)
{
    if(!snowOn{playerid}) return 0;
    for(new i; i < MAX_SNOW_OBJECTS; i++) DestroyDynamicObject(snowObject[playerid][i]);
    KillTimer(updateTimer{playerid});
    if(!Drifting) snowOn{playerid} = false;
    return 1;
}

stock IsSnowOn(playerid)
    return (snowOn{playerid});
stock IsSnowManOn(playerid)
    return (snowMan{playerid});