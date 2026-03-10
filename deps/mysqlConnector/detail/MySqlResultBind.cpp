#include "detail/MySqlResultBind.h"

#include <string.h>

namespace Mysql
{
  struct st_buffer_size_type {
    char* buffer;
    size_t size;
    enum_field_types type;
    st_buffer_size_type( char* b, size_t s, enum_field_types t )
        : buffer( b ),
          size( s ),
          type( t )
    {
    }
  };

  static size_t get_variable_field_size( const MYSQL_FIELD* const field, bool useMaxLength, size_t fallback, bool nullTerminate = false )
  {
    size_t size = fallback;

    if( useMaxLength && field->max_length > 0 )
      size = static_cast< size_t >( field->max_length );
    else if( field->length > 0 && field->length < fallback )
      size = static_cast< size_t >( field->length );

    if( nullTerminate )
      ++size;

    return std::max< size_t >( size, 1 );
  }

  static struct st_buffer_size_type
  allocate_buffer_for_field( const MYSQL_FIELD* const field, bool useMaxLength )
  {
    switch( field->type )
    {
      case MYSQL_TYPE_NULL:
        return st_buffer_size_type( nullptr, 0, field->type );
      case MYSQL_TYPE_TINY:
        return st_buffer_size_type( new char[ 1 ], 1, field->type );
      case MYSQL_TYPE_SHORT:
        return st_buffer_size_type( new char[ 2 ], 2, field->type );
      case MYSQL_TYPE_INT24:
      case MYSQL_TYPE_LONG:
      case MYSQL_TYPE_FLOAT:
        return st_buffer_size_type( new char[ 4 ], 4, field->type );
      case MYSQL_TYPE_DOUBLE:
      case MYSQL_TYPE_LONGLONG:
        return st_buffer_size_type( new char[ 8 ], 8, field->type );
      case MYSQL_TYPE_YEAR:
        return st_buffer_size_type( new char[ 2 ], 2, MYSQL_TYPE_SHORT );
      case MYSQL_TYPE_TIMESTAMP:
      case MYSQL_TYPE_DATE:
      case MYSQL_TYPE_TIME:
      case MYSQL_TYPE_DATETIME:
        return st_buffer_size_type( new char[ sizeof( MYSQL_TIME ) ], sizeof( MYSQL_TIME ), field->type );
      case MYSQL_TYPE_TINY_BLOB:
        return st_buffer_size_type( new char[ get_variable_field_size( field, useMaxLength, 256 ) ],
                                    get_variable_field_size( field, useMaxLength, 256 ), field->type );
      case MYSQL_TYPE_LONG_BLOB:
        return st_buffer_size_type( new char[ get_variable_field_size( field, useMaxLength, 64 * 1024 ) ],
                                    get_variable_field_size( field, useMaxLength, 64 * 1024 ), field->type );
      case MYSQL_TYPE_MEDIUM_BLOB:
      case MYSQL_TYPE_BLOB:
        return st_buffer_size_type( new char[ get_variable_field_size( field, useMaxLength, 64 * 1024 ) ],
                                    get_variable_field_size( field, useMaxLength, 64 * 1024 ), field->type );
      case MYSQL_TYPE_VAR_STRING:
      case MYSQL_TYPE_STRING:
        return st_buffer_size_type( new char[ get_variable_field_size( field, useMaxLength, 4096, true ) ],
                                    get_variable_field_size( field, useMaxLength, 4096, true ), field->type );

      case MYSQL_TYPE_DECIMAL:
      case MYSQL_TYPE_NEWDECIMAL:
        return st_buffer_size_type( new char[ get_variable_field_size( field, useMaxLength, 64, true ) ],
                                    get_variable_field_size( field, useMaxLength, 64, true ), field->type );
#if A1
      case MYSQL_TYPE_TIMESTAMP:
      case MYSQL_TYPE_YEAR:
        return st_buffer_size_type( new char[ 10 ], 10, field->type );
#endif
#if A0
      // There two are not sent over the wire
      case MYSQL_TYPE_ENUM:
      case MYSQL_TYPE_SET:
#endif
      case MYSQL_TYPE_BIT:
        return st_buffer_size_type( new char[ 8 ], 8, MYSQL_TYPE_BIT );
      case MYSQL_TYPE_GEOMETRY:
      default:
        throw std::runtime_error( "allocate_buffer_for_field: invalid rbind data type" );
    }
  }

  ResultBind::ResultBind( MYSQL_STMT* pStmt )
      : m_pStmt( pStmt ),
        m_numFields( 0 ),
        m_isNull( nullptr ),
        m_err( nullptr ),
        m_len( nullptr ),
        m_pBind( nullptr )
  {
  }

  ResultBind::~ResultBind()
  {
    if( m_pBind.get() )
    {
      for( uint32_t i = 0; i < m_numFields; ++i )
        delete[]( char* ) m_pBind[ i ].buffer;
    }
  }

  void ResultBind::bindResult( bool useMaxLength )
  {
    for( uint32_t i = 0; i < m_numFields; ++i )
      delete[]( char* ) m_pBind[ i ].buffer;

    m_pBind.reset( nullptr );
    m_isNull.reset( nullptr );
    m_err.reset( nullptr );
    m_len.reset( nullptr );

    m_numFields = mysql_stmt_field_count( m_pStmt );
    if( !m_numFields )
      return;

    m_pBind.reset( new MYSQL_BIND[ m_numFields ] );
    memset( m_pBind.get(), 0, sizeof( MYSQL_BIND ) * m_numFields );

    m_isNull.reset( new BindBool[ m_numFields ] );
    memset( m_isNull.get(), 0, sizeof( BindBool ) * m_numFields );

    m_err.reset( new BindBool[ m_numFields ] );
    memset( m_err.get(), 0, sizeof( BindBool ) * m_numFields );

    m_len.reset( new unsigned long[ m_numFields ] );
    memset( m_len.get(), 0, sizeof( unsigned long ) * m_numFields );


    MYSQL_RES* info = mysql_stmt_result_metadata( m_pStmt );
    if( !info )
      throw std::runtime_error( "Couldn't obtain result metadata : " + std::to_string( mysql_stmt_errno( m_pStmt ) ) );

    for( uint32_t i = 0; i < m_numFields; ++i )
    {
      //            MYSQL_FIELD * field = resultMeta->fetch_field();

      MYSQL_FIELD* field = mysql_fetch_field_direct( info, i );
      struct st_buffer_size_type p = allocate_buffer_for_field( field, useMaxLength );
      m_pBind[ i ].buffer_type = p.type;
      m_pBind[ i ].buffer = p.buffer;
      m_pBind[ i ].buffer_length = static_cast< unsigned long >( p.size );
      m_pBind[ i ].length = &m_len[ i ];
      m_pBind[ i ].is_null = &m_isNull[ i ];
      m_pBind[ i ].error = &m_err[ i ];
      m_pBind[ i ].is_unsigned = field->flags & UNSIGNED_FLAG;
    }

    mysql_free_result( info );

    if( mysql_stmt_bind_result( m_pStmt, m_pBind.get() ) )
      throw std::runtime_error( "Couldn't bind : " + std::to_string( mysql_stmt_errno( m_pStmt ) ) );
  }
}// namespace Mysql
