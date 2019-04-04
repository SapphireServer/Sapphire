#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class Quarantine : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_ALKAZOLKA_01 = 5874600;
  static constexpr auto BNPC_P1_GOLEM_01 = 5874601;
  static constexpr auto ACTION_PARTBREAK_TRIGGER = 3269;
  static constexpr auto LOC_POS1 = 5917735;
  static constexpr auto LOC_ACTOR1 = 1007111;
  static constexpr auto LOC_ACTOR2 = 1014729;
  static constexpr auto SE_ID_EVENT_TREMOR = 92;
  static constexpr auto LOGMESSAGE_PARTS_REBORN = 5347;
  static constexpr auto STATUS_DAMAGEUP = 1852;
  static constexpr auto LOC_BGM0 = 86;
  static constexpr auto BNPC_DUMMY_01 = 5962543;
  static constexpr auto ACTION_DUMMYPOP_TRIGGER = 4777;

public:
  Quarantine() : Sapphire::ScriptAPI::QuestBattleScript( 113 )
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

EXPOSE_SCRIPT( Quarantine );