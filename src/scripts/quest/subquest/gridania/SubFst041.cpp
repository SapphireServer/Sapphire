#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: SubFst041_00197
// Quest Name: Splitting Shells
// Quest ID: 65733
// Start NPC: 1000432
// End NPC: 1000411

class SubFst041 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestUI8AL
  // GetQuestUI8BH

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  uint32_t RewardItemOptional[3] = { 4657, 4658, 5823 };
  uint32_t RewardItemOptionalCount[3] = { 3, 3, 3 };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000432;
  static constexpr auto Actor1 = 1000411;
  static constexpr auto Enemy0 = 197;  //159; WRONG INFO
  static constexpr auto Item0 = 2000142;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq2Actor1 = 1;
  static constexpr auto Seq2Actor1Npctradeno = 99;
  static constexpr auto Seq2Actor1Npctradeok = 100;

public:
  SubFst041() :
    Sapphire::ScriptAPI::EventScript( 65733 )
  {
  };

  ~SubFst041()
  {
  };

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == Actor0 )
      Scene00000( player );
    if( actor == Actor1 )
      Scene00001( player );
  }

  void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
  {
    if( npcId != Enemy0 )
      return;

    auto currentKC = player.getQuestUI8BH( getId() );

    if ( currentKC + 1 >= 4 )
    {
      player.setQuestUI8AL( getId(), currentKC + 1 );
      player.setQuestUI8BH( getId(), currentKC + 1 );
      player.sendQuestMessage( getId(), 1, 0, 0, 0 );
      player.updateQuest( getId(), SeqFinish );
    }
    else
    {
      player.setQuestUI8AL( getId(), currentKC + 1 );
      player.setQuestUI8BH( getId(), currentKC + 1 );
      player.sendQuestMessage( getId(), 0, 2, currentKC + 1, 4 );
    }
  }

private:

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
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
                        if( result.param2 == 1 )
                        {
                          Scene00100( player );
                        }
                        else
                        {
                          Scene00099( player );
                        }
                      } );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.playScene( getId(), 99, 0, 0, 0 );
                      } );
  }

  void Scene00100( Entity::Player& player )
  {
    player.playScene( getId(), 100, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                        {
                          if( player.giveQuestRewards( getId(), result.param3 ) )
                          {
                            player.setQuestUI8BH( getId(), 0 );
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst041 );