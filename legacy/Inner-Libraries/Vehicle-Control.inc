
#if defined VehicleControlling_included_
    #endinput
#endif

#define VehicleControlling_included_
#define KEY_Engine           KEY_ANALOG_UP+KEY_HANDBRAKE
#define KEY_Lights           KEY_ANALOG_DOWN+KEY_HANDBRAKE

#include <YSI_Coding\y_hooks>//Credits to Y_Less
new playerPlate[MAX_PLAYERS][9];
#define PLATE_CHANGE_CASH 500

CMD:plate(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 7.0, -2097.97, 488.81, 35.85)) 
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be in a plate garage!", MESSAGE_CASE_SERVER);

    if(!IsPlayerInAnyVehicle(playerid)) 
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be in a vehicle!", MESSAGE_CASE_SERVER);
    
    if(GetPlayerMoney(playerid) < PLATE_CHANGE_CASH) 
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough cash ($500)!", MESSAGE_CASE_SERVER);

    Dialog_Show(playerid, DIALOG_PLATEMAIN, DIALOG_STYLE_LIST, "Select color", "{FF0000}Red\n{00FF00}Green\n{0000FF}Blue\n{FFFF00}Yellow\n{00FFFF}Cyan\n{FF00FF}Pink\n{F0F0F0}White\n{0F0F0F}Black", "{00FF00}Choose", "{FF0000}Cancel");

    return 1;
}

Dialog:DIALOG_PLATEMAIN(playerid, response, listitem, inputtext[])
{        
	if(response)
	{
        switch(listitem)
        {
            case 0: {
                playerPlate[playerid] =  "{FF0000}";//red
            }
            case 1: {
                playerPlate[playerid] =  "{00FF00}";//green
            }
            case 2: {
                playerPlate[playerid] =  "{0000FF}";//blue
            }
            case 3: { 
                playerPlate[playerid] =  "{FFFF00}";//yellow
            }
            case 4: { 
                playerPlate[playerid] =  "{00FFFF}";//cyan
            }
            case 5: { 
                playerPlate[playerid] =  "{FF00FF}";//pink
            }
            case 6: { 
                playerPlate[playerid] =  "{F0F0F0}";//white
            }
            case 7: { 
                playerPlate[playerid] =  "{0F0F0F}";//black
            }
        }
        
        Dialog_Show(playerid, DIALOG_PLATETEXT, DIALOG_STYLE_INPUT, "Type in text", "Enter the plate name [4-8 Characters]", "Done", "");
	}
	return 1;
}

Dialog:DIALOG_PLATETEXT(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        if(strlen(inputtext) > 8 || strlen(inputtext) < 4) 
        {
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Text needs to be 4-8 characters long!", MESSAGE_CASE_SERVER);
            return Dialog_Show(playerid, DIALOG_PLATETEXT, DIALOG_STYLE_INPUT, "Type in text", "Enter the plate name [4-8 Characters]", "Done", "");
        }
        new plateString[8+9+1], vehicleid = GetPlayerVehicleID(playerid);
        format(plateString, sizeof plateString, "%s%s", playerPlate[playerid], inputtext);
        SetVehicleNumberPlate(vehicleid, plateString);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Plate number set!", MESSAGE_CASE_SERVER);
        new Float:x, Float:y, Float:z;
        GetVehiclePos(vehicleid, x, y, z);
        SetVehicleToRespawn(vehicleid);
        PutPlayerInVehicle(playerid, vehicleid, 0);
        SetVehiclePos(vehicleid, x, y, z);
        SetVehicleZAngle(vehicleid, 1.5875);
        SetCameraBehindPlayer(playerid);
        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
    }
	return 1;
}

CMD:engine(playerid)
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 0;

    new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid;

    vehicleid = GetPlayerVehicleID(playerid);

    if(!IsVehicleUseable(vehicleid))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Vehicle is out of fuel!", MESSAGE_CASE_SERVER);
        return 0;
    }
    
    if(IsVehicleNotGasable(vehicleid)) 
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Vehicle does not not have the ability to be controlled!", MESSAGE_CASE_SERVER);
        return 0;
    }

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if(engine)
    {
        SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Engine {E31919}off!", MESSAGE_CASE_SERVER);
    }
    else
    {
        SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Engine {2F991A}on!", MESSAGE_CASE_SERVER);
    }

    return 1;
}

