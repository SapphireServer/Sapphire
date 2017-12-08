#include <Server_Common/Common.h>
#include <Server_Common/Util/Util.h>
#include <Server_Common/Util/UtilMath.h>
#include <Server_Common/Config/XMLConfig.h>
#include <Server_Common/Network/GamePacket.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Network/PacketContainer.h>

#include "Session.h"
#include "Player.h"
#include "BattleNpc.h"

#include "Zone/ZoneMgr.h"
#include "Zone/Zone.h"

#include "ServerZone.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/ModelEquipPacket.h"
#include "Network/PacketWrappers/ActorSpawnPacket.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "Network/PacketWrappers/PlayerSpawnPacket.h"

#include "Script/ScriptManager.h"

#include "Inventory/Item.h"

#include "Inventory/Inventory.h"
#include "Event/Event.h"
#include "Action/Action.h"
#include "Action/EventAction.h"
#include "Action/EventItemAction.h"
#include "Zone/ZonePosition.h"
#include "Math/CalcStats.h"
#include "Math/CalcBattle.h"
#include <boost/make_shared.hpp>

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::Scripting::ScriptManager g_scriptMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

// player constructor
Core::Entity::Player::Player() :
   Actor(),
   m_lastWrite( 0 ),
   m_lastPing( 0 ),
   m_bIsLogin( false ),
   m_contentId( 0 ),
   m_modelMainWeapon( 0 ),
   m_modelSubWeapon( 0 ),
   m_homePoint( 0 ),
   m_startTown( 0 ),
   m_townWarpFstFlags( 0 ),
   m_playTime( 0 ),
   m_bInCombat( false ),
   m_bLoadingComplete( false ),
   m_bMarkedForZoning( false ),
   m_zoningType( Common::ZoneingType::None ),
   m_bAutoattack( false ),
   m_markedForRemoval( false ),
   m_mount( 0 )
{
   m_id = 0;
   m_objKind = ObjKind::Player;
   m_currentStance = Stance::Passive;
   m_onlineStatus = 0;
   m_queuedZoneing = nullptr;
   m_status = ActorStatus::Idle;
   m_invincibilityType = InvincibilityType::InvincibilityNone;

   memset( m_questTracking, 0, sizeof( m_questTracking ) );
   memset( m_name, 0, sizeof( m_name ) );
   memset( m_stateFlags, 0, sizeof( m_stateFlags ) );
   memset( m_searchMessage, 0, sizeof( m_searchMessage ) );
   memset( m_classArray, 0, sizeof( m_classArray ) );
   memset( m_expArray, 0, sizeof( m_expArray ) );
}

Core::Entity::Player::~Player()
{
   g_log.debug( "PlayerObj destroyed" );
}

// TODO: add a proper calculation based on race / job / level / gear
uint32_t Core::Entity::Player::getMaxHp()
{
   return m_baseStats.max_hp;
}

uint32_t Core::Entity::Player::getMaxMp()
{
   return m_baseStats.max_mp;
}

uint16_t Core::Entity::Player::getZoneId() const
{
   return m_zoneId;
}

uint8_t Core::Entity::Player::getGmRank() const
{
   return m_gmRank;
}

void Core::Entity::Player::setGmRank( uint8_t rank )
{
   m_gmRank = rank;
}

uint8_t Core::Entity::Player::getMode() const
{
   return m_mode;
}

void Core::Entity::Player::setMode( uint8_t mode )
{
   m_mode = mode;
}

uint8_t Core::Entity::Player::getStartTown() const
{
   return m_startTown;
}

void Core::Entity::Player::setMarkedForRemoval()
{
   m_markedForRemoval = true;
}

bool Core::Entity::Player::isMarkedForRemoval() const
{
   return m_markedForRemoval;
}

Core::Common::OnlineStatus Core::Entity::Player::getOnlineStatus()
{
   uint64_t newMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::NewAdventurer );
   uint64_t afkMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::AwayfromKeyboard );
   uint64_t busyMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::Busy );
   uint64_t dcMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::Disconnected );
   uint64_t meldMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::LookingtoMeldMateria );
   uint64_t ptMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::LookingforParty );
   uint64_t rpMask = uint64_t( 1 ) << static_cast< uint32_t >( OnlineStatus::Roleplaying );

   OnlineStatus status = OnlineStatus::Online;

   //if( hasStateFlag( Common::PlayerStateFlag::NewAdventurer ) )
   if( m_onlineStatus & newMask )
      status = OnlineStatus::NewAdventurer;

   if( m_onlineStatus & afkMask )
      status = OnlineStatus::AwayfromKeyboard;

   if( m_onlineStatus & busyMask )
      status = OnlineStatus::Busy;

   if( m_onlineStatus & dcMask )
      status = OnlineStatus::Disconnected;

   if( m_onlineStatus & meldMask )
      status = OnlineStatus::LookingtoMeldMateria;

   if( m_onlineStatus & ptMask )
      status = OnlineStatus::LookingforParty;

   if( m_onlineStatus & rpMask )
      status = OnlineStatus::Roleplaying;

   if( hasStateFlag( PlayerStateFlag::WatchingCutscene ) || hasStateFlag( PlayerStateFlag::WatchingCutscene1 ) )
      status = OnlineStatus::ViewingCutscene;

   // TODO: add all the logic for returning the proper online status, there probably is a better way for this alltogether
   return status;
}

void Core::Entity::Player::setOnlineStatusMask( uint64_t status )
{
   m_onlineStatus = status;
}

uint64_t Core::Entity::Player::getOnlineStatusMask() const
{
   return m_onlineStatus;
}

void Core::Entity::Player::prepareZoning( uint16_t targetZone, bool fadeOut, uint8_t fadeOutTime, uint16_t animation )
{
   ZoneChannelPacket< FFXIVIpcPrepareZoning > preparePacket( getId() );
   preparePacket.data().targetZone = targetZone;
   preparePacket.data().fadeOutTime = fadeOutTime;
   preparePacket.data().animation = animation;
   preparePacket.data().fadeOut = static_cast< uint8_t >( fadeOut ? 1 : 0 );
   queuePacket( preparePacket );
}

