#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class EwerRight : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_FEMAIL_01 = 5885434;
  static constexpr auto BNPC_LUNA_01 = 5885435;
  static constexpr auto BNPC_SEBASTIAN_01 = 5885436;
  static constexpr auto BNPC_DIR_DUMMY_01 = 5926960;
  static constexpr auto BNPC_P1_GLD_01 = 5885437;
  static constexpr auto BNPC_P1_LNC_01 = 5885438;
  static constexpr auto BNPC_P1_LNC_02 = 5885439;
  static constexpr auto BNPC_P2_ACN_01 = 5885456;
  static constexpr auto BNPC_P2_LNC_01 = 5885457;
  static constexpr auto BNPC_P2_GLD_01 = 5885458;
  static constexpr auto BNPC_P2_GOLEM_01 = 5890367;
  static constexpr auto ACTION_SUMMON = 4779;
  static constexpr auto YELL_FEMAIL01_01 = 2649;
  static constexpr auto LOC_MARK_01 = 5932734;
  static constexpr auto LOC_ACTOR_LEVE = 1014684;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_ACTOR_AST = 1014955;
  static constexpr auto MOT_EVENT_LOOK_WEAPON = 1064;

public:
  EwerRight() : Sapphire::ScriptAPI::QuestBattleScript( 120 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EwerRight );