#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BigSolleretstoFill : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_CONSTAINT = 5891815;
  static constexpr auto BNPC_P1_ACN_01 = 5891816;
  static constexpr auto BNPC_P1_GLA_01 = 5891818;
  static constexpr auto BNPC_P1_PGL_01 = 5891819;
  static constexpr auto BNPC_P1_PGL_02 = 5891820;
  static constexpr auto BNPC_P2_SUMMON_01 = 5891821;
  static constexpr auto BNPC_P3_SUMMON_01 = 5891822;
  static constexpr auto BNPC_P3_SUMMON_02 = 5891823;
  static constexpr auto BNPC_P2_DEATHGAZE_01 = 5891824;
  static constexpr auto BNPC_P3_DEATHGAZE_01 = 5891825;
  static constexpr auto BNPC_P3_DEATHGAZE_02 = 5891826;
  static constexpr auto POPTIME_P2_DEATHGAZE = 30;
  static constexpr auto POPTIME_P3_DEATHGAZE = 30;
  static constexpr auto LCUT_ACTOR0 = 1014655;
  static constexpr auto LCUT_ACTOR1 = 1014656;
  static constexpr auto LCUT_ACTOR2 = 1014657;
  static constexpr auto LCUT_ACTOR3 = 1014658;
  static constexpr auto LCUT_ACTOR4 = 1014659;
  static constexpr auto LCUT_POS_ACTOR0 = 5900235;
  static constexpr auto LCUT_POS_ACTOR1 = 5900238;
  static constexpr auto LCUT_POS_ACTOR2 = 5900239;
  static constexpr auto LCUT_POS_ACTOR3 = 5900240;
  static constexpr auto LCUT_POS_ACTOR4 = 5900241;

public:
  BigSolleretstoFill() : Sapphire::ScriptAPI::QuestBattleScript( 140 )
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

EXPOSE_SCRIPT( BigSolleretstoFill );