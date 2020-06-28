// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst025_00103
// Quest Name: Death to the Bean Thieves
// Quest ID: 65639
// Start NPC: 1000627
// End NPC: 1000656

using namespace Sapphire;

class SubFst025 : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // GetQuestUI8AL
    // GetQuestUI8BH

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000627;
    static constexpr auto Actor1 = 1000656;
    static constexpr auto Enemy0 = 5;
    static constexpr auto Item0 = 2000075;

  public:
    SubFst025() : Sapphire::ScriptAPI::EventScript( 65639 ){}; 
    ~SubFst025() {};

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if ( actor == Actor0 && !player.hasQuest( getId() ) )
      Scene00000( player );
    if ( actor == Actor1 && player.getQuestSeq( getId() ) == SeqFinish )
      Scene00002( player );
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    if ( npcId != Enemy0 )
      return;

    auto credit = player.getQuestUI8AL( getId() );
    
    if ( credit + 1 >= 6 )
    {
      player.sendQuestMessage( getId(), 0, 2, credit + 1, 6 );
      player.setQuestUI8BH( getId(), credit + 1 );
      player.updateQuest( getId(), SeqFinish );
    }
    else
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.setQuestUI8BH( getId(), credit + 1 );
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
                          Scene00001( player );
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
                          Scene00003( player );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                          if ( player.giveQuestRewards( getId(), result.param3 ) )
                          {
                            player.finishQuest( getId() );
                          }
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }
};

EXPOSE_SCRIPT( SubFst025 );