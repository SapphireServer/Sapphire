#include "ExdDataGenerated.h"
#include <boost/make_shared.hpp>

#include <boost/variant.hpp>



      Core::Data::TerritoryType::TerritoryType( uint32_t id, Core::Data::ExdDataGenerated* exdData )
      {
            auto row = exdData->m_TerritoryTypeDat.get_row( id );
          field0 = exdData->getField< std::string >( row, 0 );
          field1 = exdData->getField< std::string >( row, 1 );
          field2 = exdData->getField< uint8_t >( row, 2 );
          field3 = exdData->getField< uint16_t >( row, 3 );
          field4 = exdData->getField< uint16_t >( row, 4 );
          field5 = exdData->getField< uint16_t >( row, 5 );
          field6 = exdData->getField< uint16_t >( row, 6 );
          field7 = exdData->getField< uint8_t >( row, 7 );
          field8 = exdData->getField< uint8_t >( row, 8 );
          field9 = exdData->getField< uint16_t >( row, 9 );
          field10 = exdData->getField< uint8_t >( row, 10 );
          field11 = exdData->getField< uint8_t >( row, 11 );
          field12 = exdData->getField< bool >( row, 12 );
          field13 = exdData->getField< bool >( row, 13 );
          field14 = exdData->getField< bool >( row, 14 );
          field15 = exdData->getField< uint16_t >( row, 15 );
          field16 = exdData->getField< int32_t >( row, 16 );
          field17 = exdData->getField< int32_t >( row, 17 );
          field18 = exdData->getField< uint32_t >( row, 18 );
          field19 = exdData->getField< uint16_t >( row, 19 );
          field20 = exdData->getField< int32_t >( row, 20 );
          field21 = exdData->getField< int32_t >( row, 21 );
          field22 = exdData->getField< uint8_t >( row, 22 );
          field23 = exdData->getField< int8_t >( row, 23 );
          field24 = exdData->getField< bool >( row, 24 );
          field25 = exdData->getField< uint8_t >( row, 25 );
          field26 = exdData->getField< uint8_t >( row, 26 );
          field27 = exdData->getField< uint8_t >( row, 27 );
          field28 = exdData->getField< uint8_t >( row, 28 );
      }


Core::Data::ExdDataGenerated::ExdDataGenerated()
{
}

Core::Data::ExdDataGenerated::~ExdDataGenerated()
{
}

xiv::exd::Exd Core::Data::ExdDataGenerated::setupDatAccess( const std::string& name, xiv::exd::Language lang )
{
   auto& cat = m_exd_data->get_category( name );
   return static_cast< xiv::exd::Exd >( cat.get_data_ln( lang ) );
};

bool Core::Data::ExdDataGenerated::init( const std::string& path )
{
   try
   {
      m_data = boost::make_shared< xiv::dat::GameData >( path );
      m_exd_data = boost::make_shared< xiv::exd::ExdData >( *m_data );

      m_TerritoryTypeDat = setupDatAccess( "TerritoryType", xiv::exd::Language::none );
   }
   catch( std::runtime_error )
   {
      return false;
   }

   return true;
}

///////////////////////////////////////////////////////////////
// DIRECT GETTERS
boost::shared_ptr< Core::Data::TerritoryType >
   Core::Data::ExdDataGenerated::getTerritoryType( uint32_t TerritoryTypeId )
{
   try
   {
      auto row = m_TerritoryTypeDat.get_row( TerritoryTypeId );
      auto info = boost::make_shared< TerritoryType >( TerritoryTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}




