stock FixZeros(first, second, datestr[], size, third = -1)
{
    new bool: thirdConfirmation;
    if(third != -1)
    {
        if(third <= 9) 
            thirdConfirmation = true;
    }

    new bool:firstConfirmation, bool:secondConfirmation;
    
    if(first <= 9)
        firstConfirmation = true;

    if(second <= 9)
        secondConfirmation = true;

    if(third == -1)
    {
        if(firstConfirmation && secondConfirmation)
            format(datestr, size, "0%d:0%d", first, second);
        else if(!firstConfirmation && !secondConfirmation)
            format(datestr, size, "%d:%d", first, second);
        else if(!firstConfirmation && secondConfirmation)
            format(datestr, size, "%d:0%d", first, second);
        else if(firstConfirmation && !secondConfirmation)
            format(datestr, size, "0%d:%d", first, second);
        else 
            format(datestr, size, "ERROR");
    }
    else
    {
        if(third < 1000)
        {
            if(thirdConfirmation)
            {
                if(firstConfirmation && secondConfirmation)
                    format(datestr, size, "0%d:0%d:0%d", first, second, third);
                else if(!firstConfirmation && !secondConfirmation)
                    format(datestr, size, "%d:%d:0%d", first, second, third);
                else if(!firstConfirmation && secondConfirmation)
                    format(datestr, size, "%d:0%d:0%d", first, second, third);
                else if(firstConfirmation && !secondConfirmation)
                    format(datestr, size, "0%d:%d:0%d", first, second, third);
                else 
                    format(datestr, size, "ERROR");
            }
            else
            {
                if(firstConfirmation && secondConfirmation)
                    format(datestr, size, "0%d:0%d:%d", first, second, third);
                else if(!firstConfirmation && !secondConfirmation)
                    format(datestr, size, "%d:%d:%d", first, second, third);
                else if(!firstConfirmation && secondConfirmation)
                    format(datestr, size, "%d:0%d:%d", first, second, third);
                else if(firstConfirmation && !secondConfirmation)
                    format(datestr, size, "0%d:%d:%d", first, second, third);
                else 
                    format(datestr, size, "ERROR");
            }
        }
        else
        {
            if(thirdConfirmation)
            {
                if(firstConfirmation && secondConfirmation)
                    format(datestr, size, "0%d/0%d/0%d", first, second, third);
                else if(!firstConfirmation && !secondConfirmation)
                    format(datestr, size, "%d/%d/0%d", first, second, third);
                else if(!firstConfirmation && secondConfirmation)
                    format(datestr, size, "%d/0%d/0%d", first, second, third);
                else if(firstConfirmation && !secondConfirmation)
                    format(datestr, size, "0%d/%d/0%d", first, second, third);
                else 
                    format(datestr, size, "ERROR");
            }
            else
            {
                if(firstConfirmation && secondConfirmation)
                    format(datestr, size, "0%d/0%d/%d", first, second, third);
                else if(!firstConfirmation && !secondConfirmation)
                    format(datestr, size, "%d/%d/%d", first, second, third);
                else if(!firstConfirmation && secondConfirmation)
                    format(datestr, size, "%d/0%d/%d", first, second, third);
                else if(firstConfirmation && !secondConfirmation)
                    format(datestr, size, "0%d/%d/%d", first, second, third);
                else 
                    format(datestr, size, "ERROR");
            }
        }
    }
    if(strcmp(datestr, "ERROR", true)) return 0;
    return 1;
}

stock SendRDZMessageToAllExcept(playerid, const message[], message_case)
{
    foreach(new i: Player)
    {
        if(i == playerid) continue;
        SendRDZMessage(i, RDZ_OFFICIAL_COLOR, message, message_case);
    }
    return 1;
}

