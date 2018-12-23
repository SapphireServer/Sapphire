#ifndef _LOGGER_H
#define _LOGGER_H 

#include <string>

namespace Sapphire
{

  class Logger
  {

  private:
    std::string m_logFile;
    Logger();
    ~Logger();

  public:

    static void init( const std::string& logPath );

    static void error( const std::string& text );

    static void info( const std::string& text );

    static void debug( const std::string& text );

    static void fatal( const std::string& text );

  };

}


#endif
