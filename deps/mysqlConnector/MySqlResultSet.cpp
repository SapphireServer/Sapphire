#include "MySqlResultSet.h"
#include "MySqlConnection.h"
#include "MySqlStatement.h"
#include "detail/MySqlUtil.h"
#include <cctype>
#include <vector>
#include <string.h>
#include <algorithm>

namespace
{
  MYSQL_RES* nativeResult( Mysql::NativeResultHandle handle )
  {
    return static_cast< MYSQL_RES* >( handle );
  }

  MYSQL_FIELD* getFieldMeta( Mysql::NativeResultHandle result, uint32_t columnIndex )
  {
    return mysql_fetch_field_direct( nativeResult( result ), columnIndex - 1 );
  }
}// namespace

Mysql::ResultSet::ResultSet( NativeResultHandle res, std::shared_ptr< Mysql::Statement > par ) :
  m_pStmt( std::move( par ) ),
  m_pRes( res )
{
  if( !res )
    return;

  m_numRows = mysql_num_rows( nativeResult( res ) );
  m_numFields = mysql_num_fields( nativeResult( res ) );
  m_rowPosition = 0;

  for( uint32_t i = 0; i < m_numFields; ++i )
  {

    std::string fieldName( getFieldMeta( m_pRes, i + 1 )->name );

    std::transform( fieldName.begin(), fieldName.end(), fieldName.begin(),
                    []( unsigned char c ) { return std::toupper( c ); } );

    m_fieldNameToIndex[ fieldName ] = i;
  }
}

Mysql::ResultSet::~ResultSet()
{
  if( m_pRes )
  {
    mysql_free_result( nativeResult( m_pRes ) );
    m_pRes = nullptr;
  }

  m_lifetimeGuard.reset();
}

uint32_t Mysql::ResultSet::findColumn( const std::string& columnLabel ) const
{
  std::string searchColumn = columnLabel;

  std::transform( searchColumn.begin(), searchColumn.end(), searchColumn.begin(),
                  []( unsigned char c ) { return std::toupper( c ); } );

  auto iter = m_fieldNameToIndex.find( searchColumn );
  if( iter == m_fieldNameToIndex.end() )
    return 0;

  return iter->second + 1;
}

size_t Mysql::ResultSet::getRow() const
{
  return static_cast< size_t >( m_rowPosition );
}

bool Mysql::ResultSet::isLast() const
{
  return ( m_rowPosition == m_numRows );
}

bool Mysql::ResultSet::isFirst() const
{
  return ( m_rowPosition == 1 );
}

bool Mysql::ResultSet::next()
{
  bool ret = false;

  m_lastQueriedColumn = -1;
  m_row = mysql_fetch_row( nativeResult( m_pRes ) );
  if( m_row == nullptr )
  {
    if( m_pStmt->errNo() == 2013 || m_pStmt->errNo() == 2000 )
      throw std::runtime_error( "Error fetching next row " + std::to_string( m_pStmt->errNo() ) +
                                ": " + m_pStmt->getConnection()->getError() );

    m_rowPosition = 0;
    return false;
  }

  ++m_rowPosition;
  ret = true;
  return ret;
}

size_t Mysql::ResultSet::rowsCount() const
{
  return static_cast< uint32_t >( m_numRows );
}

void Mysql::ResultSet::setLifetimeGuard( std::shared_ptr< void > lifetimeGuard )
{
  m_lifetimeGuard = std::move( lifetimeGuard );
}

const std::shared_ptr< Mysql::Statement > Mysql::ResultSet::getStatement() const
{
  return m_pStmt;
}

