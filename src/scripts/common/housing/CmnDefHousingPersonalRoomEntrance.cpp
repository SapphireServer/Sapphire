#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnDefHousingPersonalRoomEntrance : public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefHousingPersonalRoomEntrance() :
    Sapphire::ScriptAPI::EventScript( 0x000b00b2 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.playScene( eventId, 0, 0, []( Entity::Player& player, const Event::SceneResult& result )
    {

    } );
  }
};

EXPOSE_SCRIPT( CmnDefHousingPersonalRoomEntrance );