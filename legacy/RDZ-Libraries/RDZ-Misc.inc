#if defined RDZ_MISC_Included_
   #endinput
#endif

#define RDZ_MISC_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

//ACTOR IDS:

#define ACTOR_TELECAR 0
//END: ACTOR IDS

static 
	Text:RDZ_MISCTD[MAX_MISC_TD], 
	Text:RDZ_MISCTempTD[MAX_TEMP_TD], 
	RDZ_MiscTimer, 
	ACTOR_GROUP[1], 
	GANGZONE_GROUP[2], 
	RDZ_GASPrice, 
	gPlayerWorldTimer[MAX_PLAYERS],
	Lotto_Jackpot,
	lotto_price,
	lottoTicket[MAX_PLAYERS],
	Winning_Lotto;

#define MAX_SHOP_RANGE 80.000
#define SP_TYPE_ONE 1 //SPH
#define SP_TYPE_TWO 2 //SP
#define SAFEZONE_GANG_RED 0xFF000090//SAFEZONE GANGZONE COLOR
#define POLICE_GANG_BLUE 0x0000FF90//POLICE GANGZONE COLOR
#define LOCATING_TIME 2500
#define LOTTO_DELAY_TIME 30000

enum E_CARLIST_LISTITEM
{
	E_CARLIST_CARPRICE[9],
    E_CARLIST_MODELID
};

static const CAR_LIST[][E_CARLIST_LISTITEM] =
{
    {"$600,000", ELEGY_MODEL},
    {"$250,000", NRG_MODEL},
    {"$390,000", BANSHEE_MODEL},
    {"$500,000", TURISMO_MODEL},
    {"$90,000", PCJ_MODEL},
    {"$50,000", BMX_MODEL},
    {"$120,000", STALLION_MODEL},
    {"$180,000", BOBCAT_MODEL},
    {"$100,000", BURRITO_MODEL},
    {"$420,000", SUPERGT_MODEL},
    {"$200,000", HERMES_MODEL}
};