int64_t Mysql::ResultSet::getInt64( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getInt64: invalid value of 'columnIndex'" );

  m_lastQueriedColumn = columnIndex;

  if( m_row[ columnIndex - 1 ] == nullptr )
  {
    m_wasNull = true;
    return 0;
  }

  m_wasNull = false;
  if( getFieldMeta( m_pRes, columnIndex )->type == MYSQL_TYPE_BIT &&
      getFieldMeta( m_pRes, columnIndex )->flags != ( BINARY_FLAG | UNSIGNED_FLAG ) )
  {
    uint64_t uval = 0;
    std::div_t length = std::div( getFieldMeta( m_pRes, columnIndex )->length, 8 );
    if( length.rem != 0 )
      ++length.quot;

    switch( length.quot )
    {
      case 8:
        uval = ( uint64_t ) bit_uint8korr( m_row[ columnIndex - 1 ] );
        break;
      case 7:
        uval = ( uint64_t ) bit_uint7korr( m_row[ columnIndex - 1 ] );
        break;
      case 6:
        uval = ( uint64_t ) bit_uint6korr( m_row[ columnIndex - 1 ] );
        break;
      case 5:
        uval = ( uint64_t ) bit_uint5korr( m_row[ columnIndex - 1 ] );
        break;
      case 4:
        uval = ( uint64_t ) bit_uint4korr( m_row[ columnIndex - 1 ] );
        break;
      case 3:
        uval = ( uint64_t ) bit_uint3korr( m_row[ columnIndex - 1 ] );
        break;
      case 2:
        uval = ( uint64_t ) bit_uint2korr( m_row[ columnIndex - 1 ] );
        break;
      case 1:
        uval = ( uint64_t ) bit_uint1korr( m_row[ columnIndex - 1 ] );
        break;
    }
    return uval;
  }

  if( getFieldMeta( m_pRes, columnIndex )->flags & UNSIGNED_FLAG )
    return std::stoll( m_row[ columnIndex - 1 ] );
  return std::stoll( m_row[ columnIndex - 1 ] );
}

int64_t Mysql::ResultSet::getInt64( const std::string& columnLabel ) const
{
  return getInt64( findColumn( columnLabel ) );
}

uint64_t Mysql::ResultSet::getUInt64( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getUInt64: invalid value of 'columnIndex'" );

  m_lastQueriedColumn = columnIndex;

  if( m_row[ columnIndex - 1 ] == nullptr )
  {
    m_wasNull = true;
    return 0;
  }

  m_wasNull = false;
  if( getFieldMeta( m_pRes, columnIndex )->type == MYSQL_TYPE_BIT &&
      getFieldMeta( m_pRes, columnIndex )->flags != ( BINARY_FLAG | UNSIGNED_FLAG ) )
  {
    return static_cast< uint64_t >( getInt64( columnIndex ) );
  }

  return std::stoull( m_row[ columnIndex - 1 ] );
}

uint64_t Mysql::ResultSet::getUInt64( const std::string& columnLabel ) const
{
  return getUInt64( findColumn( columnLabel ) );
}

uint16_t Mysql::ResultSet::getUInt16( uint32_t columnIndex ) const
{
  return static_cast< uint16_t >( getInt( columnIndex ) );
}

uint16_t Mysql::ResultSet::getUInt16( const std::string& columnLabel ) const
{
  return getUInt16( findColumn( columnLabel ) );
}

int16_t Mysql::ResultSet::getInt16( uint32_t columnIndex ) const
{
  return static_cast< int16_t >( getInt( columnIndex ) );
}

int16_t Mysql::ResultSet::getInt16( const std::string& columnLabel ) const
{
  return getInt16( findColumn( columnLabel ) );
}

int32_t Mysql::ResultSet::getInt( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getInt: invalid value of 'columnIndex'" );

  if( ( getFieldMeta( m_pRes, columnIndex )->flags & UNSIGNED_FLAG ) != 0 )
    return static_cast< uint32_t >( getInt64( columnIndex ) );

  return static_cast< int32_t >( getInt64( columnIndex ) );
}

int32_t Mysql::ResultSet::getInt( const std::string& columnLabel ) const
{
  return getInt( findColumn( columnLabel ) );
}

uint32_t Mysql::ResultSet::getUInt( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getUInt: invalid value of 'columnIndex'" );

  return static_cast< uint32_t >( getUInt64( columnIndex ) );
}

