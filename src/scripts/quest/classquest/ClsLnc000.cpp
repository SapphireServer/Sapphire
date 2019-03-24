#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: ClsLnc000_00023
// Quest Name: Way of the Lancer
// Quest ID: 65559
// Start NPC: 1000251
// End NPC: 1000254

class ClsLnc000 : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic quest information
    // Quest vars / flags used
    // GetQuestUI8AL
    // GetQuestUI8BH
    // GetQuestUI8BL

    // Steps in this quest ( 0 is before accepting,
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
       Seq0 = 0,
       Seq1 = 1,
       Seq2 = 2,
       SeqFinish = 255,
    };

    // Quest rewards
    static constexpr auto RewardExpFactor = 100;
    static constexpr auto RewardItem = { 4639, 0, 0, 0, 0, 0 };
    static constexpr auto RewardItemCount = { 5, 0, 0, 0, 0, 0 };
    static constexpr auto RewardItemOptional = { 0, 0, 0, 0, 0 };
    static constexpr auto RewardItemOptionalCount = { 0, 0, 0, 0, 0 };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000251;
    static constexpr auto Actor1 = 1000254;
    static constexpr auto Enemy0 = 37;
    static constexpr auto Enemy1 = 49;
    static constexpr auto Enemy2 = 47;
    static constexpr auto LogmessageMonsterNotePageUnlock = 1007;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq1Actor1 = 1;
    static constexpr auto Seq3Actor1 = 2;
    static constexpr auto UnlockImageMonsterNote = 32;

  public:
    ClsLnc000() : Sapphire::ScriptAPI::EventScript( 65559 ){};
    ~ClsLnc000(){};

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = framework()->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == Actor0 )
    {
      if( !player.hasQuest( getId() ) )
        Scene00000( player );
      else
        Scene00002( player );

    }
    else if( actor == Actor1 && player.getQuestSeq( getId() ) != SeqFinish)
    {
      Scene00001( player );
    }
    else if( actor == Actor1 && player.getQuestSeq( getId() ) == SeqFinish )
    {
      Scene00002( player );
    }
  }

  bool checkCompletion( Entity::Player& player )
  {
    auto al = player.getQuestUI8AL( getId() );
    auto bh = player.getQuestUI8BH( getId() );
    auto bl = player.getQuestUI8BL( getId() );
    return al == 3 && bh == 3 && bl == 3;
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {

    auto al = player.getQuestUI8AL( getId() );
    auto bh = player.getQuestUI8BH( getId() );
    auto bl = player.getQuestUI8BL( getId() );

    switch( npcId )
    {
      case Enemy0:
        if( al < 3 )
        {
          player.setQuestUI8AL( getId(), ++al );
          player.sendQuestMessage( getId(), 0, 2, al, 3 );
        }

        break;
      case Enemy1:
        if( bh < 3 )
        {
          player.setQuestUI8BH( getId(), ++bh );
          player.sendQuestMessage( getId(), 1, 2, bh, 3 );
        }

        break;
      case Enemy2:
        if( bl < 3 )
        {
          player.setQuestUI8BL( getId(), ++bl );
          player.sendQuestMessage( getId(), 2, 2, bl, 3 );
        }

        break;
    }

    if( checkCompletion( player ) )
    {
      player.updateQuest( getId(), SeqFinish );
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
                        if( result.param2 == 1 ) // accept quest
                          player.updateQuest( getId(), Seq1 );

                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1,  FADE_OUT | HIDE_HOTBAR | CONDITION_CUTSCENE | HIDE_UI,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param1 == 256 ) // accept quest
                          player.updateQuest( getId(), Seq2 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          if( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.finishQuest( getId() );
                            player.learnAction( 21 );
                          }
                        }
                      } );
  }

};

EXPOSE_SCRIPT( ClsLnc000 );