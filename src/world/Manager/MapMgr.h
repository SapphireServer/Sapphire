#ifndef SAPPHIRE_MAPMGR_H
#define SAPPHIRE_MAPMGR_H

#include "ForwardsZone.h"

#include <bitset>
#include <map>

namespace Sapphire::World::Manager
{

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
      uint32_t actorId;
    };

    struct QuestData
    {
      uint8_t previousQuestJoin; // 1 = requires all previous quest, 2 = requires any previous quest
      uint32_t previousQuestKeys[3];
      uint8_t previousQuest0Sequence;

      uint8_t questLockJoin; // 1 = only locks when all previous quests are done, 2 = locks when any previous quest is done
      uint32_t questLockKeys[2];

      struct
      {
        std::bitset< Common::CLASSJOB_TOTAL + 1 > classJobCategoryMask;
        uint16_t classJobLevel;
      } classJobRequirements[2];

      uint8_t column18;
      uint8_t classJobUnlock;

      uint8_t requiredGC;
      uint8_t requiredGCRank;

      uint8_t startTown;

      uint16_t header;

      uint8_t instanceContentJoin; // 1 = requires all needed instances to be completed, 2 = requires any needed instance to be completed
      uint32_t instanceContent[3];

      uint8_t festival;
      uint8_t festivalBegin;
      uint8_t festivalEnd;
      uint16_t bellStart;
      uint16_t bellEnd;

      uint8_t repeatIntervalType;
      uint8_t questRepeatFlag;

      uint8_t beastTribe;
      uint8_t beastReputationRank;
      uint16_t beastReputationValue;

      int32_t mount;

      uint8_t satisfactionNpc;
      uint8_t satisfactionRank;

      uint32_t issuer;

      uint8_t deliveryQuest;

      uint8_t expansion;

      uint8_t type;

      bool isRepeatable;
      bool isHouseRequired;

      uint32_t iconValid;
      uint32_t iconInvalid;
    };

    struct less
    {
      constexpr bool operator()( const uint32_t& _Left, const uint32_t& _Right ) const
      {
        const uint16_t left = _Left;
        const uint16_t right = _Right;

        if( left == right )
        {
          const uint16_t typeLeft = _Left >> 16;
          const uint16_t typeRight = _Right >> 16;

          return typeLeft < typeRight;
        }

        return left < right;
      }
    };

    std::map< uint16_t, std::multimap< uint32_t, EventData, less > > m_mapData;
    std::map< uint32_t, QuestData > m_questData;

    bool isQuestAvailable( Entity::Player& player, std::pair< const uint32_t, EventData >& eventData );
    bool isTripleTriadAvailable( Entity::Player& player, std::pair< const uint32_t, EventData >& eventData );

    void fillPacket( std::multimap< uint32_t, EventData, less >& mapData, uint32_t* iconIds, uint32_t* levelIds, uint32_t* eventIds );
    void sendPackets( Entity::Player& player, std::multimap< uint32_t, EventData, less >& mapData, UpdateMode updateMode );
  };

}

#endif // SAPPHIRE_MAPMGR_H