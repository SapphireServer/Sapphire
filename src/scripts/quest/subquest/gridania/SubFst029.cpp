#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst029_00172
// Quest Name: More than a Flesh Wound
// Quest ID: 65708
// Start NPC: 1000430
// End NPC: 1000430

class SubFst029 :
  public Sapphire::ScriptAPI::EventScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // GetQuestUI8AH

  enum Sequence :
    uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Quest rewards
  static constexpr auto RewardExpFactor = 100;
  static constexpr auto RewardGil = 146;

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000430;
  static constexpr uint32_t Ritem0 = 4552;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor0 = 1;
  static constexpr auto Seq1Actor0Npctradeno = 99;
  static constexpr auto Seq1Actor0Npctradeok = 100;

public:
  SubFst029() : Sapphire::ScriptAPI::EventScript( 65708 )
  {};

  ~SubFst029()
  {};

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
    auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( actor == SubFst029::Actor0 && !player.hasQuest( getId() ) )
    {
       Scene00000( player );
    }
    if( actor == SubFst029::Actor0 && player.getQuestSeq ( getId() ) == 255 )
    {
       Scene00001( player );
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
                          player.updateQuest( getId(), SeqFinish );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 && player.collectHandInItems( { Ritem0 } ) )
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
                        if( player.giveQuestRewards( getId(), 0 ) )
                        {
                          player.finishQuest( getId() );
                        }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst029 );