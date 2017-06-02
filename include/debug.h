#ifndef DEBUG_H
#define DEBUG_H

#include <mutex>

class Debug
{
public:
    static void log(const char* label, const char* format, ...);

private:
    static std::mutex m_logMutex;
};

#ifdef LOGGING_DISABLED
#define LOGD(str, ...)
#define LOGW(str, ...)
#define LOGI(str, ...)
#define LOGE(str, ...)
#else
#define LOGD(str, ...) Debug::log("DEBUG", str, ##__VA_ARGS__)
#define LOGW(str, ...) Debug::log("WARNING", str, ##__VA_ARGS__)
#define LOGI(str, ...) Debug::log("INFO", str, ##__VA_ARGS__)
#define LOGE(str, ...) Debug::log("ERROR", str, ##__VA_ARGS__)
#endif

#endif // DEBUG_H
