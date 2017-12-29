#ifndef SAPPHIRE_PREPAREDSTATEMENT_H
#define SAPPHIRE_PREPAREDSTATEMENT_H
#include <stdint.h>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "Operation.h"

namespace Mysql
{
   class PreparedStatement;
}

namespace Core
{
namespace Db
{
   union PreparedStatementDataUnion
   {
      bool boolean;
      uint32_t ui32;
      int32_t i32;
      uint64_t ui64;
      int64_t i64;
      double d;
   };

   enum PreparedStatementValueType
   {
      TYPE_BOOL,
      TYPE_UI,
      TYPE_UI64,
      TYPE_I,
      TYPE_I64,
      TYPE_DOUBLE,
      TYPE_STRING,
      TYPE_BINARY,
      TYPE_NULL
   };

   struct PreparedStatementData
   {
      PreparedStatementDataUnion data;
      PreparedStatementValueType type;
      std::vector< uint8_t > binary;
   };

   class PreparedStatement
   {
   public:
      explicit PreparedStatement( uint32_t index );
      ~PreparedStatement();

      void setBool( uint8_t index, bool value );
      void setUInt( uint8_t index, uint32_t value );
      void setUInt64( uint8_t index, uint64_t value );
      void setInt( uint8_t index, int32_t value );
      void setInt64( uint8_t index, int64_t value );
      void setDouble( uint8_t index, double value );
      void setString( uint8_t index, const std::string& value );
      void setBinary( uint8_t index, const std::vector< uint8_t >& value );
      void setNull( uint8_t index );

      uint32_t getIndex() const;
      void setMysqlPS( boost::shared_ptr< Mysql::PreparedStatement > pStmt );

      void bindParameters();

   protected:
      boost::shared_ptr< Mysql::PreparedStatement > m_stmt;
      uint32_t m_index;
      std::vector< PreparedStatementData > m_statementData;

      PreparedStatement( PreparedStatement const& right ) = delete;
      PreparedStatement& operator=( PreparedStatement const& right ) = delete;
   };


}
}



#endif //SAPPHIRE_PREPAREDSTATEMENT_H
