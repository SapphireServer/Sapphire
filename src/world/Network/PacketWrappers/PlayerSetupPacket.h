#ifndef _CORE_NETWORK_PACKETS_INITUIPACKET_H
#define _CORE_NETWORK_PACKETS_INITUIPACKET_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Client Player Initialization packet. This must be sent to the client
  * once upon connection to configure the UI.
  */
  class PlayerSetupPacket : public ZoneChannelPacket< FFXIVIpcPlayerSetup >
  {
  public:
    PlayerSetupPacket( Entity::Player& player ) :
      ZoneChannelPacket< FFXIVIpcPlayerSetup >( player.getId(), player.getId() )
    {
      initialize( player );
    };

  private:
    void initialize( Entity::Player& player )
    {
      memset( &m_data.unknownOword[ 0 ], 255, reinterpret_cast< uint64_t >( &m_data.unknown5_55c ) - reinterpret_cast< uint64_t >( &m_data.unknownOword[ 0 ] ) );

      m_data.contentId = player.getContentId();

      // TODO: Support rested experience.
      m_data.restedExp = 0;
      //m_data.padding = 0x100;
      m_data.charId = player.getId();
      m_data.race = player.getLookAt( Common::CharaLook::Race );
      m_data.tribe = player.getLookAt( Common::CharaLook::Tribe );
      m_data.gender = player.getLookAt( Common::CharaLook::Gender );
      m_data.currentClass = static_cast< uint8_t >( player.getClass() );
      m_data.currentJob = static_cast< uint8_t >( player.getClass() );
      m_data.maxLevel = player.getLevel();
      m_data.deity = static_cast< uint8_t >( player.getGuardianDeity() );
      m_data.namedayMonth = player.getBirthMonth();
      m_data.namedayDay = player.getBirthDay();
      // TODO: Support grand company status.
      m_data.cityState = player.getStartTown();
      //m_data.gcRank = GCRank::None;

      m_data.homepoint = player.getHomepoint();
      m_data.pose = player.getPose();

      memset( &m_data.name[ 0 ], 0, sizeof( m_data.name ) );
      strcpy( &m_data.name[ 0 ], player.getName().c_str() );

      //memcpy( m_data.aetheryte, player.getAetheryteArray(), sizeof( m_data.aetheryte ) );

      // Set the class levels and exp.
      for( uint8_t i = 0; i < 25; i++ )
      {
        m_data.levels[ i ] = player.getClassArray()[ i ];
        m_data.exp[ i ] = player.getExpArray()[ i ];
      }

      //memcpy( m_data.orchestrionMask, player.getOrchestrionBitmask(), sizeof( m_data.orchestrionMask ) );
      //m_data.orchestrionMask[0] = 0xFE;
      //memcpy( m_data.mountGuideMask, player.getMountGuideBitmask(), sizeof( m_data.mountGuideMask ) );
      memset( m_data.mountGuideMask, 0xFF, sizeof( m_data.mountGuideMask ) );
      
      //memcpy( m_data.unlockBitmask, player.getUnlockBitmask(), sizeof( m_data.unlockBitmask ) );
      //m_data.unlockBitmask[0] = 0xFD;
      //memcpy( m_data.discovery, player.getDiscoveryBitmask(), sizeof( m_data.discovery ) );
      //m_data.discovery[0] = 0xFB;
      //memcpy( m_data.howto, player.getHowToArray(), sizeof( m_data.howto ) );
      //m_data.howto[0] = 0xEF;
      // possibly max level or current level
      m_data.maxLevel = Common::MAX_PLAYER_LEVEL;
      m_data.expansion = Common::CURRENT_EXPANSION_ID;

      // df stuff
      // todo: actually do this properly
  //      m_data.unknown70[4] = 1; // enable df

      // enable all raids/guildhests/dungeons
      memset( m_data.unlockedDungeons, 0xFF, sizeof( m_data.unlockedDungeons ) );
      //m_data.unlockedDungeons[0] = 0xEE;
      memset( m_data.unlockedGuildhests, 0xFF, sizeof( m_data.unlockedGuildhests ) );
      //m_data.unlockedGuildhests[0] = 0xDF;
      memset( m_data.unlockedPvp, 0xFF, sizeof( m_data.unlockedPvp ) );
      //m_data.unlockedPvp[0] = 0xDE;
      memset( m_data.unlockedRaids, 0xFF, sizeof( m_data.unlockedRaids ) );
      //m_data.unlockedRaids[0] = 0xDD;
      memset( m_data.unlockedTrials, 0xFF, sizeof( m_data.unlockedTrials ) );
      //m_data.unlockedTrials[0] = 0xDB;
    };
  };

}

#endif /*_CORE_NETWORK_PACKETS_CINITUIPACKET_H*/
