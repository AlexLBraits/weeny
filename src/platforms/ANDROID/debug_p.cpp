#include "debug_p.h"
#include <android/log.h>

void Debug_p::log(const char* message)
{
	__android_log_print(ANDROID_LOG_DEBUG, "WEENY", message);
}
