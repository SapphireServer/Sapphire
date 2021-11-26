#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <stdint.h>

#include <typeindex>

#if !_WIN32
# include <cxxabi.h>
#endif

#include <datReader/GameData.h>
#include <File.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <Logging/Logger.h>

namespace Sapphire::Data
{

  class ExdData
  {
  public:
    bool init( const std::string& path );

    template< typename T >
    std::shared_ptr< Component::Excel::ExcelStruct< T > > getRow( uint32_t row, uint32_t subrow = 0 )
    {
      xiv::exd::Exd sheet;
      auto needle = m_sheets.find( typeid( T ) );
      if( needle == m_sheets.end() )
      {
        auto sheetName = getSheetName< T >();

        // load sheet
        auto& cat = m_exd_data->get_category( sheetName );
        m_sheets[ typeid( T ) ] = sheet = static_cast< xiv::exd::Exd >( cat.get_data( xiv::exd::Language::en ) );
      }
      else
      {
        sheet = needle->second;
      }

      try
      {
        return sheet.get_row< T >( row );
      }
      catch( const std::runtime_error& ex )
      {
        Logger::error( "Error fetching row from sheet {}: {}", getSheetName< T >(), ex.what() );

        return nullptr;
      }
      catch( const std::out_of_range& )
      {
        return nullptr;
      }
    }

    template< typename T >
    std::vector< uint32_t > getIdList()
    {
      xiv::exd::Exd sheet;
      auto needle = m_sheets.find( typeid( T ) );
      if( needle == m_sheets.end() )
      {
        auto sheetName = getSheetName< T >();

        // load sheet
        auto& cat = m_exd_data->get_category( sheetName );
        m_sheets[ typeid( T ) ] = sheet = static_cast< xiv::exd::Exd >( cat.get_data( xiv::exd::Language::en ) );
      }
      else
      {
        sheet = needle->second;
      }

      auto rows = sheet.get_rows();
      std::vector< uint32_t > ids;

      for( const auto& row : rows )
      {
        ids.push_back( row.first );
      }

      return ids;
    }

    std::shared_ptr< xiv::dat::GameData > getGameData()
    {
      return m_data;
    }

  private:
    template< typename T >
    std::string getSheetName()
    {
      auto origName = std::string( typeid( T ).name() );
#if _WIN32
      auto pos = origName.find_last_of(':');
      if (pos != std::string::npos)
      {
          return origName.substr(pos + 1);
      }

      return "[something fucking died]";
#else

      int status = -4;

      auto res = abi::__cxa_demangle( origName.c_str(), NULL, NULL, &status );

      auto name = ( status == 0 ) ? res : origName;

      std::string demangledName( name );

      auto pos = demangledName.find_last_of( ':' );
      if( pos != std::string::npos )
      {
        demangledName = demangledName.substr( pos + 1 );
      }

      free( res );

      return demangledName;
#endif
    }

    std::unordered_map< std::type_index, xiv::exd::Exd > m_sheets;

    std::shared_ptr< xiv::dat::GameData > m_data;
    std::shared_ptr< xiv::exd::ExdData > m_exd_data;
  };

}

