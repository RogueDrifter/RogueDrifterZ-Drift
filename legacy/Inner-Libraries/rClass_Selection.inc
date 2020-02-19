#if defined _rClassSelection_included
	#endinput
#endif

#define _rClassSelection_included

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#if !defined MAX_SKINS_USED
	#define MAX_SKINS_USED 60 // Maximum amount of special skins change to your maximum amount you will use.
#endif

#if !defined KEY_SCLASS
	#define KEY_SCLASS KEY_SPRINT+KEY_WALK //the key used for the class selection
#endif

#if !defined KEY_RCLASS
	#define KEY_RCLASS KEY_RIGHT //key for switching between skins forward
#endif

#if !defined KEY_LCLASS
	#define KEY_LCLASS KEY_LEFT// key for switching backwards between skins
#endif

enum rPlayerData
{
	PlayerChoosing, 
	PlayerSkins, 
	FTimer
};

static 
	rPClass[MAX_PLAYERS][rPlayerData], 
	SpecialSkin[MAX_SKINS_USED];

#if defined OnAddSkin
	forward OnAddSkin(skinid);
#endif

#if defined OnPlayerSpecialRequestClass
	forward OnPlayerSpecialRequestClass(playerid);
#endif

#if defined OnPlayerChangeSpecialClass
	forward OnPlayerChangeSpecialClass(playerid, oldskin, newskin);
#endif

#if defined OnPlayerFinishSpecialClass
	forward OnPlayerFinishSpecialClass(playerid, fskinid);
#endif

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(KEY_PRESSED(KEY_SCLASS) && rPClass[playerid][PlayerChoosing] ==0)
	{
		rPClass[playerid][PlayerChoosing]=1;
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Returning to special class selection after next death. (press again to cancel)", MESSAGE_CASE_SERVER);
	}

	else if(KEY_PRESSED(KEY_SCLASS) && rPClass[playerid][PlayerChoosing] ==1)
	{
		rPClass[playerid][PlayerChoosing]=0;
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Cancelled the special class request.", MESSAGE_CASE_SERVER);
	}

	else if(KEY_PRESSED(KEY_SCLASS) && rPClass[playerid][PlayerChoosing] ==2)
	{
		SpawnPlayer(playerid);
	}

	if(KEY_PRESSED(KEY_LCLASS) && rPClass[playerid][PlayerChoosing] ==2 && rPClass[playerid][PlayerSkins] <= MAX_SKINS_USED && rPClass[playerid][PlayerSkins] >= 1)
	{
		rPClass[playerid][PlayerSkins]--;
		if(SpecialSkin[rPClass[playerid][PlayerSkins]] ==0 )
		{
			for(new i; i < MAX_SKINS_USED; i++)
			{
				if(SpecialSkin[i] < rPClass[playerid][PlayerSkins] && SpecialSkin[i] != 0)
				{
					#if defined OnPlayerChangeSpecialClass
						new oldskin = GetPlayerSkin(playerid);
					#endif

					SetPlayerSkin(playerid, SpecialSkin[i]);
					rPClass[playerid][PlayerSkins]=i;

		 			#if defined OnPlayerChangeSpecialClass
  						OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerSkin(playerid));
					#endif
				}
			}
		}	

		else
		{
			#if defined OnPlayerChangeSpecialClass
				new oldskin = GetPlayerSkin(playerid);
			#endif

			SetPlayerSkin(playerid, SpecialSkin[rPClass[playerid][PlayerSkins]]);

			#if defined OnPlayerChangeSpecialClass
  				OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerSkin(playerid));
			#endif
		}
	}

	if(KEY_PRESSED(KEY_RCLASS) && rPClass[playerid][PlayerChoosing] ==2 && rPClass[playerid][PlayerSkins] <= MAX_SKINS_USED -1 && rPClass[playerid][PlayerSkins] >= 0)
	{
		rPClass[playerid][PlayerSkins]++;
		if(SpecialSkin[rPClass[playerid][PlayerSkins]] ==0 )
		{
			for(new i; i < MAX_SKINS_USED; i++)
			{
  				if(SpecialSkin[i] > rPClass[playerid][PlayerSkins] && SpecialSkin[i] != 0)
				{
					#if defined OnPlayerChangeSpecialClass
						new oldskin = GetPlayerSkin(playerid);
					#endif

			 		SetPlayerSkin(playerid, SpecialSkin[i]);
				  	rPClass[playerid][PlayerSkins]=i;

					#if defined OnPlayerChangeSpecialClass
				  		OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerSkin(playerid));
					#endif
			 	}
			}
		}

		else
	 	{
	 		#if defined OnPlayerChangeSpecialClass
	 			new oldskin = GetPlayerSkin(playerid);
	 		#endif

	 		SetPlayerSkin(playerid, SpecialSkin[rPClass[playerid][PlayerSkins]]);

	 		#if defined OnPlayerChangeSpecialClass
	 			OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerSkin(playerid));
	 		#endif
	 	}
	}
	return 1;
}

