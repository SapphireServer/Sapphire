#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class StrayintotheShadows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_EXC_01 = 5032415;
  static constexpr auto INIT_POP_1ST_EXC_02 = 5032416;
  static constexpr auto INIT_POP_1ST_EXC_03 = 5032417;
  static constexpr auto INIT_POP_1ST_EXC_04 = 5032418;
  static constexpr auto INIT_POP_2ST_ARC_01 = 5032445;
  static constexpr auto INIT_POP_2ST_ARC_02 = 5032446;
  static constexpr auto INIT_POP_2ST_EXC_01 = 5032447;
  static constexpr auto BNPC_VK_BAIT_1 = 5032448;
  static constexpr auto INIT_POP_3ST_EXC_02 = 5032449;
  static constexpr auto INIT_POP_3ST_EXC_03 = 5032453;
  static constexpr auto INIT_POP_3ST_EXC_04 = 5032454;
  static constexpr auto INIT_POP_3ST_EXC_05 = 5032455;
  static constexpr auto INIT_POP_3ST_EXC_06 = 5032456;
  static constexpr auto INIT_POP_3ST_ARC_01 = 5032457;
  static constexpr auto BNPC_VK_BAIT_2 = 5032458;
  static constexpr auto INIT_POP_3ST_ARC_03 = 5032459;
  static constexpr auto INIT_POP_3ST_ARC_04 = 5032460;
  static constexpr auto INIT_POP_3ST_ARC_05 = 5032461;
  static constexpr auto INIT_POP_3ST_ARC_06 = 5032462;
  static constexpr auto INIT_POP_3ST_ARC_07 = 5032463;
  static constexpr auto INIT_POP_3ST_ARC_08 = 5032464;
  static constexpr auto INIT_P_POP_VAK_01 = 5032444;
  static constexpr auto INIT_ENPC_VAK_01 = 5032411;
  static constexpr auto INIT_ENPC_MAR_01 = 5032420;
  static constexpr auto INIT_ENPC_MAR_02 = 5032855;
  static constexpr auto INIT_ENPC_YEL_01 = 5032422;
  static constexpr auto INIT_POP_EOBJ_01 = 5032470;
  static constexpr auto EVENT_ACTION_01 = 32;
  static constexpr auto EVENT_ACTION_02 = 45;
  static constexpr auto ER_RECT_01 = 5038527;
  static constexpr auto BGM_LASTHALF = 39;
  static constexpr auto POP_RANGE_VAK_DEPOP = 5045483;
  static constexpr auto QIB_YELL_01 = 2319;
  static constexpr auto QIB_YELL_02 = 2378;
  static constexpr auto QIB_YELL_03 = 2379;
  static constexpr auto LCUT_ACTOR0 = 1010214;
  static constexpr auto LCUT_ACTOR1 = 1010215;
  static constexpr auto LCUT_ACTOR2 = 1010216;
  static constexpr auto LCUT_ACTOR3 = 1010217;
  static constexpr auto LCUT_POS0 = 5032420;
  static constexpr auto LCUT_POS1 = 5323061;
  static constexpr auto LCUT_POS2 = 5323062;
  static constexpr auto LCUT_POS3 = 5323066;
  static constexpr auto LCUT_FACE0 = 608;
  static constexpr auto INIT_POP_EOBJ_02 = 5323044;
  static constexpr auto STATUS_STEALTH = 1198;
  static constexpr auto WARP_01 = 5032443;