void Core::Entity::Player::calculateStats()
{
   uint8_t tribe = getLookAt( Common::CharaLook::Tribe );
   uint8_t level = getLevel();
   uint8_t job = static_cast< uint8_t >( getClass() );

   auto classInfoIt = g_exdData.m_classJobInfoMap.find( job );
   auto tribeInfoIt = g_exdData.m_tribeInfoMap.find( tribe );
   auto paramGrowthInfoIt = g_exdData.m_paramGrowthInfoMap.find( level );

   if( tribeInfoIt == g_exdData.m_tribeInfoMap.end() ||
       classInfoIt == g_exdData.m_classJobInfoMap.end() ||
       paramGrowthInfoIt == g_exdData.m_paramGrowthInfoMap.end() )
      return;

   auto tribeInfo = tribeInfoIt->second;
   auto classInfo = classInfoIt->second;
   auto paramGrowthInfo = paramGrowthInfoIt->second;

   // TODO: put formula somewhere else...
   float base = Math::CalcStats::calculateBaseStat( getAsPlayer() );

   m_baseStats.str =  static_cast< uint32_t >( base * ( static_cast< float >( classInfo.mod_str ) / 100 ) + tribeInfo.mod_str );
   m_baseStats.dex =  static_cast< uint32_t >( base * ( static_cast< float >( classInfo.mod_dex ) / 100 ) + tribeInfo.mod_dex );
   m_baseStats.vit =  static_cast< uint32_t >( base * ( static_cast< float >( classInfo.mod_vit ) / 100 ) + tribeInfo.mod_vit );
   m_baseStats.inte = static_cast< uint32_t >( base * ( static_cast< float >( classInfo.mod_int ) / 100 ) + tribeInfo.mod_int );
   m_baseStats.mnd =  static_cast< uint32_t >( base * ( static_cast< float >( classInfo.mod_mnd ) / 100 ) + tribeInfo.mod_mnd );
   m_baseStats.pie =  static_cast< uint32_t >( base * ( static_cast< float >( classInfo.mod_pie ) / 100 ) + tribeInfo.mod_pie );

   m_baseStats.skillSpeed      = paramGrowthInfo.base_secondary;
   m_baseStats.spellSpeed      = paramGrowthInfo.base_secondary;
   m_baseStats.accuracy        = paramGrowthInfo.base_secondary;
   m_baseStats.critHitRate     = paramGrowthInfo.base_secondary;
   m_baseStats.attackPotMagic  = paramGrowthInfo.base_secondary;
   m_baseStats.healingPotMagic = paramGrowthInfo.base_secondary;
   m_baseStats.tenacity        = paramGrowthInfo.base_secondary;

   m_baseStats.max_mp = Math::CalcStats::calculateMaxMp( getAsPlayer() );

   m_baseStats.max_hp = Math::CalcStats::calculateMaxHp( getAsPlayer() );

   if( m_mp > m_baseStats.max_mp )
      m_mp = m_baseStats.max_mp;

   if( m_hp > m_baseStats.max_hp )
      m_hp = m_baseStats.max_hp;


   m_baseStats.determination = static_cast< uint32_t >( base );

}


void Core::Entity::Player::setAutoattack(bool mode)
{
   m_bAutoattack = mode;
   m_lastAttack = Util::getTimeMs();
}

bool Core::Entity::Player::isAutoattackOn() const
{
   return m_bAutoattack;
}

void Core::Entity::Player::sendStats()
{
   ZoneChannelPacket< FFXIVIpcPlayerStats > statPacket( getId() );
   statPacket.data().strength = m_baseStats.str;
   statPacket.data().dexterity = m_baseStats.dex;
   statPacket.data().vitality = m_baseStats.vit;
   statPacket.data().intelligence = m_baseStats.inte;
   statPacket.data().mind = m_baseStats.mnd;
   statPacket.data().piety = m_baseStats.pie;
   statPacket.data().determination = m_baseStats.determination;
   statPacket.data().hp = m_baseStats.max_hp;
   statPacket.data().mp = m_baseStats.max_mp;
   statPacket.data().accuracy = m_baseStats.accuracy;
   statPacket.data().attack = m_baseStats.attack;
   statPacket.data().attackMagicPotency = m_baseStats.attackPotMagic;
   statPacket.data().healingMagicPotency = m_baseStats.healingPotMagic;
   statPacket.data().skillSpeed = m_baseStats.skillSpeed;
   statPacket.data().spellSpeed = m_baseStats.spellSpeed;
   statPacket.data().spellSpeed1 = m_baseStats.spellSpeed;
   statPacket.data().spellSpeedMod = 100;

   statPacket.data().criticalHitRate = m_baseStats.spellSpeed;
   statPacket.data().defense = m_baseStats.spellSpeed;
   statPacket.data().magicDefense = m_baseStats.spellSpeed;
   statPacket.data().attack = m_baseStats.spellSpeed;

   queuePacket( statPacket );
}

void Core::Entity::Player::teleport( uint16_t aetheryteId, uint8_t type )
{
   auto data = g_exdData.getAetheryteInfo( aetheryteId );

   if( data == nullptr )
   {
      return;
   }

   setStateFlag( PlayerStateFlag::BetweenAreas );
   sendStateFlags();

   auto z_pos = g_zoneMgr.getZonePosition( data->levelId );

   Common::FFXIVARR_POSITION3 pos;
   pos.x = 0;
   pos.y = 0;
   pos.z = 0;
   float rot = 0;

   if( z_pos != nullptr )
   {
      pos = z_pos->getTargetPosition();
      rot = z_pos->getTargetRotation();
   }

   sendDebug( "Teleport: " + data->placename + " " + data->placename_aethernet +
               "(" + std::to_string( data->levelId ) + ")" );

   // TODO: this should be simplified and a type created in server_common/common.h.
   if( type == 1 ) // teleport
   {
      prepareZoning( data->target_zone, true, 1, 112 );
      sendToInRangeSet( ActorControlPacket142( getId(), ActorDespawnEffect, 0x04 ) );
      setZoningType( Common::ZoneingType::Teleport );
   }
   else if( type == 2 ) // aethernet
   {
      prepareZoning( data->target_zone, true, 1, 112 );
      sendToInRangeSet( ActorControlPacket142( getId(), ActorDespawnEffect, 0x04 ) );
      setZoningType( Common::ZoneingType::Teleport );
   }
   else if( type == 3 ) // return
   {
      prepareZoning( data->target_zone, true, 1, 111 );
      sendToInRangeSet( ActorControlPacket142( getId(), ActorDespawnEffect, 0x03 ) );
      setZoningType( Common::ZoneingType::Return );
   }

   m_queuedZoneing = boost::make_shared< QueuedZoning >( data->target_zone, pos, Util::getTimeMs(), rot );


}

