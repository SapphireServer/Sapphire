#ifndef CONNECTION_H_
#define CONNECTION_H_

//-----------------------------------------------------------------------------

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include <list>
#include <boost/cstdint.hpp>

#include "Forwards.h"
#include "Acceptor.h"


namespace Core {
namespace Network {
//-----------------------------------------------------------------------------

class Hive;

class Acceptor;

class Connection;

//-----------------------------------------------------------------------------

class Connection :
  public boost::enable_shared_from_this< Connection >
{
  friend class Acceptor;

  friend class Hive;

protected:
  HivePtr m_hive;
  boost::asio::ip::tcp::socket m_socket;
  boost::asio::strand m_io_strand;
  std::vector< uint8_t > m_recv_buffer;
  std::list< int32_t > m_pending_recvs;
  std::list< std::vector< uint8_t > > m_pending_sends;
  int32_t m_receive_buffer_size;
  volatile uint32_t m_error_state;


  Connection( HivePtr hive );

  virtual ~Connection();

private:
  Connection( const Connection& rhs );

  Connection& operator=( const Connection& rhs );

  void StartSend();

  void StartRecv( int32_t total_bytes );

  void StartError( const boost::system::error_code& error );

  void DispatchSend( std::vector< uint8_t > buffer );

  void DispatchRecv( int32_t total_bytes );

  void HandleConnect( const boost::system::error_code& error );

  void HandleSend( const boost::system::error_code& error, std::list< std::vector< uint8_t > >::iterator itr );

  void HandleRecv( const boost::system::error_code& error, int32_t actual_bytes );


private:
  // Called when the connection has successfully connected to the local host.
  virtual void OnAccept( const std::string& host, uint16_t port )
  {
  };

  // Called when the connection has successfully connected to the remote host.
  virtual void OnConnect( const std::string& host, uint16_t port )
  {
  };

  // Called when data has been sent by the connection.
  virtual void OnSend( const std::vector< uint8_t >& buffer )
  {
  };

  // Called when data has been received by the connection.
  virtual void OnRecv( std::vector< uint8_t >& buffer )
  {
  };

  // Called when an error is encountered.
  virtual void OnError( const boost::system::error_code& error )
  {
  };

  // Called when the connection has been disconnected
  virtual void OnDisconnect()
  {
  };

public:
  // Returns the Hive object.
  HivePtr GetHive();

  // Returns the socket object.
  boost::asio::ip::tcp::socket& GetSocket();

  // Returns the strand object.
  boost::asio::strand& GetStrand();

  // Sets the application specific receive buffer size used. For stream
  // based protocols such as HTTP, you want this to be pretty large, like
  // 64kb. For packet based protocols, then it will be much smaller,
  // usually 512b - 8kb depending on the protocol. The default value is
  // 4kb.
  void SetReceiveBufferSize( int32_t size );

  // Returns the size of the receive buffer size of the current object.
  int32_t GetReceiveBufferSize() const;

  // Returns true if this object has an error associated with it.
  bool HasError();

  // Binds the socket to the specified interface.
  void Bind( const std::string& ip, uint16_t port );

  // Starts an a/synchronous connect.
  void Connect( const std::string& host, uint16_t port );

  // Posts data to be sent to the connection.
  void Send( const std::vector< uint8_t >& buffer );

  // Posts a recv for the connection to process. If total_bytes is 0, then
  // as many bytes as possible up to GetReceiveBufferSize() will be
  // waited for. If Recv is not 0, then the connection will wait for exactly
  // total_bytes before invoking OnRecv.
  void Recv( int32_t total_bytes = 0 );

  // Posts an asynchronous disconnect event for the object to process.
  void Disconnect();
};

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

template< class T >
boost::shared_ptr< T > addServerToHive( const std::string& listenIp, uint32_t port, HivePtr pHive )
{
  try
  {
    AcceptorPtr acceptor( new Acceptor( pHive ) );
    acceptor->Listen( listenIp, port );
    boost::shared_ptr< T > connection( new T( pHive, acceptor ) );
    acceptor->Accept( connection );
    return connection;
  }
  catch( std::runtime_error e )
  {
    throw;
  }
}

}


}
#endif
