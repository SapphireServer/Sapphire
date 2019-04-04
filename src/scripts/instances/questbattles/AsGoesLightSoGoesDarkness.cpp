#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AsGoesLightSoGoesDarkness : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto LOC_MARKER_01 = 6137635;
  static constexpr auto LOC_MARKER_02 = 6137636;
  static constexpr auto LOC_MARKER_03 = 6137639;
  static constexpr auto LOC_MARKER_04 = 6148118;
  static constexpr auto LOC_ACTOR0 = 1009751;
  static constexpr auto LOC_ACTOR1 = 1012497;
  static constexpr auto LOC_ACTOR2 = 1015886;
  static constexpr auto LOC_ACTOR10 = 1015853;
  static constexpr auto LOC_ACTOR11 = 1015854;
  static constexpr auto LOC_ACTOR12 = 1015855;
  static constexpr auto LOC_ACTOR13 = 1015856;
  static constexpr auto LOC_ACTOR14 = 1015887;
  static constexpr auto LOC_ACTOR15 = 1015888;
  static constexpr auto LOC_ACTOR_POP_100 = 6147799;
  static constexpr auto LOC_ACTOR_POP_101 = 6147800;
  static constexpr auto LOC_ACTOR_POP_102 = 6147801;
  static constexpr auto LOC_ACTOR_POP_103 = 6147802;
  static constexpr auto LOC_ACTOR_POP_104 = 6147803;
  static constexpr auto LOC_ACTOR_POP_110 = 6147805;
  static constexpr auto LOC_ACTOR_POP_111 = 6147806;
  static constexpr auto LOC_SE0 = 46;
  static constexpr auto LOC_BGM0 = 316;
  static constexpr auto P_BNPC_AYMERIC = 6149367;
  static constexpr auto P_BNPC_ARTOIREL = 6149368;
  static constexpr auto P_BNPC_THANCRED_01 = 6149369;
  static constexpr auto P_BNPC_ALPHINAUD = 6149370;
  static constexpr auto P_BNPC_YASHTOLA = 6149371;
  static constexpr auto P_BNPC_AYMERIC_AFTER_LCUT = 6154014;
  static constexpr auto P_BNPC_ARTOIREL_AFTER_LCUT = 6154015;
  static constexpr auto BNPC_SORD_ELE_FEM_P1_A01 = 6149344;
  static constexpr auto BNPC_PUGILIST_ELE_MALE_A02 = 6153943;
  static constexpr auto BNPC_ARCHER_ELE_FEM_A03 = 6153944;
  static constexpr auto BNPC_PUGILIST_HUM_MALE_A04 = 6160873;
  static constexpr auto BNPC_ARCHER_ELE_FEM_A05 = 6160890;
  static constexpr auto BNPC_ARCHER_ELE_FEM_B01 = 6160891;
  static constexpr auto BNPC_PUGILIST_ELE_MALE_B02 = 6160879;
  static constexpr auto BNPC_PUGILIST_HUM_MALE_B03 = 6160880;
  static constexpr auto BNPC_SORD_ELE_MALE_P2_C01 = 6149347;
  static constexpr auto BNPC_PUGILIST_ELE_MALE_C02 = 6160888;
  static constexpr auto BNPC_THAUMATURGE_ELE_FEM_C03 = 6160889;
  static constexpr auto BNPC_ARCHER_ELE_FEM_C04 = 6153938;
  static constexpr auto BNPC_PUGILIST_ELE_MALE_C05 = 6153939;
  static constexpr auto BNPC_PUGILIST_ELE_MALE_ADD01 = 6160943;
  static constexpr auto BNPC_ARCHER_ELE_FEM_ADD02 = 6160942;
  static constexpr auto BNPC_PUGILIST_HUM_MALE_ADD03 = 6153934;
  static constexpr auto BNPC_THAUMATURGE_ELE_FEM_ADD04 = 6153935;
  static constexpr auto BNPC_THAUMATURGE_ELE_FEM_D01 = 6153951;
  static constexpr auto BNPC_PUGILIST_HUM_MALE_D03 = 6160894;
  static constexpr auto BNPC_SORD_ELE_FEM_P3_E01 = 6149349;
  static constexpr auto BNPC_ARCHER_ELE_FEM_E02 = 6160908;
  static constexpr auto BNPC_ARCHER_ELE_FEM_E03 = 6160909;
  static constexpr auto BNPC_SORD_ELE_MALE_LEADER = 6149353;
  static constexpr auto BNPC_PUGILIST_HUM_MALE_F01 = 6160944;
  static constexpr auto BNPC_THAUMATURGE_ELE_MALE_F02 = 6160945;
  static constexpr auto BNPC_THAUMATURGE_ELE_MALE_G01 = 6160949;
  static constexpr auto BNPC_ARCHER_ELE_FEM_H01 = 6163963;
  static constexpr auto BNPC_THAUMATURGE_ELE_MALE_H02 = 6163964;
  static constexpr auto BNPC_PUGILIST_HUM_MALE_H03 = 6163965;
  static constexpr auto BNPC_ARCHER_ELE_FEM_H04 = 6163967;
  static constexpr auto BNPC_HORSE_DOLL_WHITE = 6153807;
  static constexpr auto BNPC_HORSE_DOLL_BLACK = 6153826;
  static constexpr auto P_BNPC_HOSTAGE_A = 6149336;
  static constexpr auto P_BNPC_HOSTAGE_B = 6149348;
  static constexpr auto P_BNPC_HOSTAGE_C = 6149355;
  static constexpr auto P_BNPC_HOSTAGE_D = 6149358;
  static constexpr auto P_BNPC_HOSTAGE_E = 6149362;
  static constexpr auto P_BNPC_HOSTAGE_F = 6149364;
  static constexpr auto EOBJ_DOOR_A = 6147777;
  static constexpr auto EOBJ_DOOR_B = 6147778;
  static constexpr auto EOBJ_DOOR_C = 6147780;
  static constexpr auto EOBJ_DOOR_D = 6147783;
  static constexpr auto EOBJ_DOOR_E = 6147784;
  static constexpr auto EOBJ_DOOR_F = 6147779;
  static constexpr auto EOBJ_SCREEN = 6147792;
  static constexpr auto PRANGE_AYMERIC_MOVE_01 = 6153771;
  static constexpr auto PRANGE_AYMERIC_MOVE_02 = 6153773;
  static constexpr auto PRANGE_AYMERIC_MOVE_03 = 6153820;
  static constexpr auto PRANGE_AYMERIC_MOVE_04 = 6153952;
  static constexpr auto PRANGE_AYMERIC_MOVE_HOSTAGE_A = 6163030;
  static constexpr auto PRANGE_AYMERIC_MOVE_HOSTAGE_B = 6163028;
  static constexpr auto PRANGE_ARTOIREL_MOVE_01 = 6153836;
  static constexpr auto PRANGE_ARTOIREL_MOVE_02 = 6153837;
  static constexpr auto PRANGE_ARTOIREL_MOVE_03 = 6153838;
  static constexpr auto PRANGE_ARTOIREL_MOVE_04 = 6163031;
  static constexpr auto PRANGE_ARTOIREL_MOVE_HOSTAGE_A = 6163029;
  static constexpr auto PRANGE_ARTOIREL_MOVE_HOSTAGE_B = 6163027;
  static constexpr auto PRANGE_YASHTOLA_MOVE_01 = 6153834;
  static constexpr auto PRANGE_YASHTOLA_MOVE_02 = 6153835;
  static constexpr auto PRANGE_THANCRED_MOVE_01 = 6153953;
  static constexpr auto PRANGE_PC_LCUT_WARP = 6153821;
  static constexpr auto ERANGE_THANCRED_ACTION_01 = 6153766;
  static constexpr auto ERANGE_SAVING_HOSTAGE_02 = 6153772;
  static constexpr auto ERANGE_P3PACK_MOVE = 6153812;
  static constexpr auto ERANGE_LCUT_START = 6153815;
  static constexpr auto ERANGE_GOOL = 6153829;
  static constexpr auto EOBJ_HOSTAGE_HANDCUFFS_01 = 6153827;
  static constexpr auto EOBJ_HOSTAGE_HANDCUFFS_02 = 6153828;
  static constexpr auto STATUS_BIND_INFINITY = 1975;
  static constexpr auto BNPC_TOUMEI_ADD_HATE = 6161053;
  static constexpr auto BNPC_TOUMEI_AYMERIC_FOLLOW = 6164149;

