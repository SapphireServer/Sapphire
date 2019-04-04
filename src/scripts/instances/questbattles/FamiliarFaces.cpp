#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FamiliarFaces : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_ALPHINAUD = 5862338;
  static constexpr auto BNPC_COMPANION_BANUBANU = 5862336;
  static constexpr auto BNPC_CENTURIO_BOSS = 5862331;
  static constexpr auto BNPC_EMPIRE_SWORD_01_02 = 5862332;
  static constexpr auto BNPC_EMPIRE_SWORD_01_03 = 5862333;
  static constexpr auto BNPC_EMPIRE_SWORD_01_04 = 5862334;
  static constexpr auto BNPC_EMPIRE_MAGIC_01_05 = 5862335;
  static constexpr auto BNPC_EMPIRE_AIRSHIP_02_01 = 5864438;
  static constexpr auto BNPC_EMPIRE_SWORD_02_02 = 5864439;
  static constexpr auto BNPC_EMPIRE_SWORD_02_03 = 5864440;
  static constexpr auto BNPC_EMPIRE_SWORD_02_04 = 5864441;
  static constexpr auto BNPC_EMPIRE_MAGIC_02_05 = 5864442;
  static constexpr auto BNPC_EMPIRE_SWORD_03_01 = 5864443;
  static constexpr auto BNPC_EMPIRE_SWORD_03_02 = 5864444;
  static constexpr auto BNPC_COMPANION_PET_CARBUNCLE_RED = 5878644;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 4785;
  static constexpr auto QIB_YELL_01 = 2650;
  static constexpr auto QIB_YELL_02 = 2651;
  static constexpr auto LOC_MAKER_BANUBANU = 5916636;
  static constexpr auto LOC_MAKER_ZAKO01 = 5916640;
  static constexpr auto LOC_MAKER_ZAKO02 = 5916644;
  static constexpr auto LOC_MAKER_AL = 5916653;
  static constexpr auto LOC_MAKER_PC = 5916656;
  static constexpr auto LOC_MAKER_ZAKO03 = 5916663;
  static constexpr auto LOC_MAKER_TAICHO = 5916664;
  static constexpr auto LOC_ACTOR_AL = 1011887;
  static constexpr auto LOC_ACTOR_RONUBANU = 1012482;
  static constexpr auto LOC_ACTOR_TAICHO = 1012483;
  static constexpr auto LOC_ACTOR_ZAKO01 = 1012484;
  static constexpr auto LOC_ACTOR_ZAKO02 = 1012485;
  static constexpr auto LOC_ACTOR_ZAKO03 = 1012486;
  static constexpr auto LOC_MAKER_START = 5917403;
  static constexpr auto LOC_ACTION0 = 985;
  static constexpr auto LOC_ACTION1 = 4194;
  static constexpr auto BNPCSTATE_SCARED = 123;

public:
  FamiliarFaces() : Sapphire::ScriptAPI::QuestBattleScript( 107 )
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

EXPOSE_SCRIPT( FamiliarFaces );