static const Float:GaragesCoords[][] =
{
	{1643.43, -1521.95, 13.56},
	{1877.30, -2097.85, 13.53},
	{1842.32, -1856.37, 13.38},
	{1797.62, -2146.73, 13.55},
	{1699.06, -2089.99, 13.55},
	{2741.21, -2003.46, 13.55},
	{2644.90, -2038.41, 13.55},
	{2072.40, -1831.38, 13.55},
	{2505.68, -1689.95, 13.56},
	{1041.42, -1026.78, 32.10},
	{1025.09, -1030.52, 32.04},
	{488.41, -1733.88, 11.18},
	{322.60, -1769.86, 4.72},
	{1353.23, -625.68, 109.13},
	{-2715.30, 217.61, 4.32},
	{-2730.48, 74.22, 4.34},
	{-2455.66, -123.73, 26.09},
	{-1935.88, 237.90, 34.31},
	{-1904.53, 276.63, 41.05},
	{-2101.90, -16.07, 35.32},
	{-2026.94, 130.57, 28.84},
	{-2038.18, 178.87, 28.84},
	{-1786.78, 1208.87, 25.13},
	{-2105.22, 897.84, 76.71},
	{-2425.70, 1029.37, 50.39},
	{-2695.94, 820.34, 49.98},
	{1585.90, 1226.73, 10.81},
	{2609.68, 1436.90, 10.82},
	{2386.75, 1042.44, 10.82},
	{2448.44, 697.76, 11.46},
	{2006.11, 2302.69, 10.82},
	{1967.55, 2162.43, 10.82},
	{1407.23, 1902.37, 11.46},
	{1280.85, 2529.82, 10.82},
	{928.43, 2011.86, 11.46},
	{-1420.43, 2591.78, 55.82},
	{-100.00, 1110.53, 19.74},
	{-360.72, 1193.05, 19.74},
	{428.90, 2546.57, 16.21},
	{-388.78, 2228.05, 42.43},
	{404.97, 2478.38, 16.48},
	{-2113.93, -2459.94, 30.63},
	{719.96, -464.34, 16.34},
	{2231.22, 167.27, 27.48},
	{785.95, -494.23, 17.34}
};

#define GARAGE_RANGE 15.0
stock bool:IsPlayerNearGarage(playerid)
{
    for(new y = 0; y < sizeof(GaragesCoords); y++)
    {
        if(IsPlayerInRangeOfPoint(playerid, GARAGE_RANGE, GaragesCoords[y][0], GaragesCoords[y][1], GaragesCoords[y][2]))
            return true;
    }
    return false;
}

