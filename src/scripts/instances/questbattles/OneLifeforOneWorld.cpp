#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OneLifeforOneWorld : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_VITUS = 8007473;
  static constexpr auto P_BNPC_RADOVAN = 8007476;
  static constexpr auto P_BNPC_SOPHIE = 8007477;
  static constexpr auto BNPC_TRASH_RASER_001 = 8007480;
  static constexpr auto BNPC_TRASH_RASER_002 = 8007481;
  static constexpr auto BNPC_TRASH_RASER_003 = 8007482;
  static constexpr auto BNPC_TRASH_CANNON_001 = 8007484;
  static constexpr auto BNPC_TRASH_CANNON_002 = 8007487;
  static constexpr auto BNPC_TRASH_CANNON_003 = 8007488;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_001 = 8010353;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_002 = 8010354;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_003 = 8010355;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_004 = 8010356;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_005 = 8010357;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_006 = 8010358;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_ABOVE_SMALL = 8010367;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_ABOVE_MIDDLE = 8010368;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_ABOVE_BIG = 8010369;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_BELOW_SMALL = 8010371;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_BELOW_MIDDLE = 8010372;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_BELOW_BIG = 8010373;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_001 = 8010380;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_002 = 8010381;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_003 = 8010382;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_004 = 8010383;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_005 = 8010384;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_006 = 8010385;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_007 = 8010386;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_008 = 8010387;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_001 = 8010388;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_002 = 8010392;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_003 = 8010393;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_004 = 8010394;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_005 = 8010395;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_006 = 8010396;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_007 = 8010397;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_008 = 8010398;
  static constexpr auto BNPC_LANDMINE_001 = 8010469;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_12 = 8010470;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_12 = 8010475;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_2 = 8010491;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_2 = 8010492;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_3 = 8010493;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_3 = 8010494;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_4 = 8010495;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_4 = 8010496;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_6 = 8010502;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_6 = 8010503;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_8 = 8010511;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_8 = 8010512;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_9 = 8010547;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_9 = 8010548;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_10 = 8010549;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_10 = 8010550;
  static constexpr auto BNPC_TOMEI_VITUS_FINAL_RAIDDAMAGE = 8010594;
  static constexpr auto BNPC_TOMEI_VITUS_NOMAL_ACTION = 8010596;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_ABOVE_LEFT = 8010597;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_ABOVE_RIGHT = 8010598;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_BELOW_LEFT = 8010599;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_BELOW_RIGHT = 8010600;
  static constexpr auto BGM_BOSS = 165;
  static constexpr auto ACTION_VITUS_OCT_EXPLOSION_BLADE1 = 17551;
  static constexpr auto ACTION_VITUS_TRAP_POP = 17554;
  static constexpr auto ACTION_VITUS_SHARE_ATTACK = 17557;
  static constexpr auto ACTION_VITUS_BREAK_FRAGMENTS_BLADE = 17560;
  static constexpr auto ACTION_VITUS_DIMENSION_BLADE = 17562;
  static constexpr auto ACTION_VITUS_CROSS_BLADE = 17566;
  static constexpr auto ACTION_VITUS_ALL_ORDER = 17568;
  static constexpr auto ACTION_VITUS_FINAL_RAIDDAMAGE = 17572;
  static constexpr auto ACTION_VITUS_SHARE_ATTACK_HIT = 17558;
  static constexpr auto ACTION_PLAYER_GUNBREAKER_COMBO3 = 16145;
  static constexpr auto ACTION_PLAYER_GUNBREAKER_MAGICBULLET = 16150;
  static constexpr auto STATUS_PARAM_NPC_KNOCKDOWN = 5210;
  static constexpr auto ACTION_SOPHIE_BENEDICTION = 17587;
  static constexpr auto STATUS_PARAM_NPC_KNOCKDOWN_SHORT = 5206;
  static constexpr auto BGM_NO_MUSIC = 1;
  static constexpr auto PR_P2_VITUS_FINAL_RAIDDAMAGE_TOMEI_WARP_001 = 8012542;
  static constexpr auto ACTION_VITUS_QUICKSTEP = 17556;
  static constexpr auto ACTION_VITUS_WIDERANGE_EXPLOSION_SHOTGUN = 17569;
  static constexpr auto STATUS_NPC_KNOCKDOWN = 774;
  static constexpr auto ACTION_VITUS_FINAL_RAIDDAMAGE_HIT = 17573;
  static constexpr auto YELL_SOPHIE_003 = 8300;
  static constexpr auto ACTION_SOPHIE_STONE3 = 17603;
  static constexpr auto YELL_VITUS_002 = 8291;
  static constexpr auto YELL_VITUS_006 = 8299;
  static constexpr auto YELL_SOPHIE_004 = 8302;
  static constexpr auto ACTION_SOPHIE_MAGICPOW_DISTRIBUTION = 17589;
  static constexpr auto YELL_RADOVAN_003 = 8303;
  static constexpr auto YELL_RADOVAN_004 = 8304;
  static constexpr auto ACTION_RADOVAN_TANK_LIMITBREAK = 17576;
  static constexpr auto YELL_RADOVAN_002 = 8294;
  static constexpr auto YELL_SOPHIE_002 = 8295;
  static constexpr auto ACTION_VITUS_MOTIONCENCER_BOMB_NOMAL = 17580;
  static constexpr auto ACTION_VITUS_MOTIONCENCER_BOMB_SHORT = 17634;
  static constexpr auto ACTION_VITUS_MOTIONCENCER_BOMB_EXPLOSION = 17630;
  static constexpr auto STATUS_MOTION_CENCER_BOMB = 1072;
  static constexpr auto ACTION_TOMEI_DIMENSION_BLADE = 17563;
  static constexpr auto ACTION_VITUS_WIDERANGE_BLADE = 17559;
  static constexpr auto ACTION_VITUS_BLADE_FORCE = 17988;
  static constexpr auto BNPC_TOMEI_BLADE_FORCE = 8034825;
  static constexpr auto PR_RADVAN_LIMITBREAK_MOVE_RANGE = 8035357;
  static constexpr auto PR_SOPHIE_LIMITBREAK_MOVE_RANGE = 8035984;

public:
  OneLifeforOneWorld() : Sapphire::ScriptAPI::QuestBattleScript( 194 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 4177874, 5, { -16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 16.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2007452, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "BladeofLight", 2007454, 0, 4, { 0.000000f, 0.000000f, 11.300000f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OneLifeforOneWorld );