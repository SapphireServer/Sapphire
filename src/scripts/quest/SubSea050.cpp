#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubSea050_00462
// Quest Name: On to Summerford
// Quest ID: 65998
// Start NPC: 1000972
// End NPC: 1002626

class SubSea050 : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000972;
    static constexpr auto Actor1 = 1002626;
    static constexpr auto LocActor0 = 1003289;
    static constexpr auto LocFace0 = 604;
    static constexpr auto LocFace1 = 617;
    static constexpr auto LocPosActor0 = 4201224;
    static constexpr auto LocPosCam1 = 4201231;
    static constexpr auto LocSe1 = 39;
    static constexpr auto LocSe2 = 40;

  public:
    SubSea050() : Sapphire::ScriptAPI::EventScript( 65998 ){}; 
    ~SubSea050() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( actorId );

    if( actor == Actor0 )
    {
      Scene00000( player );
    }
    else if( actor == Actor1 )
    {
      Scene00002( player );
    }
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, 0,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param2 == 1 )
        {
          player.updateQuest( getId(), Sequence::SeqFinish );
        }
      });
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
      });
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param2 == 1 )
        {
          if( player.giveQuestRewards( getId(), result.param3 ) )
          {
            player.finishQuest( getId() );
          }
        }
      });
  }

};

EXPOSE_SCRIPT( SubSea050 );