#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ForwardtheRoyalMarines : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto EOBJ_A_COLOR_A_GARUKI = 5887310;
  static constexpr auto EOBJ_B_COLOR_B_HECTO = 5887311;
  static constexpr auto EOBJ_C_COLOR_C_ATARI = 5887312;
  static constexpr auto EOBJ_D_COLOR_A_GARUKI = 5887313;
  static constexpr auto EOBJ_E_COLOR_B_HECTO = 5887314;
  static constexpr auto EOBJ_F_COLOR_C_ATARI = 5887315;
  static constexpr auto EOBJ_G_COLOR_A_GARUKI = 5887316;
  static constexpr auto EOBJ_H_COLOR_B_HECTO = 5887317;
  static constexpr auto EOBJ_I_COLOR_C_ATARI = 5887318;
  static constexpr auto EOBJ_J_COLOR_A_GARUKI = 5887319;
  static constexpr auto EOBJ_K_COLOR_B_HECTO = 5887320;
  static constexpr auto EOBJ_L_COLOR_C_ATARI = 5887321;
  static constexpr auto BNPC_MEFUSAGI_01 = 5887404;
  static constexpr auto BNPC_ALKA_SEARCH_01 = 5889537;
  static constexpr auto BNPC_ALKA_FIGHT_01 = 5887405;
  static constexpr auto BNPC_JUKREN_SEARCH_01 = 5889756;
  static constexpr auto BNPC_JUKREN_FIGHT_01 = 5887406;
  static constexpr auto BNPC_KIEI_SEARCH_01 = 5889757;
  static constexpr auto BNPC_KIEI_FIGHT_01 = 5887407;
  static constexpr auto P_BNPC_SURITO_01 = 5887408;
  static constexpr auto P_BNPC_KAIHEI_01 = 5887409;
  static constexpr auto P_BNPC_KAIHEI_02 = 5889672;
  static constexpr auto P_BNPC_GUNSOU_01 = 5887410;
  static constexpr auto WARP_PC_POINT = 5887211;
  static constexpr auto BNPC_A_COLOR_A_GARUKI = 5888477;
  static constexpr auto BNPC_B_COLOR_B_HECTO = 5888488;
  static constexpr auto BNPC_D_COLOR_A_GARUKI = 5888478;
  static constexpr auto BNPC_E_COLOR_B_HECTO = 5888489;
  static constexpr auto BNPC_G_COLOR_A_GARUKI = 5888482;
  static constexpr auto BNPC_H_COLOR_B_HECTO = 5888490;
  static constexpr auto BNPC_J_COLOR_A_GARUKI = 5888486;
  static constexpr auto BNPC_K_COLOR_B_HECTO = 5888498;
  static constexpr auto BNPC_PARASITE_01 = 5888500;
  static constexpr auto BNPC_PARASITE_02 = 5888501;
  static constexpr auto BNPC_PARASITE_03 = 5888502;
  static constexpr auto BNPC_MEFUSAGI_EFFECT_01 = 5888510;
  static constexpr auto BNPC_MEFUSAGI_EFFECT_02 = 5931936;
  static constexpr auto BNPC_MEFUSAGI_EFFECT_03 = 5931939;
  static constexpr auto BNPC_MEFUSAGI_EFFECT_04 = 5931942;
  static constexpr auto ER_RECT_01 = 5888754;
  static constexpr auto NCUT_01 = 940;
  static constexpr auto NCUT_02 = 941;
  static constexpr auto EVENT_ACTION_01 = 21;
  static constexpr auto POP_RANGE_MOVE_MEFUSAGI_EFFECT_01 = 5888551;
  static constexpr auto LOC_POS1 = 5917738;
  static constexpr auto LOC_ACTOR1 = 1007111;
  static constexpr auto LOC_ACTOR2 = 1014649;
  static constexpr auto LOC_ACTOR3 = 1014650;
  static constexpr auto LOC_ACTOR4 = 1014661;
  static constexpr auto BEHAVIOR_TALK = 30073;
  static constexpr auto LOG_MESSAGE_OK_01 = 3293;
  static constexpr auto LOG_MESSAGE_OK_02 = 3294;
  static constexpr auto LOG_MESSAGE_OK_03 = 3295;
  static constexpr auto LOG_MESSAGE_NG_01 = 3296;
  static constexpr auto BGM_LAST_BATTLE = 91;
  static constexpr auto POP_RANGE_MOVE_FOLLOW_EFFECT_01 = 5931951;
  static constexpr auto ACTION_SUMMON_PARASITE = 4984;
  static constexpr auto STATUS_TRANSFORMATION = 565;
  static constexpr auto STATUS_TONBERRY_DISEASE = 785;
  static constexpr auto POP_RANGE_MOVE_JUKUREN_BATTLE_01 = 5932642;
  static constexpr auto POP_RANGE_MOVE_KIEI_BATTLE_01 = 5932643;
  static constexpr auto LOC_BGM0 = 117;
  static constexpr auto STATUS_PARAM_TONBERRY_DISEASE = 1501;

public:
  ForwardtheRoyalMarines() : Sapphire::ScriptAPI::QuestBattleScript( 135 )
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

EXPOSE_SCRIPT( ForwardtheRoyalMarines );