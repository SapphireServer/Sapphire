#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Territory/HousingZone.h>
#include <Manager/HousingMgr.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/CommonActorControl.h>
#include <Exd/ExdData.h>
#include <Service.h>
#include <WorldServer.h>
#include "Manager/PlayerMgr.h"

using namespace Sapphire;
using namespace Network;
using namespace Packets;
using namespace WorldPackets;
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
      // Purchase Land
      if( result.getResult( 0 ) == 1 )
      {
        auto activeLand = player.getActiveLand();
        auto territoryId = player.getTerritoryId();

        auto pTerritory = player.getCurrentTerritory();
        auto pHousing = std::dynamic_pointer_cast< HousingZone >( pTerritory );
        auto& pHouMgr = Common::Service< HousingMgr >::ref();

        LandPurchaseResult res = pHouMgr.purchaseLand( player, activeLand.plot,
                                                        static_cast< uint8_t >( result.getResult( 0 ) ) );

        auto& server = Common::Service< World::WorldServer >::ref();
        switch( res )
        {
          case LandPurchaseResult::SUCCESS:
          {
            auto screenMsgPkt = makeActorControlSelf( player.getId(), ActorControl::DutyQuestScreenMsg, m_id, 0x98 );
            server.queueForPlayer( player.getCharacterId(), screenMsgPkt );

            PlayerMgr::sendLogMessage( player, 0x0D16, pTerritory->getTerritoryTypeInfo()->data().Area, activeLand.ward + 1, activeLand.plot + 1 );
            break;
          }

          case LandPurchaseResult::ERR_NOT_ENOUGH_GIL:
          {
            PlayerMgr::sendLogMessage( player, 3314 );
            break;
          }

          case LandPurchaseResult::ERR_NOT_AVAILABLE:
          {
            PlayerMgr::sendLogMessage( player, 3312 );
            break;
          }

          case LandPurchaseResult::ERR_NO_MORE_LANDS_FOR_CHAR:
          {
            PlayerMgr::sendLogMessage( player, 3313 );
            break;
          }

          case LandPurchaseResult::ERR_INTERNAL:
          {
            PlayerMgr::sendLogMessage( player, 1995 );
            break;
          }
        }

      }
      return LandPurchaseResult::ERR_INTERNAL;
    };

    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, callback );

  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};

EXPOSE_SCRIPT( CmnDefHousingSignboard );