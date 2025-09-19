#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class LeiasLegacy : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 2319770;
  static constexpr auto INIT_POP_02 = 2319771;
  static constexpr auto INIT_POP_03 = 2319772;
  static constexpr auto INIT_POP_04 = 2319773;
  static constexpr auto INIT_EO_POP_01 = 3867263;
  static constexpr auto LOC_ACTOR0 = 1003008;
  static constexpr auto LOC_ACTOR1 = 1000816;
  static constexpr auto LOC_ACTOR2 = 1003016;
  static constexpr auto LOC_ACTOR3 = 1003017;
  static constexpr auto LOC_ACTOR4 = 1003018;
  static constexpr auto INIT_P_POP_KUPURU_KOPO = 4097283;
  static constexpr auto DEF_ACTION_WS_CRITICAL_LANCER = 477;
  static constexpr auto INIT_EN_POP_01 = 4107577;

public:
  LeiasLegacy() : Sapphire::ScriptAPI::QuestBattleScript( 14 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2001217, 0, 3896009, 4, { 143.907898f, -26.213240f, 288.586304f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemfragment", 2001212, 0, 3920288, 4, { -233.827194f, -31.603571f, 363.483490f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemfragment_1", 2001212, 0, 3920291, 4, { -210.405304f, -30.263439f, 339.910309f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemfragment_2", 2001212, 0, 3920292, 4, { -193.951004f, -32.511791f, 287.437012f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemfragment_3", 2001212, 0, 3920297, 4, { -228.257996f, -26.702641f, 296.407501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2002500, 0, 4321459, 4, { -287.226593f, -79.420212f, 488.636688f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2002500, 0, 4321585, 4, { -280.811798f, -79.453796f, 502.494812f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_3", 2002500, 0, 4321586, 4, { -276.546906f, -81.106941f, 463.178589f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2002500, 0, 4321587, 4, { -297.265808f, -79.690392f, 498.251099f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2002500, 0, 4321588, 4, { -296.517792f, -79.288193f, 472.396301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2002500, 0, 4321589, 4, { -270.604614f, -80.473587f, 483.565308f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2002500, 0, 4321590, 4, { -255.953995f, -79.382019f, 473.689392f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2002500, 0, 4321591, 4, { -269.224091f, -77.344063f, 510.199005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2002500, 0, 4321623, 4, { -294.341888f, -79.279083f, 513.495972f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Airshipfragment", 2004261, 0, 4746509, 4, { 322.222412f, -6.361168f, 18.316811f }, 1.400000f, 0.240699f, 0); 
    instance.addEObj( "unknown_10", 2004262, 0, 4746510, 4, { 321.652802f, -6.433453f, 18.224859f }, 1.500000f, 0.774193f, 0); 
    instance.addEObj( "unknown_11", 2004263, 0, 4746511, 4, { 322.559387f, -6.321119f, 18.343599f }, 1.450000f, -1.362784f, 0); 
    instance.addEObj( "unknown_12", 2004347, 0, 4868696, 4, { 322.601105f, -6.360372f, 17.896509f }, 1.600000f, -0.570340f, 0); 
    instance.addEObj( "unknown_13", 2004348, 0, 4868697, 4, { 322.078888f, -6.432873f, 17.748600f }, 1.300000f, -0.783565f, 0); 
    instance.addEObj( "Warballoondebris", 2004442, 0, 4891873, 4, { 265.016907f, -13.914900f, 58.457279f }, 1.000000f, 0.490834f, 0); 
    instance.addEObj( "unknown_14", 2004519, 0, 4891874, 4, { 260.191315f, -17.213100f, 67.611923f }, 1.000000f, -1.276617f, 0); 
    instance.addEObj( "unknown_15", 2004520, 0, 4891875, 4, { 260.707397f, -16.157860f, 63.172409f }, 1.000000f, 0.656738f, 0); 
    instance.addEObj( "unknown_16", 2004521, 0, 4891876, 4, { 262.212708f, -16.276260f, 63.610401f }, 1.000000f, -0.810459f, 0); 
    instance.addEObj( "Ixalistoragepot", 2004443, 0, 4892061, 4, { 211.932495f, -4.898254f, 27.573000f }, 1.998901f, -1.218245f, 0); 
    instance.addEObj( "Ixalistoragepot_1", 2004444, 0, 4892062, 4, { 212.003998f, -5.292601f, 28.763309f }, 1.000000f, -1.364642f, 0); 
    instance.addEObj( "unknown_17", 2004522, 0, 4902947, 4, { -35.968399f, -40.945332f, 160.347000f }, 1.449585f, 0.173236f, 0); 
    instance.addEObj( "unknown_18", 2004445, 0, 4902948, 4, { -35.995461f, -40.393318f, 160.638199f }, 0.991760f, 0.679218f, 0); 
    instance.addEObj( "Lathegearwheel", 2004543, 0, 4922229, 4, { -35.995499f, -40.556431f, 160.638199f }, 1.000000f, 0.252590f, 0); 
    instance.addEObj( "unknown_19", 2004535, 0, 4893738, 4, { 150.100800f, -18.118971f, 99.719353f }, 1.000000f, -0.440750f, 0); 
    instance.addEObj( "Markedterritory", 2004452, 0, 4890717, 4, { 324.605103f, -14.206180f, 181.139801f }, 0.991760f, 1.171260f, 0); 
    instance.addEObj( "Markedterritory_1", 2004453, 0, 4890718, 4, { 304.042694f, -18.858070f, 190.831696f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Markedterritory_2", 2004454, 0, 4890719, 4, { 319.591797f, -16.101589f, 205.682297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Markedterritory_3", 2004455, 0, 4890720, 4, { 322.712891f, -14.480900f, 196.276703f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "EhcatlNinestoragepot", 2004456, 0, 4890806, 4, { 238.309906f, -28.467819f, 206.231796f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "EhcatlNinestoragepot_1", 2004457, 0, 4890807, 4, { 217.169205f, -27.404160f, 209.888702f }, 1.000000f, 0.825532f, 0); 
    instance.addEObj( "EhcatlNinestoragepot_2", 2004458, 0, 4890810, 4, { 215.140305f, -25.819309f, 229.686005f }, 0.991760f, 0.054122f, 0); 
    instance.addEObj( "EhcatlNinestoragepot_3", 2004459, 0, 4890811, 4, { 234.637802f, -24.271429f, 228.210907f }, 1.000000f, 0.587589f, 0); 
    instance.addEObj( "unknown_20", 2004523, 0, 4892111, 4, { 238.309906f, -29.110319f, 206.231796f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2004524, 0, 4892112, 4, { 217.169205f, -28.036131f, 209.888702f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2004525, 0, 4892113, 4, { 215.140305f, -26.448540f, 229.686005f }, 1.000000f, 0.892995f, 0); 
    instance.addEObj( "unknown_23", 2004526, 0, 4892114, 4, { 234.637802f, -24.927940f, 228.210907f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenstoragepot", 2004460, 0, 4890851, 4, { 85.656708f, -38.312939f, 342.885406f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenstoragepot_1", 2004461, 0, 4890853, 4, { 83.006599f, -41.516979f, 362.249512f }, 1.000000f, 1.480753f, 0); 
    instance.addEObj( "Stolenstoragepot_2", 2004462, 0, 4890854, 4, { 66.089668f, -40.685822f, 355.243713f }, 1.000000f, 0.843735f, 0); 
    instance.addEObj( "unknown_24", 2004527, 0, 4893977, 4, { 85.656708f, -39.027821f, 342.885406f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2004528, 0, 4893978, 4, { 83.006577f, -42.181721f, 362.249512f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2004529, 0, 4893979, 4, { 66.089668f, -41.383770f, 355.243713f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2004463, 0, 4890862, 4, { 25.760000f, -44.740002f, 441.149994f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Snatchedstoragepot", 2004464, 0, 4890863, 4, { 25.760000f, -43.430199f, 441.149994f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2004465, 0, 4890889, 4, { -22.649139f, -7.454814f, -140.625107f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "unknown_29", 2004466, 0, 4890890, 4, { -47.104740f, -7.201632f, -159.830002f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2004467, 0, 4890891, 4, { -52.509998f, -8.238971f, -149.679993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_31", 2004468, 0, 4890892, 4, { -91.447388f, -6.546204f, -100.938499f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_32", 2004469, 0, 4890893, 4, { -123.902000f, -9.035076f, -118.217903f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "unknown_33", 2004470, 0, 4890894, 4, { -135.539993f, -10.210440f, -103.639999f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_34", 2004471, 0, 4890895, 4, { -108.283203f, -8.586540f, -51.375721f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot", 2004472, 0, 4890896, 4, { -22.649111f, -6.145164f, -140.625107f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot_1", 2004473, 0, 4890897, 4, { -47.104698f, -5.909051f, -159.830002f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot_2", 2004474, 0, 4890898, 4, { -52.536758f, -6.946814f, -149.706299f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot_3", 2004475, 0, 4890899, 4, { -91.447350f, -5.247173f, -100.938499f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot_4", 2004476, 0, 4890900, 4, { -123.902000f, -7.714047f, -118.217903f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot_5", 2004477, 0, 4890901, 4, { -135.546005f, -8.900931f, -103.654503f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ixalitreasurepot_6", 2004478, 0, 4890902, 4, { -108.280899f, -7.263391f, -51.348289f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_35", 2004357, 0, 4876992, 4, { -52.983631f, -47.065941f, 415.767487f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2004500, 0, 4890947, 4, { 150.225098f, -27.664610f, 112.352203f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_37", 2004501, 0, 4890948, 4, { 150.225098f, -27.664610f, 112.352203f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_38", 2004502, 0, 4890949, 4, { 150.250000f, -27.650000f, 112.379997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_39", 2004503, 0, 4890950, 4, { 150.279999f, -27.600000f, 112.379997f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_40", 2004504, 0, 4890951, 4, { 150.225098f, -27.587971f, 112.352203f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_41", 2004505, 0, 4890952, 4, { 150.225098f, -27.587999f, 112.352203f }, 0.991800f, -1.374447f, 0); 
    instance.addEObj( "Windtouchedaethersand", 2002894, 0, 4499379, 4, { -152.819199f, -8.438673f, -78.507690f }, 0.991760f, -1.345369f, 0); 
    instance.addEObj( "unknown_42", 2002895, 0, 4499380, 4, { -152.959305f, -9.268820f, -78.665413f }, 1.200000f, -0.017453f, 0); 
    instance.addEObj( "Waterblessedaethersand", 2002896, 0, 4499400, 4, { 28.825220f, 1.576339f, -96.779503f }, 0.991760f, 0.249512f, 0); 
    instance.addEObj( "unknown_43", 2002898, 0, 4500718, 4, { -152.819199f, -9.274364f, -78.794640f }, 0.991760f, -0.503872f, 0); 
    instance.addEObj( "Stolenprovisions", 2002844, 0, 4504804, 4, { -26.169250f, -7.562927f, -147.020798f }, 0.991760f, 1.237031f, 0); 
    instance.addEObj( "Stolenprovisions_1", 2002845, 0, 4504805, 4, { -137.270294f, -9.595765f, -80.837624f }, 0.991760f, -0.470768f, 0); 
    instance.addEObj( "Stolenprovisions_2", 2002846, 0, 4504806, 4, { -147.572998f, -1.905349f, -120.313599f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_44", 2002920, 0, 4504903, 4, { 185.631302f, -27.333790f, 182.719193f }, 0.991760f, -1.242558f, 0); 
    instance.addEObj( "unknown_45", 2002921, 0, 4504904, 4, { 184.807205f, -27.269079f, 183.504700f }, 1.000000f, -1.198863f, 0); 
    instance.addEObj( "unknown_46", 2002920, 0, 4504905, 4, { 186.248795f, -27.304741f, 182.621597f }, 1.000000f, -0.571384f, 0); 
    instance.addEObj( "unknown_47", 2005471, 0, 5854744, 4, { -174.944702f, -61.875431f, 371.572296f }, 1.296936f, 0.000048f, 0); 
    instance.addEObj( "Destination", 2005966, 0, 5900030, 4, { 163.530899f, -27.328920f, 207.873505f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_48", 2005235, 0, 5764983, 4, { 440.776611f, -0.106645f, -61.750118f }, 0.642375f, -0.513324f, 0); 
    instance.addEObj( "unknown_49", 2002388, 0, 4306194, 4, { -268.843414f, -78.855553f, 444.858490f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Epitaphtoinfancy", 2002399, 0, 4306754, 4, { 107.860397f, 7.714637f, -45.129051f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_50", 2002401, 0, 4306756, 4, { 107.999603f, 7.202641f, -45.457420f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_51", 2002402, 0, 4306757, 4, { 107.645798f, 7.095438f, -45.473320f }, 1.000000f, -1.256946f, 0); 
    instance.addEObj( "unknown_52", 2005852, 0, 5889879, 4, { 110.611504f, 6.922153f, -49.352982f }, 1.800000f, 0.000000f, 0); 
    instance.addEObj( "unknown_53", 2004685, 0, 5021343, 4, { -190.692505f, -58.533581f, 347.526703f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004110, 0, 4722113, 4, { -14.232840f, -53.537338f, 531.181091f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "???_1", 2004128, 0, 4722838, 4, { 384.298492f, -8.529028f, -95.597839f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_54", 2004878, 0, 5097920, 4, { 328.908112f, -5.203369f, 266.559814f }, 0.991760f, 0.000048f, 0); 

  }

  enum vars
  {
    SUCCESS_CALLED
  };

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    player.setRot( -1.30f );
    player.setPos( { -179.f, -27.40f, 291.33f } );
  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {
    auto boss = instance.getActiveBNpcByLayoutId( INIT_POP_01 );
    auto kopo = instance.getActiveBNpcByLayoutId( INIT_P_POP_KUPURU_KOPO );
    auto pPlayer = instance.getPlayerPtr();
    auto successCalled = instance.getDirectorVar( SUCCESS_CALLED );

    if( !kopo )
      return;

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
                                  DISABLE_CANCEL_EMOTE,
                          [ & ]( Entity::Player& player, const Event::SceneResult& result ) {
                            player.setOnEnterEventDone( true );
                          } );
  }

    void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
    {
      auto boss = instance.createBNpcFromLayoutId( INIT_POP_01, 21141, Common::BNpcType::Enemy );
      auto a2 = instance.createBNpcFromLayoutId( INIT_POP_02, 1440, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLayoutId( INIT_POP_03, 1440, Common::BNpcType::Enemy );
      auto a4 = instance.createBNpcFromLayoutId( INIT_POP_04, 1440, Common::BNpcType::Enemy );

      auto kopo = instance.createBNpcFromLayoutId( INIT_P_POP_KUPURU_KOPO, 27780, Common::BNpcType::Enemy );

      boss->setFlag( Entity::NoDeaggro );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );
      a4->setFlag( Entity::NoDeaggro );
      kopo->setFlag( Entity::NoDeaggro );

      boss->hateListAdd( player.getAsChara(), 10000 );
      boss->hateListAdd( kopo, 1 );

      a2->hateListAdd( player.getAsChara(), 1 );
      a2->hateListAdd( kopo, 10000 );

      a3->hateListAdd( player.getAsChara(), 1 );
      a3->hateListAdd( kopo, 10000 );

      a4->hateListAdd( player.getAsChara(), 1 );
      a4->hateListAdd( kopo, 10000 );

      kopo->hateListAdd( a2, 10000 );
      kopo->hateListAdd( a3, 10000 );
      kopo->hateListAdd( a4, 10000 );
      kopo->hateListAdd( boss, 1 );
    }

    void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
    {
      auto idx = player.getQuestIndex( instance.getQuestId() );
      if( idx == -1 )
        return;
      auto& quest = player.getQuestByIndex( idx );
      quest.setSeq( 4 );
    }
};

EXPOSE_SCRIPT( LeiasLegacy );