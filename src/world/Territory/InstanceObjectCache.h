#ifndef SAPPHIRE_INSTANCEOBJECTCACHE_H
#define SAPPHIRE_INSTANCEOBJECTCACHE_H

#include <memory>
#include <unordered_map>

struct LGB_MAP_RANGE_ENTRY;
struct LGB_EXIT_RANGE_ENTRY;
struct LGB_POP_RANGE_ENTRY;
struct LGB_EOBJ_ENTRY;
struct LGB_ENPC_ENTRY;
struct LGB_EVENT_RANGE_ENTRY;


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
    
    ObjectMap* getAll( uint16_t zoneId )
    {
      auto it = m_objectCache.find( zoneId );
      if( it != m_objectCache.end() )
      {
        return &it->second;
      }
      return nullptr;
    }

    void insert( uint16_t zoneId, std::shared_ptr< T > entry )
    {
      if( m_objectCache.find( zoneId ) == m_objectCache.end() )
      {
        ObjectMap cache;
        cache[ entry->header.instanceId ] = std::move( entry );
        m_objectCache[ zoneId ] = cache;
      }
      else
      {
        auto it = m_objectCache.find( zoneId );
        it->second[ entry->header.instanceId ] = std::move( entry );
      }
    }

    size_t size() const
    {
      size_t size = 0;
      for( auto& it = m_objectCache.begin(); it != m_objectCache.end(); ++it )
        size += it->second.size();

      return size;
    }
  };

  class InstanceObjectCache
  {
  public:
    using MapRangePtr = std::shared_ptr< LGB_MAP_RANGE_ENTRY >;
    using ExitRangePtr = std::shared_ptr< LGB_EXIT_RANGE_ENTRY >;
    using PopRangePtr = std::shared_ptr< LGB_POP_RANGE_ENTRY >;
    using EObjPtr = std::shared_ptr< LGB_EOBJ_ENTRY >;
    using ENpcPtr = std::shared_ptr< LGB_ENPC_ENTRY >;
    using EventRangePtr = std::shared_ptr< LGB_EVENT_RANGE_ENTRY >;

    using EventNpcMapPtr = std::unordered_map< uint32_t, ENpcPtr >*;
    using EventObjMapPtr = std::unordered_map< uint32_t, EObjPtr >*;

    InstanceObjectCache();
    ~InstanceObjectCache() = default;

    MapRangePtr getMapRange( uint16_t zoneId, uint32_t mapRangeId );
    ExitRangePtr getExitRange( uint16_t zoneId, uint32_t exitRangeId );
    PopRangePtr getPopRange( uint16_t zoneId, uint32_t popRangeId );
    EObjPtr getEObj( uint32_t eObjId );
    ENpcPtr getENpc( uint32_t eNpcId );
    EventRangePtr getEventRange( uint32_t eventRangeId );
        
    EventNpcMapPtr getAllEventNpc( uint16_t zoneId );
    EventObjMapPtr getAllEventObj( uint16_t zoneId );

  private:
    ObjectCache< LGB_MAP_RANGE_ENTRY > m_mapRangeCache;
    ObjectCache< LGB_EXIT_RANGE_ENTRY > m_exitRangeCache;
    ObjectCache< LGB_POP_RANGE_ENTRY > m_popRangeCache;
    ObjectCache< LGB_EOBJ_ENTRY > m_eobjCache;
    ObjectCache< LGB_ENPC_ENTRY > m_enpcCache;
    ObjectCache< LGB_EVENT_RANGE_ENTRY > m_eventRangeCache;
    std::shared_ptr< Framework > m_pFramework;

  };

}


#endif //SAPPHIRE_INSTANCEOBJECTCACHE_H
