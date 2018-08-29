#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include "Hive.h"

namespace Core {
namespace Network {

//-----------------------------------------------------------------------------

Hive::Hive()
  :
  m_work_ptr( new boost::asio::io_service::work( m_io_service ) ),
  m_shutdown( 0 )
{
}

Hive::~Hive()
{
}

boost::asio::io_service& Hive::GetService()
{
  return m_io_service;
}

bool Hive::HasStopped()
{
  return ( boost::interprocess::ipcdetail::atomic_cas32( &m_shutdown, 1, 1 ) == 1 );
}

void Hive::Poll()
{
  m_io_service.poll();
}

void Hive::Run()
{
  m_io_service.run();
}

void Hive::Stop()
{
  if( boost::interprocess::ipcdetail::atomic_cas32( &m_shutdown, 1, 0 ) == 0 )
  {
    m_work_ptr.reset();
    m_io_service.run();
    m_io_service.stop();
  }
}

void Hive::Reset()
{
  if( boost::interprocess::ipcdetail::atomic_cas32( &m_shutdown, 0, 1 ) == 1 )
  {
    m_io_service.reset();
    m_work_ptr.reset( new boost::asio::io_service::work( m_io_service ) );
  }
}

}
}