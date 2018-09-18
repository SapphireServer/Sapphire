#include "Hive.h"
#include "Acceptor.h"
#include "Connection.h"
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/bind.hpp>

namespace Core {
namespace Network {

//-----------------------------------------------------------------------------

Acceptor::Acceptor( HivePtr hive )
  :
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

void Acceptor::OnError( const boost::system::error_code& error )
{

}


void Acceptor::StartError( const boost::system::error_code& error )
{
  if( boost::interprocess::ipcdetail::atomic_cas32( &m_error_state, 1, 0 ) == 0 )
  {
    boost::system::error_code ec;
    m_acceptor.cancel( ec );
    m_acceptor.close( ec );
    OnError( error );
  }
}

void Acceptor::DispatchAccept( ConnectionPtr connection )
{
  m_acceptor.async_accept( connection->GetSocket(),
                           connection->GetStrand().wrap( boost::bind( &Acceptor::HandleAccept,
                                                                      shared_from_this(),
                                                                      _1,
                                                                      connection ) ) );
}

void Acceptor::HandleAccept( const boost::system::error_code& error, ConnectionPtr connection )
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
  m_io_strand.post( boost::bind( &Acceptor::DispatchAccept, shared_from_this(), connection ) );
}

void Acceptor::Listen( const std::string& host, const uint16_t& port )
{
  try
  {
    boost::asio::ip::tcp::resolver resolver( m_hive->GetService() );
    boost::asio::ip::tcp::resolver::query query( host, std::to_string( port ) );
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );

    m_acceptor.open( endpoint.protocol() );
    m_acceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
    m_acceptor.bind( endpoint );
    m_acceptor.listen( boost::asio::socket_base::max_connections );
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

boost::asio::ip::tcp::acceptor& Acceptor::GetAcceptor()
{
  return m_acceptor;
}

bool Acceptor::HasError()
{
  return ( boost::interprocess::ipcdetail::atomic_cas32( &m_error_state, 1, 1 ) == 1 );
}

}
}
