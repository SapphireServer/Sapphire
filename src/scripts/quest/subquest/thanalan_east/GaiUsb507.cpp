// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsb507_00876
// Quest Name: Bringing out the Dead
// Quest ID: 66412
// Start NPC: 1003958
// End NPC: 1003958

using namespace Sapphire;

class GaiUsb507 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag16
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH
  // UI8CL
  // UI8DH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1006361
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1006353
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1006354
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 1007586
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1007599
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1007600
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    Seq5 = 5,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003958;//Eluned
  static constexpr auto Actor1 = 1006361;//Vesper Bay Shopkeep
  static constexpr auto Actor2 = 1006353;
  static constexpr auto Actor3 = 1006354;
  static constexpr auto Actor4 = 1007586;
  static constexpr auto Actor5 = 1007599;
  static constexpr auto Actor6 = 1007600;
  static constexpr auto Actor7 = 1007601;
  static constexpr auto Actor8 = 1007618;
  static constexpr auto Actor9 = 1007619;
  static constexpr auto Actor10 = 1006345;//Fallen Scion (Seq2)
  static constexpr auto Actor11 = 1006346;//Fallen Scion (Seq2)
  static constexpr auto Actor12 = 1006347;//Fallen Scion (Seq2)
  static constexpr auto Actor13 = 1006348;//Fallen Scion (Seq2)
  static constexpr auto Actor14 = 1007587;
  static constexpr auto Actor15 = 1007588;
  static constexpr auto Actor16 = 1007589;
  static constexpr auto Actor17 = 1006362;//Disconcerted Coachman
  static constexpr auto Actor18 = 1006349;//Fallen Scion (Seq4)
  static constexpr auto Actor19 = 1006344;//Fallen Sylph (Seq4)
  static constexpr auto Actor20 = 1007591;
  static constexpr auto Actor21 = 1007592;
  static constexpr auto Actor22 = 1007593;
  static constexpr auto Actor23 = 1007594;
  static constexpr auto Actor24 = 1006350;//Fallen Scion (Seq4)
  static constexpr auto Actor25 = 1006351;//Fallen Scion (Seq4)
  static constexpr auto Actor26 = 1007590;
  static constexpr auto Actor27 = 1007595;
  static constexpr auto Actor28 = 1007596;
  static constexpr auto Actor29 = 1007597;
  static constexpr auto EventActionProcessLong = 17;
  static constexpr auto EventActionProcessMiddle = 16;
  static constexpr auto EventActionProcessShor = 15;
  static constexpr auto Item0 = 2000685;
  static constexpr auto Item1 = 2001067;
  static constexpr auto Item2 = 2000686;

