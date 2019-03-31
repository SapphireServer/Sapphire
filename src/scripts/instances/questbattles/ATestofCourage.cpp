#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ATestofCourage : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_BUNCHIN = 7132423;
  static constexpr auto BNPC_KABUTO = 7132425;
  static constexpr auto BNPC_KEKKISAKAN = 7132432;
  static constexpr auto BNPC_SHIKITAHE = 7132433;
  static constexpr auto BNPC_ZUKIN = 7132434;
  static constexpr auto BNPC_MAKURA = 7132435;
  static constexpr auto BNPC_ENEMY_SAMURAI_4 = 7132436;
  static constexpr auto BNPC_ENEMY_SAMURAI_5 = 7132437;
  static constexpr auto BNPC_ENEMY_NINJA_4 = 7132438;
  static constexpr auto BNPC_ENEMY_NINJA_5 = 7132441;
  static constexpr auto BNPC_ENEMY_MANTA_1 = 7132439;
  static constexpr auto BNPC_ENEMY_MANTA_2 = 7132444;
  static constexpr auto BNPC_ENEMY_MANTA_4_WEAK = 7132457;
  static constexpr auto BNPC_ENEMY_MANTA_5_WEAK = 7132458;
  static constexpr auto BNPC_ENEMY_MANTA_6_WEAK = 7132459;
  static constexpr auto BNPC_ENEMY_SAMURAI_7_WEAK = 7132460;
  static constexpr auto BNPC_ENEMY_SAMURAI_8_WEAK = 7132461;
  static constexpr auto BNPC_ENEMY_SAMURAI_9_WEAK = 7132462;
  static constexpr auto BNPC_ENEMY_NINJA_7_WEAK = 7132463;
  static constexpr auto BNPC_ENEMY_NINJA_8_WEAK = 7132464;
  static constexpr auto BNPC_ENEMY_NINJA_9_WEAK = 7132465;
  static constexpr auto BNPC_ENEMY_MAGIC_1 = 7132467;
  static constexpr auto BNPC_ENEMY_MAGIC_2 = 7132468;
  static constexpr auto BNPC_ENEMY_SAMURAI_10 = 7132472;
  static constexpr auto BNPC_ENEMY_SAMURAI_11 = 7132473;
  static constexpr auto BNPC_ENEMY_SHAUGI = 7132474;
  static constexpr auto BNPC_TOUMEI_ETHER = 7144992;
  static constexpr auto BNPC_TOUMEI_ETHER_FOR_KABUTO = 7156920;
  static constexpr auto BNPC_TOUMEI_HATE = 7144993;
  static constexpr auto BNPC_TOUMEI_KABUTO_ULTIMATE = 7149030;
  static constexpr auto BNPC_WATERBALL_1 = 7151732;
  static constexpr auto BNPC_WATERBALL_2 = 7151733;
  static constexpr auto BNPC_WATERBALL_3 = 7151734;
  static constexpr auto BNPC_WATERBALL_4 = 7163733;
  static constexpr auto BNPC_WATERBALL_BIGACTION_1 = 7164425;
  static constexpr auto BNPC_WATERBALL_BIGACTION_2 = 7164426;
  static constexpr auto BNPC_TOUMEI_SHAUGI_ACTION_01 = 7151812;
  static constexpr auto BNPC_TOUMEI_SHAUGI_ACTION_02 = 7163734;
  static constexpr auto BNPC_TOUMEI_SHAUGI_ACTION_03 = 7163735;
  static constexpr auto BNPC_TOUMEI_SHAUGI_ACTION_04 = 7163736;
  static constexpr auto STATUS_PARAM_HOT = 3474;
  static constexpr auto STATUS_PARAM_TO_DAMAGE_UP = 3475;
  static constexpr auto STATUS_PARAM_TAKE_DAMAGE_DOWN = 3476;
  static constexpr auto STATUS_PARAM_STUN = 3464;
  static constexpr auto STATUS_PARAM_DAMAGE_UP = 3465;
  static constexpr auto STATUS_STUN = 930;
  static constexpr auto STATUS_PARAM_INVUL = 1496;
  static constexpr auto STATUS_DAMEGE_UP = 658;
  static constexpr auto ACTION_TOUMEI_EXEC_BUFF = 10031;
  static constexpr auto ACTION_IAIGIRI = 10035;
  static constexpr auto ACTION_GTAE = 10063;
  static constexpr auto ACTION_SHERE = 10064;
  static constexpr auto ACTION_SUMMON_WATERBALL = 10065;
  static constexpr auto ACTION_BIGACTION = 10051;
  static constexpr auto ACTION_DISTANCE_AWAY = 10072;
  static constexpr auto ACTION_RAIDDAMAGE = 10074;
  static constexpr auto ACTION_TOUMEI_SHERE = 10067;
  static constexpr auto EOBJ_TRESURE_1 = 7144991;
  static constexpr auto EOBJ_TRESURE_2 = 7146915;
  static constexpr auto EOBJ_TRESURE_3 = 7151735;
  static constexpr auto EOBJ_SHARED_CONTROL_1 = 7146130;
  static constexpr auto EOBJ_SHARED_CONTROL_2 = 7146132;
  static constexpr auto EOBJ_SHARED_CONTROL_2_2 = 7146133;
  static constexpr auto EOBJ_SHARED_CONTROL_3 = 7146134;
  static constexpr auto EOBJ_SHARED_CONTROL_3_BEFORE = 7156930;
  static constexpr auto EOBJ_SHARED_CONTROL_4 = 7146136;
  static constexpr auto EOBJ_SHARED_CONTROL_BOSS = 7151740;
  static constexpr auto EOBJ_SHARED_CONTROL_BOSS_ROOM = 7163737;
  static constexpr auto EVENTACTION_SYMPATHY = 60;
  static constexpr auto EVENT_RANGE_FOUND_BUNCHIN = 7156917;
  static constexpr auto EVENT_RANGE_PHASE3_KABUTO_MOVE01 = 7156924;
  static constexpr auto EVENT_RANGE_PHASE_3_BEFORE_ADD_POP = 7156931;
  static constexpr auto EVENT_RANGE_PHASE_3_ADD_POP = 7141113;
  static constexpr auto EVENT_RANGE_PHASE2 = 7146579;
  static constexpr auto EVENT_RANGE_BOSS = 7151385;
  static constexpr auto POP_RANGE_TRESURE_1 = 7141093;
  static constexpr auto POP_RANGE_PHASE_3_KABUTO = 7141094;
  static constexpr auto POP_RANGE_PHASE_4_KABUTO = 7141098;
  static constexpr auto POP_RANGE_PHASE_4_KABUTO_MOVE01 = 7163525;
  static constexpr auto POP_RANGE_TRESURE_3 = 7141115;
  static constexpr auto POP_RANGE_BOSS_PC = 7151386;
  static constexpr auto POP_RANGE_BOSS_KABUTO = 7151387;
  static constexpr auto POP_RANGE_TRESURE2_MOVE = 7146918;
  static constexpr auto POP_RANGE_TRESURE_3_NPC = 7151736;
  static constexpr auto POP_RANGE_TO_BUNCHIN_02 = 7140836;
  static constexpr auto POP_RANGE_TO_BUNCHIN_01 = 7156916;
  static constexpr auto POP_RANGE_PHASE2_KABUTO_01 = 7156921;
  static constexpr auto POP_RANGE_PHASE2_KABUTO_02 = 7156922;
  static constexpr auto POP_RANGE_PHASE3_KABUTO_MOVE01 = 7156923;
  static constexpr auto POP_RANGE_PHASE3_KABUTO_MOVE02 = 7156932;
  static constexpr auto POP_RANGE_PHASE3_KABUTO_MOVE03 = 7163484;
  static constexpr auto CHANNELING_DARK = 65;
  static constexpr auto CHANNELING_WATER = 3;
  static constexpr auto CHANNELING_DISTANCE_AWAY = 57;
  static constexpr auto LOCKON_SHARE = 62;
  static constexpr auto BGM_BOSS_BATTLE = 39;
  static constexpr auto POS_PLAYER = 7151729;
  static constexpr auto POS_HIRUMAKI = 7151730;
  static constexpr auto ACTION_EVENT_BASE_LIE1 = 981;
  static constexpr auto EVENT_MENACE = 946;

public:
  ATestofCourage() : Sapphire::ScriptAPI::QuestBattleScript( 179 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2008480, 6894787, 4, { 564.783630f, -60.304729f, -136.444901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004541, 0, 4, { 800.087585f, 0.000000f, 44.317749f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ATestofCourage );