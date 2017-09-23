#include "PreparedStatement.h"
#include "PreparedResultSet.h"
#include "Connection.h"
#include "ResultBind.h"
#include <boost/variant.hpp>
#include <boost/scoped_array.hpp>
#include <errmsg.h>
#include <string.h>

static const unsigned int MAX_SEND_LONGDATA_BUFFER = 1 << 18; //1<<18=256k (for istream)
static const unsigned int MAX_SEND_LONGDATA_CHUNK =  1 << 18; //1<<19=512k (for string)

namespace Core
{
namespace Db
{

// Visitor class to send long data contained in blob_bind
class LongDataSender : public boost::static_visitor< bool >
{
   unsigned	position;
   MYSQL_STMT* m_pStmt;
   LongDataSender()
   {}

public:

   LongDataSender(MYSQL_STMT* pStmt, unsigned int i)
           : position( i )
           , m_pStmt( pStmt )
   {
   }

   bool operator()(std::istream* my_blob) const
   {
      if (my_blob == NULL)
         return false;

      //char buf[MAX_SEND_LONGDATA_BUFFER];
      boost::scoped_array< char > buf( new char[MAX_SEND_LONGDATA_BUFFER] );

      do
      {
         if( my_blob->eof() )
            break;
         my_blob->read( buf.get(), MAX_SEND_LONGDATA_BUFFER );

         if( my_blob->bad() )
            throw std::runtime_error( "Error while reading from blob (bad)" );
         else if( my_blob->fail() )
         {
            if( !my_blob->eof() )
               throw std::runtime_error( "Error while reading from blob (fail)" );
         }
         if( mysql_stmt_send_long_data( m_pStmt, position, buf.get(), static_cast< unsigned long >( my_blob->gcount() ) ) )
         {
            switch( mysql_stmt_errno( m_pStmt ) )
            {
               case CR_OUT_OF_MEMORY:
                  throw std::bad_alloc();
               case CR_INVALID_BUFFER_USE:
                  throw std::runtime_error("PreparedStatement::setBlob: can't set blob value on that column");
               case CR_SERVER_GONE_ERROR:
               case CR_COMMANDS_OUT_OF_SYNC:
               default:
                  throw std::runtime_error("PreparedStatement:: Default error");
            }
         }
      } while( true );

      return true;
   }

   bool operator()( std::string* str ) const
   {
      if ( str == nullptr )
         return false;

      uint32_t sent = 0, chunkSize;

      while( sent < str->length() )
      {
         chunkSize = ( sent + MAX_SEND_LONGDATA_CHUNK > str->length()
                     ? str->length() - sent
                     : MAX_SEND_LONGDATA_CHUNK );

         if( mysql_stmt_send_long_data( m_pStmt, position, str->c_str() + sent, chunkSize ) )
         {

            switch( mysql_stmt_errno( m_pStmt ) )
            {
               case CR_OUT_OF_MEMORY:
                  throw std::bad_alloc();
               case CR_INVALID_BUFFER_USE:
                  throw std::runtime_error( "PreparedStatement::setBlob: can't set blob value on that column" );
               case CR_SERVER_GONE_ERROR:
               case CR_COMMANDS_OUT_OF_SYNC:
               default:
                  throw std::runtime_error( "PreparedStatement:: Default error" );
            }
         }

         sent+= chunkSize;
      }

      return true;
   }
};


class BlobBindDeleter : public boost::static_visitor<>
{
public:

   void operator()( std::string*& str ) const
   {
      if( str != nullptr )
      {
         delete str;
         str= nullptr;
      }
   }

   void operator()( std::istream*& my_blob ) const
   {
      if( my_blob!= nullptr )
      {
         delete my_blob;
         my_blob= nullptr;
      }
   }
};

class BlobIsNull : public boost::static_visitor< bool >
{
public:

   bool operator()( std::string*& str ) const
   {
      return str == nullptr;
   }

   bool operator()( std::istream*& my_blob ) const
   {
      return my_blob == nullptr;
   }
};


void resetBlobBind( MYSQL_BIND& param )
{
   delete [] static_cast<char *>( param.buffer );

   param.buffer_type = MYSQL_TYPE_LONG_BLOB;
   param.buffer = nullptr;
   param.buffer_length = 0;
   param.is_null_value = 0;

   delete param.length;
   param.length = new unsigned long( 0 );
}


class ParamBind
{
public:

   typedef boost::variant< std::istream*, std::string* > Blob_t;

private:

   unsigned int m_paramCount;
   boost::scoped_array< MYSQL_BIND > bind;
   boost::scoped_array< bool > value_set;
   boost::scoped_array< bool > delete_blob_after_execute;

