#include "Logger.h"

#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "spdlog/sinks/daily_file_sink.h"

void Engine::Logger::init( const std::string& logPath )
{
  auto pos = logPath.find_last_of( std::filesystem::path::preferred_separator );

  if( pos != std::string::npos )
  {
    std::string realPath = logPath.substr( 0, pos );
    std::filesystem::create_directories( realPath );
  }

  spdlog::init_thread_pool( 8192, 1 );

  auto stdout_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
  auto daily_sink = std::make_shared< spdlog::sinks::daily_file_sink_mt >( logPath + ".log", 0, 0 );

  std::vector< spdlog::sink_ptr > sinks { stdout_sink, daily_sink };

  auto logger = std::make_shared< spdlog::async_logger >( "logger", sinks.begin(), sinks.end(),
                                                          spdlog::thread_pool(), spdlog::async_overflow_policy::block );


  spdlog::register_logger( logger );
  spdlog::set_pattern( "[%H:%M:%S.%e] [%^%l%$] %v" );
  spdlog::set_level( spdlog::level::trace );
  // always flush the log on criticial messages, otherwise it's done by libc
  // see: https://github.com/gabime/spdlog/wiki/7.-Flush-policy
  // nb: if the server crashes, log data can be missing from the file unless something logs critical just before it does
  spdlog::flush_on( spdlog::level::debug );
}

void Engine::Logger::setLogLevel( Engine::Logger::LogLevel logLevel )
{
  spdlog::set_level( static_cast< spdlog::level::level_enum >( logLevel ) );
}

void Engine::Logger::error( const std::string& text )
{
  spdlog::error( text );
}

void Engine::Logger::warn( const std::string& text )
{
  spdlog::warn( text );
}

void Engine::Logger::info( const std::string& text )
{
  spdlog::info( text );
}

void Engine::Logger::debug( const std::string& text )
{
  spdlog::debug( text );
}

void Engine::Logger::critical( const std::string& text )
{
  spdlog::critical( text );
}

void Engine::Logger::trace( const std::string& text )
{
  spdlog::trace( text );
}
