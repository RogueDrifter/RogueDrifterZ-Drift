
#if defined RDZ_Stats_Included_
   #endinput
#endif

#define RDZ_Stats_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define MAX_IP_LENGTH 17
#define MAX_GPCI_LENGTH 46
#define MAX_BAN_REASON_LENGTH 40
#define SELF_DEFENSE_TIME 40*1000
#define SHOPS_DB_START_VWORLD 100

#define INTERIOR_WAIT_TIME 3000
#define LOCKED_STATS_SPECIAL_MAP 3

#define MAX_SHOP_ACTORS 1000

#define SHOP_SYSTEM_PICKUP_RANGE 1.5

#define SHOP_TYPE_247 1
#define SHOP_TYPE_AMMU 2
#define SHOP_TYPE_CLUCKINBELL 3
#define SHOP_TYPE_PIZZASTACK 4
#define SHOP_TYPE_BURGERSHOT 5
#define SHOP_TYPE_SEXSHOP 6
#define SHOP_TYPE_GYM 7
#define SHOP_TYPE_CASINO 8
#define SHOP_TYPE_CLOTHES 9
#define SHOP_TYPE_BAR 10
#define SHOP_TYPE_TATTOO 11
#define SHOP_TYPE_BARBER 12
#define SHOP_TYPE_MOTEL 13
#define SHOP_TYPE_POLICE 14
#define SHOP_TYPE_BANK 15 
#define SHOP_TYPE_CLUB 16
#define SHOP_TYPE_NIGHTCLUB 20
#define SHOP_TYPE_GASINTERIOR 21
#define SHOP_TYPE_JANITORROOM 22
#define SHOP_TYPE_RESTAURANT 23
#define SHOP_TYPE_DONUTS 24
#define SHOP_TYPE_MEATFACTORY 25
#define SHOP_TYPE_CRACKFACTORY 26
#define SHOP_TYPE_CARSCHOOL 27
#define SHOP_TYPE_TOILET 28
#define SHOP_TYPE_LSART 30
#define SHOP_TYPE_BIKESCHOOL 31
#define SHOP_TYPE_CHURCH 32
#define SHOP_TYPE_HOSPITAL 33
#define SHOP_TYPE_PRISON 34
#define SHOP_TYPE_PLANE 35

#define MAPICON_SEX 38
#define MAPICON_GYM 54
#define MAPICON_CASINO 44
#define MAPICON_CLOTHES 45
#define MAPICON_BAR 49
#define MAPICON_TATTOO 39
#define MAPICON_BARBER 7
#define MAPICON_MOTEL 32
#define MAPICON_POLICE 30
#define MAPICON_AMMU 18
#define MAPICON_TWENTYFOUR_SEVEN  17
#define MAPICON_BURGERSHOT 10
#define MAPICON_CLUCKINBELL 14
#define MAPICON_PIZZASTACK 29
#define MAPICON_CLUB 43
#define MAPICON_BANK 52
#define MAPICON_NIGHTCLUB 48
#define MAPICON_GASINTERIOR 62
#define MAPICON_JANITORROOM 11
#define MAPICON_DINER 50
#define MAPICON_DONUTS 24
#define MAPICON_CRACKFACTORY 28 
#define MAPICON_MEATFACTORY 40
#define MAPICON_TOILET 42
#define MAPICON_CARSCHOOL 51
#define MAPICON_LSART 46
#define MAPICON_BIKESCHOOL 62
#define MAPICON_CHURCH 21
#define MAPICON_HOSPITAL 22
#define MAPICON_PRISON 60
#define MAPICON_PLANE 5

#define AMMU_NPC 121
#define TWENTYFOUR_NPC 0
#define CLUCKINBELL_NPC 167
#define BURGERSHOT_NPC 205
#define PIZZASTACK_NPC 155
#define SEX_NPC 178
#define GYM_NPC 204
#define CASINO_NPC 171
#define CLOTHES_NPC 216
#define BAR_NPC 98
#define TATTOO_NPC 180
#define BARBER_NPC 176
#define MOTEL_NPC 147
#define POLICE_NPC 306
#define CLUB_NPC 87
#define BANK_NPC 57
#define NIGHTCLUB_NPC 85
#define GASINTERIOR_NPC 113
#define JANITOR_NPC 8
#define DINER_NPC 209
#define DONUTS_NPC 259
#define MEATFACTORY_NPC 268
#define CRACKFACTORY_NPC 230
#define CARSCHOOL_NPC 166
#define TOILET_NPC 162
#define LSART_NPC 249
#define BIKESCHOOL_NPC 253
#define PRISON_NPC 283
#define CHURCH_NPC 68
#define HOSPITAL_NPC 274
#define PILOT_NPC 61

//SUB INTERIORS: (They take same NPC and Mapicon)
#define VICTIM_SHOP 17//SHOP_TYPE_CLOTHES
#define LS_POLICE 18 //SHOP_TYPE_POLICE
#define LV_POLICE 19 //SHOP_TYPE_POLICE
#define BAR_SECONDARY 29//SHOP_TYPE_BAR
#define CHURCH_SECONDARY 36//SHOP_TYPE_CHURCH
#define PD_SECONDARY 37//SHOP_TYPE_POLICE

#define NAMES_MULTI_FROMDB 10

#define USER_GENDER_NULL 0

#define TARGET_BOOL_TRUE 1
#define TARGET_BOOL_FALSE 0
#define SAFEZONE_RANGE 30.00

#define PLAYER_GENDER_MALE 2
#define PLAYER_GENDER_FEMALE 1

static
    DB: RDZ_Database;

enum ObjectRemoved
{
    Model,
    Float:Location[3]
}

new
        RemovedObject[MAX_REMOVED_OBJECTS][ObjectRemoved],
        g_SlotID = -1
;

new DCC_Channel:Admin_Log,
    DCC_Channel:Admin_Chat;
static DCC_Channel:IGNMusic,
       DCC_Channel:SpyChatChannel,
       SHOP_ACTOR[MAX_SHOP_ACTORS];

#define SHOP_PICKUP_MODEL 1272

#define HOUSES_PICKUP_MODEL 1273
#define HOUSES_LABEL_COLOR 0xFFFFFFFF
#define HOUSES_LABEL_DRAW_DISTANCE 20.000
#define HOUSES_PICKUP_TYPE 1
#define HOUSES_MAPICON 31

enum RDZ_PLAYERS_STATS 
{ 
    USER_ID, 
    USER_VIP, 
    USER_BAN, 
    USER_MUTE, 
	USER_WANTED, 
    USER_GPS, 
	USER_SEX, 
    USER_JAIL, 
	USER_JOB, 
    USER_ARRESTS, 
    USER_RANK, 

    USER_NAME[MAX_PLAYER_NAME], 
    USER_ConstIP[MAX_IP_LENGTH], 
    USER_VarIP[MAX_IP_LENGTH], 
    USER_Constgpci[MAX_GPCI_LENGTH], 
    USER_Vargpci[MAX_GPCI_LENGTH], 
    USER_PASSWORD[BCRYPT_HASH_LENGTH], 
    USER_COB[MAX_BAN_REASON_LENGTH], 
	USER_MREASON[STRING_SIZE_SMALL], 
    USER_VERSION[STRING_SIZE_MEDIUM], 
    USER_LASTON[STRING_SIZE_MEDIUM], 
    
    USER_LEVEL, 
    USER_KILLS, 
    USER_DEATHS, 
    USER_EXP, 
    USER_RESPECT, 
    USER_PHOURS, 
    USER_JTIME, 
    USER_KICKCOUNT, 
    USER_CRIMES, 
    USER_ARRESTED, 
    USER_FUELCAN, 

    USER_TELECAR, 
    CAR_WHEELS, 
    CAR_SPOILERS, 
    CAR_EXHAUSTS, 
    CAR_FBUMBER, 
    CAR_RBUMBER, 
    CAR_ROOF, 
    CAR_SSKIRT, 
    CAR_PJOB, 
    CAR_FCOLOR, 
    CAR_SCOLOR, 
    Float:CAR_X, 
    Float:CAR_Y, 
    Float:CAR_Z, 
    Float:CAR_R, 

    USER_VIRTUALWORLD, 
    USER_INTERIOR, 
    USER_SKIN, 

    Float:USER_X, 
    Float:USER_Y, 
    Float:USER_Z, 
    Float:USER_R, 
    Float:USER_INTEREST, 
	Float:USER_VX, 
	Float:USER_VY, 
	Float:USER_VZ, 
	Float:USER_VR, 
	
    USER_BESTRIVAL, 
    USER_ODWON, 
    USER_ODLOST, 
    USER_DRIFTSCORE, 
    USER_HANDCASH, 
    USER_BANK, 
    USER_ADMIN, 
    USER_CONTICKS, 
    USER_COLOR, 

    USER_SAVER, 
    bool:USER_RESPAWN
}; 

static 
    bool:PLoggedIN[MAX_PLAYERS char], 
    bool:PTempGPS[MAX_PLAYERS char], 
    bool:selfDefense[MAX_PLAYERS char], 
    bool:adminCStats[MAX_PLAYERS char], 
    sdTimer[MAX_PLAYERS], 
    RespawnCars_Timer,
    s_copLights[MAX_VEHICLES],
    bool:s_MotelOwner[MAX_PLAYERS char],
    s_motelVW[MAX_PLAYERS];

static 
    RDZPlayer[MAX_PLAYERS][RDZ_PLAYERS_STATS];  

new 
    Player_TempName[MAX_PLAYERS][MAX_PLAYER_NAME], 
    Player_IP[MAX_PLAYERS][MAX_IP_LENGTH], 
    Player_GPCI[MAX_PLAYERS][MAX_GPCI_LENGTH], 
    Mute_StringReason[MAX_PLAYERS][STRING_SIZE_SMALL], 
    Player_TelecarID[MAX_PLAYERS], 
    bool:cmdKill[MAX_PLAYERS char];

forward respawnCars();
public respawnCars()
{
    GameTextForAll("Empty cars will respawn in 10 seconds...", 5000, 1);
    SetTimer("respawnEmpty_Cars", 10*1000, false);
    SetTimerEx("respawnEmpty_CarsDelay", 12*1000, false, "i", 500);
    return 1;
}

forward respawnEmpty_Cars();
public respawnEmpty_Cars()
{
    foreach(new x: Vehicle)
    {
		if(x < 500)
		{

			if(IsVehicleEmpty(x))
				SetVehicleToRespawn(x);
		}
		else 
		{
			break;
		}
    }
    return 1;
}

forward respawnEmpty_CarsDelay(carid);
public respawnEmpty_CarsDelay(carid)
{
	for(new x=carid; x<MAX_VEHICLES; x++)
	{
		if(!IsValidVehicle(x)) continue;
		if(IsVehicleEmpty(x))
			SetVehicleToRespawn(x);
	}
	return 1;
}

stock IsVehicleEmpty(vehicleid)
{
    foreach(new i: Player)
    {
        if(GetPlayerVehicleID(i) == vehicleid) return 0;
    }
    return 1;
}

