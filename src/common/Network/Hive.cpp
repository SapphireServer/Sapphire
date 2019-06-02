#include <memory>
#include <functional>
#include "Hive.h"

using namespace Sapphire;

//-----------------------------------------------------------------------------

Network::Hive::Hive() :
  m_work_ptr( new asio::io_service::work( m_io_service ) ),
  m_shutdown( 0 )
{
}

Network::Hive::~Hive()
{
}

asio::io_service& Network::Hive::getService()
{
  return m_io_service;
}

bool Network::Hive::hasStopped()
{
  uint32_t v1 = 1;
  uint32_t v2 = 1;
  return m_shutdown.compare_exchange_strong( v1, v2 );
}

void Network::Hive::poll()
{
  m_io_service.poll();
}

void Network::Hive::run()
{
  m_io_service.run();
}

void Network::Hive::stop()
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

void Network::Hive::reset()
{
  uint32_t v1 = 0;
  uint32_t v2 = 1;
  if( m_shutdown.compare_exchange_strong( v1, v2 ) )
  {
    m_io_service.reset();
    m_work_ptr.reset( new asio::io_service::work( m_io_service ) );
  }
}