public:
  GaiUsb507() : Sapphire::ScriptAPI::QuestScript( 66412 ){};
  ~GaiUsb507() = default;

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
        else if( quest.getSeq() == SeqFinish )
          Scene00061( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
        break;
      }
      case Actor4:
      {
        break;
      }
      case Actor5:
      {
        break;
      }
      case Actor6:
      {
        break;
      }
      case Actor7:
      {
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
        break;
      }
      case Actor10:
      {
        if( quest.getSeq() == Seq2 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessLong,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00004( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor11:
      {
        if( quest.getSeq() == Seq2 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessMiddle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00006( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor12:
      {
        if( quest.getSeq() == Seq2 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessMiddle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00008( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor13:
      {
        if( quest.getSeq() == Seq2 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessShor,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00010( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor14:
      {
        break;
      }
      case Actor15:
      {
        break;
      }
      case Actor16:
      {
        break;
      }
      case Actor17:
      {
        if( quest.getSeq() == Seq2 )
          Scene00026( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00027( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00047( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00052( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00073( quest, player );
        break;
      }
      case Actor18:
      {
        if( quest.getSeq() == Seq4 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessMiddle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00030( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor19:
      {
        if( quest.getSeq() == Seq4 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessShor,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00032( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor20:
      {
        break;
      }
      case Actor21:
      {
        break;
      }
      case Actor22:
      {
        break;
      }
      case Actor23:
      {
        break;
      }
      case Actor24:
      {
        if( quest.getSeq() == Seq4 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessMiddle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00034( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor25:
      {
        if( quest.getSeq() == Seq4 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionProcessMiddle,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00036( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Actor26:
      {
        break;
      }
      case Actor27:
      {
        break;
      }
      case Actor28:
      {
        break;
      }
      case Actor29:
      {
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getSeq() == Seq2 )
    {
      eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 4 );
      if( quest.getUI8AL() >= 4 )
      {
        quest.setUI8AH( 0 );
        quest.setUI8AL( 0 );
        quest.setUI8BH( 4 );
        quest.setUI8BL( 0 );
        quest.setUI8CH( 0 );
        quest.setUI8CL( 0 );
        quest.setUI8DH( 0 );
        quest.setBitFlag16( 1, false );
        quest.setBitFlag16( 2, false );
        quest.setBitFlag16( 3, false );
        quest.setBitFlag16( 4, false );
        quest.setSeq( Seq3 );
      }
    }
    else if( quest.getSeq() == Seq4 )
    {
      eventMgr().sendEventNotice( player, getId(), 3, 2, quest.getUI8AH(), 4 );
      if( quest.getUI8AH() >= 4 )
      {
        quest.setUI8AH( 0 );
        quest.setUI8AL( 0 );
        quest.setUI8BH( 1 );
        quest.setUI8BL( 3 );
        quest.setUI8CH( 0 );
        quest.setUI8CL( 0 );
        quest.setUI8DH( 0 );
        quest.setBitFlag16( 1, false );
        quest.setBitFlag16( 2, false );
        quest.setBitFlag16( 11, false );
        quest.setBitFlag16( 12, false );
        quest.setSeq( Seq5 );
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &GaiUsb507::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );//Increment Journal
    quest.setUI8BH( quest.getUI8BH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 1, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &GaiUsb507::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );//Increment Journal
    quest.setUI8BH( quest.getUI8BH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 2, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &GaiUsb507::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );//Increment Journal
    quest.setUI8BH( quest.getUI8BH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 3, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &GaiUsb507::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );//Increment Journal
    quest.setUI8BH( quest.getUI8BH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 4, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &GaiUsb507::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &GaiUsb507::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &GaiUsb507::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &GaiUsb507::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &GaiUsb507::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &GaiUsb507::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &GaiUsb507::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &GaiUsb507::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &GaiUsb507::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &GaiUsb507::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &GaiUsb507::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &GaiUsb507::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &GaiUsb507::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &GaiUsb507::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &GaiUsb507::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00028( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setUI8BH( 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &GaiUsb507::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8DH( quest.getUI8DH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 1, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &GaiUsb507::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8CL( 1 );                   //Increment KeyItem
    quest.setBitFlag16( 2, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &GaiUsb507::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8DH( quest.getUI8DH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 11, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, NONE, bindSceneReturn( &GaiUsb507::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8DH( quest.getUI8DH() + 1 );//Increment KeyItem
    quest.setBitFlag16( 12, true );         //Hide EObj
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, NONE, bindSceneReturn( &GaiUsb507::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, NONE, bindSceneReturn( &GaiUsb507::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, NONE, bindSceneReturn( &GaiUsb507::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, NONE, bindSceneReturn( &GaiUsb507::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, NONE, bindSceneReturn( &GaiUsb507::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, NONE, bindSceneReturn( &GaiUsb507::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, NONE, bindSceneReturn( &GaiUsb507::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, NONE, bindSceneReturn( &GaiUsb507::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, NONE, bindSceneReturn( &GaiUsb507::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, NONE, bindSceneReturn( &GaiUsb507::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, NONE, bindSceneReturn( &GaiUsb507::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, NONE, bindSceneReturn( &GaiUsb507::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, NONE, bindSceneReturn( &GaiUsb507::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, NONE, bindSceneReturn( &GaiUsb507::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00052( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 52, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00052Return ) );
  }

  void Scene00052Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00053( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00053( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 53, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00053Return ) );
  }

  void Scene00053Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00054( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 54, NONE, bindSceneReturn( &GaiUsb507::Scene00054Return ) );
  }

  void Scene00054Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00055( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 55, NONE, bindSceneReturn( &GaiUsb507::Scene00055Return ) );
  }

  void Scene00055Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00056( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 56, NONE, bindSceneReturn( &GaiUsb507::Scene00056Return ) );
  }

  void Scene00056Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00057( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 57, NONE, bindSceneReturn( &GaiUsb507::Scene00057Return ) );
  }

  void Scene00057Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00058( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 58, NONE, bindSceneReturn( &GaiUsb507::Scene00058Return ) );
  }

  void Scene00058Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00059( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 59, NONE, bindSceneReturn( &GaiUsb507::Scene00059Return ) );
  }

  void Scene00059Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00060( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 60, NONE, bindSceneReturn( &GaiUsb507::Scene00060Return ) );
  }

  void Scene00060Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00061( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 61, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00061Return ) );
  }

  void Scene00061Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00062( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 62, NONE, bindSceneReturn( &GaiUsb507::Scene00062Return ) );
  }

  void Scene00062Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00063( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 63, NONE, bindSceneReturn( &GaiUsb507::Scene00063Return ) );
  }

  void Scene00063Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00064( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 64, NONE, bindSceneReturn( &GaiUsb507::Scene00064Return ) );
  }

  void Scene00064Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00065( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 65, NONE, bindSceneReturn( &GaiUsb507::Scene00065Return ) );
  }

  void Scene00065Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00066( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 66, NONE, bindSceneReturn( &GaiUsb507::Scene00066Return ) );
  }

  void Scene00066Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00067( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 67, NONE, bindSceneReturn( &GaiUsb507::Scene00067Return ) );
  }

  void Scene00067Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00068( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 68, NONE, bindSceneReturn( &GaiUsb507::Scene00068Return ) );
  }

  void Scene00068Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00069( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 69, NONE, bindSceneReturn( &GaiUsb507::Scene00069Return ) );
  }

  void Scene00069Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00070( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 70, NONE, bindSceneReturn( &GaiUsb507::Scene00070Return ) );
  }

  void Scene00070Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00071( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 71, NONE, bindSceneReturn( &GaiUsb507::Scene00071Return ) );
  }

  void Scene00071Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00072( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 72, NONE, bindSceneReturn( &GaiUsb507::Scene00072Return ) );
  }

  void Scene00072Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00073( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 73, HIDE_HOTBAR, bindSceneReturn( &GaiUsb507::Scene00073Return ) );
  }

  void Scene00073Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( GaiUsb507 );