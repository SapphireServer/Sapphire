#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class MorethanaFeeler : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  MorethanaFeeler() : Sapphire::ScriptAPI::InstanceContentScript( 10009 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2001707, 0, 4127680, 4, { -614.880127f, -3.100000f, -60.755001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2001710, 4138685, 4138683, 5, { -598.732117f, -1.714300f, 9.483954f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_1", 2004812, 0, 5143397, 4, { -572.755005f, -1.696505f, -17.003180f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace", 2005835, 0, 5887310, 4, { 440.819214f, 4.107256f, 110.286598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_1", 2005839, 0, 5887311, 4, { 443.405701f, 8.115125f, 134.550598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_2", 2005843, 0, 5887312, 4, { 428.732697f, 7.888855f, 129.076004f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Aetherialtrace_3", 2005836, 0, 5887313, 4, { 468.506500f, 3.909009f, 94.483177f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_4", 2005840, 0, 5887314, 4, { 432.405212f, 4.109103f, 66.769440f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_5", 2005844, 0, 5887315, 4, { 467.398987f, 3.890991f, 79.609810f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Aetherialtrace_6", 2005837, 0, 5887316, 4, { 463.195312f, 3.909010f, 64.587334f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_7", 2005841, 0, 5887317, 4, { 410.121399f, 3.890898f, 58.253990f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Aetherialtrace_8", 2005845, 0, 5887318, 4, { 465.550812f, 3.908967f, 109.755699f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_9", 2005838, 0, 5887319, 4, { 443.110687f, 4.741745f, 74.515221f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Aetherialtrace_10", 2005842, 0, 5887320, 4, { 402.293793f, 3.908934f, 93.413658f }, 2.741264f, 0.099780f, 0); 
    instance.addEObj( "Aetherialtrace_11", 2005846, 0, 5887321, 4, { 410.471497f, 3.909006f, 73.024422f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Hiddenparchment", 2001892, 0, 4264402, 4, { -457.707397f, 29.192419f, 58.351582f }, 0.991760f, 0.289191f, 0); 
    instance.addEObj( "Hiddenparchment_1", 2001893, 0, 4264413, 4, { -388.696899f, 27.027069f, 45.588310f }, 0.991760f, -1.200395f, 0); 
    instance.addEObj( "Hiddenparchment_2", 2001894, 0, 4264414, 4, { -393.419098f, 42.564629f, -2.971054f }, 0.991760f, 0.282476f, 0); 
    instance.addEObj( "Oldwoodenbox", 2001895, 0, 4264446, 4, { -600.610413f, -3.390371f, -53.788090f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Oldwoodenbox_1", 2002478, 0, 4314621, 4, { -600.598816f, -3.163693f, -53.777821f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "ClsExc250", 2000295, 0, 3633524, 4, { -574.931580f, -1.449221f, -3.996652f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2004913, 0, 5110340, 4, { -436.545410f, -2.304138f, 48.599850f }, 0.800000f, 0.000048f, 0); 
    instance.addEObj( "Blackmarketeer", 2004916, 0, 5120198, 4, { -436.527588f, -2.003800f, 48.621601f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_1", 2002690, 0, 4374457, 4, { 381.565308f, 23.929300f, -138.263107f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_2", 2002707, 0, 4374458, 4, { 210.202896f, -2.049000f, 80.493843f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2001945, 0, 4268842, 4, { -620.569214f, -3.100000f, -49.759701f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Oblongfossil", 2001947, 0, 4268846, 4, { -449.912292f, 29.969191f, 10.849120f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "Oblongfossil_1", 2001948, 0, 4268847, 4, { -362.864594f, 56.403809f, -8.259895f }, 1.998901f, 0.814892f, 0); 
    instance.addEObj( "Roundfossil", 2002827, 0, 4488981, 4, { -418.364410f, 20.233049f, 58.420761f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "Roundfossil_1", 2002828, 0, 4488986, 4, { -373.909393f, 10.490130f, 88.547974f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "Oblongfossil_2", 2002829, 0, 4488989, 4, { -370.870514f, 59.220211f, -10.391420f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "Oblongfossil_3", 2002830, 0, 4488990, 4, { -428.244385f, 33.807590f, -0.686768f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2002083, 0, 4293527, 4, { 402.333588f, 8.721668f, 47.219742f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2002084, 0, 4293528, 4, { 437.288696f, 8.215124f, 133.049805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_3", 2002085, 0, 4293529, 4, { 404.886505f, 4.332874f, 88.459061f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Beastmanaetheryte", 2002086, 0, 4293686, 4, { 382.579895f, 25.278299f, -138.997299f }, 1.000000f, -1.388891f, 0); 
    instance.addEObj( "Destination_4", 2002096, 0, 4294929, 4, { 467.827301f, 3.908999f, 106.097000f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Warmwine", 2002260, 0, 4294931, 4, { 467.857910f, 3.908999f, 106.127502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_5", 2002842, 0, 4504651, 4, { 286.372192f, -3.128174f, 145.616806f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_6", 2002843, 0, 4504652, 4, { 298.423492f, -3.100000f, 166.933105f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2005469, 0, 5854719, 4, { 377.650299f, 0.796124f, -3.593968f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2005470, 0, 5854727, 4, { 398.188110f, -3.100000f, 11.229400f }, 1.300000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004938, 0, 5327277, 4, { -570.810608f, -1.522780f, -12.591280f }, 1.000000f, 0.548931f, 0); 
    instance.addEObj( "Destination_8", 2004930, 0, 5327285, 4, { 439.786499f, 12.164110f, 70.571907f }, 1.000000f, 1.152304f, 0); 
    instance.addEObj( "Weatheredcrate", 2005008, 0, 5392187, 4, { 208.299103f, -2.067544f, 259.849487f }, 0.700000f, -1.528726f, 0); 
    instance.addEObj( "unknown_5", 2005012, 0, 5392188, 4, { 208.299103f, -1.711737f, 259.849487f }, 1.000000f, -1.528727f, 0); 
    instance.addEObj( "Destination_9", 2005925, 0, 5895468, 4, { -449.088287f, -1.205505f, 116.594101f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_10", 2005926, 0, 5895469, 4, { -424.235107f, -5.147305f, 168.685699f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_11", 2005927, 0, 5895470, 4, { -457.730103f, -12.625930f, 218.931702f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Keystone", 2005520, 0, 5860073, 4, { 622.938171f, -3.052244f, 171.695999f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherialtrace_12", 2005529, 0, 5860458, 4, { 290.173706f, 41.276340f, -193.810501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005543, 0, 5862476, 4, { 405.141510f, 4.109600f, 81.067101f }, 0.991760f, -1.148674f, 0); 
    instance.addEObj( "Destination_12", 2002384, 0, 4305989, 4, { 256.798889f, -3.052744f, 60.951618f }, 0.400000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2002386, 0, 4306151, 4, { 256.381805f, -3.261654f, 58.147141f }, 0.400000f, -0.806658f, 0); 
    instance.addEObj( "Shabbycasket", 2003007, 0, 4516151, 4, { 600.538513f, -2.344561f, 173.115097f }, 1.000000f, -0.092533f, 0); 
    instance.addEObj( "Shabbycasket_1", 2003139, 0, 4532503, 4, { 600.538513f, -2.514199f, 173.115097f }, 1.000000f, -0.092534f, 0); 
    instance.addEObj( "unknown_8", 2003305, 0, 4540189, 4, { 600.538513f, -2.216532f, 173.115097f }, 1.000000f, -0.092534f, 0); 
    instance.addEObj( "unknown_9", 2004664, 0, 5021339, 4, { 496.981689f, 17.785681f, 64.169418f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004684, 0, 5021342, 4, { 212.096298f, -2.174379f, 254.544296f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2004691, 0, 5021396, 4, { 503.218414f, 16.560680f, 59.848129f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004108, 0, 4722038, 4, { 504.491302f, 16.908689f, 71.678238f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2004895, 0, 5120253, 4, { 242.957306f, -0.966233f, 257.617004f }, 1.000000f, 0.961899f, 0); 
    instance.addEObj( "Whimperingbarrel", 2004891, 0, 5120303, 4, { 274.665314f, -0.931000f, 230.617599f }, 1.000000f, -0.654481f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MorethanaFeeler );