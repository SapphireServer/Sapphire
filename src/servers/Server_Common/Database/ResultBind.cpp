#include "ResultBind.h"

#include "mysql_util.h"
#include "ResultBind.h"

#include <string.h>

#include <boost/scoped_ptr.hpp>

namespace Core
{
   namespace Db
   {

      struct st_buffer_size_type
      {
         char * buffer;
         size_t size;
         enum_field_types type;
         st_buffer_size_type( char * b, size_t s, enum_field_types t )
                 : buffer( b ),
                   size( s ),
                   type( t )
         {

         }
      };

      typedef std::pair< char*, size_t > BufferSizePair;
      static struct st_buffer_size_type
      allocate_buffer_for_field( const MYSQL_FIELD * const field )
      {
         switch( field->type )
         {
            case MYSQL_TYPE_NULL:
               return st_buffer_size_type( nullptr, 0, field->type );
            case MYSQL_TYPE_TINY:
               return st_buffer_size_type( new char[1], 1, field->type );
            case MYSQL_TYPE_SHORT:
               return st_buffer_size_type( new char[2], 2, field->type );
            case MYSQL_TYPE_INT24:
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_FLOAT:
               return st_buffer_size_type( new char[4], 4, field->type );
            case MYSQL_TYPE_DOUBLE:
            case MYSQL_TYPE_LONGLONG:
               return st_buffer_size_type( new char[8], 8, field->type );
            case MYSQL_TYPE_YEAR:
               return st_buffer_size_type( new char[2], 2, MYSQL_TYPE_SHORT );
            case MYSQL_TYPE_TIMESTAMP:
            case MYSQL_TYPE_DATE:
            case MYSQL_TYPE_TIME:
            case MYSQL_TYPE_DATETIME:
               return st_buffer_size_type( new char[sizeof( MYSQL_TIME )], sizeof( MYSQL_TIME ), field->type );


            case MYSQL_TYPE_TINY_BLOB:
            case MYSQL_TYPE_MEDIUM_BLOB:
            case MYSQL_TYPE_LONG_BLOB:
            case MYSQL_TYPE_BLOB:
            case MYSQL_TYPE_STRING:
            case MYSQL_TYPE_VAR_STRING:
#if LIBMYSQL_VERSION_ID > 50700
               case MYSQL_TYPE_JSON:
      return st_buffer_size_type(new char[field->max_length + 1], field->max_length + 1, field->type);
#endif //LIBMYSQL_VERSION_ID > 50700

            case MYSQL_TYPE_DECIMAL:
            case MYSQL_TYPE_NEWDECIMAL:
               return st_buffer_size_type( new char[64], 64, field->type );
#if A1
            case MYSQL_TYPE_TIMESTAMP:
            case MYSQL_TYPE_YEAR:
               return st_buffer_size_type(new char[10], 10, field->type);
#endif
#if A0
            // There two are not sent over the wire
            case MYSQL_TYPE_ENUM:
            case MYSQL_TYPE_SET:
#endif
            case MYSQL_TYPE_BIT:
               return st_buffer_size_type( new char[8], 8, MYSQL_TYPE_BIT );
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
               delete[] ( char* ) m_pBind[i].buffer;
         }
      }

      void ResultBind::bindResult()
      {
         for( uint32_t i = 0; i < m_numFields; ++i )
            delete[] ( char* ) m_pBind[i].buffer;

         m_pBind.reset( nullptr );
         m_isNull.reset( nullptr );
         m_err.reset( nullptr );
         m_len.reset( nullptr );

         m_numFields = mysql_stmt_field_count( m_pStmt );
         if( !m_numFields )
            return;

         m_pBind.reset( new MYSQL_BIND[m_numFields] );
         memset( m_pBind.get(), 0, sizeof( MYSQL_BIND ) * m_numFields );

         m_isNull.reset( new my_bool[m_numFields] );
         memset( m_isNull.get(), 0, sizeof( my_bool ) * m_numFields );

         m_err.reset( new my_bool[m_numFields] );
         memset( m_err.get(), 0, sizeof( my_bool ) * m_numFields );

         m_len.reset( new unsigned long[m_numFields] );
         memset( m_len.get(), 0, sizeof( unsigned long ) * m_numFields );

         //boost::scoped_ptr< NativeAPI::NativeResultsetWrapper > resultMeta(proxy->result_metadata());

         MYSQL_RES* info = mysql_stmt_result_metadata( m_pStmt );
         for( uint32_t i = 0; i < m_numFields; ++i )
         {
//            MYSQL_FIELD * field = resultMeta->fetch_field();

            MYSQL_FIELD * field = mysql_fetch_field( info );
            struct st_buffer_size_type p = allocate_buffer_for_field(field);
            m_pBind[i].buffer_type = p.type;
            m_pBind[i].buffer = p.buffer;
            m_pBind[i].buffer_length = static_cast< unsigned long >( p.size );
            m_pBind[i].length = &m_len[i];
            m_pBind[i].is_null = &m_isNull[i];
            m_pBind[i].error = &m_err[i];
            m_pBind[i].is_unsigned = field->flags & UNSIGNED_FLAG;
         }
         if( mysql_stmt_bind_result( m_pStmt, m_pBind.get() ) )
            throw std::runtime_error( "Couldn't bind : " + std::to_string( mysql_stmt_errno( m_pStmt ) ) );
      }

   }
}

