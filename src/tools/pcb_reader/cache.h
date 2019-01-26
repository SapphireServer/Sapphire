#ifndef CACHE_H
#define CACHE_H

#include <any>
#include <map>
#include <memory>
#include <mutex>
#include <set>

#include "pcb.h"
#include "lgb.h"
#include "sgb.h"

#include <datReader/GameData.h>
#include <datReader/File.h>
#include <datReader/DatCat.h>

class Cache : public std::enable_shared_from_this< Cache >
{
public:
  Cache( xiv::dat::GameData* pData )
  {
    if( !pData )
      throw std::runtime_error( "Unable to initialise cache without game data" );
    m_pData = pData;
  }
  ~Cache(){}

  std::shared_ptr< SGB_FILE > getSgbFile( const std::string& filepath )
  {
    std::scoped_lock lock( m_mutex );

    auto it = m_sgbCache.find( filepath );
    if( it != m_sgbCache.end() )
      return it->second;

    auto pFile = loadFile< SGB_FILE >( filepath );
    m_sgbCache[ filepath ] = pFile;
    return pFile;
  }

  std::shared_ptr< LGB_FILE > getLgbFile( const std::string& filepath )
  {
    std::scoped_lock lock( m_mutex );

    auto it = m_lgbCache.find( filepath );
    if( it != m_lgbCache.end() )
      return it->second;

    auto pFile = loadFile< LGB_FILE >( filepath );
    m_lgbCache[ filepath ] = pFile;
    return pFile;
  }

  std::shared_ptr< PCB_FILE > getPcbFile( const std::string& filepath )
  {
    std::scoped_lock lock( m_mutex );

    auto it = m_pcbCache.find( filepath );
    if( it != m_pcbCache.end() )
      return it->second;

    auto pFile = loadFile< PCB_FILE >( filepath );
    m_pcbCache[ filepath ] = pFile;
    return pFile;
  }

  void purge()
  {
    std::scoped_lock lock( m_mutex );
    _purge();
  }

private:
  void _purge()
  {
    m_lgbCache.clear();
    m_sgbCache.clear();
    m_pcbCache.clear();
    //std::cout << "Purged PCB/SGB/LGB cache \n";
  }
  template< typename T >
  std::shared_ptr< T > loadFile( const std::string& filepath )
  {
    auto buf = getFileBuffer( filepath );
    if( !buf.empty() )
    {
      try
      {
        auto pFile = std::make_shared< T >( &buf[0] );

        m_totalFiles++;
        if( m_totalFiles % 1000 == 0 )
        {
          _purge();
          m_totalFiles = 1;
        }

        return pFile;
      }
      catch( std::exception& e )
      {
        std::string err( filepath + " " + e.what() );
        std::cout << err << std::endl;
      }
    }
    return nullptr;
  }

  std::vector< char > getFileBuffer( const std::string& filepath )
  {
    try
    {
      //std::cout << fileName << " \n";
      auto pFile = m_pData->getFile( filepath );
      auto& sections = pFile->get_data_sections();
      auto& section = sections.at( 0 );
      return section;
    }
    catch( std::exception& e )
    {
      std::vector< char > empty;
      return empty;
    }
  }

  std::mutex m_mutex;
  xiv::dat::GameData* m_pData;
  std::map< std::string, std::shared_ptr< LGB_FILE > > m_lgbCache;
  std::map< std::string, std::shared_ptr< SGB_FILE > > m_sgbCache;
  std::map< std::string, std::shared_ptr< PCB_FILE > > m_pcbCache;
  int m_totalFiles{0};
};

#endif