hook OnGameModeInit()
{
    Admin_Log = DCC_FindChannelById("000000000000000");//Put in channel id where logs of the anti-cheat should go to
    Admin_Chat = DCC_FindChannelById("000000000000000");//Put in the channel id where you want to save admin chat to
    IGNMusic =  DCC_FindChannelById("000000000000000000");//Put in channel id where u want to saves notes from in-game using the !p command
    SpyChatChannel = DCC_FindChannelById("000000000000000000");//Put in the channel id of the one you want to have game-chat exported to

    RespawnCars_Timer = SetTimer("respawnCars", 30*1000*60, true); //Commented out til i fix the timeout issue

	//Trying to stop deAMXing
    new b;
    #emit load.pri b
    #emit stor.pri b
	//END
	
    DisableInteriorEnterExits();
    EnableStuntBonusForAll( 0 );
    UsePlayerPedAnims();

    if ((RDZ_Database = db_open("RDZBrain.db")) == DB: 0) 
    {
        print("Failed to open a connection to \"RDZBase.db\""); 
    } 
    else
    { 
        print("DB Loaded successfully!");
        db_query(RDZ_Database, "PRAGMA synchronous = OFF"); 
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userprimary (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE, password VARCHAR(129), constip VARCHAR(16), varip VARCHAR(16), constgpci VARCHAR(45), vargpci VARCHAR(45), admin INTEGER DEFAULT 0 NOT NULL, cash INTEGER DEFAULT 0 NOT NULL, viplevel INTEGER DEFAULT 0 NOT NULL, kickcount INTEGER DEFAULT 0 NOT NULL, mutereason VARCHAR(50), usergps INTEGER DEFAULT 0 NOT NULL, injail INTEGER DEFAULT 0 NOT NULL, jailtime INTEGER DEFAULT 0 NOT NULL, sampversion VARCHAR(50), laston VARCHAR(50))");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userpositions (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE, interior INTEGER DEFAULT 0 NOT NULL, virtualworld INTEGER DEFAULT 0 NOT NULL, posx FLOAT DEFAULT 0.0 NOT NULL, posy FLOAT DEFAULT 0.0 NOT NULL, posz FLOAT DEFAULT 0.0 NOT NULL, posr FLOAT DEFAULT 0.0 NOT NULL, vposx FLOAT DEFAULT 0.0 NOT NULL, vposy FLOAT DEFAULT 0.0 NOT NULL, vposz FLOAT DEFAULT 0.0 NOT NULL, vposr FLOAT DEFAULT 0.0 NOT NULL)");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS usermisc (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE, driftscore INTEGER DEFAULT 0 NOT NULL, bestrival INTEGER DEFAULT 0 NOT NULL, bankamount INTEGER DEFAULT 0 NOT NULL, bankinterest FLOAT DEFAULT 0.0 NOT NULL, savermoney INTEGER DEFAULT 0 NOT NULL, namebanned INTEGER DEFAULT 0 NOT NULL, causeofban VARCHAR(50), muted INTEGER DEFAULT 0 NOT NULL, odlost INTEGER DEFAULT 0 NOT NULL, odwon INTEGER DEFAULT 0 NOT NULL)");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userdetails (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE, level INTEGER DEFAULT 0 NOT NULL, reputation INTEGER DEFAULT 0 NOT NULL, experience INTEGER DEFAULT 0 NOT NULL, playinghours INTEGER DEFAULT 0 NOT NULL, skinid INTEGER DEFAULT 0 NOT NULL, playerkills INTEGER DEFAULT 0 NOT NULL, playerdeaths INTEGER DEFAULT 0 NOT NULL, userwanted INTEGER DEFAULT 0 NOT NULL, usersex INTEGER DEFAULT 0 NOT NULL, color INTEGER DEFAULT 0 NOT NULL)");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS usertcar (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE, model INTEGER DEFAULT 0 NOT NULL, exhausts INTEGER DEFAULT 0 NOT NULL, spoiler INTEGER DEFAULT 0 NOT NULL, wheels INTEGER DEFAULT 0 NOT NULL, roof INTEGER DEFAULT 0 NOT NULL, sideskirt INTEGER DEFAULT 0 NOT NULL, frontbumber INTEGER DEFAULT 0 NOT NULL, rearbumber INTEGER DEFAULT 0 NOT NULL, paintjob INTEGER DEFAULT 0 NOT NULL, fcolor INTEGER DEFAULT 0 NOT NULL, scolor INTEGER DEFAULT 0 NOT NULL, floatx FLOAT DEFAULT 0.0 NOT NULL, floaty FLOAT DEFAULT 0.0 NOT NULL, floatz FLOAT DEFAULT 0.0 NOT NULL, floatr DEFAULT 0.0 NOT NULL)");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userextended (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE, job INTEGER DEFAULT 0 NOT NULL, coprank INTEGER DEFAULT 0 NOT NULL, arrests INTEGER DEFAULT 0 NOT NULL, crimes INTEGER DEFAULT 0 NOT NULL, arrested INTEGER DEFAULT 0 NOT NULL)");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userclan (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24) COLLATE NOCASE)");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userbans (userid INTEGER PRIMARY KEY AUTOINCREMENT, usergpci VARCHAR(45))");
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS namebans (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24))");  
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS ipmulti (username VARCHAR(24), userip VARCHAR(16))");     
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS gpcimulti (username VARCHAR(24), gpciuser VARCHAR(46))");     
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS userhouse (userid INTEGER PRIMARY KEY AUTOINCREMENT, username VARCHAR(24), interior INTEGER DEFAULT 0 NOT NULL, virtualworld INTEGER DEFAULT 0 NOT NULL, secondworld INTEGER DEFAULT 0 NOT NULL, secondinterior INTEGER DEFAULT 0 NOT NULL, locked INTEGER DEFAULT 0 NOT NULL, ax FLOAT DEFAULT 0.0 NOT NULL, ay FLOAT DEFAULT 0.0 NOT NULL, az FLOAT DEFAULT 0.0 NOT NULL, ar FLOAT DEFAULT 0.0 NOT NULL, bx FLOAT DEFAULT 0.0 NOT NULL, by FLOAT DEFAULT 0.0 NOT NULL, bz FLOAT DEFAULT 0.0 NOT NULL, br FLOAT DEFAULT 0.0 NOT NULL)");     
        db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS rdzshops (shopid INTEGER PRIMARY KEY AUTOINCREMENT, shopname VARCHAR(24), interior INTEGER DEFAULT 0 NOT NULL, virtualworld INTEGER DEFAULT 0 NOT NULL, secondworld INTEGER DEFAULT 0 NOT NULL, secondinterior INTEGER DEFAULT 0 NOT NULL, mapicon INTEGER DEFAULT 0 NOT NULL, locked INTEGER DEFAULT 0 NOT NULL, shoptype INTEGER DEFAULT 0 NOT NULL, ax FLOAT DEFAULT 0.0 NOT NULL, ay FLOAT DEFAULT 0.0 NOT NULL, az FLOAT DEFAULT 0.0 NOT NULL, ar FLOAT DEFAULT 0.0 NOT NULL, bx FLOAT DEFAULT 0.0 NOT NULL, by FLOAT DEFAULT 0.0 NOT NULL, bz FLOAT DEFAULT 0.0 NOT NULL, br FLOAT DEFAULT 0.0 NOT NULL)");    
        
        //The below is unfinished for telecar tunes saving
        //db_query(RDZ_Database, "CREATE TABLE IF NOT EXISTS reservedcars (carid INTEGER PRIMARY KEY AUTOINCREMENT, ownername VARCHAR(24) COLLATE NOCASE, model INTEGER DEFAULT 0 NOT NULL, exhausts INTEGER DEFAULT 0 NOT NULL, spoiler INTEGER DEFAULT 0 NOT NULL, wheels INTEGER DEFAULT 0 NOT NULL, roof INTEGER DEFAULT 0 NOT NULL, sideskirt INTEGER DEFAULT 0 NOT NULL, frontbumber INTEGER DEFAULT 0 NOT NULL, rearbumber INTEGER DEFAULT 0 NOT NULL, paintjob INTEGER DEFAULT 0 NOT NULL, fcolor INTEGER DEFAULT 0 NOT NULL, scolor INTEGER DEFAULT 0 NOT NULL, floatx FLOAT DEFAULT 0.0 NOT NULL, floaty FLOAT DEFAULT 0.0 NOT NULL, floatz FLOAT DEFAULT 0.0 NOT NULL, floatr DEFAULT 0.0 NOT NULL, skip INTEGER DEFAULT 0 NOT NULL)");
        //db_query(RDZ_Database, "ALTER TABLE `tablename` ADD `column` datatype");
    } 

    new     
        DBResult: Result; 
    new buf[STRING_SIZE_QUERY];     
    new MAX_ROWS_ID;

    Result = db_query(RDZ_Database, "SELECT * FROM `userhouse` ORDER BY `userid` DESC LIMIT 1");
    
    MAX_ROWS_ID = db_get_field_int(Result); 

    db_free_result(Result);

    if(MAX_ROWS_ID != 0)
    {    
        new OWNER_NAME[MAX_PLAYER_NAME];
        for(new i; i <= MAX_ROWS_ID; i++)
        {
            format(buf, sizeof buf, "SELECT * FROM userhouse WHERE userid = %d LIMIT 1", i);
            Result = db_query(RDZ_Database, buf);

            if (db_num_rows(Result))
            { 
                if(db_get_field_assoc_int(Result, "locked") == 1)
                {
                    db_free_result(Result);
                    continue;
                }
                CreateDynamicPickup(HOUSES_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_int(Result, "secondworld"));

                CreateDynamicPickup(HOUSES_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_int(Result, "virtualworld"));
                
                db_get_field_assoc(Result, "username", OWNER_NAME, MAX_PLAYER_NAME );

                CreateDynamic3DTextLabel(OWNER_NAME, HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, db_get_field_assoc_int(Result, "secondworld"));
                CreateDynamic3DTextLabel("L-Alt to enter", HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az")+0.5, HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, db_get_field_assoc_int(Result, "secondworld"));
                CreateDynamicMapIcon(db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), HOUSES_MAPICON, 0);
            }
            db_free_result(Result);
        }
    }

    Result = db_query(RDZ_Database, "SELECT * FROM `rdzshops` ORDER BY `shopid` DESC LIMIT 1");
    
    MAX_ROWS_ID = db_get_field_int(Result); 

    db_free_result(Result);

    if(MAX_ROWS_ID != 0)
    {    
        new SHOP_NAME[MAX_PLAYER_NAME];
        for(new i; i <= MAX_ROWS_ID; i++)
        {
            format(buf, sizeof buf, "SELECT * FROM rdzshops WHERE shopid = %d LIMIT 1", i);
            Result = db_query(RDZ_Database, buf);

            if (db_num_rows(Result))
            { 
                if(db_get_field_assoc_int(Result, "locked") == 1 || i == 23 || i == 24)
                {
                    db_free_result(Result);
                    continue;
                }
                CreateDynamicPickup(SHOP_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_int(Result, "secondworld"));

                CreateDynamicPickup(SHOP_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_int(Result, "virtualworld"));
                
                db_get_field_assoc(Result, "shopname", SHOP_NAME, MAX_PLAYER_NAME );

                CreateDynamic3DTextLabel(SHOP_NAME, HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, db_get_field_assoc_int(Result, "secondworld"));
                CreateDynamic3DTextLabel("L-Alt to enter", HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az")+0.5, HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, db_get_field_assoc_int(Result, "secondworld"));

                CreateDynamicMapIcon(db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_int(Result, "mapicon"), 0);
                if(i < MAX_SHOP_ACTORS)
                {
                    switch(db_get_field_assoc_int(Result, "shoptype"))
                    {
                        case SHOP_TYPE_247:
                        {
                            SHOP_ACTOR[i] = CreateActor( TWENTYFOUR_NPC, 1.9534, -30.7201, 1003.5494, 356.8885 );
                        }
                        case SHOP_TYPE_AMMU:
                        {
                            SHOP_ACTOR[i] = CreateActor( AMMU_NPC, 316.3683, -133.5376, 999.6016, 92.3999 );
                        }
                        case SHOP_TYPE_BURGERSHOT:
                        {
                            SHOP_ACTOR[i] = CreateActor( BURGERSHOT_NPC, 376.5167, -64.9684, 1001.5078, 172.7498 );
                        }
                        case SHOP_TYPE_CLUCKINBELL:
                        {
                            SHOP_ACTOR[i] = CreateActor( CLUCKINBELL_NPC, 369.5378, -4.4830, 1001.8589, 175.1585 );
                        }
                        case SHOP_TYPE_PIZZASTACK:
                        {
                            SHOP_ACTOR[i] = CreateActor( PIZZASTACK_NPC, 374.7466, -117.0481, 1001.4922, 179.7228 );
                        }
                        case SHOP_TYPE_BARBER:
                        {
                            SHOP_ACTOR[i] = CreateActor( BARBER_NPC, 408.9911, -53.8690, 1001.8984, 273.7100 );
                        }
                        case SHOP_TYPE_CASINO:
                        {
                            SHOP_ACTOR[i] = CreateActor( CASINO_NPC, 1141.1625, -5.7393, 1000.6719, 92.3396 );
                        }
                        case SHOP_TYPE_GYM:
                        {
                            SHOP_ACTOR[i] = CreateActor( GYM_NPC, 763.3224, -49.6312, 1000.5859, 357.4102 );
                        }
                        case SHOP_TYPE_POLICE:
                        {
                            SHOP_ACTOR[i] = CreateActor( POLICE_NPC, 246.5444, 120.3937, 1003.2636, 180.4187 );
                        }
                        case SHOP_TYPE_TATTOO:
                        {
                            SHOP_ACTOR[i] = CreateActor( TATTOO_NPC, -201.0900, -22.8606, 1002.2734, 158.7730 );
                        }
                        case SHOP_TYPE_SEXSHOP:
                        {
                            SHOP_ACTOR[i] = CreateActor( SEX_NPC, -103.9734, -24.2545, 1000.7188, 0.8046 );
                        }
                        case SHOP_TYPE_CLOTHES:
                        {
                            SHOP_ACTOR[i] = CreateActor( CLOTHES_NPC, 161.2680, -81.1915, 1001.8047, 179.4253 );
                        }
                        case SHOP_TYPE_MOTEL:
                        {
                            SHOP_ACTOR[i] = CreateActor( MOTEL_NPC, 2217.3137, -1144.5304, 1026.0168, 182.7606);
                        }
                        case SHOP_TYPE_BAR:
                        {
                            SHOP_ACTOR[i] = CreateActor( BAR_NPC, 497.5840, -77.8954, 998.7651, 355.0053 );
                        }
                        case SHOP_TYPE_BANK:
                        {
                            SHOP_ACTOR[i] = CreateActor( BANK_NPC, 2308.8201, -13.4536, 26.7422, 0.5673 );
                        }
                        case SHOP_TYPE_CLUB:
                        {
                            SHOP_ACTOR[i] = CreateActor( CLUB_NPC, 1215.8168, -15.3406, 1000.9219, 1.0905 );
                        }
                        case VICTIM_SHOP:
                        {
                            SHOP_ACTOR[i] = CreateActor( CLOTHES_NPC, 204.8528, -8.1264, 1001.2109, 270.7413 );
                        }
                        case LS_POLICE:
                        {
                            SHOP_ACTOR[i] = CreateActor( POLICE_NPC, 251.7096, 68.1342, 1003.6406, 91.4559 );
                        }
                        case LV_POLICE:
                        {
                            SHOP_ACTOR[i] = CreateActor( POLICE_NPC, 293.7616, 182.6091, 1007.1719, 155.8465 );
                        }
                        case SHOP_TYPE_NIGHTCLUB:
                        {
                            SHOP_ACTOR[i] = CreateActor( NIGHTCLUB_NPC, 2320.1040, 1951.5164, 1418.0122, 25.7458 );
                        }
                        case SHOP_TYPE_GASINTERIOR:
                        {
                            SHOP_ACTOR[i] = CreateActor( GASINTERIOR_NPC, -2237.3699, 128.5864, 1035.4141, 359.8675 );
                        }
                        case SHOP_TYPE_JANITORROOM:
                        {
                            SHOP_ACTOR[i] = CreateActor( JANITOR_NPC, 302.0684, 303.5096, 1003.5391, 274.3500 );
                        }
                        case SHOP_TYPE_RESTAURANT:
                        {
                            SHOP_ACTOR[i] = CreateActor( DINER_NPC, 450.5174, -82.1227, 999.5547, 177.0567 );
                        }
                        case SHOP_TYPE_DONUTS:
                        {
                            SHOP_ACTOR[i] = CreateActor( DONUTS_NPC, 380.7887, -187.3940, 1000.6328, 96.2159 );
                        }
                        case SHOP_TYPE_MEATFACTORY:
                        {
                            SHOP_ACTOR[i] = CreateActor( MEATFACTORY_NPC, 960.6079, 2097.5723, 1011.0229, 3.0851 );
                        }
                        case SHOP_TYPE_CRACKFACTORY:
                        {
                            SHOP_ACTOR[i] = CreateActor( CRACKFACTORY_NPC, 2581.0588, -1286.1293, 1044.1250, 181.0835 );
                        }
                        case SHOP_TYPE_CARSCHOOL:
                        {
                            SHOP_ACTOR[i] = CreateActor( CARSCHOOL_NPC, -2021.7914, -115.7214, 1035.1719, 96.8661 );
                        }
                        case SHOP_TYPE_TOILET:
                        {
                            SHOP_ACTOR[i] = CreateActor( TOILET_NPC, -217.4959, 1410.8348, 27.7734, 99.3589 );
                        }
                        case SHOP_TYPE_LSART:
                        {
                            SHOP_ACTOR[i] = CreateActor( LSART_NPC, 1721.7480, -1653.9374, 20.9688, 356.9266 );
                        }
                        case SHOP_TYPE_BIKESCHOOL:
                        {
                            SHOP_ACTOR[i] = CreateActor( BIKESCHOOL_NPC, 1502.4609, 1307.9852, 1093.2891, 93.1060 );
                        }
                        case SHOP_TYPE_CHURCH:
                        {
                            SHOP_ACTOR[i] = CreateActor( CHURCH_NPC, -2022.6702, 1003.4549, 1419.4969, 356.2850 );
                        }
                        case SHOP_TYPE_HOSPITAL:
                        {
                            SHOP_ACTOR[i] = CreateActor( HOSPITAL_NPC, -25.7530, 151.4989, 999.0569, 88.1113 );
                        }
                        case SHOP_TYPE_PRISON:
                        {
                            SHOP_ACTOR[i] = CreateActor( PRISON_NPC, -1969.4702, 307.0227, 1552.1387, 358.7545 );
                        }
                        case SHOP_TYPE_PLANE:
                        {
                            SHOP_ACTOR[i] = CreateActor( PILOT_NPC, 1.5819, 23.2062, 1199.5938, 358.1417 );
                        }
                        case CHURCH_SECONDARY:
                        {
                            SHOP_ACTOR[i] = CreateActor( CHURCH_NPC, 366.8790, 2324.0217, 1890.6047, 273.2509 );
                        }
                        case BAR_SECONDARY:
                        {
                            SHOP_ACTOR[i] = CreateActor( BAR_NPC, -223.3072, 1406.3784, 27.7734, 92.8256 );
                        }
                        case PD_SECONDARY:
                        {
                            SHOP_ACTOR[i] = CreateActor( POLICE_NPC, -501.3162, 296.3616, 2001.2312, 174.4329 );
                        }
                    }
                    SetActorVirtualWorld( SHOP_ACTOR[i], db_get_field_assoc_int(Result, "virtualworld" ));
                }
                else print("ARRAY OUT OF BOUNDS DUE TO SHOP ACTORS, REWVIEW CODE");
            }
            db_free_result(Result);
        }
    }
    return 1;
}

hook OnGameModeExit() 
{ 
    KillTimer(RespawnCars_Timer);
    db_close(RDZ_Database);
    return 1; 
}  

hook OnVehicleDeath(vehicleid, killerid)
{
    new Float:health;
    GetVehicleHealth(vehicleid, health);
    new Float:Angle;
    GetVehicleZAngle(vehicleid, Angle);
    foreach(new i: Player)
    {
        if(vehicleid == Player_TelecarID[i])
        {
            if(health > 600.000)
            {
                SetVehiclePos(vehicleid, -1638.8586, 1202.3535, 6.8591);
                UpdateTelecarPos(i);
                SetVehicleZAngle(vehicleid, Angle);

            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(KEY_PRESSED(KEY_WALK))
    {
        new    
            DBResult: Result; 
        new buf[STRING_SIZE_QUERY];

        Result = db_query(RDZ_Database, "SELECT * FROM `userhouse` ORDER BY `userid` DESC LIMIT 1");
        
        new MAX_ROWS_ID = db_get_field_int(Result); 


        db_free_result(Result);

        if(MAX_ROWS_ID != 0)
        {    
            for(new i; i <= MAX_ROWS_ID; i++)
            {
                format(buf, sizeof buf, "SELECT * FROM userhouse WHERE userid = %d LIMIT 1", i);
                Result = db_query(RDZ_Database, buf);

                if (db_num_rows(Result))
                { 
                    if(db_get_field_assoc_int(Result, "locked") == 2 || db_get_field_assoc_int(Result, "locked") == 1 )
                    {
                        db_free_result(Result);
                        continue;
                    }

                    INTERIOR_ENTRY( playerid, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "br"), db_get_field_assoc_int(Result, "interior"), db_get_field_assoc_int(Result, "virtualworld"), db_get_field_assoc_int(Result, "secondworld") );
                    INTERIOR_ENTRY( playerid, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "ar"), db_get_field_assoc_int(Result, "secondinterior"), db_get_field_assoc_int(Result, "secondworld"), db_get_field_assoc_int(Result, "virtualworld") );
                }
                db_free_result(Result);
            }
        }


        Result = db_query(RDZ_Database, "SELECT * FROM `rdzshops` ORDER BY `shopid` DESC LIMIT 1");
        
        MAX_ROWS_ID = db_get_field_int(Result); 
        db_free_result(Result);

        if(MAX_ROWS_ID != 0)
        {    
            for(new i; i <= MAX_ROWS_ID; i++)
            {
                format(buf, sizeof buf, "SELECT * FROM rdzshops WHERE shopid = %d LIMIT 1", i);
                Result = db_query(RDZ_Database, buf);

                if (db_num_rows(Result))
                { 
                    if(db_get_field_assoc_int(Result, "locked") == 1 || i == 23 || i == 24)
                    {
                        db_free_result(Result);
                        continue;
                    }

                    if(i == 1)
                    {
                        if(db_get_field_assoc_int(Result, "locked") == LOCKED_STATS_SPECIAL_MAP)
                        {
                            INTERIOR_ENTRY_SPECIAL( playerid, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "br"), db_get_field_assoc_int(Result, "interior"), SHOPS_DB_START_VWORLD, db_get_field_assoc_int(Result, "secondworld") );
                            INTERIOR_ENTRY_SPECIAL( playerid, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "ar"), db_get_field_assoc_int(Result, "secondinterior"), db_get_field_assoc_int(Result, "secondworld"), SHOPS_DB_START_VWORLD );
                        }
                        else
                        {
                            INTERIOR_ENTRY( playerid, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "br"), db_get_field_assoc_int(Result, "interior"), SHOPS_DB_START_VWORLD, db_get_field_assoc_int(Result, "secondworld") );
                            INTERIOR_ENTRY( playerid, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "ar"), db_get_field_assoc_int(Result, "secondinterior"), db_get_field_assoc_int(Result, "secondworld"), SHOPS_DB_START_VWORLD );
                        }
                    }
                    else
                    {
                        if(db_get_field_assoc_int(Result, "locked") == LOCKED_STATS_SPECIAL_MAP)
                        {
                            INTERIOR_ENTRY_SPECIAL( playerid, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "br"), db_get_field_assoc_int(Result, "interior"), db_get_field_assoc_int(Result, "virtualworld"), db_get_field_assoc_int(Result, "secondworld") );
                            INTERIOR_ENTRY_SPECIAL( playerid, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "ar"), db_get_field_assoc_int(Result, "secondinterior"), db_get_field_assoc_int(Result, "secondworld"), db_get_field_assoc_int(Result, "virtualworld") );
                        }
                        else
                        {
                            INTERIOR_ENTRY( playerid, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "br"), db_get_field_assoc_int(Result, "interior"), db_get_field_assoc_int(Result, "virtualworld"), db_get_field_assoc_int(Result, "secondworld") );
                            INTERIOR_ENTRY( playerid, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_float(Result, "ar"), db_get_field_assoc_int(Result, "secondinterior"), db_get_field_assoc_int(Result, "secondworld"), db_get_field_assoc_int(Result, "virtualworld") );
                        }
                    }
                }
                db_free_result(Result);
            }
        }

        db_free_result(Result);
    }
    return 1;
}

hook OnPlayerRequestSpawn(playerid)
{
    if(!PLoggedIN{playerid}) return 0;

    if(RDZPlayer[playerid][USER_RESPAWN]) RDZPlayer[playerid][USER_SKIN] = GetPlayerSkin(playerid);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
    {
        RemovePlayerAttachedObject(playerid, 0);
    }
    GivePlayerMoney(playerid, 100);//Giving back the taken $100
    if(!PLoggedIN{playerid}) Kick(playerid);

    if(GetPlayerWantedLevel(playerid) > 0)
    {
        foreach(new i: Player)
        {
            SetPlayerMarkerForPlayer( i, playerid, ( GetPlayerColor( playerid ) & 0xFF0000FF ) );
        }
    }

    if(RDZPlayer[playerid][USER_RESPAWN]) OnPlayerSpawnEx(playerid, CASE_REGISTER);

    if(RDZPlayer[playerid][USER_BAN])
    {
        new BBN_String[STRING_SIZE_MEDIUM];
        format(BBN_String, sizeof BBN_String, "Player %s was banned again, reason was: %s", RDZPlayer[playerid][USER_NAME], RDZPlayer[playerid][USER_COB]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, BBN_String, MESSAGE_CASE_JANITOR);
        BanEx(playerid, "Ban evading");
    }

	SetPlayerWantedLevel(playerid, RDZPlayer[playerid][USER_WANTED]);
    if(GetPlayerWantedLevel(playerid) > 0) SetPlayerColor(playerid, RDZ_COLOR_WANTED);
    if(!IsPlayerOnDuty(playerid)) SetPlayerSkin(playerid, RDZPlayer[playerid][USER_SKIN]);
	
	if(RDZPlayer[playerid][USER_SEX] == USER_GENDER_NULL)
	{
		Dialog_Show(playerid, DIALOG_GENDER, DIALOG_STYLE_MSGBOX, "Gender choosing", "Please pick your gender!", "Male", "Female" ); 
	}
    return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    if(issuerid != INVALID_PLAYER_ID && IsPlayerConnected(issuerid) && issuerid >= 0 && issuerid <= MAX_PLAYERS && !IsPlayerInEvent(playerid))
    {
        if(!selfDefense{playerid})
        {
            if(!selfDefense{issuerid} && !(GetPlayerWantedLevel(playerid) > 0 && IsPlayerCop(issuerid)) )
            {
                if(weaponid != WEAPON_SPRAYCAN)
                {
                    selfDefense{playerid} = true;
                    sdTimer[playerid] = SetTimerEx("resetSD", SELF_DEFENSE_TIME, false, "i", playerid);
                    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Self defense [ACTIVATED]!", MESSAGE_CASE_JARVIS);
                }
            }
        }
    }

    if(issuerid != INVALID_PLAYER_ID && IsPlayerConnected(issuerid) && issuerid >= 0 && issuerid <= MAX_PLAYERS)
    {
        if(weaponid == WEAPON_SPRAYCAN)
        {
            new Float:phealth;
            GetPlayerHealth(playerid, phealth);
            SetPlayerHealth(playerid, phealth+amount);
            GetPlayerHealth(playerid, phealth);
            if(phealth > 100.00) SetPlayerHealth(playerid, 100.00);
        }
    }
    return 1;
}

forward resetSD(playerid);
public resetSD(playerid)
{
    selfDefense{playerid} = false;
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Self defense [DEACTIVATED]!", MESSAGE_CASE_JARVIS);
    return 1; 
}

