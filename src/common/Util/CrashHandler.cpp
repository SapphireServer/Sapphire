#include "CrashHandler.h"

#include <signal.h>
#include <Logging/Logger.h>

#ifndef _WIN32
#include <execinfo.h>
#include <cxxabi.h>
#else

#include <windows.h>
#include <intrin.h>
#include <dbghelp.h>

#pragma comment(lib, "dbghelp.lib")

inline std::string basename( const std::string& file )
{
    size_t i = file.find_last_of( "\\/" );
    if ( i == std::string::npos )
    {
        return file;
    }
    else
    {
        return file.substr( i + 1 );
    }
}

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

  DWORD machine = IMAGE_FILE_MACHINE_AMD64;

  HANDLE process = GetCurrentProcess();
  HANDLE thread = GetCurrentThread();
  CONTEXT context = {};
  context.ContextFlags = CONTEXT_FULL;
  RtlCaptureContext( &context );

  SymInitialize( process, NULL, TRUE );
  SymSetOptions( SYMOPT_LOAD_LINES );

  STACKFRAME frame = {};
  frame.AddrPC.Offset = context.Rip;
  frame.AddrPC.Mode = AddrModeFlat;
  frame.AddrFrame.Offset = context.Rbp;
  frame.AddrFrame.Mode = AddrModeFlat;
  frame.AddrStack.Offset = context.Rsp;
  frame.AddrStack.Mode = AddrModeFlat;

  while( StackWalk( machine, process, thread, &frame, &context, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL ) )
  {
    auto moduleBase = SymGetModuleBase( process, frame.AddrPC.Offset );

    std::string moduleName;
    std::string funcName;
    std::string fileName;
    int lineNum = 0;

    char moduelBuff[MAX_PATH];
    if( moduleBase && GetModuleFileNameA( ( HINSTANCE ) moduleBase, moduelBuff, MAX_PATH ) )
    {
      moduleName = basename( moduelBuff );
    }
    else
    {
      moduleName = "Unknown Module";
    }


    DWORD64 offset = 0;
    char symbolBuffer[sizeof( IMAGEHLP_SYMBOL ) + 255];
    PIMAGEHLP_SYMBOL symbol = ( PIMAGEHLP_SYMBOL ) symbolBuffer;
    symbol->SizeOfStruct = ( sizeof IMAGEHLP_SYMBOL ) + 255;
    symbol->MaxNameLength = 254;

    if( SymGetSymFromAddr( process, frame.AddrPC.Offset, &offset, symbol ) )
    {
      funcName = symbol->Name;
    }
    else
    {
      funcName = "Unknown Function";
    }

    IMAGEHLP_LINE line;
    line.SizeOfStruct = sizeof( IMAGEHLP_LINE );

    DWORD offset_ln = 0;
    if( SymGetLineFromAddr( process, frame.AddrPC.Offset, &offset_ln, &line ) )
    {
      fileName = line.FileName;
      lineNum = line.LineNumber;
    }

    Logger::fatal( "[{:x}] {}({}): {} ({})", frame.AddrPC.Offset, fileName, lineNum, funcName, moduleName );
  }

  SymCleanup( process );

#endif
}