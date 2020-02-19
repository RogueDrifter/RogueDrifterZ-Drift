#if defined bcrypt_included
	#endinput
#endif
#define bcrypt_included

#include <YSI_Coding\y_hooks>//Credits to Y_Less

#if !defined HTTP_GET
	#include <a_http>
#endif

#define BCRYPT_HASH_LENGTH 61
#define BCRYPT_PLUGIN_VERSION "2.2.3"

enum BCRYPT_DEBUG_LEVEL {
	BCRYPT_LOG_FATAL,
	BCRYPT_LOG_ERROR,
	BCRYPT_LOG_WARNING,
	BCRYPT_LOG_INFO,
	BCRYPT_LOG_DEBUG,
	BCRYPT_LOG_TRACE
}

native bcrypt_hash(key[], cost = 12, callback_name[], callback_format[] = "", {Float, _}:...);
native bcrypt_check(password[], hash[], callback_name[], callback_format[] = "", {Float, _}:...);
native bcrypt_get_hash(dest[]);
native bool:bcrypt_is_equal();
native bool:bcrypt_needs_rehash(hash[], cost);
native bcrypt_find_cost(time_target = 250);
native bcrypt_set_thread_limit(value);
native bcrypt_debug(BCRYPT_DEBUG_LEVEL:level = BCRYPT_LOG_ERROR);

forward OnBcryptVersionCheck(index, response_code, data[]);

hook OnGameModeInit()
{
	HTTP(0, HTTP_GET, "api.ls-rcr.com/bcrypt/?version_check&version=" #BCRYPT_PLUGIN_VERSION, "", "OnBcryptVersionCheck");
    return 1;
}

public OnBcryptVersionCheck(index, response_code, data[])
{
	if(response_code == 200)
	{
		if(!strcmp("OK", data, false, 2))
		{
			print("plugin.bcrypt: The plugin is up-to-date.");
		}
		else if(!strcmp("UPDATE_AVAILABLE_MAJOR", data, false, 22))
		{
			print(" ");
			printf(" * plugin.bcrypt: A MAJOR UPDATE IS AVAILABLE:");
			printf(" * plugin.bcrypt: Current version: %s", BCRYPT_PLUGIN_VERSION);
			printf(" * plugin.bcrypt: Latest version: %s", data[23]);
			printf(" * plugin.bcrypt: Download: http://api.ls-rcr.com/bcrypt/?upgrade");
			printf(" * plugin.bcrypt: Upgrading is highly recommended.");
			print(" ");
		}
		else if(!strcmp("UPDATE_AVAILABLE_MINOR", data, false, 22))
		{
			print(" ");
			printf("plugin.bcrypt: A minor update is available:");
			printf("plugin.bcrypt: Current version: %s", BCRYPT_PLUGIN_VERSION);
			printf("plugin.bcrypt: Latest version: %s", data[23]);
			printf("plugin.bcrypt: Download: http://api.ls-rcr.com/bcrypt/?upgrade");
			printf("plugin.bcrypt: Upgrading is recommended.");
			print(" ");
		}
		else if(!strcmp("UPDATE_AVAILABLE_REVISION", data, false, 25))
		{
			print(" ");
			printf("plugin.bcrypt: A new revision is available:");
			printf("plugin.bcrypt: Current version: %s", BCRYPT_PLUGIN_VERSION);
			printf("plugin.bcrypt: Latest version: %s", data[26]);
			printf("plugin.bcrypt: Download: http://api.ls-rcr.com/bcrypt/?upgrade");
			printf("plugin.bcrypt: Upgrading is recommended.");
			print(" ");
		}
	}
	else
	{
		print("plugin.bcrypt: Version check done.");
	}

	return 1;
}
