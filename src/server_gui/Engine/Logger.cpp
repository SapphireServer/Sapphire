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

  try
  {
    spdlog::init_thread_pool( 8192, 1 );
  }
  catch(...)
  {
    // ignore if already initialized
  }

  auto stdout_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
  std::shared_ptr< spdlog::sinks::daily_file_sink_mt > daily_sink;
  try
  {
    daily_sink = std::make_shared< spdlog::sinks::daily_file_sink_mt >( logPath + ".log", 0, 0 );
  }
  catch(...)
  {
    daily_sink.reset();
  }

  std::vector< spdlog::sink_ptr > sinks { stdout_sink };
  if( daily_sink ) sinks.push_back( daily_sink );

  // Use a unique logger name to avoid conflicts with Sapphire::Logger
  auto logger = std::make_shared< spdlog::async_logger >( "gui_logger", sinks.begin(), sinks.end(),
                                                          spdlog::thread_pool(), spdlog::async_overflow_policy::block );

  // Make it the default logger so Engine::Logger::* continues to work
  spdlog::set_default_logger( logger );

  // Also register it by name for completeness
  try { spdlog::register_logger( logger ); } catch(...) {}

  spdlog::set_pattern( "[%H:%M:%S.%e] [%^%l%$] %v" );
  spdlog::set_level( spdlog::level::trace );
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
