#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class RiseoftheMachinists : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_ROSTNSTHAL_01 = 5905383;
  static constexpr auto BNPC_COMPANION_STEPHANIVIEN_01 = 5905384;
  static constexpr auto BNPC_COMPANION_JOYE_01 = 5905385;
  static constexpr auto BNPC_COMPANION_SEREST_01 = 5905388;
  static constexpr auto BNPC_COMPANION_MACHINIST_01 = 5905389;
  static constexpr auto BNPC_COMPANION_MACHINIST_02 = 5905390;
  static constexpr auto BNPC_ENEMY_PACK_A_WYVERN_01 = 5905396;
  static constexpr auto BNPC_ENEMY_PACK_A_DRAGONFLY_01 = 5905397;
  static constexpr auto BNPC_ENEMY_PACK_A_DRAGONFLY_02 = 5905398;
  static constexpr auto BNPC_ENEMY_PACK_A_DRAGONFLY_03 = 5905399;
  static constexpr auto BNPC_ENEMY_PACK_B_THRUSTAEVIS_01 = 5905402;
  static constexpr auto BNPC_ENEMY_PACK_B_THRUSTAEVIS_02 = 5905403;
  static constexpr auto BNPC_ENEMY_PACK_B_THRUSTAEVIS_03 = 5905404;
  static constexpr auto BNPC_ENEMY_PACK_C_THRUSTAEVIS_01 = 5905414;
  static constexpr auto BNPC_ENEMY_PACK_C_DRAGONFLY_01 = 5905415;
  static constexpr auto BNPC_ENEMY_PACK_C_DRAGONFLY_02 = 5905417;
  static constexpr auto BNPC_ENEMY_PACK_D_WYVERN_01 = 5905420;
  static constexpr auto BNPC_ENEMY_PACK_D_THRUSTAEVIS_01 = 5905421;
  static constexpr auto BNPC_ENEMY_PACK_D_THRUSTAEVIS_02 = 5905422;
  static constexpr auto WARP_PC_POINT_01 = 5905488;
  static constexpr auto BNPC_COMPANION_ROSTNSTHAL_02 = 5905499;
  static constexpr auto BNPC_COMPANION_STEPHANIVIEN_02 = 5905500;
  static constexpr auto BNPC_COMPANION_JOYE_02 = 5905501;
  static constexpr auto BNPC_COMPANION_SEREST_02 = 5905627;
  static constexpr auto BNPC_COMPANION_MACHINIST_03 = 5905628;
  static constexpr auto BNPC_COMPANION_MACHINIST_04 = 5905629;
  static constexpr auto BNPC_COMPANION_TEDALGRINCHE_01 = 5905630;
  static constexpr auto BNPC_ENEMY_ELDER_WYVERN_01 = 5905655;
  static constexpr auto BNPC_ENEMY_PACK_E_WYVERN_01 = 5905657;
  static constexpr auto BNPC_ENEMY_PACK_E_DRAGONFLY_01 = 5905658;
  static constexpr auto BNPC_ENEMY_PACK_E_DRAGONFLY_02 = 5905659;
  static constexpr auto BNPC_ENEMY_PACK_F_THRUSTAEVIS_01 = 5905661;
  static constexpr auto BNPC_ENEMY_PACK_F_DRAGONFLY_01 = 5905662;
  static constexpr auto BNPC_ENEMY_PACK_F_DRAGONFLY_02 = 5905663;
  static constexpr auto BNPC_ENEMY_PACK_G_THRUSTAEVIS_01 = 5905667;
  static constexpr auto BNPC_ENEMY_PACK_G_THRUSTAEVIS_02 = 5905670;
  static constexpr auto BNPC_ENEMY_PACK_G_THRUSTAEVIS_03 = 5905672;
  static constexpr auto ENPC_TEDALGRINCHE_01 = 5905392;
  static constexpr auto ENPC_WITNESS_01 = 5905393;
  static constexpr auto ENPC_WITNESS_02 = 5905632;
  static constexpr auto CUT_SCENE_01 = 975;
  static constexpr auto LOGMESSAGE_TEDALGRINCHE_HP50 = 3274;
  static constexpr auto LOGMESSAGE_TEDALGRINCHE_HP25 = 3275;
  static constexpr auto STATUS_PARAM_TRANSFORM_MAYAYA = 1531;
  static constexpr auto LOC_ACTOR0 = 1014579;
  static constexpr auto LOC_ACTOR1 = 1014580;
  static constexpr auto LOC_ACTOR2 = 1015124;
  static constexpr auto LOC_ACTOR3 = 1014585;
  static constexpr auto LOC_ACTOR4 = 1014584;
  static constexpr auto LOC_ACTOR5 = 1014590;
  static constexpr auto LOC_MARKER_01 = 5932442;
  static constexpr auto LOC_MARKER_02 = 5932601;
  static constexpr auto LOC_BGM1 = 316;
  static constexpr auto BGM_BOSS_BATTLE = 91;

public:
  RiseoftheMachinists() : Sapphire::ScriptAPI::QuestBattleScript( 130 )
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

EXPOSE_SCRIPT( RiseoftheMachinists );