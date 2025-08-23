#ifndef SAPPHIRE_INSTANCEOBJECTCACHE_H
#define SAPPHIRE_INSTANCEOBJECTCACHE_H

#include <memory>
#include <unordered_map>
#include <map>
#include <Common.h>

struct MapRangeEntry;
struct ExitRangeEntry;
struct PopRangeEntry;
struct EventObjectEntry;
struct EventNPCEntry;
struct EventRangeEntry;


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
      for( auto& entry : m_objectCache )
      {
        auto rangeIt = entry.second.find( id );
        if( rangeIt != entry.second.end() )
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
        cache[ entry->header.InstanceID ] = std::move( entry );
        m_objectCache[ zoneId ] = cache;
      }
      else
      {
        auto it = m_objectCache.find( zoneId );
        it->second[ entry->header.InstanceID ] = std::move( entry );
      }
    }

    size_t size() const
    {
      size_t size = 0;
      for( auto it = m_objectCache.begin(); it != m_objectCache.end(); ++it )
        size += it->second.size();

      return size;
    }
  };

  class InstanceObjectCache
  {
  public:
    using MapRangePtr = std::shared_ptr< MapRangeEntry >;
    using ExitRangePtr = std::shared_ptr< ExitRangeEntry >;
    using PopRangePtr = std::shared_ptr< PopRangeEntry >;
    using EObjPtr = std::shared_ptr< EventObjectEntry >;
    using ENpcPtr = std::shared_ptr< EventNPCEntry >;
    using EventRangePtr = std::shared_ptr< EventRangeEntry >;

    using EObjMapPtr = std::unordered_map< uint32_t, EObjPtr >*;
    using ENpcMapPtr = std::unordered_map< uint32_t, ENpcPtr >*;

    struct PopRangeInfo
    {
      Common::FFXIVARR_POSITION3 m_pos;
      float m_rotation;
      uint16_t m_territoryTypeId;
    };

    InstanceObjectCache();
    ~InstanceObjectCache() = default;

    MapRangePtr getMapRange( uint16_t zoneId, uint32_t mapRangeId );
    ExitRangePtr getExitRange( uint16_t zoneId, uint32_t exitRangeId );
    PopRangePtr getPopRange( uint32_t popRangeId );

    std::shared_ptr< PopRangeInfo > getPopRangeInfo( uint32_t popRangeId );


    EObjPtr getEObj( uint32_t eObjId );
    EObjPtr getEObjByBaseId( uint16_t zoneId, uint32_t baseId );
    ENpcPtr getENpc( uint32_t eNpcId );

    EObjMapPtr getAllEObj( uint16_t zoneId );
    ENpcMapPtr getAllENpc( uint16_t zoneId );

    EventRangePtr getEventRange( uint32_t eventRangeId );

  private:
    ObjectCache< MapRangeEntry > m_mapRangeCache;
    ObjectCache< ExitRangeEntry > m_exitRangeCache;
    ObjectCache< PopRangeEntry > m_popRangeCache;
    ObjectCache< EventObjectEntry > m_eobjCache;
    ObjectCache< EventNPCEntry > m_enpcCache;
    ObjectCache< EventRangeEntry > m_eventRangeCache;

    std::map< std::pair< uint16_t, uint32_t >, uint32_t > m_eobjBaseInstanceMap;
    std::shared_ptr< Framework > m_pFramework;

  };

}


#endif //SAPPHIRE_INSTANCEOBJECTCACHE_H
