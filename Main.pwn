//RDZ Script

#include <a_samp>//Credits to SA-MP team.
//#define RDZ_DEBUG_MODE
#define ENABLE_037R2_VERESION
//#define CHRISTMAS_MOD

#undef MAX_PLAYERS
#define MAX_PLAYERS 100

#define MAX_REMOVED_OBJECTS (679) // Value of maximum objects which can be removed. Set your own value.

#if !defined ENABLE_037R2_VERESION
    #include <Inner-Libraries\Custom-Skin-Fix>//Credits to RogueDrifter
    #include <Constant-Libraries\Fix-Classes>//Credits to Locky_
#endif

#define MAX_VIRTUAL_WORLDS 	2147483647
#define WEAPON_FISTS 0

native IsValidVehicle(vehicleid);
native gpci(playerid, string[], length);



#define RDZ_OFFICIAL_COLOR 0xAA3333AA
#define RDZ_OOC_CHAT_COLOR 0xE6E6E6E6
#define RDZ_COLOR_WANTED 0xFF0000FF
#define REPORT_TYPE_HIJACK 0
#define REPORT_TYPE_MURDER 1
#define NORMAL_VIRTUAL_WORLD 0
#define NORMAL_INTERIOR 0
#define CITIES_WORLD 99
#define CITIES_WORLD_INVALID 99
#define MOTELROOM_VIRTUALWORLD 2000
#define MOTELROOM_INTERIOR 12

#define CMD_PREFIX "!" 
#define BOT_CHANNEL "gamecommands" 
#define BOT_NAME "Rogue[BOT]" 
#define CHANNEL_ID "000000000000" //Insert your channel id to control commands from discord

#define CADET_RANK_ID 0
#define OFFICER_RANK_ID 1
#define SERGEANT_RANK_ID 2
#define LIEUTENANT_RANK_ID 3
#define CAPTAIN_RANK_ID 4
#define CHIEF_RANK_ID 5

#define ADMIN_LEVEL_ONE 1
#define ADMIN_LEVEL_TWO 2
#define ADMIN_LEVEL_THREE 3
#define ADMIN_LEVEL_FOUR 4
#define ADMIN_LEVEL_FIVE 5
#define ADMIN_LEVEL_SIX 6 
#define ADMIN_LEVEL_SEVEN 7

#define INVALID_JOB_ID 0
#define JOB_ID_COP 1
#define JOB_ID_DRUGDEALER 2

#define STRING_SIZE_SMALL 40
#define STRING_SIZE_MEDIUM 80
#define STRING_SIZE_LARGE 128
#define STRING_SIZE_QUERY 300

#define VEHICLE_SEAT_DRIVER 0
#define VEHICLE_SEAT_FRONT_PASSENGER 1
#define VEHICLE_SEAT_BACKLEFT_PASSENGER 2
#define VEHICLE_SEAT_BACKRIGHT_PASSENGER 2

#define MESSAGE_CASE_ADMIN  0
#define MESSAGE_CASE_PAYCHECK   1
#define MESSAGE_CASE_VIP    2
#define MESSAGE_CASE_DEATH  3
#define MESSAGE_CASE_DRIFT  4
#define MESSAGE_CASE_SERVER 5
#define MESSAGE_CASE_EMPTY  6
#define MESSAGE_CASE_GAS    7
#define MESSAGE_CASE_JARVIS 8
#define MESSAGE_CASE_JANITOR    9  
#define MESSAGE_CASE_GENDER 10
#define MESSAGE_CASE_ADMINSCHAT 11
#define MESSAGE_CASE_VIPSCHAT 12
#define MESSAGE_CASE_COPS 13
#define MESSAGE_CASE_NULL 14

#define CASE_LOGIN 0
#define CASE_REGISTER 1

#define RDZ_WORLD_TIME 0
#define RDZ_WORLD_WEATHER 5

#define MAX_MISC_TD 2
#define MAX_TEMP_TD 2

#define TIME_SECONDS 0
#define TIME_MINUTES 1
#define TIME_HOURS 2

