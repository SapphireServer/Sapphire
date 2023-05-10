#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class UnderneaththeSultantree : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 4077147;
  static constexpr auto INIT_POP_01_01 = 4077151;
  static constexpr auto INIT_POP_01_02 = 4077152;
  static constexpr auto INIT_POP_02_01 = 4077427;
  static constexpr auto INIT_POP_02_02 = 4077428;
  static constexpr auto INIT_POP_02_03 = 4077429;
  static constexpr auto INIT_POP_02_04 = 4077430;
  static constexpr auto INIT_P_POP_01 = 4077150;
  static constexpr auto CUT_SCENE_01 = 140;
  static constexpr auto HOW_TO_QIB = 79;

public:
  UnderneaththeSultantree() : Sapphire::ScriptAPI::QuestBattleScript( 37 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2000409, 0, 4103367, 4, { -133.093994f, 45.826611f, -209.826797f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2001710, 4133115, 4133114, 5, { -161.384903f, 44.219810f, -218.712402f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_1", 2001898, 0, 4263490, 4, { -96.123680f, 47.631321f, -265.750793f }, 1.000000f, -0.091888f, 0); 
    instance.addEObj( "訓練用�木�", 2001889, 0, 4260848, 4, { -0.076355f, 24.396429f, 196.551407f }, 0.991760f, 1.529354f, 0); 
    instance.addEObj( "Practicecrates", 2002266, 0, 4269210, 4, { -0.112231f, 26.103210f, 196.541901f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Practicecrate", 2002476, 0, 4314044, 4, { -0.088241f, 25.966061f, 196.565002f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2001890, 0, 4260868, 4, { -95.709747f, 47.837910f, -265.453613f }, 1.000000f, -0.235299f, 0); 
    instance.addEObj( "unknown_3", 2002008, 0, 4265062, 4, { -106.820503f, 45.686199f, -252.403305f }, 0.500000f, -0.577207f, 0); 
    instance.addEObj( "unknown_4", 2002267, 0, 4269214, 4, { -95.709801f, 47.837898f, -265.453613f }, 1.000000f, -0.235300f, 0); 
    instance.addEObj( "unknown_5", 2002268, 0, 4269215, 4, { -106.820503f, 45.686199f, -252.403305f }, 0.500000f, -0.577207f, 0); 
    instance.addEObj( "Solidrock", 2001480, 0, 4013496, 4, { -68.438843f, 43.505470f, 20.266279f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_1", 2001481, 0, 4013497, 4, { -52.133999f, 46.160561f, 15.830200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_2", 2001482, 0, 4013498, 4, { -73.786758f, 43.281189f, 4.642619f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_3", 2001483, 0, 4013503, 4, { -12.308910f, 46.420311f, 31.507410f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_4", 2001484, 0, 4013505, 4, { -14.554990f, 47.428921f, 12.358590f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_5", 2001485, 0, 4013506, 4, { 1.683882f, 48.296150f, 9.603806f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_6", 2001490, 0, 4030720, 4, { -68.438843f, 43.505470f, 20.266279f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_7", 2001490, 0, 4030721, 4, { -52.133999f, 46.160561f, 15.830200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_8", 2001490, 0, 4030722, 4, { -73.786758f, 43.281189f, 4.642619f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_9", 2001493, 0, 4030763, 4, { -12.308910f, 46.420311f, 31.507410f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_10", 2001493, 0, 4030764, 4, { -14.554990f, 47.428921f, 12.358590f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Solidrock_11", 2001493, 0, 4030765, 4, { 1.683882f, 48.296150f, 9.603806f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Overturnedwain", 2000286, 0, 3633019, 4, { -88.599541f, 43.582069f, -303.057404f }, 0.991760f, 1.396356f, 0); 
    instance.addEObj( "Overturnedwain_1", 2000287, 0, 3633020, 4, { -88.599503f, 43.582130f, -303.057404f }, 0.991800f, 1.396356f, 0); 
    instance.addEObj( "Unmovableboulder", 2001486, 0, 4031426, 4, { -225.313202f, 42.198292f, -35.190151f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Unmovableboulder_1", 2001494, 0, 4031428, 4, { -225.313202f, 42.198292f, -35.190151f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2004363, 0, 4877166, 4, { -181.600403f, 46.582878f, -90.640167f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2004364, 0, 4877167, 4, { -184.348206f, 47.100651f, -87.938889f }, 1.000000f, -0.024142f, 0); 
    instance.addEObj( "unknown_8", 2004362, 0, 4877178, 4, { -181.600403f, 46.582901f, -90.640198f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_9", 2004366, 0, 4877202, 4, { -181.600403f, 46.582901f, -90.640198f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004575, 0, 4970186, 4, { -181.600403f, 46.582901f, -90.640198f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_11", 2004903, 0, 5107885, 4, { 181.414398f, 69.474243f, 327.901093f }, 0.778198f, -1.158509f, 0); 
    instance.addEObj( "unknown_12", 2004904, 0, 5108572, 4, { 5.942663f, 57.893860f, -307.682892f }, 1.000000f, 1.286985f, 0); 
    instance.addEObj( "unknown_13", 2004905, 0, 5108575, 4, { 8.628152f, 57.998081f, -307.854004f }, 1.000000f, 1.546045f, 0); 
    instance.addEObj( "unknown_14", 2005121, 0, 5583559, 4, { -2.772403f, 24.362370f, 194.110992f }, 1.000000f, -1.046180f, 0); 
    instance.addEObj( "Destination", 2005073, 0, 5583562, 4, { -1.015763f, 29.584169f, 172.964294f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2004932, 0, 5327295, 4, { -182.797897f, 30.555679f, -684.921814f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2005921, 0, 5895410, 4, { 31.010000f, 60.669998f, -205.399994f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_3", 2005922, 0, 5895412, 4, { -90.370003f, 43.049999f, -308.299988f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_4", 2005923, 0, 5895413, 4, { -148.009995f, 20.320000f, -339.399994f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stonemonument", 2001582, 0, 4081044, 4, { -58.631599f, 27.154480f, -141.767899f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004114, 0, 4722679, 4, { 80.491333f, 58.406250f, 238.890594f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "???_1", 2004126, 0, 4722827, 4, { 22.938150f, 60.530869f, -281.564606f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Leathersatchel", 2004272, 0, 4745137, 4, { 224.215805f, 114.317596f, -223.401596f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2004273, 0, 4745138, 4, { 224.024994f, 114.304802f, -223.471100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2004274, 0, 4745139, 4, { 224.589600f, 114.304802f, -223.320496f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sackoforanges", 2001279, 0, 3929264, 4, { 132.807800f, 45.762241f, 134.938995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2000451, 0, 4219429, 4, { 187.182404f, 46.250000f, 120.164803f }, 1.480042f, 0.000048f, 0); 
    instance.addEObj( "unknown_18", 2000449, 0, 4219537, 4, { 132.807800f, 46.253880f, 134.938995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackloam", 2001237, 0, 3929266, 4, { -129.381302f, 46.677361f, -192.523102f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Blackloam_1", 2001238, 0, 3929267, 4, { -121.777199f, 45.989780f, -210.821304f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackloam_2", 2001239, 0, 3929268, 4, { -132.922699f, 45.370831f, -228.919495f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2001734, 0, 4164804, 4, { -34.989449f, 11.168120f, -432.098511f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Yarzonnest", 2001240, 0, 3929270, 4, { 120.677002f, 44.595348f, 37.449879f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Yarzonnest_1", 2001241, 0, 3929273, 4, { 21.039221f, 43.143730f, 46.993542f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Yarzonnest_2", 2001242, 0, 3929276, 4, { -18.936489f, 42.160629f, 58.609852f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Tillersshovel", 2001272, 0, 3929316, 4, { 219.830002f, 113.132698f, -244.164093f }, 1.000000f, -0.974642f, 0); 
    instance.addEObj( "Cumbersomerock", 2001243, 0, 3929669, 4, { 136.521698f, 75.180031f, -150.652695f }, 3.000000f, 0.000048f, 0); 
    instance.addEObj( "Cumbersomerock_1", 2001244, 0, 3929670, 4, { 120.851097f, 69.098717f, -129.253906f }, 3.000000f, 0.000000f, 0); 
    instance.addEObj( "Cumbersomerock_2", 2001245, 0, 3929672, 4, { 114.081902f, 63.887001f, -99.500351f }, 3.000000f, 0.000000f, 0); 
    instance.addEObj( "Strewndebris", 2001246, 0, 3929673, 4, { 118.764603f, 71.366631f, -163.583298f }, 1.500000f, 0.324228f, 0); 
    instance.addEObj( "Strewndebris_1", 2001247, 0, 3929674, 4, { 108.728401f, 65.295799f, -118.655899f }, 2.000000f, 1.549894f, 0); 
    instance.addEObj( "Strewndebris_2", 2001248, 0, 3929676, 4, { 118.758202f, 63.722900f, -81.455193f }, 0.991789f, 1.477567f, 0); 
    instance.addEObj( "Ripeorange", 2001249, 0, 3929968, 4, { 78.170227f, 71.093033f, -216.863205f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ripeorange_1", 2001250, 0, 3929978, 4, { 52.508530f, 68.080292f, -223.840607f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ripeorange_2", 2001251, 0, 3930022, 4, { 77.992752f, 68.706657f, -177.286697f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ripeorange_3", 2001252, 0, 3930027, 4, { 64.534592f, 60.283661f, -141.981201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ripeorange_4", 2001253, 0, 3930035, 4, { 51.649109f, 59.454071f, -151.267395f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Vultureterritory", 2001254, 0, 3926089, 4, { -220.020798f, 17.811649f, -414.486603f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2001256, 0, 3927155, 4, { -321.174103f, 25.227871f, -536.788330f }, 0.600000f, 0.882138f, 0); 
    instance.addEObj( "unknown_21", 2001257, 0, 3927157, 4, { -308.949493f, 24.240320f, -531.609070f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_22", 2001258, 0, 3927159, 4, { -316.673187f, 24.716949f, -533.379211f }, 0.991760f, -0.990636f, 0); 
    instance.addEObj( "unknown_23", 2001259, 0, 3927160, 4, { -306.996307f, 23.603291f, -520.500488f }, 0.991760f, -0.713484f, 0); 
    instance.addEObj( "Millioncornseedling", 2001255, 0, 3927161, 4, { -320.576813f, 25.833500f, -527.550171f }, 0.961304f, -0.384837f, 0); 

  }
  enum vars
  {
    SET_1_SPAWNED,
    SET_2_SPAWNED,
    SUCCESS_CALLED,
  };

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    player.setRot( -71.03f );
    player.setPos( { 198.303f, 14.244f, 538.248f } );
  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {
    auto pair1Spawnd = instance.getDirectorVar( SET_1_SPAWNED );
    auto pair2Spawnd = instance.getDirectorVar( SET_2_SPAWNED );
    auto successCalled = instance.getDirectorVar( SUCCESS_CALLED );

    auto boss = instance.getActiveBNpcByLayoutId( INIT_POP_BOSS );
    auto thancred = instance.getActiveBNpcByLayoutId( INIT_P_POP_01 );
    auto pPlayer = instance.getPlayerPtr();

    uint32_t bossHpPercent = 0;
    if( boss )
      bossHpPercent = boss->getHpPercent();

    if( pPlayer && !pPlayer->isAlive() )
    {
      instance.fail();
      return;
    }

    if (!thancred)
      return;

    if( pair1Spawnd == 0 && bossHpPercent <= 70 )
    {
      instance.setDirectorVar( SET_1_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromLayoutId( INIT_POP_01_01, 1440 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLayoutId( INIT_POP_01_02, 1440 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a2->hateListAdd( pPlayer, 1 );
      a3->hateListAdd( pPlayer, 1 );

      thancred->hateListAdd( a2, 9999 );
      thancred->hateListAdd( a3, 9999 );
    }

    if( pair2Spawnd == 0 && bossHpPercent <= 40 )
    {
      instance.setDirectorVar( SET_2_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromLayoutId( INIT_POP_02_01, 1440 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLayoutId( INIT_POP_02_02, 1440 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      auto a4 = instance.createBNpcFromLayoutId( INIT_POP_02_03, 1440 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLayoutId( INIT_POP_02_04, 1440 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a2->hateListAdd( pPlayer, 1 );
      a3->hateListAdd( pPlayer, 1 );
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );

      thancred->hateListAdd( a2, 9999 );
      thancred->hateListAdd( a3, 9999 );
      thancred->hateListAdd( a4, 9999 );
      thancred->hateListAdd( a5, 9999 );
    }

    if( instance.getCountEnemyBNpc() == 0 && successCalled == 0 )
    {
      instance.setDirectorVar( SUCCESS_CALLED, 1 );
      instance.success();
      return;
    }

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
    eventMgr().playScene( player, instance.getDirectorId(), 1,
                          NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                          HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                          DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                          // todo: wtf is 0x00100000
                          DISABLE_CANCEL_EMOTE, [ & ]( Entity::Player& player, const Event::SceneResult& result ) {
                            player.setOnEnterEventDone( true );
                          } );
  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
    auto idx = player.getQuestIndex( instance.getQuestId() );
    if( idx == -1 )
      return;
    auto& quest = player.getQuestByIndex( idx );
    quest.setSeq( 2 );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    // TODO: Change to correct HP values
    auto boss = instance.createBNpcFromLayoutId( INIT_POP_BOSS, 10571 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    auto thancred = instance.createBNpcFromLayoutId( INIT_P_POP_01, 27780 /*TODO: Find the right value*/, Common::BNpcType::Friendly );

    boss->setFlag( Entity::NoDeaggro );
    thancred->setFlag( Entity::NoDeaggro );

    boss->hateListAdd( thancred, 10000 );
    boss->hateListAdd( player.getAsPlayer(), 1 );

    thancred->hateListAdd( boss, 10000 );

  }

};

EXPOSE_SCRIPT( UnderneaththeSultantree );