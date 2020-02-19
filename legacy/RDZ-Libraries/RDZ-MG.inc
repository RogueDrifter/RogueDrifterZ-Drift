#if defined ModGa_SYS_Included_
   #endinput
#endif

#define ModGa_SYS_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

static bool:PInModGa[MAX_PLAYERS char], 
            gPlayerHolder[MAX_PLAYERS], 
            gPlayerMGVeh[MAX_PLAYERS], 
            SPOILER_OBJECT[MAX_VEHICLES], 
            STICKER_OBJECT[MAX_VEHICLES],
            STICKER_STRING[MAX_VEHICLES][STRING_SIZE_MEDIUM],
            s_VehicleNeon[MAX_VEHICLES];

enum E_RIMS_LISTITEM
{
    E_RIMS_LISTITEM_MODEL
};

static const RIMS_LIST[][E_RIMS_LISTITEM] =
{
    {1080},
    {1081},
    {1082},
    {1083},
    {1084},
    {1085},
    {1073},
    {1074},
    {1075},
    {1076},
    {1077},
    {1078},
    {1079},
    {1025},
    {1096}
};

enum E_SPOILER_LISTITEM
{
    E_SPOILERS_LISTITEM_MODEL
};

static const SPOILERS_LIST[][E_SPOILER_LISTITEM] =
{
    {1000},
    {1001},
    {1002},
    {1003},
    {1014},
    {1015},
    {1016},
    {1023},
    {1139},
    {1163},
    {1162}
};

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (KEY_PRESSED(KEY_CROUCH))
	{
        new vehicleid = GetPlayerVehicleID(playerid);
        new mgPick;

        if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !GetPlayerWantedLevel(playerid) && IsVehicleModGarage(vehicleid) && !PInModGa{playerid})
        {
            if(IsPlayerInRangeOfPoint(playerid, 7.0, -1974.1254, 431.3540, 34.8313)) mgPick = 1;
            if(mgPick != 0)
            {
                SetPlayerVirtualWorld(playerid, playerid + 1);
                SetVehicleVirtualWorld(vehicleid, playerid + 1);
                foreach( new i: Player )
                {
                    if(i !=playerid && GetPlayerSurfingVehicleID(i) == vehicleid) SetPlayerHealth(i, 0);

                    if(GetPlayerState(i) == PLAYER_STATE_PASSENGER && GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid))
                    {
                        SetPlayerVirtualWorld(i, playerid + 1);
                        SetPlayerInterior(i, 1);
                        TogglePlayerControllable(i, false);
                        gPlayerHolder[i] = playerid;
                        PInModGa{i} = true;
                    }
                }

                if(mgPick == 1)
                {
                    SetVehicleZAngle(vehicleid, 106.2384);
                    SetPlayerCameraPos(playerid, 604.0652, -4.8276, 1002.9633);
                    SetPlayerCameraLookAt(playerid, 613.1154, -1.0521, 1000.5810);
                    SetVehiclePos(GetPlayerVehicleID(playerid), 613.1154, -1.0521, 1000.5810);
                }

                gPlayerMGVeh[playerid] = vehicleid;
                PInModGa{playerid} = true;
                TogglePlayerControllable(playerid, false);

                SetPlayerInterior(playerid, 1);
                LinkVehicleToInterior(vehicleid, 1);
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);            
            }
        }
    }
    return 1;
}

