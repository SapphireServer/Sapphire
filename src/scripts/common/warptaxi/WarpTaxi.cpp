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

class WarpTaxi : public Sapphire::ScriptAPI::EventScript
{
public:

  WarpTaxi() : Sapphire::ScriptAPI::EventScript( 0x0020000 )
  {
  }

private:

  uint16_t PreCutScene;
  uint16_t PostCutScene;
  uint32_t prevScene = 0;

public:

  bool handleMissingRequirements( uint32_t eventId, Entity::Player& player, uint64_t actorId, uint32_t returnEvent )
  {
    eventMgr().eventFinish( player, eventId, 1 );
    eventMgr().eventStart( player, actorId, returnEvent, Event::EventHandler::EventType::Talk, 0, 0, nullptr );

    return false;
  }

  bool checkRequirements( uint32_t eventId, Entity::Player& player, uint64_t actorId )
  {
    auto warpData = exdData().getRow< Excel::Warp >( eventId )->_data;

    auto warpNotQualified = warpData.UnqualifiedPreTalk;
    auto warpConditionGil = warpData.UnqualifiedGilPreTalk;

    auto warpCondition = exdData().getRow< Excel::WarpCondition >( warpData.WarpCondition )->_data;
    auto warpPrice = warpCondition.Gil;

    if( player.getCurrency( Common::CurrencyType::Gil ) < warpPrice && warpConditionGil != 0 )
    {
      return handleMissingRequirements( eventId, player, actorId, warpConditionGil );
    }
    else if( player.getLevel() < warpCondition.ClassLevel )
    {
      return handleMissingRequirements( eventId, player, actorId, warpNotQualified );
    }

    auto warpOperator = warpCondition.CompletedQuestOperator;
    bool questDone = warpOperator == 1 ? true : false;

    auto questCondsNotZero = std::any_of( std::begin( warpCondition.CompletedQuest ), std::end( warpCondition.CompletedQuest ), []( uint32_t val ) {
      return val != 0;
    } );

    if( questCondsNotZero )
    {
      for( auto quest : warpCondition.CompletedQuest )
      {
        if( quest == 0 ) continue;

        questDone = player.isQuestCompleted( quest );
        if( ( warpOperator == 1 && !questDone ) || ( warpOperator == 2 && questDone ) )
          break;
      }
    }
    else
      questDone = true;

    if( questDone )
    {
      PreCutScene = warpData.PreCutScene;
      PostCutScene = warpData.PostCutScene;

      return true;
    }
    else
      return handleMissingRequirements( eventId, player, actorId, warpNotQualified );
  }

  void warpHousingTerritory( uint32_t eventId, Entity::Player& player, uint64_t actorId )
  {
    auto warpData = exdData().getRow< Excel::Warp >( eventId )->_data;
    auto popRangeInfo = instanceObjectCache().getPopRangeInfo( warpData.PopRange );

    eventMgr().eventStart( player, actorId, 0x140001, Event::EventHandler::EventType::Nest, warpData.PopRange, 0, nullptr );
    eventMgr().playScene( player, 0x140001, 0, 0x2004, { 2, popRangeInfo->m_territoryTypeId }, [ this, popRangeInfo ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.getResult( 0 ) == 0 ) return;

      uint32_t arg1 = result.getResult( 1 );

      TerritoryPtr pTeri;
      Common::FFXIVARR_POSITION3 pos;
      float rotation;

      if( arg1 != 0xFFFFFFFF )
      {
        // Go to specific ward

        auto houseTeri = teriMgr().isHousingTerritory( player.getTerritoryTypeId() );
        uint16_t housingTeriId = houseTeri ? player.getTerritoryTypeId() : popRangeInfo->m_territoryTypeId;

        auto& housingMgr = Common::Service< World::Manager::HousingMgr >::ref();
        auto landSetId = housingMgr.toLandSetId( housingTeriId, static_cast< int8_t >( arg1 ) );
        pTeri = teriMgr().getTerritoryByGuId( landSetId );
        pos = houseTeri ? player.getPos() : popRangeInfo->m_pos;
        rotation = houseTeri ? player.getRot() : popRangeInfo->m_rotation;
      }
      else
      {
        // Go to destination territory
        pTeri = teriMgr().getTerritoryByTypeId( popRangeInfo->m_territoryTypeId );
        pos = popRangeInfo->m_pos;
        rotation = popRangeInfo->m_rotation;
      }

      if( !pTeri )
        return;

      warpMgr().requestMoveTerritory( player, Sapphire::Common::WARP_TYPE_EXIT_RANGE,
                                    pTeri->getGuId(), pos, rotation );
    } );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    if(!checkRequirements( eventId, player, actorId ))
      return;