CMD:lights(playerid)
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 0;

    new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid;

    vehicleid = GetPlayerVehicleID(playerid);

    if(!IsVehicleUseable(vehicleid))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Vehicle is out of fuel!", MESSAGE_CASE_SERVER);
        return 0;
    }
    
    if(IsVehicleNotGasable(vehicleid)) 
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Vehicle does not not have the ability to be controlled!", MESSAGE_CASE_SERVER);
        return 0;
    }

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if(lights)
    {
        SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Lights {E31919}off!", MESSAGE_CASE_SERVER);
        if(IsPlayerOnDuty(playerid) && IsVehicleSpecialCopCar(vehicleid))
        {
            HideCopLights(vehicleid);
            if(GetVehicleNeonColor(vehicleid) != INVALID_OBJECT_ID)
                SetVehicleNeonLights(vehicleid, false);
        }
    }

    else
    {
        SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Lights {2F991A}on!", MESSAGE_CASE_SERVER);
        if(IsPlayerOnDuty(playerid) && IsVehicleSpecialCopCar(vehicleid))
        {
            ShowCopLights(vehicleid);
            if(GetVehicleNeonColor(vehicleid) != INVALID_OBJECT_ID)
                SetVehicleNeonLights(vehicleid, true, GetVehicleNeonColor(vehicleid));
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(KEY_PRESSED(KEY_Engine))
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 0;

        new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid;

        vehicleid = GetPlayerVehicleID(playerid);

        if(!IsVehicleUseable(vehicleid) || IsVehicleNotGasable(vehicleid)) return 0;

        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

        if(engine)
            SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
        else
            SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
    }
    
    if(KEY_PRESSED(KEY_Lights))
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 0;

        new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid;

        vehicleid = GetPlayerVehicleID(playerid);

        if(!IsVehicleUseable(vehicleid) || IsVehicleNotGasable(vehicleid)) return 0;

        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

        if(lights)
        {
            SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
            if(IsPlayerOnDuty(playerid) && IsVehicleSpecialCopCar(vehicleid))
                HideCopLights(vehicleid);
            if(GetVehicleNeonColor(vehicleid) != INVALID_OBJECT_ID)
                SetVehicleNeonLights(vehicleid, false);
        }
        else
        {
            SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
            if(IsPlayerOnDuty(playerid) && IsVehicleSpecialCopCar(vehicleid))
                ShowCopLights(vehicleid);
            if(GetVehicleNeonColor(vehicleid) != INVALID_OBJECT_ID)
                SetVehicleNeonLights(vehicleid, true, GetVehicleNeonColor(vehicleid));
        }
    }

    if(KEY_PRESSED(KEY_SUBMISSION))
 	{
        if (GetPlayerWantedLevel(playerid) >= 1 || IsPlayerInEvent(playerid))
        {
            //NOTHING
        }
        else if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            new Float:Angle;
            GetVehicleZAngle(vehicleid, Angle);
            if(IsVehicleUpsideDown(vehicleid))
            {
                SetVehicleHealth(vehicleid, 1100.0);
                RepairVehicle(vehicleid);
                AddVehicleComponent(vehicleid, 1010);
                SetVehicleZAngle(vehicleid, Angle);
            }
            else
            {
                RepairVehicle(vehicleid);
                SetVehicleHealth(vehicleid, 1000.0);
                AddVehicleComponent(vehicleid, 1010);
            }
        }
    }
    return 1;
}

stock IsVehicleUpsideDown(vehicleid)
{
    new Float:quat_w, Float:quat_x, Float:quat_y, Float:quat_z;
    GetVehicleRotationQuat(vehicleid, quat_w, quat_x, quat_y, quat_z);
    new Float:y = atan2(2*((quat_y*quat_z)+(quat_w*quat_x)), (quat_w*quat_w)-(quat_x*quat_x)-(quat_y*quat_y)+(quat_z*quat_z));
    return (y > 90 || y < -90);
}

hook OnVehicleCreated(vehicleid)
{
    SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
    SetVehicleNumberPlate(vehicleid, "{0F0F0F}RogueDrifter" );
    return 1;
}