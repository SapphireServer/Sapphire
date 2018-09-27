#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "Forwards.h"

namespace Core {
namespace Network {

class Connection;

class Acceptor :
  public boost::enable_shared_from_this< Acceptor >
{
  friend class Hive;

private:
  HivePtr m_hive;
  boost::asio::ip::tcp::acceptor m_acceptor;
  boost::asio::strand m_io_strand;
  volatile uint32_t m_error_state;

private:
  Acceptor( const Acceptor& rhs );

  Acceptor& operator=( const Acceptor& rhs );

  void StartError( const boost::system::error_code& error );

  void DispatchAccept( ConnectionPtr connection );

  void HandleAccept( const boost::system::error_code& error, ConnectionPtr connection );

private:
  // Called when a connection has connected to the server. This function
  // should return true to invoke the connection's OnAccept function if the
  // connection will be kept. If the connection will not be kept, the
  // connection's Disconnect function should be called and the function
  // should return false.
  virtual bool OnAccept( ConnectionPtr connection, const std::string& host, uint16_t port );

  // Called when an error is encountered. Most typically, this is when the
  // acceptor is being closed via the Stop function or if the Listen is
  // called on an address that is not available.
  virtual void OnError( const boost::system::error_code& error );

public:
  Acceptor( HivePtr hive );

  virtual ~Acceptor();

  // Returns the Hive object.
  HivePtr GetHive();

  // Returns the acceptor object.
  boost::asio::ip::tcp::acceptor& GetAcceptor();

  // Returns the strand object.
  boost::asio::strand& GetStrand();

  // Returns true if this object has an error associated with it.
  bool HasError();

public:
  // Begin listening on the specific network interface.
  void Listen( const std::string& host, const uint16_t& port );

  // Posts the connection to the listening interface. The next client that
  // connections will be given this connection. If multiple calls to Accept
  // are called at a time, then they are accepted in a FIFO order.
  void Accept( ConnectionPtr connection );

  // Stop the Acceptor from listening.
  void Stop();
};

}
}
#endif
