#ifndef SAPPHIRE_DBWORKER_H
#define SAPPHIRE_DBWORKER_H

#include <atomic>
#include <thread>
#include "Util/LockedWaitQueue.h"
#include <memory>

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

#endif //SAPPHIRE_DBWORKER_H
