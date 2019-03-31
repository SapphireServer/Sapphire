#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class MasterMusosai : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_MUSOSAI = 6783224;
  static constexpr auto LOC_ACTOR0 = 1020968;
  static constexpr auto LOC_ACTOR1 = 1020969;
  static constexpr auto LOC_ACTOR2 = 1020970;
  static constexpr auto LOC_ACTOR3 = 1022927;
  static constexpr auto LOC_ACTOR4 = 1022928;
  static constexpr auto LOC_MARKER_00 = 6942129;
  static constexpr auto LOC_MARKER_01 = 6942136;
  static constexpr auto LOC_SE0 = 142;
  static constexpr auto LOC_SE1 = 153;
  static constexpr auto LOC_BGM0 = 39;
  static constexpr auto BNPC_ENEMY_BEROALD = 6984416;
  static constexpr auto BNPC_ENEMY_AXE_01 = 6984417;
  static constexpr auto BNPC_ENEMY_AXE_02 = 6984418;
  static constexpr auto BNPC_ENEMY_BOW_01 = 6984419;
  static constexpr auto BNPC_ENEMY_BOW_02 = 6984442;
  static constexpr auto BNPC_ENEMY_BOW_03 = 6984443;
  static constexpr auto BNPC_ENEMY_BOW_04 = 6984457;
  static constexpr auto ENPC_SHOWMAN = 6942131;
  static constexpr auto BNPC_MUSOSAI_02 = 6997754;
  static constexpr auto BNPC_TOUMEI_SCAPEGOAT = 6997977;
  static constexpr auto BNPC_TOUMEI_BEROALD = 6984494;
  static constexpr auto PR_MOVE_BOW_POS_01 = 6984642;
  static constexpr auto PR_MOVE_BOW_POS_02 = 6984730;
  static constexpr auto PR_MOVE_BOW_POS_03 = 6984774;
  static constexpr auto PR_MOVE_BOW_POS_04 = 6984776;
  static constexpr auto PR_MOVE_BEROALD_POS = 6996457;
  static constexpr auto PR_PLAYER_SEC_POS = 6997801;
  static constexpr auto ACT_IAIDO_SINGLE = 7487;
  static constexpr auto ACT_IAIDO_MULTI = 7488;
  static constexpr auto ACT_IAIDO_DOT = 7489;
  static constexpr auto ACT_MUSOUSAI_KATSU = 9505;
  static constexpr auto ACT_FASTBLADE = 9503;
  static constexpr auto ACT_SAMURAI_W1 = 7477;
  static constexpr auto ACT_SAMURAI_W21 = 7478;
  static constexpr auto ACT_SAMURAI_W22 = 7479;
  static constexpr auto ACT_SAMURAI_W23 = 7480;
  static constexpr auto ACT_SAMURAI_W31 = 7481;
  static constexpr auto ACT_SAMURAI_W32 = 7482;
  static constexpr auto BNPCSTATE_ARM_CROSS = 169;
  static constexpr auto BNPCSTATE_ACTIVE = 1;
  static constexpr auto BEHAVIOR_BEROALD_BASE_01 = 31047;
  static constexpr auto BEHAVIOR_BEROALD_BASE_02 = 31048;
  static constexpr auto BEHAVIOR_BEROALD_BASE_03 = 31049;
  static constexpr auto BEHAVIOR_AXE01_BASE = 30066;
  static constexpr auto BEHAVIOR_AXE02_BASE = 30078;
  static constexpr auto STA_IAIDO_DOT = 2831;
  static constexpr auto YELL_MUSOUSAI_01 = 6324;
  static constexpr auto YELL_MUSOUSAI_02 = 6325;
  static constexpr auto YELL_MUSOUSAI_03 = 6326;
  static constexpr auto YELL_MUSOUSAI_04 = 6327;
  static constexpr auto YELL_MUSOUSAI_05 = 6328;
  static constexpr auto YELL_BEROALD_07 = 6335;
  static constexpr auto YELL_BEROALD_08 = 6336;
  static constexpr auto YELL_BEROALD_09 = 6337;
  static constexpr auto SE_APPLAUSE = 142;
  static constexpr auto LOC_BGM1 = 209;

public:
  MasterMusosai() : Sapphire::ScriptAPI::QuestBattleScript( 157 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2004364, 0, 4, { -93.101089f, -13.129550f, 6.845694f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Companychest", 2000470, 4255822, 4, { 128.974701f, 5.067919f, -40.913502f }, 1.000000f, -0.343160f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MasterMusosai );