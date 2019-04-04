#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OneGolemtoRuleThemAll : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_BOSS_01 = 6843467;
  static constexpr auto P_BNPC_ZHAI_01 = 6845074;
  static constexpr auto P_BNPC_SHATO_01 = 6845075;
  static constexpr auto BNPC_GOLEM_01 = 6880074;
  static constexpr auto BNPC_GOLEM_C_01 = 6880075;
  static constexpr auto BNPC_METEOR_01 = 6880082;
  static constexpr auto BNPC_METEOR_02 = 6880083;
  static constexpr auto BNPC_METEOR_03 = 6880084;
  static constexpr auto STATUS_ATK_UP_STACK_INF = 2979;
  static constexpr auto CHANNELING_DARK = 14;
  static constexpr auto ACTION_METEOR_INPACT = 8561;
  static constexpr auto ACTION_DRAIN = 8560;
  static constexpr auto ACTION_METEOR_DEAD = 9017;
  static constexpr auto LOC_ACTOR0 = 1013068;
  static constexpr auto LOC_ACTOR1 = 1020698;
  static constexpr auto LOC_ACTOR2 = 1021902;
  static constexpr auto ACTION_TIMELINE_EVENT_LINK = 1002;
  static constexpr auto BGM_LAST_JOB = 36;
  static constexpr auto BGM_JOB_SHIREN = 91;
  static constexpr auto LOC_WEATHER = 2;
  static constexpr auto BNPC_METEOR_GOLEM_01 = 6987240;
  static constexpr auto BNPC_METEOR_GOLEM_02 = 6987241;
  static constexpr auto ACTION_METEOR_SUMMON_G = 9443;
  static constexpr auto BNPC_TOUMEI_SCAPEGOAT = 7011425;

public:
  OneGolemtoRuleThemAll() : Sapphire::ScriptAPI::QuestBattleScript( 168 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -142.306107f, 11.741690f, 188.300797f }, 1.000000f, 0.660768f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 5777776, 4, { -146.759598f, 9.382987f, 191.177994f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 5777778, 4, { -126.024696f, 11.736150f, 144.580200f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 165.208603f, 137.478806f, -62.228100f }, 1.000000f, -0.155188f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_2", 2002872, 5777792, 4, { 166.178696f, 137.607697f, -62.706631f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_wide", 2002872, 5777793, 4, { 180.090302f, 138.237793f, -115.812103f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -112.464798f, 348.165985f, -368.176514f }, 1.000000f, 0.335726f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_3", 2002872, 5777990, 4, { -112.426399f, 348.165985f, -371.392487f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_lvd_b0118_col_char_4", 2002872, 5777991, 4, { -89.965149f, 348.204498f, -416.112213f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -92.610641f, 348.164886f, -410.511993f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2005284, 5773453, 4, { -274.538086f, -4.016628f, 191.237701f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2005278, 5772621, 4, { -253.212296f, -2.894600f, 189.267303f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2005285, 5773460, 4, { -196.123306f, 3.106796f, 187.990906f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2005286, 5773461, 4, { -171.931305f, 2.815973f, 206.485794f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2005279, 5772623, 4, { -165.063995f, 4.074061f, 197.945007f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2005280, 5852453, 4, { 335.063385f, 114.335999f, -89.093300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2005281, 5777403, 4, { 247.495102f, 126.954300f, -30.577419f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2005282, 5773504, 4, { -173.859894f, 324.834686f, -273.653503f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2005283, 5773503, 4, { -191.639694f, 329.656799f, -321.158691f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5777084, 5, { -267.602997f, -18.376320f, 282.751190f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -278.421387f, -17.669189f, 277.700714f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OneGolemtoRuleThemAll );