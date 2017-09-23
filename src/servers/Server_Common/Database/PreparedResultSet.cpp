#include "PreparedResultSet.h"
#include "ResultBind.h"
#include "DataType.h"
#include <string>
#include <cctype>
#include <clocale>
#include <string.h>

namespace
{
   static inline char * my_l_to_a(char * buf, size_t buf_size, int64_t a)
   {
      snprintf(buf, buf_size, "%lld", (long long) a);
      return buf;
   }

   static inline char * my_ul_to_a(char * buf, size_t buf_size, uint64_t a)
   {
      snprintf(buf, buf_size, "%llu", (unsigned long long) a);
      return buf;
   }

   static inline char * my_f_to_a(char * buf, size_t buf_size, double a)
   {
      snprintf(buf, buf_size, "%f", a);
      return buf;
   }
}

uint32_t Core::Db::PreparedResultSet::findColumn( const std::string &columnLabel ) const
{
   std::string searchColumn = columnLabel;

   std::transform( searchColumn.begin(), searchColumn.end(), searchColumn.begin(),
                   [](unsigned char c){ return std::toupper( c ); } );

   auto iter = m_fieldNameToIndex.find( searchColumn );
   if( iter == m_fieldNameToIndex.end() )
      return 0;

   return iter->second + 1;
}

Core::Db::PreparedResultSet::PreparedResultSet( boost::shared_ptr< ResultBind >& pBind,
                                                Core::Db::PreparedStatement* par ) :
   ResultSet( nullptr, par ),
   m_pResultBind( pBind )
{

}

bool Core::Db::PreparedResultSet::isBeforeFirstOrAfterLast() const
{
   return ( m_rowPosition == 0 );
}

Core::Db::PreparedResultSet::~PreparedResultSet()
{

}

uint32_t Core::Db::PreparedResultSet::getUInt( const uint32_t columnIndex ) const
{

   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getUInt: can't fetch because not on result set" );

   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getUInt: invalid value of 'columnIndex'" );

   m_lastQueriedColumn = columnIndex;

   if (*m_pResultBind->m_pBind[columnIndex - 1].is_null) {
      return 0;
   }
   return static_cast< uint32_t >( getUInt64_intern( columnIndex, true ) );
}

uint32_t Core::Db::PreparedResultSet::getUInt( const std::string& columnLabel ) const
{
   return getUInt( findColumn( columnLabel ) );
}

int64_t Core::Db::PreparedResultSet::getInt64( const uint32_t columnIndex ) const
{

   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getInt64: can't fetch because not on result set" );

   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getInt64: invalid value of 'columnIndex'" );

   m_lastQueriedColumn = columnIndex;

   if( *m_pResultBind->m_pBind[columnIndex - 1].is_null )
      return 0;

   return getInt64_intern( columnIndex, true );
}

int64_t Core::Db::PreparedResultSet::getInt64( const std::string& columnLabel ) const
{
   return getInt64( findColumn( columnLabel ) );
}

