#include "DatCat.h"

#include "Dat.h"
#include "File.h"
#include "GameData.h"
#include "Index.h"

namespace xiv::dat
{
  Cat::Cat( const std::filesystem::path& basePath, uint32_t catNum, const std::string& name ) : m_name( name ),
                                                                                                m_catNum( catNum ),
                                                                                                m_chunk( -1 )
  {
    // Format the category number as a two-digit hex string
    std::stringstream ss;
    ss << std::setw( 2 ) << std::setfill( '0' ) << std::hex << catNum;
    std::string prefix = ss.str() + "0000.win32";

    // Create an Index object using the formatted category number and basePath
    m_index = std::make_unique< Index >( basePath / "ffxiv" / ( prefix + ".index" ) );

    // Create Dat objects for each entry in the index
    for( uint32_t i = 0; i < getIndex().getDatCount(); ++i )
    {
      m_dats.emplace_back( std::make_unique< Dat >( basePath / "ffxiv" / ( prefix + ".dat" + std::to_string( i ) ), i ) );
    }
  }

  Cat::Cat( const std::filesystem::path& basePath, uint32_t catNum, const std::string& name, uint32_t exNum, uint32_t chunk ) : m_name( name ),
                                                                                                                                m_catNum( catNum ),
                                                                                                                                m_chunk( chunk )
  {
    // Create an Index object using the basePath and formatted information
    m_index = std::make_unique< Index >( basePath / GameData::buildDatStr( "ex" + std::to_string( exNum ), catNum, exNum, chunk, "win32", "index" ) );

    // Create Dat objects for each entry in the index
    for( uint32_t i = 0; i < getIndex().getDatCount(); ++i )
    {
      m_dats.emplace_back( std::make_unique< Dat >( basePath / GameData::buildDatStr( "ex" + std::to_string( exNum ), catNum, exNum, chunk, "win32", "dat" + std::to_string( i ) ), i ) );
    }
  }

  Cat::~Cat() = default;

  const Index& Cat::getIndex() const
  {
    return *m_index;
  }

  std::unique_ptr< File > Cat::getFile( uint32_t dir_hash, uint32_t filename_hash ) const
  {
    auto& hash_table_entry = getIndex().getHashTableEntry( dir_hash, filename_hash );
    return m_dats[ hash_table_entry.datNum ]->getFile( hash_table_entry.datOffset );
  }

  bool Cat::doesFileExist( uint32_t dir_hash, uint32_t filename_hash ) const
  {
    return getIndex().doesFileExist( dir_hash, filename_hash );
  }

  bool Cat::doesDirExist( uint32_t dir_hash ) const
  {
    return getIndex().doesDirExist( dir_hash );
  }

  const std::string& Cat::getName() const
  {
    return m_name;
  }

  uint32_t Cat::getCatNum() const
  {
    return m_catNum;
  }
}// namespace xiv::dat