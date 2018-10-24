#ifndef SAPPHIRE_DB_PREPAREDSTATEMENT_H
#define SAPPHIRE_DB_PREPAREDSTATEMENT_H

#include <memory>
#include "Statement.h"
#include <mysql.h>

namespace Mysql
{

      class ParamBind;
      class ResultBind;

      class PreparedStatement : public Statement
      {
      protected:
         MYSQL_STMT * m_pStmt;
         std::shared_ptr< Connection > m_pConnection;
         std::unique_ptr< ParamBind > m_pParamBind;
         uint32_t m_paramCount;

         int32_t resultSetConcurrency;
         int32_t resultSetType;

         std::shared_ptr< ResultBind > m_pResultBind;

         unsigned int warningsCount;

         virtual void doQuery();
         virtual void closeIntern();

         bool sendLongDataBeforeParamBind();

      public:
         PreparedStatement( MYSQL_STMT* pStmt, std::shared_ptr< Connection > pConn );
         virtual ~PreparedStatement();

         std::shared_ptr< Connection > getConnection() override;
         MYSQL_STMT* getRawStmt();

         uint32_t errNo() override;

         uint32_t getWarningCount() override;

         uint64_t getUpdateCount() override;

         void clearParameters();

         bool execute();
         bool execute( const std::string& sql ) override;

         std::shared_ptr< ResultSet > executeQuery();
         std::shared_ptr< ResultSet > executeQuery( const std::string& sql ) override;

         bool getMoreResults();

         std::shared_ptr< ResultSet > getResultSet() override;

         void setBlob( uint32_t parameterIndex, std::istream * blob );

         void setBoolean( uint32_t parameterIndex, bool value );

         void setBigInt( uint32_t parameterIndex, const std::string& value );

         void setDateTime( uint32_t parameterIndex, const std::string& value );

         void setDouble( uint32_t parameterIndex, double value );

         void setInt( uint32_t parameterIndex, int32_t value );

         void setUInt( uint32_t parameterIndex, uint32_t value );

         void setInt64( uint32_t parameterIndex, int64_t value );

         void setUInt64( uint32_t parameterIndex, uint64_t value );

         void setNull( uint32_t parameterIndex, int sqlType );

         void setString( uint32_t parameterIndex, const std::string& value );

      private:
         PreparedStatement( const PreparedStatement& );
         void operator=( PreparedStatement& );
      };
}

#endif //SAPPHIRE_DB_PREPAREDSTATEMENT_H
