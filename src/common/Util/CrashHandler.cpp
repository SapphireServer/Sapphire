#include "CrashHandler.h"

#include <signal.h>
#include <Logging/Logger.h>

#ifndef _WIN32
#include <execinfo.h>
#include <cxxabi.h>
#else
#include <stackwalker/StackWalker.h>

class SapphireStackWalker : public StackWalker
{
public:
  SapphireStackWalker() : StackWalker() {}
protected:
  virtual void OnOutput( LPCSTR szText )
  {
    Sapphire::Logger::fatal( "{}", szText );
  }
};
#endif

using namespace Sapphire::Common;

Util::CrashHandler::CrashHandler()
{
  signal( SIGABRT, signalHandler );
  signal( SIGSEGV, signalHandler );
  signal( SIGILL, signalHandler );
  signal( SIGFPE, signalHandler );

#ifndef _WIN32
  // SIGBUS not supported on windows
  signal( SIGBUS, signalHandler );
#endif

#undef REGISTER_SIGNAL
}

void Util::CrashHandler::signalHandler( int sigNum )
{
#define ADD_SIGNAL_MAP( x ) case x: name = #x; break;
  const char* name = nullptr;
  switch( sigNum )
  {
    ADD_SIGNAL_MAP( SIGABRT );
    ADD_SIGNAL_MAP( SIGSEGV );
    ADD_SIGNAL_MAP( SIGILL );
    ADD_SIGNAL_MAP( SIGFPE );
#ifndef _WIN32
    // SIGBUS not supported on windows
    ADD_SIGNAL_MAP( SIGBUS );
#endif
  }
#undef ADD_SIGNAL_MAP

  if( name )
  {
    Logger::fatal( "Caught signal {} ({})", sigNum, name );
  }
  else
  {
    Logger::fatal( "Caught signal {}", sigNum );
  }

  printStackTrace();

  exit( sigNum );
}


void Util::CrashHandler::printStackTrace( unsigned int max_frames )
{
  Logger::fatal( "Stack trace:" );

#ifndef _WIN32

  // used as is from: https://oroboro.com/stack-trace-on-crash/
  // only changes output slightly

  void* addrlist[ max_frames + 1 ];

  int addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ) );

  if ( addrlen == 0 )
  {
    Logger::fatal( "No stack addresses available." );
    return;
  }

  char** symbollist = backtrace_symbols( addrlist, addrlen );

  size_t funcnamesize = 1024;
  char funcname[1024];

  // iterate over the returned symbol lines. skip the first, it is the
  // address of this function.
  for ( unsigned int i = 0; i < addrlen; i++ )
  {
    char* begin_name   = NULL;
    char* begin_offset = NULL;
    char* end_offset   = NULL;

    // find parentheses and +address offset surrounding the mangled name
    for ( char *p = symbollist[i]; *p; ++p )
    {
      if ( *p == '(' )
        begin_name = p;
      else if ( *p == '+' )
        begin_offset = p;
      else if ( *p == ')' && ( begin_offset || begin_name ))
        end_offset = p;
    }

    if ( begin_name && end_offset && ( begin_name < end_offset ))
    {
      *begin_name++ = '\0';
      *end_offset++ = '\0';
      if( begin_offset )
        *begin_offset++ = '\0';

      // mangled name is now in [begin_name, begin_offset) and caller
      // offset in [begin_offset, end_offset). now apply
      // __cxa_demangle():

      int status = 0;
      char* ret = abi::__cxa_demangle( begin_name, funcname,
                                       &funcnamesize, &status );
      char* fname = begin_name;
      if( status == 0 )
        fname = ret;

      const char* format = " {} {:40} {} + {}";

      if( begin_offset )
      {
        Logger::fatal( format, end_offset, symbollist[ i ], fname, begin_offset );
      }
      else
      {
        Logger::fatal( format, end_offset, symbollist[ i ], fname, "" );
      }
    }
  }

  free( symbollist );

#else

  SapphireStackWalker sw;
  sw.ShowCallstack();

#endif
}