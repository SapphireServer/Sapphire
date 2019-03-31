#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ShadesofShatotto : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_SHATOTO_01 = 6796562;
  static constexpr auto BNPC_MAGICCIRCLE_E01 = 6825338;
  static constexpr auto BNPC_ELEMENT_01 = 6826401;
  static constexpr auto BNPC_MAGICCIRCLE_G01 = 6826397;
  static constexpr auto BNPC_GOLEM_01 = 6825339;
  static constexpr auto BNPC_THUNDER_BALL = 6842624;
  static constexpr auto EOBJ_ICE_FLOOR = 6842626;
  static constexpr auto STATUS_ICE_FLOOR = 2868;
  static constexpr auto DEF_ACTION_ICE_FLOOR = 8113;
  static constexpr auto DEF_ACTION_THUNDER_BALL = 8114;
  static constexpr auto DEF_ACTION_FIREA_MULTI = 8112;
  static constexpr auto BNPC_TOUMEI_GTAE_POS1 = 6859149;
  static constexpr auto BNPC_TOUMEI_GTAE_POS2 = 6859157;
  static constexpr auto BNPC_TOUMEI_GTAE_POS3 = 6859159;
  static constexpr auto BNPC_TOUMEI_GTAE_POS4 = 6859163;
  static constexpr auto BNPC_TOUMEI_GTAE_POS5 = 6859167;
  static constexpr auto BNPC_TOUMEI_GTAE_POS6 = 6859170;
  static constexpr auto BNPC_TOUMEI_GTAE_POS7 = 6859172;
  static constexpr auto BNPC_TOUMEI_GTAE_POS8 = 6859176;
  static constexpr auto BNPC_TOUMEI_GTAE_POS9 = 6859185;
  static constexpr auto NCUT_01 = 1526;

public:
  ShadesofShatotto() : Sapphire::ScriptAPI::QuestBattleScript( 162 )
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

EXPOSE_SCRIPT( ShadesofShatotto );