#include "Connection.h"
#include "Hive.h"
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/bind.hpp>

namespace Core {
   namespace Network {
      //-----------------------------------------------------------------------------

      Connection::Connection( HivePtr hive )
         : m_hive( hive ), 
         m_socket( hive->GetService() ), 
         m_io_strand(  hive->GetService() ), 
         m_receive_buffer_size( 32000 ), 
         m_error_state( 0 )
      {
      }

      Connection::~Connection()
      {
      }

      void Connection::Bind( const std::string & ip, uint16_t port )
      {
         boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string( ip ), port );
         m_socket.open( endpoint.protocol() );
         m_socket.set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
         m_socket.bind( endpoint );
      }

      void Connection::StartSend()
      {
         if( !m_pending_sends.empty() )
         {
            boost::asio::async_write( m_socket, 
               boost::asio::buffer(  m_pending_sends.front() ),
               m_io_strand.wrap( boost::bind(  &Connection::HandleSend, 
               shared_from_this(), 
               boost::asio::placeholders::error, 
               m_pending_sends.begin() ) ) );
         }
      }

      void Connection::StartRecv( int32_t total_bytes )
      {
         if( total_bytes > 0 )
         {
            m_recv_buffer.resize( total_bytes );
            boost::asio::async_read( m_socket, 
               boost::asio::buffer(  m_recv_buffer ), 
               m_io_strand.wrap( boost::bind(  &Connection::HandleRecv,
               shared_from_this(), 
               _1, 
               _2 ) ) );
         }
         else
         {
            m_recv_buffer.resize( m_receive_buffer_size );
            m_socket.async_read_some( boost::asio::buffer( m_recv_buffer ),  
               m_io_strand.wrap( boost::bind( &Connection::HandleRecv,
               shared_from_this(),
               _1,
               _2 ) ) );
         }
      }

      void Connection::StartError( const boost::system::error_code & error )
      {
         if( boost::interprocess::ipcdetail::atomic_cas32( &m_error_state, 1, 0 ) == 0 )
         {
            boost::system::error_code ec;
            m_socket.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
            m_socket.close( ec );
            OnError( error );
         }
      }

      void Connection::HandleConnect( const boost::system::error_code & error )
      {
         if( error || HasError() || m_hive->HasStopped() )
         {
            StartError( error );
         }
         else
         {
            if( m_socket.is_open() )
            {
               OnConnect( m_socket.remote_endpoint().address().to_string(), m_socket.remote_endpoint().port() );
               Recv();
            }
            else
            {
               StartError( error );
            }
         }
      }

      void Connection::HandleSend( const boost::system::error_code &  error, std::list< std::vector< uint8_t > >::iterator itr )
      {
         if( error || HasError() || m_hive->HasStopped() )
         {
            StartError( error );
         }
         else
         {
            OnSend( *itr );
            m_pending_sends.erase( itr );
            StartSend();
         }
      }

      void Connection::HandleRecv( const boost::system::error_code & error, int32_t actual_bytes )
      {
         if( error || HasError() || m_hive->HasStopped() )
         {
            StartError( error );
         }
         else
         {
            m_recv_buffer.resize( actual_bytes );
            OnRecv( m_recv_buffer );
            Recv();
            m_pending_recvs.pop_front();
            if( !m_pending_recvs.empty() )
            {
               StartRecv( m_pending_recvs.front() );
            }
         }
      }

      void Connection::DispatchSend( std::vector< uint8_t > buffer )
      {
         bool should_start_send = m_pending_sends.empty();
         m_pending_sends.push_back( buffer );
         if( should_start_send )
         {
            StartSend();
         }
      }

      void Connection::DispatchRecv( int32_t total_bytes )
      {
         bool should_start_receive = m_pending_recvs.empty();
         m_pending_recvs.push_back( total_bytes );
         if( should_start_receive )
         {
            StartRecv( total_bytes );
         }
      }


      void Connection::Connect( const std::string & host, uint16_t port)
      {
         boost::asio::ip::tcp::resolver resolver( m_hive->GetService() );
         boost::asio::ip::tcp::resolver::query query( host, std::to_string( port ) );
         boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
         m_socket.async_connect( *iterator, m_io_strand.wrap( boost::bind(  &Connection::HandleConnect, shared_from_this(), _1 ) ) );

      }

      void Connection::Disconnect()
      {
         OnDisconnect();
         m_socket.close();
      }

      void Connection::Recv( int32_t total_bytes )
      {
         m_io_strand.post( boost::bind( &Connection::DispatchRecv, shared_from_this(), total_bytes ) );
      }

      void Connection::Send( const std::vector< uint8_t > & buffer )
      {
         m_io_strand.post( boost::bind( &Connection::DispatchSend, shared_from_this(), buffer ) );
      }

      boost::asio::ip::tcp::socket & Connection::GetSocket()
      {
         return m_socket;
      }

      boost::asio::strand & Connection::GetStrand()
      {
         return m_io_strand;
      }

      HivePtr Connection::GetHive()
      {
         return m_hive;
      }

      void Connection::SetReceiveBufferSize( int32_t size )
      {
         m_receive_buffer_size = size;
      }

      int32_t Connection::GetReceiveBufferSize() const
      {
         return m_receive_buffer_size;
      }

      bool Connection::HasError()
      {
         return ( boost::interprocess::ipcdetail::atomic_cas32( &m_error_state, 1, 1 ) == 1 );
      }


   }
}
//-----------------------------------------------------------------------------