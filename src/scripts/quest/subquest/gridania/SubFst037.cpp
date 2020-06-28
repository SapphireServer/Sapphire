// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst037_00174
// Quest Name: No Quarter Given
// Quest ID: 65710
// Start NPC: 1000612
// End NPC: 1000612

using namespace Sapphire;

class SubFst037 : public Sapphire::ScriptAPI::EventScript
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
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000612;
    static constexpr auto Enemy0 = 192;   //743; <- WRONG INFO
    static constexpr auto Enemy1 = 193;   //744; <- WRONG INFO
    static constexpr auto Enemy2 = 194;   //745; <- WRONG INFO

  public:
    SubFst037() : Sapphire::ScriptAPI::EventScript( 65710 ){}; 
    ~SubFst037() {};

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
    auto credit = 0;

    switch( npcId )
    {
      case Enemy0:
      {
        credit = player.getQuestUI8AL( getId() );

        player.setQuestUI8AL( getId() , credit + 1 );
        if( credit + 1 <= 2 )
          player.sendQuestMessage( getId() , 0, 2, credit + 1, 2 );

        break;
      }
      case Enemy1:
      {
        credit = player.getQuestUI8BH( getId() );

        player.setQuestUI8BH( getId() , credit + 1 );
        if ( credit + 1 <= 2 )
          player.sendQuestMessage( getId() , 1, 2, credit + 1, 2 );

        break;
      }
      case Enemy2:
      {
        credit = player.getQuestUI8BL( getId() );

        player.setQuestUI8BL( getId() , credit + 1 );
        if ( credit + 1 <= 2 )
          player.sendQuestMessage( getId() , 2, 2, credit + 1, 2 );

        break;
      }
    }

    checkQuestCompletion( player );
  }

  void checkQuestCompletion( Entity::Player& player )
  {
    auto credit192 = player.getQuestUI8AL( getId() );
    auto credit193 = player.getQuestUI8BH( getId() );
    auto credit194 = player.getQuestUI8BL( getId() );

    if ( credit192 >= 2 && credit193 >= 2 && credit194 >= 2 )
      player.updateQuest( getId() , SeqFinish );
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
                        player.updateQuest( getId() , Seq1 );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                          if ( player.giveQuestRewards( getId() , result.param3 ) )
                          {
                            player.finishQuest( getId() );
                          }
                      } );
  }
};

EXPOSE_SCRIPT( SubFst037 );