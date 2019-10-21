#ifndef SAPPHIRE_INSTANCEOBJECTCACHE_H
#define SAPPHIRE_INSTANCEOBJECTCACHE_H

#include <memory>
#include <unordered_map>

struct LGB_MAP_RANGE_ENTRY;
struct LGB_EXIT_RANGE_ENTRY;
struct LGB_POP_RANGE_ENTRY;


namespace Sapphire
{
  class Framework;

  template< typename T >
  class ObjectCache
  {

    using ObjectPtr = std::shared_ptr< T >;
    using ObjectMap = std::unordered_map< uint32_t, ObjectPtr >;
    using ZoneObjectCache = std::unordered_map< uint16_t, ObjectMap >;

    ZoneObjectCache m_objectCache;

  public:
    ObjectPtr get( uint16_t zoneId, uint32_t id )
    {
      auto it = m_objectCache.find( zoneId );
      if( it != m_objectCache.end() )
      {
        auto rangeIt = it->second.find( id );
        if( rangeIt != it->second.end() )
        {
          return rangeIt->second;
        }
      }
      return nullptr;
    }

    template< typename T >
    void insert( uint16_t zoneId, T& entry )
    {
      auto pShared = std::make_shared< T >( entry );
      if( m_objectCache.find( zoneId ) == m_objectCache.end() )
      {
        ObjectMap cache;
        cache[ entry.header.instanceId ] = pShared;
        m_objectCache[ zoneId ] = cache;
      }
      else
      {
        auto it = m_objectCache.find( zoneId );
        it->second[ entry.header.instanceId ] = pShared;
      }
    }
  };

  class InstanceObjectCache
  {
  public:
    using MapRangePtr = std::shared_ptr< LGB_MAP_RANGE_ENTRY >;
    using ExitRangePtr = std::shared_ptr< LGB_EXIT_RANGE_ENTRY >;
    using PopRangePtr = std::shared_ptr< LGB_POP_RANGE_ENTRY >;

    InstanceObjectCache( std::shared_ptr< Framework > pFramework );
    ~InstanceObjectCache() = default;

    MapRangePtr getMapRange( uint16_t zoneId, uint32_t mapRangeId );
    ExitRangePtr getExitRange( uint16_t zoneId, uint32_t exitRangeId );
    PopRangePtr getPopRange( uint16_t zoneId, uint32_t popRangeId );

  private:
    ObjectCache< LGB_MAP_RANGE_ENTRY > m_mapRangeCache;
    ObjectCache< LGB_EXIT_RANGE_ENTRY > m_exitRangeCache;
    ObjectCache< LGB_POP_RANGE_ENTRY > m_popRangeCache;
    std::shared_ptr< Framework > m_pFramework;

  };

}


#endif //SAPPHIRE_INSTANCEOBJECTCACHE_H
