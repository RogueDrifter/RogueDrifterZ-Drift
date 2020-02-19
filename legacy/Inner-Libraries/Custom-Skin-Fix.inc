

#if defined RDZ_CSKINS_Included_
   #endinput
#endif

#define RDZ_CSKINS_Included_

GetPlayerSkinEx(playerid)
   return (GetPlayerCustomSkin(playerid) <= 0) ? GetPlayerSkin(playerid) : GetPlayerCustomSkin(playerid);
  
#if defined _ALS_GetPlayerSkin 
   #undef GetPlayerSkin 
#else
#define _ALS_GetPlayerSkin
   #endif
#define GetPlayerSkin GetPlayerSkinEx