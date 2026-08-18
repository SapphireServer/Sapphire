#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <cassert>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <future>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <vector>

class ThreadPool
{
public:
  ThreadPool() = default;

  ~ThreadPool()
  {
    shutdown();
  }

  void addWorkers( unsigned int num )
  {
    std::unique_lock lock( m_mutex );

    if( !m_runFlag )
      throw std::runtime_error( "Cannot restart stopped ThreadPool" );

    if( num == 0 )
    {
      const unsigned int hc = std::thread::hardware_concurrency();
      num = hc > 1 ? hc - 1 : 1;
    }

    for( unsigned int i = 0; i < num; ++i )
    {
      m_workers.push_back( std::async( std::launch::async, [ this ] { run(); } ) );
    }
  }

  template< class Func, class Ret = std::invoke_result_t< std::decay_t< Func >& > >
  std::future< Ret > queue( Func&& f, bool waitForWorker = false )
  {

    auto task = std::make_shared< std::packaged_task< Ret() > >( std::forward< Func >( f ) );

    auto result = task->get_future();

    {
      std::unique_lock lock( m_mutex );

      if( !m_runFlag )
        throw std::runtime_error( "queue() called on stopped ThreadPool" );

      if( m_workers.empty() )
        throw std::runtime_error( "queue() called with no ThreadPool workers" );

      m_pendingJobs.emplace_back( [ task ]() { ( *task )(); } );

      ++m_outstandingJobs;
    }

    m_cvPending.notify_one();

    if( waitForWorker )
    {
      std::unique_lock lock( m_mutex );

      m_cvWorker.wait( lock, [ & ]() { return m_pendingJobs.size() <= m_workers.size(); } );
    }

    return result;
  }

  void waitForAllTasks()
  {
    std::unique_lock lock( m_mutex );
    m_cvDone.wait( lock, [ & ]() { return m_outstandingJobs == 0; } );
  }

  void cancel()
  {
    bool done = false;
    {
      std::unique_lock lock( m_mutex );

      const std::size_t cancelled = m_pendingJobs.size();
      m_pendingJobs.clear();
      m_outstandingJobs -= cancelled;

      done = ( m_outstandingJobs == 0 );
    }

    if( done )
      m_cvDone.notify_all();

    waitForAllTasks();
  }

  void shutdown()
  {
    {
      std::unique_lock lock( m_mutex );

      m_cvDone.wait( lock, [ & ]() { return m_outstandingJobs == 0; } );
      m_runFlag = false;
    }
    m_cvPending.notify_all();
    m_workers.clear();
  }

  template< typename I1, typename I2, class F >
  void parallelise_loop(
          const I1& startIndex,
          const I2& lastIndex,
          F&& loop,
          bool waitForWorker = false,
          std::uint32_t segments = 0 )
  {
    using T = std::common_type_t< I1, I2 >;

    T start = static_cast< T >( startIndex );
    T end = static_cast< T >( lastIndex );

    if( start == end )
      return;

    if( start > end )
      std::swap( start, end );

    if( segments == 0 )
    {
      std::unique_lock lock( m_mutex );
      segments = static_cast< std::uint32_t >( m_workers.size() );
    }

    if( segments == 0 )
      throw std::runtime_error( "parallelise_loop() called with no workers" );

    const T count = end - start;
    T blocksize = count / static_cast< T >( segments );

    if( blocksize == 0 )
    {
      segments = static_cast< uint32_t >( count > 1 ? count : 1 );

      blocksize = 1;
    }

    for( uint32_t i = 0; i < segments; ++i )
    {
      const T loopStart = start + static_cast< T >( i ) * blocksize;
      const T loopEnd = i == segments - 1 ? end : start + static_cast< T >( i + 1 ) * blocksize;

      queue( [ loopStart, loopEnd, loop ]() {
                loop( loopStart, loopEnd );
      }, waitForWorker );
    }
  }

private:
  void run()
  {
    while( 1 )
    {
      std::function< void() > func;
      {
        std::unique_lock lock( m_mutex );
        m_cvPending.wait( lock, [ & ]() { return !m_runFlag || !m_pendingJobs.empty(); } );

        if( !m_runFlag && m_pendingJobs.empty() )
        {
          return;
        }

        func = std::move( m_pendingJobs.front() );
        m_pendingJobs.pop_front();
      }

      m_cvWorker.notify_all();

      func();

      bool done = false;

      {
        std::unique_lock lock( m_mutex );
        --m_outstandingJobs;
        done = ( m_outstandingJobs == 0 );
      }

      if( done )
        m_cvDone.notify_all();
    }
  }

private:
  bool m_runFlag = true;

  std::size_t m_outstandingJobs = 0;

  std::mutex m_mutex;

  std::condition_variable m_cvPending;
  std::condition_variable m_cvWorker;
  std::condition_variable m_cvDone;

  std::deque< std::function< void() > > m_pendingJobs;

  std::vector< std::future< void > > m_workers;
};

#endif