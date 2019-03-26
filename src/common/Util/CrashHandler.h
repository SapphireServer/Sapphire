#ifndef SAPPHIRE_SIGNALHANDLER_H
#define SAPPHIRE_SIGNALHANDLER_H


// based on: https://oroboro.com/stack-trace-on-crash/

namespace Sapphire::Common::Util
{

  /*!
   * @brief Provides cross platform stack trace dumping.
   *
   * Statically init it somewhere so it registers the signal handlers before main runs and you're good to go.
   */
  class CrashHandler
  {
  public:
    CrashHandler();
    virtual ~CrashHandler() = default;

  private:
    static void signalHandler( int sigNum );

    static void printStackTrace( unsigned int max_frames = 63 );
  };
}

#endif //SAPPHIRE_CRASHHANDLER_H
