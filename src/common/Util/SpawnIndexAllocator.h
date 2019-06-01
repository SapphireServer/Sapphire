#ifndef SAPPHIRE_SPAWNINDEXALLOCATOR_H
#define SAPPHIRE_SPAWNINDEXALLOCATOR_H

#include <queue>
#include <unordered_map>
#include <type_traits>

namespace Sapphire::Common::Util
{

  template< typename T, typename ActorIdType = uint32_t >
  class SpawnIndexAllocator
  {
  public:
    static_assert( std::is_same< T, uint8_t >::value || std::is_same< T, uint16_t >::value ||
                   std::is_same< T, uint32_t >::value || std::is_same< T, uint64_t >::value,
                   "T must be uint8_t, uint16_t, uint32_t, uint64_t" );

    SpawnIndexAllocator() :
      m_maxSlotId( 0 ),
      m_reserveFirstSlot( false )
    {
    }

    void init( T maxSlotId, bool reserveFirstSlot = false )
    {
      m_maxSlotId = maxSlotId;
      m_reserveFirstSlot = reserveFirstSlot;

      setupQueue();

      // todo: reserve max slot id in map to prevent any runtime reshashing
    }

    T freeUsedSpawnIndex( ActorIdType actorId )
    {
      auto it = m_actorIdToAllocatedMap.find( actorId );
      if( it == m_actorIdToAllocatedMap.end() )
        return getAllocFailId();

      auto index = it->second;
      m_availableIds.push( index );
      m_actorIdToAllocatedMap.erase( it );

      return index;
    }

    T getNextFreeSpawnIndex( ActorIdType actorId )
    {
      assert( m_maxSlotId != 0 );

      if( m_availableIds.empty() )
        return getAllocFailId();

      auto nextId = m_availableIds.front();
      m_availableIds.pop();

      m_actorIdToAllocatedMap[ actorId ] = nextId;

      return nextId;
    }

    void freeAllSpawnIndexes()
    {
      setupQueue();

      m_actorIdToAllocatedMap.clear();
    }

    bool isSpawnIndexValid( T spawnIndex )
    {
      return spawnIndex != getAllocFailId();
    }

    constexpr T getAllocFailId() const
    {
      return static_cast< T >( -1 );
    }

  protected:
    void setupQueue()
    {
      assert( m_maxSlotId != 0 );

      while( !m_availableIds.empty() )
        m_availableIds.pop();

      uint32_t start = 0;

      // slot 0 is reserved when used for spawning actors/players otherwise the local player actor spawnIndex
      // will be used by another actor and despawn the local player
      if( m_reserveFirstSlot )
        start = 1;

      for( uint32_t i = start; i < m_maxSlotId; i++ )
        m_availableIds.push( i );
    }

    std::queue< T > m_availableIds;
    std::unordered_map< ActorIdType, T > m_actorIdToAllocatedMap;

    T m_maxSlotId;
    bool m_reserveFirstSlot;
  };
}

#endif //SAPPHIRE_SPAWNINDEXALLOCATOR_H