uint64_t Core::Db::PreparedResultSet::getUInt64_intern( const uint32_t columnIndex, bool ) const
{

   MYSQL_RES* res = mysql_stmt_result_metadata( m_pStmt->getRawStmt() );
   MYSQL_FIELD* field = mysql_fetch_field_direct( res, columnIndex );

   switch( Util::mysql_type_to_datatype( field ) )
   {
      case DataType::REAL:
      case DataType::DOUBLE:
         return static_cast< uint64_t >( getDouble( columnIndex ) );
      case DataType::NUMERIC:
      case DataType::DECIMAL:
      case DataType::TIMESTAMP:
      case DataType::DATE:
      case DataType::TIME:
      case DataType::CHAR:
      case DataType::BINARY:
      case DataType::VARCHAR:
      case DataType::VARBINARY:
      case DataType::LONGVARCHAR:
      case DataType::LONGVARBINARY:
      case DataType::SET:
      case DataType::ENUM:
      case DataType::JSON:
         return strtoull( getString(columnIndex).c_str(), nullptr, 10 );
      case DataType::BIT:
      {
         uint64_t uval = 0;
         /* This length is in bytes, on the contrary to what can be seen in mysql_resultset.cpp where the Meta is used */
         switch( *m_pResultBind->m_pBind[columnIndex - 1].length )
         {
            case 8:uval = (uint64_t) bit_uint8korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 7:uval = (uint64_t) bit_uint7korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 6:uval = (uint64_t) bit_uint6korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 5:uval = (uint64_t) bit_uint5korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 4:uval = (uint64_t) bit_uint4korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 3:uval = (uint64_t) bit_uint3korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 2:uval = (uint64_t) bit_uint2korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 1:uval = (uint64_t) bit_uint1korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
         }
         return uval;
      }
      case DataType::YEAR:
      case DataType::TINYINT:
      case DataType::SMALLINT:
      case DataType::MEDIUMINT:
      case DataType::INTEGER:
      case DataType::BIGINT:
      {

         uint64_t ret;
         bool is_it_null = *m_pResultBind->m_pBind[columnIndex - 1].is_null != 0;
         bool is_it_unsigned = m_pResultBind->m_pBind[columnIndex - 1].is_unsigned != 0;

         switch( m_pResultBind->m_pBind[columnIndex - 1].buffer_length )
         {
            case 1:
               if( is_it_unsigned )
                  ret = !is_it_null ? *reinterpret_cast< uint8_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret = !is_it_null ? *reinterpret_cast< int8_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            case 2:
               if(is_it_unsigned)
                  ret = !is_it_null ? *reinterpret_cast< uint16_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret = !is_it_null ? *reinterpret_cast< int16_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            case 4:
               if( is_it_unsigned )
                  ret = !is_it_null ? *reinterpret_cast< uint32_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret = !is_it_null ? *reinterpret_cast< int32_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            case 8:
               if( is_it_unsigned )
                  ret = !is_it_null ? *reinterpret_cast< uint64_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret = !is_it_null ? *reinterpret_cast< int64_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            default:
               throw std::runtime_error( "PreparedResultSet::getInt64_intern: invalid type" );
         }
         return ret;
      }
      default:
         break;
   }
   throw std::runtime_error( "MySQL_Prepared_ResultSet::getUInt64_intern: unhandled type. Please, report" );
   return 0;
}

int64_t Core::Db::PreparedResultSet::getInt64_intern( const uint32_t columnIndex, bool ) const
{

   MYSQL_RES* res = mysql_stmt_result_metadata( m_pStmt->getRawStmt() );
   MYSQL_FIELD* field = mysql_fetch_field_direct( res, columnIndex );

   switch( Util::mysql_type_to_datatype( field ) )
   {
      case DataType::REAL:
      case DataType::DOUBLE:
         return static_cast< int64_t >( getDouble( columnIndex ) );
      case DataType::NUMERIC:
      case DataType::DECIMAL:
      case DataType::TIMESTAMP:
      case DataType::DATE:
      case DataType::TIME:
      case DataType::CHAR:
      case DataType::BINARY:
      case DataType::VARCHAR:
      case DataType::VARBINARY:
      case DataType::LONGVARCHAR:
      case DataType::LONGVARBINARY:
      case DataType::SET:
      case DataType::ENUM:
      case DataType::JSON:
         return strtoll( getString( columnIndex ).c_str(), nullptr, 10 );
      case DataType::BIT:
      {
         int64_t uval = 0;
         switch( *m_pResultBind->m_pBind[columnIndex - 1].length )
         {
            case 8:uval = ( int64_t ) bit_uint8korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 7:uval = ( int64_t ) bit_uint7korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 6:uval = ( int64_t ) bit_uint6korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 5:uval = ( int64_t ) bit_uint5korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 4:uval = ( int64_t ) bit_uint4korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 3:uval = ( int64_t ) bit_uint3korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 2:uval = ( int64_t ) bit_uint2korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
            case 1:uval = ( int64_t ) bit_uint1korr( m_pResultBind->m_pBind[columnIndex - 1].buffer );break;
         }
         return uval;
      }
      case DataType::YEAR:
      case DataType::TINYINT:
      case DataType::SMALLINT:
      case DataType::MEDIUMINT:
      case DataType::INTEGER:
      case DataType::BIGINT:
      {
         int64_t ret;
         bool is_it_null = *m_pResultBind->m_pBind[columnIndex - 1].is_null != 0;
         bool is_it_unsigned = m_pResultBind->m_pBind[columnIndex - 1].is_unsigned != 0;

         switch( m_pResultBind->m_pBind[columnIndex - 1].buffer_length )
         {
            case 1:
               if( is_it_unsigned )
                  ret = !is_it_null ? *reinterpret_cast< uint8_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret = !is_it_null ? *reinterpret_cast< int8_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            case 2:
               if( is_it_unsigned )
                  ret = !is_it_null ? *reinterpret_cast< uint16_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret = !is_it_null ? *reinterpret_cast< int16_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            case 4:
               if( is_it_unsigned )
                  ret =  !is_it_null ? *reinterpret_cast< uint32_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer) : 0;
               else
                  ret =  !is_it_null ? *reinterpret_cast< int32_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer) : 0;
               break;
            case 8:
               if( is_it_unsigned )
                  ret =  !is_it_null ? *reinterpret_cast< uint64_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               else
                  ret =  !is_it_null ? *reinterpret_cast< int64_t* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0;
               break;
            default:
               throw std::runtime_error( "PreparedResultSet::getInt64_intern: invalid type" );
         }
         return ret;
      }
      default:
         break;

   }
   throw std::runtime_error( "PreparedResultSet::getInt64_intern: unhandled type. Please, report" );
   return 0;
}