static const cursings[] = 
    {"4r5e", "5h1t", "5hit", "a55", "anal", "anus", "ar5e", "arrse", "arse", "ass", "ass-fucker", "asses", "assfucker", "assfukka", "asshole", "assholes", "asswhole", "a_s_s", "b!tch", "b00bs", "b17ch", "b1tch", "ballbag", "balls", "ballsack", "bastard", "beastial", "beastiality", "bellend", "bestial", "bestiality", "bi+ch", "biatch", "bitch", "bitcher", "bitchers", "bitches", "bitchin", "bitching", "bloody", "blow job", "blowjob", "blowjobs", "boiolas", "bollock", "bollok", "boner", "boob", "boobs", "booobs", "boooobs", "booooobs", "booooooobs", "breasts", "buceta", "bugger", "bum", "bunny fucker", "butt", "butthole", "buttmuch", "buttplug", "c0ck", "c0cksucker", "carpet muncher", "cawk", "chink", "cipa", "cl1t", "clit", "clitoris", "clits", "cnut", "cock", "cock-sucker", "cockface", "cockhead", "cockmunch", "cockmuncher", "cocks", "cocksuck", "cocksucked", "cocksucker", "cocksucking", "cocksucks", "cocksuka", "cocksukka", "cok", "cokmuncher", "coksucka", "coon", "cox", "crap", "cum", "cummer", "cumming", "cums", "cumshot", "cunilingus", "cunillingus", "cunnilingus", "cunt", "cuntlick", "cuntlicker", "cuntlicking", "cunts", "cyalis", "cyberfuc", "cyberfuck", "cyberfucked", "cyberfucker", "cyberfuckers", "cyberfucking", "d1ck", "damn", "dick", "dickhead", "dildo", "dildos", "dink", "dinks", "dirsa", "dlck", "dog-fucker", "doggin", "dogging", "donkeyribber", "doosh", "duche", "dyke", "ejaculate", "ejaculated", "ejaculates", "ejaculating", "ejaculatings", "ejaculation", "ejakulate", "f u c k", "f u c k e r", "f4nny", "fag", "fagging", "faggitt", "faggot", "faggs", "fagot", "fagots", "fags", "fanny", "fannyflaps", "fannyfucker", "fanyy", "fatass", "fcuk", "fcuker", "fcuking", "feck", "fecker", "felching", "fellate", "fellatio", "fingerfuck", "fingerfucked", "fingerfucker", "fingerfuckers", "fingerfucking", "fingerfucks", "fistfuck", "fistfucked", "fistfucker", "fistfuckers", "fistfucking", "fistfuckings", "fistfucks", "flange", "fook", "fooker", "fuck", "fucka", "fucked", "fucker", "fuckers", "fuckhead", "fuckheads", "fuckin", "fucking", "fuckings", "fuckingshitmotherfucker", "fuckme", "fucks", "fuckwhit", "fuckwit", "fudge packer", "fudgepacker", "fuk", "fuker", "fukker", "fukkin", "fuks", "fukwhit", "fukwit", "fux", "fux0r", "f_u_c_k", "gangbang", "gangbanged", "gangbangs", "gaylord", "gaysex", "goatse", "God", "god-dam", "god-damned", "goddamn", "goddamned", "hardcoresex", "hell", "heshe", "hoar", "hoare", "hoer", "homo", "hore", "horniest", "horny", "hotsex", "jack-off", "jackoff", "jap", "jerk-off", "jism", "jiz", "jizm", "jizz", "kawk", "knob", "knobead", "knobed", "knobend", "knobhead", "knobjocky", "knobjokey", "kock", "kondum", "kondums", "kum", "kummer", "kumming", "kums", "kunilingus", "l3i+ch", "l3itch", "labia", "lust", "lusting", "m0f0", "m0fo", "m45terbate", "ma5terb8", "ma5terbate", "masochist", "master-bate", "masterb8", "masterbat*", "masterbat3", "masterbate", "masterbation", "masterbations", "masturbate", "mo-fo", "mof0", "mofo", "mothafuck", "mothafucka", "mothafuckas", "mothafuckaz", "mothafucked", "mothafucker", "mothafuckers", "mothafuckin", "mothafucking", "mothafuckings", "mothafucks", "mother fucker", "motherfuck", "motherfucked", "motherfucker", "motherfuckers", "motherfuckin", "motherfucking", "motherfuckings", "motherfuckka", "motherfucks", "muff", "mutha", "muthafecker", "muthafuckker", "muther", "mutherfucker", "n1gga", "n1gger", "nazi", "nigg3r", "nigg4h", "nigga", "niggah", "niggas", "niggaz", "nigger", "niggers", "nob", "nob jokey", "nobhead", "nobjocky", "nobjokey", "numbnuts", "nutsack", "orgasim", "orgasims"};