Dialog:DIALOG_MG(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!response)
    {
        SetVehiclePos(vehicleid, -1975.8916, 430.8934, 34.8291);
        SetVehicleZAngle(vehicleid, 89.0632);

        PInModGa{playerid} = false;
        TogglePlayerControllable(playerid, true);
        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);

        foreach( new i: Player )
        {
            if(!PInModGa{i}) continue;
            if(gPlayerHolder[i] == playerid)
            {
                SetPlayerVirtualWorld(i, 0);
                SetPlayerInterior(i, 0);
                TogglePlayerControllable(i, true);
                PInModGa{i} = false;
            }
        }

        SetCameraBehindPlayer(playerid);
        LinkVehicleToInterior(vehicleid, 0);
        SetVehicleVirtualWorld(vehicleid, 0);
    }
    else
    {
        switch(listitem)
        {
            case 0:
            {
                new string[sizeof(RIMS_LIST) *50];
                for (new i; i < sizeof(RIMS_LIST); i++)
                {
                    format(string, sizeof string, "%s%i\n", string, RIMS_LIST[i][E_RIMS_LISTITEM_MODEL]);
                }
                Dialog_Show(playerid, DIALOG_RIMS, DIALOG_STYLE_PREVIEW_MODEL, "Custom Rims", string, "Select", "Close");
            }
            case 1:
            {
                if( GetVehicleModel ( vehicleid ) == 562 ) //===== This is for Elegy ONLY!..
                {
                    new string[sizeof(SPOILERS_LIST) *50];
                    for (new i; i < sizeof(SPOILERS_LIST); i++)
                    {
                        format(string, sizeof string, "%s%i\n", string, SPOILERS_LIST[i][E_SPOILERS_LISTITEM_MODEL]);
                    }
                    Dialog_Show(playerid, DIALOG_SPOILERS, DIALOG_STYLE_PREVIEW_MODEL, "Spoilers",  string, "Select", "Close");
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 10.0);
                }
                else SendRDZMessage(playerid,RDZ_OFFICIAL_COLOR,"You need to be in an elegy", MESSAGE_CASE_SERVER), 
                     Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit"); 
            }
            case 2:
            {
                if( GetVehicleModel ( vehicleid ) == 562 ) //===== This is for Elegy ONLY!..
                {
                    Dialog_Show(playerid, DIALOG_STICKERS, DIALOG_STYLE_LIST, "Stickers","Add sticker\nRemove sticker\nColor sticker", "Select", "Exit");
                    PlayerPlaySound(playerid,1133,0.0,0.0,10.0);
                }
                else SendRDZMessage(playerid,RDZ_OFFICIAL_COLOR,"You need to be in an elegy", MESSAGE_CASE_SERVER), 
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit"); 
            }
            case 3:
            {
                Dialog_Show(playerid, DIALOG_RESPRAYSPOILER, DIALOG_STYLE_LIST, "Spoiler Colors.","Red\nGreen\nBlue\nWhite\nBlack\nGolden", "Select", "Exit");
            }
            case 4:
            {
                if( VehicleSupportsNeonLights(GetVehicleModel(vehicleid)) ) //===== This is for certain vehicles ONLY!..
                {
                    Dialog_Show(playerid, DIALOG_NEONS, DIALOG_STYLE_LIST, "Neons","Green\nYellow\nRed\nPink\nWhite\nBlue\nRemove Neons", "Select", "Exit");
                    PlayerPlaySound(playerid,1133,0.0,0.0,10.0);
                }
                else SendRDZMessage(playerid,RDZ_OFFICIAL_COLOR,"You need to be in a vehicle that supports neons!", MESSAGE_CASE_SERVER), 
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit"); 
            }
            case 5:
            {
                for(new i; i < MAX_VEHICLE_COMPONENTS; i++) RemoveVehicleComponent(vehicleid, GetVehicleComponentInSlot(vehicleid, i));
                ChangeVehiclePaintjob(vehicleid, 3);
                SendRDZMessage(playerid,RDZ_OFFICIAL_COLOR,"All mods were removed!", MESSAGE_CASE_SERVER);
                if(IsValidDynamicObject(SPOILER_OBJECT[vehicleid])) {
                    DestroyDynamicObject(SPOILER_OBJECT[vehicleid]);
                    SPOILER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
                }
                if(IsValidDynamicObject(STICKER_OBJECT[Player_TelecarID[playerid]])) {
                    DestroyDynamicObject(STICKER_OBJECT[Player_TelecarID[playerid]]);
                    STICKER_OBJECT[Player_TelecarID[playerid]]= INVALID_OBJECT_ID;
                }
                if(GetVehicleNeonLightsState(vehicleid)) SetVehicleNeonLights(vehicleid, false), s_VehicleNeon[vehicleid] = INVALID_OBJECT_ID;
                UpdateTelecarComponents(playerid);
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit"); 
            }
            case 6:
            {
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods", "Select", "Exit");
                if(IsValidDynamicObject(SPOILER_OBJECT[vehicleid])) {
                    DestroyDynamicObject(SPOILER_OBJECT[vehicleid]);
                    SPOILER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
                }
                SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Spoiler has been successfully Uninstalled", MESSAGE_CASE_SERVER);
            }
        }
    }
    return 1;
}
Dialog:DIALOG_NEONS(playerid, response, listitem, inputtext[])
{
    new vehicleid = GetPlayerVehicleID(playerid);

    if(!response) return    Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    
    else if(response)
    {
        if(GetPlayerMoney(playerid) < 800)
        {
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Insufficient funds!", MESSAGE_CASE_SERVER);
            return  Dialog_Show(playerid, DIALOG_NEONS, DIALOG_STYLE_LIST, "Neons","Green\nYellow\nRed\nPink\nWhite\nBlue\nRemove Neons", "Select", "Exit");
        }
        switch(listitem)
        {
            case 0://GREEN
            {
                SetVehicleNeonLights(vehicleid, true, NEON_LIGHT_GREEN);
                s_VehicleNeon[vehicleid] = NEON_LIGHT_GREEN;
            }
            case 1://YELLOW
            {
                SetVehicleNeonLights(vehicleid, true, NEON_LIGHT_YELLOW);
                s_VehicleNeon[vehicleid] = NEON_LIGHT_YELLOW;
            }
            case 2://RED
            {
                SetVehicleNeonLights(vehicleid, true, NEON_LIGHT_RED);
                s_VehicleNeon[vehicleid] = NEON_LIGHT_RED;
            }
            case 3://PINK
            {
                SetVehicleNeonLights(vehicleid, true, NEON_LIGHT_PINK);
                s_VehicleNeon[vehicleid] = NEON_LIGHT_PINK;
            }
            case 4://WHITE
            {
                SetVehicleNeonLights(vehicleid, true, NEON_LIGHT_WHITE);
                s_VehicleNeon[vehicleid] = NEON_LIGHT_WHITE;
            }
            case 5://BLUE
            {
                SetVehicleNeonLights(vehicleid, true, NEON_LIGHT_BLUE);
                s_VehicleNeon[vehicleid] = NEON_LIGHT_BLUE;
            }
            case 6://Remove neons
            {
                SetVehicleNeonLights(vehicleid, false);
                s_VehicleNeon[vehicleid] = INVALID_OBJECT_ID;
            }
        }

        GivePlayerMoney(playerid, -800);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Neons installed!", MESSAGE_CASE_SERVER);
        Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    }
    return 1;
}