uint64_t Core::Db::PreparedResultSet::getUInt64( const uint32_t columnIndex ) const
{

   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getUInt64: can't fetch because not on result set" );

   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getUInt64: invalid value of 'columnIndex'" );

   m_lastQueriedColumn = columnIndex;

   if( *m_pResultBind->m_pBind[columnIndex - 1].is_null )
      return 0;
   return getUInt64_intern( columnIndex, true );
}

uint64_t Core::Db::PreparedResultSet::getUInt64( const std::string& columnLabel ) const
{
   return getUInt64( findColumn( columnLabel ) );
}

std::string Core::Db::PreparedResultSet::getString( const uint32_t columnIndex ) const
{
   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getString: can't fetch because not on result set" );

   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getString: invalid 'columnIndex'" );

   m_lastQueriedColumn = columnIndex;
   if( *m_pResultBind->m_pBind[columnIndex - 1].is_null )
      return std::string("");

   MYSQL_RES* res = mysql_stmt_result_metadata( m_pStmt->getRawStmt() );
   MYSQL_FIELD* field = mysql_fetch_field_direct( res, columnIndex );

   switch( Util::mysql_type_to_datatype( field ) )
   {
      case DataType::TIMESTAMP:
      {
         char buf[28];
         MYSQL_TIME * t = static_cast< MYSQL_TIME* >( m_pResultBind->m_pBind[columnIndex - 1].buffer );
         if( t->second_part )
            snprintf( buf, sizeof(buf) - 1, "%04d-%02d-%02d %02d:%02d:%02d.%06lu",
                      t->year, t->month, t->day, t->hour, t->minute, t->second, t->second_part );
         else
            snprintf( buf, sizeof(buf) - 1, "%04d-%02d-%02d %02d:%02d:%02d",
                      t->year, t->month, t->day, t->hour, t->minute, t->second );

         return std::string( buf );
      }
      case DataType::DATE:
      {
         char buf[12];
         MYSQL_TIME* t = static_cast< MYSQL_TIME* >( m_pResultBind->m_pBind[columnIndex - 1].buffer );
         snprintf( buf, sizeof( buf ) - 1, "%02d-%02d-%02d", t->year, t->month, t->day );

         return std::string( buf );
      }
      case DataType::TIME:
      {
         char buf[18];
         MYSQL_TIME* t = static_cast<MYSQL_TIME*>( m_pResultBind->m_pBind[columnIndex - 1].buffer );
         if( t->second_part )
            snprintf( buf, sizeof( buf ), "%s%02d:%02d:%02d.%06lu", t->neg ? "-" : "", t->hour, t->minute, t->second, t->second_part );
         else
            snprintf( buf, sizeof( buf ), "%s%02d:%02d:%02d", t->neg ? "-" : "", t->hour, t->minute, t->second );

         return std::string( buf );
      }
      case DataType::BIT:
      case DataType::YEAR:	// fetched as a SMALLINT
      case DataType::TINYINT:
      case DataType::SMALLINT:
      case DataType::MEDIUMINT:
      case DataType::INTEGER:
      case DataType::BIGINT:
      {
         char buf[30];

         if( m_pResultBind->m_pBind[columnIndex - 1].is_unsigned )
            my_ul_to_a( buf, sizeof( buf ) - 1, getUInt64_intern( columnIndex, false ) );
         else
            my_l_to_a( buf, sizeof( buf ) - 1, getInt64_intern( columnIndex, false ) );

         return std::string( buf );
      }
      case DataType::REAL:
      case DataType::DOUBLE:
      {
         char buf[50];
         my_f_to_a( buf, sizeof( buf ) - 1, getDouble( columnIndex ) );
         return std::string( buf );
      }
      case DataType::NUMERIC:
      case DataType::DECIMAL:
      case DataType::CHAR:
      case DataType::BINARY:
      case DataType::VARCHAR:
      case DataType::VARBINARY:
      case DataType::LONGVARCHAR:
      case DataType::LONGVARBINARY:
      case DataType::SET:
      case DataType::ENUM:
      case DataType::JSON:
         return std::string( static_cast< char* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ),
                             *m_pResultBind->m_pBind[columnIndex - 1].length );
      default:
         break;
   }

   throw std::runtime_error( " PreparedResultSet::getString: unhandled type. Please, report" );
   return 0;
}

