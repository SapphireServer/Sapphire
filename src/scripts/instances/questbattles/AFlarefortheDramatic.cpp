#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AFlarefortheDramatic : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_YAMITRA_01 = 5907982;
  static constexpr auto P_BNPC_ROEGA_01 = 5907983;
  static constexpr auto BNPC_CUP_01 = 5907984;
  static constexpr auto BNPC_SORD_01 = 5907985;
  static constexpr auto BNPC_CEPTER_01 = 5907986;
  static constexpr auto BNPC_COIN_01 = 5907987;
  static constexpr auto BNPC_METEOR_01 = 5907988;
  static constexpr auto BNPC_DARK_MARSH_01 = 5920798;
  static constexpr auto NCUT_01 = 968;
  static constexpr auto YELL_QIB_CUP_DOUBLE_01 = 2727;
  static constexpr auto YELL_QIB_SWORD_END = 2931;
  static constexpr auto YELL_QIB_CEPTER_END = 2932;
  static constexpr auto YELL_QIB_COIN_END = 2933;
  static constexpr auto BNPC_ACTION_SUMMON_DARK_MARSH = 4841;
  static constexpr auto BNPC_ACTION_SUMMON_COMMET_TRIGGER = 3269;
  static constexpr auto BNPC_ACTION_SUMMON_COMET = 4842;
  static constexpr auto BNPC_ACTION_DEBRIS_BURST = 4844;
  static constexpr auto BNPC_ACTION_DOUBLE = 3443;
  static constexpr auto BNPC_ACTION_DOUBLE_TRIGGER = 4777;
  static constexpr auto BNPC_ACTION_DARK_FIRE3 = 5049;
  static constexpr auto STATUS_DOUBLE = 1280;
  static constexpr auto LOCKON_BY_COMET = 7;
  static constexpr auto POP_RANGE_DARK_MARSH_01 = 5920904;
  static constexpr auto POP_RANGE_DARK_MARSH_02 = 5920905;
  static constexpr auto POP_RANGE_DARK_MARSH_03 = 5920906;
  static constexpr auto POP_RANGE_DARK_MARSH_04 = 5920908;
  static constexpr auto POP_RANGE_DARK_MARSH_05 = 5920939;
  static constexpr auto POP_RANGE_DARK_MARSH_06 = 5920940;
  static constexpr auto POP_RANGE_DARK_MARSH_07 = 5920991;
  static constexpr auto POP_RANGE_DARK_MARSH_08 = 5920992;
  static constexpr auto LCUT_ACTOR0 = 1014921;
  static constexpr auto LCUT_ACTOR1 = 1013845;
  static constexpr auto LCUT_ACTOR2 = 1014636;
  static constexpr auto LCUT_ACTOR3 = 1014633;
  static constexpr auto LCUT_ACTOR4 = 1014634;
  static constexpr auto LCUT_ACTOR5 = 1014635;
  static constexpr auto LCUT_POS_ACTOR0 = 5907983;
  static constexpr auto QST_HEAVNA707 = 67205;
  static constexpr auto BNPCBASE_ID_CUP = 4834;
  static constexpr auto BNPCBASE_ID_COMET = 4838;
  static constexpr auto BNPC_ACTION_MEGIDDO_FLAME1 = 4839;
  static constexpr auto BNPC_ACTION_FAST_CAST_DARK_FIRE3 = 4840;
  static constexpr auto BNPC_ACTION_EXPLOSION_DARK_MARSH = 962;
  static constexpr auto BNPC_ACTION_IMPACT_COMMET = 4843;
  static constexpr auto BNPCBASE_ID_DARK_MARSH = 4904;
  static constexpr auto LCUT_BGM0 = 94;
  static constexpr auto LCUT_BGM1 = 91;
  static constexpr auto LOC_VFX0 = 251;
  static constexpr auto LOC_SE0 = 52;

public:
  AFlarefortheDramatic() : Sapphire::ScriptAPI::QuestBattleScript( 148 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "sgbg_l1p1_q3_swhu1", 2005078, 5573675, 5578187, 4, { -150.601807f, -15.195440f, 86.396042f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_1", 2005079, 5573676, 5578188, 4, { -160.177505f, -15.426880f, 111.877502f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_2", 2005080, 5573677, 5578189, 4, { -178.133102f, -15.426880f, 85.038406f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_3", 2005081, 5573687, 5578194, 4, { 147.790497f, -15.205700f, 85.606216f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_4", 2005082, 5573688, 5578197, 4, { 181.170303f, -15.426880f, 81.284790f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_5", 2005083, 5573689, 5578199, 4, { 160.730392f, -15.457460f, 117.518303f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_6", 2005084, 5573690, 5578200, 4, { -0.015320f, -15.426880f, -162.924103f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_7", 2005085, 5573691, 5578202, 4, { 19.010229f, -15.416970f, -200.015396f }, 1.000000f, 0.000000f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "sgbg_l1p1_q3_swhu1_8", 2005086, 5573692, 5578204, 4, { -18.994471f, -15.426880f, -199.992905f }, 0.991760f, 0.000048f, 0); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.addEObj( "unknown_0", 2004187, 4724282, 4723177, 4, { -0.007111f, 12.000000f, -386.299896f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2004188, 4724284, 4723182, 4, { 335.025513f, 12.000000f, 193.711899f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2004189, 4724283, 4723183, 4, { -334.556213f, 12.000000f, 193.274796f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_l1p1_lvd_b0441", 2004202, 4797506, 4724018, 4, { -0.101569f, 30.000000f, 1.413736f }, 1.000000f, 0.000000f, 0); 
    // States -> STAGE_def (id: 2) STAGE_pop_anim (id: 3) 
    instance.addEObj( "Lingeringaether", 2006281, 0, 5919142, 4, { -16.887329f, 28.500000f, -9.771084f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Lingeringaether_1", 2006282, 0, 5919143, 4, { -0.026589f, 28.500000f, -19.477510f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Lingeringaether_2", 2006283, 0, 5919144, 4, { 16.861151f, 28.488529f, -9.750549f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Lingeringaether_3", 2006284, 0, 5919145, 4, { 16.914730f, 28.500000f, 9.752019f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Lingeringaether_4", 2006285, 0, 5919146, 4, { -0.018755f, 28.500000f, 19.489780f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Lingeringaether_5", 2006286, 0, 5919147, 4, { -16.881241f, 28.500000f, 9.761797f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AFlarefortheDramatic );