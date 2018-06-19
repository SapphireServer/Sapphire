#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: ManFst003_00123
// Quest Name: Close to Home
// Quest ID: 65659
// Start NPC: 1001140
// End NPC: 1000100

class ManFst003 : public EventScript
{
private:


public:
   ManFst003() : EventScript( 65659 )
   {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {

   }
};