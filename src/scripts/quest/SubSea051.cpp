#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: SubSea051_00463
// Quest Name: Dressed to Call
// Quest ID: 65999
// Start NPC: 1002626
// End NPC: 1002626

class SubSea051 : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // GetQuestUI8AL

    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002626;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq1Actor0 = 1;

  public:
    SubSea051() : Sapphire::ScriptAPI::EventScript( 65999 ){}; 
    ~SubSea051() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    //auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    //auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    if( player.getQuestSeq( getId() ) == 0 )
    {
      Scene00000( player );
    }
    else
    {
      Scene00001( player );
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
          player.updateQuest( getId(), Sequence::SeqFinish );
        }
      });
  }

  void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, 0,
      [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        if( result.param2 == 1 )
        {
          if( player.giveQuestRewards( getId(), result.param3 ) )
          {
            player.finishQuest( getId() );
          }
        }
      });
  }

};

EXPOSE_SCRIPT( SubSea051 );