public:
  StrayintotheShadows() : Sapphire::ScriptAPI::QuestBattleScript( 90 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Companychest", 2000470, 4255817, 4255818, 4, { -199.998505f, 17.071720f, 58.787498f }, 1.000000f, -0.402012f, 0); 
    instance.addEObj( "unknown_0", 2004734, 0, 5032469, 4, { -219.744400f, 3.999157f, 273.263306f }, 1.100000f, 0.756548f, 0); 
    instance.addEObj( "Stolenfirearms", 2004733, 0, 5032470, 4, { -219.383301f, 4.908100f, 272.230713f }, 1.000000f, -0.801010f, 0); 
    instance.addEObj( "Handoff", 2004926, 0, 5323044, 4, { -193.687897f, 9.428031f, 71.954041f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2004892, 0, 5106077, 4, { -96.928200f, 27.461620f, 261.604309f }, 1.000000f, -0.745636f, 0); 
    instance.addEObj( "unknown_2", 2004906, 0, 5110332, 4, { -161.111206f, 1.953200f, 239.309006f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "BoxforTataru", 2004145, 0, 4867488, 4, { -100.126297f, 6.000001f, 202.704300f }, 0.991760f, 0.588722f, 0); 
    instance.addEObj( "unknown_3", 2004146, 0, 4867489, 4, { -101.008003f, 5.996766f, 201.230194f }, 0.991760f, -1.017078f, 0); 
    instance.addEObj( "unknown_4", 2004147, 0, 4867490, 4, { -102.275803f, 5.996765f, 200.966599f }, 0.991760f, 0.429849f, 0); 
    instance.addEObj( "unknown_5", 2004148, 0, 4867491, 4, { -101.120399f, 5.996765f, 202.233902f }, 0.991760f, 0.596492f, 0); 
    instance.addEObj( "unknown_6", 2004148, 0, 4867492, 4, { -102.120796f, 5.996764f, 199.586899f }, 0.991760f, 0.247960f, 0); 
    instance.addEObj( "unknown_7", 2004147, 0, 4867493, 4, { -100.527199f, 5.996765f, 203.762802f }, 0.991760f, -1.428476f, 0); 
    instance.addEObj( "unknown_8", 2004146, 0, 4867494, 4, { -101.017601f, 6.818192f, 202.276993f }, 0.600000f, 0.126683f, 0); 
    instance.addEObj( "unknown_9", 2004146, 0, 4867495, 4, { -102.150398f, 6.848503f, 201.116302f }, 0.600000f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2004135, 0, 4867519, 4, { -100.126297f, 5.996800f, 202.704300f }, 0.600000f, 2.159519f, 0); 
    instance.addEObj( "unknown_11", 2005933, 0, 5895639, 4, { -188.869995f, 0.990000f, 207.729996f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005934, 0, 5895641, 4, { -188.794601f, 1.735276f, 207.786301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2005935, 0, 5895644, 4, { -175.539993f, 4.000000f, 179.250000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2001314, 0, 4323433, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_13", 2001305, 0, 4323434, 4, { -169.771606f, 4.550005f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_14", 2001306, 0, 4323436, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_15", 2001307, 0, 4323437, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_16", 2001308, 0, 4323438, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_17", 2001309, 0, 4323439, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_18", 2001310, 0, 4323441, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_19", 2001311, 0, 4323442, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_20", 2001312, 0, 4323443, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_21", 2001313, 0, 4323444, 4, { -169.771606f, 4.550000f, 158.402496f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "unknown_22", 2001079, 0, 4323445, 4, { -170.175903f, 4.550000f, 159.076096f }, 1.000000f, -0.523599f, 0); 
    instance.addEObj( "???", 2004123, 0, 4722778, 4, { -208.911301f, 24.521240f, 194.515701f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Rorojaruschest", 2004569, 0, 5578172, 4, { -356.258301f, 7.980466f, 48.936020f }, 0.991760f, 1.561786f, 0); 
    instance.addEObj( "Rorojaruschest_1", 2004568, 0, 5578173, 4, { -356.285492f, 8.000032f, 48.928028f }, 1.000000f, 1.561813f, 0); 
    instance.addEObj( "Peculiarherb", 2001563, 0, 4082215, 4, { 3.636703f, 20.013130f, 9.758556f }, 0.991760f, 0.818526f, 0); 
    instance.addEObj( "Peculiarherb_1", 2001564, 0, 4082216, 4, { -3.067139f, 20.004520f, 9.994568f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Peculiarherb_2", 2001565, 0, 4082217, 4, { -11.386190f, 19.998329f, 6.643170f }, 0.991760f, -0.593593f, 0); 
    instance.addEObj( "Peculiarherb_3", 2001566, 0, 4082218, 4, { -18.295650f, 20.024580f, 1.724182f }, 0.991760f, 1.389516f, 0); 
    instance.addEObj( "Peculiarherb_4", 2001567, 0, 4082219, 4, { -30.472290f, 19.995661f, 0.839172f }, 0.991760f, -0.713480f, 0); 
    instance.addEObj( "Peculiarherb_5", 2001568, 0, 4082220, 4, { -44.724239f, 20.020281f, -0.503601f }, 0.991760f, 0.286380f, 0); 
    instance.addEObj( "Gutteringstreetlamp", 2001572, 0, 4076919, 4, { -65.368477f, 21.581499f, 54.410839f }, 1.000000f, 1.158798f, 0); 
    instance.addEObj( "Gutteringstreetlamp_1", 2001573, 0, 4076920, 4, { -84.382721f, 21.506001f, 81.176872f }, 1.000000f, -1.191708f, 0); 
    instance.addEObj( "Gutteringstreetlamp_2", 2001574, 0, 4076923, 4, { -117.660500f, 21.596270f, 134.942596f }, 1.000000f, 0.781740f, 0); 
    instance.addEObj( "Gutteringstreetlamp_3", 2001576, 0, 4076926, 4, { -162.471100f, 15.090300f, 136.587601f }, 1.000000f, -0.927998f, 0); 
    instance.addEObj( "Gutteringstreetlamp_4", 2001577, 0, 4076929, 4, { -137.529602f, 9.802422f, 170.656403f }, 0.991760f, 1.018627f, 0); 
    instance.addEObj( "Gutteringstreetlamp_5", 2001578, 0, 4077149, 4, { -65.683968f, 20.675900f, 17.784571f }, 0.991760f, 0.862734f, 0); 
    instance.addEObj( "Gutteringstreetlamp_6", 2001575, 0, 4076924, 4, { -145.330902f, 22.956011f, 159.746597f }, 0.991760f, -0.670120f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( StrayintotheShadows );