void Core::Entity::Player::forceZoneing( uint32_t zoneId )
{
   m_queuedZoneing = boost::make_shared< QueuedZoning >( zoneId, getPos(), Util::getTimeMs(), 0.f );
   //performZoning( zoneId, Common::ZoneingType::None, getPos() );
}

void Core::Entity::Player::returnToHomepoint()
{
   setZoningType( Common::ZoneingType::Return );
   teleport( getHomepoint(), 3 );
}

void Core::Entity::Player::setZone( uint32_t zoneId )
{
   auto pPlayer = getAsPlayer();

   auto pZone = g_zoneMgr.getZone( zoneId );


   if( !pZone /*|| ( ( pZone == m_pCurrentZone ) && m_lastPing )*/ )
   {
      g_log.error( "Zone " + std::to_string( zoneId ) + " not found on this server." );
      return;
   }

   m_zoneId = zoneId;

   // mark character as zoning in progress
   setLoadingComplete( false );

   if( m_lastPing != 0 )
      m_pCurrentZone->removeActor( shared_from_this() );

   m_pCurrentZone = pZone;
   m_pCurrentZone->pushActor( shared_from_this() );

   ZoneChannelPacket< FFXIVIpcInit > initPacket( getId() );
   initPacket.data().charId = getId();
   queuePacket( initPacket );

   sendInventory();

   if( isLogin() )
   {
      queuePacket(ActorControlPacket143( getId(), SetCharaGearParamUI, m_equipDisplayFlags, 1 ) );
   }

   // set flags, will be reset automatically by zoning ( only on client side though )
   pPlayer->setStateFlag( PlayerStateFlag::BetweenAreas );
   pPlayer->setStateFlag( PlayerStateFlag::BetweenAreas1 );
   pPlayer->sendStateFlags();

   pPlayer->sendStats();

   // only initialize the UI if the player in fact just logged in.
   if( isLogin() )
   {
      ZoneChannelPacket< FFXIVIpcCFAvailableContents > contentFinderList( getId() );
      for( auto i = 0; i < sizeof( contentFinderList.data().contents ); i++ )
      {
         // unlock all contents for now
         contentFinderList.data().contents[i] = 0xFF;
      }
      queuePacket( contentFinderList );

      Server::InitUIPacket initUIPacket( *pPlayer );
      queuePacket( initUIPacket );

      ZoneChannelPacket< FFXIVIpcPlayerClassInfo > classInfoPacket( getId() );
      classInfoPacket.data().classId = static_cast< uint8_t >( getClass() );
      classInfoPacket.data().unknown = 1;
      classInfoPacket.data().level = getLevel();
      classInfoPacket.data().level1 = getLevel();
      queuePacket( classInfoPacket );

      ZoneChannelPacket< FFXIVGCAffiliation > gcAffPacket( getId() );
      gcAffPacket.data().gcId = m_gc;
      gcAffPacket.data().gcRank[0] = m_gcRank[0];
      gcAffPacket.data().gcRank[1] = m_gcRank[1];
      gcAffPacket.data().gcRank[2] = m_gcRank[2];
      queuePacket( gcAffPacket );

      m_itemLevel = getInventory()->calculateEquippedGearItemLevel();
      sendItemLevel();
   }

   ZoneChannelPacket< FFXIVIpcInitZone > initZonePacket( getId() );
   initZonePacket.data().zoneId = getCurrentZone()->getLayoutId();
   initZonePacket.data().weatherId = static_cast< uint8_t >( getCurrentZone()->getCurrentWeather() );
   initZonePacket.data().bitmask = 0x1;
   initZonePacket.data().unknown5 = 0x2A;
   initZonePacket.data().pos.x = getPos().x;
   initZonePacket.data().pos.y = getPos().y;
   initZonePacket.data().pos.z = getPos().z;
   queuePacket( initZonePacket );

   if( isLogin() )
   {
      ZoneChannelPacket< FFXIVARR_IPC_UNK322 > unk322( getId() );
      queuePacket( unk322 );

      ZoneChannelPacket< FFXIVARR_IPC_UNK320 > unk320( getId() );
      queuePacket( unk320 );
   }

   if( getLastPing() == 0 )
      sendQuestInfo();

   m_bMarkedForZoning = false;
}

uint32_t Core::Entity::Player::getPlayTime() const
{
   return m_playTime;
}

uint8_t Core::Entity::Player::getRace() const
{
   return getLookAt( CharaLook::Race );
}

uint8_t Core::Entity::Player::getGender() const
{
   return getLookAt( CharaLook::Gender );
}

void Core::Entity::Player::initSpawnIdQueue()
{
   while( !m_freeSpawnIdQueue.empty() )
   {
      m_freeSpawnIdQueue.pop();
   }

   for( int32_t i = 1; i < MAX_DISPLAYED_ACTORS; i++ )
   {
      m_freeSpawnIdQueue.push( i );
   }
}

uint8_t Core::Entity::Player::getSpawnIdForActorId( uint32_t actorId )
{
   if( m_freeSpawnIdQueue.empty() )
      return 0;

   uint8_t spawnId = m_freeSpawnIdQueue.front();
   m_freeSpawnIdQueue.pop();
   m_playerIdToSpawnIdMap[actorId] = spawnId;
   return spawnId;
}

void Core::Entity::Player::assignSpawnIdToPlayerId( uint32_t actorId, uint8_t spawnId )
{
   m_playerIdToSpawnIdMap[actorId] = spawnId;
}

void Core::Entity::Player::registerAetheryte( uint8_t aetheryteId )
{

   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( aetheryteId, value, index );

   m_aetheryte[index] |= value;
   queuePacket( ActorControlPacket143( getId(), LearnTeleport, aetheryteId, 1 ) );

}

bool Core::Entity::Player::isAetheryteRegistered( uint8_t aetheryteId ) const
{
   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( aetheryteId, value, index );

   return ( m_aetheryte[index] & value ) != 0;
}

uint8_t * Core::Entity::Player::getDiscoveryBitmask()
{
   return m_discovery;
}

