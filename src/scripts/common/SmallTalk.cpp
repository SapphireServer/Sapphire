#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class SmallTalk :
  public Sapphire::ScriptAPI::EventScript
{
public:
  SmallTalk() :
    Sapphire::ScriptAPI::EventScript( 0x000B0000 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    eventMgr().playScene( player, eventId, 0, HIDE_HOTBAR, { 0 }, nullptr );
  }
};

EXPOSE_SCRIPT( SmallTalk );