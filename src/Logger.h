#ifndef LOGGER_
#define LOGGER_
#include <string>
#include <mutex>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifdef _WIN32
#define __SHORT_FILE__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define ltime util::Localtime().c_str()
#define RECORD util::Logger::GetInstance().Record

#define LOG(what) std::cout << what;
#define LOG_ERROR(fmt, ...) RECORD(util::IB2ERROR,__SHORT_FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LOG_WARNING(fmt, ...) RECORD(util::WARNING, __SHORT_FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LOG_UPGRADE(fmt,...) RECORD(util::UPGRADE,__SHORT_FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) RECORD(util::DEBUG, __SHORT_FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LOG_NOTICE(fmt, ...) RECORD(util::NOTICE, __SHORT_FILE__, __LINE__, fmt, ## __VA_ARGS__)

namespace util
{
enum LogType { NONE = 0, IB2ERROR, WARNING, UPGRADE, DEBUG, NOTICE };
class Logger
{
public:
    static Logger& GetInstance();
    ~Logger();

    void SetLoggerLevel(int nLevel);
    void Record(LogType eType, const char* file, int line, const char* fmt, ...);

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;

    std::mutex m_stMutex;
    int m_nLoggerLevel = 4;
    char * m_pBuffer = NULL;
};

std::string Localtime();
} // namespace util

#endif // !LOGGER_
