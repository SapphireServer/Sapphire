#ifndef _LOGGER_H
#define _LOGGER_H

#include <spdlog/spdlog.h>

namespace Core {

enum struct LoggingSeverity : uint8_t
{
  trace = 0,
  debug = 1,
  info = 2,
  warning = 3,
  error = 4,
  fatal = 5
};

class Logger
{

private:
  std::string m_logFile;

  std::shared_ptr< spdlog::logger > m_logger;

public:
  Logger();

  ~Logger();

  void init();

  void Log( LoggingSeverity logSev, const std::string& text );

  void error( const std::string& text );

  void info( const std::string& text );

  void debug( const std::string& text );

  void fatal( const std::string& text );

  void setLogPath( const std::string& logPath );

};


}


#endif
