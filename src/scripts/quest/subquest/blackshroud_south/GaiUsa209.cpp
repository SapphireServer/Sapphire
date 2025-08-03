// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include "Manager/PlayerMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include "Util/UtilMath.h"

// Quest Script: GaiUsa209_00732
// Quest Name: Stash Saboteur
// Quest ID: 66268
// Start NPC: 1000598 (Auphiliot)
// End NPC: 1000598 (Auphiliot)

using namespace Sapphire;

class GaiUsa209 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AH
    // UI8AL
    // UI8BH
    // UI8BL
    // UI8CH

    /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2001942
    /// Countable Num: 0 Seq: 255 Event: 8 Listener: 2001942
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000598; // Auphiliot ( Pos: -170.809998 9.964130 -84.129402  Teri: 153 )
    static constexpr auto Eobject0 = 2001942; // Storage Case ( Pos: -287.321014 24.902500 -194.147995  Teri: 153 )
    static constexpr auto Eobject1 = 2001943; // Storage Case ( Pos: -294.333008 24.268900 -207.630997  Teri: 153 )
    static constexpr auto Eobject2 = 2001944; // Storage Case ( Pos: -294.175995 25.021999 -194.072006  Teri: 153 )
    static constexpr auto Item0 = 2000586;

  public:
    GaiUsa209() : Sapphire::ScriptAPI::QuestScript( 66268 ){}; 
    ~GaiUsa209() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        if( quest.getSeq() == SeqFinish )
          Scene00008( quest, player );
        break;
      }
    }
  }

  void onEventGroundItem( World::Quest& quest, Entity::Player& player, Common::FFXIVARR_POSITION3 pos ) override
  {
    Common::FFXIVARR_POSITION3 Eobj0Pos = { -287.321014f, 24.902500f, -194.147995f };
    Common::FFXIVARR_POSITION3 Eobj1Pos = { -294.333008f, 24.268900f, -207.630997f };
    Common::FFXIVARR_POSITION3 Eobj2Pos = { -294.175995f, 25.021999f, -194.072006f };

    uint8_t hitTargets = 0;
    if( quest.getUI8AL() == 0 )
    {
      if( Sapphire::Common::Util::distance( pos, Eobj0Pos ) <= 1 )
      {
        Scene00003( quest, player );
        hitTargets++;
      }
    }
    else
    {
      hitTargets++;
    }

    if( quest.getUI8BH() == 0 )
    {
      if( Sapphire::Common::Util::distance( pos, Eobj1Pos ) <= 1 )
      {
        Scene00005( quest, player );
        hitTargets++;
      }
    }
    else
    {
      hitTargets++;
    }

    if( quest.getUI8BL() == 0 )
    {
      if( Sapphire::Common::Util::distance( pos, Eobj2Pos ) <= 1 )
      {
        Scene00007( quest, player );
        hitTargets++;
      }
    }
    else
    {
      hitTargets++;
    }

    if( quest.getUI8AH() != hitTargets )
    {
      quest.setUI8CH( 3 - hitTargets );
      quest.setUI8AH( hitTargets );
      eventMgr().sendEventNotice( player, getId(), 0, 2, hitTargets, 3 );

      if( hitTargets == 3 )
      {
        quest.setUI8AL( 0 );
        quest.setUI8BH( 0 );
        quest.setUI8BL( 0 );
        quest.setBitFlag8( 1, false );
        quest.setBitFlag8( 2, false );
        quest.setBitFlag8( 3, false );
        quest.setSeq( SeqFinish );
      }
    }
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &GaiUsa209::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8CH( 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsa209::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &GaiUsa209::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &GaiUsa209::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    quest.setBitFlag8( 3, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &GaiUsa209::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( GaiUsa209 );