hook OnGameModeInit( )
{
	RDZ_GASPrice = 21;
	
	ACTOR_GROUP[ACTOR_TELECAR] = CreateActor(121, -1657.9618,1208.1776,7.2500,351.1750);// CarD

	GANGZONE_GROUP[0] = GangZoneCreate( -1665, 684, -1560, 723 );//POLICE ZONE
	GANGZONE_GROUP[1] = GangZoneCreate( -2559, -634, -2473, -591 );//SAFE ZONE


	AddPlayerClass( 1, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 2, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 3, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 4, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 6, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 7, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 8, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 9, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 10, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 11, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 12, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 13, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 14, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 15, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 16, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 17, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 18, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 19, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 20, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 21, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 22, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 23, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 24, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 25, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 26, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 27, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 28, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 30, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 31, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 32, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 33, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 34, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 35, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 36, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 37, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 38, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 39, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 40 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 41, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 42 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 43, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 44 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 45 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 46 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 47 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 48 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 49 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 50, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 51, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 52, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 53, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 54 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 55, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 56 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 57 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 58  , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 59, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 60 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 61, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 62 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 63, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 64 , -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 65, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 66, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 67, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 68, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 69, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 70, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 71, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 72, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 73, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 75, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 76, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 77, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 78, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 79, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 80, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 81, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 82, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 83, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 84, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 85, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 86, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 87, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 88, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 89, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 90, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 91, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 92, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 93, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 94, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	AddPlayerClass( 95, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 96, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 97, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 98, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 99, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 100, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 101, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 102, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 103, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 104, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 105, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 106, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 107, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 109, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 110, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 111, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 112, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 113, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 114, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 115, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 116, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 117, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 118, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 119, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 120, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 123, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 124, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 125, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 126, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 127, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 128, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 129, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 131, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 132, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 133, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 134, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 135, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 136, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 137, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 138, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 139, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 140, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 141, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 142, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 143, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 144, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 145, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 146, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 147, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 148, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 167, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 150, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 151, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 152, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 153, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 154, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 155, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 156, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 157, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 158, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 159, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 160, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 161, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 162, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 163, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 164, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 165, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 166, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 168, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 169, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 170, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 171, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 172, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 173, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 174, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 175, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 176, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 177, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 178, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 180, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 182, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 183, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 184, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 185, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 186, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 187, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 188, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 189, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 190, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 191, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 192, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 193, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 194, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 195, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 199, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 197, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 198, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 200, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 201, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 203, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 206, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 207, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 208, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 210, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 212, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 213, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 214, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 215, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 216, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 218, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 219, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 220, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 221, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 222, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 223, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 224, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 225, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 226, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 227, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 229, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 230, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 231, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 232, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 233, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 234, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 235, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 236, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 237, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 238, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 240, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 241, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 242, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 243, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 244, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 245, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 246, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 247, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 248, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 249, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 250, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 251, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 254, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 256, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 257, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 258, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 259, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 260, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 261, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 262, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 263, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 264, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 270, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 271, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 272, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 273, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 289, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 290, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 291, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 292, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 277, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 278, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 279, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 297, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 298, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
    AddPlayerClass( 299, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );

	#if !defined ENABLE_037R2_VERESION
		AddPlayerClass( 25000, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25002, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25004, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25005, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25007, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25009, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25010, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25011, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25012, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25013, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25015, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25016, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25017, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25018, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25020, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25021, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25022, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25023, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25024, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25025, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25026, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25027, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25028, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25029, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25030, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25031, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25032, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25033, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25034, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25035, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25036, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25040, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25041, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25042, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25046, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25047, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25049, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25050, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25051, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25055, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25057, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );

		AddPlayerClass( 25059, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25060, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25061, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25062, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25063, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25064, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25065, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25066, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25067, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25068, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25069, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25070, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25071, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25072, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25073, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25074, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25075, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25076, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25077, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25078, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25079, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25080, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25081, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25082, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25083, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25084, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25085, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25086, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
		AddPlayerClass( 25087, -2540.1389, -612.3549, 132.7109, 259.9616, 0, 0, 0, 0, 0, 0 );
	#endif

	CreateDynamicPickup( 3096, 2, -1974.3033, 431.5318, 36.5790, -1 ); //MG PICKUP
	CreateDynamicPickup( 3096, 2, -2097.97, 488.81, 35.85, -1 ); //MG PICKUP
	CreateDynamicPickup( 1239, 2, -52.9399, -231.0744, 6.7646, -1 );
	CreateDynamicPickup( 1239, 2, 1968.7668, 2295.8728, 16.4559, -1 );
	CreateDynamicPickup( 1239, 2, 2506.9092, 2120.2793, 10.8398, -1 );
	CreateDynamicPickup( 1239, 2, 1366.2434, -1275.1842, 13.5469, -1 );
	CreateDynamicPickup( 1239, 2, 2481.7710, -1331.9948, 28.3017, -1 );
	CreateDynamicPickup( 1239, HOUSES_PICKUP_TYPE, 1569.5016, -1199.4155, 19.7891 , -1 );
	CreateDynamicPickup( 1239, HOUSES_PICKUP_TYPE, 331.0298, 1128.5919, 1083.8828 , -1 );
	CreateDynamicPickup( 1239, HOUSES_PICKUP_TYPE, 1154.2208, -1770.8203, 16.5992 , -1 );
	CreateDynamicPickup( 1239, HOUSES_PICKUP_TYPE, 318.7120, 1114.4792, 1083.8828, -1 );
	CreateDynamicPickup( 1239, HOUSES_PICKUP_TYPE, 772.9987, 5.4201, 1000.7802 , -1 );
	CreateDynamicPickup( 1273, HOUSES_PICKUP_TYPE, 296.7992, -111.8199, 1001.5156, -1 );
	CreateDynamicPickup( 1575, HOUSES_PICKUP_TYPE, -1554.2957,389.1695,7.2260, -1 );//TDM PICKUP
	CreateDynamicPickup( 1575, HOUSES_PICKUP_TYPE, -1973.5486, 214.9070, 27.2224, -1 );
	
	SetWorldTime( RDZ_WORLD_TIME );
	SetWeather( RDZ_WORLD_WEATHER );
	ManualVehicleEngineAndLights( );
	
	#if defined CHRISTMAS_MOD
		SendRconCommand( "worldtime Midnight(SNOW)" );
	#else
		SendRconCommand( "worldtime Midnight" );
	#endif
	
	SendRconCommand( "mapname Roguedrifters" );
	SendRconCommand( "weburl Roguedrifterz.forumotion.com" );
	SetGameModeText( "Drift/Roleplay/Freeroam" );

	RDZ_MISCTD[0] = TextDrawCreate( 580.020935, 9.970348, "00:00:00" );
	TextDrawLetterSize( RDZ_MISCTD[0], 0.297998, 1.172739 );
	TextDrawAlignment( RDZ_MISCTD[0], 1 );
	TextDrawColor( RDZ_MISCTD[0], 255 );
	TextDrawSetShadow( RDZ_MISCTD[0], 0 );
	TextDrawSetOutline( RDZ_MISCTD[0], 1 );
	TextDrawBackgroundColor( RDZ_MISCTD[0], -1768515841 );
	TextDrawFont( RDZ_MISCTD[0], 2 );
	TextDrawSetProportional( RDZ_MISCTD[0], 1 );
	TextDrawSetShadow( RDZ_MISCTD[0], 0 );

	
	RDZ_MISCTD[1] = TextDrawCreate( 502.333282, 9.970348, "0/0/0000" );
	TextDrawLetterSize( RDZ_MISCTD[1], 0.297998, 1.172739 );
	TextDrawAlignment( RDZ_MISCTD[1], 1 );
	TextDrawColor( RDZ_MISCTD[1], 255 );
	TextDrawSetShadow( RDZ_MISCTD[1], 0 );
	TextDrawSetOutline( RDZ_MISCTD[1], 1 );
	TextDrawBackgroundColor( RDZ_MISCTD[1], -1768515841 );
	TextDrawFont( RDZ_MISCTD[1], 2 );
	TextDrawSetProportional( RDZ_MISCTD[1], 1 );
	TextDrawSetShadow( RDZ_MISCTD[1], 0 );

	RDZ_MISCTempTD[0] = TextDrawCreate(63.735778, 296.615112, "Press H to enter");//3
	TextDrawAlignment(RDZ_MISCTempTD[0], 1);
	TextDrawBackgroundColor(RDZ_MISCTempTD[0], -13487566);
	TextDrawFont(RDZ_MISCTempTD[0], 2);
	TextDrawLetterSize(RDZ_MISCTempTD[0], 0.575999, 2.211850);
	TextDrawColor(RDZ_MISCTempTD[0], 255);
	TextDrawSetOutline(RDZ_MISCTempTD[0], 1);
	TextDrawSetProportional(RDZ_MISCTempTD[0], 1);
	TextDrawSetShadow(RDZ_MISCTempTD[0], 0);

	RDZ_MISCTempTD[1] = TextDrawCreate(63.735778, 296.615112, "Type /plate to start");//3
	TextDrawAlignment(RDZ_MISCTempTD[1], 1);
	TextDrawBackgroundColor(RDZ_MISCTempTD[1], -13487566);
	TextDrawFont(RDZ_MISCTempTD[1], 2);
	TextDrawLetterSize(RDZ_MISCTempTD[1], 0.575999, 2.211850);
	TextDrawColor(RDZ_MISCTempTD[1], 255);
	TextDrawSetOutline(RDZ_MISCTempTD[1], 1);
	TextDrawSetProportional(RDZ_MISCTempTD[1], 1);
	TextDrawSetShadow(RDZ_MISCTempTD[1], 0);

	RDZ_MiscTimer = SetTimer( "RDZ_MainMisc", 1000, true );
	return 1;
}

hook OnPlayerSpawn( playerid )
{
	GangZoneShowForAll( GANGZONE_GROUP[1], SAFEZONE_GANG_RED );
	GangZoneFlashForAll( GANGZONE_GROUP[1], SAFEZONE_GANG_RED );

	GangZoneShowForAll( GANGZONE_GROUP[0], POLICE_GANG_BLUE );
	GangZoneFlashForAll( GANGZONE_GROUP[0], POLICE_GANG_BLUE );
	return 1;
}

hook OnGameModeExit( )
{
	for( new x; x < MAX_MISC_TD; x++ )
	{
		TextDrawDestroy( RDZ_MISCTD[x] );
	}

	KillTimer( RDZ_MiscTimer );
	return 1;
}

hook OnPlayerConnect( playerid )
{
	lottoTicket[playerid] = -1;
	for( new x; x < MAX_MISC_TD; x++ )
	{
		TextDrawShowForPlayer( playerid, RDZ_MISCTD[x] );
	}

	gPlayerWorldTimer[playerid] = SetTimerEx("worldPlayerTiming", 1000, true, "i", playerid);
	return 1;
}

hook OnPlayerDisconnect( playerid, reason )
{
	for( new x; x < MAX_MISC_TD; x++ )
	{
		TextDrawHideForPlayer( playerid, RDZ_MISCTD[x] );
	}
	KillTimer(gPlayerWorldTimer[playerid]);
	return 1;
}

forward worldPlayerTiming(playerid);
public worldPlayerTiming(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 7.0, -1974.1254,431.3540,34.8313) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		TextDrawShowForPlayer(playerid, RDZ_MISCTempTD[0]);
	}
	if(!IsPlayerInRangeOfPoint(playerid, 7.0, -1974.1254,431.3540,34.8313) )
	{
		TextDrawHideForPlayer(playerid, RDZ_MISCTempTD[0]);
	}

	if(IsPlayerInRangeOfPoint(playerid, 7.0, -2097.97, 488.81, 35.85) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		TextDrawShowForPlayer(playerid, RDZ_MISCTempTD[1]);
	}
	if(!IsPlayerInRangeOfPoint(playerid, 7.0, -2097.97, 488.81, 35.85) )
	{
		TextDrawHideForPlayer(playerid, RDZ_MISCTempTD[1]);
	}
	return 1;
}

forward RDZ_MainMisc( );
public RDZ_MainMisc( )
{
	new 
		WorldTime_String[15], 
		second, minute, hour, 
		day, month, year;

	gettime( hour, minute, second );
	getdate( year, month, day );

	FixZeros(hour, minute, WorldTime_String, sizeof WorldTime_String, second);
	
	format(WorldTime_String, sizeof WorldTime_String, "_%s", WorldTime_String);
	TextDrawSetString( RDZ_MISCTD[0], WorldTime_String );

	FixZeros(month, day, WorldTime_String, sizeof WorldTime_String, year);
	
	format(WorldTime_String, sizeof WorldTime_String, "%s", WorldTime_String);

	TextDrawSetString( RDZ_MISCTD[1], WorldTime_String );

	foreach(new i: Player)
	{
		if(Drift_IsPlayerDrifting(i)) continue;
		TextDrawShowForPlayer(i, RDZ_MISCTD[1]);
		TextDrawShowForPlayer(i, RDZ_MISCTD[0]);
	}

	if( minute == 1 && second == 1 )
	{
		Winning_Lotto = random(100);
		new Jackpot_Increase = random(10000);
		Lotto_Jackpot += Jackpot_Increase;
		if(Lotto_Jackpot < 10000) Lotto_Jackpot += 10000; 
		KickstartLotto(Winning_Lotto);
		foreach( new i: Player )
		{
			if( ( gettime( ) - GetPlayerTicks( i ) ) >= 1800 ) RDZPayday( i );
		}
		new RDZ_GASPriceEx;
		RDZ_GASPriceEx = random(50);

		RDZ_GASPrice = RDZ_GASPriceEx + 1;
		new string[STRING_SIZE_LARGE];
		format(string, sizeof string, "Aye aye listen up, fuel gas prices just changed to $%d/litre, don't be cheap!", RDZ_GASPrice);
		SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_GAS);
		UpdateGasPriceLabel();
	}
	return 1;
}

