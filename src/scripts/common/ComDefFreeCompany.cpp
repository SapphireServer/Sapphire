// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "FreeCompany/FreeCompany.h"
#include "Manager/EventMgr.h"
#include "Manager/FreeCompanyMgr.h"
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

  void onYield( uint32_t eventId, uint16_t sceneId, uint8_t yieldId, Entity::Player& player, const std::string& resultString, uint64_t resultInt ) override
  {
    if( sceneId == 0 )
      eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 0, 0, 0,  0, 0, 0, 0, 1, 1, 1 } );
    else if( sceneId == 5 && yieldId == 17 )
    {

    //  auto& pFcMgr = Common::Service< Sapphire::World::Manager::FreeCompanyMgr >::ref();
    //  auto pFc = pFcMgr.createFreeCompany( resultString, resultString, player );
    //  pFcMgr.writeFreeCompany( pFc->getId() );
      /*
       *   GetFcStatusResult
            {
              uint64_t FreeCompanyID;
              uint64_t AuthorityList;
              uint64_t ChannelID;
              uint64_t CrestID;
              uint64_t CharaFcState;
              uint64_t CharaFcParam;
              uint16_t Param;
              uint8_t FcStatus;
              uint8_t GrandCompanyID;
              uint8_t HierarchyType;
              uint8_t FcRank;
              uint8_t IsCrest;
              uint8_t IsDecal;
              uint8_t IsFcAction;
              uint8_t IsChestExt1;
              uint8_t IsChestLock;
            };*/
      // { 3, 1, 3, 1234567290, 2444,   1, 0, 1, 1, 1, 0, 0, 0, 0, 0 } valid fc
      // { 3, 2, 7, 1234567890, 111223, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0 } valid fc
      // { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 } not in company yet and able to get a petition
      eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } );
    }
    else if( sceneId == 5 && yieldId == 18 )
    {
      // resultstring contains name and tag delimited by '|'
      std::size_t splitPos( resultString.find( '|' ) );
      std::string fcName( resultString.substr( 0, splitPos ) );
      std::string fcTag( resultString.substr( splitPos + 1 ) );

      auto& pFcMgr = Common::Service< Sapphire::World::Manager::FreeCompanyMgr >::ref();
      auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();
      auto pFc = pFcMgr.createFreeCompany( fcName, fcTag, player );
      // if no fc is returned, the name has been taken already
      if( !pFc )
      {
        playerMgr.sendLogMessage( player, 3051 );
        eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 3051 } );
        return;
      }
      pFcMgr.writeFreeCompany( pFc->getId() );
      eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 0 } );
      pFcMgr.sendFreeCompanyStatus( player );
    }
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this event, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ComDefFreeCompany::Scene00000Return ) );
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00001( player );
    else if( result.getResult( 0 ) == 5 )
      Scene00005( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ComDefFreeCompany::Scene00001Return ) );
  }

  void Scene00001Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  // disband fc
  void Scene00002( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 2, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00002Return ) );
  }

  void Scene00002Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  //change fc state
  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, NONE, bindSceneReturn( &ComDefFreeCompany::Scene00003Return ) );
  }

  void Scene00003Return( Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  // submit petition
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