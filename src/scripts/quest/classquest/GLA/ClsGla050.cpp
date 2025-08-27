// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsGla050_00256
// Quest Name: Kicking the Hornet's Nest
// Quest ID: 65792
// Start NPC: 1001739 (Mylla)
// End NPC: 1001739 (Mylla)

using namespace Sapphire;

class ClsGla050 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AH
    // UI8AL
    // UI8BH
    // UI8BL

    /// Countable Num: 4 Seq: 1 Event: 1 Listener: 1003984
    /// Countable Num: 1 Seq: 2 Event: 2 Listener: 1003984
    /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1003990
    /// Countable Num: 1 Seq: 4 Event: 2 Listener: 1003990
    /// Countable Num: 1 Seq: 5 Event: 1 Listener: 1003992
    /// Countable Num: 1 Seq: 6 Event: 2 Listener: 1003992
    /// Countable Num: 1 Seq: 7 Event: 1 Listener: 1003994
    /// Countable Num: 0 Seq: 255 Event: 2 Listener: 1003994
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
      Seq6 = 6,
      Seq7 = 7,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001739; // Mylla ( Pos: -94.529701 6.499970 39.810699  Teri: 131 )
    static constexpr auto Actor1 = 1003984; // Ill-mannered Marauder ( Pos: 45.056900 4.000000 -128.156006  Teri: 130 )
    static constexpr auto Actor2 = 1003990; // Menacing Marauder ( Pos: 77.259300 4.099990 -138.602005  Teri: 130 )
    static constexpr auto Actor3 = 1003992; // Keen-eyed Marauder ( Pos: 12.207600 4.074110 -155.528000  Teri: 130 )
    static constexpr auto Actor4 = 1003994; // Mocking Marauder ( Pos: 16.001801 7.980420 -124.067001  Teri: 130 )
    static constexpr auto Actor5 = 1003983; // ×1001ウルダハ ( Pos: 45.179798 4.000000 -127.156998  Teri: 130 )
    static constexpr auto Actor6 = 1003991; // ×1009ウルダハ ( Pos: 10.696000 4.074110 -156.438995  Teri: 130 )
    static constexpr auto Actor7 = 1003993; // ×1011ウルダハ ( Pos: 15.802900 7.999980 -122.564003  Teri: 130 )
    static constexpr auto Actor8 = 1003989; // ×1007ウルダハ ( Pos: 77.207703 4.099990 -140.341003  Teri: 130 )
    static constexpr auto Actor9 = 1004222; // Pfarmurl ( Pos: 21.930000 7.200000 -97.370003  Teri: 130 )
    static constexpr auto Actor10 = 1004236; // Frolicsome Dancer ( Pos: 21.070000 7.200000 -99.480003  Teri: 130 )
    static constexpr auto Actor11 = 1004223; // Stately Gentleman ( Pos: 24.142300 7.205100 -102.765999  Teri: 130 )
    static constexpr auto Actor12 = 1001353; // Momodi ( Pos: 21.072599 7.450000 -78.782303  Teri: 130 )
    static constexpr auto Actor13 = 1003985; // Nervous Merchant ( Pos: 201.526001 52.017899 149.432007  Teri: 140 )
    static constexpr auto Actor14 = 1006018; // Chocobo ( Pos: 137.339996 52.730000 223.759995  Teri: 140 )
    static constexpr auto CutScene01 = 34; // ???
    static constexpr auto Enemy0 = 3968834; // murderous marauder nameId: 1179
    static constexpr auto Enemy1 = 4148249; // Pfarmurl the Driven nameId: 1178
    static constexpr Common::QuestEobject Eobject0 = { 2001725, 140, { 200.677994, 52.038101, 149.031998 }, 1.000000 }; // 
    static constexpr Common::QuestEobject Eobject1 = { 2001408, 140, { 154.380997, 52.556000, 200.925995 }, 0.991760 }; // Caravan Sack
    static constexpr Common::QuestEobject Eobject2 = { 2001409, 140, { 141.835007, 53.000099, 221.576004 }, 0.991760 }; // Caravan Sack
    static constexpr auto EventActionGatherShort = 6;
    static constexpr auto EventActionSearch = 1; // Is this not used?
    static constexpr auto Item0 = 2000524; // Caravan sack?

    static constexpr auto Emote0 = 23; // /me
    static constexpr auto Bnpc0 = 1179; // Enemy0
    static constexpr auto Bnpc1 = 1178; // Enemy1

  public:
    ClsGla050() : Sapphire::ScriptAPI::QuestScript( 65792 ){}; 
    ~ClsGla050() = default; 

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
        else if( quest.getSeq() == Seq4 )
          Scene00027( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00045( quest, player );
        break;
      }
      case Actor1:
      {
        Scene00001( quest, player );
        break;
      }
      case Actor2:
      {
        Scene00004( quest, player );
        break;
      }
      case Actor3:
      {
        Scene00007( quest, player );
        break;
      }
      case Actor4:
      {
        Scene00010( quest, player );
        break;
      }
      case Actor5:
      {
        Scene00003( quest, player );
        break;
      }
      case Actor6:
      {
        Scene00006( quest, player );
        break;
      }
      case Actor7:
      {
        Scene00009( quest, player );
        break;
      }
      case Actor8:
      {
        Scene00012( quest, player );
        break;
      }
      case Actor9:
      {
        Scene00017( quest, player );
        break;
      }
      case Actor10:
      {
        // Chocobo
        break;
      }
      case Actor11:
      {
        Scene00025( quest, player );
        break;
      }
      case Actor12:
      {
        Scene00026( quest, player );
        break;
      }
      case Actor13:
      {
        if( quest.getSeq() == Seq5 )
          Scene00028( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00036( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00040( quest, player );
        break;
      }
      case Actor14:
      {
        Scene00031( quest, player );
        break;
      }
      case Eobject1.id:
      {
        eventMgr().eventActionStart( player, getId(), EventActionGatherShort, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) { Scene00032( quest, player ); }, nullptr, 0 );
        break;
      }
      case Eobject2.id:
      {
        eventMgr().eventActionStart( player, getId(), EventActionGatherShort, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) { Scene00034( quest, player ); }, nullptr, 0 );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getBNpcNameId() )
    {
      case Bnpc0:
      {
        checkQuestCompletion( quest, player );
        break;
      }
      case Bnpc1:
      {
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

  void onEmote(World::Quest& quest, uint64_t actorId, uint32_t emoteId, Sapphire::Entity::Player& player) override
  {
    if( emoteId == Emote0 )
    {
      switch( actorId )
      {
        case Actor1:
          Scene00002( quest, player );
          break;
        case Actor2:
          Scene00005( quest, player );
          break;
        case Actor3:
          Scene00008( quest, player );
          break;
        case Actor4:
          Scene00011( quest, player );
          break;
        case Actor9:
          Scene00018( quest, player );
          break;
      }
    }
  }

  private:
    void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
    {
      switch( quest.getSeq() )
      {
        case Seq1:
        {
          auto currentCC0 = quest.getUI8AL() + 1;
          if( currentCC0 <= 4 )
          {
            quest.setUI8AL( currentCC0 );
            eventMgr().sendEventNotice( player, getId(), 0, 2, currentCC0, 4 );
            if( currentCC0 == 4 )
            {
              quest.setUI8AL( 0 );
              quest.setBitFlag8( 1, false );
              quest.setBitFlag8( 2, false );
              quest.setBitFlag8( 3, false );
              quest.setBitFlag8( 4, false );
              quest.setSeq( Seq2 );
            }
          }
          break;
        }
        case Seq6:
        {
          auto currentCC1 = quest.getUI8AH() + 1;
          if( currentCC1 <= 2 )
          {
            quest.setUI8AH( currentCC1 );
            quest.setUI8BL( currentCC1 );
            quest.setUI8BH( currentCC1 );
            eventMgr().sendEventNotice( player, getId(), 5, 3, currentCC1, 2 );
            if( currentCC1 == 2 )
            {
              quest.setBitFlag8( 1, false );
              quest.setBitFlag8( 2, false );
              quest.setSeq( Seq7 );
            }
          }
          break;
        }
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( Seq1 );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    //The 'ells ye want? This don't concern ye, so bugger off!
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    //Ye know yer friend 'ere's a Twelve-damned cheat!? Thinks •e can charge us more 'cause we' re foreigners !But 'e' ll get 'is own back, mark me words!
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsGla050::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    //Bugger off !Can 't ye see I' m •avin' a civilized conversation with this poxy whoreson !?
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    //What? Ye blamin' me 'cause this little shite shat 'is own pants!? Well, bugger 'im, an' bugger you, too !
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsGla050::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    //Ye gots a lot o' nerve, thinkin' ye can talk to me like that!
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    //Oi, come on now, 'e was disrespectin' me proud Sea Wolf 'eritage! <spit> Fine, I'll leave the bastard be, but we ain't finished!
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 3, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ClsGla050::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    //...Just turn around an' walk away, 'venturer. Are ye deaf? Get lost!
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    //The 'ells is yer problem!? Maybe she likes 'er men rough! What're ye s'posed to be, 'er bleedin' lady-in-waitin'!? Bah, it don't matter, ye've gone an' spoiled the mood...
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 4, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ClsGla050::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ClsGla050::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &ClsGla050::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ClsGla050::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ClsGla050::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    //Me poxy arse this is yer best brew! I'd sooner drink a pint o' me own piss than this swill!
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR | CONDITION_CUTSCENE, bindSceneReturn( &ClsGla050::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ClsGla050::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ClsGla050::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ClsGla050::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ClsGla050::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &ClsGla050::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &ClsGla050::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    //'Tis a rare day indeed I have the honor of speaking with such a fair maiden. A toast to a most fortuitous meeting─the first of many, I pray.
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0, 0, 0 );
    quest.setSeq( Seq5 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    //They...they tore me from my saddle and took everything I own! Bring my goods back to me, I beg of you!
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0, 0, 0 );
    quest.setSeq( Seq6 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &ClsGla050::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, NONE, bindSceneReturn( &ClsGla050::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &ClsGla050::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, NONE, bindSceneReturn( &ClsGla050::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00033( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    //A concatenation of anarv curses assaults vour ears!
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &ClsGla050::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsPlayer(), 100 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, NONE, bindSceneReturn( &ClsGla050::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00035( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    //A concatenation of anarv curses assaults vour ears!
    eventMgr().playQuestScene( player, getId(), 35, NONE, bindSceneReturn( &ClsGla050::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsPlayer(), 100 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    //They...they tore me from my saddle and took everything I own! Bring my goods back to me, I beg of you!
    eventMgr().playQuestScene( player, getId(), 36, NONE, bindSceneReturn( &ClsGla050::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, NONE, bindSceneReturn( &ClsGla050::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, NONE, bindSceneReturn( &ClsGla050::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, NONE, bindSceneReturn( &ClsGla050::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    //They...they tore me from my saddle and took everything I own! Bring my goods back to me, I beg of you!
    eventMgr().playQuestScene( player, getId(), 40, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // Accept trade of quest item
    {
      quest.setUI8AH( 0 );
      quest.setUI8BL( 0 );
      quest.setUI8BH( 0 );
      Scene00041( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    //Twelve bless you, adventurer! If it weren't for good women like you, I'd never leave home.
    eventMgr().playQuestScene( player, getId(), 41, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 6, 0, 0, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, NONE, bindSceneReturn( &ClsGla050::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, NONE, bindSceneReturn( &ClsGla050::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, NONE, bindSceneReturn( &ClsGla050::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    //Twelve bless you, adventurer! If it weren't for good women like you, I'd never leave home.
    eventMgr().playQuestScene( player, getId(), 46, HIDE_HOTBAR, bindSceneReturn( &ClsGla050::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, NONE, bindSceneReturn( &ClsGla050::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, NONE, bindSceneReturn( &ClsGla050::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, NONE, bindSceneReturn( &ClsGla050::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

};

EXPOSE_SCRIPT( ClsGla050 );