#include "log.h"

void StdoutLogger::log(LogLevel lvl, std::string msg)
{
    switch (lvl) {
        case LogLevel::Info:
            fmt::print("{}\n", msg);
            break;
        case LogLevel::Success:
            fmt::print("SUCCESS - {}\n", msg);
            break;
        case LogLevel::Warning:
            fmt::print("WARNING - {}\n", msg);
            break;
        case LogLevel::Error:
            fmt::print("ERROR - {}\n", msg);
            break;
    }
}

namespace Log {

static std::unique_ptr<Logger> _globl_logger = std::make_unique<StdoutLogger>();

Logger* global_logger()
{
    return _globl_logger.get();
}

void set_global_logger(std::unique_ptr<Logger>&& logger)
{
    _globl_logger = std::move(logger);
}

} // namespace Log
