#include <ScriptObject.h>
#include <Actor/Player.h>

#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Territory/InstanceObjectCache.h"
#include "Territory/Territory.h"

#include <Exd/ExdData.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

using namespace Sapphire;

class WarpInnLimsa : public Sapphire::ScriptAPI::EventScript
{
public:
  constexpr static auto InnTerritoryType = 179;

  WarpInnLimsa() :
    Sapphire::ScriptAPI::EventScript( 131079 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
   auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();

    auto warp = exdData.getRow< Excel::Warp >( eventId );
    if( !warp )
      return;

    auto qualifiedPreResult = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto warpChoice = [ this ]( Entity::Player& player, const Event::SceneResult& result )
      {
        auto warp = this->exdData().getRow< Excel::Warp >( result.eventId );
        if( warp )
        {
          auto popRangeInfo = instanceObjectCache().getPopRangeInfo( warp->data().PopRange );
          if( popRangeInfo )
          {
            auto pTeri = teriMgr().getTerritoryByTypeId( popRangeInfo->m_territoryTypeId );
            warpMgr().requestMoveTerritory( player, Sapphire::Common::WARP_TYPE_TOWN_TRANSLATE,
                                            pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
          }
        }
      };

      eventMgr().playScene( player, result.eventId, 1, HIDE_HOTBAR, { 1 }, warpChoice );
    };

    if( player.hasReward( Common::UnlockEntry::InnRoom ) )
      eventMgr().playScene( player, eventId, 0, HIDE_HOTBAR, { 1 }, qualifiedPreResult );
    else
      eventMgr().playScene( player, eventId, 2, HIDE_HOTBAR, { 1 }, nullptr );
  }
};

EXPOSE_SCRIPT( WarpInnLimsa );