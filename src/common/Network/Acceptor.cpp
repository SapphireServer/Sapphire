#include "Hive.h"
#include "Acceptor.h"
#include "Connection.h"


using namespace Sapphire;

Network::Acceptor::Acceptor( HivePtr hive ) :
  m_hive( hive ),
  m_acceptor( hive->getService() ),
  m_io_strand( hive->getService() ),
  m_error_state( 0 )
{
}

Network::Acceptor::~Acceptor()
{
}

bool Network::Acceptor::onAccept( ConnectionPtr connection, const std::string& host, uint16_t port )
{
  return true;
}

void Network::Acceptor::onError( const asio::error_code& error )
{

}

void Network::Acceptor::startError( const asio::error_code& error )
{
  uint32_t v1 = 1;
  uint32_t v2 = 0;
  if( m_error_state.compare_exchange_strong( v1, v2 ) )
  {
    asio::error_code ec;
    m_acceptor.cancel( ec );
    m_acceptor.close( ec );
    onError( error );
  }
}

void Network::Acceptor::dispatchAccept( ConnectionPtr connection )
{
  m_acceptor.async_accept( connection->getSocket(),
                           connection->getStrand().wrap( std::bind( &Acceptor::handleAccept,
                                                                    shared_from_this(),
                                                                    std::placeholders::_1,
                                                                    connection ) ) );
}

void Network::Acceptor::handleAccept( const asio::error_code& error, ConnectionPtr connection )
{
  if( error || hasError() || m_hive->hasStopped() )
  {
    connection->startError( error );
  }
  else
  {
    if( connection->getSocket().is_open() )
    {
      if( onAccept( connection,
                    connection->getSocket().remote_endpoint().address().to_string(),
                    connection->getSocket().remote_endpoint().port() ) )
      {
        connection->onAccept( m_acceptor.local_endpoint().address().to_string(),
                              m_acceptor.local_endpoint().port() );
        connection->recv();
      }
    }
    else
    {
      connection->startError( error );
    }
  }
}

void Network::Acceptor::stop()
{

}

void Network::Acceptor::accept( ConnectionPtr connection )
{
  m_io_strand.post( std::bind( &Acceptor::dispatchAccept, shared_from_this(), connection ) );
}

void Network::Acceptor::listen( const std::string& host, const uint16_t& port )
{
  try
  {
    asio::ip::tcp::resolver resolver( m_hive->getService() );
    asio::ip::tcp::resolver::query query( host, std::to_string( port ) );
    asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );

    m_acceptor.open( endpoint.protocol() );
    m_acceptor.set_option( asio::ip::tcp::acceptor::reuse_address( false ) );
    m_acceptor.bind( endpoint );
    m_acceptor.listen( asio::socket_base::max_connections );
  }
  catch( ... )
  {
    // this should not happen
    assert( true );
  }

}

Network::HivePtr Network::Acceptor::getHive()
{
  return m_hive;
}

asio::ip::tcp::acceptor& Network::Acceptor::getAcceptor()
{
  return m_acceptor;
}

bool Network::Acceptor::hasError()
{
  uint32_t v1 = 1;
  uint32_t v2 = 1;
  return ( m_error_state.compare_exchange_strong( v1, v2 ) );
}