    Scene00000( player, eventId );
  }  

  void callback( Entity::Player& player, uint32_t eventId )
  {
    auto warpData = exdData().getRow< Excel::Warp >( eventId )->_data;
    auto warpCost = exdData().getRow< Excel::WarpCondition >( warpData.WarpCondition )->_data.Gil;

    auto popRangeInfo = instanceObjectCache().getPopRangeInfo( warpData.PopRange );

    if( popRangeInfo )
    {
      if( warpCost )
        player.removeCurrency( Common::CurrencyType::Gil, warpCost );

      auto pTeri = teriMgr().getTerritoryByTypeId( popRangeInfo->m_territoryTypeId );
      warpMgr().requestMoveTerritory( player, Sapphire::Common::WARP_TYPE_TOWN_TRANSLATE,
                                    pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
    }
  }

  void Scene00000( Entity::Player& player, uint32_t eventId )
  {
    eventMgr().playScene( player, eventId, 0, 0x3000, bindSceneReturn( &WarpTaxi::Scene00000Return ) );
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult(0) == 1 )
    {
      auto warpData = exdData().getRow< Excel::Warp >( result.eventId )->_data;
      auto popRangeInfo = instanceObjectCache().getPopRangeInfo( warpData.PopRange );

      if (teriMgr().isHousingTerritory(player.getTerritoryTypeId()) || (popRangeInfo && teriMgr().isHousingTerritory(popRangeInfo->m_territoryTypeId)))
      {
        warpHousingTerritory( result.eventId, player, result.actorId );
        return;
      }
      else if (PreCutScene == 0 && PostCutScene == 0)
      {
        callback( player, result.eventId );
        return;
      }

      eventMgr().eventFinish( player, result.eventId, 1 );
      eventMgr().eventStart( player, result.actorId, result.eventId, Event::EventHandler::EventType::Nest, 0, 0, nullptr );

      if ( PreCutScene != 0 )
        Scene01000( player, result.eventId );
      else
        Scene01001( player, result.eventId );
        
    }

  }

  void Scene01000( Entity::Player& player, uint32_t eventId )
  {
    eventMgr().playScene( player, eventId, 1000, 0x4203, bindSceneReturn( &WarpTaxi::Scene01000Return ) );
  }

  void Scene01000Return( Entity::Player& player, const Event::SceneResult& result )
  {
    PostCutScene != 0 ? Scene01001( player, result.eventId ) : Scene01002( player, result.eventId );
  }

  void Scene01001( Entity::Player& player, uint32_t eventId )
  {
    eventMgr().playScene( player, eventId, 1001, 0x4203, bindSceneReturn( &WarpTaxi::Scene01001Return ) );
  }

  void Scene01001Return( Entity::Player& player, const Event::SceneResult& result )
  {
    Scene01002( player, result.eventId );
  }

  void Scene01002( Entity::Player& player, uint32_t eventId )
  {
    eventMgr().playScene( player, eventId, 1002, 0x4203, bindSceneReturn( &WarpTaxi::Scene01002Return ) );
  }

  void Scene01002Return( Entity::Player& player, const Event::SceneResult& result )
  {
    callback( player, result.eventId );
  }
};

EXPOSE_SCRIPT( WarpTaxi );