#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class RegFstEternalCeremonyGuideRoom : public Sapphire::ScriptAPI::EventScript
{
public:
  RegFstEternalCeremonyGuideRoom() : Sapphire::ScriptAPI::EventScript( 720912 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }

  void Scene00000( Entity::Player& player )
  {
    player.playSceneChain( getId(), 0, HIDE_HOTBAR, bindScene( &RegFstEternalCeremonyGuideRoom::Scene00001 ) );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR );
  }
};

EXPOSE_SCRIPT( RegFstEternalCeremonyGuideRoom );