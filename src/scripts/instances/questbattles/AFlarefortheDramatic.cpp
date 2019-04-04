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
  static constexpr auto BNPC_ACTION_MEGIDDO_FLAME = 4839;
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