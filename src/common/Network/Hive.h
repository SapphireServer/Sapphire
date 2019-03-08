#ifndef HIVE_H_
#define HIVE_H_

#include <asio.hpp>
#include <atomic>
#include <memory>

namespace Sapphire:: Network
{

  class Hive : public std::enable_shared_from_this< Hive >
  {
  private:
    asio::io_service m_io_service;
    std::shared_ptr< asio::io_service::work > m_work_ptr;
    std::atomic< uint32_t > m_shutdown;

  private:
    Hive( const Hive& rhs );

    Hive& operator=( const Hive& rhs );

  public:
    Hive();

    virtual ~Hive();

    // Returns the io_service of this object.
    asio::io_service& getService();

    // Returns true if the Stop function has been called.
    bool hasStopped();

    // Polls the networking subsystem once from the current thread and
    // returns.
    void poll();

    // Runs the networking system on the current thread. This function blocks
    // until the networking system is stopped, so do not call on a single
    // threaded application with no other means of being able to call Stop
    // unless you code in such logic.
    void run();

    // Stops the networking system. All work is finished and no more
    // networking interactions will be possible afterwards until Reset is called.
    void stop();

    // Restarts the networking system after Stop as been called. A new work
    // object is created ad the shutdown flag is cleared.
    void reset();
  };

}
#endif