   typedef std::map< uint32_t, Blob_t > Blobs;

   Blobs blob_bind;

public:

   ParamBind( uint32_t paramCount )
           :  m_paramCount( paramCount ),
              bind( nullptr ),
              value_set( nullptr ),
              delete_blob_after_execute( nullptr )
   {
      if( m_paramCount )
      {
         bind.reset( new MYSQL_BIND[paramCount] );
         memset( bind.get(), 0, sizeof( MYSQL_BIND ) * paramCount );

         value_set.reset( new bool[paramCount] );
         delete_blob_after_execute.reset( new bool[paramCount] );
         for( uint32_t i = 0; i < paramCount; ++i )
         {
            bind[i].is_null_value = 1;
            value_set[i] = false;
            delete_blob_after_execute[i] = false;
         }
      }
   }

   virtual ~ParamBind()
   {
      clearParameters();

      for( Blobs::iterator it = blob_bind.begin(); it != blob_bind.end(); ++it )
      {
         if( delete_blob_after_execute[it->first] )
         {
            delete_blob_after_execute[it->first] = false;
            boost::apply_visitor( BlobBindDeleter(), it->second );
         }
      }
   }

   void set( uint32_t position )
   {
      value_set[position] = true;
   }

   void unset( uint32_t position )
   {
      value_set[position] = false;
      if( delete_blob_after_execute[position] )
      {
         delete_blob_after_execute[position] = false;
         boost::apply_visitor( BlobBindDeleter(), blob_bind[position] );
         blob_bind.erase( position );
      }
   }


   void setBlob( uint32_t position, Blob_t & blob, bool delete_after_execute )
   {
      set( position );

      resetBlobBind( bind[position] );

      Blobs::iterator it = blob_bind.find( position );
      if( it != blob_bind.end() && delete_blob_after_execute[position] )
          boost::apply_visitor( BlobBindDeleter(), it->second );

      if( boost::apply_visitor( BlobIsNull(), blob ) )
      {
         if( it != blob_bind.end() )
            blob_bind.erase( it );

         delete_blob_after_execute[position] = false;
      }
      else
      {
         blob_bind[position] = blob;
         delete_blob_after_execute[position] = delete_after_execute;
      }
   }


   bool isAllSet()
   {
      for( uint32_t i = 0; i < m_paramCount; ++i )
      {
         if( !value_set[i] )
            return false;
      }
      return true;
   }


   void clearParameters()
   {
      for( uint32_t i = 0; i < m_paramCount; ++i )
      {
         delete ( char* ) bind[i].length;
         bind[i].length = nullptr;
         delete[] ( char* ) bind[i].buffer;
         bind[i].buffer = nullptr;
         if (value_set[i])
         {
            Blobs::iterator it = blob_bind.find( i );
            if( it != blob_bind.end() && delete_blob_after_execute[i] )
            {
               boost::apply_visitor( BlobBindDeleter(), it->second );
               blob_bind.erase( it );
            }
            blob_bind[i] = Blob_t();
            value_set[i] = false;
         }
      }
   }

   MYSQL_BIND * getBindObject()
   {
      return bind.get();
   }


   boost::variant< std::istream*, std::string* > getBlobObject( uint32_t position )
   {
      Blobs::iterator it = blob_bind.find( position );

      if( it != blob_bind.end() )
         return it->second;

      return Blob_t();
   }

};

}
}

Core::Db::PreparedStatement::PreparedStatement( MYSQL_STMT* pStmt, Core::Db::Connection* pConn )
        : Statement( pConn )
{
   m_pStmt = pStmt;
   m_pConnection = pConn;
   m_paramCount = mysql_stmt_param_count( m_pStmt );
   m_pParamBind.reset( new ParamBind( m_paramCount ) );
   m_pResultBind.reset( new ResultBind( pStmt ) );
}

uint32_t Core::Db::PreparedStatement::errNo()
{
   return mysql_stmt_errno( m_pStmt );
}

Core::Db::Connection *Core::Db::PreparedStatement::getConnection()
{
   return m_pConnection;
}

Core::Db::PreparedStatement::~PreparedStatement()
{
   if( m_pStmt )
      closeIntern();
}

uint32_t Core::Db::PreparedStatement::getWarningCount()
{
   return mysql_warning_count( m_pConnection->getRawCon() );
}

uint64_t Core::Db::PreparedStatement::getUpdateCount()
{
   throw std::runtime_error( "PreparedStatement::getUpdateCount() Not implemented" );
   return 0;
}

