#ifndef SAPPHIRE_STATEMENTTASK_H
#define SAPPHIRE_STATEMENTTASK_H

#include <string>
#include "Operation.h"
#include <memory>

namespace Sapphire::Db
{
  class PreparedStatement;

  class StatementTask :
    public Operation
  {
  public:

    StatementTask( const std::string& sql, bool async = false );

    ~StatementTask();

    bool execute() override;

    //   QueryResultFuture getFuture() const
    //   {
    //      return m_result->get_future();
    //   }

  private:
    std::string m_sql;
    bool m_hasResult;
  //      QueryResultPromise *m_result;
  };

  class PreparedStatementTask :
    public Operation
  {
  public:
    PreparedStatementTask( std::shared_ptr< PreparedStatement > stmt, bool async = false );

    ~PreparedStatementTask();

    bool execute() override;
    //PreparedQueryResultFuture getFuture() { return m_result->get_future(); }

  protected:
    std::shared_ptr< PreparedStatement > m_stmt;
    bool m_hasResult;
    //PreparedQueryResultPromise* m_result;
  };

}


#endif //SAPPHIRE_STATEMENTTASK_H
