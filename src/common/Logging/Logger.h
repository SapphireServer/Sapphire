#ifndef _LOGGER_H
#define _LOGGER_H 

#include <string>

namespace Sapphire
{

  class Logger
  {

  private:
    std::string m_logFile;

  public:
    Logger();

    ~Logger();

    void init();

    void error( const std::string& text );

    void info( const std::string& text );

    void debug( const std::string& text );

    void fatal( const std::string& text );

    void setLogPath( const std::string& logPath );

  };

}


#endif
