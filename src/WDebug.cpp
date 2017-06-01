#include <WDebug.h>

#if defined( BUILD_ANDROID )
#include <platforms/ANDROID/debug_p.h>
#elif defined( BUILD_GENERIC )
#include <platforms/GENERIC/debug_p.h>
#elif defined( BUILD_IOS )
#include <platforms/IOS/debug_p.h>
#endif

#include <stdio.h>
#include <stdarg.h>

#define LOG_LINE_LIMIT  65535

std::mutex WDebug::m_logMutex;

void WDebug::log(const char* label, const char* format, ... )
{
  static char buffer[LOG_LINE_LIMIT];

  std::lock_guard<std::mutex> lock(WDebug::m_logMutex);

  snprintf (buffer, LOG_LINE_LIMIT - 1, "%s: %s", label, format);
  
  va_list args;
  va_start(args, format);
  vsnprintf (buffer, LOG_LINE_LIMIT - 1, buffer, args);
  va_end(args);

  Debug_p::log(buffer);
}
