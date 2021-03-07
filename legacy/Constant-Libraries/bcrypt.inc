#if defined bcrypt_included
	#endinput
#endif
#define bcrypt_included

#define BCRYPT_HASH_LENGTH 61
#define BCRYPT_PLUGIN_VERSION "2.2.4"

enum BCRYPT_DEBUG_LEVEL {
	BCRYPT_LOG_FATAL,
	BCRYPT_LOG_ERROR,
	BCRYPT_LOG_WARNING,
	BCRYPT_LOG_INFO,
	BCRYPT_LOG_DEBUG,
	BCRYPT_LOG_TRACE
}

native bcrypt_hash(const key[], cost = 12, const callback_name[], const callback_format[] = "", {Float, _}:...);
native bcrypt_check(const password[], const hash[], const callback_name[], const callback_format[] = "", {Float, _}:...);
native bcrypt_get_hash(const dest[]);
native bool:bcrypt_is_equal();
native bool:bcrypt_needs_rehash(const hash[], cost);
native bcrypt_find_cost(time_target = 250);
native bcrypt_set_thread_limit(value);
native bcrypt_debug(BCRYPT_DEBUG_LEVEL:level = BCRYPT_LOG_ERROR);