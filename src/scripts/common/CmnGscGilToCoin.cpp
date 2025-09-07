#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnGscGilToCoin : public Sapphire::ScriptAPI::EventScript
{
public:
  CmnGscGilToCoin() : Sapphire::ScriptAPI::EventScript( 721136 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 0, 0,
                          [ & ]( Entity::Player& player, const Event::SceneResult& result ) {
                            if (result.getResult(0) == 1 )
                            {
                              auto curr = result.getResult( 1 );
                              player.removeCurrency( Common::CurrencyType::Gil, curr * 10 );
                              player.addCurrency( Common::CurrencyType::Mgp, curr );
                            }
                          } );
  }
};

EXPOSE_SCRIPT( CmnGscGilToCoin );