hook OnPlayerText(playerid, text[])
{
	if(RDZPlayer[playerid][USER_MUTE] || !PLoggedIN{playerid})
	{
		return 0;
	}

	new SpyString[STRING_SIZE_LARGE*2], pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, sizeof pName);
	format(SpyString, sizeof(SpyString), "%s: %s", Player_TempName[playerid], text);
	DCC_SendChannelMessage(SpyChatChannel, SpyString); 

    //Replace these with ur in-game name
	if(!strcmp(pName, "Andy[RDZ]", true))
	{
        if(text[0] == '!' && text[1] == 'p' && text[2] == ' ') {
            DCC_SendChannelMessage(IGNMusic, text);
            return 0;
        }
	}
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{        
    new 
        Query[STRING_SIZE_QUERY], 
        DBResult: Result; 
    if(!PLoggedIN{playerid})
    {
        format(Query, sizeof Query, "SELECT password FROM userprimary WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]); 
        Result = db_query(RDZ_Database, Query); 
        
        if (db_num_rows(Result))
        { 
            db_get_field_assoc(Result, "password", RDZPlayer[playerid][USER_PASSWORD], 129);
            Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", "Type in your password below to log in.", "Login", "Leave");
            SetPlayerSkin(playerid, GetSkinFromDB(playerid));
        } 
        else 
        {  
            Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register", "Type in a password below to register an account.", "Register", "Leave");
        } 
        db_free_result(Result);
    }

    if(IsPlayerRegistered(Player_TempName[playerid]) && !RDZPlayer[playerid][USER_RESPAWN])
    {
        format(Query, sizeof Query, "SELECT * FROM userdetails WHERE username = '%q' LIMIT 1", Player_TempName[playerid]);
        Result = db_query(RDZ_Database, Query);
        new skin;
        if (db_num_rows(Result))
        { 
            skin = db_get_field_assoc_int(Result, "skinid"); 
        }
        SetPlayerSkin(playerid, skin);
    }
    return 1;
}

stock playerColors[99] = {
0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF, 0xf0e68cFF, 0x778899FF, 0xFF1493FF, 0xF4A460FF, 0xEE82EEFF, 0xFFD720FF, 
0x8b4513FF, 0x4949A0FF, 0x148b8bFF, 0x14ff7fFF, 0x556b2fFF, 0x0FD9FAFF, 0x10DC29FF, 0x534081FF, 0x0495CDFF, 0xEF6CE8FF, 0xBD34DAFF, 
0x247C1BFF, 0x0C8E5DFF, 0x635B03FF, 0xCB7ED3FF, 0x65ADEBFF, 0x5C1ACCFF, 0xF2F853FF, 0x11F891FF, 0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 
0x275222FF, 0xF09F5BFF, 0x3D0A4FFF, 0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF, 0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF, 
0x057F94FF, 0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF, 0x93AB1CFF, 0x95BAF0FF, 0x369976FF, 0x18F71FFF, 0x4B8987FF, 
0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF, 0x2D74FDFF, 0x3C1C0DFF, 0x12D6D4FF, 0x2A51E2FF, 0xE3AC1, 0x3FE65CFF2FF, 
0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF, 0x42ACF5FF, 0x2FD9DEFF, 0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF, 0x94436EFF, 0xC1F7ECFF, 
0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF, 0x3214AAFF, 0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF, 0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 
0x9F945CFF, 0xDCDE3DFF, 0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF, 0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF, 0xD8C762FF
};

static playerSkins[62] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 31, 32, 
    33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62
};

