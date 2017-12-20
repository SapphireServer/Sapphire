#include "StatementTask.h"
#include <string.h>
#include "Operation.h"
#include "DbConnection.h"
#include "PreparedStatement.h"

Core::Db::StatementTask::StatementTask( const std::string &sql, bool async )
{
   m_sql = sql;
   m_hasResult = async; // If the operation is async, then there's a result
   //if (async)
   //   m_result = new QueryResultPromise();
}

Core::Db::StatementTask::~StatementTask()
{
   //if( m_hasResult && m_result != nullptr)
   //   delete m_result;
}

bool Core::Db::StatementTask::execute()
{
   if( m_hasResult )
   {
      /*ResultSet* result = m_conn->Query(m_sql);
      if (!result || !result->GetRowCount() || !result->NextRow())
      {
         delete result;
         m_result->set_value(QueryResult(NULL));
         return false;
      }

      m_result->set_value(QueryResult(result));
      return true;*/
   }

   return m_pConn->execute( m_sql );
}



Core::Db::PreparedStatementTask::PreparedStatementTask( boost::shared_ptr< Core::Db::PreparedStatement > stmt, bool async ) :
        m_stmt(stmt)
        //, m_result(nullptr)
{
   m_hasResult = async; // If the operation is async, then there's a result
}

Core::Db::PreparedStatementTask::~PreparedStatementTask()
{
   //if (m_has_result && m_result != nullptr)
   //   delete m_result;
}

bool Core::Db::PreparedStatementTask::execute()
{
   //if (m_has_result)
   //{
   //   PreparedResultSet* result = m_conn->Query(m_stmt);
   //   if (!result || !result->GetRowCount())
   //   {
   //      delete result;
   //      m_result->set_value(PreparedQueryResult(NULL));
   //      return false;
   //   }
   //   m_result->set_value(PreparedQueryResult(result));
   //   return true;
   //}

   return m_pConn->execute( m_stmt );
}
