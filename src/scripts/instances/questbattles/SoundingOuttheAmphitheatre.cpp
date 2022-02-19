#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SoundingOuttheAmphitheatre : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto LOC_MARKER_0 = 5855126;
  static constexpr auto LOC_ACTOR_0 = 1012442;
  static constexpr auto LOC_ACTOR_1 = 1012443;
  static constexpr auto LOC_ACTOR_2 = 1009991;
  static constexpr auto LOC_ACTOR_3 = 1009991;
  static constexpr auto LOC_ACTOR_4 = 1009991;
  static constexpr auto LOC_ACTOR_5 = 1009991;
  static constexpr auto INIT_POP_COMPANION_BNPC_ALPHINAUD = 5855526;
  static constexpr auto INIT_POP_COMPANION_BNPC_ESTINIEN = 5855527;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_A_ZAKO_KEN = 5855123;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_A_ZAKO_YARI = 5855522;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_B_ZAKO_JU = 5855524;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_B_ZAKO_GEN = 5855525;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_C_ZAKO_JU = 5855542;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_C_ZAKO_KEN_DRAGON = 5855541;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_D_ZAKO_GEN = 5855544;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_D_ZAKO_KEN_DRAGON = 5855543;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_E_ZAKO_KEN_DRAGON = 5855643;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_E_ZAKO_JU = 5855644;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_F_ZAKO_KEN_DRAGON = 5855648;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_F_BOSS = 5855647;
  static constexpr auto FOURTH_POP_ENEMY_BNPC_P4_G_ZAKO_KEN_DRAGON = 5855691;
  static constexpr auto FOURTH_POP_ENEMY_BNPC_P4_G_ZAKO_JU = 5855698;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_01 = 5855582;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_02 = 5855591;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_03 = 5855593;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_04 = 5855594;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_05 = 5855595;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_06 = 5855596;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_07 = 5855597;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_08 = 5855598;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_09 = 5855613;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_10 = 5855618;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_11 = 5855626;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_12 = 5855629;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_13 = 5855630;
  static constexpr auto LOC_MARKER0 = 5855126;
  static constexpr auto LOC_ACTOR0 = 1013665;
  static constexpr auto LOC_ACTOR1 = 1013666;
  static constexpr auto LOC_ACTOR2 = 1013667;
  static constexpr auto LOC_ACTOR3 = 1013668;
  static constexpr auto LOC_ACTOR4 = 1013669;
  static constexpr auto LOC_ACTOR5 = 1013670;
  static constexpr auto ACTION_TRANSFORM_TO_DRAG = 3930;
  static constexpr auto ACTION_TRANSFORM_TO_MSHUFUSHU = 3994;
  static constexpr auto QIB_YELL_01 = 2652;
  static constexpr auto QIB_YELL_02 = 2653;
  static constexpr auto STATUS_PARAM_DAMAGE_UP = 385;
  static constexpr auto LOC_ACTION_HAX = 934;
  static constexpr auto LOC_ACTION_HAX_BASE = 936;
  static constexpr auto PLAY_BGM_LCUT_DRAGON = 314;
  static constexpr auto PLAY_BGM_LCUT_HANYOB = 16;
  static constexpr auto PLAY_BGM_LCUT_DRAGONWAR = 316;

