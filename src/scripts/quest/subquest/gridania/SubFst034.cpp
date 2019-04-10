#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;


// Quest Script: SubFst034_00128
// Quest Name: Eggs over Queasy
// Quest ID: 65664
// Start NPC: 1000421
// End NPC: 1000449

class SubFst034 : public Sapphire::ScriptAPI::EventScript
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

    // Quest rewards 
    static constexpr auto RewardExpFactor = 200;
    static constexpr auto RewardGil = 151;
    static constexpr auto RewardItem = { 4552, 0, 0, 0, 0, 0 };
    static constexpr auto RewardItemCount = { 1, 0, 0, 0, 0, 0 };
    static constexpr auto RewardItemOptional = { 0, 0, 0, 0, 0 };
    static constexpr auto RewardItemOptionalCount = { 0, 0, 0, 0, 0 };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000421;
    static constexpr auto Actor1 = 1000449;
    static constexpr auto Enemy0 = 43;
    static constexpr auto Item0 = 2000062;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq2Actor1 = 1;
    static constexpr auto Seq2Actor1Npctradeno = 99;
    static constexpr auto Seq2Actor1Npctradeok = 100;

  public:
    SubFst034() : Sapphire::ScriptAPI::EventScript( 65664 ){}; 
    ~SubFst034() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == Actor0 && !player.hasQuest( getId() ) )
    {
      Scene00000( player );
    }

    if( actor == Actor1 )
    {
      player.setQuestUI8BH( getId(), 8 );
      Scene00001( player );
    }

  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player )
  {
    switch( npcId )
    {
      case Enemy0:
      {
        if( player.getQuestSeq( getId() ) != Seq1 )
          return;
        auto currentKC = player.getQuestUI8AL( getId() ) + 1;

        if( currentKC >= 8 )
        {
          player.updateQuest( getId(), SeqFinish );
          player.setQuestUI8BH( getId(), 8 );
        }
        else
        {
          player.setQuestUI8AL( getId(), currentKC );
          player.setQuestUI8BH( getId(), currentKC );
        }
        player.sendQuestMessage( getId(), 0, 2, currentKC, 8 );

        break;
      }
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
          player.updateQuest( getId(), Seq1 );
        }
      });
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, 0,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param1 == 0 )
          Scene00099( player );
        else
          Scene00100( player );
      });
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, 0,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
      });
  }

  void Scene00100( Entity::Player& player )
  {
    player.playScene( getId(), 100, 0,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param2 == 1 )
        {
          if( player.giveQuestRewards( getId(), 0 ) )
          {
            player.finishQuest( getId() );
          }
        }
      });
  }

};

EXPOSE_SCRIPT( SubFst034 );