#ifndef SAPPHIRE_PREPAREDRESULTSET_H
#define SAPPHIRE_PREPAREDRESULTSET_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "ResultSet.h"

namespace Core
{
   namespace Db
   {
      class PreparedStatement;
//      class PreparedResultSetMetaData;
      class ResultBind;

      class PreparedResultSet : public ResultSet
      {
      private:
         mutable uint32_t m_lastQueriedColumn;  // this is updated by calls to getInt(int), getString(int), etc...

         uint32_t m_numFields;
         uint64_t m_numRows;
         uint64_t m_rowPosition;

         typedef std::map< std::string, uint32_t > FieldNameIndexMap;

         FieldNameIndexMap m_fieldNameToIndex;

         PreparedStatement * m_pStmt;

         bool is_valid;

//         boost::scoped_ptr< MySQL_PreparedResultSetMetaData > rs_meta;

         boost::shared_ptr< ResultBind > m_pResultBind;

      protected:
         void checkValid() const;
         void closeIntern();
         bool isBeforeFirstOrAfterLast() const;
         void seek();

         int64_t getInt64_intern(const uint32_t columnIndex, bool cutTooBig) const;
         uint64_t getUInt64_intern(const uint32_t columnIndex, bool cutTooBig) const;

      public:
         PreparedResultSet( boost::shared_ptr< ResultBind >& pBind, PreparedStatement* par );

         virtual ~PreparedResultSet();

         void clearWarnings();

         void close();

         uint32_t findColumn( const std::string& columnLabel ) const;

         std::istream * getBlob(uint32_t columnIndex) const;
         std::istream * getBlob(const std::string& columnLabel) const;

         std::vector< char > getBlobVector( uint32_t columnIndex ) const;
         std::vector< char > getBlobVector( const std::string& columnLabel ) const;

         bool getBoolean(uint32_t columnIndex) const;
         bool getBoolean(const std::string& columnLabel) const;

         long double getDouble(uint32_t columnIndex) const;
         long double getDouble(const std::string& columnLabel) const;

         int32_t getInt(uint32_t columnIndex) const;
         int32_t getInt(const std::string& columnLabel) const;

         uint32_t getUInt(uint32_t columnIndex) const;
         uint32_t getUInt(const std::string& columnLabel) const;

         int64_t getInt64(uint32_t columnIndex) const;
         int64_t getInt64(const std::string& columnLabel) const;

         uint64_t getUInt64(uint32_t columnIndex) const;
         uint64_t getUInt64(const std::string& columnLabel) const;

         //sql::ResultSetMetaData * getMetaData() const;

         size_t getRow() const;

         const Statement * getStatement() const;

         std::string getString(uint32_t columnIndex) const;
         std::string getString(const std::string& columnLabel) const;

         void getWarnings();

         bool isClosed() const;

         void insertRow();

         bool isFirst() const;

         bool isLast() const;

         bool isNull(uint32_t columnIndex) const;

         bool isNull(const std::string& columnLabel) const;

         bool next();

         size_t rowsCount() const;

      };

   }
}



#endif //SAPPHIRE_PREPAREDRESULTSET_H
