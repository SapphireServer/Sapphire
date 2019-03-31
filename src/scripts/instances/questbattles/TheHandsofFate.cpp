#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheHandsofFate : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_LUNA_01 = 5890132;
  static constexpr auto P_BNPC_SEBAS_01 = 5890133;
  static constexpr auto P_BNPC_ABAN_01 = 5890135;
  static constexpr auto BNPC_SEIMEI_01 = 5890136;
  static constexpr auto BNPC_ZAKO_SORD_01 = 5890137;
  static constexpr auto BNPC_ZAKO_ARC_01 = 5890138;
  static constexpr auto BNPC_ZAKO_ARC_02 = 5890139;
  static constexpr auto BNPC_ZAKO_ADD_SORD_01 = 5890402;
  static constexpr auto BNPC_ZAKO_ADD_ARC_01 = 5890403;
  static constexpr auto BNPC_ZAKO_ADD_ARC_02 = 5890404;
  static constexpr auto BNPC_ZAKO_ADD_CNJ_01 = 5890405;
  static constexpr auto BNPC_TAROT_LIGHTNING_01 = 5890146;
  static constexpr auto BNPC_TAROT_FIRE_01 = 5890148;
  static constexpr auto BNPC_TAROT_EARTH_01 = 5890149;
  static constexpr auto BNPC_TAROT_ICE_01 = 5890150;
  static constexpr auto BNPC_TAROT_WATER_01 = 5890152;
  static constexpr auto BNPC_TAROT_WIND_01 = 5890153;
  static constexpr auto POP_RANGE_MOVE_SEITEN_01 = 5890464;
  static constexpr auto NCUT_01 = 989;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_0 = 1768;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_1 = 1769;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_2 = 1770;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_3 = 1771;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_4 = 1772;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_5 = 1773;
  static constexpr auto STATUS_PARAM_TIMESTOP_TAROT_6 = 1774;
  static constexpr auto ACTION_TIMESTOP = 4880;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto BNPCBASE_ENEMY_GLA = 4709;
  static constexpr auto BNPCBASE_ENEMY_ARC = 4710;
  static constexpr auto BNPCBASE_ENEMY_CNJ = 4711;
  static constexpr auto STATUS_PARAM_BLAZE_SPIKE = 1775;
  static constexpr auto BNPC_TOUMEI_FOLLOW_PLAYER_A = 5921771;
  static constexpr auto BNPC_TOUMEI_FOLLOW_PLAYER_B = 5921832;
  static constexpr auto STATUS_PARAM_ICE_SPIKE = 1778;
  static constexpr auto STATUS_PARAM_SHOCK_SPIKE = 1779;
  static constexpr auto CHANNELING_WATER = 3;
  static constexpr auto CHANNELING_WIND = 4;
  static constexpr auto CHANNELING_FIRE = 5;
  static constexpr auto CHANNELING_LIGHTENING = 6;
  static constexpr auto CHANNELING_EARTH = 7;
  static constexpr auto CHANNELING_ICE = 8;
  static constexpr auto LOG_MESSAGE_01 = 3290;
  static constexpr auto LOG_MESSAGE_02 = 3291;
  static constexpr auto QIB_YELL_01 = 2934;
  static constexpr auto QIB_YELL_02 = 2935;
  static constexpr auto QIB_YELL_03 = 2936;
  static constexpr auto QIB_YELL_04 = 2937;
  static constexpr auto ACTION_OFFER_MP_REGEN = 4882;
  static constexpr auto ACTION_OFFER_HASTE = 4883;
  static constexpr auto STATUS_PARAM_HASTE_FOR_SEIMEI = 1781;
  static constexpr auto LOC_ACTOR_SEVE = 1014701;
  static constexpr auto LOC_ACTOR_LEVE = 1014684;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_ACTOR_JANE = 1014691;
  static constexpr auto LOC_ACTOR_SERVANT_01 = 1015121;
  static constexpr auto LOC_ACTOR_SERVANT_02 = 1015122;
  static constexpr auto LOC_ACTOR_SERVANT_03 = 1015123;
  static constexpr auto LOC_LEVEL_LEVE = 5937551;
  static constexpr auto LOC_LEVEL_QUIMP = 5937552;
  static constexpr auto LOC_LEVEL_JANE = 5937553;
  static constexpr auto EOBJ_TAROT_WATER = 5926254;
  static constexpr auto EOBJ_TAROT_LIGHTENING = 5939358;
  static constexpr auto EOBJ_TAROT_FIRE = 5939361;
  static constexpr auto EOBJ_TAROT_EARTH = 5939365;
  static constexpr auto EOBJ_TAROT_ICE = 5939367;
  static constexpr auto EOBJ_TAROT_WIND = 5939371;
  static constexpr auto LOC_BGM0 = 91;
  static constexpr auto LOC_FACE0 = 608;

public:
  TheHandsofFate() : Sapphire::ScriptAPI::QuestBattleScript( 141 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheHandsofFate );