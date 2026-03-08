#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class SealRockSeize : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SealRockSeize() : Sapphire::ScriptAPI::InstanceContentScript( 50004 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "sgvf_w_lvd_b0286", 2005325, 5810980, 5811163, 4, { 187.869202f, 8.108603f, 250.084000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 187.871902, 10.108603, 244.084000 }, -0.000000, 2.497972, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 187.870956, 10.108603, 256.083984 }, -0.000000, 2.500406, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 193.869202, 10.108603, 250.079605 }, -1.570451, 2.500640, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 181.869202, 10.108603, 250.082535 }, -1.570451, 2.504768, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 183.671265, 10.108603, 245.881927 }, -0.785398, 2.650707, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 192.067139, 10.108603, 254.286072 }, -0.785398, 2.644853, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 192.069199, 10.108603, 245.884003 }, 0.785398, 2.647780, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 183.669205, 10.108603, 254.283997 }, 0.785398, 2.647780, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0286_1", 2005326, 5810982, 5811164, 4, { 57.053249f, 17.165449f, -249.904694f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 57.055950, 19.165449, -255.904694 }, -0.000000, 2.497972, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 57.055008, 19.165449, -243.904694 }, -0.000000, 2.500406, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 63.053253, 19.165449, -249.909088 }, -1.570451, 2.500640, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 51.053253, 19.165449, -249.906158 }, -1.570451, 2.504768, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 52.855320, 19.165449, -254.106766 }, -0.785398, 2.650707, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 61.251179, 19.165449, -245.702621 }, -0.785398, 2.644853, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 61.253250, 19.165449, -254.104691 }, 0.785398, 2.647780, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 52.853249, 19.165449, -245.704697 }, 0.785398, 2.647780, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0286_2", 2005327, 5810983, 5811175, 4, { -314.464996f, 41.657890f, 126.635803f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -314.462311, 43.657890, 120.635803 }, -0.000000, 2.497972, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -314.463226, 43.657890, 132.635803 }, -0.000000, 2.500406, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -308.464996, 43.657890, 126.631409 }, -1.570451, 2.500640, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -320.464996, 43.657890, 126.634338 }, -1.570451, 2.504768, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -318.662933, 43.657890, 122.433731 }, -0.785398, 2.650707, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -310.267059, 43.657890, 130.837875 }, -0.785398, 2.644853, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -310.264984, 43.657890, 122.435806 }, 0.785398, 2.647780, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -318.665009, 43.657890, 130.835800 }, 0.785398, 2.647780, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "AllagantomelithA1", 2005338, 5821682, 5821708, 4, { 18.148529f, 18.849100f, 267.572693f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithA2", 2005339, 5821685, 5821709, 4, { 8.120948f, 21.013821f, 167.772705f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithA3", 2005340, 5821686, 5821711, 4, { 96.414833f, 34.135899f, 108.177002f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithA4", 2005341, 5821687, 5821714, 4, { 200.335693f, 30.775141f, 68.234734f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithB1", 2005342, 5821688, 5821716, 4, { 157.733093f, 4.437783f, -49.087921f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithB2", 2005343, 5821689, 5821719, 4, { 51.290970f, 32.733749f, -82.673607f }, 0.991760f, 0.000000f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithB3", 2005344, 5821690, 5821720, 4, { 74.829063f, 13.976150f, -16.412930f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithB4", 2005345, 5821691, 5821722, 4, { -47.222630f, 31.708929f, -92.240723f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithC2", 2005346, 5821693, 5821723, 4, { -163.868805f, 46.920021f, 1.751138f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithD2", 2005347, 5821695, 5821725, 4, { -32.930420f, 18.645050f, 19.141041f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithD3", 2005348, 5821697, 5821726, 4, { -62.119572f, 40.360111f, 48.813599f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithC4", 2005349, 5821698, 5821727, 4, { -148.508499f, 43.280338f, 161.458603f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithC3", 2005350, 5821699, 5821728, 4, { -167.072998f, 26.487570f, 71.059898f }, 0.991760f, 0.088708f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithC1", 2005351, 5821700, 5821730, 4, { -120.087196f, 28.019110f, -46.859772f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "AllagantomelithD1", 2005352, 5821701, 5821731, 4, { 15.841110f, 19.797770f, 101.591301f }, 0.991760f, 0.000048f, 0 ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1", 2005502, 5821737, 5858760, 4, { 18.255230f, 16.804850f, 267.227814f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_1", 2005503, 5821738, 5858773, 4, { 8.225257f, 19.763350f, 167.312195f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_2", 2005504, 5821739, 5858777, 4, { 96.322990f, 33.288559f, 107.972397f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_3", 2005505, 5821740, 5858780, 4, { 200.310593f, 29.688540f, 68.217537f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_4", 2005506, 5821741, 5858781, 4, { 157.696793f, 2.356474f, -49.159088f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_5", 2005507, 5821743, 5858782, 4, { 51.310070f, 31.154039f, -82.935127f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_6", 2005508, 5821744, 5858784, 4, { 74.846779f, 11.294810f, -16.719721f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_7", 2005509, 5821746, 5858785, 4, { -47.175869f, 29.272760f, -92.573776f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_8", 2005510, 5821747, 5858788, 4, { -164.055405f, 45.557041f, 1.093665f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_9", 2005511, 5821748, 5858795, 4, { -32.986580f, 17.328630f, 18.981670f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_10", 2005512, 5821749, 5858797, 4, { -62.187111f, 38.493420f, 48.440479f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_11", 2005513, 5821750, 5858798, 4, { -148.519196f, 41.333549f, 161.070908f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_12", 2005514, 5821751, 5858799, 4, { -167.089294f, 24.449400f, 70.683212f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_13", 2005515, 5821752, 5858800, 4, { -120.122597f, 27.122120f, -47.061981f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

    pEObj = instance.addEObj( "sgbg_s2p1_q1_ocup1_14", 2005516, 5821753, 5858801, 4, { 15.812600f, 18.748220f, 101.435699f }, 1.000000f, 0.000000f, 0 ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 


  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, Entity::EventObject& eobj, uint32_t eventId ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint64_t actorId ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

  void onLeaveTerritory( InstanceContent& instance, Entity::Player& player ) override
  {

  }

};

EXPOSE_SCRIPT( SealRockSeize );