bool Core::Db::PreparedStatement::sendLongDataBeforeParamBind()
{
   MYSQL_BIND* bind = m_pParamBind->getBindObject();

   for( unsigned int i = 0; i < m_paramCount; ++i )
   {
      if( bind[i].buffer_type == MYSQL_TYPE_LONG_BLOB )
      {
         LongDataSender lv( m_pStmt, i );
         ParamBind::Blob_t dummy( m_pParamBind->getBlobObject( i ) );
         boost::apply_visitor( lv, dummy );
      }
   }
   return true;
}

void Core::Db::PreparedStatement::doQuery()
{
   if( m_paramCount && !m_pParamBind->isAllSet() )
      throw std::runtime_error( "Value not set for all parameters" );

   if( mysql_stmt_bind_param( m_pStmt, m_pParamBind->getBindObject() ) )
      throw std::runtime_error("Couldn't bind : " + std::to_string( errNo() ) );

   if( !sendLongDataBeforeParamBind() || mysql_stmt_execute( m_pStmt ) )
      throw std::runtime_error( "Couldn't execute : " + std::to_string( errNo() ) + ": " + m_pConnection->getError() );

   warningsCount = getWarningCount();
}

void Core::Db::PreparedStatement::closeIntern()
{
   if( m_pStmt )
      mysql_stmt_close( m_pStmt );
   clearParameters();
}

void Core::Db::PreparedStatement::clearParameters()
{
   m_pParamBind->clearParameters();
}

bool Core::Db::PreparedStatement::execute()
{
   doQuery();
   return mysql_stmt_field_count( m_pStmt ) > 0;
}

bool Core::Db::PreparedStatement::execute( const std::string &sql )
{
   throw std::runtime_error("PreparedStatement::execute( const std::string &sql ) Not implemented");
   return false;
}

Core::Db::ResultSet* Core::Db::PreparedStatement::executeQuery( const std::string &sql )
{
   // not to be implemented for prepared statements
   return nullptr;
}

Core::Db::ResultSet* Core::Db::PreparedStatement::executeQuery()
{
   doQuery();

   my_bool bool_tmp = 1;
   mysql_stmt_attr_set( m_pStmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bool_tmp );

   ResultSet* tmp = new PreparedResultSet( m_pResultBind, this );

   return tmp;
}

Core::Db::ResultSet* Core::Db::PreparedStatement::getResultSet()
{
   my_bool bool_tmp = 1;
   mysql_stmt_attr_set( m_pStmt, STMT_ATTR_UPDATE_MAX_LENGTH, &bool_tmp );

   ResultSet* tmp = new PreparedResultSet( m_pResultBind, this );

   return tmp;
}

MYSQL_STMT* Core::Db::PreparedStatement::getRawStmt()
{
   return m_pStmt;
}

typedef std::pair< char*, size_t > BufferSizePair;

static BufferSizePair allocate_buffer_for_type(enum_field_types t)
{
   switch( t )
   {
      case MYSQL_TYPE_LONG:
         return BufferSizePair( new char[4], 4 );
      case MYSQL_TYPE_DOUBLE:
      case MYSQL_TYPE_LONGLONG:
         return BufferSizePair( new char[8], 8 );
      case MYSQL_TYPE_STRING:
         return BufferSizePair( NULLCSTR, 0 );
      case MYSQL_TYPE_NULL:
         return BufferSizePair( NULLCSTR, 0 );
      default:
         throw std::runtime_error( "allocate_buffer_for_type: invalid result_bind data type" );
   }
}

void Core::Db::PreparedStatement::setInt( uint32_t parameterIndex, int32_t value )
{

   if( parameterIndex == 0 || parameterIndex > m_paramCount )
      throw std::runtime_error( "PreparedStatement::setInt: invalid 'parameterIndex'" );
   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_LONG;

   BufferSizePair p = allocate_buffer_for_type(t);

   m_pParamBind->set(parameterIndex);
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   param->buffer_type = t;
   delete [] static_cast< char* >( param->buffer );
   param->buffer = p.first;
   param->buffer_length = 0;
   param->is_null_value = 0;
   delete param->length;
   param->length = nullptr;

   memcpy( param->buffer, &value, p.second );

}

void Core::Db::PreparedStatement::setUInt( uint32_t parameterIndex, uint32_t value )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
      throw std::runtime_error( "PreparedStatement::setInt: invalid 'parameterIndex'" );
   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_LONG;

   BufferSizePair p = allocate_buffer_for_type(t);

   m_pParamBind->set( parameterIndex );
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   param->buffer_type = t;
   delete [] static_cast< char* >( param->buffer );
   param->buffer = p.first;
   param->buffer_length = 0;
   param->is_null_value = 0;
   param->is_unsigned = 1;
   delete param->length;
   param->length = nullptr;

   memcpy( param->buffer, &value, p.second );
}

