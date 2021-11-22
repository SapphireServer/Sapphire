// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst043_00199
// Quest Name: A Clear Sign
// Quest ID: 65735
// Start NPC: 1000172
// End NPC: 1000627

using namespace Sapphire;

class SubFst043 : public Sapphire::ScriptAPI::EventScript
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
    static constexpr auto Actor0 = 1000172;
    static constexpr auto Actor1 = 1000627;
    static constexpr auto Eobject0 = 2000143;
    static constexpr auto Eobject1 = 2000144;
    static constexpr auto EventActionProcessMiddle = 16;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq1Eobject0 = 1;
    static constexpr auto Seq1Eobject0Eventactionno = 99;
    static constexpr auto Seq1Eobject0Eventactionok = 100;
    static constexpr auto Seq1Eobject1 = 2;
    static constexpr auto Seq1Eobject1Eventactionno = 97;
    static constexpr auto Seq1Eobject1Eventactionok = 98;
    static constexpr auto Seq2Actor1 = 3;

  public:
    SubFst043() : Sapphire::ScriptAPI::EventScript( 65735 ){}; 
    ~SubFst043() {};

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if ( actor == Actor0 )
      Scene00000( player );
    else if (actor == Actor1 && player.getQuestSeq( getId() ) == SeqFinish )
      Scene00003( player );
    else if ( actor == Eobject0 )
      player.eventActionStart( getId(), EventActionProcessMiddle,
                               [&]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00001( player );
                               },
                                   nullptr, eventId );
    else if ( actor == Eobject1 )
      player.eventActionStart( getId(), EventActionProcessMiddle,
                               [&]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                               {
                                 Scene00002( player );
                               },
                                   nullptr, eventId );
  }

  void checkQuestCompletion( Entity::Player& player )
  {
    auto credit = player.getQuestUI8AL( getId() );

    if ( credit + 1 >= 2 )
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.sendQuestMessage( getId(), 0, 2, credit + 1, 2 );
      player.updateQuest( getId(), SeqFinish );
    }
    else
    {
      player.setQuestUI8AL( getId(), credit + 1 );
      player.sendQuestMessage( getId(), 0, 2, credit + 1, 2 );
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
                          player.updateQuest( getId(), Seq1 );
                        }
                      } );
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00100( player );
                      } );
  }

  void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        Scene00098( player );
                      } );
  }

  void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if ( result.param2 == 1 )
                        {
                          if ( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.setQuestUI8BH( getId(), 0 );
                            player.finishQuest( getId() );
                          }
                        }
                      });
  }

  void Scene00097( Entity::Player& player )
  {
    player.playScene( getId(), 97, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00098( Entity::Player& player )
  {
    player.playScene( getId(), 98, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 2, true );
                      } );
  }

  void Scene00099( Entity::Player& player )
  {
    player.playScene( getId(), 99, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

  void Scene00100( Entity::Player& player )
  {
    player.playScene( getId(), 100, HIDE_HOTBAR,
                      [&]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        checkQuestCompletion( player );
                        player.setQuestBitFlag8( getId(), 1, true );
                      } );
  }
};

EXPOSE_SCRIPT( SubFst043 );