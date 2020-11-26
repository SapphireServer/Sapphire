#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: SubFst042_00198
// Quest Name: Butcher of Greentear
// Quest ID: 65734
// Start NPC: 1000685
// End NPC: 1000685

class SubFst042 : public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information 
  // Quest vars / flags used
  // GetQuestUI8AL

  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Quest rewards 
  static constexpr auto RewardExpFactor = 200;
  uint32_t RewardItemOptional[3] = { 4092, 4091, 5824 };
  uint32_t RewardItemOptionalCount[3] = { 1, 1, 1 };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000685;
  static constexpr auto Enemy0 = 14;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq2Actor0 = 1;

public:
  SubFst042() : Sapphire::ScriptAPI::EventScript( 65734 ){};
  ~SubFst042(){};

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

    if ( actor == Actor0 && !player.hasQuest( getId() ) )
    {
      Scene00000( player );
    }
    else if ( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
    {
      Scene00001( player );
    }
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    if ( npcId != Enemy0 )
      return;

    auto currentKC = player.getQuestUI8AL( getId() ) + 1;

    if ( currentKC >= 6 )
      player.updateQuest( getId(), SeqFinish );
    else
    {
      player.setQuestUI8AL( getId(), currentKC );
      player.sendQuestMessage( getId(), 0, 2, currentKC, 6 );
    }
  }

private:

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                          player.updateQuest( getId(), 1 );
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                        {
                          if ( player.giveQuestRewards( getId(), 0 ) )
                            player.finishQuest( getId() );
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst042 );