#include "Logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

// #include <iostream>

namespace Core {


Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::setLogPath( const std::string& logPath )
{
  m_logFile = logPath;
}

void Logger::init()
{

  std::vector< spdlog::sink_ptr > sinks;

  sinks.push_back( std::make_shared< spdlog::sinks::stdout_color_sink_mt >() );
  sinks.push_back( std::make_shared< spdlog::sinks::daily_file_sink_mt >( m_logFile, 0, 0 ) );

  m_logger = std::make_shared< spdlog::logger >( "logger", std::begin( sinks ), std::end( sinks ) );

  //spdlog::set_pattern( "[%H:%M:%S] [%l] %v" );
}


void Logger::Log( LoggingSeverity logSev, const std::string& text )
{
  // BOOST_LOG_SEV( m_lg, ( boost::log::trivial::severity_level ) logSev ) << text;
}

void Logger::error( const std::string& text )
{
  m_logger->error( text );
}

void Logger::info( const std::string& text )
{
  m_logger->info( text );
}

void Logger::debug( const std::string& text )
{
  m_logger->debug( text );
}

void Logger::fatal( const std::string& text )
{
  m_logger->critical( text );
}


}