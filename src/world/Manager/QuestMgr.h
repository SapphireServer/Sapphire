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
    void onCompleteQuest( Entity::Player& player, uint16_t questId );


    ////////////////////

    void sendQuestTracker( Entity::Player& player );

    void sendQuestsInfo( Entity::Player& player );

  };

}
