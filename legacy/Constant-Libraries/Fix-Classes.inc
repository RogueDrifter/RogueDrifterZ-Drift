/*
    Fix Classes
    by Locky
*/
 #if defined FIXCLASS_Included_
   #endinput
#endif

#define FIXCLASS_Included_

new _PlayerClassesSkin[320]; // 320 is max
 
stock f_AddPlayerClass(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo) {
    new class = AddPlayerClass(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
    _PlayerClassesSkin[class] = modelid;
    return class;
}
 
#if defined _ALS_AddPlayerClass
    #undef AddPlayerClass
#else  
    #define _ALS_AddPlayerClass
#endif
#define AddPlayerClass f_AddPlayerClass
 
stock f_AddPlayerClassEx(teamid, modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo) {
    new class = AddPlayerClassEx(teamid, modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
    _PlayerClassesSkin[class] = modelid;
    return class;
}
 
#if defined _ALS_AddPlayerClassEx
    #undef AddPlayerClassEx
#else
    #define _ALS_AddPlayerClassEx
#endif
#define AddPlayerClassEx f_AddPlayerClassEx
 
public OnPlayerRequestClass(playerid, classid)
{
    if((20000 < _PlayerClassesSkin[classid] <= 30000) && (GetPlayerCustomSkin(playerid) == 0))
        SetTimerEx("TimerSetSkin", 10, false, "dd", playerid, _PlayerClassesSkin[classid]);
    return CallLocalFunction("f_OnPlayerRequestClass", "dd", playerid, classid);
}
forward f_OnPlayerRequestClass(playerid, classid);
 
#if defined _ALS_OnPlayerRequestClass
    #undef OnPlayerRequestClass
#else
    #define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass f_OnPlayerRequestClass
 
 
forward TimerSetSkin(playerid, skin);
public TimerSetSkin(playerid, skin) return SetPlayerSkin(playerid, skin);