#ifndef _EXDDATA_H
#define _EXDDATA_H

/* This file has been automatically generated.
   Changes will be lost upon regeneration.
   To change the content edit tools/exd_struct_gen */

#include <GameData.h>
#include <File.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

namespace Core {
namespace Data {
  class ExdDataGenerated;
   struct TerritoryType
   {
   std::string  field0;
   std::string  field1;
   uint8_t  field2;
   uint16_t  field3;
   uint16_t  field4;
   uint16_t  field5;
   uint16_t  field6;
   uint8_t  field7;
   uint8_t  field8;
   uint16_t  field9;
   uint8_t  field10;
   uint8_t  field11;
   bool  field12;
   bool  field13;
   bool  field14;
   uint16_t  field15;
   int32_t  field16;
   int32_t  field17;
   uint32_t  field18;
   uint16_t  field19;
   int32_t  field20;
   int32_t  field21;
   uint8_t  field22;
   int8_t  field23;
   bool  field24;
   uint8_t  field25;
   uint8_t  field26;
   uint8_t  field27;
   uint8_t  field28;

      TerritoryType( uint32_t id, Core::Data::ExdDataGenerated* exdData );
   };


  class ExdDataGenerated
  {
  public:
     ExdDataGenerated();
     ~ExdDataGenerated();

     bool init( const std::string& path );

     xiv::exd::Exd setupDatAccess( const std::string& name, xiv::exd::Language lang );

     template< class T >
     T getField( std::vector< xiv::exd::Field >& fields, uint32_t index )
     {
        return *boost::get< T >( &fields.at( index ) );
     }

     boost::shared_ptr< xiv::dat::GameData > m_data;
     boost::shared_ptr< xiv::exd::ExdData > m_exd_data;

     xiv::exd::Exd m_TerritoryTypeDat;


     boost::shared_ptr< TerritoryType > getTerritoryType( uint32_t TerritoryTypeId );

  };

}
}

#endif

