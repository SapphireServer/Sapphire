#include <memory>
#include <functional>
#include "Hive.h"

namespace Sapphire::Network
{

//-----------------------------------------------------------------------------

Hive::Hive() :
  m_work_ptr( new asio::io_service::work( m_io_service ) ),
  m_shutdown( 0 )
{
}

Hive::~Hive()
{
}

asio::io_service& Hive::getService()
{
  return m_io_service;
}

bool Hive::hasStopped()
{
  uint32_t v1 = 1;
  uint32_t v2 = 1;
  return m_shutdown.compare_exchange_strong( v1, v2 );
}

void Hive::poll()
{
  m_io_service.poll();
}

void Hive::run()
{
  m_io_service.run();
}

void Hive::stop()
{
  uint32_t v1 = 1;
  uint32_t v2 = 0;
  if( !m_shutdown.compare_exchange_strong( v1, v2 ) )
  {
    m_work_ptr.reset();
    m_io_service.run();
    m_io_service.stop();
  }
}

void Hive::reset()
{
  uint32_t v1 = 0;
  uint32_t v2 = 1;
  if( m_shutdown.compare_exchange_strong( v1, v2 ) )
  {
    m_io_service.reset();
    m_work_ptr.reset( new asio::io_service::work( m_io_service ) );
  }
}

}
