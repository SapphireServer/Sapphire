#ifndef SAPPHIRE_PREPAREDRESULTSET_H
#define SAPPHIRE_PREPAREDRESULTSET_H

#include <memory>
#include "ResultSet.h"

namespace Mysql
{
      class PreparedStatement;
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

         std::shared_ptr< PreparedStatement > m_pStmt;

         bool is_valid;

         std::shared_ptr< ResultBind > m_pResultBind;

      protected:
         void checkValid() const;
         void closeIntern();
         bool isBeforeFirstOrAfterLast() const;
         void seek();

         int64_t getInt64_intern( const uint32_t columnIndex, bool cutTooBig ) const;
         uint64_t getUInt64_intern( const uint32_t columnIndex, bool cutTooBig ) const;

      public:
         PreparedResultSet( std::shared_ptr< ResultBind >& pBind, std::shared_ptr< PreparedStatement > par );

         ~PreparedResultSet() override;

         void free();

         void clearWarnings();

         void close();

         uint32_t findColumn( const std::string& columnLabel ) const override;

         std::istream * getBlob( uint32_t columnIndex ) const override;
         std::istream * getBlob( const std::string& columnLabel ) const override;

         std::vector< char > getBlobVector( uint32_t columnIndex ) const override;
         std::vector< char > getBlobVector( const std::string& columnLabel ) const override;

         bool getBoolean( uint32_t columnIndex ) const override;
         bool getBoolean( const std::string& columnLabel ) const override;

         long double getDouble( uint32_t columnIndex ) const override;
         long double getDouble( const std::string& columnLabel ) const override;

         float getFloat( uint32_t columnIndex ) const override;
         float getFloat( const std::string& columnLabel ) const override;

         int32_t getInt( uint32_t columnIndex ) const override;
         int32_t getInt( const std::string& columnLabel ) const override;

         int16_t getInt16( uint32_t columnIndex ) const override;
         int16_t getInt16( const std::string& columnLabel ) const override;

         int8_t getInt8( uint32_t columnIndex ) const;
         int8_t getInt8( const std::string& columnLabel ) const;

         uint32_t getUInt( uint32_t columnIndex ) const override;
         uint32_t getUInt( const std::string& columnLabel ) const override;

         uint8_t getUInt8( uint32_t columnIndex ) const;
         uint8_t getUInt8( const std::string& columnLabel ) const;

         uint16_t getUInt16( uint32_t columnIndex ) const override;
         uint16_t getUInt16( const std::string& columnLabel ) const override;

         int64_t getInt64( uint32_t columnIndex ) const override;
         int64_t getInt64( const std::string& columnLabel ) const override;

         uint64_t getUInt64( uint32_t columnIndex ) const override;
         uint64_t getUInt64( const std::string& columnLabel ) const override;

         size_t getRow() const override;

         const std::shared_ptr< Statement > getStatement() const override;

         std::string getString( uint32_t columnIndex ) const override;
         std::string getString( const std::string& columnLabel ) const override;

         void getWarnings();

         bool isClosed() const;

         void insertRow();

         bool isFirst() const override;

         bool isLast() const override;

         bool isNull( uint32_t columnIndex ) const override;

         bool isNull( const std::string& columnLabel ) const override;

         bool next() override;

         size_t rowsCount() const;

      };
}

#endif //SAPPHIRE_PREPAREDRESULTSET_H