void Core::Entity::Player::discover( int16_t map_id, int16_t sub_id )
{
   // map.exd field 12 -> index in one of the two discovery sections, if field 15 is false, need to use 2nd section
   // section 1 starts at 4 - 2 bytes each

   // section to starts at 320 - 4 bytes long

   int32_t offset = 4;

   auto info = g_exdData.m_zoneInfoMap[getCurrentZone()->getId()];
   if( info.is_two_byte )
      offset = 4 + 2 * info.discovery_index;
   else
      offset = 324 + 4 * info.discovery_index;

   int32_t index = offset + sub_id / 8;
   uint8_t bitIndex = sub_id % 8;

   uint8_t value = 1 << bitIndex;

   m_discovery[index] |= value;

   uint16_t level = getLevel();

   uint32_t exp = ( g_exdData.m_paramGrowthInfoMap[level].needed_exp * 5 / 100 );

   gainExp( exp );



}

bool Core::Entity::Player::isNewAdventurer() const
{
   return m_bNewAdventurer;
}

void Core::Entity::Player::setNewAdventurer( bool state )
{
   //if( !state )
   //{
   //   unsetStateFlag( PlayerStateFlag::NewAdventurer );
   //}
   //else
   //{
   //   setStateFlag( PlayerStateFlag::NewAdventurer );
   //}
   sendStateFlags();
   m_bNewAdventurer = state;
}

void Core::Entity::Player::resetDiscovery()
{
   memset( m_discovery, 0, sizeof( m_discovery ) );
}

void Core::Entity::Player::changePosition( float x, float y, float z, float o )
{
   Common::FFXIVARR_POSITION3 pos;
   pos.x = x;
   pos.y = y;
   pos.z = z;
   m_queuedZoneing = boost::make_shared<QueuedZoning>( getZoneId(), pos, Util::getTimeMs(), o );
}

void Core::Entity::Player::learnAction( uint8_t actionId )
{
   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( actionId, value, index );

   m_unlocks[index] |= value;

   queuePacket( ActorControlPacket143( getId(), ToggleActionUnlock, actionId, 1 ) );
}

void Core::Entity::Player::learnSong( uint8_t songId, uint32_t itemId )
{
   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( songId, value, index );

   m_orchestrion[index] |= value;

   queuePacket( ActorControlPacket143( getId(), ToggleOrchestrionUnlock, songId, 1, itemId ) );
}

bool Core::Entity::Player::isActionLearned( uint8_t actionId ) const
{
   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( actionId, value, index );

   return ( m_unlocks[index] & value ) != 0;
}

void Core::Entity::Player::gainExp( uint32_t amount )
{
   uint32_t currentExp = getExp();

   uint16_t level = getLevel();

   uint32_t neededExpToLevel = g_exdData.m_paramGrowthInfoMap[level].needed_exp;

   uint32_t neededExpToLevelplus1 = g_exdData.m_paramGrowthInfoMap[level + 1].needed_exp;

   queuePacket( ActorControlPacket143( getId(), GainExpMsg, static_cast< uint8_t >( getClass() ), amount ) );

   if( level >= 70 ) // temporary fix for leveling over levelcap
   {
      queuePacket( ActorControlPacket143( getId(), UpdateUiExp, static_cast< uint8_t >( getClass() ), amount ) );
      return;
   }

   if( ( currentExp + amount ) >= neededExpToLevel )
   {
      // levelup
      amount = ( currentExp + amount - neededExpToLevel ) > neededExpToLevelplus1 ?
               neededExpToLevelplus1 - 1 :
               ( currentExp + amount - neededExpToLevel );
      setExp( amount );
      gainLevel();
      queuePacket( ActorControlPacket143( getId(), UpdateUiExp, static_cast< uint8_t >( getClass() ), amount ) );

   }
   else
   {
      queuePacket( ActorControlPacket143( getId(), UpdateUiExp, static_cast< uint8_t >( getClass() ), currentExp + amount ) );
      setExp( currentExp + amount );
   }

   sendStatusUpdate();
}

void Core::Entity::Player::gainLevel()
{
   setLevel( getLevel() + 1 );

   calculateStats();
   sendStats();
   sendStatusUpdate();

   m_hp = getMaxHp();
   m_mp = getMaxMp();

   ZoneChannelPacket< FFXIVIpcStatusEffectList > effectListPacket( getId() );
   effectListPacket.data().classId = static_cast< uint8_t > ( getClass() );
   effectListPacket.data().classId1 = static_cast< uint8_t > ( getClass() );
   effectListPacket.data().level = getLevel();
   effectListPacket.data().current_hp = getMaxHp();
   effectListPacket.data().current_mp = getMaxMp();
   effectListPacket.data().currentTp = 1000;
   effectListPacket.data().max_hp = getMaxHp();
   effectListPacket.data().max_mp = getMaxMp();
   sendToInRangeSet( effectListPacket, true );

   sendToInRangeSet( ActorControlPacket142( getId(), LevelUpEffect, static_cast< uint8_t >( getClass() ),
                                            getLevel(), getLevel() - 1 ), true );


   ZoneChannelPacket< FFXIVIpcUpdateClassInfo > classInfoPacket( getId() );
   classInfoPacket.data().classId = static_cast< uint8_t > ( getClass() );
   classInfoPacket.data().classId1 = static_cast< uint8_t > ( getClass() );
   classInfoPacket.data().level = getLevel();
   classInfoPacket.data().nextLevelIndex = getLevel();
   classInfoPacket.data().currentExp = getExp();
   queuePacket( classInfoPacket );

}

void Core::Entity::Player::unlock()
{
   queuePacket( PlayerStateFlagsPacket( *getAsPlayer(), PlayerStateFlagList{} ) );
}

void Core::Entity::Player::sendStatusUpdate( bool toSelf )
{
   //   CGamePacket* pPE = new CGamePacket(0x140, 0x0128, getId(), getId());

   //pPE->setInt8At(0x20, static_cast<uint8_t>(getClass()));

   //   pPE->setInt8At(0x21, getLevel());
   //   pPE->setInt8At(0x22, getLevel());

   //   // current exp
   //   pPE->setInt32At(0x28, getExp());

   //   // rested exp
   //   //pPE->setInt32At(0x2C, m_hp);

   //   pPE->setInt32At(0x24, m_hp);
   //   pPE->setInt32At(0x28, getMaxHp());
   //   pPE->setInt16At(0x2C, m_mp);
   //   pPE->setInt16At(0x2E, getMaxMp());
   //   pPE->setInt16At(0x30, m_tp);

   //   sendToInRangeSet(pPE, toSelf);

   sendToInRangeSet( UpdateHpMpTpPacket( shared_from_this() ), true );

}

