#ifndef SAPPHIRE_STATEMENTBASE_H
#define SAPPHIRE_STATEMENTBASE_H

#include <string>

namespace Mysql
{
   class Connection;
   class ResultSet;

   class StatementBase
   {
   public:
      virtual ~StatementBase() {};

      virtual Connection* getConnection() = 0;

      virtual bool execute( const std::string& sql ) = 0;

      virtual ResultSet* executeQuery( const std::string& sql ) = 0;

      virtual ResultSet* getResultSet() = 0;

      virtual uint64_t getUpdateCount() = 0;

      virtual uint32_t getWarningCount() = 0;

      virtual uint32_t errNo() = 0;
   };
}

#endif //SAPPHIRE_STATEMENTBASE_H
