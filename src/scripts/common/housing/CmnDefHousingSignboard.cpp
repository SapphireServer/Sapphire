#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Territory/Zone.h>
#include <Territory/HousingZone.h>
#include <Manager/HousingMgr.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>
#include <Network/CommonActorControl.h>
#include <Exd/ExdDataGenerated.h>
#include "Framework.h"


using namespace Sapphire;
using namespace Network;
using namespace Packets;
using namespace Server;
using namespace Sapphire::World::Manager;

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
      auto pFw = framework();
      if( !pFw )
        return LandPurchaseResult::ERR_INTERNAL;
      // Purchase Land
      if( result.param2 == 2 )
      {
        auto activeLand = player.getActiveLand();
        auto territoryId = player.getTerritoryId();

        auto pTerritory = player.getCurrentZone();
        auto pHousing = std::dynamic_pointer_cast< HousingZone >( pTerritory );
        auto pHouMgr = pFw->get< HousingMgr >();

        LandPurchaseResult res = pHouMgr->purchaseLand( player, activeLand.plot,
                                                        static_cast< uint8_t >( result.param2 ) );

        switch( res )
        {
          case LandPurchaseResult::SUCCESS:
          {
            auto screenMsgPkt = makeActorControl143( player.getId(), ActorControl::DutyQuestScreenMsg, m_id, 0x98 );
            player.queuePacket( screenMsgPkt );

            player.sendLogMessage( 0x0D16, pTerritory->getTerritoryTypeInfo()->placeName, activeLand.ward + 1, activeLand.plot + 1 );
            break;
          }

          case LandPurchaseResult::ERR_NOT_ENOUGH_GIL:
          {
            player.sendLogMessage( 3314 );
            break;
          }

          case LandPurchaseResult::ERR_NOT_AVAILABLE:
          {
            player.sendLogMessage( 3312 );
            break;
          }

          case LandPurchaseResult::ERR_NO_MORE_LANDS_FOR_CHAR:
          {
            player.sendLogMessage( 3313 );
            break;
          }

          case LandPurchaseResult::ERR_INTERNAL:
          {
            player.sendLogMessage( 1995 );
            break;
          }
        }

      }
      return LandPurchaseResult::ERR_INTERNAL;
    };

    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, callback );

  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};

EXPOSE_SCRIPT( CmnDefHousingSignboard );