uint8_t Core::Entity::Player::getLevel() const
{
   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( getClass() )].exp_idx;
   return static_cast< uint8_t >( m_classArray[classJobIndex] );
}

uint8_t Core::Entity::Player::getLevelForClass( Common::ClassJob pClass ) const
{
   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( pClass )].exp_idx;
   return static_cast< uint8_t >( m_classArray[classJobIndex] );
}

uint32_t Core::Entity::Player::getExp() const
{
   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( getClass() )].exp_idx;
   return m_expArray[classJobIndex];
}

void Core::Entity::Player::setExp( uint32_t amount )
{
   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( getClass() )].exp_idx;
   m_expArray[classJobIndex] = amount;
}

bool Core::Entity::Player::isInCombat() const
{
   return m_bInCombat;
}

void Core::Entity::Player::setInCombat( bool mode )
{
   //m_lastAttack = GetTickCount();
   m_bInCombat = mode;
}

void Core::Entity::Player::setClassJob( Common::ClassJob classJob )
{
   m_class = classJob;
   uint8_t level = getLevel();

   if( getHp() > getMaxHp() )
      m_hp = getMaxHp();

   if( getMp() > getMaxMp() )
      m_mp = getMaxMp();

   m_tp = 0;

   ZoneChannelPacket< FFXIVIpcPlayerClassInfo > classInfoPacket( getId() );
   classInfoPacket.data().classId = static_cast< uint8_t >( getClass() );
   classInfoPacket.data().level = getLevel();
   queuePacket( classInfoPacket );

   sendToInRangeSet( ActorControlPacket142( getId(), ClassJobChange, 0x04 ), true );

   sendStatusUpdate( true );
}

void Core::Entity::Player::setLevel( uint8_t level )
{
   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( static_cast< uint8_t >( getClass() ) )].exp_idx;
   m_classArray[classJobIndex] = level;
}

void Core::Entity::Player::setLevelForClass( uint8_t level, Common::ClassJob classjob )
{
    uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( classjob )].exp_idx;
    m_classArray[classJobIndex] = level;
}

void Core::Entity::Player::sendModel()
{
   ModelEquipPacket modelEquip( *getAsPlayer() );
   sendToInRangeSet( modelEquip, true );
}

uint32_t Core::Entity::Player::getModelForSlot( Inventory::EquipSlot slot )
{
   return m_modelEquip[slot];
}

void Core::Entity::Player::setModelForSlot( Inventory::EquipSlot slot, uint32_t val )
{
   m_modelEquip[slot] = val;
}

uint64_t Core::Entity::Player::getModelMainWeapon() const
{
   return m_modelMainWeapon;
}

uint64_t Core::Entity::Player::getModelSubWeapon() const
{
   return m_modelSubWeapon;
}

uint64_t Core::Entity::Player::getModelSystemWeapon() const
{
   return m_modelSystemWeapon;
}

int8_t Core::Entity::Player::getAetheryteMaskAt( uint8_t index ) const
{
   if( index > sizeof( m_aetheryte ) )
      return 0;
   return m_aetheryte[index];
}

uint8_t Core::Entity::Player::getBirthDay() const
{
   return m_birthDay;
}

uint8_t Core::Entity::Player::getBirthMonth() const
{
   return m_birthMonth;
}

uint8_t Core::Entity::Player::getGuardianDeity() const
{
   return m_guardianDeity;
}

uint8_t Core::Entity::Player::getLookAt( uint8_t index ) const
{
   return m_customize[index];
}

void Core::Entity::Player::setLookAt( uint8_t index, uint8_t value )
{
   m_customize[index] = value;
}

// spawn this player for pTarget
void Core::Entity::Player::spawn( Entity::PlayerPtr pTarget )
{
   g_log.debug( "[" + std::to_string( pTarget->getId() ) + "] Spawning " +
                getName() + " for " +
                pTarget->getName() );

   PlayerSpawnPacket spawnActor( *getAsPlayer(), *pTarget );
   pTarget->queuePacket( spawnActor );
}

// despawn
void Core::Entity::Player::despawn( Entity::ActorPtr pTarget )
{
   auto pPlayer = pTarget->getAsPlayer();

   pPlayer->freePlayerSpawnId( getId() );

   pPlayer->queuePacket( ActorControlPacket143( getId(), DespawnZoneScreenMsg, 0x04, getId(), 0x01 ) );
}

Core::Entity::ActorPtr Core::Entity::Player::lookupTargetById( uint64_t targetId )
{
   ActorPtr targetActor;
   auto inRange = getInRangeActors( true );
   for( auto actor : inRange )
   {
      if( actor->getId() == targetId )
         targetActor = actor;
   }
   return targetActor;
}

void Core::Entity::Player::setLastPing( uint32_t ping )
{
   m_lastPing = ping;
}

uint32_t Core::Entity::Player::getLastPing() const
{
   return m_lastPing;
}

void Core::Entity::Player::setVoiceId( uint8_t voiceId )
{
   m_voice = voiceId;
}

void Core::Entity::Player::setGc( uint8_t gc )
{
   m_gc = gc;

   ZoneChannelPacket< FFXIVGCAffiliation > gcAffPacket( getId() );
   gcAffPacket.data().gcId = m_gc;
   gcAffPacket.data().gcRank[0] = m_gcRank[0];
   gcAffPacket.data().gcRank[1] = m_gcRank[1];
   gcAffPacket.data().gcRank[2] = m_gcRank[2];
   queuePacket( gcAffPacket );
}

void Core::Entity::Player::setGcRankAt( uint8_t index, uint8_t rank )
{
   m_gcRank[index] = rank;

   ZoneChannelPacket< FFXIVGCAffiliation > gcAffPacket( getId() );
   gcAffPacket.data().gcId = m_gc;
   gcAffPacket.data().gcRank[0] = m_gcRank[0];
   gcAffPacket.data().gcRank[1] = m_gcRank[1];
   gcAffPacket.data().gcRank[2] = m_gcRank[2];
   queuePacket( gcAffPacket );
}

const uint8_t* Core::Entity::Player::getStateFlags() const
{
   return m_stateFlags;
}

bool Core::Entity::Player::actionHasCastTime( uint32_t actionId ) //TODO: Add logic for special cases
{
   auto actionInfoPtr = g_exdData.getActionInfo( actionId );
   if( actionInfoPtr->is_instant )
      return false;

   return actionInfoPtr->cast_time != 0;

}

