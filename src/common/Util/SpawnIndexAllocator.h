#pragma once

#include <type_traits>
#include <unordered_set>

namespace Sapphire::Common::Util
{
  // The SpawnIndexAllocator class template is a utility class that allocates
  // unique indices for spawned objects in the game world. It is parameterized
  // by the index type T and an optional actor ID type.
  template< typename T, typename ActorIdType = uint32_t >
  class SpawnIndexAllocator
  {
  public:
    static_assert( std::is_same< T, uint8_t >::value || std::is_same< T, uint16_t >::value ||
                   std::is_same< T, uint32_t >::value || std::is_same< T, uint64_t >::value,
                   "T must be uint8_t, uint16_t, uint32_t, uint64_t" );

    // Constructor for the SpawnIndexAllocator, initializing internal variables
    // such as maximum slot ID, reserve first slot flag, and allocation failure ID.
    SpawnIndexAllocator() : m_maxSlotId( 0 ),
                            m_reserveFirstSlot( false ),
                            m_allocFailId( static_cast< T >( -1 ) )
    {
    }

    // Initializes the SpawnIndexAllocator by setting the maximum slot ID and
    // whether to reserve the first slot. Sets up the free and used index sets.
    void init( T maxSlotId, bool reserveFirstSlot = false )
    {
      m_maxSlotId = maxSlotId;
      m_reserveFirstSlot = reserveFirstSlot;

      setupSet();

      // reserve max slot id in set to prevent any runtime rehashing
      m_freeIndexes.reserve( m_maxSlotId );
      m_usedIndexes.reserve( m_maxSlotId );
    }

    // Frees a used spawn index, given an actor ID. Removes the index from the
    // used set and adds it back to the free set. Returns the freed index or
    // the allocation failure ID if the actor ID is not found.
    T freeUsedSpawnIndex( ActorIdType actorId )
    {
      auto it = m_usedIndexes.find( actorId );
      if( it == m_usedIndexes.end() )
        return m_allocFailId;

      auto index = *it;
      m_usedIndexes.erase( it );
      m_freeIndexes.insert( index );

      return index;
    }

    // Allocates the next free spawn index and associates it with the given
    // actor ID. Removes the index from the free set and adds it to the used set.
    // Returns the allocated index or the allocation failure ID if there are no
    // free indices.
    T getNextFreeSpawnIndex( ActorIdType actorId )
    {
      assert( m_maxSlotId != 0 );

      if( m_freeIndexes.empty() )
        return m_allocFailId;

      auto nextId = *m_freeIndexes.begin();
      m_freeIndexes.erase( m_freeIndexes.begin() );
      m_usedIndexes.insert( nextId );

      return nextId;
    }

    // Frees all used spawn indices and clears the used set. Resets the free
    // set to contain all possible indices.
    void freeAllSpawnIndexes()
    {
      setupSet();

      m_usedIndexes.clear();
    }

    // Returns true if the given spawn index is valid (i.e., not equal to the
    // allocation failure ID), false otherwise.
    bool isSpawnIndexValid( T spawnIndex )
    {
      return spawnIndex != m_allocFailId;
    }

    // Returns the allocation failure ID.
    constexpr T getAllocFailId() const
    {
      return m_allocFailId;
    }

  protected:
    // Sets up the free index set by inserting all possible spawn indices
    // into the set, optionally reserving the first slot.
    void setupSet()
    {
      assert( m_maxSlotId != 0 );

      m_freeIndexes.clear();

      uint32_t start = 0;

      // slot is reserved when used for spawning actors/players otherwise the local player actor spawnIndex
      // will be used by another actor and despawn the local player
      if( m_reserveFirstSlot )
        start = 1;

      for( uint32_t i = start; i < m_maxSlotId; i++ )
        m_freeIndexes.insert( i );
    }

    std::unordered_set< T > m_freeIndexes;
    std::unordered_set< T > m_usedIndexes;

    T m_maxSlotId;
    bool m_reserveFirstSlot;
    const T m_allocFailId;
  };
}// namespace Sapphire::Common::Util