static TriggerTelecarProcess(playerid, money, price, model)
{
	if(money < price) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough cash on you to buy this item", MESSAGE_CASE_SERVER);

	GivePlayerMoney(playerid, -price);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've bought the vehicle successfully, type /telecar to teleport to it!", MESSAGE_CASE_SERVER);

	CreateTelecar(playerid, model, FIRST_TIME);
	return 1;
}

static RDZPayday( playerid )
{
	new paycheck_amount, interest_amount;
	if( IsPlayerVIP( playerid ) )
	{
		GivePlayerEXP( playerid, 1 );
	}

	GivePlayerEXP( playerid, 1 );
	new rand_cash;
	
	if(GetPlayerLevel(playerid) > 0)
	{
		rand_cash = random( 1000*GetPlayerLevel( playerid ) );
	}
	else
	{
		rand_cash = random(1000);
	}
	rand_cash += 100;
	if(GetPlayerInterest(playerid) > 0.0) interest_amount = floatround(  GetPlayerInterest( playerid ) *rand_cash );
	else interest_amount = random(50) + 1;

	new result_amount = rand_cash + interest_amount;
	if( IsPlayerVIP( playerid ) )
	{
		result_amount += 2500;
		SendRDZMessage( playerid, RDZ_OFFICIAL_COLOR, "You've gained extra EXP and cash for being a VIP, hurray!", MESSAGE_CASE_PAYCHECK);
	}

	paycheck_amount = result_amount;

	if( IsPlayerSaver( playerid ) )
	{
		IncreasePlayerBankB( playerid, paycheck_amount );
	}
	else
	{
		GivePlayerMoney( playerid, paycheck_amount );
	}

	GivePlayerReps(playerid, 1);
	IncreasePlayerInterest( playerid, 0.1 );
	IncreasePlayingHours( playerid, 1 );
	
	DisplayPaycheck( playerid, paycheck_amount, interest_amount );
	return 1;
}

