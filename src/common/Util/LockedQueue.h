#pragma once

#include <memory>
#include <mutex>
#include <queue>
#include <utility>

namespace Sapphire::Common::Util
{
  // The LockedQueue class template is a thread-safe wrapper around std::queue.
  // It ensures that only one thread can access the underlying queue at a time
  // by using a std::mutex for synchronization.
  template< class T >
  class LockedQueue
  {
  public:
    LockedQueue() = default;
    ~LockedQueue() = default;

    // Returns the size of the queue in a thread-safe manner.
    // Locks the mutex before accessing the queue and unlocks it after
    // the operation is complete.
    std::size_t size() const;

    // Removes the front element from the queue and returns it
    // in a thread-safe manner. If the queue is empty, it returns
    // a default-constructed object of type T.
    // Locks the mutex before accessing the queue and unlocks it after
    // the operation is complete.
    T pop();

    // Adds an object to the end of the queue, using a const reference.
    // The object is copied into the queue in a thread-safe manner.
    // Locks the mutex before accessing the queue and unlocks it after
    // the operation is complete.
    void push( const T& object );

    // Adds an object to the end of the queue, using an rvalue reference.
    // The object is moved into the queue in a thread-safe manner.
    // Locks the mutex before accessing the queue and unlocks it after
    // the operation is complete.
    void push( T&& object );

  protected:
    std::queue< T > m_queue;
    mutable std::mutex m_mutex;// Make mutex mutable to be used in const member functions
  };

  template< class T >
  std::size_t LockedQueue< T >::size() const
  {
    std::lock_guard< std::mutex > lock( m_mutex );
    return m_queue.size();
  }

  template< class T >
  T LockedQueue< T >::pop()
  {
    std::lock_guard< std::mutex > lock( m_mutex );

    if( m_queue.empty() )
    {
      return T();
    }

    T result = std::move( m_queue.front() );
    m_queue.pop();

    return result;
  }

  template< class T >
  void LockedQueue< T >::push( const T& object )
  {
    std::lock_guard< std::mutex > lock( m_mutex );
    m_queue.push( object );
  }

  template< class T >
  void LockedQueue< T >::push( T&& object )
  {
    std::lock_guard< std::mutex > lock( m_mutex );
    m_queue.emplace( std::forward< T >( object ) );
  }

}// namespace Sapphire::Common::Util