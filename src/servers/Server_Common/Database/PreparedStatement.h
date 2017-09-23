#ifndef SAPPHIRE_PREPAREDSTATEMENT_H
#define SAPPHIRE_PREPAREDSTATEMENT_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "Statement.h"
#include <mysql.h>

namespace Core
{
   namespace Db
   {

      class ParamBind;
      class ResultBind;

      class PreparedStatement : public Statement
      {
      protected:
         MYSQL_STMT * m_pStmt;
         Connection * m_pConnection;
         boost::scoped_ptr< ParamBind > m_pParamBind;
         uint32_t m_paramCount;

         int32_t resultSetConcurrency;
         int32_t resultSetType;

         //boost::scoped_ptr< MySQL_PreparedResultSetMetaData > res_meta;
         //boost::scoped_ptr< MySQL_ParameterMetaData > param_meta;

         boost::shared_ptr< ResultBind > m_pResultBind;

         unsigned int warningsCount;

         virtual void doQuery();
         virtual void closeIntern();

         bool sendLongDataBeforeParamBind();

      public:
         PreparedStatement( MYSQL_STMT* pStmt, Connection* pConn );
         virtual ~PreparedStatement();

         Connection* getConnection() override;
         MYSQL_STMT* getRawStmt();

         uint32_t errNo() override;

         uint32_t getWarningCount() override;

         uint64_t getUpdateCount() override;

         void clearParameters();

         bool execute();
         bool execute( const std::string& sql );

         ResultSet* executeQuery();
         ResultSet* executeQuery( const std::string& sql );

         bool getMoreResults();

         ResultSet* getResultSet();

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
}

#endif //SAPPHIRE_PREPAREDSTATEMENT_H