Dialog:DIALOG_RIMS(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);

    if(!response) return    Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    
    else if(response)
    {
        if(GetPlayerMoney(playerid) < 650)
        {
            new string[sizeof(RIMS_LIST) *50];
            for (new i; i < sizeof(RIMS_LIST); i++)
            {
                format(string, sizeof string, "%s%i\n", string, RIMS_LIST[i][E_RIMS_LISTITEM_MODEL]);
            }
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Insufficient funds!", MESSAGE_CASE_SERVER);
            return Dialog_Show(playerid, DIALOG_RIMS, DIALOG_STYLE_PREVIEW_MODEL, "Custom Rims", string, "Select", "Close");
        }

        switch(listitem)
        {

            case 0:
                AddVehicleComponent(vehicleid, 1084);
            case 1:
                AddVehicleComponent(vehicleid, 1085);
            case 2:
                AddVehicleComponent(vehicleid, 1083);
            case 3:
                AddVehicleComponent(vehicleid, 1082);
            case 4:
                AddVehicleComponent(vehicleid, 1081);
            case 5:
                AddVehicleComponent(vehicleid, 1080);
            case 6:
                AddVehicleComponent(vehicleid, 1079);
            case 7:
                AddVehicleComponent(vehicleid, 1078);
            case 8:
                AddVehicleComponent(vehicleid, 1077);
            case 9:
                AddVehicleComponent(vehicleid, 1076);
            case 10:
                AddVehicleComponent(vehicleid, 1075);
            case 11:
                AddVehicleComponent(vehicleid, 1074);
            case 12:
                AddVehicleComponent(vehicleid, 1073);
            case 13:
                AddVehicleComponent(vehicleid, 1025);
            case 14:
                AddVehicleComponent(vehicleid, 1096);
        }

        GivePlayerMoney(playerid, -650);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Rims installed!", MESSAGE_CASE_SERVER);
        Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)   
{
    if(PInModGa{playerid})
    {
        PInModGa{playerid} = false;
        if( IsValidVehicle(gPlayerMGVeh[playerid]) ) SetVehicleToRespawn(gPlayerMGVeh[playerid]);
    }

	if(IsValidVehicle(Player_TelecarID[playerid]))
	{
        if(IsValidDynamicObject(SPOILER_OBJECT[Player_TelecarID[playerid]])) {
            DestroyDynamicObject(SPOILER_OBJECT[Player_TelecarID[playerid]]);
            SPOILER_OBJECT[Player_TelecarID[playerid]]= INVALID_OBJECT_ID;
        }
        if(GetVehicleNeonLightsState(Player_TelecarID[playerid])) SetVehicleNeonLights(Player_TelecarID[playerid], false);

        if(IsValidDynamicObject(STICKER_OBJECT[Player_TelecarID[playerid]])) {
            DestroyDynamicObject(STICKER_OBJECT[Player_TelecarID[playerid]]);
            STICKER_OBJECT[Player_TelecarID[playerid]]= INVALID_OBJECT_ID;
        }
    }
    return 1;
}

