
#if defined FuelSystem_included_
    #endinput
#endif

#define FuelSystem_included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define REFUEL_TIMING 5000

static 
    Vehicles_Fuel[MAX_VEHICLES] = {100, ...}, 
    Vehicles_Intervals[MAX_VEHICLES], 
    bool:Vehicles_Turn[MAX_VEHICLES char] = {true, ...}, 
    Player_LastVeh[MAX_PLAYERS], 
    PlayerText:Fuel_TDraw[MAX_PLAYERS], 
    Vehicles_Timer,
    bool:Refueling[MAX_PLAYERS char],
    bool:vRefueling[MAX_VEHICLES char],
    Refuel_Timer[MAX_PLAYERS],
    bool:fuelSwitch[MAX_PLAYERS char];

forward UpdateFuelMeter(playerid, vehicleid);
public UpdateFuelMeter(playerid, vehicleid)
{
    new Fuel_String[120];

    if(fuelSwitch{playerid})
    {
        if(Vehicles_Fuel[vehicleid] ==100)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~--------~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=100 && Vehicles_Fuel[vehicleid] >=90)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~-------~w~-~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=89 && Vehicles_Fuel[vehicleid] >=80)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~------~w~--~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=79 && Vehicles_Fuel[vehicleid] >=70)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~-----~w~---~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=69 && Vehicles_Fuel[vehicleid] >=60)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~----~w~----~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=59 && Vehicles_Fuel[vehicleid] >=50)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~---~w~-----~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=49 && Vehicles_Fuel[vehicleid] >=40)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~--~w~------~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=39 && Vehicles_Fuel[vehicleid] >=30)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~b~-~w~-------~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=29 && Vehicles_Fuel[vehicleid] >=20)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~--~w~I~w~--------~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=19 && Vehicles_Fuel[vehicleid] >=10)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~b~-~w~-I--------~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] <=9 && Vehicles_Fuel[vehicleid] >=1)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E-~w~--I--------~g~-F", Vehicles_Fuel[vehicleid]);
        }
        else if(Vehicles_Fuel[vehicleid] ==0)
        {
            format(Fuel_String, sizeof(Fuel_String), "~r~E---I--------~g~-F", Vehicles_Fuel[vehicleid]);
        }
    }
    else
    {
        format(Fuel_String, sizeof(Fuel_String), "~g~Fuel:~w~%d", Vehicles_Fuel[vehicleid]);
    }
    
    PlayerTextDrawSetString(playerid, Fuel_TDraw[playerid], Fuel_String);
    PlayerTextDrawHide(playerid, Fuel_TDraw[playerid]);
    PlayerTextDrawShow(playerid, Fuel_TDraw[playerid]);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    Player_LastVeh[playerid] = INVALID_VEHICLE_ID;
    if(Refueling{playerid}) CancelRefueling(playerid);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)  
{
    if(Refueling{playerid}) CancelRefueling(playerid);
    return 1;
}

