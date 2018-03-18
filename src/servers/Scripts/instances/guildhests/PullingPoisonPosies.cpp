#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class PullingPoisonPosies : public InstanceContentScript
{
public:
   PullingPoisonPosies() : InstanceContentScript( 10005 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {

   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                             uint16_t param2 ) override
   {

   }

};