#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheVoidgateBreathesGloomy : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_DAZA_01 = 4294979;
  static constexpr auto INIT_POP_1_VOID_01 = 4294980;
  static constexpr auto INIT_POP_1_VOID_02 = 4294981;
  static constexpr auto INIT_POP_1_VOID_03 = 4294983;
  static constexpr auto INIT_POP_1_VOID_04 = 4294984;
  static constexpr auto INIT_POP_1_VOID_05 = 4294985;
  static constexpr auto INIT_POP_1_DMN_01 = 4294986;
  static constexpr auto INIT_POP_1_DMN_02 = 4294987;
  static constexpr auto INIT_POP_1_GST_01 = 4294988;
  static constexpr auto INIT_POP_1_GST_02 = 4294989;
  static constexpr auto INIT_POP_1_GST_03 = 4294990;
  static constexpr auto INIT_POP_2_VOID_01 = 4294992;
  static constexpr auto INIT_POP_2_VOID_02 = 4294993;
  static constexpr auto INIT_POP_2_VOID_03 = 4294994;
  static constexpr auto INIT_POP_2_VOID_04 = 4294995;
  static constexpr auto INIT_POP_2_VOID_05 = 4294996;
  static constexpr auto INIT_POP_2_VOID_06 = 4294997;
  static constexpr auto INIT_POP_2_VOID_07 = 4294998;
  static constexpr auto INIT_POP_2_DMN_01 = 4295000;
  static constexpr auto INIT_POP_2_DMN_02 = 4295001;
  static constexpr auto INIT_POP_2_DMN_03 = 4295002;
  static constexpr auto INIT_POP_2_GST_01 = 4295003;
  static constexpr auto INIT_POP_2_GST_02 = 4295004;
  static constexpr auto INIT_POP_2_GST_03 = 4295005;
  static constexpr auto INIT_POP_2_GST_04 = 4295006;
  static constexpr auto INIT_POP_3_VOID_01 = 4295008;
  static constexpr auto INIT_POP_3_VOID_02 = 4295009;
  static constexpr auto INIT_POP_3_VOID_03 = 4295010;
  static constexpr auto INIT_POP_3_VOID_04 = 4295011;
  static constexpr auto INIT_POP_3_VOID_05 = 4295012;
  static constexpr auto INIT_POP_3_VOID_06 = 4295013;
  static constexpr auto INIT_POP_3_VOID_07 = 4295014;
  static constexpr auto INIT_POP_3_DGAZE_01 = 4295015;
  static constexpr auto INIT_POP_3_DGAZE_02 = 4295016;
  static constexpr auto INIT_POP_3_DGAZE_03 = 4295017;
  static constexpr auto INIT_POP_3_GST_01 = 4295018;
  static constexpr auto INIT_POP_3_GST_02 = 4295019;
  static constexpr auto INIT_POP_3_GST_03 = 4295020;
  static constexpr auto INIT_POP_3_GST_04 = 4295021;
  static constexpr auto LOC_ACTOR0 = 1007898;
  static constexpr auto LOC_ACTOR1 = 1007895;
  static constexpr auto LOC_ACTOR2 = 1007895;
  static constexpr auto LOC_ACTOR3 = 1007895;
  static constexpr auto LOC_ACTOR4 = 1007895;
  static constexpr auto LOC_POS_ACTOR0 = 4328116;
  static constexpr auto JOB_STORY_MES = 3645;
  static constexpr auto LOC_BGM1 = 37;

public:
  TheVoidgateBreathesGloomy() : Sapphire::ScriptAPI::QuestBattleScript( 73 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheVoidgateBreathesGloomy );