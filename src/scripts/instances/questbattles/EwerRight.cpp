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
    instance.addEObj( "Entrance", 2000182, 5021407, 5021409, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 5022207, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2000412, 1824621, 3671487, 4, { 41.519749f, 31.998119f, -243.976501f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_1", 2000411, 2263931, 3671491, 4, { 12.924340f, 24.612749f, -195.452896f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2000410, 2263930, 3671493, 4, { 59.367592f, 22.826191f, -188.589005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrypoint", 2001278, 0, 3915596, 4, { 57.856419f, 22.763201f, -178.983093f }, 1.000000f, -1.095531f, 0); 
    instance.addEObj( "Entrypoint_1", 2001278, 0, 3915613, 4, { 18.769621f, 24.894320f, -193.620804f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrypoint_2", 2001278, 0, 3915615, 4, { 37.416389f, 32.348339f, -239.311096f }, 1.000000f, -0.652703f, 0); 
    instance.addEObj( "Poachedhide", 2001213, 0, 3891752, 4, { 394.645203f, -0.876246f, 14.063940f }, 1.000000f, -0.328607f, 0); 
    instance.addEObj( "Poachedhide_1", 2001213, 0, 3891753, 4, { 416.253815f, -0.631977f, 6.064347f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Poachedhide_2", 2001213, 0, 3891754, 4, { 441.281189f, -0.871319f, 5.591451f }, 1.000000f, -1.145925f, 0); 
    instance.addEObj( "Poachedhide_3", 2001213, 0, 3891755, 4, { 444.053986f, -1.354348f, -7.858485f }, 1.000000f, 0.769634f, 0); 
    instance.addEObj( "Poachedhide_4", 2001213, 0, 3891756, 4, { 427.091187f, 0.795383f, -21.211519f }, 1.000000f, 1.386498f, 0); 
    instance.addEObj( "Poachedhide_5", 2001213, 0, 3891757, 4, { 428.098694f, -0.372076f, -44.936699f }, 1.000000f, 0.361490f, 0); 
    instance.addEObj( "Poachedhide_6", 2001213, 0, 3891758, 4, { 388.528412f, 5.055710f, -41.158878f }, 0.991789f, 0.615184f, 0); 
    instance.addEObj( "Poachedhide_7", 2001213, 0, 3891759, 4, { 369.974701f, 2.409312f, -17.115330f }, 0.991789f, -1.035117f, 0); 
    instance.addEObj( "Stolencrate", 2001211, 0, 3893542, 4, { 309.890686f, 2.438642f, -15.921920f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolencrate_1", 2001211, 0, 3893554, 4, { 315.482605f, 0.489576f, 6.344935f }, 1.000000f, -1.233403f, 0); 
    instance.addEObj( "Stolencrate_2", 2001211, 0, 3893555, 4, { 293.996002f, 0.529292f, 16.107109f }, 1.000000f, -0.302822f, 0); 
    instance.addEObj( "Stolencrate_3", 2001211, 0, 3893556, 4, { 326.452606f, 1.409641f, -5.736907f }, 1.000000f, 0.065125f, 0); 
    instance.addEObj( "Stolencrate_4", 2001211, 0, 3893557, 4, { 299.152802f, -0.256716f, -10.429610f }, 1.000000f, -0.520127f, 0); 
    instance.addEObj( "Stolencrate_5", 2001211, 0, 3893558, 4, { 284.523010f, 1.461086f, 14.716700f }, 1.000000f, -1.474365f, 0); 
    instance.addEObj( "Stolencrate_6", 2001211, 0, 3893559, 4, { 318.418701f, 2.247562f, -18.365980f }, 1.000000f, -1.227122f, 0); 
    instance.addEObj( "Stolencrate_7", 2001211, 0, 3893560, 4, { 316.222412f, 0.155651f, 16.766951f }, 1.000000f, -0.731933f, 0); 
    instance.addEObj( "Entrance", 2001710, 4138604, 4138602, 5, { -78.116699f, 3.688327f, -39.524689f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Entrance_1", 2001710, 4138624, 4138622, 5, { 194.548599f, 13.313300f, 46.466358f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "TheBalance", 2005959, 0, 5898834, 4, { 136.800598f, 18.895130f, 75.564049f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "TheEwer", 2005960, 0, 5898836, 4, { 105.079201f, 24.025770f, 173.886902f }, 1.000000f, 0.725376f, 0); 
    instance.addEObj( "TheArrow", 2005961, 0, 5898837, 4, { 46.323479f, 24.970020f, 132.759506f }, 1.000000f, 0.920975f, 0); 
    instance.addEObj( "TheBole", 2005962, 0, 5898840, 4, { 75.653030f, 23.748159f, 200.252304f }, 1.000000f, -0.854824f, 0); 
    instance.addEObj( "TheSpire", 2005963, 0, 5898841, 4, { 47.082329f, 19.440081f, 217.822296f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "TheSpear", 2005964, 0, 5898842, 4, { 56.640099f, 12.526610f, 280.343414f }, 1.000000f, 0.903463f, 0); 
    instance.addEObj( "unknown_3", 2004356, 0, 4876927, 4, { 659.983582f, 21.846149f, 70.454659f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance_2", 2003673, 0, 4621850, 4, { -362.233490f, 1.217181f, 456.390015f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_3", 2005123, 0, 5584700, 4, { 614.997070f, 22.127399f, 83.073334f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Hulkinghogcarcass", 2002893, 0, 4499354, 4, { 467.401306f, 2.212447f, 154.063599f }, 0.991760f, 0.433121f, 0); 
    instance.addEObj( "unknown_4", 2004660, 0, 5099944, 4, { 170.997192f, 16.160179f, 59.052219f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005065, 0, 5607524, 4, { -225.261093f, 13.156470f, 56.919300f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2005066, 0, 5607529, 4, { 109.694603f, 24.166731f, 174.784805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2005067, 0, 5607536, 4, { -338.428711f, -0.067347f, 453.487488f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_3", 2005068, 0, 5607547, 4, { 604.605286f, 24.055861f, 105.129700f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2006322, 0, 5925629, 4, { 177.604706f, 14.795990f, 55.369701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2006313, 0, 5926377, 4, { 185.645096f, 14.040300f, 50.517399f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Overloadedwain", 2002403, 0, 4306922, 4, { 151.561203f, 18.129620f, -127.292297f }, 1.000000f, -1.500076f, 0); 
    instance.addEObj( "unknown_7", 2002407, 0, 4306923, 4, { 151.300507f, 17.340410f, -127.860397f }, 1.000000f, 0.553560f, 0); 
    instance.addEObj( "MarkoftheBuilder", 2004589, 0, 4982804, 4, { -279.111908f, 4.760251f, 297.794800f }, 0.991760f, 1.136364f, 0); 
    instance.addEObj( "MarkoftheKeeper", 2004590, 0, 4982805, 4, { 112.312103f, 25.242331f, 180.341705f }, 1.000000f, 0.121728f, 0); 
    instance.addEObj( "Claykrater", 2000961, 0, 3777736, 4, { -166.819000f, 9.467051f, -68.951370f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Witheredtreant", 2000725, 0, 3776231, 4, { 42.626968f, 4.274199f, 48.897511f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2000726, 0, 3776233, 4, { 42.628422f, 4.222789f, 48.897511f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd", 2000727, 0, 3762253, 4, { -226.459198f, 10.627730f, 16.678061f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Muddypotsherd_1", 2000728, 0, 3762254, 4, { -240.419205f, 11.106410f, 52.238739f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd_2", 2000729, 0, 3762256, 4, { -261.672485f, 16.412470f, 49.871571f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd_3", 2001184, 0, 3875403, 4, { -228.599701f, 13.824810f, 66.576767f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd_4", 2001185, 0, 3875404, 4, { -251.366592f, 14.166620f, 32.252441f }, 0.991789f, 1.120479f, 0); 
    instance.addEObj( "Muddypotsherd_5", 2001186, 0, 3875405, 4, { -238.464294f, 15.838870f, 17.265980f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd_6", 2001187, 0, 3875406, 4, { -213.814301f, 9.174041f, 19.635111f }, 0.991789f, 0.726399f, 0); 
    instance.addEObj( "Muddypotsherd_7", 2001188, 0, 3875407, 4, { -198.683502f, 6.976239f, 32.638371f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd_8", 2001189, 0, 3875408, 4, { -203.453003f, 9.440011f, 54.683540f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Muddypotsherd_9", 2001190, 0, 3875409, 4, { -213.227905f, 9.599085f, 62.954021f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Destination_4", 2000731, 0, 3777873, 4, { 87.151657f, 8.191072f, -74.345261f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2001651, 0, 4101229, 4, { -254.810394f, 15.060610f, 4.379272f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2001652, 0, 4101230, 4, { -255.790100f, 15.141020f, 3.643538f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2001653, 0, 4101231, 4, { -255.597107f, 14.962130f, 2.632248f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2001654, 0, 4101232, 4, { -255.676697f, 15.242050f, 4.474526f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2001359, 0, 3951346, 4, { -274.069214f, 22.196470f, -174.910995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2001360, 0, 3951353, 4, { -240.589096f, 7.755447f, -92.976707f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2001361, 0, 3951356, 4, { -206.772797f, 8.545876f, -81.818642f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_8", 2001362, 0, 3951357, 4, { -146.683807f, 7.302510f, -44.484200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_9", 2001363, 0, 3951361, 4, { -122.599602f, 4.438381f, -50.170559f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_10", 2001364, 0, 3951364, 4, { -175.622894f, 6.913669f, 4.099701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_11", 2001366, 0, 3951383, 4, { -105.779198f, 2.364898f, -57.375599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_12", 2001367, 0, 3951398, 4, { -209.033203f, 9.881900f, 111.748001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2004686, 0, 5021388, 4, { -335.539886f, 20.119431f, 616.384216f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004113, 0, 4722129, 4, { 446.995392f, 1.130214f, -110.054604f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???_1", 2004124, 0, 4722813, 4, { -185.961700f, -0.060072f, 444.449493f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_13", 2004282, 0, 4757269, 4, { 261.585297f, 15.432220f, -125.871803f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_14", 2004581, 0, 5101542, 4, { 354.733185f, 5.612688f, -30.140120f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_15", 2004582, 0, 5101543, 4, { 343.292694f, 2.437127f, 8.920555f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_16", 2004845, 0, 5101545, 4, { 362.531494f, 1.671068f, -18.454340f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Suspiciousthicket", 2004846, 0, 5101564, 4, { -181.445099f, 8.093226f, 101.304604f }, 0.991760f, 0.000048f, 0); 

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