bool Core::Entity::Player::hasStateFlag( Common::PlayerStateFlag flag ) const
{
   int32_t iFlag = static_cast< uint32_t >( flag );

   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( iFlag, value, index );

   return ( m_stateFlags[index] & value ) != 0;
}

void Core::Entity::Player::setStateFlag( Common::PlayerStateFlag flag )
{
   int32_t iFlag = static_cast< uint32_t >( flag );

   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( iFlag, value, index );

   m_stateFlags[index] |= value;

}

void Core::Entity::Player::setStateFlags( std::vector< Common::PlayerStateFlag > flags )
{
   for( const auto& flag : flags )
   {
      int iFlag = static_cast< uint32_t >( flag );

      uint16_t index;
      uint8_t value;
      Util::valueToFlagByteIndexValue( iFlag, value, index );

      m_stateFlags[index] |= value;
   }
}

void Core::Entity::Player::sendStateFlags()
{
   queuePacket( PlayerStateFlagsPacket( *getAsPlayer() ) );
}

void Core::Entity::Player::unsetStateFlag( Common::PlayerStateFlag flag )
{
   if( !hasStateFlag( flag ) )
      return;

   int32_t iFlag = static_cast< uint32_t >( flag );

   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( iFlag, value, index );

   m_stateFlags[index] ^= value;

}

void Core::Entity::Player::update( int64_t currTime )
{

   // a zoning is pending, lets do it
   if( m_queuedZoneing && ( currTime - m_queuedZoneing->m_queueTime ) > 800 )
   {
      Common::FFXIVARR_POSITION3 targetPos = m_queuedZoneing->m_targetPosition;
      if( getCurrentZone()->getId() != m_queuedZoneing->m_targetZone )
      {
         performZoning( m_queuedZoneing->m_targetZone, targetPos, m_queuedZoneing->m_targetRotation);
      }
      else
      {
         ZoneChannelPacket< FFXIVIpcActorSetPos > setActorPosPacket( getId() );
         setActorPosPacket.data().r16 = Math::Util::floatToUInt16Rot( m_queuedZoneing->m_targetRotation );
         setActorPosPacket.data().waitForLoad = 0x04;
         setActorPosPacket.data().x = targetPos.x;
         setActorPosPacket.data().y = targetPos.y;
         setActorPosPacket.data().z = targetPos.z;
         sendToInRangeSet( setActorPosPacket, true );
         setPosition( targetPos );
      }
      m_queuedZoneing.reset();
      return;
   }

   if( m_hp <= 0 && m_status != ActorStatus::Dead )
      die();

   if( !isAlive() )
      return;

   updateStatusEffects();

   m_lastUpdate = currTime;

   if( !checkAction() )
   {
      if( m_targetId && m_currentStance == Entity::Actor::Stance::Active && isAutoattackOn() )
      {
         auto mainWeap = m_pInventory->getItemAt( Inventory::GearSet0, Inventory::EquipSlot::MainHand );

         // @TODO i dislike this, iterating over all in range actors when you already know the id of the actor you need...
         for( auto actor : m_inRangeActors )
         {
            if( actor->getId() == m_targetId && actor->isAlive() && mainWeap )
            {
               // default autoattack range
               // TODO make this dependant on bnpc size
               uint32_t range = 7;

               // default autoattack range for ranged classes
               if( getClass() == ClassJob::Machinist ||
                   getClass() == ClassJob::Bard ||
                   getClass() == ClassJob::Archer )
                  range = 25;


               if( Math::Util::distance(getPos().x, getPos().y, getPos().z,
                   actor->getPos().x, actor->getPos().y, actor->getPos().z) <= range )
               {

                  if( ( currTime - m_lastAttack ) > mainWeap->getDelay() )
                  {
                     m_lastAttack = currTime;
                     autoAttack( actor );
                  }

               }
            }
         }
      }
   }

   if( ( currTime - m_lastTickTime ) > 3000 )
   {
      // add 3 seconds to total play time
      m_playTime += 3;
      m_lastTickTime = currTime;
      onTick();
   }
}

void Core::Entity::Player::onMobKill( uint16_t nameId )
{
   g_scriptMgr.onMobKill( *getAsPlayer(), nameId );
}

void Core::Entity::Player::freePlayerSpawnId( uint32_t actorId )
{
   uint8_t spawnId = m_playerIdToSpawnIdMap[actorId];
   m_playerIdToSpawnIdMap.erase( actorId );
   m_freeSpawnIdQueue.push( spawnId );

   ZoneChannelPacket< FFXIVIpcActorFreeSpawn > freeActorSpawnPacket( getId() );
   freeActorSpawnPacket.data().actorId = actorId;
   freeActorSpawnPacket.data().spawnId = spawnId;
   queuePacket( freeActorSpawnPacket );

}

uint8_t * Core::Entity::Player::getAetheryteArray()
{
   return m_aetheryte;
}

/*! set homepoint */
void Core::Entity::Player::setHomepoint( uint8_t aetheryteId )
{
   m_homePoint = aetheryteId;

   queuePacket( ActorControlPacket143( getId(), SetHomepoint, aetheryteId ) );
}

/*! get homepoint */
uint8_t Core::Entity::Player::getHomepoint() const
{
   return m_homePoint;
}

uint16_t* Core::Entity::Player::getClassArray()
{
   return m_classArray;
}

const uint16_t* Core::Entity::Player::getClassArray() const
{
   return m_classArray;
}

const uint8_t* Core::Entity::Player::getLookArray() const
{
   return m_customize;
}

const uint32_t* Core::Entity::Player::getModelArray() const
{
   return m_modelEquip;
}

uint32_t* Core::Entity::Player::getExpArray()
{
   return m_expArray;
}

const uint32_t* Core::Entity::Player::getExpArray() const
{
   return m_expArray;
}

uint8_t* Core::Entity::Player::getHowToArray()
{
   return m_howTo;
}

const uint8_t* Core::Entity::Player::getHowToArray() const
{
   return m_howTo;
}

const uint8_t* Core::Entity::Player::getUnlockBitmask() const
{
   return m_unlocks;
}

const uint8_t* Core::Entity::Player::getOrchestrionBitmask() const
{
   return m_orchestrion;
}

const uint8_t* Core::Entity::Player::getMountGuideBitmask() const
{
   return m_mountGuide;
}