static const cursing[] = 
    {"orgasm", "orgasms", "p0rn", "pawn", "pecker", "penis", "penisfucker", "phonesex", "phuck", "phuk", "phuked", "phuking", "phukked", "phukking", "phuks", "phuq", "pigfucker", "pimpis", "piss", "pissed", "pisser", "pissers", "pisses", "pissflaps", "pissin", "pissing", "pissoff", "poop", "porn", "porno", "pornography", "pornos", "prick", "pricks", "pron", "pube", "pusse", "pussi", "pussies", "pussy", "pussys", "rectum", "retard", "rimjaw", "rimming", "s hit", "s.o.b.", "sadist", "schlong", "screwing", "scroat", "scrote", "scrotum", "semen", "sex", "sh!+", "sh!t", "sh1t", "shag", "shagger", "shaggin", "shagging", "shemale", "shi+", "shit", "shitdick", "shite", "shited", "shitey", "shitfuck", "shitfull", "shithead", "shiting", "shitings", "shits", "shitted", "shitter", "shitters", "shitting", "shittings", "shitty", "skank", "slut", "sluts", "smegma", "smut", "snatch", "son-of-a-bitch", "spac", "spunk", "s_h_i_t", "t1tt1e5", "t1tties", "teets", "teez", "testical", "testicle", "tit", "titfuck", "tits", "titt", "tittie5", "tittiefucker", "titties", "tittyfuck", "tittywank", "titwank", "tosser", "turd", "tw4t", "twat", "twathead", "twatty", "twunt", "twunter", "v14gra", "v1gra", "vagina", "viagra", "vulva", "w00se", "wang", "wank", "wanker", "wanky", "whoar", "whore", "willies", "willy", "xrated", "xxx", "puta", "cyka", "blyad", "blyat"};

stock bool:IsContainingACurse(const string[])
{
    for(new o = 0; o < sizeof(cursing); o++)
    {
        if(strfind(string, cursings[o], true))
            return true;
        if(strfind(string, cursing[o], true))
            return true;
    }
    return false;
}

// **DISCORD FUNCTIONS
stock ReplaceDiscordMentions(const message[]) 
{     
    new DCC_User:mention_id,  
        mention_name[33], 
        user[19], 
        string[166],  
        pos; 

    format(string, sizeof(string), message); 

    for(new i; i < sizeof(string); i++) 
    {     
        if(string[i] == '<' && string[i + 1] == '@') 
        {     
            pos = i; 

            if(string[i + 2] == '!') 
                i++; 

            strmid(user, string, i + 2, i + 21); 

            mention_id = DCC_FindUserById(user); 

            if(!mention_id) 
                continue; 

            DCC_GetGuildMemberNickname(dc_Guild, mention_id, mention_name); 

            if(isnull(mention_name)) 
                DCC_GetUserName(mention_id, mention_name); 

            format(mention_name, sizeof(mention_name), "@%s", mention_name); 

            strdel(string, pos, pos + 21 + (i - pos)); 
            strins(string, mention_name, pos); 
        } 
    } 

    return string; 
}  
//END

stock Float:GeoDistance(Float:lat1, Float:lon1, Float:lat2, Float:lon2) //Get distance using haversine formula - Thanks to Marmeladova
{ 
    const Float:R = 6371.0087714; // Earth radius 
    new Float:sin1 = floatsin((lat1 - lat2) /2 ); 
    new Float:sin2 = floatsin((lon1 - lon2) /2 ); 
    return 2 * R * asin(floatsqroot(sin1 * sin1 + sin2 * sin2 * floatcos(lat1) * floatcos(lat2))) * (3.14 / 180); 
}  

stock bool:IsPlayerUnderWater(playerid) 
{ 
    new PPAnim = GetPlayerAnimationIndex(playerid); 
    return (PPAnim == 1540 || PPAnim == 1544); 
}  

stock RemovePlayerWeapon(playerid, weaponid) // Thanks to rogercosta (PS. Won't work for melee weps)
{
	if(GetPlayerWeapon(playerid) == weaponid) 
    {
		GivePlayerWeapon(playerid, weaponid, -GetPlayerAmmo(playerid));
	}
	else 
    {
		new slot, weapon, ammo, currentWeapon = GetPlayerWeapon(playerid);
		for(new i = 0; i < 12; i++) {
			GetPlayerWeaponData(playerid, i, weapon, ammo);
			if(weapon == weaponid && ammo > 0) {
				GivePlayerWeapon(playerid, weaponid, -ammo);
				SetPlayerArmedWeapon(playerid, currentWeapon);
				break;
			}
		}
	}
    return 1;
}

