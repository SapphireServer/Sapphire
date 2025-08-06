#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <cstdint>

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
    std::shared_ptr< Excel::ExcelStruct< T > > getRow( uint32_t row, uint32_t subrow = 0 )
    {
      auto& sheet = getSheet< T >();
      try
      {
        return sheet.template get_row< T >( row );
      } catch( const std::runtime_error& ex )
      {
        Logger::error( "Error fetching row from sheet {}: {}", getSheetName< T >(), ex.what() );

        return nullptr;
      } catch( const std::out_of_range& )
      {
        return nullptr;
      }
    }

    template< typename T >
    std::vector< uint32_t > getIdList()
    {
      auto& sheet = getSheet< T >();
      const auto& rows = sheet.get_rows();
      std::vector< uint32_t > ids;
      ids.reserve( rows.size() );

      for( const auto& row : rows )
      {
        ids.push_back( row.first );
      }

      return ids;
    }

    template< typename T >
    std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< T > > > getRows()
    {
      auto& sheet = getSheet< T >();
      return sheet.template get_sheet_rows< T >();
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
      auto pos = origName.find_last_of( ':' );
      if( pos != std::string::npos )
      {
        return origName.substr( pos + 1 );
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

    template< typename T >
    xiv::exd::Exd& getSheet()
    {
      auto needle = m_sheets.find( typeid( T ) );
      if( needle == m_sheets.end() )
      {
        auto sheetName = getSheetName< T >();

        // load sheet
        auto& cat = m_exd_data->get_category( sheetName );
        auto& data = cat.get_data( xiv::exd::Language::en );
        m_sheets.emplace( typeid( T ), &data );
        return data;
      }
      else
      {
        return *needle->second;
      }
    }

    std::unordered_map< std::type_index, xiv::exd::Exd* > m_sheets;

    std::shared_ptr< xiv::dat::GameData > m_data;
    std::shared_ptr< xiv::exd::ExdData > m_exd_data;
  };

}