uint64_t Core::Entity::Player::getContentId() const
{
   return m_contentId;
}

uint8_t Core::Entity::Player::getVoiceId() const
{
   return m_voice;
}

uint8_t Core::Entity::Player::getGc() const
{
   return m_gc;
}

const uint8_t* Core::Entity::Player::getGcRankArray() const
{
   return m_gcRank;
}

void Core::Entity::Player::queuePacket( Network::Packets::GamePacketPtr pPacket )
{
   auto pSession = g_serverZone.getSession( m_id );

   if( !pSession )
      return;

   auto pZoneCon = pSession->getZoneConnection();

   if( pZoneCon )
      pZoneCon->queueOutPacket( pPacket );

}

void Core::Entity::Player::queueChatPacket( Network::Packets::GamePacketPtr pPacket )
{
   auto pSession = g_serverZone.getSession( m_id );

   if( !pSession )
      return;

   auto pChatCon = pSession->getChatConnection();

   if( pChatCon )
      pChatCon->queueOutPacket( pPacket );
}

bool Core::Entity::Player::isLoadingComplete() const
{
   return m_bLoadingComplete;
}

void Core::Entity::Player::setLoadingComplete( bool bComplete )
{
   m_bLoadingComplete = bComplete;
}

void Core::Entity::Player::performZoning( uint16_t zoneId, const Common::FFXIVARR_POSITION3 &pos, float rotation )
{
   m_pos = pos;
   m_zoneId = zoneId;
   m_bMarkedForZoning = true;
   setRotation( rotation );
   setZone( zoneId );
}

bool Core::Entity::Player::isMarkedForZoning() const
{
   return m_bMarkedForZoning;
}

ZoneingType Core::Entity::Player::getZoningType() const
{
   return m_zoningType;
}

void Core::Entity::Player::setZoningType( Common::ZoneingType zoneingType )
{
   m_zoningType = zoneingType;
}

void Core::Entity::Player::setSearchInfo( uint8_t selectRegion, uint8_t selectClass, const char* searchMessage )
{
   m_searchSelectRegion = selectRegion;
   m_searchSelectClass = selectClass;
   memset( &m_searchMessage[0], 0, sizeof( searchMessage ) );
   strcpy( &m_searchMessage[0], searchMessage );
}

const char* Core::Entity::Player::getSearchMessage() const
{
   return &m_searchMessage[0];
}

uint8_t Core::Entity::Player::getSearchSelectRegion() const
{
   return m_searchSelectRegion;
}

uint8_t Core::Entity::Player::getSearchSelectClass() const
{
   return m_searchSelectClass;
}

void Core::Entity::Player::sendNotice( const std::string& message ) //Purple Text
{
   queuePacket( ServerNoticePacket( getId(), message ) );
}

void Core::Entity::Player::sendUrgent( const std::string& message ) //Red Text
{
   queuePacket( ChatPacket( *getAsPlayer(), ChatType::ServerUrgent, message ) );
}

void Core::Entity::Player::sendDebug( const std::string& message ) //Grey Text
{
   queuePacket( ChatPacket( *getAsPlayer(), ChatType::ServerDebug, message ) );
}

void Core::Entity::Player::updateHowtosSeen( uint32_t howToId )
{
   uint8_t index = howToId / 8;
   uint8_t bitIndex = howToId % 8;

   uint8_t value = 1 << bitIndex;

   m_howTo[index] |= value;
}


void Core::Entity::Player::onMobAggro( BattleNpcPtr pBNpc )
{
   hateListAdd( pBNpc );

   queuePacket( ActorControlPacket142( getId(), ToggleAggro, 1 ) );
}

void Core::Entity::Player::onMobDeaggro( BattleNpcPtr pBNpc )
{
   hateListRemove( pBNpc );

   if( m_actorIdTohateSlotMap.empty() )
      queuePacket( ActorControlPacket142( getId(), ToggleAggro ) );
}

void Core::Entity::Player::hateListAdd( BattleNpcPtr pBNpc )

{
   if( m_freeHateSlotQueue.empty() )
      return;
   uint8_t hateId = m_freeHateSlotQueue.front();
   m_freeHateSlotQueue.pop();
   m_actorIdTohateSlotMap[pBNpc->getId()] = hateId;
   sendHateList();

}

void Core::Entity::Player::hateListRemove( BattleNpcPtr pBNpc )
{

   auto it = m_actorIdTohateSlotMap.begin();
   for( ; it != m_actorIdTohateSlotMap.end(); ++it )
   {
      if( it->first == pBNpc->getId() )
      {
         uint8_t hateSlot = it->second;
         m_freeHateSlotQueue.push( hateSlot );
         m_actorIdTohateSlotMap.erase( it );
         sendHateList();

         return;
      }
   }
}

bool Core::Entity::Player::hateListHasMob( BattleNpcPtr pBNpc )
{

   auto it = m_actorIdTohateSlotMap.begin();
   for( ; it != m_actorIdTohateSlotMap.end(); ++it )
   {
      if( it->first == pBNpc->getId() )
         return true;
   }
   return false;
}

void Core::Entity::Player::initHateSlotQueue()
{
   m_freeHateSlotQueue = std::queue< uint8_t >();
   for( int32_t i = 1; i < 26; i++ )
      m_freeHateSlotQueue.push( i );
}

void Core::Entity::Player::sendHateList()
{
   ZoneChannelPacket< FFXIVIpcHateList > hateListPacket( getId() );
   hateListPacket.data().numEntries = m_actorIdTohateSlotMap.size();
   auto it = m_actorIdTohateSlotMap.begin();
   for( int32_t i = 0; it != m_actorIdTohateSlotMap.end(); ++it, i++ )
   {
      hateListPacket.data().entry[i].actorId = it->first;
      hateListPacket.data().entry[i].hatePercent = 100;
   }
   queuePacket( hateListPacket );
}

bool Core::Entity::Player::isLogin() const
{
   return m_bIsLogin;
}

void Core::Entity::Player::setIsLogin( bool bIsLogin )
{
   m_bIsLogin = bIsLogin;
}

uint8_t* Core::Entity::Player::getTitleList()
{
   return m_titleList;
}

uint16_t Core::Entity::Player::getTitle() const
{
   return m_activeTitle;
}

void Core::Entity::Player::addTitle( uint16_t titleId )
{
   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( titleId, value, index );

   m_titleList[index] |= value;
}

