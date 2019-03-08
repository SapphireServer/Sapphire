#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <asio.hpp>
#include <atomic>
#include "Forwards.h"
#include <condition_variable>
#include <deque>
#include <memory>
#include <functional>
#include <mutex>
#include <typeinfo>
#include <vector>


namespace Sapphire::Network
{

  class Connection;

  class Acceptor : public std::enable_shared_from_this< Acceptor >
  {
    friend class Hive;

  private:
    HivePtr m_hive;
    asio::ip::tcp::acceptor m_acceptor;
    asio::strand m_io_strand;
    std::atomic< uint32_t > m_error_state;

  private:
    Acceptor( const Acceptor& rhs );

    Acceptor& operator=( const Acceptor& rhs );

    void startError( const asio::error_code& error );

    void dispatchAccept( ConnectionPtr connection );

    void handleAccept( const asio::error_code& error, ConnectionPtr connection );

  private:
    // Called when a connection has connected to the server. This function
    // should return true to invoke the connection's OnAccept function if the
    // connection will be kept. If the connection will not be kept, the
    // connection's Disconnect function should be called and the function
    // should return false.
    virtual bool onAccept( ConnectionPtr connection, const std::string& host, uint16_t port );

    // Called when an error is encountered. Most typically, this is when the
    // acceptor is being closed via the Stop function or if the Listen is
    // called on an address that is not available.
    virtual void onError( const asio::error_code& error );

  public:
    Acceptor( HivePtr hive );

    virtual ~Acceptor();

    // Returns the Hive object.
    HivePtr getHive();

    // Returns the acceptor object.
    asio::ip::tcp::acceptor& getAcceptor();

    // Returns the strand object.
    asio::strand& getStrand();

    // Returns true if this object has an error associated with it.
    bool hasError();

  public:
    // Begin listening on the specific network interface.
    void listen( const std::string& host, const uint16_t& port );

    // Posts the connection to the listening interface. The next client that
    // connections will be given this connection. If multiple calls to Accept
    // are called at a time, then they are accepted in a FIFO order.
    void accept( ConnectionPtr connection );

    // Stop the Acceptor from listening.
    void stop();
  };

}
#endif
