#if 	defined 	_drift_included
	#endinput
#endif

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define _drift_included

#define Drift:: Drift_

// constants
#define MIN_DRIFT_ANGLE     (12.0)   // minimum drift angle to start a drift
#define MAX_DRIFT_ANGLE     (80.0)  // maximum drift angle to start a drift
#define MIN_DRIFT_SPEED     (50.0)  // minimum speed to start a drift

#define DRIFT_PROCESS_INTERVAL    (250)     // delay interval between each tick in ms
#define DRIFT_TIMEOUT_INTERVAL    (10)       // how much ticks before a drift ends after the player stops drifting

// drift ending reasons
enum {
    DRIFT_END_REASON_TIMEOUT, 
    DRIFT_END_REASON_DAMAGED, 
    DRIFT_END_REASON_OTHER 
}
// drift states
enum {
    DRIFT_STATE_NONE,
    DRIFT_STATE_DRIFTING
}

// option flags

enum DriftOptions: (<<= 1) {
    DRIFT_CHECK_ENABLED = 1,
    DAMAGE_CHECK_ENABLED,
}
// player drift structure
enum e_DRIFT_PLAYER_STRUCT {
    Float:  vHealth,
    Float:  startPosX,
    Float:  startPosY,
    Float:  startPosZ,

    driftState,
    startTimestamp,
    lastTimestamp,
    timeoutTicks,

    // options
    DriftOptions: playerFlags
}

// callback forwards
#if defined OnPlayerDriftStart
    forward	OnPlayerDriftStart(playerid);
#endif 

#if defined OnPlayerDriftUpdate
    forward	OnPlayerDriftUpdate(playerid, Float: drift_angle, Float: speed);
#endif

#if defined OnPlayerDriftEnd
    forward	OnPlayerDriftEnd(playerid, reason, Float: distance, time);
#endif

static g_DriftPlayers[MAX_PLAYERS][e_DRIFT_PLAYER_STRUCT];
static DriftOptions: g_DriftFlags = DRIFT_CHECK_ENABLED | DAMAGE_CHECK_ENABLED;

static Float: g_MinDriftAngle = MIN_DRIFT_ANGLE;
static Float: g_MinDriftSpeed = MIN_DRIFT_SPEED;
static g_DriftTimeoutTicks = DRIFT_TIMEOUT_INTERVAL;
 
// internal functions

static bool:IsModelDriftable(modelid)
{
    switch(modelid)
	{
		case 480: return true;
		case 533: return true;
		case 439: return true;
		case 555: return true;
		case 536: return true;
		case 575: return true;
		case 534: return true;
		case 567: return true;
		case 535: return true;
		case 566: return true;
		case 576: return true;
		case 412: return true;
		case 445: return true;
		case 504: return true;
		case 401: return true;
		case 518: return true;
		case 527: return true;
		case 542: return true;
		case 507: return true;
		case 562: return true;
		case 585: return true;
		case 419: return true;
		case 526: return true;
		case 604: return true;
		case 466: return true;
		case 492: return true;
		case 474: return true;
		case 546: return true;
		case 517: return true;
		case 410: return true;
		case 551: return true;
		case 516: return true;
		case 467: return true;
		case 426: return true;
		case 436: return true;
		case 547: return true;
		case 405: return true;
		case 580: return true;
		case 550: return true;
		case 549: return true;
		case 540: return true;
		case 491: return true;
		case 529: return true;
		case 421: return true;
		case 602: return true;
		case 496: return true;
		case 402: return true;
		case 589: return true;
		case 587: return true;
		case 565: return true;
		case 494: return true;
		case 502: return true;
		case 503: return true;
		case 411: return true;
		case 559: return true;
		case 603: return true;
		case 475: return true;
		case 558: return true;
		case 477: return true;
		case 418: return true;
		case 404: return true;
		case 479: return true;
		case 458: return true;
		case 561: return true;
	}
    return false;
}

stock bool: IsModelACar(modelid) 
{
	switch(modelid)
	{
		case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return false; // Boats.
		case 448, 461, 462, 463, 468, 471, 481, 509, 510, 521, 522, 523, 581, 586: return false; // Bikes
		case 417, 425, 447, 460, 469, 476, 487, 488, 497, 511, 512, 513, 519, 520, 548, 553, 563, 577, 592, 593: return false; // Airplanes
	}
	return true;
}