static const female_skins[] = 
{ 
    9, 10, 11, 12, 13, 31, 39, 40, 41, 53, 54, 55, 56, 63, 
    64, 65, 69, 75, 76, 77, 85, 87, 88, 89, 90, 91, 92, 93, 
    129, 130, 131, 138, 139, 140, 141, 145, 148, 150, 151, 151, 
    157, 169, 172, 178, 190, 191, 192, 193, 194, 195, 196, 197, 
    198, 199, 201, 205, 207, 211, 214, 215, 216, 218, 219, 224, 
    225, 226, 231, 232, 233, 237, 238, 243, 244, 245, 246, 251, 
    256, 257, 263, 298 
}; 

stock bool:IsMale(playerid) 
{ 
    for(new x = 0; x < sizeof(female_skins); x++) 
    { 
        if(GetPlayerSkin(playerid) == female_skins[x]) return 0; 
    } 
    return 1; 
}

//RakNet Functions:
stock ExplosionForPlayer(playerid, Float:x, Float:y, Float:z, explosion_type, radius_of_explosion) 
{ 
    new BitStream:bs_of_explosion = BS_New(); 
    BS_WriteValue(bs_of_explosion, 
        PR_FLOAT, x, 
            PR_FLOAT, y, 
                PR_FLOAT, z, 
                    PR_UINT16, explosion_type, 
                        PR_FLOAT, radius_of_explosion 
    ); 
    BS_RPC(bs_of_explosion, playerid, 79, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED); 
    BS_Delete(bs_of_explosion); 
}  
//END

static Float:Hospitalcoor[][4] = 
{ 
    {2027.4375,-1421.0703,16.9922,137.2809}, // Los Santos Hospital 
    {1177.9089,-1323.9611,14.0939,269.8222},  // Los Santos Hospital #2 
    {1579.6106,1769.0625,10.8203,90.7178},  // Las Venturas Hospital 
    {-321.8259,1056.7279,19.7422,316.0064}, // Fort Carson Hospital 
    {-1514.8807,2527.8003,55.7315,358.6234},  // El Quebrados Hospital 
    {-2662.0439,630.5056,14.4531,177.8114}, // San Fierro Hospital 
    {-2199.2495,-2311.0444,30.6250,321.2772}, // Angel Pine Hospital 
    {1244.1959,332.2817,19.5547,338.3063} // Montgomery Hospital 
}; 

#define Hospital_RANGE 15.0
stock bool:IsPlayerNearHospital(playerid)
{
    for(new y = 0; y < sizeof(GaragesCoords); y++)
    {
        if(IsPlayerInRangeOfPoint(playerid, Hospital_RANGE, Hospitalcoor[y][0], Hospitalcoor[y][1], Hospitalcoor[y][2]))
            return true;
    }
    return false;
}

#define MAX_NUM 10
#define MY_SERVER_IP "255.255.255.255:7777"
stock ContainsIP(const string[])
{
    new num[MAX_NUM][128];
    new numpos[MAX_NUM];
    new dotcount,i;
    if(strfind(string,MY_SERVER_IP)!=-1)return 0;
    for(new npos=0;npos<=MAX_NUM;npos++)
    {
        new c;
        for(c=0;i<strlen(string);i++)
        {

            new ch = string[i];

            if((string[i] == '.' || string[i] == ':') && ((i>0 && '0' <= string[i-1] <= '9') || (i>1 && '0' <= string[i-2] <= '9') ))
            {
                dotcount++;
                i++;
                break;
            }
            if ((npos==0 || i - numpos[npos - 1] < strlen(num[npos-1])+4) && '0' <= ch <= '9' || (c == 0 && ch == '-'))
            {
                num[npos][c] = string[i];
                numpos[npos] = i;
                c++;
            }


        }

    }
    new found=0;
    for(new npos=0;npos<MAX_NUM;npos++)
    {
        if( strlen(num[npos]) > 0 && 0 < strval(num[npos]) <= 225)
        {
            found++;
        }
    }
    if(found >= 3 && dotcount >= 3)return 1;
    return 0;
}

