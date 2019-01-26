#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

// credit to
// https://riptutorial.com/cplusplus/example/15806/create-a-simple-thread-pool

class ThreadPool
{
public:
  ThreadPool()
  {

  }

  ~ThreadPool()
  {
    complete();
  }

  void addWorkers( unsigned int num )
  {

    std::unique_lock lock( m_mutex );
    m_runFlag = true;
    if( num == 0 )
      num = std::thread::hardware_concurrency() - 1;

    for( auto i = 0; i < num; ++i )
    {
      m_workers.push_back( std::async( std::launch::async, [this]{ run(); } ) );
    }
  }

  template< class Func, class Ret = std::result_of_t< Func&() > >
  std::future< Ret > queue( Func&& f )
  {
    std::packaged_task< Ret() > task( std::forward< Func >( f ) );
    auto ret = task.get_future();
    {
      std::unique_lock lock( m_mutex );
      m_pendingJobs.emplace_back( std::move( task ) );
    }
    m_cv.notify_one();
    return ret;
  }

  void cancel()
  {
    {
      std::unique_lock lock( m_mutex );
      m_pendingJobs.clear();
    }
    complete();
  }

  bool complete()
  {
    {
      std::unique_lock lock( m_mutex );
      for( auto&& worker : m_workers )
      {
        m_pendingJobs.push_back( {} );
      }
    }
    m_cv.notify_all();
    m_workers.clear();
    return true;
  }
private:
  void run()
  {
    while( 1 )
    {
      std::packaged_task< void() > func;
      {
        std::unique_lock lock( m_mutex );
        if( m_pendingJobs.empty() )
        {
          m_cv.wait( lock, [&](){ return !m_pendingJobs.empty(); } );
        }
        func = std::move( m_pendingJobs.front() );
        m_pendingJobs.pop_front();
      }
      if( !func.valid() )
      {
        return;
      }
      func();
    }
  }

  bool m_runFlag{ true };
  std::mutex m_mutex;
  std::condition_variable m_cv;
  std::deque< std::packaged_task< void() > > m_pendingJobs;
  std::vector< std::future< void > > m_workers;
};

#endif