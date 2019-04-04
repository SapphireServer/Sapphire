#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class StifledScreams : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_YEL_01 = 5041137;
  static constexpr auto INIT_POP_YEL_02 = 5041138;
  static constexpr auto INIT_POP_YEL_03 = 5041139;
  static constexpr auto INIT_POP_YEL_04 = 5041140;
  static constexpr auto INIT_POP_YEL_05 = 5041141;
  static constexpr auto INIT_POP_YEL_06 = 5041142;
  static constexpr auto INIT_POP_YEL_07 = 5041143;
  static constexpr auto INIT_POP_YEL_08 = 5041144;
  static constexpr auto INIT_POP_YEL_09 = 5041145;
  static constexpr auto INIT_POP_YEL_10 = 5041146;
  static constexpr auto INIT_POP_ADV_01 = 5041156;
  static constexpr auto INIT_POP_ADV_02 = 5041160;
  static constexpr auto INIT_POP_ADV_03 = 5041168;
  static constexpr auto INIT_POP_ADV_04 = 5041169;
  static constexpr auto INIT_POP_ADV_05 = 5041171;
  static constexpr auto INIT_POP_ADV_06 = 5041172;
  static constexpr auto INIT_POP_ADV_07 = 5041173;
  static constexpr auto INIT_POP_ADV_08 = 5041174;
  static constexpr auto INIT_POP_ADV_09 = 5041175;
  static constexpr auto INIT_POP_ADV_10 = 5041176;
  static constexpr auto INIT_POP_ADV_11 = 5041177;
  static constexpr auto INIT_POP_ADV_12 = 5041180;
  static constexpr auto INIT_POP_ADV_13 = 5041182;
  static constexpr auto INIT_POP_ADV_14 = 5041183;
  static constexpr auto INIT_POP_TAR_01 = 5041184;
  static constexpr auto INIT_POP_TAR_02 = 5041185;
  static constexpr auto INIT_POP_TAR_03 = 5041186;
  static constexpr auto INIT_ENPC_GIL_01 = 5040879;
  static constexpr auto INIT_ENPC_SLV_01 = 5040881;
  static constexpr auto INIT_ENPC_SLV_02 = 5040882;
  static constexpr auto INIT_ENPC_SLV_03 = 5040883;
  static constexpr auto INIT_ENPC_SLV_04 = 5040885;
  static constexpr auto INIT_ENPC_SLV_05 = 5040888;
  static constexpr auto INIT_ENPC_SLV_06 = 5040890;
  static constexpr auto INIT_POP_EOBJ_01 = 5041583;
  static constexpr auto INIT_POP_EOBJ_02 = 5041584;
  static constexpr auto INIT_POP_EOBJ_03 = 5041585;
  static constexpr auto INIT_POP_EOBJ_04 = 5041586;
  static constexpr auto INIT_POP_EOBJ_05 = 5041588;
  static constexpr auto INIT_POP_EOBJ_06 = 5041589;
  static constexpr auto BNPC_001 = 3399;
  static constexpr auto BNPC_002 = 3400;
  static constexpr auto BNPC_003 = 3401;
  static constexpr auto BNPC_004 = 3402;
  static constexpr auto INIT_P_POP_GIL_01 = 5041694;
  static constexpr auto INIT_POP_TAR_ADD_01 = 5041695;
  static constexpr auto INIT_POP_TAR_ADD_02 = 5041696;
  static constexpr auto QIB_YELL_03 = 2322;
  static constexpr auto QIB_YELL_04 = 2323;
  static constexpr auto QIB_YELL_05 = 2324;
  static constexpr auto QIB_YELL_07 = 2326;
  static constexpr auto QIB_YELL_08 = 2333;
  static constexpr auto QIB_YELL_09 = 2334;
  static constexpr auto EVENT_ACTION_01 = 16;
  static constexpr auto POP_RANGE_GUILD_MASTER_MOVE = 5048506;
  static constexpr auto BGM_LASTHALF = 39;
  static constexpr auto BEHAVIOR_CLAMOR = 30469;
  static constexpr auto BEHAVIOR_CLAMOR_A = 30490;
  static constexpr auto BEHAVIOR_CLAMOR_B = 30491;
  static constexpr auto LCUT_ACTOR0 = 1010200;
  static constexpr auto LCUT_ACTOR1 = 1010224;
  static constexpr auto LCUT_ACTOR2 = 1010225;
  static constexpr auto LCUT_POS0 = 5110371;
  static constexpr auto LCUT_POS1 = 5110372;
  static constexpr auto LCUT_POS2 = 5106386;
  static constexpr auto LCUT_ACTION0 = 918;
  static constexpr auto BEHAVIOR_CLAMOR_C = 30487;

public:
  StifledScreams() : Sapphire::ScriptAPI::QuestBattleScript( 91 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6228959, 5, { 457.583801f, 5.680784f, 280.512787f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2000608, 2807920, 4, { -95.322441f, -25.054260f, 61.518002f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( StifledScreams );