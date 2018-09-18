#include "Logger.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <iostream>

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

  auto format = (
    boost::log::expressions::stream <<
                                    boost::log::expressions::format_date_time< boost::posix_time::ptime >(
                                      "TimeStamp", "[%H:%M:%S]" ) <<
                                    "[" << boost::log::trivial::severity << "] " <<
                                    boost::log::expressions::smessage
  );

  boost::log::add_file_log
    (
      boost::log::keywords::file_name =
        m_logFile + "%Y-%m-%d.log",                                        /*< file name pattern >*/
      boost::log::keywords::rotation_size =
        10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
      boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point( 0, 0,
                                                                                                   0 ), /*< ...or at midnight >*/
      boost::log::keywords::open_mode = std::ios::app,
      boost::log::keywords::format = format,
      boost::log::keywords::auto_flush = true
    );

  boost::log::add_console_log( std::cout, boost::log::keywords::format = format );

  boost::log::add_common_attributes();
}


void Logger::Log( LoggingSeverity logSev, const std::string& text )
{
  BOOST_LOG_SEV( m_lg, ( boost::log::trivial::severity_level ) logSev ) << text;
}

void Logger::error( const std::string& text )
{
  BOOST_LOG_SEV( m_lg, boost::log::trivial::severity_level::error ) << text;
}

void Logger::info( const std::string& text )
{
  BOOST_LOG_SEV( m_lg, boost::log::trivial::severity_level::info ) << text;
}

void Logger::debug( const std::string& text )
{
  BOOST_LOG_SEV( m_lg, boost::log::trivial::severity_level::debug ) << text;
}

void Logger::fatal( const std::string& text )
{
  BOOST_LOG_SEV( m_lg, boost::log::trivial::severity_level::fatal ) << text;
}


}