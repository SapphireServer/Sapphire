#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Random/RNGMgr.h>

#include <Actor/EventObject.h>
#include <Actor/Player.h>
#include <Actor/BNpc.h>

#include <Encounter/Encounter.h>

#include <WorldServer.h>

#include <Network/GamePacket.h>
#include <Network/GameConnection.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;

class Sastasha :
  public Sapphire::ScriptAPI::InstanceContentScript
{
private:
  enum Corals : int
  {
    Blue = 2000213,
    Red = 2000214,
    Green = 2000215
  };

  enum Variables : uint8_t
  {
    Coral,
    Shortcut,
  };

  enum Sequence : uint8_t
  {
    Seq1 = 1,
    Seq2 = 3,
    Seq3 = 7,
    Seq4 = 23,
    Seq5 = 31,
    SeqFinish = 255
  };

  static constexpr auto EventActionTouch = 24;
  static constexpr auto EventActionShort = 15;


  static constexpr uint32_t BGM_NORMAL{ 35 };               // From the Depths
  static constexpr uint32_t BGM_ENCOUNTER_BOSS{ 37 };       // A Fine Death
  static constexpr uint32_t BGM_ENCOUNTER_FINAL_BOSS{ 38 }; // Nemesis

  static constexpr uint32_t ENCOUNTER_CHOPPER{ 1 };
  static constexpr uint32_t PLACENAME_CATTERY{ 662 };
  static constexpr uint32_t BOSS_CHOPPER{ 4035011 };
  static constexpr uint32_t HP_CHOPPER{ 400 };

  static constexpr uint32_t ENCOUNTER_RAMBADE{ 2 };
  static constexpr uint32_t PLACENAME_RAMBADE{ 663 };
  static constexpr uint32_t BOSS_MADISON{ 3988325 };
  static constexpr uint32_t HP_MADISON{ 600 };

  static constexpr uint32_t ENCOUNTER_RAMBADE_2{ 3 };
  static constexpr uint32_t PLACENAME_RAMBADE_2{ 670 };
  static constexpr uint32_t BOSS_MADISON_2{ 4035056 };
  static constexpr uint32_t HP_MADISON_2{ 800 };

  static constexpr uint32_t ENCOUNTER_DENN{ 4 };
  static constexpr uint32_t PLACENAME_SULTANAS_LAP{ 672 };
  static constexpr uint32_t BOSS_DENN{ 3978771 };
  static constexpr uint32_t HP_DENN{ 1000 };

  // < groupName, vector< layoutId > >
  // todo: use this to track which trash groups need to drop eobj etc
  std::map< std::string, std::vector< uint32_t > > trashGroups;

public:
  Sastasha() :
    Sapphire::ScriptAPI::InstanceContentScript( 4 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    // Random coral
    auto& RNGMgr = Common::Service< Common::Random::RNGMgr >::ref();
    instance.setCustomVar( Coral, RNGMgr.getRandGenerator< uint32_t >( Corals::Blue, Corals::Green ).next() );

    switch( instance.getCustomVar( Coral ) )
    {
      case Corals::Blue:
        instance.addEObj( "Bloodymemo", 2000212, 0, 4072691, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f, -0.898762f, 0 );
        break;
      case Corals::Red:
        instance.addEObj( "Bloodymemo", 2001548, 0, 4072692, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f, -0.898762f, 0 );
        break;
      case Corals::Green:
        instance.addEObj( "Bloodymemo", 2001549, 0, 4072693, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f, -0.898762f, 0 );
        break;
    }

    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_0", 2000211, 0, 3280858, 4, { 367.827087f, 47.400051f, -226.694305f }, 4.714991f, 0.000432f, 0 );

    pEObj = instance.addEObj( "Bluecoralformation", 2000213, 3668215, 3280868, 4, { 75.869797f, 35.101421f, -32.537209f }, 0.930753f, 0.000240f, 0 );

    pEObj = instance.addEObj( "Redcoralformation", 2000214, 3668214, 3280879, 4, { 88.769371f, 31.135691f, -40.869640f }, 0.930753f, 0.000240f, 0 );

    pEObj = instance.addEObj( "Greencoralformation", 2000215, 3668216, 3280932, 4, { 64.988159f, 33.672821f, -56.690559f }, 0.991789f, 0.000048f, 0 );

    pEObj = instance.addEObj( "Inconspicuousswitch", 2000216, 3653858, 3280956, 4, { 62.907951f, 33.969521f, -31.172279f }, 1.000000f, -1.396264f, 0 );
    pEObj->setPermissionInvisibility( 1 );

    pEObj = instance.addEObj( "Hiddendoor", 2000217, 3653517, 3280959, 4, { 59.000000f, 32.000000f, -35.000000f }, 1.000000f, -2.007129f, 0 );
    pEObj->addCollisionBox( { 59.048332, 39.016666, -35.022537 }, 2.007129, 8.800000, 7.718333, 0.738304 );
    pEObj->setCollisionEnabled( true );

    pEObj = instance.addEObj( "Rambadedoor", 2000225, 3653865, 3281037, 4, { -35.299999f, 24.000000f, 60.799999f }, 1.000000f, -2.007129f, 0 );
    pEObj->addCollisionBox( { -35.299999, 29.043749, 60.799999 }, 2.007129, 7.260001, 5.795626, 0.300003 );
    pEObj->setCollisionEnabled( true );

    pEObj = instance.addEObj( "Captainsquarters", 2000227, 3687697, 3281045, 4, { -95.044670f, 20.513069f, 172.039597f }, 0.991789f, 0.000048f, 0 );
    pEObj->addCollisionBox( { -95.065819, 23.074062, 172.106201 }, -3.141593, 3.715981, 3.381584, 0.490808 );
    pEObj->setCollisionEnabled( true );

    pEObj = instance.addEObj( "WaveriderGate", 2000231, 3655909, 3281133, 4, { -130.600006f, 16.000000f, 156.800003f }, 1.000000f, -2.007129f, 0 );
    pEObj->addCollisionBox( { -130.600006, 20.793749, 156.800003 }, 2.007129, 7.260001, 5.795626, 0.300003 );
    pEObj->setCollisionEnabled( true );

    pEObj = instance.addEObj( "TheHole", 2000232, 3656260, 3281161, 4, { -36.000000f, 16.500000f, 163.300003f }, 1.000000f, 1.047198f, 0 );
    pEObj->addCollisionBox( { -36.000000, 22.126310, 163.300003 }, -2.094395, 7.590004, 6.187500, 0.525011 );
    pEObj->setCollisionEnabled( true );

    pEObj = instance.addEObj( "Rambadedoor_1", 2000236, 3655908, 3281175, 4, { -190.000000f, 7.000000f, 252.000000f }, 1.000000f, -2.443461f, 0 );
    pEObj->addCollisionBox( { -190.000000, 11.943748, 252.000000 }, 2.443461, 7.260001, 5.795626, 0.300003 );
    pEObj->setCollisionEnabled( true );

    pEObj = instance.addEObj( "unknown_3", 2000235, 3656262, 3281178, 4, { -156.500000f, 8.600000f, 252.500000f }, 1.000000f, 1.134464f, 0 );
    pEObj->addCollisionBox( { -156.500000, 14.225000, 252.500000 }, -2.007129, 7.590004, 6.187500, 0.525011 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 3281180, 4, { -314.279114f, 5.630589f, 348.735596f }, 0.900235f, 0.000336f, 0 );

    pEObj = instance.addEObj( "Giantclam", 2000222, 4208408, 3284776, 4, { 181.170303f, 32.104599f, -128.069000f }, 0.991789f, -0.862350f, 0 );
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8)

    pEObj = instance.addEObj( "WaveriderGatekey", 2000255, 0, 3332312, 4, { -95.515343f, 20.000000f, 177.197800f }, 1.000000f, 0.000000f, 0 );

    pEObj = instance.addEObj( "KeytotheHole", 2000256, 0, 3332313, 4, { -38.076599f, 17.232731f, 158.839401f }, 0.991760f, 1.561760f, 0 );

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1", 2000260, 4208409, 3424283, 4, { 166.318695f, 30.735420f, -128.312103f }, 0.991789f, 0.481030f, 0 );
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8)

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_1", 2000261, 4208410, 3425471, 4, { 158.800598f, 28.586321f, -76.340927f }, 0.991789f, 1.471638f, 0 );
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8)

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_2", 2000262, 4208411, 3425472, 4, { 125.463402f, 29.260550f, -51.934608f }, 0.991789f, -0.375975f, 0 );
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8)

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_3", 2000263, 4208412, 3425473, 4, { 126.070198f, 28.913260f, -99.908722f }, 1.000000f, 0.020540f, 0 );
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8)

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_4", 2000264, 4208413, 3425474, 4, { 97.055313f, 27.081551f, -70.264381f }, 0.991789f, -0.618915f, 0 );
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8)

    pEObj = instance.addEObj( "Unnaturalripples", 2000405, 3992454, 3741845, 4, { -301.973206f, 6.500000f, 300.029388f }, 0.991789f, 0.000048f, 0 );

    pEObj = instance.addEObj( "Unnaturalripples_1", 2000406, 3992452, 3741894, 4, { -302.037598f, 6.500000f, 336.047302f }, 1.000000f, 0.000000f, 0 );

    pEObj = instance.addEObj( "Unnaturalripples_2", 2000407, 3992449, 3741895, 4, { -338.036499f, 6.500000f, 300.206512f }, 0.991789f, 0.000048f, 0 );

    pEObj = instance.addEObj( "Unnaturalripples_3", 2000408, 3992453, 3741897, 4, { -337.929596f, 6.500000f, 335.975311f }, 1.000000f, 0.000000f, 0 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4033735, 4, { 344.705688f, 43.781551f, -217.365997f }, 0.991760f, 0.000048f, 0 );
    pEObj->setPermissionInvisibility( 1 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2001504, 4323996, 4036038, 4, { 94.597588f, 26.865030f, -68.584061f }, 1.000000f, 0.000000f, 0 );
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4)
    pEObj->addCollisionBox( { 98.210648, 29.116930, -61.158611 }, -0.916448, 10.500000, 5.000000, 0.750000 );
    pEObj->setPermissionInvisibility( 1 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0249", 2001505, 4323997, 4036039, 4, { 95.510597f, 26.620729f, -67.853653f }, 1.000000f, 0.000000f, 0 );
    // States -> vf_line_on (id: 10) vf_line_of (id: 11)

    pEObj = instance.addEObj( "unknown_2", 2001539, 3653864, 4036041, 4, { -158.560898f, 8.099012f, 214.344803f }, 0.991760f, 0.000048f, 0 );
    pEObj->addCollisionBox( { -162.986496, 11.158604, 219.803619 }, -0.261799, 3.088758, 3.731382, 0.510000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094_1", 2001540, 4056793, 4036043, 4, { -163.598602f, 8.026373f, 214.030106f }, 0.991760f, 0.000048f, 0 );
    // States -> vf_line_on (id: 12) vf_line_of (id: 13)

    pEObj = instance.addEObj( "sgpl_s1d1_bosswall", 2001508, 4236989, 4036045, 4, { -303.983612f, 5.576412f, 276.214111f }, 1.000000f, 0.000000f, 0 );
    pEObj->addCollisionBox( { -300.141296, 8.076687, 278.205902 }, -3.141593, 5.250000, 4.000000, 0.750000 );
    pEObj->addCollisionBox( { -345.069397, 7.546691, 278.205902 }, -3.141593, 10.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgpl_s1d1_bossline", 2001509, 4236990, 4036046, 4, { -305.302002f, 5.542851f, 275.750885f }, 1.000000f, 0.000000f, 0 );

    pEObj = instance.addEObj( "unknown_1", 2001506, 3653862, 4056797, 4, { -9.239832f, 24.789940f, 35.778252f }, 0.991760f, 0.000048f, 0 );
    pEObj->addCollisionBox( { -3.186494, 26.457243, 30.003618 }, -0.261799, 3.088758, 3.731382, 0.510000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094", 2001507, 4035750, 4056798, 4, { -2.841087f, 23.114571f, 38.090420f }, 0.991760f, 0.000048f, 0 );
    // States -> vf_line_on (id: 12) vf_line_of (id: 13)

    pEObj = instance.addEObj( "Entrance", 2000182, 4096706, 4096707, 5, { 361.881714f, 46.092751f, -225.181305f }, 1.000000f, 0.000000f, 0 );
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12)
    pEObj->addCollisionBox( { 359.516113, 47.920158, -228.417206 }, 0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 359.525909, 47.920158, -222.417206 }, 0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 362.516113, 47.920158, -225.413315 }, 1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 356.516113, 47.920158, -225.406235 }, 1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 357.416107, 47.920158, -227.517212 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 361.616119, 47.920158, -223.317200 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 361.616119, 47.920158, -227.517212 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 357.416107, 47.920158, -223.317200 }, -0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Captainsquarterskey", 2000250, 0, 4192068, 4, { -100.625000f, 15.600010f, 137.150696f }, 1.000000f, 0.000000f, 0 );

    pEObj = instance.addEObj( "sgpl_s1d1_sghit_ctrl", 2000223, 4200832, 4200772, 4, { -24.018980f, 18.475060f, 111.404900f }, 1.000000f, 0.000000f, 0 );
    pEObj->addCollisionBox( { -11.414590, 22.215639, 108.525803 }, 0.000000, 9.368054, 3.097398, 0.263885 );
  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {
    auto pEncounter = instance.getEncounter();
    if( pEncounter )
    {
      pEncounter->update( tickCount );

      Entity::BNpcPtr pBNpc = nullptr;

      if( pEncounter->getId() == ENCOUNTER_CHOPPER )
        pBNpc = pEncounter->getBNpc( BOSS_CHOPPER );
      else if( pEncounter->getId() == ENCOUNTER_RAMBADE )
        pBNpc = pEncounter->getBNpc( BOSS_MADISON );
      else if( pEncounter->getId() == ENCOUNTER_RAMBADE_2 )
        pBNpc = pEncounter->getBNpc( BOSS_MADISON_2 );
      else if( pEncounter->getId() == ENCOUNTER_DENN )
        pBNpc = pEncounter->getBNpc( BOSS_DENN );

      if( pBNpc )
      {
        // set the encounter to active if a player has aggro
        if( pBNpc->hateListGetHighest() && pEncounter->getStatus() == EncounterStatus::IDLE )
        {
          pEncounter->setStatus( EncounterStatus::ACTIVE );

          // todo: hacky workaround for undefined arena coords
          pEncounter->onEnterRange( pBNpc->hateListGetHighest() );
          pEncounter->onEnterRange( pBNpc );
        }
        // set the encounter as successful if boss is dead
        else if( !pBNpc->isAlive() && pEncounter->getStatus() == EncounterStatus::ACTIVE )
        {
          pEncounter->setStatus( EncounterStatus::SUCCESS );
        }
      }

      /*
      auto deadPlayers = 0;
      for( const auto& pPlayer : pEncounter->getPlayers() )
      {
        if( pPlayer->getHp() != 0 )
          break;

        ++deadPlayers;
      }
      */

      // all players dead probably, fail
      if( pEncounter->getStatus() == EncounterStatus::ACTIVE )
      {
        if( pBNpc->hateListGetHighest() == nullptr )
          pEncounter->setStatus( EncounterStatus::FAIL );
      }
    }
    /*
    if( madison && !madison->isAlive() )
    {
      instance.setVar( 0, Seq3 );
      instance.getEObjByName( "Rambadedoor" )->setPermissionInvisibility( 7 );
      madison2 = instance.createBNpcFromLayoutId( 4035056, 600, Common::BNpcType::Enemy );
      madison = nullptr;
    }

    if( madison2 && !madison2->isAlive() )
    {
      instance.getEObjByName( "Rambadedoor_1" )->setPermissionInvisibility( 7 );
      madison2 = nullptr;
    }

    if( denn && !denn->isAlive() )
    {
      instance.setVar( 0, SeqFinish );
      instance.sendDutyComplete();
      denn = nullptr;
    }
    */
  }

  void onTalk( InstanceContent& instance, Entity::Player& player, Entity::EventObject& eobj, uint32_t eventId ) override
  {
    if( eobj.getName() == "Bloodymemo" )
    {
      eventMgr().playScene( player, eventId, 1, HIDE_HOTBAR, { 1 } );
    }

    if( eobj.getName() == "Bluecoralformation" || eobj.getName() == "Redcoralformation" || eobj.getName() == "Greencoralformation" )
    {
      eventMgr().playScene( player, eventId, 1, HIDE_HOTBAR, { 1 }, 
                            [ & ]( Entity::Player& player, const Event::SceneResult& result )
                            {
                              if( result.getResult( 0 ) == 0 )
                              {
                                eventMgr().eventActionStart( player, getId(), EventActionTouch,
                                                            [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                                            { 
                                                              eobj.setPermissionInvisibility( 1 );

                                                              if( eobj.getBaseId() == instance.getCustomVar( Coral ) )
                                                              {
                                                                instance.getEObjByName( "Inconspicuousswitch" )->setPermissionInvisibility( 0 );
                                                                //instance.addEObj( "Inconspicuousswitch", 2000216, 3653858, 3280956, 4, { 62.907951f, 33.969521f, -31.172279f }, 1.000000f, -1.396264f, 0 );
                                                                instance.setVar( 0, Seq1 );
                                                                instance.sendEventLogMessage( player, instance, 2034, { 0, 0 } );
                                                              }
                                                              else
                                                              {
                                                                // TODO: spawn adds
                                                              }
                                                            },
                                                            nullptr, getId() );
                              }
                            } );
    }

    // Open the door and progress duty
    if( eobj.getName() == "Inconspicuousswitch" )
    {
      auto instanceContent = instance.shared_from_this()->getAsInstanceContent();
      auto director = std::static_pointer_cast< Event::Director >( instanceContent );

      std::shared_ptr< Encounter > pEncounter = instance.getEncounter();
      // set up chopper encounter
      if( pEncounter == nullptr || pEncounter->getId() < ENCOUNTER_CHOPPER )
      {
        pEncounter = std::make_shared< Encounter >( instanceContent, director, "dungeons/sastasha/Chopper" );
        EncounterSetup setup;
        setup.timelineName = "dungeons/sastasha/Chopper";
        // todo: make this a box
        setup.encounterShape = EncounterShape::CYLINDER;
        setup.position = { 74, 29, -46 };
        setup.position2 = { 40, 10, 0 };
        //{ { uint32_t layoutId, uint32_t hp, Common::BNpcType type, bool isBoss } }
        setup.bnpcSetupList = { { BOSS_CHOPPER, HP_CHOPPER, Common::BNpcType::Enemy, Entity::BNpcFlag::NoRoam, true } };
        // { { std::string name, uint32_t baseId, uint32_t boundInstanceId, uint32_t instanceId, uint8_t state, Common::Vector3 pos, float scale, float rotation, uint8_t permissionInvisibility } }
        setup.lockoutEntrances = { { "sgvf_w_lvd_b0250", 2001504, 4323996, 4036038, 4, { 94.597588f, 26.865030f, -68.584061f }, 1.000000f, 0.000000f, 1 } };
        setup.lockoutExits = { {} };
        setup.hasLockout = true;
        setup.placeName = PLACENAME_CATTERY;
        setup.bgmInCombat = 37;
        setup.bgmInTeri = 35;

        pEncounter->setEncounterSetup( setup );
        instance.setEncounter( pEncounter );
        pEncounter->init();
      }
      // chopper encounter is successful, set up the next encounter
      else if( pEncounter && pEncounter->getId() == ENCOUNTER_CHOPPER && pEncounter->getStatus() == EncounterStatus::SUCCESS )
      {
        eventMgr().eventActionStart( player, getId(), EventActionTouch, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                                      eobj.setPermissionInvisibility( 1 );

                                      auto pDoor = instance.getEObjByName( "Hiddendoor" );
                                      pDoor->setPermissionInvisibility( 7 );
                                      pDoor->setCollisionEnabled( false );

                                      instance.setVar( 0, Seq2 );
                                      instance.sendEventLogMessage( player, instance, 2064, { 0, 0 } );
                                      //madison = instance.createBNpcFromLayoutId( 3988325, 600, Common::BNpcType::Enemy );
        }, nullptr, getId() );
      }
    }

    // Pick up key and progress duty
    if( eobj.getName() == "Captainsquarterskey" )
    {
      eventMgr().eventActionStart( player, getId(), EventActionShort,
                                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                  {
                                    eobj.setPermissionInvisibility( 1 );
                                    instance.setVar( 0, Seq4 );
                                    instance.sendEventLogMessage( player, instance, 2031, { 2000512 } );
                                  },
                                  nullptr, getId() );
    }

    // Pick up 2nd key and set variable
    if( eobj.getName() == "WaveriderGatekey" )
    {
      eventMgr().eventActionStart( player, getId(), EventActionShort,
                                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                  {
                                    eobj.setPermissionInvisibility( 1 );
                                    instance.setVar( 0, Seq5 );
                                    instance.sendEventLogMessage( player, instance, 2031, { 2000513 } );
                                    //denn = instance.createBNpcFromLayoutId( 3978771, 1000, Common::BNpcType::Enemy );
                                  },
                                  nullptr, getId() );
    }

    // Open the door if the right key has been obtained
    if( ( eobj.getName() == "Captainsquarters" && instance.getDirectorVar( 0 ) == Seq4 ) || 
        ( eobj.getName() == "WaveriderGate" && instance.getDirectorVar( 0 ) == Seq5 ) )
    {
      eventMgr().playScene( player, eventId, 1, HIDE_HOTBAR, { 1 }, 
                            [ & ]( Entity::Player& player, const Event::SceneResult& result )
                            {
                              if( result.getResult( 0 ) == 0 )
                              {
                                eventMgr().eventActionStart( player, getId(), EventActionTouch,
                                                      [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                                      {
                                                        eobj.setPermissionInvisibility( 1 );
                                                        if( eobj.getName() == "Captainsquarters" )
                                                          instance.sendEventLogMessage( player, instance, 2059, { 668 } );
                                                        else
                                                          instance.sendEventLogMessage( player, instance, 2059, { 671 } );
                                                      },
                                                      nullptr, getId() );
                              }
                            } );
    }
  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

  void onDirectorVarChange( InstanceContent& instance, uint8_t var, uint8_t val ) override
  {
    // spawn madison
    if( var == 0 && val == Seq2 )
    {
      auto instanceContent = instance.shared_from_this()->getAsInstanceContent();
      auto director = std::static_pointer_cast< Event::Director >( instanceContent );

      auto pEncounter = std::make_shared< Encounter >( instanceContent, director, "dungeons/sastasha/Madison" );
      EncounterSetup setup;
      setup.timelineName = "dungeons/sastasha/Madison";
      // todo: make this a box
      setup.encounterShape = EncounterShape::CYLINDER;
      setup.position = { -17, 22, 48 };
      setup.position2 = { 40, 10, 0 };
      //{ { uint32_t layoutId, uint32_t hp, Common::BNpcType type, bool isBoss } }
      setup.bnpcSetupList = { { BOSS_MADISON, HP_MADISON, Common::BNpcType::Enemy, Entity::BNpcFlag::NoRoam, true } };
      // { { std::string name, uint32_t baseId, uint32_t boundInstanceId, uint32_t instanceId, uint8_t state, Common::Vector3 pos, float scale, float rotation, uint8_t permissionInvisibility } }
      setup.lockoutEntrances = { { "unknown_1", 2001506, 3653862, 4056797, 4, { -9.239832f, 24.789940f, 35.778252f }, 0.991760f, 0.000048f, 1 } };
      setup.lockoutExits = { { "Rambadedoor", 2000225, 3653865, 3281037, 4, { -35.299999f, 24.000000f, 60.799999f }, 1.000000f, -2.007129f, 0 } };
      setup.hasLockout = true;
      setup.placeName = PLACENAME_RAMBADE;
      setup.bgmInCombat = 37;
      setup.bgmInTeri = 35;

      pEncounter->setEncounterSetup( setup );
      instance.setEncounter( pEncounter );
      pEncounter->init();
    }
  }

  void onLeaveTerritory( InstanceContent& instance, Entity::Player& player ) override
  {
    if( instance.getDirectorVar( 0 ) != SeqFinish )
      return;

    if( auto quest = player.getQuest( 66211 ) )
      if( quest->getSeq() == 3 )
      {
        quest->setSeq( 255 );
        player.updateQuest( quest.value() );
      }
    else if( auto quest = player.getQuest( 65781 ) )
      if( quest->getSeq() == 3 )
      {
        quest->setSeq( 255 );
        player.updateQuest( quest.value() );
      }
  }

};

EXPOSE_SCRIPT( Sastasha );