// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include <Inventory/Item.h>

// Quest Script: SubWil129_00574
// Quest Name: Dressed to Deceive
// Quest ID: 66110
// Start NPC: 1003929
// End NPC: 1005116

using namespace Sapphire;

class SubWil129 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1003947
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1004325
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1004327
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1004506
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003929;//Isembard
  static constexpr auto Actor1 = 1003947;//Knerl
  static constexpr auto Actor2 = 1004325;//Swaenhylt
  static constexpr auto Actor3 = 1004327;//Aurildis
  static constexpr auto Actor4 = 1004506;//Ermegarde
  static constexpr auto Actor5 = 1004556;//Adelstan
  static constexpr auto Actor6 = 1004324;//Thancred(Seq1/Seq2)
  static constexpr auto Actor7 = 1004330;//Thancred(Seq3)
  static constexpr auto Actor8 = 1005116;//Minfilia
  static constexpr auto LocActor0 = 1005015;
  static constexpr auto LocActor1 = 1004580;
  static constexpr auto LocActor2 = 1004581;
  static constexpr auto LocActor3 = 1003932;
  static constexpr auto LocFace0 = 604;
  static constexpr auto LocFace1 = 617;
  static constexpr auto LocFace2 = 605;
  static constexpr auto LocPosActor1 = 3967322;
  static constexpr auto Ritem0 = 2995;//Weathered Shepard's Tunic
  static constexpr auto Ritem1 = 3306;//Weathered Shepard's Slops
  static constexpr auto Seq0Actor0Lq = 90;

public:
  SubWil129() : Sapphire::ScriptAPI::QuestScript( 66110 ){};
  ~SubWil129() = default;

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
        else if( quest.getSeq() == Seq1 )
          Scene00018( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00023( quest, player );
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
        if( quest.getSeq() == Seq1 )
          Scene00005( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00008( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq1 )
          Scene00011( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq1 )
          Scene00014( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq1 )
          Scene00017( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00019( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq3 )
          Scene00020( quest, player );
        break;
      }
      case Actor8:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00024( quest, player );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
    if( quest.getUI8AL() >= 5 )
    {
      quest.setUI8BH( quest.getUI8CH() );
      quest.setSeq( Seq2 );
      quest.setUI8AL( 0 );
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
      quest.setBitFlag8( 4, false );
      quest.setBitFlag8( 5, false );
    }
  }

  bool checkPlayerCorrectEquipment( Entity::Player& player )
  {
    auto bodyEquipped = player.getItemAt( Sapphire::Common::InventoryType::GearSet0, Sapphire::Common::GearSetSlot::Body );
    auto legsEquipped = player.getItemAt( Sapphire::Common::InventoryType::GearSet0, Sapphire::Common::GearSetSlot::Legs );

    if( bodyEquipped && legsEquipped && bodyEquipped->getId() == Ritem0 && legsEquipped->getId() == Ritem1 )
      return true;
    else
      return false;
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &SubWil129::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    player.addItem( Ritem0, 1 );
    player.addItem( Ritem1, 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( checkPlayerCorrectEquipment( player ) )
      Scene00003( quest, player );
    else
      Scene00004( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setBitFlag8( 1, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( checkPlayerCorrectEquipment( player ) )
      Scene00006( quest, player );
    else
      Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setBitFlag8( 2, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( checkPlayerCorrectEquipment( player ) )
      Scene00009( quest, player );
    else
      Scene00010( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setBitFlag8( 3, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( checkPlayerCorrectEquipment( player ) )
      Scene00012( quest, player );
    else
      Scene00013( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setBitFlag8( 4, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( checkPlayerCorrectEquipment( player ) )
      Scene00015( quest, player );
    else
      Scene00016( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setBitFlag8( 5, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Inventory::InventoryContainerPair pair;
    bool hasBody = player.findFirstItemWithId( Ritem0, pair );
    bool hasLegs = player.findFirstItemWithId( Ritem1, pair );
    if( !hasBody )
      player.addItem( Ritem0 );
    if( !hasLegs )
      player.addItem( Ritem1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( checkPlayerCorrectEquipment( player ) )
      Scene00021( quest, player );
    else
      Scene00022( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &SubWil129::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Inventory::InventoryContainerPair pair;
    bool hasBody = player.findFirstItemWithId( Ritem0, pair );
    bool hasLegs = player.findFirstItemWithId( Ritem1, pair );
    if( !hasBody )
      player.addItem( Ritem0 );
    if( !hasLegs )
      player.addItem( Ritem1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &SubWil129::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubWil129 );