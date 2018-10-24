#ifndef SAPPHIRE_RESULTSET_H
#define SAPPHIRE_RESULTSET_H

#include <vector>

#include "ResultSetBase.h"
#include <mysql.h>
#include <memory>

namespace Mysql
{
      class Statement;

      class ResultSet
      {
         MYSQL_ROW m_row;

         uint32_t m_numFields;
         uint64_t m_numRows;
         uint64_t m_rowPosition;

         using FieldNameIndexMap = std::map< std::string, uint32_t >;

         FieldNameIndexMap	m_fieldNameToIndex;

         mutable bool m_wasNull;

         mutable uint32_t m_lastQueriedColumn;

         std::shared_ptr< Statement > m_pStmt;

         MYSQL_RES* m_pRes;

      protected:
         MYSQL_FIELD* getFieldMeta( unsigned int columnIndex ) const;

      public:
         ResultSet( MYSQL_RES* res, std::shared_ptr< Statement > par );

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

         virtual float getFloat( uint32_t columnIndex ) const;
         virtual float getFloat( const std::string& columnLabel ) const;

         virtual int32_t getInt( uint32_t columnIndex ) const;
         virtual int32_t getInt( const std::string& columnLabel ) const;
         
         virtual uint32_t getUInt( uint32_t columnIndex ) const;
         virtual uint32_t getUInt( const std::string& columnLabel ) const;

         virtual int16_t getInt16( uint32_t columnIndex ) const;
         virtual int16_t getInt16( const std::string& columnLabel ) const;
         
         virtual uint16_t getUInt16( uint32_t columnIndex ) const;
         virtual uint16_t getUInt16( const std::string& columnLabel ) const;
         
         virtual int64_t getInt64( uint32_t columnIndex ) const;
         virtual int64_t getInt64( const std::string& columnLabel ) const;

         virtual uint64_t getUInt64( uint32_t columnIndex ) const;
         virtual uint64_t getUInt64( const std::string& columnLabel ) const;

         //sql::ResultSetMetaData * getMetaData() const;

         virtual size_t getRow() const;

         virtual const std::shared_ptr< Statement > getStatement() const;

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


#endif //SAPPHIRE_RESULTSET_H
