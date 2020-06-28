// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst021_00095
// Quest Name: Hematophagic Harassment
// Quest ID: 65631
// Start NPC: 1000640
// End NPC: 1000640

using namespace Sapphire;

class SubFst021 : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // GetQuestUI8AL

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000640;
    static constexpr auto Enemy0 = 118; //136; <- WRONG INFO 

  public:
    SubFst021() : Sapphire::ScriptAPI::EventScript( 65631 ){}; 
    ~SubFst021(){};

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if ( actor == Actor0 && !player.hasQuest( getId() ) )
      Scene00000( player );
    if ( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
      Scene00002( player );
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    if ( npcId != Enemy0 )
      return;

    auto credit = player.getQuestUI8AL( getId() );
    if ( credit + 1 >= 6 )
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.sendQuestMessage( getId(), 0, 2, credit + 1, 6 );
      player.updateQuest( getId(), SeqFinish );
    }
    else
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.sendQuestMessage( getId(), 0, 2, credit + 1, 6 );
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                        {
                          Scene00001( player );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.updateQuest( getId(), Seq1 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                          if ( player.giveQuestRewards( getId(), result.param3 ) )
                          {
                            player.finishQuest( getId() );
                          }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst021 );