//TELECAR STUFF
#define FIRST_TIME 0
#define SECOND_TIME 1

#define NRG_MODEL 522
#define NRG_PRICE 250000
#define ELEGY_MODEL 562
#define ELEGY_PRICE 600000
#define BANSHEE_MODEL 429
#define BANSHEE_PRICE 390000
#define BOBCAT_MODEL 422
#define BOBCAT_PRICE 180000
#define STALLION_MODEL 439
#define STALLION_PRICE 120000
#define TURISMO_MODEL 451
#define TURISMO_PRICE 500000
#define PCJ_MODEL 461
#define PCJ_PRICE 90000
#define BMX_MODEL 481
#define BMX_PRICE 50000
#define BURRITO_MODEL 482
#define BURRITO_PRICE 100000
#define SUPERGT_MODEL 506
#define SUPERGT_PRICE 420000
#define HERMES_MODEL 474
#define HERMES_PRICE 200000
//END:TELECAR STUFF

#define KEY_PRESSED(%0) \
                    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#include <Constant-Libraries\crashdetect>//Credits to zeex
//-- Legacy --//
//#include <Constant-Libraries\fixes.inc>//Credits to Y_Less and every other contributor on the repo - Too many errors with the fixes need to single them out
//#include <Constant-Libraries\PawnPlus>//Credits to  IllidanS4 - Causing sampgdk errors
//#include <Constant-Libraries\colandreas>// Credits to Pottus, chris420, slice, crayder, codectile, uint32.- Cannot use due to folder issues
//#include <Constant-Libraries\YSF>//Kurta's version, credits to everyone who contributed to this over the repo. - Compatibility issues

#include <YSI_Coding\y_va>//Credits to Y_LESS

#include <Constant-Libraries\memory.inc> //Credits to BigETI

#include <Constant-Libraries\PreviewModelDialog>//Credits to Gammix

#include <Constant-Libraries\Humanize> //Credits to Codeah

#include <Constant-Libraries\streamer> // Credits to Incognito

#include <Constant-Libraries\easyDialog> // Credits to Emmet_

#include <YSI_DATA\y_iterate>//Credits to Y_Less

#include <Constant-Libraries\MapFixes> //Credits to OstGot

#define KICKBAN_FIX_WAIT 250 //In ms
#include <Inner-Libraries\kickbanfix>//Credits to RogueDrifter

#include <Constant-Libraries\Pawn.CMD>//Credits to urShadow

#include <Constant-Libraries\sscanf2>//Credits to Y_Less

#define BCRYPT_COST 12

#include <Constant-Libraries\bcrypt>//Credits to Johnson_boy
#include <Constant-Libraries\discordconnect>//Credits to maddinat0r
#include <Constant-Libraries\dcc>// Credits to Inn0cent

//-- Components --//

#if !defined ENABLE_037R2_VERESION
    #include <Constant-Libraries\LC-Map>//Credits to Kalcor for converting this
    #include <Constant-Libraries\VC-Map>//Credits to Kalcor for converting this
#endif

#if defined CHRISTMAS_MOD
    #include <Constant-Libraries\AllObjects>//Credits to Pottus
    #include <Constant-Libraries\modelsizes>//Credits to Y_Less
#endif

#include <Constant-Libraries\vSync>//Credits to RIDE2DAY
#include <Constant-Libraries\strlib>//Credits to Slice and all the other contributors over the git repo
#include <Constant-Libraries\Compat>//Credits to Adrian Graber
#include <Constant-Libraries\Pawn.Regex>//Credits to urShadow
#include <Constant-Libraries\SpikeStrip>//Credits to whoever made this because it wasn't me.

#include <Constant-Libraries\actor_plus>//Credits to Dayrion
#include <Constant-Libraries\Pawn.RakNet>//Credits to urShadow
#include <RDZ-Libraries\RDZ-Regex>//Credits to RogueDrifter for the regular expressions, urShadow for the plugin

#include <RDZ-Libraries\RDZ-AC> //Credits to RogueDrifter
#include <Inner-Libraries\Frequents>//Credits to RogueDrifter

