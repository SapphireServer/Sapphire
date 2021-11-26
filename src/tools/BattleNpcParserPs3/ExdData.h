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

#include <datReaderPs3/GameData.h>
#include <datReaderPs3/File.h>
#include <datReaderPs3/ExdData.h>
#include <datReaderPs3/ExdCat.h>
#include <datReaderPs3/Exd.h>

#include <Logging/Logger.h>

namespace Data
{

  class ExdData
  {
  public:
    bool init( const std::string& path );

    template< typename T >
    std::shared_ptr< Component::Excel::Ps3::ExcelStruct< T > > getRow( uint32_t row, uint32_t subrow = 0 )
    {
      xivps3::exd::Exd sheet;
      auto needle = m_sheets.find( typeid( T ) );
      if( needle == m_sheets.end() )
      {
        auto sheetName = getSheetName< T >();

        // load sheet
        auto& cat = m_exd_data->get_category( sheetName );
        m_sheets[ typeid( T ) ] = sheet = static_cast< xivps3::exd::Exd >( cat.get_data( xivps3::exd::Language::en ) );
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
        //Logger::error( "Error fetching row from sheet {}: {}", getSheetName< T >(), ex.what() );

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
      xivps3::exd::Exd sheet;
      auto needle = m_sheets.find( typeid( T ) );
      if( needle == m_sheets.end() )
      {
        auto sheetName = getSheetName< T >();

        // load sheet
        auto& cat = m_exd_data->get_category( sheetName );
        m_sheets[ typeid( T ) ] = sheet = static_cast< xivps3::exd::Exd >( cat.get_data( xivps3::exd::Language::en ) );
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

    std::shared_ptr< xivps3::dat::GameData > getGameData()
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

    std::unordered_map< std::type_index, xivps3::exd::Exd > m_sheets;

    std::shared_ptr< xivps3::dat::GameData > m_data;
    std::shared_ptr< xivps3::exd::ExdData > m_exd_data;
  };

}

