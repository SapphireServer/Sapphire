#ifndef SAPPHIRE_RESULTSET_H
#define SAPPHIRE_RESULTSET_H

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>

#include "ResultSetBase.h"
#include <mysql.h>

namespace Core
{
   namespace Db
   {

      class Statement;
      //class ResultSetMetaData;


      class ResultSet
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

         virtual uint32_t findColumn( const std::string& columnLabel ) const;

         virtual std::istream * getBlob( uint32_t columnIndex ) const;
         virtual std::istream * getBlob( const std::string& columnLabel ) const;

         virtual std::vector< char > getBlobVector( uint32_t columnIndex ) const;
         virtual std::vector< char > getBlobVector( const std::string& columnLabel ) const;

         virtual bool getBoolean( uint32_t columnIndex ) const;
         virtual bool getBoolean( const std::string& columnLabel ) const;

         virtual long double getDouble( uint32_t columnIndex ) const;
         virtual long double getDouble( const std::string& columnLabel ) const;

         virtual int32_t getInt( uint32_t columnIndex ) const;
         virtual int32_t getInt( const std::string& columnLabel ) const;

         virtual uint32_t getUInt( uint32_t columnIndex ) const;
         virtual uint32_t getUInt( const std::string& columnLabel ) const;

         virtual int64_t getInt64( uint32_t columnIndex ) const;
         virtual int64_t getInt64( const std::string& columnLabel ) const;

         virtual uint64_t getUInt64( uint32_t columnIndex ) const;
         virtual uint64_t getUInt64( const std::string& columnLabel ) const;

         //sql::ResultSetMetaData * getMetaData() const;

         virtual size_t getRow() const;

         virtual const Statement * getStatement() const;

         virtual std::string getString( uint32_t columnIndex ) const;
         virtual std::string getString( const std::string& columnLabel ) const;

         virtual bool isFirst() const;

         virtual bool isLast() const;

         virtual bool isNull( uint32_t columnIndex ) const;

         virtual bool isNull( const std::string& columnLabel ) const;

         virtual bool next();

         size_t rowsCount() const;
      private:
         ResultSet( const ResultSet& );
         void operator=( ResultSet& );
      };

   }
}


#endif //SAPPHIRE_RESULTSET_H
