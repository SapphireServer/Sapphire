#ifndef SAPPHIRE_ACTIONMGR_H
#define SAPPHIRE_ACTIONMGR_H

#include <Forwards.h>
#include <Common.h>

#include <unordered_map>

namespace Core {
namespace Action {

   class ActionMgr
   {
   public:
      ActionMgr();

      /*!
       * @brief Handler for all incoming actions
       *
       *
       * @param player the casting player
       * @param type the action type
       * @param actionId the action id
       * @param useCount
       * @param actorId the target actor id
       */
      void actionRouter( Entity::Player& player, uint8_t type, uint32_t actionId, uint32_t useCount, uint64_t targetId );

   private:
      void handleAction( Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId );
      void handleCraftAction( Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId );
      void handleItemAction( Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId );
   };

}
}


#endif //SAPPHIRE_ACTIONMGR_H