void Core::Entity::Player::setTitle( uint16_t titleId )
{
   uint16_t index;
   uint8_t value;
   Util::valueToFlagByteIndexValue( titleId, value, index );

   if ( ( m_titleList[index] & value ) == 0 )   // Player doesn't have title - bail
      return;

   m_activeTitle = titleId;

   sendToInRangeSet( ActorControlPacket142( getId(), SetTitle, titleId ), true );
}

void Core::Entity::Player::setEquipDisplayFlags( uint8_t state )
{
   m_equipDisplayFlags = state;
   ZoneChannelPacket< FFXIVIpcEquipDisplayFlags > paramPacket( getId() );
   paramPacket.data().bitmask = m_equipDisplayFlags;
   sendToInRangeSet( paramPacket, true );
}

uint8_t Core::Entity::Player::getEquipDisplayFlags() const
{
   return m_equipDisplayFlags;
}

void Core::Entity::Player::mount( uint32_t id )
{
   m_mount = id;
   sendToInRangeSet( ActorControlPacket142( getId(), ActorControlType::SetStatus, static_cast< uint8_t >( Entity::Actor::ActorStatus::Mounted )), true );
   sendToInRangeSet( ActorControlPacket143( getId(), 0x39e, 12 ), true ); //?

   ZoneChannelPacket< FFXIVIpcMount > mountPacket( getId() );
   mountPacket.data().id = id;
   sendToInRangeSet( mountPacket, true );
}

void Core::Entity::Player::dismount()
{
   sendToInRangeSet( ActorControlPacket142( getId(), ActorControlType::SetStatus,
                                            static_cast< uint8_t >( Entity::Actor::ActorStatus::Idle )), true );
   sendToInRangeSet( ActorControlPacket143( getId(), ActorControlType::Dismount, 1 ), true );
   m_mount = 0;
}

uint8_t Core::Entity::Player::getCurrentMount() const
{
   return m_mount;
}

void Core::Entity::Player::autoAttack( ActorPtr pTarget )
{

   auto mainWeap = m_pInventory->getItemAt( Inventory::GearSet0,
                                            Inventory::EquipSlot::MainHand );

   pTarget->onActionHostile( shared_from_this() );
   //uint64_t tick = Util::getTimeMs();
   //srand(static_cast< uint32_t >(tick));

   uint32_t damage = static_cast< uint32_t >( mainWeap->getAutoAttackDmg() );
   uint32_t variation = 0 + rand() % 3;

   if( getClass() == ClassJob::Machinist ||
       getClass() == ClassJob::Bard ||
       getClass() == ClassJob::Archer )
   {
      ZoneChannelPacket< FFXIVIpcEffect > effectPacket(getId());
      effectPacket.data().targetId = pTarget->getId();
      effectPacket.data().actionAnimationId = 8;
     // effectPacket.data().unknown_2 = variation;
      effectPacket.data().numEffects = 1;
      effectPacket.data().unknown_61 = 1;
      effectPacket.data().unknown_62 = 1;
      effectPacket.data().actionTextId = 8;
      effectPacket.data().rotation = Math::Util::floatToUInt16Rot(getRotation());
      effectPacket.data().effectTargetId = pTarget->getId();
      effectPacket.data().effectTarget = pTarget->getId();
      effectPacket.data().effects[0].value = damage;
      effectPacket.data().effects[0].effectType = Common::ActionEffectType::Damage;
      effectPacket.data().effects[0].hitSeverity = Common::ActionHitSeverityType::NormalDamage;
      effectPacket.data().effects[0].unknown_3 = 7;

      sendToInRangeSet(effectPacket, true);
   }
   else
   {

      ZoneChannelPacket< FFXIVIpcEffect > effectPacket(getId());
      effectPacket.data().targetId = pTarget->getId();
      effectPacket.data().actionAnimationId = 7;
      // effectPacket.data().unknown_2 = variation;
      effectPacket.data().numEffects = 1;
      effectPacket.data().unknown_61 = 1;
      effectPacket.data().unknown_62 = 1;
      effectPacket.data().actionTextId = 7;
      effectPacket.data().rotation = Math::Util::floatToUInt16Rot(getRotation());
      effectPacket.data().effectTarget = pTarget->getId();
      effectPacket.data().effects[0].value = damage;
      effectPacket.data().effects[0].effectType = Common::ActionEffectType::Damage;
      effectPacket.data().effects[0].hitSeverity = Common::ActionHitSeverityType::NormalDamage;
      effectPacket.data().effects[0].unknown_3 = 71;

      sendToInRangeSet(effectPacket, true);
   }

   pTarget->takeDamage(damage);

}


/////////////////////////////
// Content Finder
/////////////////////////////
uint32_t Core::Entity::Player::getCFPenaltyTimestamp() const
{
   return m_cfPenaltyUntil;
}

void Core::Entity::Player::setCFPenaltyTimestamp( uint32_t timestamp )
{
   m_cfPenaltyUntil = timestamp;
}

uint32_t Core::Entity::Player::getCFPenaltyMinutes() const
{
   auto currentTimestamp = Core::Util::getTimeSeconds();
   auto endTimestamp = getCFPenaltyTimestamp();

   // check if penalty timestamp already passed current time
   if( currentTimestamp > endTimestamp )
      return 0;

   auto deltaTime = endTimestamp - currentTimestamp;
   return static_cast< uint32_t > ( ceil( static_cast< float > (deltaTime) / 60 ) );
}

void Core::Entity::Player::setCFPenaltyMinutes( uint32_t minutes )
{
   auto currentTimestamp = Core::Util::getTimeSeconds();
   setCFPenaltyTimestamp( static_cast< uint32_t >( currentTimestamp + minutes * 60 ) );
}

uint8_t Core::Entity::Player::getOpeningSequence() const
{
   return m_openingSequence;
}

void Core::Entity::Player::setOpeningSequence( uint8_t seq )
{
   m_openingSequence = seq;
}

uint16_t Core::Entity::Player::getItemLevel() const
{
   return m_itemLevel;
}

/// Tells client to offset their eorzean time by given timestamp.
void Core::Entity::Player::setEorzeaTimeOffset( uint64_t timestamp )
{
   // TODO: maybe change to persistent?
   ZoneChannelPacket< FFXIVIpcEorzeaTimeOffset > packet ( getId() );
   packet.data().timestamp = timestamp;

   // Send to single player
   queuePacket( packet );
}
