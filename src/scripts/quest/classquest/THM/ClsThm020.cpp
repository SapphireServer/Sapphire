// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsThm020_00345
// Quest Name: Way of the Thaumaturge
// Quest ID: 65881
// Start NPC: 1002279 (Yayake)
// End NPC: 1001708 (Cocobuki)

using namespace Sapphire;

class ClsThm020 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1001709
  /// Countable Num: 3 Seq: 2 Event: 5 Listener: 351
  /// Countable Num: 3 Seq: 2 Event: 5 Listener: 385
  /// Countable Num: 3 Seq: 2 Event: 5 Listener: 205
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1001708
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1002279;        // Yayake ( Pos: -196.886993 18.459999 59.952599  Teri: 130 )
  static constexpr auto Actor1 = 1001709;        // Cocobygo ( Pos: -240.473999 18.700001 85.611702  Teri: 130 )
  static constexpr auto Actor2 = 1001708;        // Cocobuki ( Pos: -250.347000 18.000000 80.903603  Teri: 130 )
  static constexpr auto enemyStarMarmot = 262;   // Star Marmots
  static constexpr auto enemyHugeHornet = 632;   // Huge Hornets
  static constexpr auto enemySnappingShrew = 318;// Snapping Shrews
  static constexpr auto LocActor1 = 1001708;     // Cocobuki ( Pos: -250.347000 18.000000 80.903603  Teri: 130 )
  static constexpr auto LocActor2 = 1001709;     // Cocobygo ( Pos: -240.473999 18.700001 85.611702  Teri: 130 )
  static constexpr auto LocActor3 = 1001710;     // Cocobani ( Pos: -240.251007 18.799999 86.916702  Teri: 130 )
  static constexpr auto LocActor4 = 1001711;     // Cocobezi ( Pos: -241.621002 18.799999 83.356400  Teri: 130 )
  static constexpr auto LocActor5 = 1001712;     // Cocoboha ( Pos: -241.473999 19.577299 84.641701  Teri: 130 )
  static constexpr auto LocPosActor3 = 3996617;  //
  static constexpr auto LocPosActor4 = 3996618;  //
  static constexpr auto LocPosActor5 = 3996619;  //
  static constexpr auto LogmessageMonsterNotePageUnlock = 1014;
  static constexpr auto UnlockImageMonsterNote = 32;

public:
  ClsThm020() : Sapphire::ScriptAPI::QuestScript( 65881 ){};
  ~ClsThm020() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
        {
          Scene00000( quest, player );
        }
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
        {
          Scene00003( quest, player );
        }
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
        {
          Scene00004( quest, player );
        }
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq2 )
    {
      switch( bnpc.getBNpcNameId() )
      {
        case enemyStarMarmot:
        {
          if( quest.getUI8AL() < 3 )
          {
            quest.setUI8AL( quest.getUI8AL() + 1 );
            eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 3 );
          }
          break;
        }
        case enemyHugeHornet:
        {
          if( quest.getUI8BH() < 3 )
          {
            quest.setUI8BH( quest.getUI8BH() + 1 );
            eventMgr().sendEventNotice( player, getId(), 2, 2, quest.getUI8BH(), 3 );
          }
          break;
        }
        case enemySnappingShrew:
        {
          if( quest.getUI8BL() < 3 )
          {
            quest.setUI8BL( quest.getUI8BL() + 1 );
            eventMgr().sendEventNotice( player, getId(), 3, 2, quest.getUI8BL(), 3 );
          }
          break;
        }
      }
      if( quest.getUI8AL() == 3 && quest.getUI8BH() == 3 && quest.getUI8BL() == 3 )
      {
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsThm020::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
      Scene00001( quest, player );
    }
    else
    {
      Scene00002( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsThm020::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsThm020::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | HIDE_UI | INVIS_ENPC | SET_INVIS_BASE | DISABLE_SKIP, bindSceneReturn( &ClsThm020::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      quest.setSeq( Seq2 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsThm020::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.setRewardFlag( Sapphire::Common::UnlockEntry::HuntingLog );
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsThm020 );