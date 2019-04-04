#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AVermilionVendetta : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_XRHUNTIA = 6797880;
  static constexpr auto P_BNPC_ARIA = 6797881;
  static constexpr auto BNPC_PACK1_SKE_01 = 6797884;
  static constexpr auto BNPC_PACK1_SKE_02 = 6798700;
  static constexpr auto BNPC_PACK1_SKE_03 = 6798701;
  static constexpr auto BNPC_PACK2_SKE_01 = 6797885;
  static constexpr auto BNPC_PACK2_SKE_02 = 6798702;
  static constexpr auto BNPC_PACK2_SKE_03 = 6798703;
  static constexpr auto BNPC_PACK3_THA_01 = 6797888;
  static constexpr auto BNPC_PACK3_THA_02 = 6798705;
  static constexpr auto BNPC_PACK4_THA_01 = 6797891;
  static constexpr auto BNPC_PACK4_THA_02 = 6798706;
  static constexpr auto BNPC_PACK5_THA_01 = 6797892;
  static constexpr auto BNPC_PACK5_THA_02 = 6798707;
  static constexpr auto BNPC_PACK6_THA_BOSS = 6797901;
  static constexpr auto BNPC_PACK6_THA_01 = 6797900;
  static constexpr auto BNPC_PACK6_THA_02 = 6797899;
  static constexpr auto BNPC_SHADOW_BOSS = 6798708;
  static constexpr auto ER_PACK3_START = 6798710;
  static constexpr auto BGM_BOSSBATTLE = 37;
  static constexpr auto LOCKON_SHARE = 62;
  static constexpr auto STATUS_VULNERABILITY = 202;
  static constexpr auto ACTION_DARK_SHARE = 7981;
  static constexpr auto BNPC_GIMMICK_01 = 6798812;
  static constexpr auto BNPC_GIMMICK_02 = 6798813;
  static constexpr auto BNPC_GIMMICK_03 = 6798814;
  static constexpr auto BNPC_DARK_SPRITE_01 = 6798815;
  static constexpr auto BNPC_DARK_SPRITE_02 = 6798816;
  static constexpr auto BNPC_DARK_SPRITE_03 = 6798817;
  static constexpr auto CHANNELING_DARK = 1;
  static constexpr auto BNPCBASE_DARK_SPRITE = 6886;
  static constexpr auto STATUS_PARAM_REGEN = 2810;
  static constexpr auto STATUS_PARAM_INFINITY_INVINCIBLE = 1721;
  static constexpr auto PR_ARIA_MOVE_01 = 6798818;
  static constexpr auto BNPC_SUMMON_MAHOUJIN = 6824106;
  static constexpr auto PR_DARKBALL_MOVE_01 = 6825253;
  static constexpr auto BNPC_DARKBALL = 6824699;
  static constexpr auto DEF_ACTION_TORRIGER = 3269;
  static constexpr auto QIB_YELL_03 = 4784;

public:
  AVermilionVendetta() : Sapphire::ScriptAPI::QuestBattleScript( 164 )
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

EXPOSE_SCRIPT( AVermilionVendetta );