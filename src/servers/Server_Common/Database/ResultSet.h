#ifndef SAPPHIRE_RESULTSET_H
#define SAPPHIRE_RESULTSET_H

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "ResultSetBase.h"
#include <mysql.h>

namespace Core
{
   namespace Db
   {

      class Statement;
      //class ResultSetMetaData;


      class ResultSet : public ResultSetBase
      {
         MYSQL_ROW m_row;

         uint32_t m_numFields;
         uint64_t m_numRows;
         uint64_t m_rowPosition;

         typedef std::map< std::string, uint32_t > FieldNameIndexMap;

         FieldNameIndexMap	m_fieldNameToIndex;

         mutable bool m_wasNull;

         mutable uint32_t m_lastQueriedColumn;

         Statement* m_pStmt;

         MYSQL_RES* m_pRes;

         //boost::scoped_ptr< MySQL_ResultSetMetaData > rs_meta;

      protected:
         MYSQL_FIELD* getFieldMeta( unsigned int columnIndex ) const;

      public:
         ResultSet( MYSQL_RES* res, Statement* par );

         virtual ~ResultSet();

         uint32_t findColumn( const std::string& columnLabel ) const;

         std::istream * getBlob( uint32_t columnIndex ) const;
         std::istream * getBlob( const std::string& columnLabel ) const;

         bool getBoolean( uint32_t columnIndex ) const;
         bool getBoolean( const std::string& columnLabel ) const;

         long double getDouble( uint32_t columnIndex ) const;
         long double getDouble( const std::string& columnLabel ) const;

         int32_t getInt( uint32_t columnIndex ) const;
         int32_t getInt( const std::string& columnLabel ) const;

         uint32_t getUInt( uint32_t columnIndex ) const;
         uint32_t getUInt( const std::string& columnLabel ) const;

         int64_t getInt64( uint32_t columnIndex ) const;
         int64_t getInt64( const std::string& columnLabel ) const;

         uint64_t getUInt64( uint32_t columnIndex ) const;
         uint64_t getUInt64( const std::string& columnLabel ) const;

         //sql::ResultSetMetaData * getMetaData() const;

         size_t getRow() const;

         const Statement * getStatement() const;

         std::string getString( uint32_t columnIndex ) const;
         std::string getString( const std::string& columnLabel ) const;

         bool isFirst() const;

         bool isLast() const;

         bool isNull( uint32_t columnIndex ) const;

         bool isNull( const std::string& columnLabel ) const;

         bool next();

         size_t rowsCount() const;
      private:
         ResultSet( const ResultSet& );
         void operator=( ResultSet& );
      };

   }
}


#endif //SAPPHIRE_RESULTSET_H
