#include "Logger.h"
#include <stdarg.h>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>


namespace util
{
void Logger::Record(LogType eType, const char *file, int line, const char *fmt, ...)
{
    std::lock_guard<std::mutex> lk(m_stMutex);

    if (eType > m_nLoggerLevel)
    {
        return;
    }
    memset(m_pBuffer, 0, 2048);

    switch (eType)
    {
    case IB2ERROR:
        snprintf(m_pBuffer, 2048, ANSI_COLOR_RED "%s [ERROR] [%s-%d] %s" ANSI_COLOR_RESET "\n",
            ltime, file, line, fmt);
        break;
    case WARNING:
        snprintf(m_pBuffer, 2048, ANSI_COLOR_MAGENTA "%s [WARNING] [%s-%d] %s" ANSI_COLOR_RESET "\n",
            ltime, file, line, fmt);
        break;
    case UPGRADE:
        snprintf(m_pBuffer, 2048, ANSI_COLOR_BLUE "%s [UPGRADE] [%s-%d] %s" ANSI_COLOR_RESET "\n",
            ltime, file, line, fmt);
        break;
    case DEBUG:
        snprintf(m_pBuffer, 2048, ANSI_COLOR_GREEN "%s [DEBUG] [%s-%d] %s" ANSI_COLOR_RESET "\n",
            ltime, file, line, fmt);
        break;
    case NOTICE:
        snprintf(m_pBuffer, 2048, ANSI_COLOR_CYAN "%s [NOTICE] [%s-%d] %s" ANSI_COLOR_RESET "\n",
            ltime, file, line, fmt);
        break;
    default:
        break;
    }

    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, m_pBuffer, args);
    va_end(args);
}

Logger & Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    m_nLoggerLevel = 4;
    m_pBuffer = new char[2048];
}

Logger::~Logger()
{
    delete[] m_pBuffer;
}

void Logger::SetLoggerLevel(int nLevel)
{
    if ((nLevel == 0) || (nLevel > NOTICE))
    {
        Record(WARNING, __SHORT_FILE__, __LINE__, "Invalid logger level (%d)", nLevel);
    }
    else
    {
        m_nLoggerLevel = nLevel;
    }
}

std::string Localtime()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());

    auto t = std::time(nullptr);
    auto tm_c = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm_c, "%Y-%m-%d %H:%M:%S");
    std::string strTime = oss.str();
    strTime += ".";
    strTime += std::to_string(ms.count() % 1000);

    return strTime;
}
}
