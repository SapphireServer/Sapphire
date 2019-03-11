#ifndef SAPPHIRE_STATEMENTTASK_H
#define SAPPHIRE_STATEMENTTASK_H

#include <string>
#include "Operation.h"
#include <memory>

namespace Sapphire::Db
{
  class PreparedStatement;

  class StatementTask : public Operation
  {
  public:

    StatementTask( const std::string& sql, bool async = false );

    ~StatementTask();

    bool execute() override;

  private:
    std::string m_sql;
    bool m_hasResult;
  };

  class PreparedStatementTask :
    public Operation
  {
  public:
    PreparedStatementTask( std::shared_ptr< PreparedStatement > stmt, bool async = false );

    ~PreparedStatementTask();

    bool execute() override;

  protected:
    std::shared_ptr< PreparedStatement > m_stmt;
    bool m_hasResult;
  };

}


#endif //SAPPHIRE_STATEMENTTASK_H
