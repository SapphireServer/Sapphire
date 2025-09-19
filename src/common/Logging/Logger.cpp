#include "Logger.h"

#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info", "warn", "error", "fatal", "off" }

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

// #include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

std::shared_ptr< Sapphire::buffer_sink_mt > Sapphire::Logger::m_bufferSink;


void Sapphire::Logger::init( const std::string& logPath )
{
  auto pos = logPath.find_last_of( fs::path::preferred_separator );

  if( pos != std::string::npos )
  {
    std::string realPath = logPath.substr( 0, pos );
    fs::create_directories( realPath );
  }

  spdlog::init_thread_pool( 8192, 1 );

  auto stdout_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
  auto daily_sink = std::make_shared< spdlog::sinks::daily_file_sink_mt >( logPath + ".log", 0, 0 );

  m_bufferSink = std::make_shared< buffer_sink_mt >();

  std::vector< spdlog::sink_ptr > sinks{ stdout_sink, daily_sink, m_bufferSink };

  auto logger = std::make_shared< spdlog::async_logger >( "logger", sinks.begin(), sinks.end(),
                                                          spdlog::thread_pool(), spdlog::async_overflow_policy::block );


  spdlog::register_logger( logger );
  spdlog::set_pattern( "[%H:%M:%S.%e] [%^%l%$] %v" );
  spdlog::set_level( spdlog::level::debug );
  // always flush the log on criticial messages, otherwise it's done by libc
  // see: https://github.com/gabime/spdlog/wiki/7.-Flush-policy
  // nb: if the server crashes, log data can be missing from the file unless something logs critical just before it does
  spdlog::flush_on( spdlog::level::critical );
}

void Sapphire::Logger::setLogLevel( uint8_t logLevel )
{
  spdlog::set_level( static_cast< spdlog::level::level_enum >( logLevel ) );
}

std::shared_ptr< Sapphire::buffer_sink_mt > Sapphire::Logger::getBufferSink()
{
  return m_bufferSink;
}

void Sapphire::Logger::error( const std::string& text )
{
  spdlog::get( "logger" )->error( text );
}

void Sapphire::Logger::warn( const std::string& text )
{
  spdlog::get( "logger" )->warn( text );
}

void Sapphire::Logger::info( const std::string& text )
{
  spdlog::get( "logger" )->info( text );
}

void Sapphire::Logger::debug( const std::string& text )
{
  spdlog::get( "logger" )->debug( text );
}

void Sapphire::Logger::fatal( const std::string& text )
{
  spdlog::get( "logger" )->critical( text );
}

void Sapphire::Logger::trace( const std::string& text )
{
  spdlog::get( "logger" )->trace( text );
}
