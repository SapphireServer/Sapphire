#ifndef SAPPHIRE_RESULTSETBASE_H
#define SAPPHIRE_RESULTSETBASE_H

#include <list>
#include <map>
#include <iostream>

namespace Mysql
{

   class Statement;

   class ResultSetBase
   {
   public:

      virtual ~ResultSetBase() {}

      virtual uint32_t findColumn( const std::string &columnLabel ) const = 0;

      virtual std::istream *getBlob( uint32_t columnIndex ) const = 0;
      virtual std::istream *getBlob( const std::string &columnLabel ) const = 0;

      virtual bool getBoolean( uint32_t columnIndex ) const = 0;
      virtual bool getBoolean( const std::string &columnLabel ) const = 0;

      virtual long double getDouble( uint32_t columnIndex ) const = 0;
      virtual long double getDouble( const std::string &columnLabel ) const = 0;

      virtual int32_t getInt( uint32_t columnIndex ) const = 0;
      virtual int32_t getInt( const std::string &columnLabel ) const = 0;

      virtual uint32_t getUInt( uint32_t columnIndex ) const = 0;
      virtual uint32_t getUInt( const std::string &columnLabel ) const = 0;

      virtual int64_t getInt64( uint32_t columnIndex ) const = 0;
      virtual int64_t getInt64( const std::string &columnLabel ) const = 0;

      virtual uint64_t getUInt64( uint32_t columnIndex ) const = 0;
      virtual uint64_t getUInt64( const std::string &columnLabel ) const = 0;

      //virtual ResultSetMetaData *getMetaData() const = 0;

      virtual size_t getRow() const = 0;

      virtual const Statement *getStatement() const = 0;

      virtual std::string getString( uint32_t columnIndex ) const = 0;
      virtual std::string getString( const std::string &columnLabel ) const = 0;

      virtual bool isFirst() const = 0;

      virtual bool isLast() const = 0;

      virtual bool isNull( uint32_t columnIndex ) const = 0;

      virtual bool isNull( const std::string &columnLabel ) const = 0;

      virtual bool next() = 0;

      virtual size_t rowsCount() const = 0;
   };
}

#endif //SAPPHIRE_RESULTSETBASE_H