std::string Core::Db::PreparedResultSet::getString( const std::string& columnLabel) const
{
   return getString( findColumn( columnLabel ) );
}

int32_t Core::Db::PreparedResultSet::getInt( uint32_t columnIndex ) const
{
   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getInt: can't fetch because not on result set" );

   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getInt: invalid value of 'columnIndex'" );

   m_lastQueriedColumn = columnIndex;

   if( *m_pResultBind->m_pBind[columnIndex - 1].is_null )
      return 0;

   return static_cast< int32_t >( getInt64_intern( columnIndex, true ) );
}

int32_t Core::Db::PreparedResultSet::getInt( const std::string& columnLabel ) const
{
   return getInt( findColumn( columnLabel ) );
}

long double Core::Db::PreparedResultSet::getDouble(const uint32_t columnIndex) const
{
   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getDouble: can't fetch because not on result set" );

   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getDouble: invalid 'columnIndex'" );


   m_lastQueriedColumn = columnIndex;

   if( *m_pResultBind->m_pBind[columnIndex - 1].is_null)
      return 0.0;

   MYSQL_RES* res = mysql_stmt_result_metadata( m_pStmt->getRawStmt() );
   MYSQL_FIELD* field = mysql_fetch_field_direct( res, columnIndex );

   switch( Util::mysql_type_to_datatype( field ) )
   {
      case DataType::BIT:
      case DataType::YEAR:
      case DataType::TINYINT:
      case DataType::SMALLINT:
      case DataType::MEDIUMINT:
      case DataType::INTEGER:
      case DataType::BIGINT:
      {
         long double ret;
         bool is_it_unsigned = m_pResultBind->m_pBind[columnIndex - 1].is_unsigned != 0;

         if( is_it_unsigned )
         {
            uint64_t ival = getUInt64_intern( columnIndex, false );
            ret = static_cast< long double >( ival );
         }
         else
         {
            int64_t ival = getInt64_intern( columnIndex, false );
            ret = static_cast< long double >( ival );
         }
         return ret;
      }
      case DataType::NUMERIC:
      case DataType::DECIMAL:
      case DataType::TIMESTAMP:
      case DataType::DATE:
      case DataType::TIME:
      case DataType::CHAR:
      case DataType::BINARY:
      case DataType::VARCHAR:
      case DataType::VARBINARY:
      case DataType::LONGVARCHAR:
      case DataType::LONGVARBINARY:
      case DataType::SET:
      case DataType::ENUM:
      case DataType::JSON:
      {
         long double ret = Util::strtonum( getString( columnIndex ).c_str() );
         return ret;
      }
      case DataType::REAL:
      {
         long double ret = !*m_pResultBind->m_pBind[columnIndex - 1].is_null ?
                           *reinterpret_cast< float* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0.;
         return ret;
      }
      case DataType::DOUBLE:
      {
         long double ret = !*m_pResultBind->m_pBind[columnIndex - 1].is_null ?
                           *reinterpret_cast< double* >( m_pResultBind->m_pBind[columnIndex - 1].buffer ) : 0.;
         return ret;
      }
   }

   throw std::runtime_error("PreparedResultSet::getDouble: unhandled type. Please, report");
   return .0;
}