static IsVehicleModGarage(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 499, 609, 498, 524, 532, 578, 486, 406, 573, 455, 588, 403, 423, 414, 443, 515, 514, 531, 456, 530, 572, 583, 478, 482, 459, 568, 424, 457, 508, 571, 471, 539, 432, 601, 428, 416, 433, 427, 490, 528, 407, 544, 523, 470, 596, 598, 599, 597, 485, 431, 438, 437, 574, 420, 525, 408, 552, 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469, 581, 509, 481, 462, 521, 463, 510, 522, 461, 448, 468, 586: return 0;
    }
	return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    if(GetVehicleNeonLightsState(vehicleid)) SetVehicleNeonLights(vehicleid, false), s_VehicleNeon[vehicleid] = INVALID_OBJECT_ID;

    if(IsValidDynamicObject(SPOILER_OBJECT[vehicleid])) {
        DestroyDynamicObject(SPOILER_OBJECT[vehicleid]);
        SPOILER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
    }

    if(IsValidDynamicObject(STICKER_OBJECT[vehicleid])) {
        DestroyDynamicObject(STICKER_OBJECT[vehicleid]);
        STICKER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
    }
    return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
    if(GetVehicleNeonLightsState(vehicleid)) SetVehicleNeonLights(vehicleid, false), s_VehicleNeon[vehicleid] = INVALID_OBJECT_ID;
    if(IsValidDynamicObject(SPOILER_OBJECT[vehicleid])) {
        DestroyDynamicObject(SPOILER_OBJECT[vehicleid]);
        SPOILER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
    }

    if(IsValidDynamicObject(STICKER_OBJECT[vehicleid])) {
        DestroyDynamicObject(STICKER_OBJECT[vehicleid]);
        STICKER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
    }
    return 1;
}

hook OnVehicleMod(playerid, vehicleid, componentid)
{
    if (IsVehicleUpgradeCompatible(GetVehicleModel(vehicleid), componentid))
    {
        new compocost = GetVehicleComponentCost(componentid);

        if(GetPlayerMoney(playerid) < compocost) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Not enough cash to upgrade, sorry!", MESSAGE_CASE_SERVER);
        
        new
            name[STRING_SIZE_SMALL], 
            string[STRING_SIZE_LARGE];

        GetVehicleComponentName(componentid, name, sizeof(name));

        format(string, sizeof(string), "You have successfully installed \"%s\" price %d", name, compocost);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
        GivePlayerMoney(playerid, -compocost);
    }
    if(componentid == 1147 || componentid == 1146)
    {
        if(IsValidDynamicObject(SPOILER_OBJECT[vehicleid])) {
            DestroyDynamicObject(SPOILER_OBJECT[vehicleid]);
            SPOILER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
        }

        if(IsValidDynamicObject(STICKER_OBJECT[vehicleid])) {
            DestroyDynamicObject(STICKER_OBJECT[vehicleid]);
            STICKER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
        }
    }
    return 1;
}


