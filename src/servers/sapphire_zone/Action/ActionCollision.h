#ifndef _ACTIONCOLLISION_H
#define _ACTIONCOLLISION_H

#include <common/Common.h>
#include <common/Exd/ExdDataGenerated.h>

#include "Actor/Chara.h"
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

      static bool isActorApplicable( Chara& actor, TargetFilter targetFilter );
      static std::set< CharaPtr > getActorsHitFromAction( Common::FFXIVARR_POSITION3 aoePosition,
                                                          std::set< CharaPtr > actorsInRange,
                                                          boost::shared_ptr< Data::Action > actionInfo,
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