void Core::Db::PreparedStatement::setInt64( uint32_t parameterIndex, int64_t value )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
      throw std::runtime_error( "PreparedStatement::setInt64: invalid 'parameterIndex'" );
   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_LONGLONG;

   BufferSizePair p = allocate_buffer_for_type(t);

   m_pParamBind->set( parameterIndex );
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   param->buffer_type = t;
   delete [] static_cast< char* >( param->buffer );
   param->buffer = p.first;
   param->buffer_length = 0;
   param->is_null_value = 0;
   delete param->length;
   param->length = nullptr;

   memcpy( param->buffer, &value, p.second );
}

void Core::Db::PreparedStatement::setUInt64( uint32_t parameterIndex, uint64_t value )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
      throw std::runtime_error( "PreparedStatement::setInt64: invalid 'parameterIndex'" );
   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_LONGLONG;

   BufferSizePair p = allocate_buffer_for_type(t);

   m_pParamBind->set( parameterIndex );
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   param->buffer_type = t;
   delete [] static_cast< char* >( param->buffer );
   param->buffer = p.first;
   param->buffer_length = 0;
   param->is_null_value = 0;
   param->is_unsigned = 1;
   delete param->length;
   param->length = nullptr;

   memcpy( param->buffer, &value, p.second );
}

void Core::Db::PreparedStatement::setNull( uint32_t parameterIndex, int )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
      throw std::runtime_error( "PreparedStatement::setNull: invalid 'parameterIndex'" );
   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_NULL;

   m_pParamBind->set( parameterIndex );
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   param->buffer_type = t;
   delete [] static_cast< char* >( param->buffer );
   param->buffer = nullptr;
   delete param->length;
   param->length = nullptr;
}

void Core::Db::PreparedStatement::setString( uint32_t parameterIndex, const std::string& value )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
   {
      throw std::runtime_error( "PreparedStatement::setString: invalid 'parameterIndex'" );
   }
   if( value.length() > 256*1024 )
   {
      std::string* pvalue = new std::string( value );
      ParamBind::Blob_t dummy( pvalue );
      return m_pParamBind->setBlob( --parameterIndex, dummy, true );
   }

   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_STRING;

   m_pParamBind->set( parameterIndex );
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   delete [] static_cast< char* >( param->buffer );

   param->buffer_type = t;
   param->buffer = memcpy( new char[value.length() + 1], value.c_str(), value.length() + 1 );
   param->buffer_length = static_cast< unsigned long >( value.length() ) + 1;
   param->is_null_value = 0;

   delete param->length;
   param->length = new unsigned long( static_cast< unsigned long >( value.length() ) );
}

void Core::Db::PreparedStatement::setDouble( uint32_t parameterIndex, double value )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
   {
      throw std::runtime_error( "PreparedStatement::setDouble: invalid 'parameterIndex'" );
   }
   --parameterIndex;

   {
      ParamBind::Blob_t dummy;
      m_pParamBind->setBlob( parameterIndex, dummy, false );
      m_pParamBind->unset( parameterIndex );
   }

   enum_field_types t = MYSQL_TYPE_DOUBLE;

   BufferSizePair p = allocate_buffer_for_type(t);

   m_pParamBind->set( parameterIndex );
   MYSQL_BIND* param = &m_pParamBind->getBindObject()[parameterIndex];

   param->buffer_type = t;
   delete [] static_cast< char* >( param->buffer );
   param->buffer = p.first;
   param->buffer_length = 0;
   param->is_null_value = 0;
   delete param->length;
   param->length = nullptr;

   memcpy( param->buffer, &value, p.second );
}

void Core::Db::PreparedStatement::setDateTime( uint32_t parameterIndex, const std::string& value )
{
   setString( parameterIndex, value );
}

void Core::Db::PreparedStatement::setBoolean( uint32_t parameterIndex, bool value )
{
   setInt( parameterIndex, value );
}

void Core::Db::PreparedStatement::setBigInt( uint32_t parameterIndex, const std::string& value )
{
   setString( parameterIndex, value );
}

void Core::Db::PreparedStatement::setBlob( uint32_t parameterIndex, std::istream* blob )
{
   if( parameterIndex == 0 || parameterIndex > m_paramCount )
      throw std::runtime_error( "PreparedStatement::setBlob: invalid 'parameterIndex'" );

   ParamBind::Blob_t dummy(blob);
   m_pParamBind->setBlob( --parameterIndex, dummy, false );
}