hook OnGameModeInit()
{
    Vehicles_Timer = SetTimer("Vehicles_FuelTimer", 1000, true);
    foreach(new x: Vehicle)
    {
        Vehicles_Turn{x} = true;
        if(IsValidVehicle(x))
        {
            SetVehicleParamsEx(x, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
        }
    }
    return 1;
}

hook OnGameModeExit()
{
    KillTimer(Vehicles_Timer);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    Fuel_TDraw[playerid] = CreatePlayerTextDraw(playerid, 245.999969, 415.659271, " ");
	PlayerTextDrawLetterSize(playerid, Fuel_TDraw[playerid], 0.635333, 2.085333);
    PlayerTextDrawAlignment(playerid, Fuel_TDraw[playerid], 1);
    PlayerTextDrawColor(playerid, Fuel_TDraw[playerid], 16711935);
    PlayerTextDrawSetShadow(playerid, Fuel_TDraw[playerid], 0);
    PlayerTextDrawSetOutline(playerid, Fuel_TDraw[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, Fuel_TDraw[playerid], 50);
    PlayerTextDrawFont(playerid,  Fuel_TDraw[playerid], 2);
    PlayerTextDrawSetProportional(playerid,  Fuel_TDraw[playerid], 1);
    return 1;
}

forward Vehicles_FuelTimer();
public Vehicles_FuelTimer()
{
    new engine, lights, alarm, doors, bonnet, boot, objective;
    foreach(new x: Vehicle)
    {
        if(!IsValidVehicle(x) || IsVehicleNotGasable(x) || vRefueling{x}) continue;
    

        if(Vehicles_Turn{x})
        {
            GetVehicleParamsEx(x, engine, lights, alarm, doors, bonnet, boot, objective);

            if(engine && Vehicles_Intervals[x] < 15)
            {
                Vehicles_Intervals[x]++;
            }

            if(Vehicles_Intervals[x] == 15 && Vehicles_Fuel[x] != 1)
            {
                Vehicles_Fuel[x]--;
                UpdateFuelMeterEx(x);
                Vehicles_Intervals[x] = 0;
            }

            if(Vehicles_Fuel[x] == 1)
            {
                Vehicles_Fuel[x] = 0;
                Vehicles_Turn{x} = false;
                Vehicles_Intervals[x] = 0;
                SetVehicleParamsEx(x, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
            }
        }
        else
        {
            if(Vehicles_Fuel[x] > 1) 
            {
                Vehicles_Turn{x} = true;
                Vehicles_Intervals[x] = 0;
                return 0;
            }
            if(Vehicles_Intervals[x] < 60*30)
            {
                Vehicles_Intervals[x]++;
            }
            else
            {
                Vehicles_Intervals[x] = 0;
                Vehicles_Fuel[x] = 100;
                Vehicles_Turn{x} = true;
            }
        }
    }
    return 1;
}

cmd:switchfuel(playerid)
{
    fuelSwitch{playerid} = !fuelSwitch{playerid};
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Fuel style has been switched successfully!", MESSAGE_CASE_GAS);
    return 1;
}

static UpdateFuelMeterEx(vehicleid)
{
    new driver_id = GetVehicleDriver(vehicleid);
    if(driver_id != INVALID_PLAYER_ID && IsPlayerConnected(driver_id))
    {
        UpdateFuelMeter(driver_id, vehicleid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(!IsPlayerPaused(playerid))
    {
        if(newstate == PLAYER_STATE_DRIVER)
        {
            Player_LastVeh[playerid] = GetPlayerVehicleID(playerid);
            new engine, lights, alarm, doors, bonnet, boot, objective;
            GetVehicleParamsEx(Player_LastVeh[playerid], engine, lights, alarm, doors, bonnet, boot, objective);

            if(!IsVehicleNotGasable(Player_LastVeh[playerid])) ShowFuelMeter(playerid, Player_LastVeh[playerid]);
            else SetVehicleParamsEx(Player_LastVeh[playerid], VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
        }
        else if(oldstate == PLAYER_STATE_DRIVER)
        {
            HideFuelMeter(playerid, Player_LastVeh[playerid]);
            if(Refueling{playerid}) CancelRefueling(playerid);
        }
    }
    return 1;
}

stock bool:IsVehicleUseable(vehicleid)
    return (Vehicles_Turn{vehicleid});

static ShowFuelMeter(playerid, vehicleid)
{
    UpdateFuelMeter(playerid, vehicleid);
    PlayerTextDrawShow(playerid, Fuel_TDraw[playerid]);
    return 1;
}

stock HideFuelMeter(playerid, vehicleid)
{
    UpdateFuelMeter(playerid, vehicleid);
    PlayerTextDrawHide(playerid, Fuel_TDraw[playerid]);
    return 1;
}

stock IsVehicleNotGasable(vehicleid)
{
    switch(GetVehicleModel(vehicleid))
    {
        case 520, 425, 447, 449, 537, 510, 509, 481, 476, 497, 430, 446, 452, 453, 454, 472, 473, 484, 493, 595, 513, 487, 592, 519, 593: return 1;
    }
    return 0;
}

stock GetVehicleDriver(vehicleid)
{
    foreach(new i: Player)
    {
        if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER)
        {
            return i;
        }
    }    
    return INVALID_PLAYER_ID;
}

#define MAX_FUELCAN_SIZE 20
CMD:getfuel(playerid)
{
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be on foot to fill your can!", MESSAGE_CASE_GAS);
    if(!IsPlayerAtFuelStation(playerid)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be near a gas station!", MESSAGE_CASE_GAS);
    if(GetPlayerFuelCan(playerid) == MAX_FUELCAN_SIZE) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Your fuel can is already maxed out!", MESSAGE_CASE_GAS);

    new outcome = MAX_FUELCAN_SIZE - GetPlayerFuelCan(playerid);
    new outcome2 = outcome * ReturnGasPrice();

    if(GetPlayerMoney(playerid) < outcome2) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough cash!", MESSAGE_CASE_GAS);
    
    GivePlayerMoney(playerid, -outcome2);
    SetPlayerFuelCan(playerid, MAX_FUELCAN_SIZE);

    new string[STRING_SIZE_LARGE];
    format(string, sizeof string, "Fuel can filled, current fuel can contains: %d, price paid: %d", GetPlayerFuelCan(playerid), outcome2);
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_GAS);
    return 1;
}

CMD:usecan(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(Refueling{playerid}) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You are currently refueling!", MESSAGE_CASE_GAS);
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to be in a vehicle!", MESSAGE_CASE_GAS);
    if(Vehicles_Fuel[vehicleid] == 100) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't need to refuel at the moment!", MESSAGE_CASE_GAS);
    if(GetPlayerFuelCan(playerid) == 0) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough fuel in your can!", MESSAGE_CASE_GAS);

    new outcome = 100 - Vehicles_Fuel[vehicleid];
    new outcome2 = 0;

    if(GetPlayerFuelCan(playerid) - outcome < 0)
        Vehicles_Fuel[vehicleid] += GetPlayerFuelCan(playerid),
        SetPlayerFuelCan(playerid, 0);

    else if(GetPlayerFuelCan(playerid) - outcome > 0)
        outcome2 = GetPlayerFuelCan(playerid) - outcome,
        SetPlayerFuelCan(playerid, outcome2),
        Vehicles_Fuel[vehicleid] = 100;

    else if(GetPlayerFuelCan(playerid) - outcome == 0)
    {
        SetPlayerFuelCan(playerid, 0);
        Vehicles_Fuel[vehicleid] = 100;
    }

    new string[STRING_SIZE_LARGE];
    format(string, sizeof string, "Fuel can processed, current fuel can contains: %d, current vehicle fuel: %d", GetPlayerFuelCan(playerid), Vehicles_Fuel[vehicleid]);
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_GAS);
    return 1;
}

CMD:refuel(playerid)
{
    if(Refueling{playerid}) return 0;
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 0;
    if(!IsPlayerAtFuelStation(playerid) && GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return 0;

    new vehicleid = GetPlayerVehicleID(playerid);

    if(Vehicles_Fuel[vehicleid] == 100) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't need to refuel at the moment!", MESSAGE_CASE_GAS);

    new outcome = 100 - Vehicles_Fuel[vehicleid];
    new outcome2 = outcome * ReturnGasPrice();

    if(GetPlayerMoney(playerid) < outcome2) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough cash!", MESSAGE_CASE_GAS);
    
    GivePlayerMoney(playerid, -outcome2);

    Refueling{playerid} = true;
    vRefueling{vehicleid} = true;
    TogglePlayerControllable(playerid, false);
    
    GameTextForPlayer(playerid, "Refueling...", REFUEL_TIMING, 5);
    Refuel_Timer[playerid] = SetTimerEx("CancelRefuelingEx", REFUEL_TIMING, false, "iii", playerid, outcome2, vehicleid);
    return 1;
}

forward CancelRefuelingEx(playerid, fuelprice, vehicleid);

public CancelRefuelingEx(playerid, fuelprice, vehicleid)
{
    KillTimer(Refuel_Timer[playerid]);
    
    Refueling{playerid} = false;
    vRefueling{vehicleid} = false;

    TogglePlayerControllable(playerid, true);

    new string[STRING_SIZE_MEDIUM];
    format(string, sizeof string, "Refuel successful, price: %d", fuelprice);
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_GAS);
    Vehicles_Fuel[vehicleid] = 100;
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
    return 1;
}

static CancelRefueling(playerid)
{
    KillTimer(Refuel_Timer[playerid]);
    
    Refueling{playerid} = false;
    vRefueling{GetPlayerVehicleID(playerid)} = false;
    return 1;
}

static IsPlayerAtFuelStation(playerid)
{
    if(PlayerToPoint(10.0,playerid,1004.0070,-939.3102,42.1797) || PlayerToPoint(10.0,playerid,1944.3260,-1772.9254,13.3906))
    {//LS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-90.5515,-1169.4578,2.4079) || PlayerToPoint(10.0,playerid,-1609.7958,-2718.2048,48.5391))
    {//LS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,655.5993,-564.9833,16.3359) || PlayerToPoint(10.0,playerid,3714.6628,522.0750,10.7310))
    {//LS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,1004.0070,-939.3102,42.1797) || PlayerToPoint(10.0,playerid,1944.3260,-1772.9254,13.3906))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-1609.7958,-2718.2048,48.5391) || PlayerToPoint(10.0,playerid,-90.5515,-1169.4578,2.4079))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-2029.4968,156.4366,28.9498) || PlayerToPoint(10.0,playerid,-2408.7590,976.0934,45.4175))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-1676.6323,414.0262,6.9484) || PlayerToPoint(10.0,playerid,-2243.9629,-2560.6477,31.8840))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,2202.2349,2474.3494,10.5258) || PlayerToPoint(10.0,playerid,614.9333,1689.7418,6.6968))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-1328.8250,2677.2173,49.7665) || PlayerToPoint(10.0,playerid,70.3882,1218.6783,18.5165))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-2029.4968,156.4366,28.9498) || PlayerToPoint(10.0,playerid,-2408.7590,976.0934,45.4175))
    {//SF
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-2243.9629,-2560.6477,31.8841) || PlayerToPoint(10.0,playerid,-1676.6323,414.0262,6.9484))
    {//Between LS and SF
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,2202.2349,2474.3494,10.5258) || PlayerToPoint(10.0,playerid,614.9333,1689.7418,6.6968))
    {//LV
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-1328.8250,2677.2173,49.7665) || PlayerToPoint(10.0,playerid,70.3882,1218.6783,18.5165))
    {//LV
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,2113.7390,920.1079,10.5255) || PlayerToPoint(10.0,playerid,2640.3997,1115.1472,10.5930))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,1595.8685,2201.7771,10.5911) || PlayerToPoint(10.0,playerid,2146.6772,2749.3394,10.5925))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,1388.5361,1496.2334,10.5926) || PlayerToPoint(10.0,playerid,1763.8405,-2539.2888,13.3183))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,-1464.4287,1863.5211,32.4067) || PlayerToPoint(10.0,playerid,-1657.7621,-313.3628,13.9160))
    {//FUELGAS
        return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid,5.0,-759.65210, 511.66989, 1371.57507))
    {//newlib
    return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid,5.0,-2196.6179,1027.3286,79.6674))
    {//unadded izorx
    return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid,5.0,-2185.3457,1027.4388,79.7132))
    {//unadded izorx
    return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid,3.0,3395.4934,-779.6038,7.8688))
    {//decasas 2
    return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid,3.0,3395.4941,-767.2846,7.8688))
    {//decasas 1
    return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid,3.0,1421.9811,2853.0291,10.8203))
    {//EmsStation
    return 1;
    }
    else if(PlayerToPoint(10.0,playerid,1383.7537,461.6335,19.8969) || PlayerToPoint(10.0,playerid,-403.9550,441.2943,17.7999))
    {//FUELGAS
        return 1;
    }
    else if(PlayerToPoint(10.0,playerid,2113.7390,920.1079,10.5255) || PlayerToPoint(10.0,playerid,-1327.7218,2678.8723,50.0625))
    {//LV
        return 1;
    }
	return 0;
}

static PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    new Float:oldposx, Float:oldposy, Float:oldposz;
    new Float:tempposx, Float:tempposy, Float:tempposz;
    GetPlayerPos(playerid, oldposx, oldposy, oldposz);
    tempposx = (oldposx -x);
    tempposy = (oldposy -y);
    tempposz = (oldposz -z);

    if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
        return 1;
	return 0;
}