#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#if !_WIN32
#include <cxxabi.h>
#endif

#include <Exd.h>
#include <ExdCat.h>
#include <ExdData.h>
#include <File.h>
#include <Logging/Logger.h>
#include <datReader/GameData.h>

namespace Sapphire::Data
{
  class ExdData
  {
  public:
    bool init( const std::string& path );

    template< typename T >
    std::shared_ptr< Excel::ExcelStruct< T > > getRow( uint32_t row, uint32_t subrow = 0 );

    template< typename T >
    std::vector< uint32_t > getIdList();

    template< typename T >
    std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< T > > > getRows();

    std::shared_ptr< xiv::dat::GameData > getGameData()
    {
      return m_data;
    }

  private:
    template< typename T >
    std::string getSheetName();

    template< typename T >
    xiv::exd::Exd& getSheet();

    std::unordered_map< std::type_index, xiv::exd::Exd > m_sheets;
    std::unordered_map< std::type_index, std::string > m_name_cache;
    std::shared_ptr< xiv::dat::GameData > m_data;
    std::shared_ptr< xiv::exd::ExdData > m_exd_data;
  };

  template< typename T >
  std::string ExdData::getSheetName()
  {
    auto type = std::type_index( typeid( T ) );
    auto it = m_name_cache.find( type );
    if( it != m_name_cache.end() )
    {
      return it->second;
    }

    auto origName = std::string( typeid( T ).name() );

#if _WIN32
    auto pos = origName.find_last_of( ':' );
    if( pos != std::string::npos )
    {
      std::string sheetName = origName.substr( pos + 1 );
      m_name_cache[ type ] = sheetName;
      return sheetName;
    }
    else
    {
      throw std::runtime_error( "Failed to extract the sheet name" );
    }
#else
    int status = -4;
    char* res = abi::__cxa_demangle( origName.c_str(), nullptr, nullptr, &status );
    if( status == 0 )
    {
      std::string demangledName = res;
      auto pos = demangledName.find_last_of( ':' );
      if( pos != std::string::npos ) demangledName = demangledName.substr( pos + 1 );
      m_name_cache[ type ] = demangledName;
      free( res );
      return demangledName;
    }
    else
    {
      throw std::runtime_error( "Failed to demangle the type name" );
    }
#endif
  }

  template< typename T >
  xiv::exd::Exd& ExdData::getSheet()
  {
    auto needle = m_sheets.find( typeid( T ) );
    if( needle == m_sheets.end() )
    {
      auto sheetName = getSheetName< T >();
      auto& cat = m_exd_data->get_category( sheetName );
      needle = m_sheets.emplace( typeid( T ), static_cast< xiv::exd::Exd >( cat.get_data( xiv::exd::Language::en ) ) ).first;
    }
    return needle->second;
  }

  template< typename T >
  std::shared_ptr< Excel::ExcelStruct< T > > ExdData::getRow( uint32_t row, uint32_t subrow )
  {
    try
    {
      return getSheet< T >().template get_row< T >( row );
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
  std::vector< uint32_t > ExdData::getIdList()
  {
    auto sheet = getSheet< T >();
    auto rows = sheet.get_rows();
    std::vector< uint32_t > ids;
    for( const auto& row : rows ) ids.push_back( row.first );
    return ids;
  }

  template< typename T >
  std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< T > > > ExdData::getRows()
  {
    return getSheet< T >().template get_sheet_rows< T >();
  }

}// namespace Sapphire::Data