static Float: GasPumpCoords[78][3] = {
	{-85.2422, -1165.0312, 2.6328},
	{-90.1406, -1176.6250, 2.6328},
	{-92.1016, -1161.7891, 2.9609},
	{-97.0703, -1173.7500, 3.0312},
	{1941.6562, -1767.2891, 14.1406},
	{1941.6562, -1771.3438, 14.1406},
	{1941.6562, -1774.3125, 14.1406},
	{1941.6562, -1778.4531, 14.1406},
	{-1327.0312, 2685.5938, 49.4531},
	{-1327.7969, 2680.1250, 49.4531},
	{-1328.5859, 2674.7109, 49.4531},
	{-1329.2031, 2669.2812, 49.4531},
	{-1464.9375, 1860.5625, 31.8203},
	{-1465.4766, 1868.2734, 31.8203},
	{-1477.6562, 1859.7344, 31.8203},
	{-1477.8516, 1867.3125, 31.8203},
	{-1600.6719, -2707.8047, 47.9297},
	{-1603.9922, -2712.2031, 47.9297},
	{-1607.3047, -2716.6016, 47.9297},
	{-1610.6172, -2721.0000, 47.9297},
	{-1665.5234, 416.9141, 6.3828},
	{-1669.9062, 412.5312, 6.3828},
	{-1672.1328, 423.5000, 6.3828},
	{-1675.2188, 407.1953, 6.3828},
	{-1676.5156, 419.1172, 6.3828},
	{-1679.3594, 403.0547, 6.3828},
	{-1681.8281, 413.7812, 6.3828},
	{-1685.9688, 409.6406, 6.3828},
	{-2241.7188, -2562.2891, 31.0625},
	{-2246.7031, -2559.7109, 31.0625},
	{-2410.8047, 970.8516, 44.4844},
	{-2410.8047, 976.1875, 44.4844},
	{-2410.8047, 981.5234, 44.4844},
	{1378.9609, 461.0391, 19.3281},
	{1380.6328, 460.2734, 19.3281},
	{1383.3984, 459.0703, 19.3281},
	{1385.0781, 458.2969, 19.3281},
	{603.4844, 1707.2344, 6.1797},
	{606.8984, 1702.2188, 6.1797},
	{610.2500, 1697.2656, 6.1797},
	{613.7188, 1692.2656, 6.1797},
	{617.1250, 1687.4531, 6.1797},
	{620.5312, 1682.4609, 6.1797},
	{624.0469, 1677.6016, 6.1797},
	{655.6641, -558.9297, 15.3594},
	{655.6641, -560.5469, 15.3594},
	{655.6641, -569.6016, 15.3594},
	{655.6641, -571.2109, 15.3594},
	{1590.3516, 2193.7109, 11.3125},
	{1590.3516, 2204.5000, 11.3125},
	{1596.1328, 2193.7109, 11.3125},
	{1596.1328, 2204.5000, 11.3125},
	{1602.0000, 2193.7109, 11.3125},
	{1602.0000, 2204.5000, 11.3125},
	{2109.0469, 914.7188, 11.2578},
	{2109.0469, 925.5078, 11.2578},
	{2114.9062, 914.7188, 11.2578},
	{2114.9062, 925.5078, 11.2578},
	{2120.8203, 914.7188, 11.2578},
	{2120.8203, 925.5078, 11.2578},
	{2141.6719, 2742.5234, 11.2734},
	{2141.6719, 2753.3203, 11.2734},
	{2147.5312, 2742.5234, 11.2734},
	{2147.5312, 2753.3203, 11.2734},
	{2153.3125, 2742.5234, 11.2734},
	{2153.3125, 2753.3203, 11.2734},
	{2196.8984, 2470.2500, 11.3125},
	{2196.8984, 2474.6875, 11.3125},
	{2196.8984, 2480.3281, 11.3125},
	{2207.6953, 2470.2500, 11.3125},
	{2207.6953, 2474.6875, 11.3125},
	{2207.6953, 2480.3281, 11.3125},
	{2634.6406, 1100.9453, 11.2500},
	{2634.6406, 1111.7500, 11.2500},
	{2639.8750, 1100.9609, 11.2500},
	{2639.8750, 1111.7500, 11.2500},
	{2645.2500, 1100.9609, 11.2500},
	{2645.2500, 1111.7500, 11.2500}
};