Dialog:DIALOG_SPOILERS(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!response)
    {
        Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    }
    else
    {
        new modelid;
        switch(listitem)
        {
            case 0:modelid=1000;
            case 1:modelid=1001;
            case 2:modelid=1002;
            case 3:modelid=1003;
            case 4:modelid=1014;
            case 5:modelid=1015;
            case 6:modelid=1016;
            case 7:modelid=1023;
            case 8:modelid=1139;
            case 9:modelid=1163;
            case 10:modelid=1162;
        }
        if(GetPlayerMoney(playerid) >= 650)
        {
            if(IsValidDynamicObject(SPOILER_OBJECT[vehicleid]))
            {
                DestroyDynamicObject(SPOILER_OBJECT[vehicleid]);
                SPOILER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
            }
            SPOILER_OBJECT[vehicleid] = CreateDynamicObject(modelid, 0, 0, 0, 0, 0, 0);
            AttachDynamicObjectToVehicle(SPOILER_OBJECT[vehicleid], vehicleid, 0.000000, -2.205003, 0.309999, 0.000000, 0.000000, 0.000000);

            RemoveVehicleComponent(vehicleid, 1146);
            RemoveVehicleComponent(vehicleid, 1147);

            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 10.0);
            GivePlayerMoney(playerid, -650);

            GameTextForPlayer(playerid, "~r~-~w~650~g~:-", 3000, 1);
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Spoiler has been successfully installed", MESSAGE_CASE_SERVER);

            SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, 1163, "", "", 0xBB0000FF);
            Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
        }
        else if(GetPlayerMoney(playerid) < 650)
        {   
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Insufficient funds!", MESSAGE_CASE_SERVER);
            Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
        }
    }
    return 1;
}

#define MAX_STICKER_LENGTH 10
Dialog:DIALOG_INPUT_STICKERS(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(response)
    {
        format(STICKER_STRING[vehicleid], STRING_SIZE_MEDIUM, "%s", inputtext);
        if(strlen(STICKER_STRING[vehicleid]) >= MAX_STICKER_LENGTH) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, " Shorten it down a bit! ", MESSAGE_CASE_SERVER), 
        Dialog_Show(playerid, DIALOG_STICKERS, DIALOG_STYLE_LIST, "Stickers", "Add sticker\nRemove sticker\nColor sticker", "Select", "Exit");
        SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid], 0, STICKER_STRING[vehicleid], OBJECT_MATERIAL_SIZE_256x128, "Arial", 60, 1, 0xFFFF8200, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Sticker Installed", MESSAGE_CASE_SERVER);
        Dialog_Show(playerid, DIALOG_STICKERS, DIALOG_STYLE_LIST, "Stickers", "Add sticker\nRemove sticker\nColor sticker", "Select", "Exit");
    }
    else 
    {
        if(IsValidDynamicObject(STICKER_OBJECT[vehicleid])) {
            DestroyDynamicObject(STICKER_OBJECT[vehicleid]);
            STICKER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
        }
        Dialog_Show(playerid, DIALOG_STICKERS, DIALOG_STYLE_LIST, "Stickers", "Add sticker\nRemove sticker\nColor sticker", "Select", "Exit");
    }
    return 1;
}


Dialog:DIALOG_STICKERS(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!response) 
    {
        Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    }
    else 
    {
        switch(listitem)
        {
            case 0:
            {
                if(GetPlayerMoney(playerid) < 650) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Insufficient funds!", MESSAGE_CASE_SERVER), 
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
                if(IsValidDynamicObject(STICKER_OBJECT[vehicleid])) {
                    DestroyDynamicObject(STICKER_OBJECT[vehicleid]);
                    STICKER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
                }
                GivePlayerMoney(playerid, -650);
                STICKER_OBJECT[vehicleid] = CreateDynamicObject( 1547, 0, 0, 0, 0, 0, 0, 80 ); 
                AttachDynamicObjectToVehicle( STICKER_OBJECT[vehicleid], vehicleid, -0.000000, -1.400000, 0.500000, 31.000000, 0.000000, 0.000000 ); 
                Dialog_Show(playerid, DIALOG_INPUT_STICKERS, DIALOG_STYLE_INPUT, "Sticker", "Type your sticker's text below", "Accept", "Cancel");
            }
            case 1:
            {
                if(IsValidDynamicObject(STICKER_OBJECT[vehicleid])) {
                    DestroyDynamicObject(STICKER_OBJECT[vehicleid]);
                    STICKER_OBJECT[vehicleid]= INVALID_OBJECT_ID;
                }
                Dialog_Show(playerid, DIALOG_STICKERS, DIALOG_STYLE_LIST, "Stickers", "Add sticker\nRemove sticker\nColor sticker", "Select", "Exit");
            }
            case 2:
            {
                if(GetPlayerMoney(playerid) < 650) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Insufficient funds!", MESSAGE_CASE_SERVER), 
                Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
                Dialog_Show(playerid, DIALOG_STICKERCOLOR, DIALOG_STYLE_LIST, "Color your sticker.", "Red\nGreen\nBlue\nWhite\nBlack\nGolden", "Select", "Exit");
            }
        }
    }
    return 1;
}


