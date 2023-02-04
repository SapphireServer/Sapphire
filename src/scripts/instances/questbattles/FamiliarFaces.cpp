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
    instance.addEObj( "ClanHuntboard", 2005909, 5863338, 5892509, 4, { 73.908386f, 24.322830f, 22.067520f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2000608, 5105673, 5836320, 4, { 84.499992f, 24.124950f, 22.859011f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2000608, 5048108, 5836321, 4, { 97.900009f, 24.465071f, -4.244444f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2002273, 0, 5898500, 4, { 62.971050f, 23.979130f, -3.075622f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005898, 0, 5891872, 4, { 83.645264f, 23.979130f, -32.735580f }, 1.000000f, -0.381721f, 0); 
    instance.addEObj( "Destination_1", 2005910, 0, 5894424, 4, { 10.005710f, 1.279128f, 109.469704f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2005463, 0, 5860760, 4, { -185.413193f, 15.994000f, -49.339149f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2005550, 0, 5865259, 4, { 84.610123f, -6.970500f, 81.567253f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_3", 2005551, 0, 5865260, 4, { 38.278580f, -6.818152f, 76.358253f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_3", 2005763, 0, 5886043, 4, { 92.493622f, 15.000010f, 37.163952f }, 0.600000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2006267, 0, 5918660, 4, { -153.264801f, 16.979589f, -21.172760f }, 1.000000f, -1.468150f, 0); 
    instance.addEObj( "unknown_5", 2006278, 0, 5918730, 4, { -153.951706f, 16.999969f, -49.919941f }, 1.000000f, -0.857633f, 0); 
    instance.addEObj( "unknown_6", 2005533, 0, 5878492, 4, { -155.231995f, 17.497999f, -57.408001f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_7", 2005534, 0, 5886096, 4, { -154.955399f, 25.986080f, -55.649719f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_8", 2006424, 0, 5957331, 4, { -124.174500f, 6.716109f, 35.974468f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2006425, 0, 5957332, 4, { -126.827400f, 6.708973f, 38.789871f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2006426, 0, 5957333, 4, { -126.676804f, 6.709237f, 39.167229f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2006427, 0, 5957334, 4, { -129.981598f, 5.991162f, 37.839439f }, 1.100000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2006428, 0, 5957335, 4, { -129.934296f, 5.991236f, 38.043739f }, 1.100000f, 0.000000f, 0); 
    instance.addEObj( "Stainedsack", 2006254, 0, 5926806, 4, { 33.974140f, -12.000030f, 29.159000f }, 1.000000f, 0.421397f, 0); 

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