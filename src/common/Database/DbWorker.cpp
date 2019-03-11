#include "DbWorker.h"
#include "Operation.h"
#include "Util/LockedWaitQueue.h"

Sapphire::Db::DbWorker::DbWorker( Sapphire::LockedWaitQueue< std::shared_ptr< Operation > >* newQueue,
                                  DbConnection* pConn )
{
  m_pConn = pConn;
  m_queue = newQueue;
  m_cancelationToken = false;
  m_workerThread = std::thread( &DbWorker::workerThread, this );
}

Sapphire::Db::DbWorker::~DbWorker()
{
  m_cancelationToken = true;
  m_queue->cancel();
  m_workerThread.join();
}

void Sapphire::Db::DbWorker::workerThread()
{
  if( !m_queue )
    return;

  while( true )
  {
    std::shared_ptr< Operation > operation = nullptr;

    m_queue->waitAndPop( operation );

    if( m_cancelationToken || !operation )
      return;

    operation->setConnection( m_pConn );
    operation->call();
  }
}
