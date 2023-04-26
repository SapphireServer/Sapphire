#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <type_traits>
#include <utility>

namespace Sapphire::Common::Util
{
  // The LockedWaitQueue class template is a thread-safe wrapper around std::queue
  // that provides blocking and non-blocking operations for concurrent access.
  // It uses a combination of a std::mutex and a std::condition_variable to
  // synchronize access to the queue and allow waiting for new elements to arrive.
  template< typename T >
  class LockedWaitQueue
  {
  private:
    std::mutex m_queueLock;
    std::queue< T > m_queue;
    std::condition_variable m_condition;
    std::atomic< bool > m_shutdown;

  public:
    LockedWaitQueue< T >() : m_shutdown( false )
    {
    }

    // Adds an element to the end of the queue. The element can be passed as an
    // lvalue or rvalue reference, and it will be either copied or moved into
    // the queue as appropriate. The queue is locked during the push operation,
    // and a waiting thread is notified using the condition variable.
    template< typename U >
    void push( U&& value )
    {
      std::lock_guard< std::mutex > lock( m_queueLock );
      m_queue.push( std::forward< U >( value ) );

      m_condition.notify_one();
    }

    // Returns true if the queue is empty, false otherwise. The queue is locked
    // during the check.
    bool empty()
    {
      std::lock_guard< std::mutex > lock( m_queueLock );

      return m_queue.empty();
    }

    // Tries to remove the front element from the queue and move it into the
    // provided reference. Returns true if an element was successfully popped,
    // or false if the queue was empty or the wait queue was in shutdown state.
    // The queue is locked during the pop operation.
    bool pop( T& value )
    {
      std::lock_guard< std::mutex > lock( m_queueLock );

      if( m_queue.empty() || m_shutdown )
        return false;

      value = std::move( m_queue.front() );

      m_queue.pop();

      return true;
    }

    // Waits for an element to become available in the queue and then removes
    // it and moves it into the provided reference. If the queue is empty and
    // not in shutdown state, the thread will block until an element is added
    // or the wait queue is shut down. The queue is locked during the operation.
    void waitAndPop( T& value )
    {
      std::unique_lock< std::mutex > lock( m_queueLock );

      while( m_queue.empty() && !m_shutdown )
        m_condition.wait( lock );

      if( m_queue.empty() || m_shutdown )
        return;

      value = std::move( m_queue.front() );

      m_queue.pop();
    }

    // Shuts down the wait queue, deleting all elements currently in the queue
    // (if T is a pointer type) and notifying all waiting threads. Any future
    // calls to pop() or waitAndPop() will return immediately with false or
    // without modifying the provided reference, respectively.
    void cancel()
    {
      std::unique_lock< std::mutex > lock( m_queueLock );

      while( !m_queue.empty() )
      {
        T& value = m_queue.front();

        deleteQueuedObject( value );

        m_queue.pop();
      }

      m_shutdown = true;

      m_condition.notify_all();
    }

  private:
    // Helper functions for deleting queued objects depending on whether T is
    // a pointer type or not.
    template< typename E = T >
    typename std::enable_if< std::is_pointer< E >::value >::type deleteQueuedObject( E& obj )
    {
      delete obj;
    }

    template< typename E = T >
    typename std::enable_if< !std::is_pointer< E >::value >::type deleteQueuedObject( E const& )
    {
    }
  };
}// namespace Sapphire::Common::Util
