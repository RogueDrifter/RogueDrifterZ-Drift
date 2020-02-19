#if defined RDZ_INTERIOR_Included_
   #endinput
#endif

#define RDZ_INTERIOR_Included_

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#define DEFAULT_ROTATION 0.0

static playerShop[MAX_PLAYERS];


hook OnPlayerDisconnect(playerid, reason)
{
    playerShop[playerid] = 0;
    return 1;
}
CMD:createshop(playerid, params[])
{
	if(GetPlayerADMIN(playerid) < ADMIN_LEVEL_SEVEN) return RestrictForAdmin(playerid, ADMIN_LEVEL_SEVEN);

    Dialog_Show(playerid, DIALOG_SPECIAL_MAP, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "Is this a specially created map?", "Yes", "No");

    return 1;
}

Dialog:DIALOG_SPECIAL_MAP(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        playerShop[playerid] = 1;
    }
    else 
    {
        playerShop[playerid] = 0;
    }
    Dialog_Show(playerid, DIALOG_ENTRY_SHOP, DIALOG_STYLE_LIST, "RogueDrifterZ shops", "24/7\nAmmunation\nCluckin bell\nPizza stack\nBurger shot\nGym\nSex shop\nZip clothing\nMotel\nSF- Police\nBar\nBarber shop\nCasino\nTattoo shop\nBank\nStrip club\nVictim clothing\nLS- Police\nLV- Police\nGas-station interior\nJanitor room\nPrison interior\nToilet place\nSecond bar\nNight club\nMeat factory\nCrack factory\nPlane interior(SHAMAL)\nCar school\nBike school\nDiner interior\nDonuts shop\nChurch interior\nSecond church\nSecondary PD\nHospital interior\nLS Atrium", "Choose", "Cancel");
    return 1;
}

