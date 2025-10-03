#include "Logger.h"

#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info", "warn", "error", "fatal", "off" }

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

// #include <iostream>
#include <filesystem>
#include <mutex>
namespace fs = std::filesystem;

std::shared_ptr< Sapphire::buffer_sink_mt > Sapphire::Logger::m_bufferSink;

static inline std::shared_ptr< spdlog::logger > get_logger_nolock()
{
  return spdlog::get( "logger" );
}

// one-time init guard for async init
static std::once_flag s_init_once;

void Sapphire::Logger::ensure_initialized()
{
  auto existing = get_logger_nolock();
  if( existing )
  {
    // If a logger already exists, assume it was properly configured (e.g., via init()).
    // Avoid mutating sinks here to prevent data races with concurrent logging.
    if( !m_bufferSink )
    {
      m_bufferSink = std::make_shared< buffer_sink_mt >();
    }
    return;
  }

  // Serialize minimal logger creation to avoid races
  static std::mutex ensure_mtx;
  std::lock_guard< std::mutex > lk( ensure_mtx );
  // Re-check after acquiring lock
  existing = get_logger_nolock();
  if( existing )
  {
    if( !m_bufferSink ) m_bufferSink = std::make_shared< buffer_sink_mt >();
    return;
  }

  // Create a minimal synchronous logger to avoid crashes before init() is called
  try
  {
    if( !m_bufferSink )
      m_bufferSink = std::make_shared< buffer_sink_mt >();

    auto stdout_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
    std::vector< spdlog::sink_ptr > sinks{ stdout_sink, m_bufferSink };
    auto logger = std::make_shared< spdlog::logger >( "logger", sinks.begin(), sinks.end() );
    try { spdlog::register_logger( logger ); } catch( ... )
    {
      /* ignore duplicate */
    }
    spdlog::set_pattern( "[%H:%M:%S.%e] [%^%l%$] %v" );
    spdlog::set_level( spdlog::level::info );
    spdlog::flush_on( spdlog::level::critical );
  } catch( ... )
  {
    // Swallow to avoid throwing in logging path
  }
}

void Sapphire::Logger::init( const std::string& logPath )
{
  // Ensure target directory exists regardless of slash style
  try
  {
    fs::path p( logPath );
    auto dir = p.parent_path();
    if( !dir.empty() )
    {
      fs::create_directories( dir );
    }
  } catch( ... )
  {
    // ignore directory creation errors; we'll still try to log to console
  }

  // Run initialization once to avoid races when multiple threads call init()
  std::call_once( s_init_once, [&]()
  {
    // If a logger already exists, do not drop/recreate it to avoid races; just adopt it.
    if( auto existing = get_logger_nolock() )
    {
      try { spdlog::set_default_logger( existing ); } catch( ... )
      {
      }
      return;
    }

    try
    {
      // initialize async thread pool (ignore if already initialized)
      spdlog::init_thread_pool( 8192, 1 );
    } catch( ... )
    {
      // ignore
    }

    auto stdout_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();

    // Try to create a daily file sink, but tolerate failures (e.g., missing permissions/dirs)
    std::shared_ptr< spdlog::sinks::daily_file_sink_mt > daily_sink;
    try
    {
      daily_sink = std::make_shared< spdlog::sinks::daily_file_sink_mt >( logPath + ".log", 0, 0 );
    } catch( ... )
    {
      daily_sink.reset();
    }

    if( !m_bufferSink )
      m_bufferSink = std::make_shared< buffer_sink_mt >();

    std::vector< spdlog::sink_ptr > sinks{ stdout_sink };
    if( daily_sink ) sinks.push_back( daily_sink );
    sinks.push_back( m_bufferSink );

    auto logger = std::make_shared< spdlog::async_logger >( "logger", sinks.begin(), sinks.end(),
                                                            spdlog::thread_pool(),
                                                            spdlog::async_overflow_policy::block );

    // Make it the default logger for any direct spdlog::* calls
    try { spdlog::set_default_logger( logger ); } catch( ... )
    {
    }

    // Register it by name as well (ignore if already exists due to a race)
    try { spdlog::register_logger( logger ); } catch( ... )
    {
    }
    spdlog::set_pattern( "[%H:%M:%S.%e] [%^%l%$] %v" );
    spdlog::set_level( spdlog::level::debug );
    spdlog::flush_on( spdlog::level::critical );
  } );
}

void Sapphire::Logger::setLogLevel( uint8_t logLevel )
{
  ensure_initialized();
  spdlog::set_level( static_cast< spdlog::level::level_enum >( logLevel ) );
}

std::shared_ptr< Sapphire::buffer_sink_mt > Sapphire::Logger::getBufferSink()
{
  ensure_initialized();
  return m_bufferSink;
}

void Sapphire::Logger::error( const std::string& text )
{
  ensure_initialized();
  auto l = spdlog::get( "logger" );
  if( !l ) return;
  l->error( text );
}

void Sapphire::Logger::warn( const std::string& text )
{
  ensure_initialized();
  auto l = spdlog::get( "logger" );
  if( !l ) return;
  l->warn( text );
}

void Sapphire::Logger::info( const std::string& text )
{
  ensure_initialized();
  auto l = spdlog::get( "logger" );
  if( !l ) return;
  l->info( text );
}

void Sapphire::Logger::debug( const std::string& text )
{
  ensure_initialized();
  auto l = spdlog::get( "logger" );
  if( !l ) return;
  l->debug( text );
}

void Sapphire::Logger::fatal( const std::string& text )
{
  ensure_initialized();
  auto l = spdlog::get( "logger" );
  if( !l ) return;
  l->critical( text );
}

void Sapphire::Logger::trace( const std::string& text )
{
  ensure_initialized();
  auto l = spdlog::get( "logger" );
  if( !l ) return;
  l->trace( text );
}
