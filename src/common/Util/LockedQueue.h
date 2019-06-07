#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <algorithm>
#include <utility>

namespace Sapphire::Common::Util
{

  template< class T >
  class LockedQueue
  {
  public:
    LockedQueue();

    ~LockedQueue();

    T pop();

    //we can pass this in by reference, instead of copying
    void push( const T object );

    //we can pass this in by reference
    //this will push it onto the queue, and swap the object
    // with a default-constructed T at the same time.
    void push_swap( T& object );

    void push_reset( T& object );


    std::size_t size();


  protected:
    std::queue< T > m_queue;
    std::mutex m_mutex;

  };

  template< class T >
  LockedQueue< T >::LockedQueue()
  {

  }

  template< class T >
  std::size_t LockedQueue< T >::size()
  {
    std::lock_guard< std::mutex > lock( m_mutex );
    return m_queue.size();
  }


  template< class T >
  LockedQueue< T >::~LockedQueue()
  {


  }


  template< class T >
  T LockedQueue< T >::pop()
  {
    std::lock_guard< std::mutex > lock( m_mutex );

    if( m_queue.empty() )
    {
      return T();
    }

    T result = m_queue.front();

    m_queue.pop();

    return result;
  }

  template< class T >
  void LockedQueue< T >::push( const T object )
  {
    std::lock_guard< std::mutex > lock( m_mutex );
    m_queue.push( object );
  }

  template< class T >
  void LockedQueue< T >::push_swap( T& object )
  {
    std::lock_guard< std::mutex > lock( m_mutex );

    m_queue.push( object );

    T default_ctored_object = T();
    //this is a special swap that will do a legit naive swap normally,
    // except if there exists a function called T::swap(), which is
    // specialized and possibly faster.
    std::swap( object, default_ctored_object );



    //default_ctored_object is now the value of object, and it will go out
    // of scope here. In the case that T is a shared_ptr of some kind,
    // this will allow that the object on the queue is the *last* shared_ptr
    // in existance by the time this function returns.

  }

  template< class T >
  void LockedQueue< T >::push_reset( T& object )
  {
    std::lock_guard< std::mutex > lock( m_mutex );

    m_queue.push( object );

    T default_ctored_object = T();

    object.reset();

    //default_ctored_object is now the value of object, and it will go out
    // of scope here. In the case that T is a shared_ptr of some kind,
    // this will allow that the object on the queue is the *last* shared_ptr
    // in existance by the time this function returns.

  }

}
