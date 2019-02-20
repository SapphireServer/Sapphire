#include <ScriptObject.h>
#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst013_00040
// Quest Name: For Friendship
// Quest ID: 65576
// Start NPC: 1000162
// End NPC: 1000162

class SubFst013 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_1 = 1;
  static constexpr auto SEQ_2 = 2;
  static constexpr auto SEQ_3 = 3;
  static constexpr auto SEQ_4 = 4;
  static constexpr auto SEQ_5 = 5;
  static constexpr auto SEQ_FINISH = 255;


  // Entities found in the script data of the quest
  static constexpr auto ACTOR0 = 1000162;
  static constexpr auto ACTOR1 = 1000161;
  static constexpr auto FIRST_QUEST = 65575;
  static constexpr auto SEQ_0_ACTOR0 = 0;
  static constexpr auto SEQ_1_ACTOR1 = 1;
  static constexpr auto SEQ_1_ACTOR1_EMOTENO = 99;
  static constexpr auto SEQ_1_ACTOR1_EMOTEOK = 100;
  static constexpr auto SEQ_2_ACTOR0 = 2;
  static constexpr auto SEQ_3_ACTOR1 = 3;
  static constexpr auto SEQ_3_ACTOR1_EMOTENO = 97;
  static constexpr auto SEQ_3_ACTOR1_EMOTEOK = 98;
  static constexpr auto SEQ_4_ACTOR0 = 4;
  static constexpr auto SEQ_5_ACTOR1 = 5;
  static constexpr auto SEQ_5_ACTOR1_EMOTENO = 95;
  static constexpr auto SEQ_5_ACTOR1_EMOTEOK = 96;
  static constexpr auto SEQ_6_ACTOR0 = 6;

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 )
      {
        player.updateQuest( getId(), SEQ_1 );
      }
    };

    player.playScene( getId(), 0, NONE, callback );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 2, NONE );
  }

  void Scene00002( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), SEQ_3 );
    };

    player.playScene( getId(), 2, NONE, callback );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, NONE );
  }

  void Scene00004( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), SEQ_5 );
    };

    player.playScene( getId(), 4, NONE, callback );
  }

  void Scene00005( Entity::Player& player )
  {
    player.playScene( getId(), 5, NONE );
  }

  void Scene00006( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 == 1 ) // finish quest
      {
        if( player.giveQuestRewards( getId(), 0 ) )
          player.finishQuest( getId() );
      }
    };

    player.playScene( getId(), 6, NONE, callback );
  }

  void Scene00095( Entity::Player& player )
  {
    player.playScene( getId(), 95, NONE );
  }

  void Scene00096( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), SEQ_FINISH );
      player.sendQuestMessage( getId(), 4, 2, 0, 0 );
    };

    player.playScene( getId(), 96, NONE, callback );
  }

  void Scene00097( Entity::Player& player )
  {
    player.playScene( getId(), 97, NONE );
  }

  void Scene00098( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), SEQ_4 );
      player.sendQuestMessage( getId(), 2, 2, 0, 0 );
    };

    player.playScene( getId(), 98, NONE, callback );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, NONE );
  }

  void Scene00100( Entity::Player& player )
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.updateQuest( getId(), SEQ_2 );
      player.sendQuestMessage( getId(), 0, 2, 0, 0 );
    };

    player.playScene( getId(), 100, NONE, callback );
  }


public:
  SubFst013() :
    Sapphire::ScriptAPI::EventScript( 65576 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( !player.hasQuest( getId() ) )
    {
      Scene00000( player );
      return;
    }

    if( actor == ACTOR1 ) // talking to Aunillie while on quest
      Scene00003( player );
    else if( actor == ACTOR0 && player.getQuestSeq( getId() ) == SEQ_2 )
      Scene00002( player );
    else if( actor == ACTOR0 && player.getQuestSeq( getId() ) == SEQ_4 )
      Scene00004( player );
    else if( actor == ACTOR0 && player.getQuestSeq( getId() ) == SEQ_FINISH )
      Scene00006( player );
  }

  void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == ACTOR1 && emoteId == 5 && player.getQuestSeq( getId() ) == SEQ_1 )
      Scene00100( player );
    else if( actor == ACTOR1 && emoteId == 18 && player.getQuestSeq( getId() ) == SEQ_3 )
      Scene00098( player );
    else if( actor == ACTOR1 && emoteId == 11 && player.getQuestSeq( getId() ) == SEQ_5 )
      Scene00096( player );
  }
};

EXPOSE_SCRIPT( SubFst013 );