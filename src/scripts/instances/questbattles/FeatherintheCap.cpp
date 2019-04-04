#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FeatherintheCap : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_LUNA_01 = 5886119;
  static constexpr auto BNPC_SEBASTIAN_01 = 5886120;
  static constexpr auto BNPC_HUNTER_01 = 5886154;
  static constexpr auto BNPC_HUNTER_02 = 5886155;
  static constexpr auto BNPC_HUNTER_03 = 5886156;
  static constexpr auto BNPC_HUNTER_04 = 5886157;
  static constexpr auto BNPC_P1_GLD_01 = 5886121;
  static constexpr auto BNPC_P1_LNC_01 = 5886122;
  static constexpr auto BNPC_P1_LNC_02 = 5886123;
  static constexpr auto BNPC_P2_ACN_01 = 5886146;
  static constexpr auto BNPC_P2_LNC_01 = 5886147;
  static constexpr auto BNPC_P2_LNC_02 = 5886148;
  static constexpr auto BNPC_P2_ARC_01 = 5886149;
  static constexpr auto BNPC_P2_ARC_02 = 5886150;
  static constexpr auto BNPC_P2_ARC_03 = 5886151;
  static constexpr auto BNPC_P2_ARC_04 = 5886152;
  static constexpr auto BNPC_P2_ARC_05 = 5886153;
  static constexpr auto BNPC_P2_BANDERSNATCH_01 = 5890660;
  static constexpr auto ACTION_SUMMON = 4779;
  static constexpr auto LOC_ACTOR_HUNTER_01 = 1015097;
  static constexpr auto LOC_ACTOR_HUNTER_02 = 1015098;
  static constexpr auto LOC_ACTOR_HUNTER_03 = 1015099;
  static constexpr auto LOC_ACTOR_HUNTER_04 = 1015100;
  static constexpr auto LOC_ACTOR_JANE = 1014691;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_ACTOR_LEVE = 1014684;
  static constexpr auto LOC_ACTOR_CELIE = 1015074;
  static constexpr auto LOC_ACTOR_ENEMY_01 = 1015101;
  static constexpr auto LOC_ACTOR_ENEMY_02 = 1015102;
  static constexpr auto LOC_ACTOR_ENEMY_03 = 1015103;
  static constexpr auto LOC_LEVEL_ENEMY_01 = 5936432;
  static constexpr auto LOC_LEVEL_LEVE_01 = 5935764;
  static constexpr auto LOC_LEVEL_QUIMP_01 = 5935771;
  static constexpr auto LOC_BGM0 = 39;

public:
  FeatherintheCap() : Sapphire::ScriptAPI::QuestBattleScript( 121 )
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

EXPOSE_SCRIPT( FeatherintheCap );