#include <Constant-Libraries\Components>// Credits to Pawnoholic and ziggi
#include <RDZ-Libraries\RDZ-Init>//Credits to RogueDrifter

#define REWIND_FULLY_SYNCED_TIMER 10
#define SYNCEED_REWIND_BUFFER 250
#include <Inner-Libraries\Rewind>//Credits to RogueDrifter

#define RTL_MAX_PLAYER_RANGE 90.000
#define MAX_RTLIGHTS 5
#include <Inner-Libraries\Tech_Lights>//Credits to RogueDrifter


#include <Inner-Libraries\AFK-Checker> //Credits to RogueDrifter


#include <Constant-Libraries\customtags>//Credits to Bork and Nyzenic

#if defined CHRISTMAS_MOD
    #include <Inner-Libraries\Christmas-Mode>//Credits to Correlli for the tutorial 
    #include <Inner-Libraries\Christmas-Addons>//Credits to Zh3ro for snowman, Kwarde for snow
#endif

#include <RDZ-Libraries\RDZ-DrugDealer> //Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-MG> //Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-Misc>//Credits to RogueDrifter

#include <RDZ-Libraries\RDZ-ADMIN> //Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-VIP> //Credits to RogueDrifter
#include <Constant-Libraries\spec>//Credits to Gammix, edited by RogueDrifter

#include <RDZ-Libraries\RDZ-Map>//Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-Cops>//Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-TC>//Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-JS>//Credits to RogueDrifter

#include <Inner-Libraries\Fuel-System> // Credits to RogueDrifter
#include <Inner-Libraries\Vehicle-Control> // Credits to RogueDrifter

#include <Constant-Libraries\Drifting>//Credits to iKarim, fixed exit vehicle bug by RogueDrifter.
#include <Inner-Libraries\Drift-Counter>//Credits to RogueDrifter
#include <Inner-Libraries\Drift-Battle>//Credits to RogueDrifter

#include <RDZ-Libraries\RDZ-Inners>//Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-Interiors>//Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-Cmds> //Credits to RogueDrifter

#include <RDZ-Libraries\RDZ-TDM>//Credits to RogueDrifter
#include <RDZ-Libraries\RDZ-MKO>//Credits to RogueDrifter

#include <RDZ-Libraries\RDZ-Reserved>//Credits to RogueDrifter
//--//

#include <YSI_Coding\y_hooks>//Credits to Y_Less

main()
{
    print("Loaded server");
}

public OnGameModeInit()
{
    new r;
    foreach(new x:Vehicle)
    {
        r++;
    }
    printf("Total vehicles: %d", r);
    return 1;
}

public OnPlayerConnect(playerid)
{
    if(IsPlayerCompat(playerid))
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Your version doesn't match the server's version", MESSAGE_CASE_SERVER);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You'll still be able to play but you won't be able to experience some features.", MESSAGE_CASE_SERVER);   
    }
    return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) 
{ 
    if(result == -1) 
    { 
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "SERVER: Unknown command.", MESSAGE_CASE_EMPTY); 
        return 0; 
    } 
    return 1; 
} 

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
    if(!IsPlayerLoggedIn(playerid)) return 0;

    if( (IsPlayerMuted(playerid) || IsPlayerInJail(playerid) || IsPlayerInTDM(playerid)) && !(GetPlayerADMIN(playerid) != 7) )
    {
        return 0;
    }

    return 1;
}

#if !defined ENABLE_037R2_VERESION
    public OnPlayerRequestDownload(playerid, type, crc)
    {
        return 1;
    }

    public OnPlayerFinishedDownloading(playerid, virtualworld)
    {
        rTDM_Player[playerid][rTdmPTicks] = gettime();
        rAFK_Player[playerid][rAfkPTicks] = gettime();
        return 1;
    }
#endif

/* Scripts using timers:

1- RDZ-Misc
2- Fuel-system
3- Drift-counter
4- Drift-Battle
5- Kickban fix
6- nametags
*/

