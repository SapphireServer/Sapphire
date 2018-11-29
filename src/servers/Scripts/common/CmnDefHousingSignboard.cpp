#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Zone/Zone.h>
#include <Zone/HousingZone.h>
#include <Zone/HousingMgr.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>
#include <Network/CommonActorControl.h>
#include "Framework.h"


using namespace Sapphire;
using namespace Network;
using namespace Packets;
using namespace Server;

class CmnDefHousingSignboard : public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefHousingSignboard() : Sapphire::ScriptAPI::EventScript( 721031 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto pFw = getFramework();
      if( !pFw )
        return LandPurchaseResult::ERR_INTERNAL;      
      // Purchase Land
      if( result.param2 == 2 )
      {
        auto activeLand = player.getActiveLand();
        auto territoryId = player.getTerritoryId();

        auto pTerritory = player.getCurrentZone();
        auto pHousing = std::dynamic_pointer_cast< HousingZone >( pTerritory );
        auto pHouMgr = pFw->get< Sapphire::HousingMgr >();
        
        LandPurchaseResult res = pHouMgr->purchaseLand( player, activeLand.plot,
                                                        static_cast< uint8_t >( result.param2 ) );

        switch( res )
        {
          case LandPurchaseResult::SUCCESS:
          {
            auto screenMsgPkt = makeActorControl143( player.getId(), ActorControl::DutyQuestScreenMsg, m_id, 0x98 );
            player.queuePacket( screenMsgPkt );
            auto screenMsgPkt2 = makeActorControl143( player.getId(), ActorControl::LogMsg, 0x0D16, 0x1AA,
                                                      activeLand.ward + 1, activeLand.plot + 1 );
            player.queuePacket( screenMsgPkt2 );
            break;
          }

          case LandPurchaseResult::ERR_NOT_ENOUGH_GIL:
          {
            auto errorMsg = makeActorControl143( player.getId(), ActorControl::LogMsg, 3314 );
            player.queuePacket( errorMsg );
            break;
          }

          case LandPurchaseResult::ERR_NOT_AVAILABLE:
          {
            auto errorMsg = makeActorControl143( player.getId(), ActorControl::LogMsg, 3312 );
            player.queuePacket( errorMsg );
            break;
          }

          case LandPurchaseResult::ERR_NO_MORE_LANDS_FOR_CHAR:
          {
            auto errorMsg = makeActorControl143( player.getId(), ActorControl::LogMsg, 3313 );
            player.queuePacket( errorMsg );
            break;
          }

          case LandPurchaseResult::ERR_INTERNAL:
          {
            auto errorMsg = makeActorControl143( player.getId(), ActorControl::LogMsg, 1995 );
            player.queuePacket( errorMsg );
            break;
          }
        }

      }
    };

    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, callback );

  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};