static DisplayPaycheck( playerid, paycheck_amount, interest_amount )
{
	new string[128];
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "|___ {00FF00}BANK STATMENT{CCCCCC}___|", MESSAGE_CASE_NULL );
	HumanizeThousand(paycheck_amount, string);

	format( string, sizeof( string ), "  Paycheck: {00FF00}$%s ", string );
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
	if( IsPlayerSaver( playerid ) )
	{
		HumanizeThousand(GetPlayerBankB( playerid ) - paycheck_amount, string);
		format( string, sizeof( string ), "  Balance: {00FF00}$%s", string );
	}
	else
	{
		HumanizeThousand(GetPlayerMoney( playerid )- paycheck_amount, string);
		format( string, sizeof( string ), "  Cash on hand: {00FF00}$%s", string );
	}
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
	format( string, sizeof( string ), "  Interest Rate: {00FF00}%0.1f {FFFFFF}percent", GetPlayerInterest( playerid ) );
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
	format( string, sizeof( string ), "  Interest Gained {00FF00}$%d", interest_amount );
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "|--------------------------------------|", MESSAGE_CASE_NULL );
	if( IsPlayerSaver( playerid ) )
	{
		HumanizeThousand(GetPlayerBankB( playerid ), string);
		format( string, sizeof( string ), "  New Balance: {00FF00}$%s", string );
	}
	else
	{
		HumanizeThousand(GetPlayerMoney( playerid ), string);
		format( string, sizeof( string ), "  New cash on hand: {00FF00}$%s", string );
	}
	SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, string, MESSAGE_CASE_NULL);
	format( string, sizeof( string ), "~y~PayDay~n~~w~Paycheck +1 Rep +1 EXP" );
	GameTextForPlayer( playerid, string, 5000, 1 );
	return 1;
}