uint32_t Mysql::ResultSet::getUInt( const std::string& columnLabel ) const
{
  return getUInt( findColumn( columnLabel ) );
}

long double Mysql::ResultSet::getDouble( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getDouble: invalid value of 'columnIndex'" );

  m_lastQueriedColumn = columnIndex;

  if( m_row[ columnIndex - 1 ] == nullptr )
  {
    m_wasNull = true;
    return 0.0;
  }
  m_wasNull = false;
  if( getFieldMeta( m_pRes, columnIndex )->type == MYSQL_TYPE_BIT )
    return static_cast< long double >( getInt64( columnIndex ) );

  return Mysql::Util::strtonum( m_row[ columnIndex - 1 ] );
}

long double Mysql::ResultSet::getDouble( const std::string& columnLabel ) const
{
  return getDouble( findColumn( columnLabel ) );
}

float Mysql::ResultSet::getFloat( uint32_t columnIndex ) const
{
  return static_cast< float >( getDouble( columnIndex ) );
}

float Mysql::ResultSet::getFloat( const std::string& columnLabel ) const
{
  return getFloat( findColumn( columnLabel ) );
}

bool Mysql::ResultSet::getBoolean( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getBoolean: invalid value of 'columnIndex'" );

  return getInt( columnIndex ) ? true : false;
}

bool Mysql::ResultSet::getBoolean( const std::string& columnLabel ) const
{
  return getInt( columnLabel ) ? true : false;
}

std::string Mysql::ResultSet::getString( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getString: invalid value of 'columnIndex'" );

  if( m_row == nullptr || m_row[ columnIndex - 1 ] == nullptr )
  {
    m_wasNull = true;
    return "";
  }

  if( getFieldMeta( m_pRes, columnIndex )->type == MYSQL_TYPE_BIT )
  {
    char buf[ 30 ];
    snprintf( buf, sizeof( buf ) - 1, "%llu", ( unsigned long long ) getUInt64( columnIndex ) );
    return std::string( buf );
  }

  size_t len = mysql_fetch_lengths( nativeResult( m_pRes ) )[ columnIndex - 1 ];
  m_wasNull = false;
  return std::string( m_row[ columnIndex - 1 ], len );
}

std::string Mysql::ResultSet::getString( const std::string& columnLabel ) const
{
  return getString( findColumn( columnLabel ) );
}

bool Mysql::ResultSet::isNull( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::isNull: invalid value of 'columnIndex'" );

  return ( m_row[ columnIndex - 1 ] == nullptr );
}

bool Mysql::ResultSet::isNull( const std::string& columnLabel ) const
{
  return isNull( findColumn( columnLabel ) );
}

std::istream* Mysql::ResultSet::getBlob( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getBlob: invalid value of 'columnIndex'" );

  return new std::istringstream( getString( columnIndex ) );
}

std::istream* Mysql::ResultSet::getBlob( const std::string& columnLabel ) const
{
  return new std::istringstream( getString( columnLabel ) );
}

std::vector< char > Mysql::ResultSet::getBlobVector( uint32_t columnIndex ) const
{
  if( columnIndex == 0 || columnIndex > m_numFields )
    throw std::runtime_error( "ResultSet::getBlobVector: invalid value of 'columnIndex'" );

  std::unique_ptr< std::istream > inStr( getBlob( columnIndex ) );
  char buff[ 4196 ];
  std::vector< char > data;

  while( inStr->good() )
  {
    inStr->read( buff, sizeof( buff ) );
    const auto count = inStr->gcount();
    if( count <= 0 )
      break;

    const auto oldSize = data.size();
    data.resize( oldSize + static_cast< size_t >( count ) );
    memcpy( data.data() + oldSize, buff, static_cast< size_t >( count ) );
  }

  return data;
}

std::vector< char > Mysql::ResultSet::getBlobVector( const std::string& columnLabel ) const
{
  return getBlobVector( findColumn( columnLabel ) );
}
