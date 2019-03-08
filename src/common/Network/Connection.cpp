#include "Connection.h"
#include "Hive.h"
#include <functional>
#include "Framework.h"

namespace Sapphire::Network 
{
//-----------------------------------------------------------------------------

Connection::Connection( HivePtr hive, FrameworkPtr pFw ) :
  m_hive( hive ),
  m_socket( hive->getService() ),
  m_io_strand( hive->getService() ),
  m_receive_buffer_size( 32000 ),
  m_error_state( 0 ),
  m_pFw( pFw )
{
}

Connection::~Connection()
{
}

void Connection::bind( const std::string& ip, uint16_t port )
{
  asio::ip::tcp::endpoint endpoint( asio::ip::address::from_string( ip ), port );
  m_socket.open( endpoint.protocol() );
  m_socket.set_option( asio::ip::tcp::acceptor::reuse_address( false ) );
  m_socket.bind( endpoint );
}

void Connection::startSend()
{
  if( !m_pending_sends.empty() )
  {
    asio::async_write( m_socket,
                       asio::buffer( m_pending_sends.front() ),
                       m_io_strand.wrap( std::bind( &Connection::handleSend,
                                                    shared_from_this(),
                                                    std::placeholders::_1,
                                                    m_pending_sends.begin() ) ) );
  }
}

void Connection::startRecv( int32_t total_bytes )
{
  if( total_bytes > 0 )
  {
    m_recv_buffer.resize( total_bytes );
    asio::async_read( m_socket,
                      asio::buffer( m_recv_buffer ),
                      m_io_strand.wrap( std::bind( &Connection::handleRecv,
                                                   shared_from_this(),
                                                   std::placeholders::_1,
                                                   std::placeholders::_2 ) ) );
  }
  else
  {
    m_recv_buffer.resize( m_receive_buffer_size );
    m_socket.async_read_some( asio::buffer( m_recv_buffer ),
                              m_io_strand.wrap( std::bind( &Connection::handleRecv,
                                                           shared_from_this(),
                                                           std::placeholders::_1,
                                                           std::placeholders::_2 ) ) );
  }
}

void Connection::startError( const asio::error_code& error )
{
  uint32_t v1 = 1;
  uint32_t v2 = 0;
  if( !m_error_state.compare_exchange_strong( v1, v2 ) )
  {
    asio::error_code ec;
    m_socket.shutdown( asio::ip::tcp::socket::shutdown_both, ec );
    m_socket.close( ec );
    onError( error );
  }
}

void Connection::handleConnect( const asio::error_code& error )
{
  if( error || hasError() || m_hive->hasStopped() )
  {
    startError( error );
  }
  else
  {
    if( m_socket.is_open() )
    {
      onConnect( m_socket.remote_endpoint().address().to_string(), m_socket.remote_endpoint().port() );
      recv();
    }
    else
    {
      startError( error );
    }
  }
}

void
Connection::handleSend( const asio::error_code& error, std::list< std::vector< uint8_t > >::iterator itr )
{
  if( error || hasError() || m_hive->hasStopped() )
  {
    startError( error );
  }
  else
  {
    onSend( *itr );
    m_pending_sends.erase( itr );
    startSend();
  }
}

void Connection::handleRecv( const asio::error_code& error, int32_t actual_bytes )
{
  if( error || hasError() || m_hive->hasStopped() )
  {
    startError( error );
  }
  else
  {
    m_recv_buffer.resize( actual_bytes );
    onRecv( m_recv_buffer );
    recv();
    m_pending_recvs.pop_front();
    if( !m_pending_recvs.empty() )
    {
      startRecv( m_pending_recvs.front() );
    }
  }
}

void Connection::dispatchSend( std::vector< uint8_t > buffer )
{
  bool should_start_send = m_pending_sends.empty();
  m_pending_sends.push_back( buffer );
  if( should_start_send )
  {
    startSend();
  }
}

void Connection::dispatchRecv( int32_t total_bytes )
{
  bool should_start_receive = m_pending_recvs.empty();
  m_pending_recvs.push_back( total_bytes );
  if( should_start_receive )
  {
    startRecv( total_bytes );
  }
}


void Connection::connect( const std::string& host, uint16_t port )
{
  asio::ip::tcp::resolver resolver( m_hive->getService() );
  asio::ip::tcp::resolver::query query( host, std::to_string( port ) );
  asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
  m_socket.async_connect( *iterator,
                          m_io_strand.wrap( std::bind( &Connection::handleConnect, shared_from_this(), std::placeholders::_1 ) ) );

}

void Connection::disconnect()
{
  onDisconnect();
  m_socket.close();
}

void Connection::recv( int32_t total_bytes )
{
  m_io_strand.post( std::bind( &Connection::dispatchRecv, shared_from_this(), total_bytes ) );
}

void Connection::send( const std::vector< uint8_t >& buffer )
{
  m_io_strand.post( std::bind( &Connection::dispatchSend, shared_from_this(), buffer ) );
}

asio::ip::tcp::socket& Connection::getSocket()
{
  return m_socket;
}

asio::strand& Connection::getStrand()
{
  return m_io_strand;
}

HivePtr Connection::getHive()
{
  return m_hive;
}

void Connection::setReceiveBufferSize( int32_t size )
{
  m_receive_buffer_size = size;
}

int32_t Connection::getReceiveBufferSize() const
{
  return m_receive_buffer_size;
}

bool Connection::hasError()
{
  uint32_t v1 = 1;
  uint32_t v2 = 1;
  return ( m_error_state.compare_exchange_strong( v1, v2 ) );
}
}
