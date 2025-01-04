#pragma once

#include <Common.h>
#include "ForwardsZone.h"

#include "Territory/Territory.h"

#include <bitset>
#include <map>

namespace Sapphire::World::Manager
{
  using QuestMap = std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< Excel::Quest > > >;
  using EObjDataCache = std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< Excel::EObj > > >;
  using ENpcDataCache = std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< Excel::ENpcBase > > >;

  class MapMgr
  {
  public:
    enum UpdateMode : uint8_t
    {
      Quest = 1,
      GuildLeveAssignment = 2,
      GuildOrderGuide = 4,
      TripleTriad = 8,
      CustomTalk = 16,
      PreHandler = 32,

      Fates = 0x0F,

      All = 0x3F
    };

    MapMgr() = default;

    bool loadQuests();

    void updateAll( Entity::Player& player );
    void updateQuests( Entity::Player& player );

  private:
    struct EventData
    {
      uint32_t iconId;
      uint32_t layoutId;
      uint32_t handlerId;
    };

    struct less
    {
      constexpr bool operator()( const EventData& _Left, const EventData& _Right ) const
      {
        const uint16_t left = _Left.handlerId;
        const uint16_t right = _Right.handlerId;

        if( left == right )
        {
          const uint16_t typeLeft = _Left.handlerId >> 16;
          const uint16_t typeRight = _Right.handlerId >> 16;

          return typeLeft < typeRight;
        }

        return left < right;
      }
    };

    using EventSet = std::multiset< EventData, less >;
    

    QuestMap m_questCacheMap;
    ENpcDataCache m_eNpcCacheMap;
    EObjDataCache m_eObjCacheMap;

    void insertQuest( Entity::Player& player, uint32_t questId, uint32_t layoutId, EventSet& mapData );

    bool isQuestVisible( Entity::Player& player, uint32_t questId, Excel::Quest& quest );
    bool isQuestAvailable( Entity::Player& player, uint32_t questId, Excel::Quest& quest );
    bool isTripleTriadAvailable( Entity::Player& player, uint32_t tripleTriadId );

    void fillPacket( EventSet& mapData, uint32_t* iconIds, uint32_t* levelIds, uint32_t* eventIds );
    void sendPackets( Entity::Player& player, EventSet& mapData, UpdateMode updateMode );
  };

}