public:
  AsGoesLightSoGoesDarkness() : Sapphire::ScriptAPI::QuestBattleScript( 150 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5588600, 4, { 0.359463f, 300.000000f, 26.171600f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 0.428600f, 300.000000f, 24.562250f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2005580, 5873754, 4, { 0.360928f, 300.000000f, -15.306860f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2006743, 5474300, 4, { 39.139400f, -300.007690f, 29.587160f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2006744, 5474303, 4, { 43.961182f, -299.855103f, -30.197689f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2006745, 6143050, 4, { -34.927921f, -300.007690f, -80.460876f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2006746, 6147782, 4, { -38.559631f, -300.007690f, -72.068359f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2006747, 6147781, 4, { -38.986820f, -300.007690f, -30.014530f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2006748, 6143048, 4, { 52.795311f, -299.984589f, -36.063671f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2006749, 6147791, 4, { 0.604760f, -291.999908f, -117.413803f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Bonds", 2006752, 0, 4, { -52.262211f, -300.000793f, -27.878300f }, 0.991760f, 0.000144f ); 
    instance.registerEObj( "Bonds_1", 2006752, 0, 4, { 56.960300f, -299.984589f, -73.657806f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 5581166, 4, { -18.416611f, -292.000000f, -99.614120f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2002735, 0, 4, { -20.099001f, -292.000000f, -98.859291f }, 0.700000f, -1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_1", 2005106, 5581173, 4, { -0.494135f, -292.000000f, -117.713799f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_8", 2002735, 0, 4, { 18.757099f, 0.000000f, 72.079903f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 5583050, 4, { 17.161560f, 0.000000f, 73.880867f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_9", 2005087, 5474300, 4, { 37.735470f, -300.007690f, 30.228149f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2005088, 5499954, 4, { 51.884090f, -300.000000f, -35.577080f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2005089, 5474303, 4, { 44.255379f, -300.000000f, -31.015051f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2005090, 5474308, 4, { -36.242680f, -300.000000f, -29.871010f }, 1.000000f, -0.000345f ); 
    instance.registerEObj( "unknown_13", 2005091, 5474306, 4, { -37.591751f, -300.000000f, -69.819733f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2005092, 5499959, 4, { -33.701191f, -300.000000f, -79.843872f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2005093, 5499966, 4, { 6.953651f, -281.975708f, -150.744995f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2005094, 5476161, 4, { 101.518402f, -263.140503f, -12.115350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2005095, 5476162, 4, { 101.390800f, -263.204315f, 11.842000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2005096, 5474532, 4, { 99.222763f, -264.000000f, -0.362554f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2005097, 5499987, 4, { 22.634041f, 0.000000f, 71.960167f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2005098, 5499980, 4, { -17.585621f, 0.000000f, 72.136276f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2005099, 5444302, 4, { -92.607063f, -0.015320f, 0.076233f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2005100, 5499663, 4, { -52.663239f, 291.000000f, 42.623951f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2005101, 5499660, 4, { -67.359016f, 291.000000f, 42.656231f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2005102, 5499645, 4, { -66.869476f, 291.000000f, 55.587841f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2005103, 5499653, 4, { -53.398609f, 291.000000f, 55.570320f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2005104, 5499600, 4, { -46.140011f, 291.000000f, 48.667049f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5578486, 5, { -5.010592f, -300.000000f, 86.198753f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 11.135890f, -300.000000f, 78.862717f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.136796f, 299.977112f, -9.654591f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AsGoesLightSoGoesDarkness );