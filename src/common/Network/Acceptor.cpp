#include "Hive.h"
#include "Acceptor.h"
#include "Connection.h"

namespace Sapphire {
namespace Network {

//-----------------------------------------------------------------------------

Acceptor::Acceptor( HivePtr hive ) :
  m_hive( hive ),
  m_acceptor( hive->GetService() ),
  m_io_strand( hive->GetService() ),
  m_error_state( 0 )
{
}

Acceptor::~Acceptor()
{
}


bool Acceptor::OnAccept( ConnectionPtr connection, const std::string& host, uint16_t port )
{
  return true;
}

void Acceptor::OnError( const asio::error_code& error )
{

}


void Acceptor::StartError( const asio::error_code& error )
{
  uint32_t v1 = 1;
  uint32_t v2 = 0;
  if( m_error_state.compare_exchange_strong( v1, v2 ) )
  {
    asio::error_code ec;
    m_acceptor.cancel( ec );
    m_acceptor.close( ec );
    OnError( error );
  }
}

void Acceptor::DispatchAccept( ConnectionPtr connection )
{
  m_acceptor.async_accept( connection->GetSocket(),
                           connection->GetStrand().wrap( std::bind( &Acceptor::HandleAccept,
                                                                    shared_from_this(),
                                                                    std::placeholders::_1,
                                                                    connection ) ) );
}

void Acceptor::HandleAccept( const asio::error_code& error, ConnectionPtr connection )
{
  if( error || HasError() || m_hive->HasStopped() )
  {
    connection->StartError( error );
  }
  else
  {
    if( connection->GetSocket().is_open() )
    {
      if( OnAccept( connection,
                    connection->GetSocket().remote_endpoint().address().to_string(),
                    connection->GetSocket().remote_endpoint().port() ) )
      {
        connection->OnAccept( m_acceptor.local_endpoint().address().to_string(),
                              m_acceptor.local_endpoint().port() );
        connection->Recv();
      }
    }
    else
    {
      connection->StartError( error );
    }
  }
}

void Acceptor::Stop()
{

}

void Acceptor::Accept( ConnectionPtr connection )
{
  m_io_strand.post( std::bind( &Acceptor::DispatchAccept, shared_from_this(), connection ) );
}

void Acceptor::Listen( const std::string& host, const uint16_t& port )
{
  try
  {
    asio::ip::tcp::resolver resolver( m_hive->GetService() );
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

HivePtr Acceptor::GetHive()
{
  return m_hive;
}

asio::ip::tcp::acceptor& Acceptor::GetAcceptor()
{
  return m_acceptor;
}

bool Acceptor::HasError()
{
  uint32_t v1 = 1;
  uint32_t v2 = 1;
  return ( m_error_state.compare_exchange_strong( v1, v2 ) );
}

}
}
