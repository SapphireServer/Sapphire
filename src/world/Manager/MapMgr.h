#ifndef SAPPHIRE_MAPMGR_H
#define SAPPHIRE_MAPMGR_H

#include "ForwardsZone.h"

#include <set>
#include <unordered_map>

namespace Sapphire::World::Manager
{

  using QuestMap = std::unordered_map< uint32_t, Data::ExdDataGenerated::QuestPtr >;

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

      All = 0x3F
    };

    MapMgr();

    void updateAll( Entity::Player& player );
    void updateQuests( Entity::Player& player );
    
  private:
    struct EventData
    {
      uint32_t iconId;
      uint32_t levelId;
      uint32_t eventId;
    };

    struct less
    {
      constexpr bool operator()( const EventData& _Left, const EventData& _Right ) const
      {
        const uint16_t left = _Left.eventId;
        const uint16_t right = _Right.eventId;

        if( left == right )
        {
          const uint16_t typeLeft = _Left.eventId >> 16;
          const uint16_t typeRight = _Right.eventId >> 16;

          return typeLeft < typeRight;
        }

        return left < right;
      }
    };

    using EventSet = std::multiset< EventData, less >;

    QuestMap m_quests;

    void insertQuest( Entity::Player& player, uint32_t questId, EventSet& mapData );

    bool isQuestVisible( Entity::Player& player, uint32_t questId, Data::ExdDataGenerated::QuestPtr questPtr );
    bool isQuestAvailable( Entity::Player& player, uint32_t questId, Data::ExdDataGenerated::QuestPtr questPtr );
    bool isTripleTriadAvailable( Entity::Player& player, uint32_t tripleTriadId );

    void fillPacket( EventSet& mapData, uint32_t* iconIds, uint32_t* levelIds, uint32_t* eventIds );
    void sendPackets( Entity::Player& player, EventSet& mapData, UpdateMode updateMode );
  };

}

#endif // SAPPHIRE_MAPMGR_H