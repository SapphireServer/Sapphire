// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Script: ComDefGrandCompanyOfficer_00073
// Event Name: Small Talk
// Event ID: 720969
using namespace Sapphire;

class ComDefGrandCompanyOfficer : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic event information 
    // Entities found in the script data of the event
    static constexpr auto GcLeveUnlock = 1616;
    static constexpr auto GcRank08 = 8;
    static constexpr auto GcRankMax = 9;
    static constexpr auto GcRankRewardDeliverly = 6;
    static constexpr auto GcRankRewardGcchange = 9;
    static constexpr auto GcRankRewardLv30Leve = 5;
    static constexpr auto GcRankRewardLv45Leve = 8;
    static constexpr auto GcTransferUnlock = 1617;
    static constexpr auto GrandCompanyInvalid = 0;
    static constexpr auto ImmortalFlames = 3;
    static constexpr auto LogmsgGcTransferCfError = 3151;
    static constexpr auto Maelstrom = 1;
    static constexpr auto NpcOfGridania = 1002394;
    static constexpr auto NpcOfLimsa = 1002388;
    static constexpr auto NpcOfUldah = 1002391;
    static constexpr auto OrderOfTwinAdder = 2;
    static constexpr auto ProcurementMission = 720971;
    static constexpr auto ScreenImageBooty = 70;
    static constexpr auto ScreenImageLeve = 71;

  public:
    ComDefGrandCompanyOfficer() : Sapphire::ScriptAPI::EventScript( 720969 ){}; 
    ~ComDefGrandCompanyOfficer() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this event, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00000Return ) );
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00001Return ) );
  }

  void Scene00001Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 2, NONE, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00002Return ) );
  }

  void Scene00002Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, NONE, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00003Return ) );
  }

  void Scene00003Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 4, NONE, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00004Return ) );
  }

  void Scene00004Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 5, FADE_OUT | HIDE_UI, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00005Return ) );
  }

  void Scene00005Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 6, FADE_OUT | HIDE_UI, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00006Return ) );
  }

  void Scene00006Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 7, NONE, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00007Return ) );
  }

  void Scene00007Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 8, FADE_OUT | HIDE_UI, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00008Return ) );
  }

  void Scene00008Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 9, FADE_OUT | HIDE_UI, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00009Return ) );
  }

  void Scene00009Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 10, FADE_OUT | HIDE_UI, bindSceneReturn( &ComDefGrandCompanyOfficer::Scene00010Return ) );
  }

  void Scene00010Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

};

EXPOSE_SCRIPT( ComDefGrandCompanyOfficer );