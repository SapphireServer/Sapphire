#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Zone/Zone.h>
#include <Zone/HousingZone.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>
#include <Network/CommonActorControl.h>


using namespace Core;
using namespace Network;
using namespace Packets;
using namespace Server;

class CmnDefHousingSignboard : public EventScript
{
public:
  CmnDefHousingSignboard() : EventScript( 721031 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      // Purchase Land
      if( result.param2 == 2 )
      {
        auto activeLand = player.getActiveLand();
        auto territoryId = player.getTerritoryId();

        auto pTerritory = player.getCurrentZone();
        auto pHousing = std::dynamic_pointer_cast< HousingZone >( pTerritory );
        
        PurchaseResult res = pHousing->purchseLand( player, activeLand.plot,
                                                    static_cast< uint8_t >( result.param2 ) );

        switch( res )
        {
          case PurchaseResult::SUCCESS:
          {
            auto screenMsgPkt = makeActorControl143( player.getId(), ActorControl::DutyQuestScreenMsg, m_id, 0x98 );
            player.queuePacket( screenMsgPkt );
            break;
          }

          case PurchaseResult::ERR_NOT_ENOUGH_GIL:
          {
            auto errorMsg = makeActorControl143( player.getId(), ActorControl::LogMsg, 4027 );
            player.queuePacket( errorMsg );
            break;
          }

          case PurchaseResult::ERR_NOT_AVAILABLE:
            break;

          case PurchaseResult::ERR_INTERNAL:
            break;
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