// hooked callbacks
hook OnPlayerUpdate(playerid)
{
    if(g_DriftFlags & DRIFT_CHECK_ENABLED && g_DriftPlayers[playerid][playerFlags] & DRIFT_CHECK_ENABLED)
    {
        if(GetTickDiff(GetTickCount(), g_DriftPlayers[playerid][lastTimestamp]) > DRIFT_PROCESS_INTERVAL)
        {
            new vehicleID = GetPlayerVehicleID(playerid);
            new vehicleMODEL = GetVehicleModel(vehicleID);

            if(vehicleID && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsModelACar(vehicleMODEL) && IsModelDriftable(vehicleMODEL) )
            {
                new Float: vX, Float: vY, Float: vZ;
                GetVehicleVelocity(vehicleID, vX, vY, vZ);

                new Float: angle;
                GetVehicleZAngle(vehicleID, angle);

                new Float: speed;
                speed = floatsqroot(vX*vX + vY*vY + vZ*vZ) * 180.0;
                
                new Float: direction;
                direction = atan2(vY, vX);
                direction -= 90.0;
        
                if(direction < 0) direction += 360.0;

                new Float: driftAngle;
                driftAngle = angle - floatabs(direction);

                if(driftAngle > 270.0) driftAngle -= 270.0;
                if(driftAngle < -270.0) driftAngle += 270.0;

                driftAngle = floatabs(driftAngle);
            
                switch(g_DriftPlayers[playerid][driftState])
                {
                    case DRIFT_STATE_NONE:
                    {
                        if(g_MinDriftAngle <= driftAngle <= MAX_DRIFT_ANGLE && speed >= g_MinDriftSpeed)
                        {                        
                            g_DriftPlayers[playerid][driftState] = DRIFT_STATE_DRIFTING;
                            g_DriftPlayers[playerid][startTimestamp] = gettime();

                            GetVehicleHealth(vehicleID, g_DriftPlayers[playerid][vHealth]);
                            GetPlayerPos(playerid, g_DriftPlayers[playerid][startPosX], g_DriftPlayers[playerid][startPosY], g_DriftPlayers[playerid][startPosZ]);
                            
                            #if defined OnPlayerDriftStart
                                OnPlayerDriftStart(playerid);
                            #endif
                        }
                    }
                    case DRIFT_STATE_DRIFTING:
                    {
                        if(g_DriftFlags & DAMAGE_CHECK_ENABLED && g_DriftPlayers[playerid][playerFlags] & DAMAGE_CHECK_ENABLED)
                        {
                            new Float: vehicleHealth;
                            GetVehicleHealth(vehicleID, vehicleHealth);

                            if(vehicleHealth < g_DriftPlayers[playerid][vHealth])
                            {
                                GetPlayerPos(playerid, vX, vY, vZ);

                                g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
                                g_DriftPlayers[playerid][timeoutTicks] = 0;

                                #if defined OnPlayerDriftEnd
                                    new Float: distance;
                                    distance = GetPlayerDistanceFromPoint(playerid, g_DriftPlayers[playerid][startPosX], g_DriftPlayers[playerid][startPosY], g_DriftPlayers[playerid][startPosZ]);

                                    OnPlayerDriftEnd(playerid, DRIFT_END_REASON_DAMAGED, distance, gettime() - g_DriftPlayers[playerid][startTimestamp]);
                                #endif
                            }
                        }
                        if(g_MinDriftAngle <= driftAngle <= MAX_DRIFT_ANGLE && speed >= g_MinDriftSpeed)
                        {
                            g_DriftPlayers[playerid][timeoutTicks] = 0;
                            
                            #if defined OnPlayerDriftUpdate
                                OnPlayerDriftUpdate(playerid, driftAngle, speed);
                            #endif
                        }
                        else
                        {
                            g_DriftPlayers[playerid][timeoutTicks]++;

                            if(g_DriftPlayers[playerid][timeoutTicks] >= g_DriftTimeoutTicks)
                            {
                                GetPlayerPos(playerid, vX, vY, vZ);
                                
                                g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
                                g_DriftPlayers[playerid][timeoutTicks] = 0;

                                #if defined OnPlayerDriftEnd
                                    new Float: distance;
                                    distance = GetPlayerDistanceFromPoint(playerid, g_DriftPlayers[playerid][startPosX], g_DriftPlayers[playerid][startPosY], g_DriftPlayers[playerid][startPosZ]);

                                    OnPlayerDriftEnd(playerid, DRIFT_END_REASON_TIMEOUT, distance, gettime() - g_DriftPlayers[playerid][startTimestamp]);
                                #endif
                            }
                        }
                    }
                }
            }
            g_DriftPlayers[playerid][lastTimestamp] = GetTickCount();
        }
    }
    return 1;
}
hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(g_DriftPlayers[playerid][driftState] == DRIFT_STATE_DRIFTING && oldstate == PLAYER_STATE_DRIVER)
    {
        new Float: pX, Float: pY, Float: pZ;
        GetPlayerPos(playerid, pX, pY, pZ);

        g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
        g_DriftPlayers[playerid][timeoutTicks] = 0;

        #if defined OnPlayerDriftEnd
            new Float: distance;
            distance = GetPlayerDistanceFromPoint(playerid, g_DriftPlayers[playerid][startPosX], g_DriftPlayers[playerid][startPosY], g_DriftPlayers[playerid][startPosZ]);

            OnPlayerDriftEnd(playerid, DRIFT_END_REASON_OTHER, distance, gettime() - g_DriftPlayers[playerid][startTimestamp]);
        #endif
    }
    return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    #if defined OnPlayerDriftEnd
            new Float: distance;
            distance = GetPlayerDistanceFromPoint(playerid, g_DriftPlayers[playerid][startPosX], g_DriftPlayers[playerid][startPosY], g_DriftPlayers[playerid][startPosZ]);

            OnPlayerDriftEnd(playerid, DRIFT_END_REASON_OTHER, distance, gettime() - g_DriftPlayers[playerid][startTimestamp]);
    #endif
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(g_DriftPlayers[playerid][driftState] == DRIFT_STATE_DRIFTING)
    {
        new Float: pX, Float: pY, Float: pZ;
        GetPlayerPos(playerid, pX, pY, pZ);
                
        g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
        g_DriftPlayers[playerid][timeoutTicks] = 0;   

        #if defined OnPlayerDriftEnd
            new Float: distance;
            distance = GetPlayerDistanceFromPoint(playerid, g_DriftPlayers[playerid][startPosX], g_DriftPlayers[playerid][startPosY], g_DriftPlayers[playerid][startPosZ]);

            OnPlayerDriftEnd(playerid, DRIFT_END_REASON_OTHER, distance, gettime() - g_DriftPlayers[playerid][startTimestamp]);
        #endif
    }
    return 1;
}

