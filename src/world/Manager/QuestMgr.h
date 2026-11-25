#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Notifications/Forwards.h"

namespace Sapphire::World::Manager
{

  class QuestMgr
  {
  public:
    QuestMgr() = default;

    /// Perform required actions for events
    void onActiveQuestChanged( const Notifications::ActiveQuestChanged& event );
    void onCompleteQuest( Entity::Player& player, uint16_t questId, uint32_t optionalChoice = 0 );


    ////////////////////

    void sendQuestTracker( Entity::Player& player );

    void sendQuestsInfo( Entity::Player& player );

    bool giveQuestRewards( Entity::Player& player, uint16_t questId, uint32_t optionalChoice );

    uint16_t getItemIcon( uint32_t itemId );
  };

}
