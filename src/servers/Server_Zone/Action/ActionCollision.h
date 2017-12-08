#ifndef _ACTIONCOLLISION_H
#define _ACTIONCOLLISION_H

#include <Server_Common/Common.h>

#include "Actor/Actor.h"
#include "Action.h"

namespace Core {
namespace Entity {

   enum class TargetFilter
   {
      All,        // All actors in the AoE are applicable for collision
      Players,    // Only players
      Allies,     // Only allies (players, ally NPCs)
      Party,      // Only party members
      Enemies     // Only enemies
   };

   class ActionCollision
   {
   public:

      static bool isActorApplicable( ActorPtr actorPtr, TargetFilter targetFilter );
      static std::set< ActorPtr > getActorsHitFromAction( Common::FFXIVARR_POSITION3 aoePosition,
                                                          std::set< ActorPtr > actorsInRange,
                                                          boost::shared_ptr< Data::ActionInfo > actionInfo,
                                                          TargetFilter targetFilter );

   private:
      static bool radiusCollision( Common::FFXIVARR_POSITION3 actorPosition, Common::FFXIVARR_POSITION3 aoePosition,
                                   uint16_t radius );

      static bool boxCollision( Common::FFXIVARR_POSITION3 actorPosition, Common::FFXIVARR_POSITION3 aoePosition,
                                uint16_t width, uint16_t height );

   };

}
}

#endif