// option functions
stock Drift::SetMinAngle(Float: angle)
{
    if(angle < MAX_DRIFT_ANGLE)
    {
        g_MinDriftAngle = angle;
    }
}
stock Float: Drift::GetMinAngle()
{
    return g_MinDriftAngle;
}
stock Drift::SetMinSpeed(Float: speed)
{
    g_MinDriftSpeed = speed;
}
stock Float: Drift::GetMinSpeed()
{
    return g_MinDriftSpeed;
}
stock Drift::SetTimeoutTicks(ticks)
{
    g_DriftTimeoutTicks = ticks;
}
stock Drift::GetTimeoutTicks()
{
    return g_DriftTimeoutTicks;
}
stock Drift::EnableDetection(playerid = -1)
{
    if(playerid != -1 && 0 <= playerid < MAX_PLAYERS)
    {
        g_DriftPlayers[playerid][playerFlags] |= DRIFT_CHECK_ENABLED;
    }
    else g_DriftFlags |= DRIFT_CHECK_ENABLED;
}
stock Drift::DisableDetection(playerid = -1)
{
    if(playerid != -1 && 0 <= playerid < MAX_PLAYERS)
    {
        g_DriftPlayers[playerid][playerFlags] &= ~DRIFT_CHECK_ENABLED;
    }
    else g_DriftFlags &= ~DRIFT_CHECK_ENABLED;
}
stock bool: Drift::IsDetectionEnabled(playerid = -1)
{
    if(playerid != -1 && 0 <= playerid < MAX_PLAYERS)
    {
        return (g_DriftPlayers[playerid][playerFlags] & DRIFT_CHECK_ENABLED) ? true : false;
    }
    else (g_DriftFlags & DRIFT_CHECK_ENABLED) ? true : false;
}
stock Drift::EnableDamageCheck(playerid = -1)
{
    if(playerid != -1 && 0 <= playerid < MAX_PLAYERS)
    {
        g_DriftPlayers[playerid][playerFlags] |= DAMAGE_CHECK_ENABLED;
    }
    else g_DriftFlags |= DAMAGE_CHECK_ENABLED;
}
stock Drift::DisableDamageCheck(playerid = -1)
{
    if(playerid != -1 && 0 <= playerid < MAX_PLAYERS)
    {
        g_DriftPlayers[playerid][playerFlags] &= ~DAMAGE_CHECK_ENABLED;
    }
    else g_DriftFlags &= ~DAMAGE_CHECK_ENABLED;
}
stock bool: Drift::IsDamageCheckEnabled(playerid = -1)
{
    if(playerid != -1 && 0 <= playerid < MAX_PLAYERS)
    {
        return (g_DriftPlayers[playerid][playerFlags] & DAMAGE_CHECK_ENABLED) ? true : false;
    }
    else return (g_DriftFlags & DAMAGE_CHECK_ENABLED) ? true : false;
}
stock Drift::IsPlayerDrifting(playerid)
{
    return !!g_DriftPlayers[playerid][driftState];
}