#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>

namespace Sapphire::World::Manager
{

  class QuestMgr
  {
  public:
    QuestMgr() = default;

    /// Perform required actions for events
    void onUpdateQuest( Entity::Player& player, uint8_t questIndex );
    void onRemoveQuest( Entity::Player& player, uint8_t questIndex );
    void onCompleteQuest( Entity::Player& player, uint16_t questId, uint32_t optionalChoice = 0 );


    ////////////////////

    void sendQuestTracker( Entity::Player& player );

    void sendQuestsInfo( Entity::Player& player );

    bool giveQuestRewards( Entity::Player& player, uint16_t questId, uint32_t optionalChoice );

  };

}
