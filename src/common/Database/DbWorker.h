#pragma once

#include <atomic>
#include <thread>
#include <memory>

#include "Util/LockedWaitQueue.h"

namespace Sapphire::Db
{
  class DbConnection;
  class Operation;

  class DbWorker
  {
  public:
    DbWorker( Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >* newQueue, DbConnection* connection );

    ~DbWorker();

  private:
    Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >* m_queue;
    DbConnection* m_pConn;

    void workerThread();

    std::thread m_workerThread;

    std::atomic< bool > m_cancelationToken;

    DbWorker( DbWorker const& right ) = delete;

    DbWorker& operator=( DbWorker const& right ) = delete;
  };
}

