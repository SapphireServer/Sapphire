#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SlavetotheCode : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_BOSS_01 = 5039764;
  static constexpr auto INIT_POP_1ST_CNJ_01 = 5039765;
  static constexpr auto INIT_POP_1ST_LNC_01 = 5039766;
  static constexpr auto INIT_POP_2ST_LNC_01 = 5039758;
  static constexpr auto INIT_POP_2ST_LNC_02 = 5039759;
  static constexpr auto INIT_POP_2ST_DODO_01 = 5039760;
  static constexpr auto INIT_POP_2ST_DODO_02 = 5039761;
  static constexpr auto INIT_POP_2ST_DODO_03 = 5039762;
  static constexpr auto INIT_POP_2ST_DODO_04 = 5039763;
  static constexpr auto INIT_POP_3ST_LNC_01 = 5039767;
  static constexpr auto INIT_POP_3ST_LNC_02 = 5039768;
  static constexpr auto INIT_POP_3ST_DODO_01 = 5039769;
  static constexpr auto INIT_POP_3ST_DODO_02 = 5039770;
  static constexpr auto INIT_POP_3ST_DODO_03 = 5039773;
  static constexpr auto INIT_POP_3ST_DODO_04 = 5039776;
  static constexpr auto INIT_POP_4ST_LNC_01 = 5039787;
  static constexpr auto INIT_POP_4ST_DODO_01 = 5039788;
  static constexpr auto INIT_POP_4ST_DODO_02 = 5039789;
  static constexpr auto INIT_POP_5ST_LNC_01 = 5039792;
  static constexpr auto INIT_POP_5ST_LNC_02 = 5039793;
  static constexpr auto INIT_POP_5ST_DODO_01 = 5039794;
  static constexpr auto INIT_POP_5ST_DODO_02 = 5039795;
  static constexpr auto INIT_POP_5ST_DODO_03 = 5071259;
  static constexpr auto INIT_POP_5ST_DODO_04 = 5071260;
  static constexpr auto INIT_P_POP_1ST_JACKE_01 = 5039796;
  static constexpr auto BNPC_PERIMU = 5039790;
  static constexpr auto BNPC_VKEBBE = 5039791;
  static constexpr auto BEHAVIOR_LOOK_AROUND = 30470;
  static constexpr auto LCUT_ACTOR0 = 1010200;
  static constexpr auto LCUT_ACTOR1 = 1010231;
  static constexpr auto LCUT_ACTOR2 = 1010232;
  static constexpr auto LCUT_ACTOR3 = 1010233;
  static constexpr auto LCUT_ACTOR4 = 1010234;
  static constexpr auto LCUT_ACTOR5 = 1010235;
  static constexpr auto LCUT_ACTOR6 = 1010236;
  static constexpr auto LCUT_POS0 = 5351202;
  static constexpr auto LCUT_POS1 = 5110374;
  static constexpr auto LCUT_POS2 = 5122283;
  static constexpr auto LCUT_POS3 = 5351312;
  static constexpr auto LCUT_ACTION0 = 983;
  static constexpr auto LCUT_ACTION1 = 985;
  static constexpr auto LCUT_BGM1 = 78;
  static constexpr auto LCUT_BGM2 = 39;

public:
  SlavetotheCode() : Sapphire::ScriptAPI::QuestBattleScript( 92 )
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

EXPOSE_SCRIPT( SlavetotheCode );