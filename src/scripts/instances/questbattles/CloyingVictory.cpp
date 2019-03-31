#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class CloyingVictory : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1TEAM_EXC_01 = 5072084;
  static constexpr auto INIT_POP_1TEAM_EXC_02 = 5072086;
  static constexpr auto INIT_POP_1TEAM_EXC_03 = 5072087;
  static constexpr auto INIT_POP_1TEAM_CNJ_01 = 5072088;
  static constexpr auto INIT_POP_1TEAM_ARC_01 = 5072089;
  static constexpr auto INIT_POP_1TEAM_ARC_02 = 5072090;
  static constexpr auto INIT_POP_1TEAM_ARC_03 = 5072091;
  static constexpr auto INIT_POP_2TEAM_EXC_01 = 5072110;
  static constexpr auto INIT_POP_2TEAM_EXC_02 = 5072111;
  static constexpr auto INIT_POP_2TEAM_EXC_03 = 5072112;
  static constexpr auto INIT_POP_2TEAM_CNJ_01 = 5072114;
  static constexpr auto INIT_POP_2TEAM_ARC_01 = 5072115;
  static constexpr auto INIT_POP_2TEAM_ARC_02 = 5072117;
  static constexpr auto INIT_POP_2TEAM_ARC_03 = 5072119;
  static constexpr auto INIT_POP_3TEAM_BOS_01 = 5072145;
  static constexpr auto INIT_POP_3TEAM_GLA_01 = 5072146;
  static constexpr auto INIT_POP_3TEAM_GLA_02 = 5072147;
  static constexpr auto INIT_POP_3TEAM_GLA_03 = 5072148;
  static constexpr auto INIT_POP_EX_DEV_01 = 5072762;
  static constexpr auto INIT_POP_EX_DEV_02 = 5072763;
  static constexpr auto INIT_POP_EX_DEV_03 = 5072764;
  static constexpr auto INIT_POP_EX_GAR_01 = 5072766;
  static constexpr auto INIT_POP_EX_GAR_02 = 5072768;
  static constexpr auto INIT_POP_EX_GAR_03 = 5072765;
  static constexpr auto INIT_POP_NOTAR_01 = 5072780;
  static constexpr auto INIT_P_POP_NOTAR_01 = 5072782;
  static constexpr auto INIT_POP_NOTAR_02 = 5072784;
  static constexpr auto INIT_P_POP_NOTAR_02 = 5072783;
  static constexpr auto INIT_POP_NOTAR_03 = 5072785;
  static constexpr auto INIT_P_POP_NOTAR_03 = 5072786;
  static constexpr auto INIT_POP_ACTOR_EXPLOSION = 5110373;
  static constexpr auto INIT_P_POP_1ST_JACKE_01 = 5073620;
  static constexpr auto INIT_P_POP_1ST_PERIMU_01 = 5073621;
  static constexpr auto INIT_P_POP_1ST_VKEBBE_01 = 5073622;
  static constexpr auto INIT_NPC_MOVE_JACKE_01 = 5073744;
  static constexpr auto INIT_NPC_MOVE_PERIMU_01 = 5073745;
  static constexpr auto INIT_NPC_MOVE_VKEBBE_01 = 5073746;
  static constexpr auto DEVICE_BNPC_BASE_TYPE = 3470;
  static constexpr auto LOGMESSAGE_QIB_EXPLOSION_90 = 3246;
  static constexpr auto LOGMESSAGE_QIB_EXPLOSION_60 = 3247;
  static constexpr auto LOGMESSAGE_QIB_EXPLOSION_30 = 3248;
  static constexpr auto LOGMESSAGE_QIB_EXPLOSION_20 = 3249;
  static constexpr auto LOGMESSAGE_QIB_EXPLOSION_10 = 3250;
  static constexpr auto LOGMESSAGE_QIB_EXPLOSION_5 = 3251;
  static constexpr auto DEF_ACTION_EXPLOSION = 3201;
  static constexpr auto EOBJ_QIB_1 = 5071851;
  static constexpr auto EOBJ_QIB_2 = 5071920;
  static constexpr auto ER_RECT_01 = 5110387;
  static constexpr auto QIB_YELL_01 = 2343;
  static constexpr auto QIB_YELL_02 = 2344;
  static constexpr auto QIB_YELL_03 = 2345;
  static constexpr auto CUT_SCENE_01 = 688;
  static constexpr auto CUT_SCENE_02 = 689;
  static constexpr auto DEF_ACTION_EXPLOSION_TRIGGER = 3269;

public:
  CloyingVictory() : Sapphire::ScriptAPI::QuestBattleScript( 95 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Companychest", 2000470, 4255757, 4, { 90.371834f, 41.346722f, 60.735680f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Huntboard", 2004438, 4887771, 4, { 94.366341f, 40.247021f, 60.480110f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CloyingVictory );