stock ReturnGasPrice()
	return RDZ_GASPrice;
	
hook OnPlayerTargetActor(playerid, actorid, weaponid)
{
	if(weaponid == WEAPON_FISTS)
	{
		if(actorid == ACTOR_GROUP[ACTOR_TELECAR])
		{
			Dialog_Show(playerid, DIALOG_PRECARDEALER, DIALOG_STYLE_LIST, "Cars list", "Buy telecar\nSell telecar", "Buy", "Cancel");
			//Dialog_Show(playerid, DIALOG_CARDEALER, DIALOG_STYLE_LIST, "Cars list", "Elegy			$600,000\nElegy			$600,000\nNRG			$250,000\nBanshee			$390,000\nTurismo			$500,000\nPCJ-600			$90,000\nBMX			$50,000\nStallion			$120,000\nBobcat			$180,000\nBurrito			$100,000\nSuperGT			$420,000\nHermes			$200,000\nSell", "Buy", "Cancel");
		}
	}
    return 1;
}

Dialog:DIALOG_PRECARDEALER(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleModel = GetVehicleModel(Player_TelecarID[playerid]);
		switch(listitem)
		{
			case 0:
			{
				new string[sizeof(CAR_LIST) *50];
				for (new i; i < sizeof(CAR_LIST); i++)
				{
					format(string, sizeof string, "%s%i\t%s\n", string, CAR_LIST[i][E_CARLIST_MODELID], CAR_LIST[i][E_CARLIST_CARPRICE]);
				}
				Dialog_Show(playerid, DIALOG_CARDEALER, DIALOG_STYLE_PREVIEW_MODEL, "Cars list", string, "Buy", "Cancel");
			}
			case 1:
			{
				if(IsTelecarOwner(playerid)) 
					SellTelecar(playerid, vehicleModel);
				else 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to have an existing telecar to sell it", MESSAGE_CASE_SERVER);
			}
		}
	}
	return 1;
}