Dialog:DIALOG_ENTRY_SHOP(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, DIALOG_SHOP_ONE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked 24/7, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 1:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWO, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked ammunation, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 2:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THREE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked cluckin bell, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 3:
            {
                Dialog_Show(playerid, DIALOG_SHOP_FOUR, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked pizza stack, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 4:
            {
                Dialog_Show(playerid, DIALOG_SHOP_FIVE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked burger shot, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 5:
            {
                Dialog_Show(playerid, DIALOG_SHOP_SIX, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked gym, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 6:
            {
                Dialog_Show(playerid, DIALOG_SHOP_SEVEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked sex shop, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 7:
            {
                Dialog_Show(playerid, DIALOG_SHOP_EIGHT, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked zip clothing shop, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 8:
            {
                Dialog_Show(playerid, DIALOG_SHOP_NINE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked motel, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 9:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked SF PD, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 10:
            {
                Dialog_Show(playerid, DIALOG_SHOP_ELEVEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked bar, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 11:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWELVE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked barber shop, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 12:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked casino, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 13:
            {
                Dialog_Show(playerid, DIALOG_SHOP_FOURTEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked tattoo shop, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 14:
            {
                Dialog_Show(playerid, DIALOG_SHOP_FIFTEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked bank, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 15:
            {
                Dialog_Show(playerid, DIALOG_SHOP_SIXTEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked strip club, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 16:
            {
                Dialog_Show(playerid, DIALOG_SHOP_SEVENTEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked victim clothing, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 17:
            {
                Dialog_Show(playerid, DIALOG_SHOP_EIGHTEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked LS PD, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 18:
            {
                Dialog_Show(playerid, DIALOG_SHOP_NINETEEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked LV PD, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 19:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTY, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Gas-station interior, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 20:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYONE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Janitor room, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 21:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYTWO, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Prison interior, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 22:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYTHREE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Toilet place, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 23:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYFOUR, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Second bar, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 24:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYFIVE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Night club, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 25:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYSIX, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Meat factory, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 26:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYSEVEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Crack factory, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 27:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYEIGHT, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Plane interior(SHAMAL), please make sure you got the right one!", "Accept", "Cancel");
            }
            case 28:
            {
                Dialog_Show(playerid, DIALOG_SHOP_TWENTYNINE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Car school, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 29:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTY, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Bike school, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 30:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYONE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Diner interior, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 31:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYTWO, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Donuts shop, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 32:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYTHREE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Church interior, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 33:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYFOUR, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Second church, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 34:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYFIVE, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Secondary PD, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 35:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYSIX, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked Hospital interior, please make sure you got the right one!", "Accept", "Cancel");
            }
            case 36:
            {
                Dialog_Show(playerid, DIALOG_SHOP_THIRTYSEVEN, DIALOG_STYLE_MSGBOX, "RogueDrifterZ shops", "{FFFFFF}You've picked LS Atrium, please make sure you got the right one!", "Accept", "Cancel");
            }
        }
	}
	return 1;
}

Dialog:DIALOG_SHOP_ONE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("24/7", x, y, z, r, 5.93, -30.91, 1003.55, DEFAULT_ROTATION, 10, SHOP_TYPE_247, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWO(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Ammunation", x, y, z, r, 315.58, -142.67, 999.60, DEFAULT_ROTATION, 7, SHOP_TYPE_AMMU, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THREE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Cluckin Bell", x, y, z, r, 365.7158, -9.8873, 1001.8516, DEFAULT_ROTATION, 9, SHOP_TYPE_CLUCKINBELL, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_FOUR(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Pizza stack", x, y, z, r, 	372.3520, -131.6510, 1001.4922, DEFAULT_ROTATION, 5, SHOP_TYPE_PIZZASTACK, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_FIVE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Burger shot", x, y, z, r, 363.4129, -74.5786, 1001.5078, DEFAULT_ROTATION, 10, SHOP_TYPE_BURGERSHOT, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_SIX(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Gym", x, y, z, r, 774.213989, -48.924297, 1000.585937, DEFAULT_ROTATION, 6, SHOP_TYPE_GYM, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_SEVEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Sex shop", x, y, z, r, -100.3521, -24.9300, 1000.7188, DEFAULT_ROTATION, 3, SHOP_TYPE_SEXSHOP, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_EIGHT(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Clothes shop", x, y, z, r, 161.391006, -93.159156, 1001.804687, DEFAULT_ROTATION, 18, SHOP_TYPE_CLOTHES, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_NINE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Motel", x, y, z, r, 2214.4973, -1150.5391, 1025.7969, DEFAULT_ROTATION, 15, SHOP_TYPE_MOTEL, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Police department", x, y, z, r, 246.375991, 109.245994, 1003.218750, DEFAULT_ROTATION, 10, SHOP_TYPE_POLICE, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_ELEVEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Bar", x, y, z, r, 501.980987, -69.150199, 998.757812, DEFAULT_ROTATION, 11, SHOP_TYPE_BAR, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWELVE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Barber shop", x, y, z, r, 411.9413, -54.3382, 1001.8984, DEFAULT_ROTATION, 12, SHOP_TYPE_BARBER, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Casino", x, y, z, r, 1133.2880, -15.7240, 1000.6797, DEFAULT_ROTATION, 12, SHOP_TYPE_CASINO, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_FOURTEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Tattoo shop", x, y, z, r, -204.2778, -27.2380, 1002.2734, DEFAULT_ROTATION, 16, SHOP_TYPE_TATTOO, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_FIFTEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Bank", x, y, z, r, 2315.952880, -1.618174, 26.742187, DEFAULT_ROTATION, 0, SHOP_TYPE_BANK, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_SIXTEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Club", x, y, z, r, 1204.809936, -11.586799, 1000.921875, DEFAULT_ROTATION, 2, SHOP_TYPE_CLUB, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_SEVENTEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Clothes shop", x, y, z, r, 226.293991, -7.431529, 1002.210937, DEFAULT_ROTATION, 5, VICTIM_SHOP, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_EIGHTEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Police department", x, y, z, r, 246.783996, 63.900199, 1003.640625, DEFAULT_ROTATION, 6, LS_POLICE, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_NINETEEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Police department", x, y, z, r, 288.745971, 169.350997, 1007.171875, DEFAULT_ROTATION, 3, LV_POLICE, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTY(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Gas-Station shop", x, y, z, r, -2240.468505, 137.060440, 1035.414062, DEFAULT_ROTATION, 6, SHOP_TYPE_GASINTERIOR, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYONE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Janitor room", x, y, z, r, 300.5835, 305.9462, 1003.5391, DEFAULT_ROTATION, 4, SHOP_TYPE_JANITORROOM, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYTWO(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Prison", x, y, z, r, -1968.4318, 324.6616, 1552.1387, DEFAULT_ROTATION, 14, SHOP_TYPE_PRISON, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYTHREE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Toilet", x, y, z, r, -221.059051, 1408.984008, 27.773437, DEFAULT_ROTATION, 18, SHOP_TYPE_TOILET, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYFOUR(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Bar", x, y, z, r, -229.2923, 1401.2948, 27.7656, DEFAULT_ROTATION, 18, BAR_SECONDARY, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYFIVE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Night club", x, y, z, r, 2305.8494, 1939.2384, 1419.5835, DEFAULT_ROTATION, 90, SHOP_TYPE_NIGHTCLUB, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYSIX(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Meat factory", x, y, z, r, 963.418762, 2108.292480, 1011.030273, DEFAULT_ROTATION, 1, SHOP_TYPE_MEATFACTORY, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYSEVEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Crack factory", x, y, z, r, 2541.6536, -1304.0980, 1025.0703, DEFAULT_ROTATION, 2, SHOP_TYPE_CRACKFACTORY, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYEIGHT(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Plane", x, y, z, r, 1.808619, 32.384357, 1199.593750, DEFAULT_ROTATION, 1, SHOP_TYPE_PLANE, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_TWENTYNINE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Car school", x, y, z, r, -2026.8298, -103.7083, 1035.1719, DEFAULT_ROTATION, 3, SHOP_TYPE_CARSCHOOL, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTY(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Bike school", x, y, z, r, 1494.325195, 1304.942871, 1093.289062, DEFAULT_ROTATION, 3, SHOP_TYPE_BIKESCHOOL, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYONE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Diner", x, y, z, r, 460.4912, -88.6018, 999.5547, DEFAULT_ROTATION, 4, SHOP_TYPE_RESTAURANT, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYTWO(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Donuts shop", x, y, z, r, 376.9821, -193.1117, 1000.6401, DEFAULT_ROTATION, 17, SHOP_TYPE_DONUTS, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYTHREE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Church", x, y, z, r, -2029.3816, 1019.2564, 1418.4969, DEFAULT_ROTATION, 0, SHOP_TYPE_CHURCH, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYFOUR(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Church", x, y, z, r, 388.0646, 2324.4270, 1889.5764, DEFAULT_ROTATION, 10, CHURCH_SECONDARY, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYFIVE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Police Department", x, y, z, r, -500.9834, 286.2127, 2001.0950, DEFAULT_ROTATION, 0, PD_SECONDARY, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYSIX(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Hospital", x, y, z, r, -54.9127, 149.2451, 999.0637, DEFAULT_ROTATION, 0, SHOP_TYPE_HOSPITAL, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}

Dialog:DIALOG_SHOP_THIRTYSEVEN(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z, Float:r;
        GetPlayerFacingAngle(playerid, r);
        GetPlayerPos(playerid, x, y, z);
        AddShop("Art Museum", x, y, z, r, 1700.6350, -1667.8002, 20.2188, DEFAULT_ROTATION, 18, SHOP_TYPE_LSART, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerShop[playerid] );
        SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Shop was added!", MESSAGE_CASE_SERVER);
    }
	return 1;
}
/*
AddPlayerClass(0, -229.2923, 1401.2948, 27.7656, 265.9331, 0, 0, 0, 0, 0, 0); // Bar

Dialog name, pos, interior, shoptype, shopname
Gas-station interior
Janitor room
Prison interior
Toilet place
Second bar
Night club
Meat factory
Crack factory
Plane interior(SHAMAL)
Car school
Bike school
Diner interior
Donuts shop
Church interior
Second church
Secondary PD
Hospital interior
LS Atrium


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


#define VICTIM_SHOP 17//SHOP_TYPE_CLOTHES
#define LS_POLICE 18 //SHOP_TYPE_POLICE
#define LV_POLICE 19 //SHOP_TYPE_POLICE
#define BAR_SECONDARY 29//SHOP_TYPE_BAR
#define CHURCH_SECONDARY 36//SHOP_TYPE_CHURCH
#define PD_SECONDARY 37//SHOP_TYPE_POLICE
*/