#include <memory>
#include <functional>
#include "Hive.h"

using namespace Sapphire;

//-----------------------------------------------------------------------------

Network::Hive::Hive() :
  m_work_ptr( std::make_shared< asio::io_service::work >( m_io_service ) ),
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
  return m_shutdown.load() != 0;
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
  // Mark shutdown; idempotent
  uint32_t expected = 0;
  if( m_shutdown.compare_exchange_strong( expected, 1 ) )
  {
    // Destroy work to allow io_service::run() to exit when queue is empty
    m_work_ptr.reset();
    // Post a no-op to wake the service if it's blocked
    m_io_service.post( []
    {
    } );
    // Request stop; this will cause run() to return ASAP
    m_io_service.stop();
  }
}

void Network::Hive::reset()
{
  // Only reset if we were stopped
  if( m_shutdown.exchange( 0 ) != 0 )
  {
    m_io_service.reset();
    m_work_ptr = std::make_shared< asio::io_service::work >( m_io_service );
  }
}
