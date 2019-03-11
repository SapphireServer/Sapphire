#ifndef CONNECTION_H_
#define CONNECTION_H_

//-----------------------------------------------------------------------------

#include <asio.hpp>
#include <vector>
#include <list>
#include <atomic>

#include "Forwards.h"
#include "Acceptor.h"
#include <memory>

namespace Sapphire
{
  class Framework;
  using FrameworkPtr = std::shared_ptr< Framework >;
}

namespace Sapphire::Network
{

  class Hive;
  class Acceptor;
  class Connection;

  //-----------------------------------------------------------------------------

  class Connection : public std::enable_shared_from_this< Connection >
  {
    friend class Acceptor;
    friend class Hive;

  protected:
    HivePtr m_hive;
    asio::ip::tcp::socket m_socket;
    asio::strand m_io_strand;
    std::vector< uint8_t > m_recv_buffer;
    std::list< int32_t > m_pending_recvs;
    std::list< std::vector< uint8_t > > m_pending_sends;
    int32_t m_receive_buffer_size;
    std::atomic< uint32_t > m_error_state;
    Sapphire::FrameworkPtr m_pFw;

    Connection( HivePtr hive, FrameworkPtr pFw );

    virtual ~Connection();

  private:
    Connection( const Connection& rhs );

    Connection& operator=( const Connection& rhs );

    void startSend();

    void startRecv( int32_t total_bytes );

    void startError( const asio::error_code& error );

    void dispatchSend( std::vector< uint8_t > buffer );

    void dispatchRecv( int32_t total_bytes );

    void handleConnect( const asio::error_code& error );

    void handleSend( const asio::error_code& error, std::list< std::vector< uint8_t > >::iterator itr );

    void handleRecv( const asio::error_code& error, int32_t actual_bytes );


  private:
    // Called when the connection has successfully connected to the local host.
    virtual void onAccept( const std::string& host, uint16_t port )
    {
    };

    // Called when the connection has successfully connected to the remote host.
    virtual void onConnect( const std::string& host, uint16_t port )
    {
    };

    // Called when data has been sent by the connection.
    virtual void onSend( const std::vector< uint8_t >& buffer )
    {
    };

    // Called when data has been received by the connection.
    virtual void onRecv( std::vector< uint8_t >& buffer )
    {
    };

    // Called when an error is encountered.
    virtual void onError( const asio::error_code& error )
    {
    };

    // Called when the connection has been disconnected
    virtual void onDisconnect()
    {
    };

  public:
    // Returns the Hive object.
    HivePtr getHive();

    // Returns the socket object.
    asio::ip::tcp::socket& getSocket();

    // Returns the strand object.
    asio::strand& getStrand();

    // Sets the application specific receive buffer size used. For stream
    // based protocols such as HTTP, you want this to be pretty large, like
    // 64kb. For packet based protocols, then it will be much smaller,
    // usually 512b - 8kb depending on the protocol. The default value is
    // 4kb.
    void setReceiveBufferSize( int32_t size );

    // Returns the size of the receive buffer size of the current object.
    int32_t getReceiveBufferSize() const;

    // Returns true if this object has an error associated with it.
    bool hasError();

    // Binds the socket to the specified interface.
    void bind( const std::string& ip, uint16_t port );

    // Starts an a/synchronous connect.
    void connect( const std::string& host, uint16_t port );

    // Posts data to be sent to the connection.
    void send( const std::vector< uint8_t >& buffer );

    // Posts a recv for the connection to process. If total_bytes is 0, then
    // as many bytes as possible up to GetReceiveBufferSize() will be
    // waited for. If Recv is not 0, then the connection will wait for exactly
    // total_bytes before invoking OnRecv.
    void recv( int32_t total_bytes = 0 );

    // Posts an asynchronous disconnect event for the object to process.
    void disconnect();
  };

  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------

  template< class T >
  std::shared_ptr< T > addServerToHive( const std::string& listenIp, uint32_t port, HivePtr pHive, FrameworkPtr pFw )
  {
    try
    {
      AcceptorPtr acceptor( new Acceptor( pHive ) );
      acceptor->listen( listenIp, port );
      std::shared_ptr< T > connection( new T( pHive, acceptor, pFw ) );
      acceptor->accept( connection );
      return connection;
    }
    catch( std::runtime_error e )
    {
      throw;
    }
  }

}
#endif