Dialog:DIALOG_STICKERCOLOR(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(response)
    {
        if(GetPlayerMoney(playerid) < 650 || !IsValidDynamicObject(STICKER_OBJECT[vehicleid])) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Cannot color your sticker at the moment!", MESSAGE_CASE_SERVER),
        Dialog_Show(playerid, DIALOG_STICKERCOLOR, DIALOG_STYLE_LIST, "Color your sticker.", "Red\nGreen\nBlue\nWhite\nBlack\nGolden", "Select", "Exit");
        switch(listitem)
        {
            case 0:
            {
                SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid], 0, STICKER_STRING[vehicleid], OBJECT_MATERIAL_SIZE_256x128       ,"Arial", 60, 1, 0xFFFF0000, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
            }
            case 1:
            {
                SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid],  0, STICKER_STRING[vehicleid], OBJECT_MATERIAL_SIZE_256x128     ,"Arial", 60, 1, 0xFF00FF00, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
            }
            case 2:
            {
                SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid], 0, STICKER_STRING[vehicleid], OBJECT_MATERIAL_SIZE_256x128     ,"Arial", 60, 1, 0xFF0000FF, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
            }
            case 3:
            {
                SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid], 0, STICKER_STRING[vehicleid],  OBJECT_MATERIAL_SIZE_256x128     ,"Arial", 60, 1, 0xFFFFFFFF, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
            }
            case 4:
            {
                SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid], 0, STICKER_STRING[vehicleid],  OBJECT_MATERIAL_SIZE_256x128     ,"Arial", 60, 1, 0xFF000000, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
            }
            case 5:
            {
                SetDynamicObjectMaterialText(STICKER_OBJECT[vehicleid], 0, STICKER_STRING[vehicleid],  OBJECT_MATERIAL_SIZE_256x128     ,"Arial", 60, 1, 0xFF908950, 0x00000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
            }
        }
        Dialog_Show(playerid, DIALOG_STICKERCOLOR, DIALOG_STYLE_LIST, "Color your sticker.", "Red\nGreen\nBlue\nWhite\nBlack\nGolden", "Select", "Exit");
        GivePlayerMoney(playerid, -650);
    }
    else 
    { 
        Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    }
    return 1;
}

Dialog:DIALOG_RESPRAYSPOILER(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!response)
    {
        Dialog_Show(playerid, DIALOG_MG, DIALOG_STYLE_LIST, "Mod Garage", "Rims\nSpoilers\nStickers\nRespray spoiler\nNeons\nRemove mods\nRemove spoilers", "Select", "Exit");
    }
    else
    {
        if(GetPlayerMoney(playerid) < 650 || !IsValidDynamicObject(SPOILER_OBJECT[vehicleid])) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Cannot color your spoiler at the moment!", MESSAGE_CASE_SERVER),
        Dialog_Show(playerid, DIALOG_RESPRAYSPOILER, DIALOG_STYLE_LIST, "Spoiler Colors.","Red\nGreen\nBlue\nWhite\nBlack\nGolden", "Select", "Exit");
        switch(listitem)
        {
            case 0:
            {
                SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, -1, "none", "none",0xFFFF0000 );
            }
            case 1:
            {
                SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, -1, "none", "none",0xFF00FF00 );
            }
            case 2:
            {
                SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, -1, "none", "none",0xFF0000FF );
            }
            case 3:
            {
                SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, -1, "none", "none",0xFFFFFFFF );
            }
            case 4:
            {
                SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, -1, "none", "none",0xFF000000 );
            }
            case 5:
            {
                SetDynamicObjectMaterial(SPOILER_OBJECT[vehicleid], 0, -1, "none", "none",0xFF908950 );
            }
        }
        Dialog_Show(playerid, DIALOG_RESPRAYSPOILER, DIALOG_STYLE_LIST, "Spoiler Colors.","Red\nGreen\nBlue\nWhite\nBlack\nGolden", "Select", "Exit");
        GivePlayerMoney(playerid, -650);
    }
    return 1;
}

stock GetVehicleNeonColor(vehicleid)
{
    return s_VehicleNeon[vehicleid];
}

stock DestroyVehicleNeon(vehicleid)
{
    SetVehicleNeonLights(vehicleid, false), s_VehicleNeon[vehicleid] = INVALID_OBJECT_ID;
    return 1;
}