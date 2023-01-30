// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Script: ComDefFreeCompany_00076
// Event Name: Small Talk
// Event ID: 720972
using namespace Sapphire;

class ComDefFreeCompany : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic event information 
    // Entities found in the script data of the event
    static constexpr auto FcErrGeneral = 4070;
    static constexpr auto FcHierarchyMaster = 0;
    static constexpr auto GrandCompanyInvalid = 0;
    static constexpr auto ImmortalFlames = 3;
    static constexpr auto InfoErrorFcrename = 3064;
    static constexpr auto InfoErrorGil = 3021;
    static constexpr auto InfoErrorSameName = 3051;
    static constexpr auto InfoErrorStringEnd = 3110;
    static constexpr auto InfoErrorStringStart = 3022;
    static constexpr auto Maelstrom = 1;
    static constexpr auto NpcOfGridania = 1002395;
    static constexpr auto NpcOfLimsa = 1003247;
    static constexpr auto NpcOfUldah = 1002392;
    static constexpr auto OrderOfTwinAdder = 2;

  public:
    ComDefFreeCompany() : Sapphire::ScriptAPI::EventScript( 720972 ){}; 
    ~ComDefFreeCompany() = default; 

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
    eventMgr().playScene( player, getId(), 0, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00000Return ) );
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 1, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00001Return ) );
  }

  void Scene00001Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 2, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00002Return ) );
  }

  void Scene00002Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00003Return ) );
  }

  void Scene00003Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 4, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00004Return ) );
  }

  void Scene00004Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 5, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00005Return ) );
  }

  void Scene00005Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 6, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00006Return ) );
  }

  void Scene00006Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 7, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00007Return ) );
  }

  void Scene00007Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 8, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00008Return ) );
  }

  void Scene00008Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

};

EXPOSE_SCRIPT( ComDefFreeCompany );