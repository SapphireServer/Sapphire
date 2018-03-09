#ifndef SAPPHIRE_DBWORKER_H
#define SAPPHIRE_DBWORKER_H

#include <atomic>
#include <thread>
#include "Util/LockedWaitQueue.h"
#include <boost/shared_ptr.hpp>

namespace Core
{
namespace Db
{
   class DbConnection;
   class Operation;

   class DbWorker
   {
   public:
      DbWorker( LockedWaitQueue< boost::shared_ptr< Operation > >* newQueue, DbConnection* connection );
      ~DbWorker();

   private:
      LockedWaitQueue< boost::shared_ptr< Operation > >* m_queue;
      DbConnection* m_pConn;

      void workerThread();
      std::thread m_workerThread;

      std::atomic< bool > m_cancelationToken;

      DbWorker( DbWorker const& right ) = delete;
      DbWorker& operator=( DbWorker const& right ) = delete;
   };
}
}



#endif //SAPPHIRE_DBWORKER_H
