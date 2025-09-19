#pragma once

#include <string>
#include <vector>
#include <spdlog/fmt/fmt.h>

#include "spdlog/sinks/base_sink.h"

namespace Sapphire
{
  // Custom sink class
  // Simplified custom sink class that avoids formatter conflicts
  template< typename Mutex >
  class buffer_sink : public spdlog::sinks::base_sink< Mutex >
  {
  public:
    buffer_sink() = default;

    std::vector< std::string > getMessages() const
    {
      std::lock_guard< Mutex > lock( this->mutex_ );
      return messages_;
    }

    void clearMessages()
    {
      std::lock_guard< Mutex > lock( this->mutex_ );
      messages_.clear();
    }

    size_t getMessageCount() const
    {
      std::lock_guard< Mutex > lock( this->mutex_ );
      return messages_.size();
    }

  protected:
    void sink_it_( const spdlog::details::log_msg& msg ) override
    {
      // Simple approach: extract the raw message and add basic formatting
      std::string raw_message( msg.payload.data(), msg.payload.size() );

      // Create a simple timestamp (you can improve this)
      auto time_t = std::chrono::system_clock::to_time_t( msg.time );
      auto tm = *std::localtime( &time_t );

      // Format: [HH:MM:SS] [LEVEL] message
      char time_buf[32];
      std::strftime( time_buf, sizeof( time_buf ), "%H:%M:%S", &tm );

      std::string level_str;
      switch( msg.level )
      {
        case spdlog::level::trace: level_str = "trace"; break;
        case spdlog::level::debug: level_str = "debug"; break;
        case spdlog::level::info: level_str = "info"; break;
        case spdlog::level::warn: level_str = "warn"; break;
        case spdlog::level::err: level_str = "error"; break;
        case spdlog::level::critical: level_str = "fatal"; break;
        default: level_str = "unknown"; break;
      }

      std::string formatted_message = fmt::format( "[{}] [{}] {}", time_buf, level_str, raw_message );

      messages_.push_back( std::move( formatted_message ) );

      // Limit buffer size
      if( messages_.size() > max_messages_ )
      {
        messages_.erase( messages_.begin() );
      }
    }

    void flush_() override
    {
      // Nothing to flush for this sink
    }

  private:
    std::vector< std::string > messages_;
    static const size_t max_messages_ = 1000;
  };

  using buffer_sink_mt = buffer_sink< std::mutex >;
  using buffer_sink_st = buffer_sink< spdlog::details::null_mutex >;



  class Logger
  {
  private:
    std::string m_logFile;
    static std::shared_ptr< buffer_sink_mt > m_bufferSink;

    Logger() = default;

    ~Logger() = default;

  public:
    static void init( const std::string& logPath );

    static void setLogLevel( uint8_t logLevel );

    static std::shared_ptr< buffer_sink_mt > getBufferSink();

    // todo: this is a minor increase in build time because of fmtlib, but much less than including spdlog directly

    static void error( const std::string& text );

    template< typename... Args >
    static void error( const std::string& text, const Args&... args )
    {
      error( fmt::format( text, args... ) );
    }

    static void warn( const std::string& text );

    template< typename... Args >
    static void warn( const std::string& text, const Args&... args )
    {
      warn( fmt::format( text, args... ) );
    }


    static void info( const std::string& text );

    template< typename... Args >
    static void info( const std::string& text, const Args&... args )
    {
      info( fmt::format( text, args... ) );
    }


    static void debug( const std::string& text );

    template< typename... Args >
    static void debug( const std::string& text, const Args&... args )
    {
      debug( fmt::format( text, args... ) );
    }


    static void fatal( const std::string& text );

    template< typename... Args >
    static void fatal( const std::string& text, const Args&... args )
    {
      fatal( fmt::format( text, args... ) );
    }


    static void trace( const std::string& text );

    template< typename... Args >
    static void trace( const std::string& text, const Args&... args )
    {
      trace( fmt::format( text, args... ) );
    }
  };
}