forward FreezeClass(playerid);
public FreezeClass(playerid)
{
	if(rPClass[playerid][PlayerChoosing]==2 && GetPlayerInterior(playerid) ==4) TogglePlayerControllable(playerid, false);
	else if(GetPlayerInterior(playerid) ==0 && rPClass[playerid][PlayerChoosing] ==2) rPClass[playerid][PlayerChoosing]=0;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	KillTimer(rPClass[playerid][FTimer]);

	return 1;
}

hook OnPlayerConnect(playerid)
{
	rPClass[playerid][FTimer] = SetTimerEx("FreezeClass", 1000, true, "d", playerid);
	rPClass[playerid][PlayerChoosing]= 0;
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if(rPClass[playerid][PlayerChoosing] ==1)
	{
		#if defined OnPlayerSpecialRequestClass
			OnPlayerSpecialRequestClass(playerid);
		#endif

		rPClass[playerid][PlayerChoosing]=2;
		rPClass[playerid][PlayerSkins]=0;
		TogglePlayerControllable(playerid, true);
		SetPlayerPos(playerid, 305.8891, 305.6985, 999.1484);

		SetPlayerInterior(playerid, 4);
		SetPlayerFacingAngle(playerid, 85.0351);
		SetPlayerCameraPos(playerid, 302.58, 305.86, 999.15);
		SetPlayerCameraLookAt(playerid, 305.8891, 305.6985, 999.1484);
	}

	else if(rPClass[playerid][PlayerChoosing]==2)
	{
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
		SetPlayerInterior(playerid, 0);
		rPClass[playerid][PlayerChoosing]=0;

		#if defined OnPlayerFinishSpecialClass
			OnPlayerFinishSpecialClass(playerid, GetPlayerSkin(playerid));
		#endif
	}
	return 1;
}

static stock IsSkinUsed(skinid)
{
	for(new i; i < MAX_SKINS_USED; i++)
	{
		if(SpecialSkin[i] == skinid) return 1;
	}
	return 0;
}

stock AddSkin(skinid)
{
	if(skinid > 30000 || skinid < 25000) return 0;
	if(IsSkinUsed(skinid)) return 0;

 	for(new i; i < MAX_SKINS_USED; i++)
	{
		if(SpecialSkin[i] == 0 && SpecialSkin[i] != skinid)
		{
 			SpecialSkin[i]= skinid;
			 
 			#if defined OnAddSkin
 				OnAddSkin(skinid);
 			#endif

		 	break;
 		}
	}
	return 1;
}

CMD:rclass(playerid, params[])
{
	if(rPClass[playerid][PlayerChoosing] ==0)
	{
		rPClass[playerid][PlayerChoosing]=1;
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Returning to special class selection after next death. (press again to cancel)", MESSAGE_CASE_SERVER);
	}
	else if(rPClass[playerid][PlayerChoosing] ==1)
	{
		rPClass[playerid][PlayerChoosing]=0;
		SendRDZMessage(playerid, RDZ_OFFICIAL_COLOR, "Cancelled the special class request.", MESSAGE_CASE_SERVER);
	}
	return 1;
}

CMD:saverclass(playerid, params[])
{
	if(rPClass[playerid][PlayerChoosing] ==2) SpawnPlayer(playerid);
	return 1;
}

stock IsPlayerPickingSkin(playerid)
	return (rPClass[playerid][PlayerChoosing] == 1 || rPClass[playerid][PlayerChoosing] == 2);