Dialog:DIALOG_CARDEALER(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new money = GetPlayerMoney(playerid);
		
		switch(listitem)
		{
			case 0:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, ELEGY_PRICE, ELEGY_MODEL);
			}
			case 1:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, NRG_PRICE, NRG_MODEL);
			}
			case 2:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, BANSHEE_PRICE, BANSHEE_MODEL);
			}
			case 3:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, TURISMO_PRICE, TURISMO_MODEL);
			}
			case 4:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, PCJ_PRICE, PCJ_MODEL);
			}
			case 5:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, BMX_PRICE, BMX_MODEL);
			}
			case 6:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, STALLION_PRICE, STALLION_MODEL);
			}
			case 7:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, BOBCAT_PRICE, BOBCAT_MODEL);
			}
			case 8:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, BURRITO_PRICE, BURRITO_MODEL);
			}
			case 9:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, SUPERGT_PRICE, SUPERGT_MODEL);
			}
			case 10:
			{
				if(IsTelecarOwner(playerid)) 
					return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You need to sell the existing telecar first before buying another", MESSAGE_CASE_SERVER);
				TriggerTelecarProcess(playerid, money, HERMES_PRICE, HERMES_MODEL);
			}
		}
	}
	return 1;
}

static KickstartLotto(number)
{
	new string[STRING_SIZE_LARGE];
	lotto_price = random(5000) + 1000;
	//if(lotto_price > Lotto_Jackpot) lotto_price -= Lotto_Jackpot;
	format(string, sizeof string, "Lottery is starting in 30 seconds! /lotto [0-100] to take your pick! Ticket price: [$%d], Jackpot: [$%d]", lotto_price, Lotto_Jackpot);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
	SetTimerEx("startLotto", LOTTO_DELAY_TIME, false, "i", number);
	return 1;
}

forward startLotto(number);
public startLotto(number)
{
	new string[STRING_SIZE_LARGE];
	foreach(new i: Player)
	{
		if(lottoTicket[i] == number)
		{
			format(string, sizeof string, "Player %s has won the lottery! Jackpot: %d, ticket: %d", Player_TempName[i], Lotto_Jackpot, number);
			SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
			BreakLotto();
			return 0;
		}
	}
	format(string, sizeof string, "No one has won the lottery! Jackpot: %d, ticket: %d", Lotto_Jackpot, number);
	SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
	return 1;
}

static BreakLotto()
{
	foreach(new i: Player)
	{
		lottoTicket[i] = -1;
	}
	return 1;
}

CMD:lotto(playerid, params[])
{
	new lottoid;
	if(sscanf(params, "i", lottoid))
	{
		return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state the ticket id", MESSAGE_CASE_JARVIS);
	}
	
	if(GetPlayerMoney(playerid) < lotto_price) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough cash!", MESSAGE_CASE_JARVIS);
	if(lottoTicket[playerid] != -1) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You already bought a ticket!", MESSAGE_CASE_JARVIS);
	if(lottoid > 100 || lottoid < 0 ) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Ticket value is invalid!", MESSAGE_CASE_JARVIS);
	foreach(new i: Player)
	{
		if(lottoTicket[i] == Winning_Lotto)
		{
			SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Ticket was already bought by someone else!", MESSAGE_CASE_SERVER);
			break;
		}
	}
	lottoTicket[playerid] = lottoid;
	GivePlayerMoney(playerid, -lotto_price);
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You bought a ticket!", MESSAGE_CASE_JARVIS);
	return 1;
}

stock ShowMiscTDsForPlayer(playerid)
{
	for( new x; x < MAX_MISC_TD; x++ )
	{
		TextDrawShowForPlayer( playerid, RDZ_MISCTD[x] );
	}
	return 1;
}

stock HideMiscTDsForPlayer(playerid)
{
	for( new x; x < MAX_MISC_TD; x++ )
	{
		TextDrawHideForPlayer( playerid, RDZ_MISCTD[x] );
	}
	return 1;
}
