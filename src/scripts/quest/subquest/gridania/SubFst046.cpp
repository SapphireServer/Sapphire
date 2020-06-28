// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst046_00210
// Quest Name: Idle Initiatives
// Quest ID: 65746
// Start NPC: 1000408
// End NPC: 1000408

using namespace Sapphire;

class SubFst046 :
  public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // GetQuestBitFlag8
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
    static constexpr auto ActionTimelineEventBaseIdle = 783;
    static constexpr auto Actor0 = 1000408;
    static constexpr auto Actor1 = 1000792;
    static constexpr auto Actor2 = 1000793;
    static constexpr auto Actor3 = 1000794;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq1Actor1 = 1;
    static constexpr auto Seq1Actor2 = 2;
    static constexpr auto Seq1Actor3 = 3;
    static constexpr auto Seq2Actor0 = 4;

  public:
    SubFst046() : Sapphire::ScriptAPI::EventScript( 65746 ){}; 
    ~SubFst046() {};

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if ( actor == Actor0 && !player.hasQuest( getId() ) )
      Scene00000( player );
    if ( actor == Actor1 )
      Scene00001( player );
    if ( actor == Actor2 )
      Scene00002( player );
    if ( actor == Actor3 )
      Scene00003( player );
    if ( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
      Scene00004( player );
  }

  void checkQuestCompletion( Entity::Player& player )
  {
    auto credit = player.getQuestUI8AL( getId() );

    if ( credit + 1 >= 3 )
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.sendQuestMessage( getId(), 0, 0, credit + 1, 3 );
      player.updateQuest( getId(), SeqFinish );
    }
    else
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.sendQuestMessage( getId(), 0, 0, credit + 1, 3 );
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                        {
                          player.updateQuest( getId(), Seq1 );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 1, true );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 2, true );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 3, true );
                      } );
  }

  void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                        {
                          if ( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.setQuestUI8BH( getId(), 0 );
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst046 );