#define GAS_RANGE 5.0
stock bool:IsPlayerNearGasPump(playerid)
{
    for(new y = 0; y < sizeof(GasPumpCoords); y++)
    {
        if(IsPlayerInRangeOfPoint(playerid, GAS_RANGE, GasPumpCoords[y][0], GasPumpCoords[y][1], GasPumpCoords[y][2]))
            return true;
    }
    return false;
}

static Float: HydrantCoords[46][3] = {
	{-2089.2109, 1258.6953, 13.8047},
	{-2210.7500, 1258.6953, 34.7109},
	{-2282.8750, 952.8516, 65.8672},
	{-2283.6797, 573.9766, 34.7266},
	{-2283.6797, 662.5781, 48.4531},
	{-2283.6797, 802.8984, 48.9766},
	{-2361.6172, 1323.4922, 14.4453},
	{-2370.5781, 573.9766, 24.4766},
	{-2370.5781, 662.5781, 34.7422},
	{-2370.5781, 798.8359, 35.1016},
	{-2370.5781, 952.8125, 45.0781},
	{-2414.8750, 573.9609, 24.4844},
	{-2414.8750, 699.0781, 34.7266},
	{-2414.8750, 813.8047, 34.7734},
	{-2415.5469, 902.4844, 45.1328},
	{-2461.6484, 1323.4922, 12.2969},
	{-2477.6875, 1215.1406, 34.7734},
	{-2501.7656, 573.8281, 14.1641},
	{-2501.7656, 699.0781, 31.1641},
	{-2501.7656, 813.7188, 44.0469},
	{-2501.7656, 913.8984, 64.3750},
	{-2569.3750, 713.7734, 27.4688},
	{-2583.0156, 813.6953, 49.5625},
	{-2593.1172, 573.8203, 14.1484},
	{-2599.3203, 1343.5547, 6.8047},
	{-2634.5625, 899.6016, 70.6406},
	{-2634.5625, 998.9219, 72.2031},
	{-2656.2734, 713.5781, 27.5156},
	{-2669.9062, 817.6953, 49.5234},
	{-2680.0156, 573.8594, 14.1562},
	{-2721.4609, 892.9531, 71.6953},
	{-2721.4609, 998.7422, 54.3203},
	{1266.0859, -906.7031, 42.3984},
	{1289.1406, -938.1250, 40.7734},
	{2495.2656, -1653.6719, 12.9141},
	{2505.6641, -1657.9375, 12.9219},
	{317.8359, -1609.5781, 32.9141},
	{374.6406, -1576.8516, 30.8906},
	{438.8359, -1608.6094, 25.2734},
	{456.3438, -1301.5781, 14.6797},
	{457.2500, -1300.8906, 14.6797},
	{544.3984, -1440.2109, 15.2891},
	{546.0156, -1494.7109, 13.8984},
	{546.5625, -1547.2188, 15.1016},
	{555.1562, -1251.9297, 16.6406},
	{592.8984, -1212.2812, 17.6484}
};

#define HYDRANT_RANGE 5.0
stock bool:IsPlayerNearFireHydrant(playerid)
{
    for(new y = 0; y < sizeof(HydrantCoords); y++)
    {
        if(IsPlayerInRangeOfPoint(playerid, HYDRANT_RANGE, HydrantCoords[y][0], HydrantCoords[y][1], HydrantCoords[y][2]))
            return true;
    }
    return false;
}

stock IsNumeric(const string[])
{
    for (new i = 0, j = strlen(string); i < j; i++)
    {
        if (string[i] > '9' || string[i] < '0') return 0;
    }
    return 1;
}