public:
  SoundingOuttheAmphitheatre() : Sapphire::ScriptAPI::QuestBattleScript( 108 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2001141, 0, 5891583, 4, { 252.521500f, 19.607790f, 552.788574f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2006376, 0, 5937404, 4, { 0.099157f, 113.226097f, 824.702515f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2005570, 0, 5887150, 4, { -864.774475f, -183.660004f, -679.736511f }, 0.991760f, -1.188709f, 0); 
    instance.addEObj( "Destination", 2005565, 0, 5868098, 4, { -428.034088f, -166.195801f, -411.866699f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2006236, 0, 5916340, 4, { -649.711304f, -176.450195f, -538.675171f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2006237, 0, 5916341, 4, { -637.686829f, -176.450195f, -558.359802f }, 0.991760f, 0.824617f, 0); 
    instance.addEObj( "Destination_3", 2006238, 0, 5916342, 4, { -645.151123f, -174.559402f, -477.921509f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter", 2006363, 0, 5933502, 4, { -145.599899f, -154.815994f, -503.467712f }, 1.000000f, 0.101768f, 0); 
    instance.addEObj( "Destination_4", 2005567, 0, 5868102, 4, { 249.256104f, -55.497131f, -406.515594f }, 0.991760f, 1.277873f, 0); 
    instance.addEObj( "Destination_5", 2005568, 0, 5868103, 4, { 344.136688f, -55.375000f, -428.488586f }, 0.991760f, -1.501740f, 0); 
    instance.addEObj( "Destination_6", 2005569, 0, 5868104, 4, { 296.711700f, -55.283451f, -459.250793f }, 0.991760f, -1.501932f, 0); 
    instance.addEObj( "Allaganteleporter_1", 2006364, 0, 5933503, 4, { 778.826721f, -17.959999f, -483.525604f }, 0.991800f, -0.767449f, 0); 
    instance.addEObj( "unknown_2", 2006357, 0, 5932938, 4, { 228.278503f, 15.208610f, 553.955872f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2005764, 0, 5932939, 4, { 228.214600f, 14.880500f, 553.987976f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2005465, 0, 5854603, 4, { -696.118713f, -37.054840f, 432.427094f }, 1.000000f, -0.847118f, 0); 
    instance.addEObj( "Entrance_1", 2005549, 0, 5868100, 4, { -56.497799f, 271.229004f, 0.217211f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2006358, 0, 5932940, 4, { -62.904671f, 271.232788f, -5.669081f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrypoint", 2006458, 0, 5963443, 4, { -62.475479f, 272.732788f, 6.245296f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Allaganteleporter_2", 2006374, 0, 5937249, 4, { 206.419998f, 21.774599f, 558.773987f }, 1.000000f, -0.046921f, 0); 
    instance.addEObj( "Deactivatedterminal", 2005552, 0, 5889580, 4, { -635.767578f, -176.470596f, -577.018677f }, 0.991760f, 1.264739f, 0); 
    instance.addEObj( "Helixterminal", 2005553, 0, 5889581, 4, { -635.767578f, -176.470596f, -577.018677f }, 0.991800f, 1.264739f, 0); 
    instance.addEObj( "Allaganteleporter_3", 2005554, 0, 5889582, 4, { -145.599899f, -154.815994f, -503.467712f }, 1.000000f, 0.101768f, 0); 
    instance.addEObj( "Allaganteleporter_4", 2005555, 0, 5889583, 4, { -145.599899f, -154.815994f, -503.467712f }, 1.000000f, 0.101768f, 0); 
    instance.addEObj( "Allaganteleporter_5", 2005557, 0, 5889588, 4, { 778.826721f, -17.959961f, -483.525604f }, 0.991760f, -0.767449f, 0); 
    instance.addEObj( "Allaganteleporter_6", 2005558, 0, 5889590, 4, { 778.826721f, -17.959999f, -483.525604f }, 0.991800f, -0.767449f, 0); 
    instance.addEObj( "Allaganteleporter_7", 2005560, 0, 5889593, 4, { 206.419601f, 21.774599f, 558.774170f }, 0.991760f, -0.453206f, 0); 
    instance.addEObj( "Allaganteleporter_8", 2005561, 0, 5889594, 4, { 206.419601f, 21.774599f, 558.774170f }, 0.991800f, -0.453206f, 0); 
    instance.addEObj( "Deactivatedterminal_1", 2005563, 0, 5889596, 4, { -58.104759f, 271.229004f, -4.099541f }, 0.991760f, 1.142594f, 0); 
    instance.addEObj( "Facilityterminal", 2005564, 0, 5889597, 4, { -58.104801f, 271.229004f, -4.099500f }, 0.991800f, 1.142594f, 0); 
    instance.addEObj( "AirshiptoIshgard", 2005372, 0, 5836083, 4, { -877.062927f, -184.313797f, -670.110291f }, 0.991760f, -0.678214f, 0); 
    instance.addEObj( "Allaganteleporter_9", 2005556, 0, 5889585, 4, { 213.880096f, -66.095032f, -612.001282f }, 1.000000f, -0.080963f, 0); 
    instance.addEObj( "Allaganteleporter_10", 2005559, 0, 5889591, 4, { 598.452881f, 18.753241f, 78.770218f }, 0.991760f, -0.757478f, 0); 
    instance.addEObj( "Allaganteleporter_11", 2005562, 0, 5889595, 4, { -175.888306f, -95.201103f, 465.026306f }, 0.991760f, -0.431405f, 0); 
    instance.addEObj( "unknown_5", 2005908, 0, 5892089, 4, { -529.219116f, -143.575897f, -580.444275f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cermetcontainer", 2005899, 0, 5892047, 4, { 545.414917f, 20.236309f, 802.878418f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Cermetcontainer_1", 2005900, 0, 5892048, 4, { 506.770111f, 16.861151f, 750.268188f }, 0.500000f, 0.822635f, 0); 
    instance.addEObj( "Cermetcontainer_2", 2005901, 0, 5892049, 4, { 605.345093f, 15.951490f, 708.073181f }, 0.500000f, -0.518275f, 0); 
    instance.addEObj( "Cermetcontainer_3", 2005902, 0, 5892050, 4, { 614.706177f, 20.236309f, 758.949402f }, 0.991760f, -1.009165f, 0); 
    instance.addEObj( "Cermetcontainer_4", 2005903, 0, 5892051, 4, { 544.649109f, 15.951490f, 760.644226f }, 1.000000f, -0.279566f, 0); 
    instance.addEObj( "unknown_6", 2005904, 0, 5892069, 4, { -375.864014f, -105.610497f, 710.407471f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2005905, 0, 5892070, 4, { -372.604187f, -105.869202f, 747.436829f }, 0.991760f, -0.027548f, 0); 
    instance.addEObj( "unknown_8", 2005906, 0, 5892071, 4, { -322.858612f, -106.609596f, 716.846191f }, 0.991760f, 0.000115f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SoundingOuttheAmphitheatre );