hook OnPlayerConnect(playerid)
{
    new     
        DBResult: Result;

    SetPlayerColor(playerid, playerColors[random(sizeof(playerColors))]);
    new
        tmp[RDZ_PLAYERS_STATS];
    RDZPlayer[playerid] = tmp;

    new rulesString[564];
    strcat(rulesString, "{FF3333}WARNING 18+ Server, Please Read The Following Message");
    strcat(rulesString, "\n{99FF00}contains language and themes not suitable for young players");
    strcat(rulesString, "\n{99FF00}No cheating, hacking or gameplay mods of any kind or shape");
    strcat(rulesString, "\n{99FF00}Always respect the server administrators no matter what");
    strcat(rulesString, "\n{99FF00}No abusing, flaming, trolling or any racist remarks");
    strcat(rulesString, "\n\n{CCCCCC}This drift server was originally made by RogueDrifter (Andy)");
    strcat(rulesString, "\n\n{CCCCCC}>>> {FFFFFF}Click 'Accept' to Agree or 'Decline' to Quit.");

    Dialog_Show(playerid, DIALOG_RULES_TOS, DIALOG_STYLE_MSGBOX, "RULES", rulesString, "Accept", "Decline");
    
    GetPlayerName(playerid, RDZPlayer[playerid][USER_NAME], MAX_PLAYER_NAME); 
    GetPlayerIp(playerid, RDZPlayer[playerid][USER_VarIP], MAX_IP_LENGTH);

    GetPlayerIp(playerid, Player_IP[playerid], MAX_IP_LENGTH);
    gpci(playerid, Player_GPCI[playerid], MAX_GPCI_LENGTH);
    GetPlayerName(playerid, Player_TempName[playerid], MAX_PLAYER_NAME);

    gpci(playerid, RDZPlayer[playerid][USER_Vargpci], MAX_GPCI_LENGTH);

    RDZPlayer[playerid][USER_CONTICKS] = gettime();

    new temp_Version[STRING_SIZE_MEDIUM];
    GetPlayerVersion(playerid, temp_Version, sizeof temp_Version);
    new string[STRING_SIZE_LARGE];
    format(string, sizeof string, "{00D900}.: ( {AFAFAF}%s{00D900} ) joined the server ( {AFAFAF}Joining{00D900} ) -%s :.", RDZPlayer[playerid][USER_NAME], temp_Version);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_NULL);

    new gpcihash[STRING_SIZE_MEDIUM];
    GetGPCIFromDB(Player_TempName[playerid], gpcihash, sizeof gpcihash);
    if(IsGpciBanned(gpcihash))
    {
        format(string, sizeof string, "Player %s was kicked, reason: Possible ban evading", RDZPlayer[playerid][USER_NAME]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
        Kick(playerid);
    }

    if(IsNameBanned(RDZPlayer[playerid][USER_NAME]))
    {
        format(string, sizeof string, "Player %s was kicked, reason: NAME BANNED", RDZPlayer[playerid][USER_NAME]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
        Kick(playerid);
    }

    if(IsStringInvalid(Player_TempName[playerid]) && !IsPlayerRegistered(Player_TempName[playerid]))
    {
        format(string, sizeof string, "Player %s was kicked, reason: Invalid characters in the user name", RDZPlayer[playerid][USER_NAME]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please remove any numbers/symbols from your name and rejoin", MESSAGE_CASE_JARVIS);
        Kick(playerid);
    }

    if( strfind( Player_TempName[playerid], "[RDZ]", true ) != -1 )
    {
        new 
        Query[STRING_SIZE_QUERY];

        format(Query, sizeof Query, "SELECT username FROM userclan WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]); 
        Result = db_query(RDZ_Database, Query); 

        if (!db_num_rows(Result))
        { 
            format(string, sizeof string, "Player %s was kicked, reason: Having [RDZ] clan tag", RDZPlayer[playerid][USER_NAME]);
            SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
            Kick(playerid);
        } 
        db_free_result(Result);
    }
    if(!IsPlayerNPC(playerid))
    {
        ProcessAkaIp(playerid);
        ProcessAkaGpci(playerid);
    }

    //cstats
    new accounts[NAMES_MULTI_FROMDB][MAX_PLAYER_NAME], c_string[STRING_SIZE_LARGE * 3];
    GetAKAIP(playerid, accounts);

    if(accounts[0][0] != '\0')
    {
        for(new i; i < sizeof(accounts); i++)   
        {   
            if(accounts[i][0] == '\0') break;   
            format(c_string, sizeof(c_string), "%s{CCCCCC}PlayerName: %s\n", c_string, accounts[i]);   
        }   
        format(c_string, sizeof(c_string), "{00FF00}Full player names under the same IP for %s:\n{CCCCCC}%s", Player_TempName[playerid], c_string);  
    }

    new g_string[STRING_SIZE_LARGE *3];
    GetAKAGpci(playerid, accounts);
    if(accounts[0][0] != '\0')
    {
        for(new i; i < sizeof(accounts); i++)   
        {   
            if(accounts[i][0] == '\0') break;   
            format(g_string, sizeof(g_string), "%s{CCCCCC}PlayerName: %s\n", g_string, accounts[i]);   
        }   
        format(g_string, sizeof(g_string), "{00FF00}Full player names under the same GPCI for %s:\n{CCCCCC}%s", Player_TempName[playerid], g_string);  
    }

    new z_string[STRING_SIZE_LARGE * 6];
    format(z_string, sizeof(z_string), "%s\n%s", c_string, g_string);
    foreach(new i: Player)
    {
        if(adminCStats{i})
        {
            Dialog_Show(i, DIALOG_AKA, DIALOG_STYLE_MSGBOX, "{CCCCCC}All Player Accounts", z_string, "Okay", "");  
        }
    }
    //
    return 1;
}

forward OnPasswordHashed(playerid);
public OnPasswordHashed(playerid)
{
    GetPlayerIp(playerid, RDZPlayer[playerid][USER_ConstIP], MAX_IP_LENGTH);
    gpci(playerid, RDZPlayer[playerid][USER_Constgpci], MAX_GPCI_LENGTH);

    bcrypt_get_hash(RDZPlayer[playerid][USER_PASSWORD]);

    new 
        Query[STRING_SIZE_QUERY]; 

    format(Query, sizeof Query, "INSERT INTO userprimary (username, password, constip, constgpci, varip, vargpci) VALUES ('%q', '%q', '%q', '%q', '%q', '%q')", RDZPlayer[playerid][USER_NAME], RDZPlayer[playerid][USER_PASSWORD], RDZPlayer[playerid][USER_ConstIP], RDZPlayer[playerid][USER_Constgpci], RDZPlayer[playerid][USER_ConstIP], RDZPlayer[playerid][USER_Constgpci]);
    db_query(RDZ_Database, Query);
	
	format(Query, sizeof Query, "INSERT INTO userdetails (username) VALUES ('%q')", RDZPlayer[playerid][USER_NAME]);
    db_query(RDZ_Database, Query); 
    
    format(Query, sizeof Query, "INSERT INTO usertcar (username) VALUES ('%q')", RDZPlayer[playerid][USER_NAME]);
    db_query(RDZ_Database, Query); 
    
	format(Query, sizeof Query, "INSERT INTO usermisc (username) VALUES ('%q')", RDZPlayer[playerid][USER_NAME]);
    db_query(RDZ_Database, Query); 
	
	format(Query, sizeof Query, "INSERT INTO userpositions (username) VALUES ('%q')", RDZPlayer[playerid][USER_NAME]);
    db_query(RDZ_Database, Query); 
    	
	format(Query, sizeof Query, "INSERT INTO userextended (username) VALUES ('%q')", RDZPlayer[playerid][USER_NAME]);
    db_query(RDZ_Database, Query); 

    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Hi, Thanks for registering! We've logged you in automatically this time!", MESSAGE_CASE_EMPTY);
    RDZPlayer[playerid][USER_COLOR] = playerColors[random(sizeof(playerColors))];
    RDZPlayer[playerid][USER_SKIN] = playerSkins[random(sizeof(playerSkins))];
    new     
        DBResult: Result; 
                 
    Result = db_query(RDZ_Database, "SELECT last_insert_rowid()"); 
    RDZPlayer[playerid][USER_ID] = db_get_field_int(Result); 

    PLoggedIN{playerid} = true;
    SpawnPlayer(playerid);
    OnPlayerSpawnEx(playerid, CASE_REGISTER);

    db_free_result(Result); 
    return 1;
}

hook OnPlayerTargetActor(playerid, actorid, weaponid)
{
    new DBResult:Result;
    new buf[STRING_SIZE_QUERY];
	if(weaponid == WEAPON_FISTS)
	{
        Result = db_query(RDZ_Database, "SELECT * FROM `rdzshops` ORDER BY `shopid` DESC LIMIT 1");
    
        new MAX_ROWS_ID = db_get_field_int(Result); 

        db_free_result(Result);

        if(MAX_ROWS_ID != 0)
        {    
            format(buf, sizeof buf, "SELECT * FROM rdzshops WHERE virtualworld = %d LIMIT 1", GetPlayerVirtualWorld(playerid));
            Result = db_query(RDZ_Database, buf);

            if (db_num_rows(Result))
            { 
                if(GetPlayerInterior(playerid) == db_get_field_assoc_int(Result, "interior"))
                {
                    switch(db_get_field_assoc_int(Result, "shoptype"))
                    {
                        case SHOP_TYPE_247:
                        {
                            Dialog_Show(playerid, DIALOG_SHOPDEALER, DIALOG_STYLE_LIST, "24/7 Shop list", "GPS			$350", "Select", "Cancel");
                        }
                        case SHOP_TYPE_AMMU:
                        {
                            Dialog_Show(playerid, DIALOG_WEAPONS, DIALOG_STYLE_LIST, "Weapons", "Deagle			500$\nShotGun		600$\nMicroUZI		500$\nMP5			500$\nTec9			500$\nKatana			25$\nSpas12			750$\nAK47			750$\nM4a1			750$\nSniperRifle		900$\nCountryRifle		1000$\nArmour			1000$\nParachute		550$\nCamera			750$\nShovel			250$", "Select", "Close");
                        }
                        case SHOP_TYPE_BURGERSHOT:
                        {
                            Dialog_Show(playerid, DIALOG_BURGERSHOT, DIALOG_STYLE_LIST, "Burger shot", "Burger			$25", "Select", "Cancel");
                        }
                        case SHOP_TYPE_CLUCKINBELL:
                        {
                            Dialog_Show(playerid, DIALOG_CLUCKINBELL, DIALOG_STYLE_LIST, "Cluckin bell", "Chicken			$75", "Select", "Cancel");
                        }
                        case SHOP_TYPE_PIZZASTACK:
                        {
                            Dialog_Show(playerid, DIALOG_PIZZASTACK, DIALOG_STYLE_LIST, "Pizza stack", "Pizza			$125", "Select", "Cancel");
                        }
                        case SHOP_TYPE_BARBER:
                        {
                            Dialog_Show(playerid, DIALOG_BARBER, DIALOG_STYLE_LIST, "Barber shop", "Hair-style 1(White)			$250\nHair-style 2(Dark grey)			$250\nHair-style 3(Clown wig)			$250\nHair-style 4(Black)			$250\nRemove Hair-style", "Select", "Cancel");
                        }
                        case SHOP_TYPE_GYM:
                        {
                            Dialog_Show(playerid, DIALOG_GYM, DIALOG_STYLE_LIST, "Gym", "Normal			$0\nBoxing			$700\nKung-fu			$700\nKnee-head			$700\nGrab-kick			$700\nElbow			$700", "Select", "Cancel");
                        }
                        case SHOP_TYPE_POLICE, LS_POLICE, LV_POLICE, PD_SECONDARY:
                        {
                            if(!IsPlayerOnDuty(playerid))
                            {
                                SetDutyStats(playerid, true);
                            }
                            else  Dialog_Show(playerid, DIALOG_DUTYSTATE, DIALOG_STYLE_MSGBOX, "RDZPD", "Do you wish to go off duty?", "Yes", "No");
                        }
                        case SHOP_TYPE_TATTOO:
                        {
                            Dialog_Show(playerid, DIALOG_TATTOO, DIALOG_STYLE_LIST, "Tattoo shop", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_SEXSHOP:
                        {
                            Dialog_Show(playerid, DIALOG_SEXSHOP, DIALOG_STYLE_LIST, "Choose gender", "Male			1 Rep\nFemale       1 Rep", "Select", "Cancel");
                        }
                        case SHOP_TYPE_CLOTHES, VICTIM_SHOP:
                        {
                            Dialog_Show(playerid, DIALOG_CLOTHES, DIALOG_STYLE_LIST, "Clothes shop", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_MOTEL:
                        {
                            Dialog_Show(playerid, DIALOG_MOTEL, DIALOG_STYLE_LIST, "Motel", "Rent			$500\nCheck-in", "Select", "Cancel");
                        }
                        case SHOP_TYPE_BAR, BAR_SECONDARY, SHOP_TYPE_CASINO, SHOP_TYPE_CLUB, SHOP_TYPE_NIGHTCLUB:
                        {
                            Dialog_Show(playerid, DIALOG_BAR, DIALOG_STYLE_LIST, "Bar", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_BANK:
                        {
                            Dialog_Show(playerid, DIALOG_BANK, DIALOG_STYLE_LIST, "Bank", "Balance\nWithdraw\nDeposit", "Select", "Cancel");
                        }
                        case SHOP_TYPE_GASINTERIOR:
                        {
                            Dialog_Show(playerid, DIALOG_GASINTERIOR, DIALOG_STYLE_LIST, "Gas-station shop", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_JANITORROOM:
                        {
                            Dialog_Show(playerid, DIALOG_JANITORROOM, DIALOG_STYLE_LIST, "Janitor room", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_RESTAURANT:
                        {
                            Dialog_Show(playerid, DIALOG_DINER, DIALOG_STYLE_LIST, "Diner", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_DONUTS:
                        {
                            Dialog_Show(playerid, DIALOG_DONUTS, DIALOG_STYLE_LIST, "Donuts shop", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_MEATFACTORY:
                        {
                            Dialog_Show(playerid, DIALOG_MEATFACTORY, DIALOG_STYLE_LIST, "Meat factory", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_CRACKFACTORY:
                        {
                            Dialog_Show(playerid, DIALOG_CRACKFACTORY, DIALOG_STYLE_LIST, "Crack factory", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_CARSCHOOL:
                        {
                            Dialog_Show(playerid, DIALOG_CARSCHOOL, DIALOG_STYLE_LIST, "Car school", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_TOILET:
                        {
                            Dialog_Show(playerid, DIALOG_TOILET, DIALOG_STYLE_LIST, "Toilet", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_LSART:
                        {
                            Dialog_Show(playerid, DIALOG_LSTART, DIALOG_STYLE_LIST, "Art museum", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_BIKESCHOOL:
                        {
                            Dialog_Show(playerid, DIALOG_BIKESCHOOL, DIALOG_STYLE_LIST, "Bike school", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_CHURCH, CHURCH_SECONDARY:
                        {
                            Dialog_Show(playerid, DIALOG_CHURCH, DIALOG_STYLE_LIST, "Church", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_HOSPITAL:
                        {
                            Dialog_Show(playerid, DIALOG_HOSPITAL, DIALOG_STYLE_LIST, "Hospital", "Heal			$100", "Select", "Cancel");
                        }
                        case SHOP_TYPE_PRISON:
                        {
                            Dialog_Show(playerid, DIALOG_PRISON, DIALOG_STYLE_LIST, "Prison", "NULL			$0", "Select", "Cancel");
                        }
                        case SHOP_TYPE_PLANE:
                        {
                            Dialog_Show(playerid, DIALOG_PLANE, DIALOG_STYLE_LIST, "Plane", "NULL			$0", "Select", "Cancel");
                        }
                    }
                }
            }
            db_free_result(Result);
        }
	}
    return 1;
}

forward OnPasswordChecked(playerid);
public OnPasswordChecked(playerid)
{
    new bool:match = bcrypt_is_equal();
    if(match)
    {
        new 
            DBResult: Result; 
        new
            buf[STRING_SIZE_LARGE];
            
        format(buf, sizeof buf, "SELECT * FROM userprimary WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]);
        Result = db_query(RDZ_Database, buf);
             
        if (db_num_rows(Result))
        { 
                
            RDZPlayer[playerid][USER_ID] = db_get_field_assoc_int(Result, "userid"); 
            RDZPlayer[playerid][USER_GPS] = db_get_field_assoc_int(Result, "usergps"); 
            RDZPlayer[playerid][USER_ADMIN] = db_get_field_assoc_int(Result, "admin"); 
            RDZPlayer[playerid][USER_VIP] = db_get_field_assoc_int(Result, "viplevel");
            RDZPlayer[playerid][USER_HANDCASH] = db_get_field_assoc_int(Result, "cash");
            RDZPlayer[playerid][USER_KICKCOUNT] = db_get_field_assoc_int(Result, "kickcount");
			RDZPlayer[playerid][USER_JAIL] = db_get_field_assoc_int(Result, "injail");
			RDZPlayer[playerid][USER_JTIME] = db_get_field_assoc_int(Result, "jailtime");
            db_get_field_assoc(Result, "constip", RDZPlayer[playerid][USER_ConstIP], MAX_IP_LENGTH);
            db_get_field_assoc(Result, "constgpci", RDZPlayer[playerid][USER_Constgpci], MAX_GPCI_LENGTH);
			db_get_field_assoc(Result, "mutereason", RDZPlayer[playerid][USER_MREASON], STRING_SIZE_SMALL);
            db_get_field_assoc(Result, "sampversion", RDZPlayer[playerid][USER_VERSION], STRING_SIZE_MEDIUM);
			db_get_field_assoc(Result, "laston", RDZPlayer[playerid][USER_LASTON], STRING_SIZE_MEDIUM);
        }

        db_free_result(Result);
        format(buf, sizeof buf, "SELECT * FROM userdetails WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]);
        Result = db_query(RDZ_Database, buf);

        if (db_num_rows(Result))
        {
			
            RDZPlayer[playerid][USER_COLOR] = db_get_field_assoc_int(Result, "color"); 
			RDZPlayer[playerid][USER_SEX] = db_get_field_assoc_int(Result, "usersex"); 
            RDZPlayer[playerid][USER_LEVEL] = db_get_field_assoc_int(Result, "level"); 
            RDZPlayer[playerid][USER_EXP] = db_get_field_assoc_int(Result, "experience"); 
            RDZPlayer[playerid][USER_RESPECT] = db_get_field_assoc_int(Result, "reputation"); 
            RDZPlayer[playerid][USER_PHOURS] = db_get_field_assoc_int(Result, "playinghours");             
            RDZPlayer[playerid][USER_SKIN] = db_get_field_assoc_int(Result, "skinid"); 
            RDZPlayer[playerid][USER_KILLS] = db_get_field_assoc_int(Result, "playerkills");
            RDZPlayer[playerid][USER_DEATHS] = db_get_field_assoc_int(Result, "playerdeaths");
			RDZPlayer[playerid][USER_WANTED] = db_get_field_assoc_int(Result, "userwanted");
        }

        db_free_result(Result);
        format(buf, sizeof buf, "SELECT * FROM userextended WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]);
        Result = db_query(RDZ_Database, buf);

        if (db_num_rows(Result))
        {
            RDZPlayer[playerid][USER_JOB] = db_get_field_assoc_int(Result, "job"); 
			RDZPlayer[playerid][USER_RANK] = db_get_field_assoc_int(Result, "coprank"); 
            RDZPlayer[playerid][USER_ARRESTS] = db_get_field_assoc_int(Result, "arrests"); 
            RDZPlayer[playerid][USER_ARRESTED] = db_get_field_assoc_int(Result, "arrested"); 
            RDZPlayer[playerid][USER_CRIMES] = db_get_field_assoc_int(Result, "crimes"); 
            RDZPlayer[playerid][USER_FUELCAN] = db_get_field_assoc_int(Result, "fuelcan"); 
        }

        db_free_result(Result);
        format(buf, sizeof buf, "SELECT * FROM usertcar WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]);
        Result = db_query(RDZ_Database, buf);

        if (db_num_rows(Result))
        {
            RDZPlayer[playerid][USER_TELECAR] = db_get_field_assoc_int(Result, "model");
            RDZPlayer[playerid][CAR_EXHAUSTS] = db_get_field_assoc_int(Result, "exhausts");
            RDZPlayer[playerid][CAR_SPOILERS] = db_get_field_assoc_int(Result, "spoiler");
            RDZPlayer[playerid][CAR_WHEELS] = db_get_field_assoc_int(Result, "wheels");
            RDZPlayer[playerid][CAR_FBUMBER] = db_get_field_assoc_int(Result, "frontbumber");
            RDZPlayer[playerid][CAR_RBUMBER] = db_get_field_assoc_int(Result, "rearbumber");
            RDZPlayer[playerid][CAR_SSKIRT] = db_get_field_assoc_int(Result, "sideskirt");
            RDZPlayer[playerid][CAR_ROOF] = db_get_field_assoc_int(Result, "roof");
            RDZPlayer[playerid][CAR_PJOB] = db_get_field_assoc_int(Result, "paintjob");
            RDZPlayer[playerid][CAR_FCOLOR] = db_get_field_assoc_int(Result, "fcolor");
            RDZPlayer[playerid][CAR_SCOLOR] = db_get_field_assoc_int(Result, "scolor");

            RDZPlayer[playerid][CAR_X] =db_get_field_assoc_float(Result, "floatx");
            RDZPlayer[playerid][CAR_Y] =db_get_field_assoc_float(Result, "floaty");
            RDZPlayer[playerid][CAR_Z] =db_get_field_assoc_float(Result, "floatz");
            RDZPlayer[playerid][CAR_R] =db_get_field_assoc_float(Result, "floatr");
        }

        db_free_result(Result);
        format(buf, sizeof buf, "SELECT * FROM usermisc WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]);
        Result = db_query(RDZ_Database, buf);
        
        if (db_num_rows(Result))
        {

            RDZPlayer[playerid][USER_DRIFTSCORE] = db_get_field_assoc_int(Result, "driftscore");
            RDZPlayer[playerid][USER_BESTRIVAL] = db_get_field_assoc_int(Result, "bestrival"); 
            RDZPlayer[playerid][USER_ODWON] = db_get_field_assoc_int(Result, "odwon");
            RDZPlayer[playerid][USER_ODLOST] = db_get_field_assoc_int(Result, "odlost");
            RDZPlayer[playerid][USER_BANK] = db_get_field_assoc_int(Result, "bankamount");
            RDZPlayer[playerid][USER_SAVER] = db_get_field_assoc_int(Result, "savermoney");
            RDZPlayer[playerid][USER_INTEREST] =db_get_field_assoc_float(Result, "bankinterest");
            RDZPlayer[playerid][USER_BAN] =db_get_field_assoc_int(Result, "namebanned");
			RDZPlayer[playerid][USER_MUTE] =db_get_field_assoc_int(Result, "muted");
			
            db_get_field_assoc(Result, "causeofban", RDZPlayer[playerid][USER_COB], MAX_BAN_REASON_LENGTH);

        }

        db_free_result(Result);
        format(buf, sizeof buf, "SELECT * FROM userpositions WHERE username = '%q' LIMIT 1", RDZPlayer[playerid][USER_NAME]);
        Result = db_query(RDZ_Database, buf);

        if (db_num_rows(Result))
        {

            RDZPlayer[playerid][USER_INTERIOR] = db_get_field_assoc_int(Result, "interior"); 
            RDZPlayer[playerid][USER_VIRTUALWORLD] = db_get_field_assoc_int(Result, "virtualworld"); 
            RDZPlayer[playerid][USER_X] = db_get_field_assoc_float(Result, "posx"); 
            RDZPlayer[playerid][USER_Y] = db_get_field_assoc_float(Result, "posy"); 
            RDZPlayer[playerid][USER_Z] =db_get_field_assoc_float(Result, "posz"); 
            RDZPlayer[playerid][USER_R] =db_get_field_assoc_float(Result, "posr"); 
			RDZPlayer[playerid][USER_VX] = db_get_field_assoc_float(Result, "vposx"); 
            RDZPlayer[playerid][USER_VY] = db_get_field_assoc_float(Result, "vposy"); 
            RDZPlayer[playerid][USER_VZ] =db_get_field_assoc_float(Result, "vposz"); 
            RDZPlayer[playerid][USER_VR] =db_get_field_assoc_float(Result, "vposr"); 
        }

        if (db_num_rows(Result))
        {
            SetPlayerScore(playerid, RDZPlayer[playerid][USER_DRIFTSCORE]);
            GivePlayerMoney(playerid, RDZPlayer[playerid][USER_HANDCASH]);
            PLoggedIN{playerid} = true;

            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Good job you've logged in bud welcome back!", MESSAGE_CASE_EMPTY);

            SpawnPlayer(playerid);  
            OnPlayerSpawnEx(playerid, CASE_LOGIN);
            SetPlayerColor(playerid, RDZPlayer[playerid][USER_COLOR]);
        }

        db_free_result(Result);
        format(buf, sizeof(buf), "{00D900}.: ( {AFAFAF}%s{00D900} ) logged in ( {AFAFAF}Connected{00D900} ) :. ", RDZPlayer[playerid][USER_NAME]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, buf, MESSAGE_CASE_NULL);
    }

    else
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Nope incorrect, give it another whirl maybe?", MESSAGE_CASE_EMPTY);
        Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login", "Type in your password below to log in.", "Login", "Leave" ); 
    }
    return 1;
}

Dialog:DIALOG_REGISTER(playerid, response, listitem, inputtext[]) 
{
    if (!response) return Kick(playerid); 
        
    if (!(strlen(inputtext) <= 20) || !(strlen(inputtext) >= 6)) 
    {
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Okay so, Invalid length on the password. It should be between 3-20 characters for your own safety.", MESSAGE_CASE_SERVER);
        Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register", "Type in a password below to register an account.", "Register", "Leave" );
    } 
    
    else
    bcrypt_hash(inputtext, BCRYPT_COST, "OnPasswordHashed", "d", playerid);
    return 1;
} 

Dialog:DIALOG_GENDER(playerid, response, listitem, inputtext[]) 
{
    if(!response) RDZPlayer[playerid][USER_SEX] = PLAYER_GENDER_FEMALE;
	if(response) RDZPlayer[playerid][USER_SEX] = PLAYER_GENDER_MALE;
	
	SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Congrats your gender was set!", MESSAGE_CASE_EMPTY);
    return 1;
} 

Dialog:DIALOG_LOGIN(playerid, response, listitem, inputtext[]) 
{
    if (!response) return Kick(playerid);  

    bcrypt_check(inputtext, RDZPlayer[playerid][USER_PASSWORD], "OnPasswordChecked", "d", playerid);
    return 1;
} 

Dialog:DIALOG_RULES_TOS(playerid, response, listitem, inputtext[]) 
{
    if(!response) Kick(playerid);
    return 1;
} 

Dialog:DIALOG_CLUCKINBELL(playerid, response, listitem, inputtext[]) 
{
    if (response) 
    {
    	switch(listitem)
		{
			case 0:
			{
				if(GetPlayerMoney(playerid) < 75) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				SetPlayerHealth(playerid, 100.000);
				SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You just ate a chicken!", MESSAGE_CASE_SERVER);
				GivePlayerMoney(playerid, -75);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
		}
    }
    return 1;
}

Dialog:DIALOG_BURGERSHOT(playerid, response, listitem, inputtext[]) 
{
    if (response) 
    {
    	switch(listitem)
		{
			case 0:
			{
				if(GetPlayerMoney(playerid) < 25) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				SetPlayerHealth(playerid, 100.000);
				SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You just ate a burger!", MESSAGE_CASE_SERVER);
				GivePlayerMoney(playerid, -25);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
		}
    }
    return 1;
}

Dialog:DIALOG_PIZZASTACK(playerid, response, listitem, inputtext[]) 
{
    if (response) 
    {
    	switch(listitem)
		{
			case 0:
			{
				if(GetPlayerMoney(playerid) < 125) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				SetPlayerHealth(playerid, 100.000);
				SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You just ate a pizza!", MESSAGE_CASE_SERVER);
				GivePlayerMoney(playerid, -125);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
		}
    }
    return 1;
}

Dialog:DIALOG_SHOPDEALER(playerid, response, listitem, inputtext[]) 
{
    if (response) 
    {
    	switch(listitem)
		{
			case 0:
			{
				if(GetPlayerMoney(playerid) < 350) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerTempGPS(playerid);
				SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Type /gps to find out the usage!", MESSAGE_CASE_SERVER);
				GivePlayerMoney(playerid, -350);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
		}
    }
    return 1;
}

Dialog:DIALOG_WEAPONS(playerid, response, listitem, inputtext[]) 
{
    if (response) 
    {
    	switch(listitem)
		{
			case 0:
			{
				if(GetPlayerMoney(playerid) < 500) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 24, 100);
				GivePlayerMoney(playerid, -500);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 1:
			{
				if(GetPlayerMoney(playerid) < 600) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 25, 100);
				GivePlayerMoney(playerid, -600);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 2:
			{
				if(GetPlayerMoney(playerid) < 500) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 28, 100);
				GivePlayerMoney(playerid, -500);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 3:
			{
				if(GetPlayerMoney(playerid) < 500) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 29, 100);
				GivePlayerMoney(playerid, -500);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 4:
			{
				if(GetPlayerMoney(playerid) < 500) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 32, 100);
				GivePlayerMoney(playerid, -500);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 5:
			{
				if(GetPlayerMoney(playerid) < 25) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 8, 100);
				GivePlayerMoney(playerid, -25);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 6:
			{
				if(GetPlayerMoney(playerid) < 750) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 27, 100);
				GivePlayerMoney(playerid, -750);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 7:
			{
				if(GetPlayerMoney(playerid) < 750) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 30, 100);
				GivePlayerMoney(playerid, -750);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 8:
			{
				if(GetPlayerMoney(playerid) < 750) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 31, 100);
				GivePlayerMoney(playerid, -750);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 9:
			{
				if(GetPlayerMoney(playerid) < 900) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 34, 100);
				GivePlayerMoney(playerid, -900);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 10:
			{
				if(GetPlayerMoney(playerid) < 1000) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerWeapon(playerid, 33, 100);
				GivePlayerMoney(playerid, -1000);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 11:
			{
				if(GetPlayerMoney(playerid) < 1000) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerMoney(playerid, -1000);
				SetPlayerArmour(playerid, 100);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 12:
			{
				if(GetPlayerMoney(playerid) < 550) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerMoney(playerid, -550);
				GivePlayerWeapon(playerid, 46, 100);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 13:
			{
				if(GetPlayerMoney(playerid) < 750) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerMoney(playerid, -750);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				GivePlayerWeapon(playerid, 43, 100);
			}
			case 14:
			{
				if(GetPlayerMoney(playerid) < 250) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
				GivePlayerMoney(playerid, -250);
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				GivePlayerWeapon(playerid, 6, 1);
			}
		}
	}
    return 1;
} 

Dialog:DIALOG_SEXSHOP(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        if(GetPlayerReps(playerid) < 1) 
            return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have enough reps!", MESSAGE_CASE_SERVER);
        
        switch(listitem)
        {
            case 0:
            {
                if(GetPlayerSex(playerid) == PLAYER_GENDER_MALE) 
                    return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're already a male!", MESSAGE_CASE_SERVER);
                    
                SetPlayerSex(playerid, PLAYER_GENDER_MALE);
            }
            case 1:
            {
                if(GetPlayerSex(playerid) == PLAYER_GENDER_FEMALE)
                    return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You're already a female!", MESSAGE_CASE_SERVER);
                SetPlayerSex(playerid, PLAYER_GENDER_FEMALE);
            }
        }
        GivePlayerReps(playerid, -1);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Your gender was changed!", MESSAGE_CASE_SERVER);
    }
    return 1;
} 

Dialog:DIALOG_DUTYSTATE(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        SetDutyStats(playerid, false);
    }
    return 1;
} 

Dialog:DIALOG_GYM(playerid, response, listitem, inputtext[]) 
{
    if(GetPlayerMoney(playerid) < 700)  return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
    switch(listitem)
    {
        case 0:
        {
            SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
            return 1;
        }
        case 1: SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
        case 3: SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
        case 4: SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
        case 5: SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
        case 6: SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);
    }
    GivePlayerMoney(playerid, -700);
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Fighting style set!", MESSAGE_CASE_SERVER);
    return 1;
} 

Dialog:DIALOG_MOTEL(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        if(GetPlayerMoney(playerid) < 500) 
            return    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Not enough cash on hand!", MESSAGE_CASE_SERVER);

        switch(listitem)
        {
            case 0://Buy
            {
                if(s_MotelOwner{playerid})     
                    return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You already own a motel room!", MESSAGE_CASE_SERVER);
                s_MotelOwner{playerid} = true;
                GivePlayerMoney(playerid, -500);
            }
            case 1://Check in
            {
                if(!s_MotelOwner{playerid})     
                    return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't own a motel room!", MESSAGE_CASE_SERVER);
                s_motelVW[playerid] = GetPlayerVirtualWorld(playerid);
                SetPlayerInterior(playerid, MOTELROOM_INTERIOR);
                SetPlayerPos(playerid, 444.646911, 508.239044, 1001.419494);
                SetPlayerVirtualWorld(playerid, playerid+MOTELROOM_VIRTUALWORLD);
                SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Type /motel to get out", MESSAGE_CASE_SERVER);
            }
        }
    }
    return 1;
} 

Dialog:DIALOG_CLOTHES(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_CASINO(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_TATTOO(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_BAR(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_BARBER(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        if(GetPlayerMoney(playerid) < 250) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You don't have sufficient money!", MESSAGE_CASE_EMPTY);
        if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
        {
            RemovePlayerAttachedObject(playerid, 0);
        }
        switch(listitem)
        {
            case 0:
            {
                SetPlayerAttachedObject(playerid, 0, 19517, 2, 0.093999, 0.000000, 0.000000);
            }
            case 1:
            {
                SetPlayerAttachedObject(playerid, 0, 19516, 2, 0.075999, 0.000000, 0.000000);
            }
            case 2:
            {
                SetPlayerAttachedObject(playerid, 0, 19274, 2, 0.084000, -0.032000, 0.003000);
            }
            case 3:
            {
                SetPlayerAttachedObject(playerid, 0, 19077, 2, 0.091000, 0.000000, 0.000000);
            }
            case 4:
            {
                if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
                {
                    RemovePlayerAttachedObject(playerid, 0);
                }
            }
        }
    }
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Hairstyle done!", MESSAGE_CASE_EMPTY);
    GivePlayerMoney(playerid, -250);
    return 1;
} 

Dialog:DIALOG_BANK(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        switch(listitem)
        {
            case 0://Balance
            {
                new string[STRING_SIZE_MEDIUM];
                format(string, sizeof string, "Your bank balance is: %d", GetPlayerBankB(playerid));
                SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_SERVER);
            }
            case 1://Withdraw
            {
                    Dialog_Show(playerid, DIALOG_WITHDRAWINPUT, DIALOG_STYLE_INPUT, "Bank", "Type in the amount to withdraw", "Submit", "Cancel");
            }
            case 2://Deposit
            {
                Dialog_Show(playerid, DIALOG_DEPOSITINPUT, DIALOG_STYLE_INPUT, "Bank", "Type in the amount to deposit", "Submit", "Cancel");
            }
        }
    }
    return 1;
} 

Dialog:DIALOG_DEPOSITINPUT(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        new amount = strval(inputtext);
        if(!IsNumeric(inputtext))
        {
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Input must be in digits!", MESSAGE_CASE_SERVER);
            return Dialog_Show(playerid, DIALOG_DEPOSITINPUT, DIALOG_STYLE_INPUT, "Bank", "Type in the amount to deposit", "Submit", "Cancel");
        }
        if(GetPlayerMoney(playerid) < amount)
        {
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Not enough cash on hand!", MESSAGE_CASE_SERVER);
            return Dialog_Show(playerid, DIALOG_DEPOSITINPUT, DIALOG_STYLE_INPUT, "Bank", "Type in the amount to deposit", "Submit", "Cancel");
        }
        GivePlayerMoney(playerid, -amount);
        IncreasePlayerBankB(playerid, amount);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Amount was submitted!", MESSAGE_CASE_SERVER);
    }
    return 1;
} 

Dialog:DIALOG_WITHDRAWINPUT(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        new amount = strval(inputtext);
        if(!IsNumeric(inputtext))
        {
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Input must be in digits!", MESSAGE_CASE_SERVER);
            return Dialog_Show(playerid, DIALOG_WITHDRAWINPUT, DIALOG_STYLE_INPUT, "Bank", "Type in the amount to withdraw", "Submit", "Cancel");
        }
        if(GetPlayerBankB(playerid) < amount)
        {
            SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Not enough cash in bank!", MESSAGE_CASE_SERVER);
            return Dialog_Show(playerid, DIALOG_WITHDRAWINPUT, DIALOG_STYLE_INPUT, "Bank", "Type in the amount to withdraw", "Submit", "Cancel");
        }
        GivePlayerMoney(playerid, amount);
        IncreasePlayerBankB(playerid, -amount);
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Amount was taken!", MESSAGE_CASE_SERVER);
    }
    return 1;
} 

Dialog:DIALOG_CLUB(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_NIGHTCLUB(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_GASINTERIOR(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_JANITORROOM(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_DINER(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_DONUTS(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_MEATFACTORY(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_CRACKFACTORY(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_CHURCH(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_CARSCHOOL(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_BIKESCHOOL(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_TOILET(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_LSTART(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_HOSPITAL(playerid, response, listitem, inputtext[]) 
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(GetPlayerMoney(playerid) < 100)
                    return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Not enough cash on hand!", MESSAGE_CASE_SERVER);
                SetPlayerHealth(playerid, 100.00);
                SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Healed!", MESSAGE_CASE_SERVER);
            }
        }
    }
    return 1;
} 

Dialog:DIALOG_PRISON(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

Dialog:DIALOG_PLANE(playerid, response, listitem, inputtext[]) 
{

    return 1;
} 

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
    {
        RemovePlayerAttachedObject(playerid, 0);
    }
    if(PLoggedIN{playerid} && !IsPlayerInEvent(playerid))
    {
        if(!cmdKill{playerid}) RDZPlayer[playerid][USER_DEATHS]++;
        if(killerid < MAX_PLAYERS && killerid >= 0 && killerid != INVALID_PLAYER_ID)
        {
            if(IsPlayerConnected(killerid) && PLoggedIN{killerid} && !cmdKill{playerid} && !(IsPlayerCop(killerid) && GetPlayerWantedLevel(playerid) > 0) ) 
            {
                if(!selfDefense{killerid})
                {
                    RDZPlayer[killerid][USER_KILLS]++;
                    SendDeathMessage(killerid, playerid, reason);
                    SendPDReport(killerid, REPORT_TYPE_MURDER, "Murder");
                    new wanted_level = GetPlayerWantedLevel(killerid)+1;
                    if(GetPlayerWantedLevel(killerid) < 6)
                    { 
                        SetPlayerWantedLevel(killerid, wanted_level), SetUserWanted(killerid, wanted_level);
                        SetPlayerColor(killerid, RDZ_COLOR_WANTED);
                    }
                }
                else
                {
                    SendRDZMessage(killerid, RDZ_OFFICIAL_COLOR, "You've killed someone with self-defense!", MESSAGE_CASE_JARVIS);
                    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "You've been killed by self-defense!", MESSAGE_CASE_JARVIS);
                }
            }
        }
    }

    if(IsPlayerInRangeOfPoint(playerid, SAFEZONE_RANGE, -2513.3269, -613.8036, 132.5625)
     && killerid != INVALID_PLAYER_ID && IsPlayerConnected(killerid) && !(GetPlayerWantedLevel(playerid) > 0 && IsPlayerCop(killerid)) && !selfDefense{killerid} && !cmdKill{playerid})
    {
        new SAFEZONE_STRING[STRING_SIZE_LARGE];
        format(SAFEZONE_STRING, sizeof SAFEZONE_STRING, "Janitor[BOT]: Player %s was kicked, Reason : SAFEZONE KILL.", RDZPlayer[killerid][USER_NAME]);
        SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, SAFEZONE_STRING, MESSAGE_CASE_JANITOR);
        Kick(killerid);
    }

    if(!IsPlayerOnDuty(playerid) && !IsPlayerInEvent(playerid)) RDZPlayer[playerid][USER_SKIN] = GetPlayerSkin(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason) 
{ 
    if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
    {
        RemovePlayerAttachedObject(playerid, 0);
    }
    s_MotelOwner{playerid} = false;
    adminCStats{playerid} = false;
    selfDefense{playerid} =  false;
    KillTimer(sdTimer[playerid]);
    
	RDZPlayer[playerid][USER_WANTED] = GetPlayerWantedLevel(playerid);
    new 
        Query[STRING_SIZE_QUERY];
    switch(reason)
    {
        case 0://Timeout/Crash
        {
            format(Query, sizeof(Query), "{FF6347}.: ( {AFAFAF}%s{FF6347} ) left the server ( {AFAFAF}Timeout/crash{FF6347} ) :. ", RDZPlayer[playerid][USER_NAME]);
        }
        case 1://Quit
        {
            format(Query, sizeof(Query), "{FF6347}.: ( {AFAFAF}%s{FF6347} ) left the server ( {AFAFAF}Quit{FF6347} ) :. ", RDZPlayer[playerid][USER_NAME]);
        }
        case 2://Kick/Ban	
        {
            format(Query, sizeof(Query), "{FF6347}.: ( {AFAFAF}%s{FF6347} ) left the server ( {AFAFAF}Kick/ban{FF6347} ) :. ", RDZPlayer[playerid][USER_NAME]);
        }
    }
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, Query, MESSAGE_CASE_NULL);

    if(PLoggedIN{playerid})
    {

        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, r);
        new temp_Version[STRING_SIZE_MEDIUM];
        GetPlayerVersion(playerid, temp_Version, sizeof temp_Version);
        new last_On[STRING_SIZE_MEDIUM], year, month, day;
        getdate(year, month, day);
        FixZeros(month, day, last_On, sizeof last_On, year);

        //userextended::START
        format(Query, sizeof Query, "UPDATE userextended SET coprank = %d WHERE userid = %d", RDZPlayer[playerid][USER_RANK], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userextended SET arrests = %d WHERE userid = %d", RDZPlayer[playerid][USER_ARRESTS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userextended SET job = %d WHERE userid = %d", RDZPlayer[playerid][USER_JOB], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userextended SET crimes = %d WHERE userid = %d", RDZPlayer[playerid][USER_CRIMES], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userextended SET arrested = %d WHERE userid = %d", RDZPlayer[playerid][USER_ARRESTED], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userextended SET fuelcan = %d WHERE userid = %d", RDZPlayer[playerid][USER_FUELCAN], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        //userextended::END

        //userprimary::START
        format(Query, sizeof Query, "UPDATE userprimary SET admin = %d WHERE userid = %d", RDZPlayer[playerid][USER_ADMIN], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userprimary SET viplevel = %d WHERE userid = %d", RDZPlayer[playerid][USER_VIP], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

		format(Query, sizeof Query, "UPDATE userprimary SET mutereason = '%q' WHERE userid = %d", RDZPlayer[playerid][USER_MREASON], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

		format(Query, sizeof Query, "UPDATE userprimary SET sampversion = '%q' WHERE userid = %d", temp_Version, RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

		format(Query, sizeof Query, "UPDATE userprimary SET laston = '%q' WHERE userid = %d", last_On, RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userprimary SET cash = %d WHERE userid = %d", GetPlayerMoney(playerid), RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userprimary SET varip = '%q' WHERE userid = %d", RDZPlayer[playerid][USER_VarIP], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userprimary SET usergps = %d WHERE userid = %d", RDZPlayer[playerid][USER_GPS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userprimary SET kickcount = %d WHERE userid = %d", RDZPlayer[playerid][USER_KICKCOUNT], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userprimary SET injail = %d WHERE userid = %d", RDZPlayer[playerid][USER_JAIL], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
		
        format(Query, sizeof Query, "UPDATE userprimary SET jailtime = %d WHERE userid = %d", RDZPlayer[playerid][USER_JTIME], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
		
        format(Query, sizeof Query, "UPDATE userprimary SET vargpci = '%q' WHERE userid = %d", RDZPlayer[playerid][USER_Vargpci], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        //userprimary::END

        //userdetails::START
        if(GetPlayerWantedLevel(playerid) == 0  && !IsPlayerOnDuty(playerid) && !IsPlayerInEvent(playerid))
            format(Query, sizeof Query, "UPDATE userdetails SET color = %d WHERE userid = %d", GetPlayerColor(playerid), RDZPlayer[playerid][USER_ID]);
        else
            format(Query, sizeof Query, "UPDATE userdetails SET color = %d WHERE userid = %d", RDZPlayer[playerid][USER_COLOR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
    
        format(Query, sizeof Query, "UPDATE userdetails SET playerkills = %d WHERE userid = %d", RDZPlayer[playerid][USER_KILLS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userdetails SET playerdeaths = %d WHERE userid = %d", RDZPlayer[playerid][USER_DEATHS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userdetails SET level = %d WHERE userid = %d", RDZPlayer[playerid][USER_LEVEL], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        
		format(Query, sizeof Query, "UPDATE userdetails SET usersex = %d WHERE userid = %d", RDZPlayer[playerid][USER_SEX], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
		
		format(Query, sizeof Query, "UPDATE userdetails SET userwanted = %d WHERE userid = %d", RDZPlayer[playerid][USER_WANTED], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
		
        format(Query, sizeof Query, "UPDATE userdetails SET experience = %d WHERE userid = %d", RDZPlayer[playerid][USER_EXP], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userdetails SET reputation = %d WHERE userid = %d", RDZPlayer[playerid][USER_RESPECT], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE userdetails SET playinghours = %d WHERE userid = %d", RDZPlayer[playerid][USER_PHOURS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        //userdetails::END
        
        //TELECAR::START
        UpdateTelecarComponents(playerid);
        format(Query, sizeof Query, "UPDATE usertcar SET model = %d WHERE userid = %d", RDZPlayer[playerid][USER_TELECAR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        
        format(Query, sizeof Query, "UPDATE usertcar SET roof = %d WHERE userid = %d", RDZPlayer[playerid][CAR_ROOF], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET sideskirt = %d WHERE userid = %d", RDZPlayer[playerid][CAR_SSKIRT], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET exhausts = %d WHERE userid = %d", RDZPlayer[playerid][CAR_EXHAUSTS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET frontbumber = %d WHERE userid = %d", RDZPlayer[playerid][CAR_FBUMBER], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET rearbumber = %d WHERE userid = %d", RDZPlayer[playerid][CAR_RBUMBER], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET wheels = %d WHERE userid = %d", RDZPlayer[playerid][CAR_WHEELS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET spoiler = %d WHERE userid = %d", RDZPlayer[playerid][CAR_SPOILERS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET paintjob = %d WHERE userid = %d", RDZPlayer[playerid][CAR_PJOB], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET fcolor = %d WHERE userid = %d", RDZPlayer[playerid][CAR_FCOLOR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET scolor = %d WHERE userid = %d", RDZPlayer[playerid][CAR_SCOLOR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        //TELECAR::END

        //usermisc::START
        format(Query, sizeof Query, "UPDATE usermisc SET savermoney = %d WHERE userid = %d", RDZPlayer[playerid][USER_SAVER], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usermisc SET bankamount = %d WHERE userid = %d", RDZPlayer[playerid][USER_BANK], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usermisc SET namebanned = %d WHERE userid = %d", RDZPlayer[playerid][USER_BAN], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
		
		format(Query, sizeof Query, "UPDATE usermisc SET muted = %d WHERE userid = %d", RDZPlayer[playerid][USER_MUTE], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
		
        format(Query, sizeof Query, "UPDATE usermisc SET bankinterest = %f WHERE userid = %d", RDZPlayer[playerid][USER_INTEREST], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usermisc SET driftscore = %d WHERE userid = %d", GetPlayerScore(playerid), RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usermisc SET causeofban = '%q' WHERE userid = %d", RDZPlayer[playerid][USER_COB], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usermisc SET bestrival = %d WHERE userid = %d", RDZPlayer[playerid][USER_BESTRIVAL], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usermisc SET odlost = %d WHERE userid = %d", RDZPlayer[playerid][USER_ODLOST], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        
        format(Query, sizeof Query, "UPDATE usermisc SET odwon = %d WHERE userid = %d", RDZPlayer[playerid][USER_ODWON], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        //usermisc::END

        if(IsSkinSaveable(playerid)) 
        { 
            format(Query, sizeof Query, "UPDATE userdetails SET skinid = %d WHERE userid = %d", RDZPlayer[playerid][USER_SKIN], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
        }
        
        if(IsPositionSaveable(playerid))
        {
            UpdateTelecarPos(playerid);
            format(Query, sizeof Query, "UPDATE usertcar SET floatx = %f WHERE userid = %d", RDZPlayer[playerid][CAR_X], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
            
            format(Query, sizeof Query, "UPDATE usertcar SET floaty = %f WHERE userid = %d", RDZPlayer[playerid][CAR_Y], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
            
            format(Query, sizeof Query, "UPDATE usertcar SET floatz = %f WHERE userid = %d", RDZPlayer[playerid][CAR_Z], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
            
            format(Query, sizeof Query, "UPDATE usertcar SET floatr = %f WHERE userid = %d", RDZPlayer[playerid][CAR_R], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);

            format(Query, sizeof Query, "UPDATE userpositions SET interior = %d WHERE userid = %d", GetPlayerInterior(playerid), RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);

            format(Query, sizeof Query, "UPDATE userpositions SET virtualworld = %d WHERE userid = %d", GetPlayerVirtualWorld(playerid), RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);

            format(Query, sizeof Query, "UPDATE userpositions SET posx = %f WHERE userid = %d", x, RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
            
            format(Query, sizeof Query, "UPDATE userpositions SET posy = %f WHERE userid = %d", y, RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
            
            new PLAYER_STATE = GetPlayerState(playerid);
            if(PLAYER_STATE == PLAYER_STATE_DRIVER || PLAYER_STATE == PLAYER_STATE_PASSENGER) format(Query, sizeof Query, "UPDATE userpositions SET posz = %f WHERE userid = %d", z+3, RDZPlayer[playerid][USER_ID]);
            else format(Query, sizeof Query, "UPDATE userpositions SET posz = %f WHERE userid = %d", z, RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);

            format(Query, sizeof Query, "UPDATE userpositions SET posr = %f WHERE userid = %d", r, RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
			
			format(Query, sizeof Query, "UPDATE userpositions SET vposx = %f WHERE userid = %d", RDZPlayer[playerid][USER_VX], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
            
            format(Query, sizeof Query, "UPDATE userpositions SET vposy = %f WHERE userid = %d", RDZPlayer[playerid][USER_VY], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);

            if(PLAYER_STATE == PLAYER_STATE_DRIVER || PLAYER_STATE == PLAYER_STATE_PASSENGER) format(Query, sizeof Query, "UPDATE userpositions SET vposz = %f WHERE userid = %d", RDZPlayer[playerid][USER_VZ] + 1, RDZPlayer[playerid][USER_ID]);
            else format(Query, sizeof Query, "UPDATE userpositions SET vposz = %f WHERE userid = %d", RDZPlayer[playerid][USER_VZ], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);

            format(Query, sizeof Query, "UPDATE userpositions SET vposr = %f WHERE userid = %d", RDZPlayer[playerid][USER_VR], RDZPlayer[playerid][USER_ID]);
            db_query(RDZ_Database, Query);
        }
        if(reason == 0)
        { 
            if(IsPlayerCop(playerid))
            {
                format(Query, sizeof Query, "UPDATE userpositions SET posx = %f WHERE userid = %d", -1616.2546, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);
                
                format(Query, sizeof Query, "UPDATE userpositions SET posy = %f WHERE userid = %d", 683.4163, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);
                
                format(Query, sizeof Query, "UPDATE userpositions SET posz = %f WHERE userid = %d", 7.1875, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);

                format(Query, sizeof Query, "UPDATE userpositions SET posr = %f WHERE userid = %d", 262.5524, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);
            }
            else
            {
                format(Query, sizeof Query, "UPDATE userpositions SET posx = %f WHERE userid = %d", -2539.0410, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);
                
                format(Query, sizeof Query, "UPDATE userpositions SET posy = %f WHERE userid = %d", -610.9685, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);
                
                format(Query, sizeof Query, "UPDATE userpositions SET posz = %f WHERE userid = %d", 132.7109, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);

                format(Query, sizeof Query, "UPDATE userpositions SET posr = %f WHERE userid = %d", 262.5524, RDZPlayer[playerid][USER_ID]);
                db_query(RDZ_Database, Query);
            }
        }
    }

    new  
        tmp[RDZ_PLAYERS_STATS]; 

    RDZPlayer[playerid] = tmp; 
    PLoggedIN{playerid} = false;
    RDZPlayer[playerid][USER_RESPAWN] = false;
    PTempGPS{playerid} = false;
    RDZPlayer[playerid][USER_CONTICKS] = 0;
    return 1; 
}  

forward playerControllable(playerid);
public playerControllable(playerid) 
    return TogglePlayerControllable(playerid, true);

static IsPositionSaveable(playerid)
{
    if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0 || !PLoggedIN{playerid}) return 0;
    return 1;
}

static INTERIOR_ENTRY( playerid, Float:ix, Float:iy, Float:iz, Float:x, Float:y, Float:z, Float:rot, Interior, World, PreviousWorld )
{
    if( GetPlayerState( playerid ) == PLAYER_STATE_ONFOOT && IsPlayerInRangeOfPoint( playerid, SHOP_SYSTEM_PICKUP_RANGE, ix, iy, iz ) && GetPlayerVirtualWorld( playerid ) == PreviousWorld )
    {
        SetPlayerPos( playerid, x, y, z );
        SetPlayerVirtualWorld( playerid, World );
        SetPlayerFacingAngle( playerid, rot );
        SetPlayerInterior( playerid, Interior );
    }
    return 1;
}

static INTERIOR_ENTRY_SPECIAL( playerid, Float:ix, Float:iy, Float:iz, Float:x, Float:y, Float:z, Float:rot, Interior, World, PreviousWorld )
{
    if( GetPlayerState( playerid ) == PLAYER_STATE_ONFOOT && IsPlayerInRangeOfPoint( playerid, SHOP_SYSTEM_PICKUP_RANGE, ix, iy, iz ) && GetPlayerVirtualWorld( playerid ) == PreviousWorld )
    {
        TogglePlayerControllable(playerid, false);
        SetTimerEx("playerControllable", INTERIOR_WAIT_TIME, false, "i", playerid);
        SetPlayerPos( playerid, x, y, z );
        SetPlayerVirtualWorld( playerid, World );
        SetPlayerFacingAngle( playerid, rot );
        SetPlayerInterior( playerid, Interior );
    }
    return 1;
}


static IsSkinSaveable(playerid)
{
    if(!PLoggedIN{playerid}) return 0;
    return 1;
}

// :: Exterior functions:

//START: boolean functions

stock bool:IsTelecarOwner(playerid)
{
    if(IsPlayerRegistered(Player_TempName[playerid]))
    {
        new 
            DBResult: Result; 
        new
            buf[STRING_SIZE_LARGE];
            
        format(buf, sizeof buf, "SELECT * FROM usertcar WHERE username = '%q' LIMIT 1", Player_TempName[playerid]);
        Result = db_query(RDZ_Database, buf);

        if(db_num_rows(Result)) {
            RDZPlayer[playerid][USER_TELECAR] = db_get_field_assoc_int(Result, "model");
            RDZPlayer[playerid][CAR_EXHAUSTS] = db_get_field_assoc_int(Result, "exhausts");
            RDZPlayer[playerid][CAR_SPOILERS] = db_get_field_assoc_int(Result, "spoiler");
            RDZPlayer[playerid][CAR_WHEELS] = db_get_field_assoc_int(Result, "wheels");
            RDZPlayer[playerid][CAR_FBUMBER] = db_get_field_assoc_int(Result, "frontbumber");
            RDZPlayer[playerid][CAR_RBUMBER] = db_get_field_assoc_int(Result, "rearbumber");
            RDZPlayer[playerid][CAR_SSKIRT] = db_get_field_assoc_int(Result, "sideskirt");
            RDZPlayer[playerid][CAR_ROOF] = db_get_field_assoc_int(Result, "roof");
            RDZPlayer[playerid][CAR_PJOB] = db_get_field_assoc_int(Result, "paintjob");
            RDZPlayer[playerid][CAR_FCOLOR] = db_get_field_assoc_int(Result, "fcolor");
            RDZPlayer[playerid][CAR_SCOLOR] = db_get_field_assoc_int(Result, "scolor");

            RDZPlayer[playerid][CAR_X] =db_get_field_assoc_float(Result, "floatx");
            RDZPlayer[playerid][CAR_Y] =db_get_field_assoc_float(Result, "floaty");
            RDZPlayer[playerid][CAR_Z] =db_get_field_assoc_float(Result, "floatz");
            RDZPlayer[playerid][CAR_R] =db_get_field_assoc_float(Result, "floatr");
        }
        db_free_result(Result);
    }
    return (RDZPlayer[playerid][USER_TELECAR] > 0);
}
    
stock bool:IsPlayerSaver(playerid)
    return (RDZPlayer[playerid][USER_SAVER] > 0);

stock bool:IsGPSOwner(playerid)
    return (RDZPlayer[playerid][USER_GPS] > 0);
    
stock bool:IsTempGPSOwner(playerid)
    return (PTempGPS{playerid});

stock bool:IsPlayerLoggedIn(playerid)
    return (PLoggedIN{playerid});

stock bool:IsPlayerVIP(playerid)
    return (RDZPlayer[playerid][USER_VIP] > 0);

stock bool:IsPlayerADMIN(playerid)
    return (RDZPlayer[playerid][USER_ADMIN] > 0);
	
stock bool:IsPlayerMuted(playerid)
	return (RDZPlayer[playerid][USER_MUTE] > 0);

stock bool:IsPlayerInJail(playerid)
	return (RDZPlayer[playerid][USER_JAIL] > 0);

stock IsPlayerRegistered(playername[])
{
	new 
        Query[STRING_SIZE_QUERY], 
        DBResult: Result; 

    format(Query, sizeof Query, "SELECT password FROM userprimary WHERE username = '%q' LIMIT 1", playername); 
    Result = db_query(RDZ_Database, Query); 
	
    if (db_num_rows(Result)) 
	{
		db_free_result(Result);
		return true;
	}
	db_free_result(Result);
	return false;
}
//END: boolean functions 

//START: Get functions

stock GetTCarCol1(playerid)
    return RDZPlayer[playerid][CAR_FCOLOR];

stock GetTCarCol2(playerid)
    return RDZPlayer[playerid][CAR_SCOLOR];
    
stock SendToAdminLogs(string[])
{
    DCC_SendChannelMessage(Admin_Log, string);
    return 1;
}

stock SendToAdminsReports(string[])
{
    DCC_SendChannelMessage(Admin_Chat, string);
    return 1;
}

stock IsPlayerSelfDefense(playerid)
    return selfDefense{playerid};

stock GetPlayerFuelCan(playerid)
    return RDZPlayer[playerid][USER_FUELCAN];

stock GetPlayerArrested(playerid)
    return RDZPlayer[playerid][USER_ARRESTED];

stock GetPlayerCrimes(playerid)
    return RDZPlayer[playerid][USER_CRIMES];

stock GetSkinFromDB(playerid)
{
    new buf[STRING_SIZE_QUERY];
    new DBResult: Result; 
    format(buf, sizeof buf, "SELECT * FROM userdetails WHERE username = '%q' LIMIT 1", Player_TempName[playerid]);
    Result = db_query(RDZ_Database, buf);

    new DB_SKIN;

    if(db_num_rows(Result))
    {          
        DB_SKIN = db_get_field_assoc_int(Result, "skinid"); 

    }
    else
    {
        db_free_result(Result);
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "DB::ERROR Please contact the owner!", MESSAGE_CASE_JARVIS);
    }

    db_free_result(Result);
    return DB_SKIN;
}

stock GetGPCIFromDB(entry[], gpcihashed[], size)
{
    new buf[STRING_SIZE_QUERY];
    new DBResult: Result; 
    format(buf, sizeof buf, "SELECT * FROM userprimary WHERE username = '%q' LIMIT 1", entry);
    Result = db_query(RDZ_Database, buf);

    if(db_num_rows(Result))
    {          
        db_get_field_assoc(Result, "vargpci", gpcihashed, size);
    }

    db_free_result(Result);
    return 1;
}

stock GetOriginalSkin(playerid)
    return RDZPlayer[playerid][USER_SKIN];
    
stock GetOriginalColor(playerid)
    return RDZPlayer[playerid][USER_COLOR];

stock GetPlayerJob(playerid)
    return RDZPlayer[playerid][USER_JOB];

stock GetPlayerArrests(playerid)
    return RDZPlayer[playerid][USER_ARRESTS];

stock GetPlayerRank(playerid)
    return RDZPlayer[playerid][USER_RANK];

stock Float:GetTcarX(playerid)
    return RDZPlayer[playerid][CAR_X];

stock Float:GetTcarY(playerid)
    return RDZPlayer[playerid][CAR_Y];

stock Float:GetTcarZ(playerid)
    return RDZPlayer[playerid][CAR_Z];

stock Float:GetTcarR(playerid)  
    return RDZPlayer[playerid][CAR_R];

stock GetTcarModel(playerid)
    return RDZPlayer[playerid][USER_TELECAR];

stock GetPlayerJailTime(playerid)
	return RDZPlayer[playerid][USER_JTIME];
	
stock GetPlayerBestRival(playerid)
    return RDZPlayer[playerid][USER_BESTRIVAL];

stock GetPlayerODWon(playerid) 
    return RDZPlayer[playerid][USER_ODWON];

stock GetPlayerODLost(playerid) 
    return RDZPlayer[playerid][USER_ODLOST];

stock GetPlayerDriftScore(playerid)
    return RDZPlayer[playerid][USER_DRIFTSCORE];
    
stock GetPlayerTicks(playerid)
    return RDZPlayer[playerid][USER_CONTICKS];

stock Float:GetPlayerX(playerid)
    return RDZPlayer[playerid][USER_X];

stock Float:GetPlayerY(playerid)
    return RDZPlayer[playerid][USER_Y];

stock Float:GetPlayerZ(playerid)
    return RDZPlayer[playerid][USER_Z];

stock Float:GetPlayerR(playerid)
    return RDZPlayer[playerid][USER_R];

stock GetPlayerWorld(playerid)
    return RDZPlayer[playerid][USER_VIRTUALWORLD];

stock GetPlayerInt(playerid)
    return RDZPlayer[playerid][USER_INTERIOR];

stock GetPlayerLevel(playerid)
    return RDZPlayer[playerid][USER_LEVEL];

stock GetNormalJailTime(WantedLevel)
	return WantedLevel * 2000 * 60 / 10000 - (10*WantedLevel);

stock IsPlayerAlreadyOwner(name[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT username FROM userhouse WHERE username = '%q' LIMIT 1", name); 
    Result = db_query(RDZ_Database, Query); 

    if (db_num_rows(Result))
    { 
        db_free_result(Result);
        return 1;
    }
    db_free_result(Result);
    return 0;
}

//END: Get functions 

//START: Action functions

stock ReservedTeleport(playerid)
{
    new 
        Query[STRING_SIZE_QUERY]; 

    new 
        DBResult: Result; 

    format(Query, sizeof Query, "SELECT * FROM userhouse WHERE username = '%q' LIMIT 1", Player_TempName[playerid]);
    Result = db_query(RDZ_Database, Query);

    if (db_num_rows(Result))
    { 
        SetPlayerPos(playerid, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"));
    }
    return 1;
}

stock AddShop(const name[], Float:ix, Float:iy, Float:iz, Float:ir, Float:x, Float:y, Float:z, Float:r, interior, type, second_world, second_interior, special_map)
{
    new map_icon;
    switch(type)
    {
        case SHOP_TYPE_247:
            map_icon = MAPICON_TWENTYFOUR_SEVEN;
        case SHOP_TYPE_AMMU:
            map_icon = MAPICON_AMMU;
        case SHOP_TYPE_BURGERSHOT:
            map_icon = MAPICON_BURGERSHOT;
        case SHOP_TYPE_CLUCKINBELL:
            map_icon = MAPICON_CLUCKINBELL;
        case SHOP_TYPE_PIZZASTACK:
            map_icon = MAPICON_PIZZASTACK;
        case SHOP_TYPE_BAR, BAR_SECONDARY:
            map_icon = MAPICON_BAR;
        case SHOP_TYPE_BARBER:
            map_icon = MAPICON_BARBER;
        case SHOP_TYPE_CASINO:
            map_icon = MAPICON_CASINO;
        case SHOP_TYPE_GYM:
            map_icon = MAPICON_GYM;
        case SHOP_TYPE_CLOTHES, VICTIM_SHOP:
            map_icon = MAPICON_CLOTHES;
        case SHOP_TYPE_POLICE, LS_POLICE, LV_POLICE, PD_SECONDARY:
            map_icon = MAPICON_POLICE;
        case SHOP_TYPE_TATTOO:
            map_icon = MAPICON_TATTOO;
        case SHOP_TYPE_MOTEL:
            map_icon = MAPICON_MOTEL;
        case SHOP_TYPE_SEXSHOP:
            map_icon = MAPICON_SEX;
        case SHOP_TYPE_BANK:
            map_icon = MAPICON_BANK;
        case SHOP_TYPE_CLUB:
            map_icon = MAPICON_CLUB;
        case SHOP_TYPE_NIGHTCLUB:
            map_icon = MAPICON_NIGHTCLUB;
        case SHOP_TYPE_JANITORROOM:
            map_icon = MAPICON_JANITORROOM;
        case SHOP_TYPE_CHURCH, CHURCH_SECONDARY:
            map_icon = MAPICON_CHURCH;
        case SHOP_TYPE_MEATFACTORY:
            map_icon = MAPICON_MEATFACTORY;
        case SHOP_TYPE_CRACKFACTORY:
            map_icon = MAPICON_CRACKFACTORY;
        case SHOP_TYPE_PLANE:
            map_icon = MAPICON_PLANE;
        case SHOP_TYPE_TOILET:
            map_icon = MAPICON_TOILET;
        case SHOP_TYPE_CARSCHOOL:
            map_icon = MAPICON_CARSCHOOL;
        case SHOP_TYPE_BIKESCHOOL:
            map_icon = MAPICON_BIKESCHOOL;
        case SHOP_TYPE_LSART:
            map_icon = MAPICON_LSART;
        case SHOP_TYPE_HOSPITAL:
            map_icon = MAPICON_HOSPITAL;
        case SHOP_TYPE_RESTAURANT:
            map_icon = MAPICON_DINER;
        case SHOP_TYPE_DONUTS:
            map_icon = MAPICON_DONUTS;
        case SHOP_TYPE_PRISON:
            map_icon = MAPICON_PRISON;
        case SHOP_TYPE_GASINTERIOR:
            map_icon = MAPICON_GASINTERIOR;
    }
    new 
        Query[STRING_SIZE_QUERY]; 

    new virtualworld = 0;
    
    new 
        DBResult: Result; 
        
    Result = db_query(RDZ_Database, "SELECT * FROM `rdzshops` ORDER BY `shopid` DESC LIMIT 1");
    
    new MAX_ROWS_ID = db_get_field_int(Result); 

    if(MAX_ROWS_ID != 0)
    {
        format(Query, sizeof Query, "SELECT * FROM rdzshops WHERE shopid = %d LIMIT 1", MAX_ROWS_ID);
        Result = db_query(RDZ_Database, Query);

        virtualworld = db_get_field_assoc_int(Result, "virtualworld") + 1;
    }

    db_free_result(Result);

    if(virtualworld > MAX_VIRTUAL_WORLDS)
    {
        db_free_result(Result);
        return print("ERROR, MAX VIRTUAL WORLDS BREACHED, REVIEW THE USER DATABASE AND YOUR CODE");
    }

    if(virtualworld != 0) {
        format(Query, sizeof Query, "INSERT INTO rdzshops (shopname, ax, ay, az, ar, bx, by, bz, br, interior, virtualworld, shoptype, mapicon, secondworld, secondinterior) VALUES ('%q', %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d)", name, ix, iy, iz, ir, x, y, z, r, interior, virtualworld, type, map_icon, second_world, second_interior );
        db_query(RDZ_Database, Query);
    }
    else {
        format(Query, sizeof Query, "INSERT INTO rdzshops (shopname, ax, ay, az, ar, bx, by, bz, br, interior, virtualworld, shoptype, mapicon, secondworld, secondinterior) VALUES ('%q', %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d)", name, ix, iy, iz, ir, x, y, z, r, interior, SHOPS_DB_START_VWORLD, type, map_icon, second_world, second_interior);
        db_query(RDZ_Database, Query);
    }
    Result = db_query(RDZ_Database, "SELECT * FROM `rdzshops` ORDER BY `shopid` DESC LIMIT 1");
    
    MAX_ROWS_ID = db_get_field_int(Result); 

    format(Query, sizeof Query, "SELECT * FROM rdzshops WHERE shopid = %d LIMIT 1", MAX_ROWS_ID);
    Result = db_query(RDZ_Database, Query);

    if (db_num_rows(Result))
    { 
        if(db_get_field_assoc_int(Result, "locked") == 1)
        {
            return db_free_result(Result);
        }
        CreateDynamicPickup(SHOP_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), second_world);

        CreateDynamicPickup(SHOP_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_int(Result, "virtualworld"));

        CreateDynamic3DTextLabel(name, HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, second_world);
        CreateDynamic3DTextLabel("L-Alt to enter", HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az")+0.5, HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, second_world);
        if(special_map)
        {
            format(Query, sizeof Query, "UPDATE rdzshops SET locked = %d WHERE shopid = %d", LOCKED_STATS_SPECIAL_MAP, MAX_ROWS_ID);
            db_query(RDZ_Database, Query);
        }

        if(MAX_ROWS_ID < MAX_SHOP_ACTORS)
        {
            switch(type)
            {
                case SHOP_TYPE_247:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( TWENTYFOUR_NPC, 1.9534, -30.7201, 1003.5494, 356.8885 );
                }
                case SHOP_TYPE_AMMU:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( AMMU_NPC, 316.3683, -133.5376, 999.6016, 92.3999 );
                }
                case SHOP_TYPE_BURGERSHOT:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( BURGERSHOT_NPC, 376.5167, -64.9684, 1001.5078, 172.7498 );
                }
                case SHOP_TYPE_CLUCKINBELL:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CLUCKINBELL_NPC, 369.5378, -4.4830, 1001.8589, 175.1585 );
                }
                case SHOP_TYPE_PIZZASTACK:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( PIZZASTACK_NPC, 374.7466, -117.0481, 1001.4922, 179.7228 );
                }
                case SHOP_TYPE_BARBER:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( BARBER_NPC, 408.9911, -53.8690, 1001.8984, 273.7100 );
                }
                case SHOP_TYPE_CASINO:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CASINO_NPC, 1141.1625, -5.7393, 1000.6719, 92.3396 );
                }
                case SHOP_TYPE_GYM:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( GYM_NPC, 763.3224, -49.6312, 1000.5859, 357.4102 );
                }
                case SHOP_TYPE_POLICE:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( POLICE_NPC, 246.5444, 120.3937, 1003.2636, 180.4187 );
                }
                case SHOP_TYPE_TATTOO:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( TATTOO_NPC, -201.0900, -22.8606, 1002.2734, 158.7730 );
                }
                case SHOP_TYPE_SEXSHOP:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( SEX_NPC, -103.9734, -24.2545, 1000.7188, 0.8046 );
                }
                case SHOP_TYPE_CLOTHES:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CLOTHES_NPC, 161.2680, -81.1915, 1001.8047, 179.4253 );
                }
                case SHOP_TYPE_MOTEL:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( MOTEL_NPC, 2217.3137, -1144.5304, 1026.0168, 182.7606 );
                }
                case SHOP_TYPE_BAR:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( BAR_NPC, 497.5840, -77.8954, 998.7651, 355.0053 );
                }
                case SHOP_TYPE_BANK:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( BANK_NPC, 2308.8201, -13.4536, 26.7422, 0.5673 );
                }
                case SHOP_TYPE_CLUB:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CLUB_NPC, 1215.8168, -15.3406, 1000.9219, 1.0905 );
                }
                case VICTIM_SHOP:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CLOTHES_NPC, 204.8528, -8.1264, 1001.2109, 270.7413 );
                }
                case LS_POLICE:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( POLICE_NPC, 251.7096, 68.1342, 1003.6406, 91.4559 );
                }
                case LV_POLICE:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( POLICE_NPC, 293.7616, 182.6091, 1007.1719, 155.8465 );
                }
                case SHOP_TYPE_NIGHTCLUB:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( NIGHTCLUB_NPC, 2320.1040, 1951.5164, 1418.0122, 25.7458 );
                }
                case SHOP_TYPE_GASINTERIOR:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( GASINTERIOR_NPC, -2237.3699, 128.5864, 1035.4141, 359.8675 );
                }
                case SHOP_TYPE_JANITORROOM:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( JANITOR_NPC, 302.0684, 303.5096, 1003.5391, 274.3500 );
                }
                case SHOP_TYPE_RESTAURANT:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( DINER_NPC, 450.5174, -82.1227, 999.5547, 177.0567 );
                }
                case SHOP_TYPE_DONUTS:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( DONUTS_NPC, 380.7887, -187.3940, 1000.6328, 96.2159 );
                }
                case SHOP_TYPE_MEATFACTORY:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( MEATFACTORY_NPC, 960.6079, 2097.5723, 1011.0229, 3.0851 );
                }
                case SHOP_TYPE_CRACKFACTORY:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CRACKFACTORY_NPC, 2581.0588, -1286.1293, 1044.1250, 181.0835 );
                }
                case SHOP_TYPE_CARSCHOOL:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CARSCHOOL_NPC, -2021.7914, -115.7214, 1035.1719, 96.8661 );
                }
                case SHOP_TYPE_TOILET:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( TOILET_NPC, -217.4959, 1410.8348, 27.7734, 99.3589 );
                }
                case SHOP_TYPE_LSART:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( LSART_NPC, 1721.7480, -1653.9374, 20.9688, 356.9266 );
                }
                case SHOP_TYPE_BIKESCHOOL:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( BIKESCHOOL_NPC, 1502.4609, 1307.9852, 1093.2891, 93.1060 );
                }
                case SHOP_TYPE_CHURCH:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CHURCH_NPC, -2022.6702, 1003.4549, 1419.4969, 356.2850 );
                }
                case SHOP_TYPE_HOSPITAL:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( HOSPITAL_NPC, -25.7530, 151.4989, 999.0569, 88.1113 );
                }
                case SHOP_TYPE_PRISON:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( PRISON_NPC, -1969.4702, 307.0227, 1552.1387, 358.7545 );
                }
                case SHOP_TYPE_PLANE:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( PILOT_NPC, 1.5819, 23.2062, 1199.5938, 358.1417 );
                }
                case CHURCH_SECONDARY:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( CHURCH_NPC, 366.8790, 2324.0217, 1890.6047, 273.2509 );
                }
                case BAR_SECONDARY:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( BAR_NPC, -223.3072, 1406.3784, 27.7734, 92.8256 );
                }
                case PD_SECONDARY:
                {
                    SHOP_ACTOR[MAX_ROWS_ID] = CreateActor( POLICE_NPC, -501.3162, 296.3616, 2001.2312, 174.4329 );
                }
            }
            SetActorVirtualWorld( SHOP_ACTOR[MAX_ROWS_ID], db_get_field_assoc_int(Result, "virtualworld" ));
        }
        else print("ARRAY OUT OF BOUNDS DUE TO SHOP ACTORS, REWVIEW CODE");
        CreateDynamicMapIcon(db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), db_get_field_assoc_int(Result, "mapicon"), 0);
        
    }
    db_free_result(Result);
    return 1;
}

stock AddHouse(const name[], Float:ix, Float:iy, Float:iz, Float:ir, Float:x, Float:y, Float:z, Float:r, interior, second_world, second_interior)
{
    new 
        Query[STRING_SIZE_QUERY]; 

    new virtualworld;
    
    new 
        DBResult: Result; 
        
    format(Query, sizeof Query, "SELECT * FROM userprimary WHERE username = '%q' LIMIT 1", name);
    Result = db_query(RDZ_Database, Query);
            
    if (db_num_rows(Result))
    { 
        virtualworld = db_get_field_assoc_int(Result, "userid") + 100; 
    }
    if(virtualworld > MAX_VIRTUAL_WORLDS)
    {
        db_free_result(Result);
        return print("ERROR, MAX VIRTUAL WORLDS BREACHED, REVIEW THE USER DATABASE AND YOUR CODE");
    }
    db_free_result(Result);

    format(Query, sizeof Query, "INSERT INTO userhouse (username, ax, ay, az, ar, bx, by, bz, br, interior, virtualworld, secondworld, secondinterior) VALUES ('%q', %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d)", name, ix, iy, iz, ir, x, y, z, r, interior, virtualworld, second_world, second_interior );
    db_query(RDZ_Database, Query);

    format(Query, sizeof Query, "SELECT * FROM userhouse WHERE username = '%q' LIMIT 1", name);
    Result = db_query(RDZ_Database, Query);

    if (db_num_rows(Result))
    { 
        if(db_get_field_assoc_int(Result, "locked") == 1)
        {
            return db_free_result(Result);
        }
        CreateDynamicPickup(HOUSES_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), second_world);

        CreateDynamicPickup(HOUSES_PICKUP_MODEL, HOUSES_PICKUP_TYPE, db_get_field_assoc_float(Result, "bx"), db_get_field_assoc_float(Result, "by"), db_get_field_assoc_float(Result, "bz"), db_get_field_assoc_int(Result, "virtualworld"));
        CreateDynamicMapIcon(db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), HOUSES_MAPICON, 0);
        CreateDynamic3DTextLabel(name, HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az"), HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, second_world);
        CreateDynamic3DTextLabel("L-Alt to enter", HOUSES_LABEL_COLOR, db_get_field_assoc_float(Result, "ax"), db_get_field_assoc_float(Result, "ay"), db_get_field_assoc_float(Result, "az")+0.5, HOUSES_LABEL_DRAW_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, second_world);
    }
    db_free_result(Result);
    return 1;
}

stock AddNameBan(name[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT username FROM namebans WHERE username = '%q' LIMIT 1", name); 
    Result = db_query(RDZ_Database, Query); 

    if (!db_num_rows(Result))
    { 
        format(Query, sizeof Query, "INSERT INTO namebans (username) VALUES ('%q')", name);
        db_query(RDZ_Database, Query); 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock DelNameBan(name[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT username FROM namebans WHERE username = '%q' LIMIT 1", name); 
    Result = db_query(RDZ_Database, Query); 

    if (db_num_rows(Result))
    { 
        format(Query, sizeof Query, "DELETE FROM namebans WHERE username = '%q'", name);
        db_query(RDZ_Database, Query); 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock IsNameBanned(name[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT username FROM namebans WHERE username = '%q' LIMIT 1", name); 
    Result = db_query(RDZ_Database, Query); 

    if (db_num_rows(Result))
    { 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}


stock AddRDZMember(name[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT username FROM userclan WHERE username = '%q' LIMIT 1", name); 
    Result = db_query(RDZ_Database, Query); 

    if (!db_num_rows(Result))
    { 
        format(Query, sizeof Query, "INSERT INTO userclan (username) VALUES ('%q')", name);
        db_query(RDZ_Database, Query); 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock DelRDZMember(name[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT username FROM userclan WHERE username = '%q' LIMIT 1", name); 
    Result = db_query(RDZ_Database, Query); 

    if (db_num_rows(Result))
    { 
        format(Query, sizeof Query, "DELETE FROM userclan WHERE username = '%q'", name);
        db_query(RDZ_Database, Query); 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock AddGpciBan(gpcihash[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT usergpci FROM userbans WHERE usergpci = '%q' LIMIT 1", gpcihash); 
    Result = db_query(RDZ_Database, Query); 

    if (!db_num_rows(Result))
    { 
        format(Query, sizeof Query, "INSERT INTO userbans (usergpci) VALUES ('%q')", gpcihash);
        db_query(RDZ_Database, Query); 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock DelGpciBan(gpcihash[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT usergpci FROM userbans WHERE usergpci = '%q' LIMIT 1", gpcihash); 
    Result = db_query(RDZ_Database, Query); 

    if (db_num_rows(Result))
    { 
        format(Query, sizeof Query, "DELETE FROM userbans WHERE usergpci = '%q'", gpcihash);
        db_query(RDZ_Database, Query); 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock IsGpciBanned(gpcihash[])
{
    new 
    Query[STRING_SIZE_QUERY], 
    DBResult: Result; 

    format(Query, sizeof Query, "SELECT usergpci FROM userbans WHERE usergpci = '%q' LIMIT 1", gpcihash); 
    Result = db_query(RDZ_Database, Query); 

    if (db_num_rows(Result))
    { 
        db_free_result(Result);
        return 1;
    } 
    db_free_result(Result);
    return 0;
}

stock SetTCVehiclePaintjob(playerid, paintjob)
    return RDZPlayer[playerid][CAR_PJOB] = paintjob;

stock SetPlayerSaver(playerid, integer)
    return RDZPlayer[playerid][USER_SAVER] = integer;
    
stock SetPlayerFuelCan(playerid, amount)
    return RDZPlayer[playerid][USER_FUELCAN] = amount;

stock UpdatePlayerSkin(playerid)
    return RDZPlayer[playerid][USER_SKIN] = GetPlayerSkin(playerid);

stock SetPlayerArrested(playerid, arrested_times)
    return RDZPlayer[playerid][USER_ARRESTED] = arrested_times;

stock SetPlayerCrimes(playerid, crime_times)
    return RDZPlayer[playerid][USER_CRIMES] = crime_times;

stock SetOriginalColor(playerid, color)
    return RDZPlayer[playerid][USER_COLOR] = color;

stock SetPlayerJob(playerid, job_id)
    return RDZPlayer[playerid][USER_JOB] = job_id;

stock SetPlayerRank(playerid, rank_id)
    return RDZPlayer[playerid][USER_RANK] = rank_id;

stock SetPlayerArrests(playerid, arrests)
    return RDZPlayer[playerid][USER_ARRESTS] = arrests;

stock ResetTelecar(playerid)
{
    RDZPlayer[playerid][USER_TELECAR] = 0;
    RDZPlayer[playerid][CAR_ROOF] = 0;
    RDZPlayer[playerid][CAR_SSKIRT] = 0;
    RDZPlayer[playerid][CAR_EXHAUSTS] = 0;
    RDZPlayer[playerid][CAR_FBUMBER] = 0;
    RDZPlayer[playerid][CAR_RBUMBER] = 0;
    RDZPlayer[playerid][CAR_WHEELS] = 0;
    RDZPlayer[playerid][CAR_SPOILERS] = 0;
    RDZPlayer[playerid][CAR_PJOB] = 0;

    UpdateTelecarComponents(playerid, FIRST_TIME);
    return 1;
}

stock UpdateTelecarPos(playerid)
{
    GetVehiclePos(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_X], RDZPlayer[playerid][CAR_Y], RDZPlayer[playerid][CAR_Z]);
    GetVehicleZAngle(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_R]);
    return 1;
}

stock UpdateTelecarComponents(playerid, time = SECOND_TIME, model = 0)
{
    if(time == FIRST_TIME)
    {
        new Query[STRING_SIZE_QUERY];
        RDZPlayer[playerid][USER_TELECAR] = model;

        format(Query, sizeof Query, "UPDATE usertcar SET model = %d WHERE userid = %d", RDZPlayer[playerid][USER_TELECAR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
        
        format(Query, sizeof Query, "UPDATE usertcar SET roof = %d WHERE userid = %d", RDZPlayer[playerid][CAR_ROOF], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET sideskirt = %d WHERE userid = %d", RDZPlayer[playerid][CAR_SSKIRT], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET exhausts = %d WHERE userid = %d", RDZPlayer[playerid][CAR_EXHAUSTS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET frontbumber = %d WHERE userid = %d", RDZPlayer[playerid][CAR_FBUMBER], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET rearbumber = %d WHERE userid = %d", RDZPlayer[playerid][CAR_RBUMBER], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET wheels = %d WHERE userid = %d", RDZPlayer[playerid][CAR_WHEELS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET spoiler = %d WHERE userid = %d", RDZPlayer[playerid][CAR_SPOILERS], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET paintjob = %d WHERE userid = %d", RDZPlayer[playerid][CAR_PJOB], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET fcolor = %d WHERE userid = %d", RDZPlayer[playerid][CAR_FCOLOR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);

        format(Query, sizeof Query, "UPDATE usertcar SET scolor = %d WHERE userid = %d", RDZPlayer[playerid][CAR_SCOLOR], RDZPlayer[playerid][USER_ID]);
        db_query(RDZ_Database, Query);
    }
    RDZPlayer[playerid][CAR_ROOF] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_ROOF);
    RDZPlayer[playerid][CAR_SSKIRT] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_SIDESKIRT);
    RDZPlayer[playerid][CAR_EXHAUSTS] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_EXHAUST);
    RDZPlayer[playerid][CAR_FBUMBER] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_FRONT_BUMPER);
    RDZPlayer[playerid][CAR_RBUMBER] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_REAR_BUMPER);
    RDZPlayer[playerid][CAR_WHEELS] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_WHEELS);
    RDZPlayer[playerid][CAR_SPOILERS] = GetVehicleComponentInSlot(Player_TelecarID[playerid], CARMODTYPE_SPOILER);
    RDZPlayer[playerid][CAR_PJOB] = GetVehiclePaintjob(Player_TelecarID[playerid]);
    GetVehicleColor(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_FCOLOR], RDZPlayer[playerid][CAR_SCOLOR]);
    return 1;
}

stock InstallCopLights(vehicleid)
{
    s_copLights[vehicleid] = CreateObject(18646, 0, 0, 0, 0, 0, 0);
    switch(GetVehicleModel(vehicleid))
    {
        case ELEGY_MODEL:
        {
            AttachObjectToVehicle(s_copLights[vehicleid], vehicleid, -0.500000, -0.200000, 0.80000, 2.00000, 2.00000, 3.00000);
        }
        case NRG_MODEL:
        {
            AttachObjectToVehicle(s_copLights[vehicleid], vehicleid, 0.000000, 0.375000, 0.599999, 0.000000, 0.000000, 0.000000);
        }
    }
    return 1;
}

stock HideCopLights(vehicleid)
{
    switch(GetVehicleModel(vehicleid))
    {
        case ELEGY_MODEL:
        {
            AttachObjectToVehicle(s_copLights[vehicleid], vehicleid, 0.000000, -0.199999, -0.299999, 157.000000, 0.000000, 0.000000 ); 
        }
        case NRG_MODEL:
        {
            AttachObjectToVehicle( s_copLights[vehicleid], vehicleid, 0.000000, 0.000000, 0.399999, 181.000000, 0.000000, 0.000000 );
        }
    }
    return 1;
}

stock ShowCopLights(vehicleid)
{
    switch(GetVehicleModel(vehicleid))
    {
        case ELEGY_MODEL:
        {
            AttachObjectToVehicle(s_copLights[vehicleid], vehicleid, -0.500000, -0.200000, 0.80000, 2.00000, 2.00000, 3.00000);
        }
        case NRG_MODEL:
        {
            AttachObjectToVehicle(s_copLights[vehicleid], vehicleid, 0.000000, 0.375000, 0.599999, 0.000000, 0.000000, 0.000000);
        }
    }
    return 1;
}

stock SetTelecarComponents(playerid)
{
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_ROOF]);
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_SSKIRT]);
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_WHEELS]);
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_FBUMBER]);
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_RBUMBER]);
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_SPOILERS]);
    AddVehicleComponent(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_EXHAUSTS]);

    ChangeVehiclePaintjob(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_PJOB]);
    ChangeVehicleColor(Player_TelecarID[playerid], RDZPlayer[playerid][CAR_FCOLOR], RDZPlayer[playerid][CAR_SCOLOR]);
    return 1;
}

stock SetPlayerJailTime(playerid, jail_time)
	return RDZPlayer[playerid][USER_JTIME] = jail_time;
	
stock GivePlayerTempGPS(playerid)
    return PTempGPS{playerid} = true;
	
stock IncreaseODWon(playerid, amount)
    return RDZPlayer[playerid][USER_ODWON]+= amount;

stock IncreaseODLost(playerid, amount)
    return RDZPlayer[playerid][USER_ODLOST]+= amount;
	
stock BanByName(playerid)
    return RDZPlayer[playerid][USER_BAN] = 1;
	
stock IncreasePlayerLevel(playerid, level)
	return RDZPlayer[playerid][USER_LEVEL] += level;
		
stock GivePlayerReps(playerid, reps_amount)
    return RDZPlayer[playerid][USER_RESPECT] += reps_amount;

stock GivePlayerEXP(playerid, exp_points)
    return RDZPlayer[playerid][USER_EXP]+= exp_points;
	
stock GivePlayerDP(playerid, drift_points)
    return RDZPlayer[playerid][USER_DRIFTSCORE]+= drift_points;

stock UpdatePlayerDriftScore(playerid, score)
    return RDZPlayer[playerid][USER_DRIFTSCORE] = score;

stock SetCauseOfBan(playerid, const cause[])
    return format(RDZPlayer[playerid][USER_COB], MAX_BAN_REASON_LENGTH, "%s", cause);

stock SetMuteCause(playerid, const cause[])
	return format(RDZPlayer[playerid][USER_MREASON], STRING_SIZE_SMALL, "%s", cause);

stock ClearWanted(playerid)
	return RDZPlayer[playerid][USER_WANTED] = 0;

stock SetUserWanted(playerid, level)
    return RDZPlayer[playerid][USER_WANTED] = level;
    
stock SetPlayerJailed(playerid, a_case)
	return RDZPlayer[playerid][USER_JAIL] = a_case;
	
stock GetMuteCause(playerid)
	return format(Mute_StringReason[playerid], STRING_SIZE_SMALL, "%s", RDZPlayer[playerid][USER_MREASON]);
	
stock GetPlayerReps(playerid)
    return RDZPlayer[playerid][USER_RESPECT];
	
stock GetPlayerEXP(playerid)
	return RDZPlayer[playerid][USER_EXP];
	
stock GetPlayingHours(playerid)
    return RDZPlayer[playerid][USER_PHOURS];
    
stock Float:GetPlayerInterest(playerid)
    return RDZPlayer[playerid][USER_INTEREST];
	
stock GetPlayerSex(playerid)
	return RDZPlayer[playerid][USER_SEX];

stock GetMotelVW(playerid)
    return s_motelVW[playerid];

stock GetPlayerVIP(playerid)
    return RDZPlayer[playerid][USER_VIP];

stock GetPlayerADMIN(playerid)
    return RDZPlayer[playerid][USER_ADMIN];

stock GetPlayerID(playerid)
    return RDZPlayer[playerid][USER_ID];

stock GetPlayerDeaths(playerid)
    return RDZPlayer[playerid][USER_DEATHS];

stock GetPlayerKills(playerid)
    return RDZPlayer[playerid][USER_KILLS];
	
stock IncreaseKickCount(playerid)
    return RDZPlayer[playerid][USER_KICKCOUNT]++;

stock SetPlayerBestDP(playerid, drift_points)
    return RDZPlayer[playerid][USER_BESTRIVAL] = drift_points;

stock SetPlayerSpawned(playerid, bool:value)
    return RDZPlayer[playerid][USER_RESPAWN] = value;

stock IncreasePlayerInterest(playerid, Float:Interest_rate) {
    RDZPlayer[playerid][USER_INTEREST] += Interest_rate;
    return 1;
}

stock UpdateVIPSaves(playerid)
{
	switch(GetPlayerState(playerid))
	{
		case PLAYER_STATE_ONFOOT:
		{
			GetPlayerPos(playerid, RDZPlayer[playerid][USER_VX], RDZPlayer[playerid][USER_VY], RDZPlayer[playerid][USER_VZ]);
			GetPlayerFacingAngle(playerid, RDZPlayer[playerid][USER_VR]);
		}
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
		{
            new vehicleid = GetPlayerVehicleID(playerid);
			GetVehiclePos(vehicleid, RDZPlayer[playerid][USER_VX], RDZPlayer[playerid][USER_VY], RDZPlayer[playerid][USER_VZ]);
			GetVehicleZAngle(vehicleid, RDZPlayer[playerid][USER_VR]);
		}
	}
	return 1;
}

stock TeleportVIPSaves(playerid)
{
	switch(GetPlayerState(playerid))
	{
		case PLAYER_STATE_ONFOOT, PLAYER_STATE_PASSENGER:
		{
			SetPlayerPos(playerid, RDZPlayer[playerid][USER_VX], RDZPlayer[playerid][USER_VY], RDZPlayer[playerid][USER_VZ]);
			SetPlayerFacingAngle(playerid, RDZPlayer[playerid][USER_VR]);
		}
		case PLAYER_STATE_DRIVER:
		{
            new vehicleid = GetPlayerVehicleID(playerid);
			SetVehiclePos(vehicleid, RDZPlayer[playerid][USER_VX], RDZPlayer[playerid][USER_VY], RDZPlayer[playerid][USER_VZ]);
			SetVehicleZAngle(vehicleid, RDZPlayer[playerid][USER_VR]);
		}
	}
	return 1;
}

stock BanOfflineName(playerid, targetname[], ban_reason[])
{
	new 
		DBResult: Result; 
	new
		buf[STRING_SIZE_LARGE];
	new 
		rdz_id, 
		userban, 
        user_ip[MAX_IP_LENGTH];
   
    format(buf, sizeof buf, "SELECT * FROM usermisc WHERE username = '%q' LIMIT 1", targetname);
	Result = db_query(RDZ_Database, buf);
    if(db_num_rows(Result))         db_get_field_assoc(Result, "varip", user_ip, MAX_IP_LENGTH);
    db_free_result(Result);

	format(buf, sizeof buf, "SELECT * FROM usermisc WHERE username = '%q' LIMIT 1", targetname);
	Result = db_query(RDZ_Database, buf);

	if (db_num_rows(Result))
	{ 
			
		rdz_id = db_get_field_assoc_int(Result, "userid");
		userban = db_get_field_assoc_int(Result, "namebanned");
	}
	else
	{		
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Database error occured please review this with the owner!", MESSAGE_CASE_ADMIN);
		db_free_result(Result);
		return 0;
	}
	
	if(userban)
	{		
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player is already banned.", MESSAGE_CASE_ADMIN);
		return 0;
	}
    
    new string[STRING_SIZE_MEDIUM];
    format(string, sizeof string, "banip %s", user_ip);
    SendRconCommand(string);
    SendRconCommand("reloadbans");

	new 
		Query[STRING_SIZE_QUERY];

	format(Query, sizeof Query, "UPDATE usermisc SET namebanned = %d WHERE userid = %d", TARGET_BOOL_TRUE, rdz_id);
	db_query(RDZ_Database, Query);
	
	format(Query, sizeof Query, "UPDATE usermisc SET causeofban = '%q' WHERE userid = %d", ban_reason, rdz_id);
	db_query(RDZ_Database, Query);
    db_free_result(Result);
	return 1;
}

stock UnbanOfflineName(playerid, targetname[], ban_reason[])
{
	new 
		DBResult: Result; 
	new
		buf[STRING_SIZE_LARGE];
	new 
		rdz_id, 
		userban, 
        user_ip[MAX_IP_LENGTH];

    format(buf, sizeof buf, "SELECT * FROM userprimary WHERE username = '%q' LIMIT 1", targetname);
	Result = db_query(RDZ_Database, buf);

    if(db_num_rows(Result))         
        db_get_field_assoc(Result, "varip", user_ip, MAX_IP_LENGTH);
    db_free_result(Result);

    
	format(buf, sizeof buf, "SELECT * FROM usermisc WHERE username = '%q' LIMIT 1", targetname);
	Result = db_query(RDZ_Database, buf);

	if (db_num_rows(Result))
	{ 
			
		rdz_id = db_get_field_assoc_int(Result, "userid");
		userban = db_get_field_assoc_int(Result, "namebanned");
	}
	else
	{		
        SendRconCommand("reloadbans");
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Database error occured please review this with the owner!", MESSAGE_CASE_ADMIN);
		db_free_result(Result);
		return 0;
	}
	
	if(!userban)
	{		
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player is already unbanned.", MESSAGE_CASE_ADMIN);
		return 0;
	}
	
    new string[STRING_SIZE_MEDIUM];
    format(string, sizeof string, "unbanip %s", user_ip);
    SendRconCommand(string);
    SendRconCommand("reloadbans");

	new 
		Query[STRING_SIZE_QUERY];

	format(Query, sizeof Query, "UPDATE usermisc SET namebanned = %d WHERE userid = %d", TARGET_BOOL_FALSE, rdz_id);
	db_query(RDZ_Database, Query);
	
	format(Query, sizeof Query, "UPDATE usermisc SET causeofban = '%q' WHERE userid = %d", ban_reason, rdz_id);
	db_query(RDZ_Database, Query);
    db_free_result(Result);
	return 1;
}

stock IncreasePlayingHours(playerid, amount)
    return RDZPlayer[playerid][USER_PHOURS] += amount;

stock GivePlayerGPS(playerid)
    return RDZPlayer[playerid][USER_GPS] = 1;

stock IncreasePlayerBankB(playerid, amount)
    return RDZPlayer[playerid][USER_BANK] += amount;

stock GetPlayerBankB(playerid)
    return RDZPlayer[playerid][USER_BANK];

stock SetPlayerVIP(playerid, vip_level)
    return RDZPlayer[playerid][USER_VIP] = vip_level;

stock SetPlayerSex(playerid, gender)
	return RDZPlayer[playerid][USER_SEX] = gender;
	
stock SetPlayerADMIN(playerid, admin_level)
    return RDZPlayer[playerid][USER_ADMIN] = admin_level;

stock MutePlayer(playerid, index)
	return RDZPlayer[playerid][USER_MUTE] = index;

stock UpdateTelecarColors(playerid, col1, col2)
{
    RDZPlayer[playerid][CAR_FCOLOR] = col1;
    RDZPlayer[playerid][CAR_SCOLOR] = col2;
    return 1;
}
//END: Action functions

stock SendRDZMessage(playerid, color, message[], message_case, secondid = 0)
{
    #pragma unused color
    new 
        RDZ_String[STRING_SIZE_LARGE];

    switch(message_case)
    {
        case MESSAGE_CASE_ADMIN:
        {
			if(playerid != INVALID_PLAYER_ID)
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Admins: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Admins: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_VIP:
        {
			if(playerid != INVALID_PLAYER_ID)
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-VIPs: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-VIPs: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_SERVER:
        {
			if(playerid != INVALID_PLAYER_ID)
            {
				format(RDZ_String, sizeof RDZ_String, ".: Server-Staff: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Staff: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_GAS:
        {
            if(playerid != INVALID_PLAYER_ID)   
            {
                format(RDZ_String, sizeof RDZ_String, ".: Server-Gas station: %s :.", message);
                SendClientMessage(playerid, color, RDZ_String);
            }
            else
            {
                format(RDZ_String, sizeof RDZ_String, ".: Server-Gas station: %s :.", message);
                SendClientMessageToAll(color, RDZ_String);
            }
        }
        case MESSAGE_CASE_DEATH:
        {
			if(playerid != INVALID_PLAYER_ID)   
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Executor: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Executor: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_DRIFT:
        {
			if(playerid != INVALID_PLAYER_ID)   
            {
				format(RDZ_String, sizeof RDZ_String, ".: Server-Drift: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Drift: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_EMPTY:
        {
			if(playerid != INVALID_PLAYER_ID)
			{				
				format(RDZ_String, sizeof RDZ_String, ".: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_JARVIS:
        {
            if(playerid != INVALID_PLAYER_ID)   
            {
                format(RDZ_String, sizeof RDZ_String, ".: Jarvis[BOT]: %s :.", message);
                SendClientMessage(playerid, color, RDZ_String);
            }
            else
            {
                format(RDZ_String, sizeof RDZ_String, ".: Jarvis[BOT]: %s :.", message);
                SendClientMessageToAll(color, RDZ_String);
            }
        }
        case MESSAGE_CASE_JANITOR:
        {
            if(playerid != INVALID_PLAYER_ID)   
            {
                format(RDZ_String, sizeof RDZ_String, ".: Janitor[BOT]: %s :.", message);
                SendClientMessage(playerid, color, RDZ_String);
            }
            else
            {
                format(RDZ_String, sizeof RDZ_String, ".: Janitor[BOT]: %s :.", message);
                SendClientMessageToAll(color, RDZ_String);
            }
        }
		case MESSAGE_CASE_GENDER:
		{
			if(playerid != INVALID_PLAYER_ID)
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Surgeon: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Surgeon: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
		case MESSAGE_CASE_PAYCHECK:
		{
			if(playerid != INVALID_PLAYER_ID)
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Paycheck: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Paycheck: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
		}
        case MESSAGE_CASE_ADMINSCHAT:
        {
            format(RDZ_String, sizeof RDZ_String, ".: Admins chat [%s]: %s :.", Player_TempName[secondid], message);
            SendClientMessage(playerid, color, RDZ_String);
        }
        case MESSAGE_CASE_VIPSCHAT:
        {
            format(RDZ_String, sizeof RDZ_String, ".: VIPs chat [%s]: %s :.", Player_TempName[secondid], message);
            SendClientMessage(playerid, color, RDZ_String);
        }
        case MESSAGE_CASE_COPS:
        {
			if(playerid != INVALID_PLAYER_ID)
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Dispatch: %s :.", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, ".: Server-Dispatch: %s :.", message);
				SendClientMessageToAll(color, RDZ_String);
			}
        }
        case MESSAGE_CASE_NULL:
        {
			if(playerid != INVALID_PLAYER_ID)
			{
				format(RDZ_String, sizeof RDZ_String, "%s", message);
				SendClientMessage(playerid, color, RDZ_String);
			}
			else
			{
				format(RDZ_String, sizeof RDZ_String, "%s", message);
				SendClientMessageToAll(color, RDZ_String);
			}
        }
    }
    return 1;
}
// :: End Exterior functions:

CMD:cstats(playerid)
{
    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE ) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
    adminCStats{playerid} = !adminCStats{playerid};
    new string[STRING_SIZE_MEDIUM];
    format(string, sizeof(string), "Your stats were switched %s!", (adminCStats{playerid}) ? "on" : "off");
    SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JARVIS);
    return 1;
}

CMD:rules(playerid)
{
    new rulesString[564];
    strcat(rulesString, "{FF3333}WARNING 18+ Server, Please Read The Following Message");
    strcat(rulesString, "\n{99FF00}contains language and themes not suitable for young players");
    strcat(rulesString, "\n{99FF00}No cheating, hacking or gameplay mods of any kind or shape");
    strcat(rulesString, "\n{99FF00}Always respect the server administrators no matter what");
    strcat(rulesString, "\n{99FF00}No abusing, flaming, trolling or any racist remarks");
    strcat(rulesString, "\n\n{CCCCCC}This drift server was originally made by RogueDrifter (Andy)");
    strcat(rulesString, "\n\n{CCCCCC}>>> {FFFFFF}Click 'Accept' to continue");
    Dialog_Show(playerid, DIALOG_RULES, DIALOG_STYLE_MSGBOX, "[RDZ] RULES", rulesString, "Accept", "");
    return 1;
}

CMD:getstats(playerid, params[])
{
    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN ) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);
    new pName[MAX_PLAYER_NAME];
    if(sscanf(params, "s[24]", pName))
    {
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "State the player's name afterwards!", MESSAGE_CASE_ADMIN);
    }
    if(!IsPlayerRegistered(pName)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player not registered!", MESSAGE_CASE_ADMIN);

    new 
        DBResult: Result; 
    new
        buf[STRING_SIZE_LARGE];
        
    format(buf, sizeof buf, "SELECT * FROM userprimary WHERE username = '%q' LIMIT 1", pName);
    Result = db_query(RDZ_Database, buf);

    new xUSER_ID, 
    xUSER_ADMIN, 
    xUSER_VIP, 
    xUSER_HANDCASH, 
    xUSER_KICKCOUNT, 
    xUSER_CIP[MAX_IP_LENGTH], 
    xUSER_CGPCI[MAX_GPCI_LENGTH], 
    xUSER_VARIP[MAX_IP_LENGTH], 
    xUSER_VARGPCI[MAX_GPCI_LENGTH], 
    xUSER_VERSION[STRING_SIZE_MEDIUM], 
    xUSER_LASTON[STRING_SIZE_MEDIUM];

    if (db_num_rows(Result))
    { 
        xUSER_ID = db_get_field_assoc_int(Result, "userid"); 
        xUSER_ADMIN = db_get_field_assoc_int(Result, "admin"); 
        xUSER_VIP = db_get_field_assoc_int(Result, "viplevel");
        xUSER_HANDCASH = db_get_field_assoc_int(Result, "cash");
        xUSER_KICKCOUNT = db_get_field_assoc_int(Result, "kickcount");
        db_get_field_assoc(Result, "constip", xUSER_CIP, MAX_IP_LENGTH);
        db_get_field_assoc(Result, "constgpci", xUSER_CGPCI, MAX_GPCI_LENGTH);
        db_get_field_assoc(Result, "varip", xUSER_VARIP, MAX_IP_LENGTH);
        db_get_field_assoc(Result, "vargpci", xUSER_VARGPCI, MAX_GPCI_LENGTH);
        db_get_field_assoc(Result, "laston", xUSER_LASTON, STRING_SIZE_MEDIUM);
        db_get_field_assoc(Result, "sampversion", xUSER_VERSION, STRING_SIZE_MEDIUM);
    }
    else
    {
        db_free_result(Result);
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "DB::ERROR Please contact the owner!", MESSAGE_CASE_JARVIS);
    }

    db_free_result(Result);
    format(buf, sizeof buf, "SELECT * FROM userdetails WHERE username = '%q' LIMIT 1", pName);
    Result = db_query(RDZ_Database, buf);

    new xUSER_SEX, 
    xUSER_LEVEL, 
    xUSER_REPS, 
    xUSER_PH, 
    xUSER_SKIN, 
    xUSER_KILLS, 
    xUSER_DEATHS, 
    xUSER_WANTED;

    if(db_num_rows(Result))
    {
        xUSER_SEX = db_get_field_assoc_int(Result, "usersex"); 
        xUSER_LEVEL = db_get_field_assoc_int(Result, "level"); 
        xUSER_REPS = db_get_field_assoc_int(Result, "reputation"); 
        xUSER_PH = db_get_field_assoc_int(Result, "playinghours");             
        xUSER_SKIN = db_get_field_assoc_int(Result, "skinid"); 
        xUSER_KILLS = db_get_field_assoc_int(Result, "playerkills");
        xUSER_DEATHS = db_get_field_assoc_int(Result, "playerdeaths");
        xUSER_WANTED = db_get_field_assoc_int(Result, "userwanted");

    }
    else
    {
        db_free_result(Result);
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "DB::ERROR Please contact the owner!", MESSAGE_CASE_JARVIS);
    }

    db_free_result(Result);
    format(buf, sizeof buf, "SELECT * FROM usermisc WHERE username = '%q' LIMIT 1", pName);
    Result = db_query(RDZ_Database, buf);
    
    new xUSER_DRIFTSCORE, 
    xUSER_BESTRIVAL, 
    xUSER_ODWON, 
    xUSER_ODLOST, 
    xUSER_BANK, 
    xUSER_BAN, 
    xUSER_MUTE, 
    xUSER_COB[MAX_BAN_REASON_LENGTH];

    if (db_num_rows(Result))
    {
        db_get_field_assoc(Result, "causeofban", xUSER_COB, MAX_BAN_REASON_LENGTH);
        xUSER_DRIFTSCORE = db_get_field_assoc_int(Result, "driftscore");
        xUSER_BESTRIVAL = db_get_field_assoc_int(Result, "bestrival"); 
        xUSER_ODWON = db_get_field_assoc_int(Result, "odwon");
        xUSER_ODLOST = db_get_field_assoc_int(Result, "odlost");
        xUSER_BANK = db_get_field_assoc_int(Result, "bankamount");
        xUSER_BAN =db_get_field_assoc_int(Result, "namebanned");
        xUSER_MUTE =db_get_field_assoc_int(Result, "muted");
    }
    else
    {
        db_free_result(Result);
        return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "DB::ERROR Please contact the owner!", MESSAGE_CASE_JARVIS);
    }

    db_free_result(Result);

    new statsString[STRING_SIZE_QUERY*3];

	new sex[11];
    sex = (xUSER_SEX == PLAYER_GENDER_MALE) ? "Male" : "Female";

	new team[10];
	if(xUSER_ADMIN > 0) team = "Staff";
	else if(xUSER_VIP > 0) team = "Donator";
	else team = "Civillian";

	new mute_stats[10];
    mute_stats = (xUSER_MUTE > 0) ? "Yes" : "No";

    new ban_stats[10];
    ban_stats = (xUSER_BAN > 0) ? "Yes" : "No";

    format(statsString, sizeof statsString, "{00FF00}||| %s |||{CCCCCC}", pName);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);

    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "____________________________", MESSAGE_CASE_EMPTY);
    format(statsString, sizeof statsString, "|Level:[%d] Sex:[%s] Cash:[$%d] Bank[$%d] VIP:[%d] Playing hours:[%d]|", xUSER_LEVEL, sex, xUSER_HANDCASH, xUSER_BANK, xUSER_VIP, xUSER_PH);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
    format(statsString, sizeof statsString, "|Kills:[%d] Deaths:[%d] WantedLevel:[%d] Team:[%s] BestOD:[%d] Reputation:[%d]|", xUSER_KILLS, xUSER_DEATHS, xUSER_WANTED, team, xUSER_BESTRIVAL, xUSER_REPS);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
    format(statsString, sizeof statsString, "|Outdrift wins:[%d] Outdrift losses:[%d] Server ranking:[%d] Mute stats:[%s]|", xUSER_ODWON, xUSER_ODLOST, xUSER_ID, mute_stats);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
    format(statsString, sizeof statsString, "|Skin:[%d] Score:[%d] Kicks:[%d] Admin:[%d] Ban:[%s] Ban reason:[%s]|", xUSER_SKIN, xUSER_DRIFTSCORE, xUSER_KICKCOUNT, xUSER_ADMIN, ban_stats, xUSER_COB);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
    format(statsString, sizeof statsString, "|IP:[%s] Constant-IP:[%s] SA-Version:[%s] Last-On:[%s]|", xUSER_VARIP, xUSER_CIP, xUSER_VERSION, xUSER_LASTON);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);
    format(statsString, sizeof statsString, "Gpci:[%s] Constant-GPCI:[%s]|", xUSER_VARGPCI, xUSER_CGPCI);
    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, statsString, MESSAGE_CASE_EMPTY);

    SendRDZMessage(playerid, RDZ_OOC_CHAT_COLOR, "____________________________", MESSAGE_CASE_EMPTY);
    return 1;
}

DC_CMD:kick(user, args)
{
    new id, giveplayer[MAX_PLAYER_NAME], string[STRING_SIZE_LARGE*2], reason[MAX_BAN_REASON_LENGTH];
    if(sscanf(args, "rs[256]", id, reason)) return SendDC(CHANNEL_ID, "```Usage: /kick [playerid] [reason]```");
    else if(!IsPlayerConnected(id))  return SendDC(CHANNEL_ID, "**Player is not connected.**");

    GetPlayerName(id, giveplayer, MAX_PLAYER_NAME);
    SendDC(CHANNEL_ID, "```Player %s has been kicked, reason: %s```", giveplayer, reason);

    format(string, sizeof(string), "%s has been kicked from the server by an invisible moderator, reason: %s", giveplayer, reason);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
    Kick(id);
    return 1;
}

DC_CMD:kickall(user, args)
{
    new string[STRING_SIZE_LARGE], reason[MAX_BAN_REASON_LENGTH];
    if(sscanf(args, "s[128]", reason)) return SendDC(CHANNEL_ID, "```Usage: /kickall [reason]```");

    SendDC(CHANNEL_ID, "```All players were kicked, reason: %s```", reason);

    format(string, sizeof(string), "All players were kicked by an invisible moderator, reason: %s", reason);
    SendRDZMessage(INVALID_PLAYER_ID, RDZ_OFFICIAL_COLOR, string, MESSAGE_CASE_JANITOR);
    foreach(new i: Player)
    {
        Kick(i);
    }
    return 1;
}

DC_CMD:players(user, args)
{
    new count = 0;
    new name[MAX_PLAYER_NAME];
    SendDC(CHANNEL_ID, "**__Online Players__**");

    foreach(new i: Player)
    {
        GetPlayerName(i, name, sizeof name);
        SendDC(CHANNEL_ID, "```%s(%d)```", name, i);
        count++; 
    }

    if (count == 0) return SendDC(CHANNEL_ID, "There are no players online.");
    return 1;
}

static IsStringInvalid(const string[])
{
    new const invalidstring[] = "123456789.~!@#$%^&*(){}-=;:'`<>?/|";

    for(new x=0; x < strlen(string); x++)
    {
        for(new i=0; i < sizeof invalidstring; i++)
        {
            if(string[x] == invalidstring[i])
            {
                return 1;
            }
        }
    }
    return 0;
}

static ProcessAkaIp(playerid) 
{ 
    new DBResult:Result, string[STRING_SIZE_LARGE]; 
    format(string, sizeof(string), "SELECT * FROM ipmulti WHERE username = '%q' LIMIT 1", Player_TempName[playerid]);
 
    Result = db_query(RDZ_Database, string); 

    switch(db_num_rows(Result))  
    { 

        case 0: format(string, sizeof(string), "INSERT INTO ipmulti (username, userip) VALUES ('%q', '%q')", Player_TempName[playerid], Player_IP[playerid]); 
        default: format(string, sizeof(string), "UPDATE ipmulti SET userip = '%q' WHERE username = '%q'", Player_IP[playerid], Player_TempName[playerid]); 
    } 

    db_free_result(Result); 
    db_query(RDZ_Database, string); 
    return 1; 
} 

static ProcessAkaGpci(playerid) 
{ 
    new DBResult:Result, string[STRING_SIZE_LARGE * 2]; 
    format(string, sizeof(string), "SELECT * FROM gpcimulti WHERE username = '%q' LIMIT 1", Player_TempName[playerid]);
 
    Result = db_query(RDZ_Database, string); 

    switch(db_num_rows(Result))  
    { 

        case 0: format(string, sizeof(string), "INSERT INTO gpcimulti (username, gpciuser) VALUES ('%q', '%q')", Player_TempName[playerid], Player_GPCI[playerid]); 
        default: format(string, sizeof(string), "UPDATE gpcimulti SET gpciuser = '%q' WHERE username = '%q'", Player_GPCI[playerid], Player_TempName[playerid]); 
    } 

    db_free_result(Result); 
    db_query(RDZ_Database, string); 
    return 1; 
} 

static GetAKAGpci(playerid, accs[][], const size=sizeof(accs)) 
{ 
    new DBResult:Result, string[STRING_SIZE_LARGE * 2]; 

    format(string, sizeof(string), "SELECT * FROM gpcimulti WHERE gpciuser = '%q'", Player_GPCI[playerid]); 

    Result = db_query(RDZ_Database, string); 
    if(db_num_rows(Result)) 
    { 
        for(new i, j; i < db_num_rows(Result); i++) 
        { 
            if(j == size) break; 
            db_get_field_assoc(Result, "username", accs[j++], MAX_PLAYER_NAME);
            db_next_row(Result); 
        } 
    } 
    return db_free_result(Result); 
}  

static GetAKAIP(playerid, accs[][], const size=sizeof(accs)) 
{ 
    new DBResult:Result, string[STRING_SIZE_LARGE * 2]; 

    format(string, sizeof(string), "SELECT * FROM ipmulti WHERE userip = '%q'", Player_IP[playerid]); 

    Result = db_query(RDZ_Database, string); 
    if(db_num_rows(Result)) 
    { 
        for(new i, j; i < db_num_rows(Result); i++) 
        { 
            if(j == size) break; 
            db_get_field_assoc(Result, "username", accs[j++], MAX_PLAYER_NAME);
            db_next_row(Result); 
        } 
    } 
    return db_free_result(Result); 
}  

CMD:bustip(playerid, params[])   
{   
    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
    new user;   
    if(sscanf(params, "r", user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state player's id/name!", MESSAGE_CASE_SERVER);
    if(!IsPlayerConnected(user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_SERVER);

    new accounts[NAMES_MULTI_FROMDB][MAX_PLAYER_NAME], string[STRING_SIZE_LARGE * 4];
    GetAKAIP(user, accounts);

    if(accounts[0][0] == '\0') return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player has no outcoming results, he's clean!", MESSAGE_CASE_SERVER);

    for(new i; i < sizeof(accounts); i++)   
    {   
        if(accounts[i][0] == '\0') break;   
        format(string, sizeof(string), "%s{CCCCCC}PlayerName: %s\n", string, accounts[i]);   
    }   
    format(string, sizeof(string), "{00FF00}Full player names under the same IP:\n{CCCCCC}%s", string);   
    Dialog_Show(playerid, DIALOG_AKA, DIALOG_STYLE_MSGBOX, "{CCCCCC}All Player Accounts", string, "Okay", "");   
    return 1;
}  

CMD:bustgpci(playerid, params[])   
{   
    if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_THREE) return RestrictForAdmin(playerid, ADMIN_LEVEL_THREE);
    new user;   
    if(sscanf(params, "r", user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Please state player's id/name!", MESSAGE_CASE_SERVER);
    if(!IsPlayerConnected(user)) return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player isn't connected!", MESSAGE_CASE_SERVER);

    new accounts[NAMES_MULTI_FROMDB][MAX_PLAYER_NAME], string[STRING_SIZE_LARGE * 4];
    GetAKAGpci(user, accounts);

    if(accounts[0][0] == '\0') return SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Player has no outcoming results, he's clean!", MESSAGE_CASE_SERVER);

    for(new i; i < sizeof(accounts); i++)   
    {   
        if(accounts[i][0] == '\0') break;   
        format(string, sizeof(string), "%s{CCCCCC}PlayerName: %s\n", string, accounts[i]);   
    }   
    format(string, sizeof(string), "{00FF00}Full player names under the same GPCI:\n{CCCCCC}%s", string);   
    Dialog_Show(playerid, DIALOG_AKA, DIALOG_STYLE_MSGBOX, "{CCCCCC}All Player Accounts", string, "Okay", "");   
    return 1;  
}  

stock IsPlayerInEvent(playerid)
{
    return (IsPlayerInTDM(playerid) || IsPlayerInMKO(playerid));
}