long double Core::Db::PreparedResultSet::getDouble( const std::string& columnLabel ) const
{
   return getDouble( findColumn( columnLabel ) );
}

size_t Core::Db::PreparedResultSet::getRow() const
{
   return static_cast< size_t >( m_rowPosition );
}

size_t Core::Db::PreparedResultSet::rowsCount() const
{
   return static_cast< uint32_t >( m_numRows );
}

const Core::Db::Statement* Core::Db::PreparedResultSet::getStatement() const
{
   return m_pStmt;
}

std::istream* Core::Db::PreparedResultSet::getBlob( const uint32_t columnIndex ) const
{
   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getBlob: can't fetch because not on result set" );

   return new std::istringstream( getString( columnIndex ) );
}

std::istream* Core::Db::PreparedResultSet::getBlob( const std::string& columnLabel ) const
{
   return new std::istringstream( getString( columnLabel ) );
}

std::vector< char > Core::Db::PreparedResultSet::getBlobVector( uint32_t columnIndex ) const
{
   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::getBlobVector: invalid value of 'columnIndex'" );

   boost::scoped_ptr< std::istream > inStr( getBlob( columnIndex ) );
   char buff[4196];
   std::vector< char > data;
   inStr->read( buff, sizeof( buff ) );
   if( inStr->gcount() )
   {
      data.resize( static_cast< uint32_t >( inStr->gcount() ) );
      memcpy( data.data(), buff, static_cast< size_t >( inStr->gcount() ) );
   }
   return data;
}

std::vector< char > Core::Db::PreparedResultSet::getBlobVector( const std::string& columnLabel ) const
{
   return getBlobVector( findColumn( columnLabel ) );
}

bool Core::Db::PreparedResultSet::getBoolean( const uint32_t columnIndex ) const
{
   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::getBoolean: can't fetch because not on result set" );
   return getInt(columnIndex ) != 0;
}

bool Core::Db::PreparedResultSet::getBoolean( const std::string& columnLabel ) const
{
   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error("PreparedResultSet::getBoolean: can't fetch because not on result set");
   return getInt(columnLabel ) != 0;
}

bool Core::Db::PreparedResultSet::isLast() const
{
   return ( m_rowPosition == m_numRows );
}

bool Core::Db::PreparedResultSet::isFirst() const
{
   return ( m_rowPosition == 1 );
}

bool Core::Db::PreparedResultSet::isNull( const uint32_t columnIndex ) const
{
   if( columnIndex == 0 || columnIndex > m_numFields )
      throw std::runtime_error( "PreparedResultSet::isNull: invalid value of 'columnIndex'" );

   if( isBeforeFirstOrAfterLast() )
      throw std::runtime_error( "PreparedResultSet::isNull: can't fetch because not on result set" );
   return *m_pResultBind->m_pBind[columnIndex - 1].is_null != 0;
}

bool Core::Db::PreparedResultSet::isNull( const std::string& columnLabel ) const
{
   uint32_t index = findColumn( columnLabel );
   if( index == 0 )
      throw std::runtime_error( "PreparedResultSet::isNull: invalid value of 'columnLabel'" );
   return isNull( index );
}

bool Core::Db::PreparedResultSet::next()
{
   bool ret = false;

   // reset last_queried_column
   // m_lastQueriedColumn = std::numeric_limits< uint32_t >::max();

   int result = mysql_stmt_fetch( m_pStmt->getRawStmt() );
   if( !result || result == MYSQL_DATA_TRUNCATED )
      ret = true;
   if( result == MYSQL_NO_DATA )
      ret = false;
   if( result == 1 )
      throw std::runtime_error( "PreparedResultSet:next: error getting next result" );
   ++m_rowPosition;

   return ret;
}