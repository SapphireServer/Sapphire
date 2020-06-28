#include <Common.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/EffectPacket.h>
#include <cmath>
#include <Service.h>

#include "Session.h"
#include "Player.h"
#include "BNpc.h"

#include "Manager/HousingMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/RNGMgr.h"

#include "Territory/Territory.h"
#include "Territory/ZonePosition.h"
#include "Territory/InstanceContent.h"
#include "Territory/InstanceObjectCache.h"
#include "Territory/Land.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/ModelEquipPacket.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "Network/PacketWrappers/PlayerSpawnPacket.h"

#include "Script/ScriptMgr.h"

#include "Action/Action.h"

#include "Math/CalcStats.h"
#include "Math/CalcBattle.h"

#include "ServerMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

using InventoryMap = std::map< uint16_t, Sapphire::ItemContainerPtr >;
using InvSlotPair = std::pair< uint16_t, int8_t >;
using InvSlotPairVec = std::vector< InvSlotPair >;

// player constructor
Sapphire::Entity::Player::Player() :
  Chara( ObjKind::Player ),
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
  m_mount( 0 ),
  m_emoteMode( 0 ),
  m_directorInitialized( false ),
  m_onEnterEventDone( false ),
  m_falling( false ),
  m_pQueuedAction( nullptr )
{
  m_id = 0;
  m_currentStance = Stance::Passive;
  m_onlineStatus = 0;
  m_queuedZoneing = nullptr;
  m_status = ActorStatus::Idle;
  m_invincibilityType = InvincibilityType::InvincibilityNone;
  m_radius = 1.f;

  memset( m_questTracking, 0, sizeof( m_questTracking ) );
  memset( m_name, 0, sizeof( m_name ) );
  memset( m_stateFlags, 0, sizeof( m_stateFlags ) );
  memset( m_searchMessage, 0, sizeof( m_searchMessage ) );
  memset( m_classArray, 0, sizeof( m_classArray ) );
  memset( m_expArray, 0, sizeof( m_expArray ) );

  for ( uint8_t i = 0; i < 5; i++ )
  {
    memset( &m_landFlags[i], 0xFF, 8 );
    memset( &m_landFlags[i].landFlags, 0, 8 );
  }

  m_objSpawnIndexAllocator.init( MAX_DISPLAYED_EOBJS );
  m_actorSpawnIndexAllocator.init( MAX_DISPLAYED_ACTORS, true );

  gaugeClear();
}

Sapphire::Entity::Player::~Player()
{
}

void Sapphire::Entity::Player::injectPacket( const std::string& path )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto session = serverMgr.getSession( getId() );
  if( session )
    session->getZoneConnection()->injectPacket( path, *this );
}

// TODO: add a proper calculation based on race / job / level / gear
uint32_t Sapphire::Entity::Player::getMaxHp()
{
  return m_baseStats.max_hp;
}

uint32_t Sapphire::Entity::Player::getMaxMp()
{
  return m_baseStats.max_mp;
}

uint16_t Sapphire::Entity::Player::getZoneId() const
{
  return m_territoryTypeId;
}

uint32_t Sapphire::Entity::Player::getTerritoryId() const
{
  return m_territoryId;
}

void Sapphire::Entity::Player::setTerritoryId( uint32_t territoryId )
{
  m_territoryId = territoryId;
}

uint8_t Sapphire::Entity::Player::getGmRank() const
{
  return m_gmRank;
}

void Sapphire::Entity::Player::setGmRank( uint8_t rank )
{
  m_gmRank = rank;
}

bool Sapphire::Entity::Player::getGmInvis() const
{
  return m_gmInvis;
}

void Sapphire::Entity::Player::setGmInvis( bool invis )
{
  m_gmInvis = invis;
}

bool Sapphire::Entity::Player::isActingAsGm() const
{
  auto status = getOnlineStatus();
  return status == OnlineStatus::GameMaster || status == OnlineStatus::GameMaster1 ||
         status == OnlineStatus::GameMaster2;
}

uint8_t Sapphire::Entity::Player::getMode() const
{
  return m_mode;
}

void Sapphire::Entity::Player::setMode( uint8_t mode )
{
  m_mode = mode;
}

uint8_t Sapphire::Entity::Player::getStartTown() const
{
  return m_startTown;
}

void Sapphire::Entity::Player::setMarkedForRemoval()
{
  m_markedForRemoval = true;
}

bool Sapphire::Entity::Player::isMarkedForRemoval() const
{
  return m_markedForRemoval;
}

Sapphire::Common::OnlineStatus Sapphire::Entity::Player::getOnlineStatus() const
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  uint32_t statusDisplayOrder = 0xFF14;
  uint32_t applicableStatus = static_cast< uint32_t >( OnlineStatus::Online );

  for( uint32_t i = 0; i < std::numeric_limits< decltype( m_onlineStatus ) >::digits; i++ )
  {
    bool bit = ( m_onlineStatus >> i ) & 1;

    if( !bit )
      continue;

    auto pOnlineStatus = exdData.get< Data::OnlineStatus >( i );
    if( !pOnlineStatus )
      continue;

    if( pOnlineStatus->priority < statusDisplayOrder )
    {
      // todo: also check that the status can actually be set here, otherwise we need to ignore it (and ban the player obv)
      statusDisplayOrder = pOnlineStatus->priority;
      applicableStatus = i;
    }
  }

  return static_cast< OnlineStatus >( applicableStatus );
}

void Sapphire::Entity::Player::setOnlineStatusMask( uint64_t status )
{
  m_onlineStatus = status;
}

uint64_t Sapphire::Entity::Player::getOnlineStatusMask() const
{
  return m_onlineStatus;
}

void Sapphire::Entity::Player::prepareZoning( uint16_t targetZone, bool fadeOut, uint8_t fadeOutTime, uint16_t animation )
{
  auto preparePacket = makeZonePacket< FFXIVIpcPrepareZoning >( getId() );
  preparePacket->data().targetZone = targetZone;
  preparePacket->data().fadeOutTime = fadeOutTime;
  preparePacket->data().animation = animation;
  preparePacket->data().fadeOut = static_cast< uint8_t >( fadeOut ? 1 : 0 );
  queuePacket( preparePacket );
}

void Sapphire::Entity::Player::calculateStats()
{
  uint8_t tribe = getLookAt( Common::CharaLook::Tribe );
  uint8_t level = getLevel();
  uint8_t job = static_cast< uint8_t >( getClass() );

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto classInfo = exdData.get< Sapphire::Data::ClassJob >( job );
  auto tribeInfo = exdData.get< Sapphire::Data::Tribe >( tribe );
  auto paramGrowthInfo = exdData.get< Sapphire::Data::ParamGrow >( level );

  float base = Math::CalcStats::calculateBaseStat( *this );

  m_baseStats.str = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierStrength ) / 100 ) +
                                             tribeInfo->sTR );
  m_baseStats.dex = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierDexterity ) / 100 ) +
                                             tribeInfo->dEX );
  m_baseStats.vit = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierVitality ) / 100 ) +
                                             tribeInfo->vIT );
  m_baseStats.inte = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierIntelligence ) / 100 ) +
                                              tribeInfo->iNT );
  m_baseStats.mnd = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierMind ) / 100 ) +
                                             tribeInfo->mND );
  /*m_baseStats.pie = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierPiety ) / 100 ) +
                                             tribeInfo->pIE );*/

  m_baseStats.determination = static_cast< uint32_t >( base );
  m_baseStats.pie = static_cast< uint32_t >( base );
  m_baseStats.skillSpeed = paramGrowthInfo->baseSpeed;
  m_baseStats.spellSpeed = paramGrowthInfo->baseSpeed;
  m_baseStats.accuracy = paramGrowthInfo->baseSpeed;
  m_baseStats.critHitRate = paramGrowthInfo->baseSpeed;
  m_baseStats.attackPotMagic = paramGrowthInfo->baseSpeed;
  m_baseStats.healingPotMagic = paramGrowthInfo->baseSpeed;
  m_baseStats.tenacity = paramGrowthInfo->baseSpeed;

  m_baseStats.attack = m_baseStats.str;
  m_baseStats.attackPotMagic = m_baseStats.inte;
  m_baseStats.healingPotMagic = m_baseStats.mnd;

  m_baseStats.max_mp = 10000;

  m_baseStats.max_hp = Math::CalcStats::calculateMaxHp( getAsPlayer() );

  if( m_mp > m_baseStats.max_mp )
    m_mp = m_baseStats.max_mp;

  if( m_hp > m_baseStats.max_hp )
    m_hp = m_baseStats.max_hp;

}


void Sapphire::Entity::Player::setAutoattack( bool mode )
{
  m_bAutoattack = mode;
}

bool Sapphire::Entity::Player::isAutoattackOn() const
{
  return m_bAutoattack;
}

void Sapphire::Entity::Player::sendStats()
{
  auto statPacket = makeZonePacket< FFXIVIpcPlayerStats >( getId() );

  statPacket->data().strength = getStatValue( Common::BaseParam::Strength );
  statPacket->data().dexterity = getStatValue( Common::BaseParam::Dexterity );
  statPacket->data().vitality = getStatValue( Common::BaseParam::Vitality );
  statPacket->data().intelligence = getStatValue( Common::BaseParam::Intelligence );
  statPacket->data().mind = getStatValue( Common::BaseParam::Mind );
  statPacket->data().piety = getStatValue( Common::BaseParam::Piety );
  statPacket->data().determination = getStatValue( Common::BaseParam::Determination );
  statPacket->data().hp = getStatValue( Common::BaseParam::HP );
  statPacket->data().mp = getStatValue( Common::BaseParam::MP );
  statPacket->data().directHitRate = getStatValue( Common::BaseParam::DirectHitRate );
  statPacket->data().attackPower = getStatValue( Common::BaseParam::AttackPower );
  statPacket->data().attackMagicPotency = getStatValue( Common::BaseParam::AttackMagicPotency );
  statPacket->data().healingMagicPotency = getStatValue( Common::BaseParam::HealingMagicPotency );
  statPacket->data().skillSpeed = getStatValue( Common::BaseParam::SkillSpeed );
  statPacket->data().spellSpeed = getStatValue( Common::BaseParam::SpellSpeed );
  statPacket->data().haste = 100;
  statPacket->data().criticalHit = getStatValue( Common::BaseParam::CriticalHit );
  statPacket->data().defense = getStatValue( Common::BaseParam::Defense );
  statPacket->data().magicDefense = getStatValue( Common::BaseParam::MagicDefense );
  statPacket->data().tenacity = getStatValue( Common::BaseParam::Tenacity );

  queuePacket( statPacket );
}

void Sapphire::Entity::Player::teleport( uint16_t aetheryteId, uint8_t type )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();

  auto data = exdData.get< Sapphire::Data::Aetheryte >( aetheryteId );

  if( data == nullptr )
    return;

  setStateFlag( PlayerStateFlag::BetweenAreas );

  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto pop = instanceObjectCache.getPopRange( data->territory, data->level[ 0 ] );

  Common::FFXIVARR_POSITION3 pos;
  pos.x = 0;
  pos.y = 0;
  pos.z = 0;
  float rot = 0;

  if( pop )
  {
    sendDebug( "Teleport: popRange {0} found!", data->level.at( 0 ) );

    pos.x = pop->header.transform.translation.x;
    pos.y = pop->header.transform.translation.y;
    pos.z = pop->header.transform.translation.z;
    rot = pop->header.transform.rotation.y;
  }
  else
  {
    sendDebug( "Teleport: popRange {0} not found in {1}!", data->level[ 0 ], data->territory );
  }

  sendDebug( "Teleport: {0} {1} ({2})",
             exdData.get< Sapphire::Data::PlaceName >( data->placeName )->name,
             exdData.get< Sapphire::Data::PlaceName >( data->aethernetName )->name,
             data->territory );

  // TODO: this should be simplified and a type created in server_common/common.h.
  if( type == 1 ) // teleport
  {
    prepareZoning( data->territory, true, 1, 0 ); // TODO: Really?
    sendToInRangeSet( makeActorControl( getId(), ActorDespawnEffect, 0x04 ) );
    setZoningType( Common::ZoneingType::Teleport );
  }
  else if( type == 2 ) // aethernet
  {
    prepareZoning( data->territory, true, 1, 112 );
    sendToInRangeSet( makeActorControl( getId(), ActorDespawnEffect, 0x04 ) );
    setZoningType( Common::ZoneingType::Teleport );
  }
  else if( type == 3 ) // return
  {
    prepareZoning( data->territory, true, 1, 111 );
    sendToInRangeSet( makeActorControl( getId(), ActorDespawnEffect, 0x03 ) );
    setZoningType( Common::ZoneingType::Return );
  }

  m_queuedZoneing = std::make_shared< QueuedZoning >( data->territory, pos, Util::getTimeMs(), rot );


}

void Sapphire::Entity::Player::forceZoneing( uint32_t zoneId )
{
  m_queuedZoneing = std::make_shared< QueuedZoning >( zoneId, getPos(), Util::getTimeMs(), 0.f );
  //performZoning( zoneId, Common::ZoneingType::None, getPos() );
}

void Sapphire::Entity::Player::returnToHomepoint()
{
  setZoningType( Common::ZoneingType::Return );
  teleport( getHomepoint(), 3 );
}

void Sapphire::Entity::Player::setZone( uint32_t zoneId )
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  m_onEnterEventDone = false;
  if( !teriMgr.movePlayer( zoneId, getAsPlayer() ) )
  {
    // todo: this will require proper handling, for now just return the player to their previous area
    m_pos = m_prevPos;
    m_rot = m_prevRot;
    m_territoryTypeId = m_prevTerritoryTypeId;

    if( !teriMgr.movePlayer( m_territoryTypeId, getAsPlayer() ) )
      return;
  }

}

bool Sapphire::Entity::Player::setInstance( uint32_t instanceContentId )
{
  m_onEnterEventDone = false;
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();

  auto instance = teriMgr.getTerritoryByGuId( instanceContentId );
  if( !instance )
    return false;

  return setInstance( instance );
}

bool Sapphire::Entity::Player::setInstance( TerritoryPtr instance )
{
  m_onEnterEventDone = false;
  if( !instance )
    return false;

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto currentZone = getCurrentTerritory();

  // zoning within the same zone won't cause the prev data to be overwritten
  if( instance->getTerritoryTypeId() != m_territoryTypeId )
  {
    m_prevPos = m_pos;
    m_prevRot = m_rot;
    m_prevTerritoryTypeId = currentZone->getTerritoryTypeId();
    m_prevTerritoryId = getTerritoryId();
  }

  return teriMgr.movePlayer( instance, getAsPlayer() );
}

bool Sapphire::Entity::Player::setInstance( TerritoryPtr instance, Common::FFXIVARR_POSITION3 pos )
{
  m_onEnterEventDone = false;
  if( !instance )
    return false;

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto currentZone = getCurrentTerritory();

  // zoning within the same zone won't cause the prev data to be overwritten
  if( instance->getTerritoryTypeId() != m_territoryTypeId )
  {
    m_prevPos = m_pos;
    m_prevRot = m_rot;
    m_prevTerritoryTypeId = currentZone->getTerritoryTypeId();
    m_prevTerritoryId = getTerritoryId();
  }

  if( teriMgr.movePlayer( instance, getAsPlayer() ) )
  {
    m_pos = pos;
    return true;
  }

  return false;
}

bool Sapphire::Entity::Player::exitInstance()
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();

  auto pZone = getCurrentTerritory();
  auto pInstance = pZone->getAsInstanceContent();

  resetHp();
  resetMp();

  // check if housing zone
  if( teriMgr.isHousingTerritory( m_prevTerritoryTypeId ) )
  {
    if( !teriMgr.movePlayer( teriMgr.getZoneByLandSetId( m_prevTerritoryId ), getAsPlayer() ) )
      return false;
  }
  else
  {
    if( !teriMgr.movePlayer( m_prevTerritoryTypeId, getAsPlayer() ) )
      return false;
  }

  m_pos = m_prevPos;
  m_rot = m_prevRot;
  m_territoryTypeId = m_prevTerritoryTypeId;
  m_territoryId = m_prevTerritoryId;

  //m_queuedZoneing = std::make_shared< QueuedZoning >( m_territoryTypeId, m_pos, Util::getTimeMs(), m_rot );

  return true;
}

uint32_t Sapphire::Entity::Player::getPlayTime() const
{
  return m_playTime;
}

uint8_t Sapphire::Entity::Player::getRace() const
{
  return getLookAt( CharaLook::Race );
}

uint8_t Sapphire::Entity::Player::getGender() const
{
  return getLookAt( CharaLook::Gender );
}

void Sapphire::Entity::Player::initSpawnIdQueue()
{
  m_actorSpawnIndexAllocator.freeAllSpawnIndexes();
}

uint8_t Sapphire::Entity::Player::getSpawnIdForActorId( uint32_t actorId )
{
  auto index = m_actorSpawnIndexAllocator.getNextFreeSpawnIndex( actorId );

  if( index == m_actorSpawnIndexAllocator.getAllocFailId() )
  {
    Logger::warn( "Failed to spawn Chara#{0} for Player#{1} - no remaining spawn indexes available. "
                  "Consider lowering InRangeDistance in world config.",
                  actorId, getId() );

    sendUrgent( "Failed to spawn Chara#{0} for you - no remaining spawn slots. See world log.", actorId );

    return index;
  }

  return index;
}

bool Sapphire::Entity::Player::isActorSpawnIdValid( uint8_t spawnIndex )
{
  return m_actorSpawnIndexAllocator.isSpawnIndexValid( spawnIndex );
}

void Sapphire::Entity::Player::registerAetheryte( uint8_t aetheryteId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( aetheryteId, value, index );

  m_aetheryte[ index ] |= value;
  queuePacket( makeActorControlSelf( getId(), LearnTeleport, aetheryteId, 1 ) );
}

bool Sapphire::Entity::Player::isAetheryteRegistered( uint8_t aetheryteId ) const
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( aetheryteId, value, index );

  return ( m_aetheryte[ index ] & value ) != 0;
}

uint8_t* Sapphire::Entity::Player::getDiscoveryBitmask()
{
  return m_discovery;
}

void Sapphire::Entity::Player::discover( int16_t map_id, int16_t sub_id )
{
  // map.exd field 12 -> index in one of the two discovery sections, if field 15 is false, need to use 2nd section
  // section 1 starts at 4 - 2 bytes each

  // section to starts at 320 - 4 bytes long

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  int32_t offset = 4;

  auto info = exdData.get< Sapphire::Data::Map >( map_id );
  if ( !info )
  {
    sendDebug( "discover(): Could not obtain map data for map_id == {0}", map_id );
    return;
  }

  if( info->discoveryArrayByte )
    offset = 5 + 2 * info->discoveryIndex;
  else
    offset = 325 + 4 * info->discoveryIndex;

  int32_t index = offset + sub_id / 8;
  uint8_t bitIndex = sub_id % 8;

  uint8_t value = 1 << bitIndex;

  m_discovery[ index ] |= value;

  uint16_t level = getLevel();

  uint32_t exp = ( exdData.get< Sapphire::Data::ParamGrow >( level )->expToNext * 5 / 100 );

  gainExp( exp );

  // gain 10x additional EXP if entire map is completed
  uint32_t mask = info->discoveryFlag;
  uint32_t discoveredAreas;
  if( info->discoveryArrayByte )
  {
    discoveredAreas = ( m_discovery[ offset + 1 ] << 8 ) |
                        m_discovery[ offset ];
  }
  else
  {
    discoveredAreas = ( m_discovery[ offset + 3 ] << 24 ) |
                      ( m_discovery[ offset + 2 ] << 16 ) |
                      ( m_discovery[ offset + 1 ] << 8  ) |
                        m_discovery[ offset ];
  }

  bool allDiscovered = ( ( discoveredAreas & mask ) == mask );

  if( allDiscovered )
  {
    gainExp( exp * 10 );
  }
}

bool Sapphire::Entity::Player::isNewAdventurer() const
{
  return m_bNewAdventurer;
}

void Sapphire::Entity::Player::setNewAdventurer( bool state )
{
  //if( !state )
  //{
  //   unsetStateFlag( PlayerStateFlag::NewAdventurer );
  //}
  //else
  //{
  //   setStateFlag( PlayerStateFlag::NewAdventurer );
  //}
  m_bNewAdventurer = state;
}

void Sapphire::Entity::Player::resetDiscovery()
{
  memset( m_discovery, 0, sizeof( m_discovery ) );
}

void Sapphire::Entity::Player::changePosition( float x, float y, float z, float o )
{
  Common::FFXIVARR_POSITION3 pos;
  pos.x = x;
  pos.y = y;
  pos.z = z;
  m_queuedZoneing = std::make_shared< QueuedZoning >( getZoneId(), pos, Util::getTimeMs(), o );
}

void Sapphire::Entity::Player::learnAction( uint16_t actionId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( actionId, value, index );

  m_unlocks[ index ] |= value;

  queuePacket( makeActorControlSelf( getId(), ToggleActionUnlock, actionId, 1 ) );
}

void Sapphire::Entity::Player::learnSong( uint8_t songId, uint32_t itemId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( songId, value, index );

  m_orchestrion[ index ] |= value;

  queuePacket( makeActorControlSelf( getId(), ToggleOrchestrionUnlock, songId, 1, itemId ) );
}

bool Sapphire::Entity::Player::isActionLearned( uint8_t actionId ) const
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( actionId, value, index );

  return ( m_unlocks[ index ] & value ) != 0;
}

void Sapphire::Entity::Player::gainExp( uint32_t amount )
{
  uint32_t currentExp = getExp();

  uint16_t level = getLevel();

  if( level >= Common::MAX_PLAYER_LEVEL )
  {
    setExp( 0 );
    if( currentExp != 0 )
      queuePacket( makeActorControlSelf( getId(), UpdateUiExp, static_cast< uint8_t >( getClass() ), 0 ) );
    return;
  }

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  uint32_t neededExpToLevel = exdData.get< Sapphire::Data::ParamGrow >( level )->expToNext;

  uint32_t neededExpToLevelplus1 = exdData.get< Sapphire::Data::ParamGrow >( level + 1 )->expToNext;

  queuePacket( makeActorControlSelf( getId(), GainExpMsg, static_cast< uint8_t >( getClass() ), amount ) );

  if( ( currentExp + amount ) >= neededExpToLevel )
  {
    // levelup
    amount = ( currentExp + amount - neededExpToLevel ) > neededExpToLevelplus1 ?
             neededExpToLevelplus1 - 1 :
             ( currentExp + amount - neededExpToLevel );
    if( level + 1 >= Common::MAX_PLAYER_LEVEL )
      amount = 0;
    setExp( amount );
    gainLevel();
    queuePacket( makeActorControlSelf( getId(), UpdateUiExp, static_cast< uint8_t >( getClass() ), amount ) );

  }
  else
  {
    queuePacket(
      makeActorControlSelf( getId(), UpdateUiExp, static_cast< uint8_t >( getClass() ), currentExp + amount ) );
    setExp( currentExp + amount );
  }

  sendStatusUpdate();
}

void Sapphire::Entity::Player::gainLevel()
{

  setLevel( getLevel() + 1 );
  calculateStats();
  sendStats();
  sendStatusUpdate();

  m_hp = getMaxHp();
  m_mp = getMaxMp();

  auto effectListPacket = makeZonePacket< FFXIVIpcStatusEffectList >( getId() );
  effectListPacket->data().classId = static_cast< uint8_t > ( getClass() );
  effectListPacket->data().level1 = getLevel();
  effectListPacket->data().level = getLevel();
  effectListPacket->data().current_hp = getMaxHp();
  effectListPacket->data().current_mp = getMaxMp();
  effectListPacket->data().max_hp = getMaxHp();
  effectListPacket->data().max_mp = getMaxMp();
  sendToInRangeSet( effectListPacket, true );

  sendToInRangeSet( makeActorControl( getId(), LevelUpEffect, static_cast< uint8_t >( getClass() ),
                                      getLevel(), getLevel() - 1 ), true );

  auto classInfoPacket = makeZonePacket< FFXIVIpcUpdateClassInfo >( getId() );
  classInfoPacket->data().classId = static_cast< uint8_t > ( getClass() );
  classInfoPacket->data().level1 = getLevel();
  classInfoPacket->data().level = getLevel();
  classInfoPacket->data().nextLevelIndex = getLevel();
  classInfoPacket->data().currentExp = getExp();
  queuePacket( classInfoPacket );

}

void Sapphire::Entity::Player::sendStatusUpdate()
{
  sendToInRangeSet( std::make_shared< UpdateHpMpTpPacket >( *this ), true );
}

uint8_t Sapphire::Entity::Player::getLevel() const
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( getClass() ) )->expArrayIndex;
  return static_cast< uint8_t >( m_classArray[ classJobIndex ] );
}

uint8_t Sapphire::Entity::Player::getLevelForClass( Common::ClassJob pClass ) const
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( pClass ) )->expArrayIndex;
  return static_cast< uint8_t >( m_classArray[ classJobIndex ] );
}

bool Sapphire::Entity::Player::isClassJobUnlocked( Common::ClassJob classJob ) const
{
  // todo: need to properly check if a job is unlocked, at the moment we just check the class array which will return true for every job if the base class is unlocked
  return getLevelForClass( classJob ) != 0;
}

uint32_t Sapphire::Entity::Player::getExp() const
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( getClass() ) )->expArrayIndex;
  return m_expArray[ classJobIndex ];
}

void Sapphire::Entity::Player::setExp( uint32_t amount )
{
  auto exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( getClass() ) )->expArrayIndex;
  m_expArray[ classJobIndex ] = amount;
}

bool Sapphire::Entity::Player::isInCombat() const
{
  return m_bInCombat;
}

void Sapphire::Entity::Player::setInCombat( bool mode )
{
  //m_lastAttack = GetTickCount();
  m_bInCombat = mode;
}

void Sapphire::Entity::Player::setClassJob( Common::ClassJob classJob )
{
  m_class = classJob;
  uint8_t level = getLevel();

  if( getHp() > getMaxHp() )
    m_hp = getMaxHp();

  if( getMp() > getMaxMp() )
    m_mp = getMaxMp();

  m_tp = 0;

  auto classInfoPacket = makeZonePacket< FFXIVIpcPlayerClassInfo >( getId() );
  classInfoPacket->data().classId = static_cast< uint8_t >( getClass() );
  classInfoPacket->data().classLevel = getLevel();
  classInfoPacket->data().syncedLevel = getLevel();
  queuePacket( classInfoPacket );

  sendToInRangeSet( makeActorControl( getId(), ClassJobChange, 0x04 ), true );

  sendStatusUpdate();

  gaugeClear();
  sendActorGauge();
}

void Sapphire::Entity::Player::setLevel( uint8_t level )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( getClass() ) )->expArrayIndex;
  m_classArray[ classJobIndex ] = level;
}

void Sapphire::Entity::Player::setLevelForClass( uint8_t level, Common::ClassJob classjob )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( classjob ) )->expArrayIndex;

  if( m_classArray[ classJobIndex ] == 0 )
    insertDbClass( classJobIndex );

  m_classArray[ classJobIndex ] = level;
}

void Sapphire::Entity::Player::sendModel()
{
  sendToInRangeSet( std::make_shared< ModelEquipPacket >( *getAsPlayer() ), true );
}

uint32_t Sapphire::Entity::Player::getModelForSlot( Common::GearModelSlot slot )
{
  return m_modelEquip[ slot ];
}

uint64_t Sapphire::Entity::Player::getModelMainWeapon() const
{
  return m_modelMainWeapon;
}

uint64_t Sapphire::Entity::Player::getModelSubWeapon() const
{
  return m_modelSubWeapon;
}

uint64_t Sapphire::Entity::Player::getModelSystemWeapon() const
{
  return m_modelSystemWeapon;
}

int8_t Sapphire::Entity::Player::getAetheryteMaskAt( uint8_t index ) const
{
  if( index > sizeof( m_aetheryte ) )
    return 0;
  return m_aetheryte[ index ];
}

uint8_t Sapphire::Entity::Player::getBirthDay() const
{
  return m_birthDay;
}

uint8_t Sapphire::Entity::Player::getBirthMonth() const
{
  return m_birthMonth;
}

uint8_t Sapphire::Entity::Player::getGuardianDeity() const
{
  return m_guardianDeity;
}

uint8_t Sapphire::Entity::Player::getLookAt( uint8_t index ) const
{
  return m_customize[ index ];
}

void Sapphire::Entity::Player::setLookAt( uint8_t index, uint8_t value )
{
  m_customize[ index ] = value;
}

// spawn this player for pTarget
void Sapphire::Entity::Player::spawn( Entity::PlayerPtr pTarget )
{
  Logger::debug( "[{0}] Spawning {1} for {2}", pTarget->getId(), getName(), pTarget->getName() );

  pTarget->queuePacket( std::make_shared< PlayerSpawnPacket >( *getAsPlayer(), *pTarget ) );
}

// despawn
void Sapphire::Entity::Player::despawn( Entity::PlayerPtr pTarget )
{
  auto pPlayer = pTarget;
  Logger::debug( "Despawning {0} for {1}", getName(), pTarget->getName() );

  pPlayer->freePlayerSpawnId( getId() );

  pPlayer->queuePacket( makeActorControlSelf( getId(), DespawnZoneScreenMsg, 0x04, getId(), 0x01 ) );
}

Sapphire::Entity::ActorPtr Sapphire::Entity::Player::lookupTargetById( uint64_t targetId )
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

void Sapphire::Entity::Player::setLastPing( uint32_t ping )
{
  m_lastPing = ping;
}

uint32_t Sapphire::Entity::Player::getLastPing() const
{
  return m_lastPing;
}

void Sapphire::Entity::Player::setVoiceId( uint8_t voiceId )
{
  m_voice = voiceId;
}

void Sapphire::Entity::Player::setGc( uint8_t gc )
{
  m_gc = gc;

  auto gcAffPacket = makeZonePacket< FFXIVGCAffiliation >( getId() );
  gcAffPacket->data().gcId = m_gc;
  gcAffPacket->data().gcRank[ 0 ] = m_gcRank[ 0 ];
  gcAffPacket->data().gcRank[ 1 ] = m_gcRank[ 1 ];
  gcAffPacket->data().gcRank[ 2 ] = m_gcRank[ 2 ];
  queuePacket( gcAffPacket );
}

void Sapphire::Entity::Player::setGcRankAt( uint8_t index, uint8_t rank )
{
  m_gcRank[ index ] = rank;

  auto gcAffPacket = makeZonePacket< FFXIVGCAffiliation >( getId() );
  gcAffPacket->data().gcId = m_gc;
  gcAffPacket->data().gcRank[ 0 ] = m_gcRank[ 0 ];
  gcAffPacket->data().gcRank[ 1 ] = m_gcRank[ 1 ];
  gcAffPacket->data().gcRank[ 2 ] = m_gcRank[ 2 ];
  queuePacket( gcAffPacket );
}

const uint8_t* Sapphire::Entity::Player::getStateFlags() const
{
  return m_stateFlags;
}

bool Sapphire::Entity::Player::actionHasCastTime( uint32_t actionId ) //TODO: Add logic for special cases
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto actionInfoPtr = exdData.get< Sapphire::Data::Action >( actionId );
  if( actionInfoPtr->preservesCombo )
    return false;

  return actionInfoPtr->cast100ms != 0;

}

bool Sapphire::Entity::Player::hasStateFlag( Common::PlayerStateFlag flag ) const
{
  int32_t iFlag = static_cast< uint32_t >( flag );

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( iFlag, value, index );

  return ( m_stateFlags[ index ] & value ) != 0;
}

void Sapphire::Entity::Player::setStateFlag( Common::PlayerStateFlag flag )
{
  auto prevOnlineStatus = getOnlineStatus();
  int32_t iFlag = static_cast< uint32_t >( flag );

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( iFlag, value, index );

  m_stateFlags[ index ] |= value;
  sendStateFlags();

  auto newOnlineStatus = getOnlineStatus();

  if( prevOnlineStatus != newOnlineStatus )
    sendToInRangeSet( makeActorControl( getId(), SetStatusIcon,
                                        static_cast< uint8_t >( getOnlineStatus() ) ), true );

}

void Sapphire::Entity::Player::setStateFlags( std::vector< Common::PlayerStateFlag > flags )
{
  for( const auto& flag : flags )
  {
    setStateFlag( flag );
  }
}

void Sapphire::Entity::Player::sendStateFlags()
{
  queuePacket( std::make_shared< PlayerStateFlagsPacket >( *getAsPlayer() ) );
}

void Sapphire::Entity::Player::unsetStateFlag( Common::PlayerStateFlag flag )
{
  if( !hasStateFlag( flag ) )
    return;

  auto prevOnlineStatus = getOnlineStatus();

  int32_t iFlag = static_cast< uint32_t >( flag );

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( iFlag, value, index );

  m_stateFlags[ index ] ^= value;
  sendStateFlags();

  auto newOnlineStatus = getOnlineStatus();

  if( prevOnlineStatus != newOnlineStatus )
    sendToInRangeSet( makeActorControl( getId(), SetStatusIcon, static_cast< uint8_t >( getOnlineStatus() ) ), true );
}

void Sapphire::Entity::Player::update( uint64_t tickCount )
{
  // a zoning is pending, lets do it
  if( m_queuedZoneing && ( tickCount - m_queuedZoneing->m_queueTime ) > 800 )
  {
    Common::FFXIVARR_POSITION3 targetPos = m_queuedZoneing->m_targetPosition;
    if( getCurrentTerritory()->getTerritoryTypeId() != m_queuedZoneing->m_targetZone )
    {
      performZoning( m_queuedZoneing->m_targetZone, targetPos, m_queuedZoneing->m_targetRotation );
    }
    else
    {
      auto setActorPosPacket = makeZonePacket< FFXIVIpcActorSetPos >( getId() );
      setActorPosPacket->data().r16 = Util::floatToUInt16Rot( m_queuedZoneing->m_targetRotation );
      setActorPosPacket->data().waitForLoad = 0x04;
      setActorPosPacket->data().x = targetPos.x;
      setActorPosPacket->data().y = targetPos.y;
      setActorPosPacket->data().z = targetPos.z;
      sendToInRangeSet( setActorPosPacket, true );
      setPos( targetPos );
    }
    m_queuedZoneing.reset();
    return;
  }

  if( m_hp <= 0 && m_status != ActorStatus::Dead )
    die();

  if( !isAlive() )
    return;

  m_lastUpdate = tickCount;

  if( !checkAction() )
  {
    if( m_targetId && m_currentStance == Common::Stance::Active && isAutoattackOn() )
    {
      auto mainWeap = getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );

      // @TODO i dislike this, iterating over all in range actors when you already know the id of the actor you need...
      for( auto actor : m_inRangeActor )
      {
        if( actor->getId() == m_targetId && actor->getAsChara()->isAlive() && mainWeap )
        {
          auto chara = actor->getAsChara();

          // default autoattack range
          float range = 3.f + chara->getRadius();

          // default autoattack range for ranged classes
          if( getClass() == ClassJob::Machinist ||
              getClass() == ClassJob::Bard ||
              getClass() == ClassJob::Archer )
            range = 25;


          if( Util::distance( getPos().x, getPos().y, getPos().z,
                              actor->getPos().x, actor->getPos().y, actor->getPos().z ) <= range )
          {

            if( ( tickCount - m_lastAttack ) > mainWeap->getDelay() )
            {
              m_lastAttack = tickCount;
              autoAttack( actor->getAsChara() );
            }

          }
        }
      }
    }
  }

  Chara::update( tickCount );
}

void Sapphire::Entity::Player::onMobKill( uint16_t nameId )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onBNpcKill( *getAsPlayer(), nameId );

  if( isActionLearned( static_cast< uint8_t >( Common::UnlockEntry::HuntingLog ) ) )
  {
    updateHuntingLog( nameId );
  }
}

void Sapphire::Entity::Player::freePlayerSpawnId( uint32_t actorId )
{
  auto spawnId = m_actorSpawnIndexAllocator.freeUsedSpawnIndex( actorId );

  // actor was never spawned for this player
  if( spawnId == m_actorSpawnIndexAllocator.getAllocFailId() )
    return;

  auto freeActorSpawnPacket = makeZonePacket< FFXIVIpcActorFreeSpawn >( getId() );
  freeActorSpawnPacket->data().actorId = actorId;
  freeActorSpawnPacket->data().spawnId = spawnId;
  queuePacket( freeActorSpawnPacket );
}

uint8_t* Sapphire::Entity::Player::getAetheryteArray()
{
  return m_aetheryte;
}

/*! set homepoint */
void Sapphire::Entity::Player::setHomepoint( uint8_t aetheryteId )
{
  m_homePoint = aetheryteId;

  queuePacket( makeActorControlSelf( getId(), SetHomepoint, aetheryteId ) );
}

/*! get homepoint */
uint8_t Sapphire::Entity::Player::getHomepoint() const
{
  return m_homePoint;
}

uint16_t* Sapphire::Entity::Player::getClassArray()
{
  return m_classArray;
}

const uint16_t* Sapphire::Entity::Player::getClassArray() const
{
  return m_classArray;
}

uint32_t* Sapphire::Entity::Player::getExpArray()
{
  return m_expArray;
}

const uint32_t* Sapphire::Entity::Player::getExpArray() const
{
  return m_expArray;
}

uint8_t* Sapphire::Entity::Player::getHowToArray()
{
  return m_howTo;
}

const uint8_t* Sapphire::Entity::Player::getHowToArray() const
{
  return m_howTo;
}

const uint8_t* Sapphire::Entity::Player::getUnlockBitmask() const
{
  return m_unlocks;
}

const uint8_t* Sapphire::Entity::Player::getOrchestrionBitmask() const
{
  return m_orchestrion;
}

const uint8_t* Sapphire::Entity::Player::getMountGuideBitmask() const
{
  return m_mountGuide;
}

uint64_t Sapphire::Entity::Player::getContentId() const
{
  return m_contentId;
}

uint8_t Sapphire::Entity::Player::getVoiceId() const
{
  return m_voice;
}

uint8_t Sapphire::Entity::Player::getGc() const
{
  return m_gc;
}

const uint8_t* Sapphire::Entity::Player::getGcRankArray() const
{
  return m_gcRank;
}

void Sapphire::Entity::Player::queuePacket( Network::Packets::FFXIVPacketBasePtr pPacket )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto pSession = serverMgr.getSession( m_id );

  if( !pSession )
    return;

  auto pZoneCon = pSession->getZoneConnection();

  if( pZoneCon )
    pZoneCon->queueOutPacket( pPacket );

}

void Sapphire::Entity::Player::queueChatPacket( Network::Packets::FFXIVPacketBasePtr pPacket )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto pSession = serverMgr.getSession( m_id );

  if( !pSession )
    return;

  auto pChatCon = pSession->getChatConnection();

  if( pChatCon )
    pChatCon->queueOutPacket( pPacket );
}

bool Sapphire::Entity::Player::isLoadingComplete() const
{
  return m_bLoadingComplete;
}

void Sapphire::Entity::Player::setLoadingComplete( bool bComplete )
{
  m_bLoadingComplete = bComplete;
}

void Sapphire::Entity::Player::performZoning( uint16_t zoneId, const Common::FFXIVARR_POSITION3& pos, float rotation )
{
  m_pos = pos;
  m_territoryTypeId = zoneId;
  m_bMarkedForZoning = true;
  setRot( rotation );
  setZone( zoneId );
  clearBuyBackMap();
}

bool Sapphire::Entity::Player::isMarkedForZoning() const
{
  return m_bMarkedForZoning;
}

ZoneingType Sapphire::Entity::Player::getZoningType() const
{
  return m_zoningType;
}

void Sapphire::Entity::Player::setZoningType( Common::ZoneingType zoneingType )
{
  m_zoningType = zoneingType;
}

void Sapphire::Entity::Player::setSearchInfo( uint8_t selectRegion, uint8_t selectClass, const char* searchMessage )
{
  m_searchSelectRegion = selectRegion;
  m_searchSelectClass = selectClass;
  memset( &m_searchMessage[ 0 ], 0, sizeof( searchMessage ) );
  strcpy( &m_searchMessage[ 0 ], searchMessage );
}

const char* Sapphire::Entity::Player::getSearchMessage() const
{
  return &m_searchMessage[ 0 ];
}

uint8_t Sapphire::Entity::Player::getSearchSelectRegion() const
{
  return m_searchSelectRegion;
}

uint8_t Sapphire::Entity::Player::getSearchSelectClass() const
{
  return m_searchSelectClass;
}

void Sapphire::Entity::Player::sendNotice( const std::string& message ) //Purple Text
{
  queuePacket( std::make_shared< ServerNoticePacket >( getId(), message ) );
}

void Sapphire::Entity::Player::sendUrgent( const std::string& message ) //Red Text
{
  queuePacket( std::make_shared< ChatPacket >( *getAsPlayer(), ChatType::ServerUrgent, message ) );
}

void Sapphire::Entity::Player::sendDebug( const std::string& message ) //Grey Text
{
  queuePacket( std::make_shared< ChatPacket >( *getAsPlayer(), ChatType::ServerDebug, message ) );
}

void Sapphire::Entity::Player::sendLogMessage( uint32_t messageId, uint32_t param2, uint32_t param3,
                                           uint32_t param4, uint32_t param5, uint32_t param6 )
{
  queuePacket( makeActorControlTarget( getId(), ActorControlType::LogMsg, messageId, param2, param3, param4, param5, param6 ) );
}

void Sapphire::Entity::Player::updateHowtosSeen( uint32_t howToId )
{
  uint8_t index = howToId / 8;
  uint8_t bitIndex = howToId % 8;

  uint8_t value = 1 << bitIndex;

  m_howTo[ index ] |= value;
}

void Sapphire::Entity::Player::initHateSlotQueue()
{
  m_freeHateSlotQueue = std::queue< uint8_t >();
  for( int32_t i = 1; i < 26; i++ )
    m_freeHateSlotQueue.push( i );
}

void Sapphire::Entity::Player::hateListAdd( BNpcPtr pBNpc )
{
  if( !m_freeHateSlotQueue.empty() )
  {
    uint8_t hateId = m_freeHateSlotQueue.front();
    m_freeHateSlotQueue.pop();
    m_actorIdTohateSlotMap[ pBNpc->getId() ] = hateId;
    sendHateList();
  }
}

void Sapphire::Entity::Player::hateListRemove( BNpcPtr pBNpc )
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

bool Sapphire::Entity::Player::hateListHasEntry( BNpcPtr pBNpc )
{
  for( const auto& entry : m_actorIdTohateSlotMap )
  {
    if( entry.first == pBNpc->getId() )
      return true;
  }
  return false;
}

void Sapphire::Entity::Player::sendHateList()
{
  auto hateListPacket = makeZonePacket< FFXIVIpcHateList >( getId() );
  hateListPacket->data().numEntries = m_actorIdTohateSlotMap.size();
  auto hateRankPacket = makeZonePacket< FFXIVIpcHateRank >( getId() );
  hateRankPacket->data().numEntries = m_actorIdTohateSlotMap.size();
  auto it = m_actorIdTohateSlotMap.begin();
  for( int32_t i = 0; it != m_actorIdTohateSlotMap.end(); ++it, i++ )
  {
    // TODO: get actual hate values for these
    hateListPacket->data().entry[ i ].actorId = it->first;
    hateListPacket->data().entry[ i ].hatePercent = 100;

    hateRankPacket->data().entry[ i ].actorId = it->first;
    hateRankPacket->data().entry[ i ].hateAmount = 1;
  }
  queuePacket( hateRankPacket );
  queuePacket( hateListPacket );
}

void Sapphire::Entity::Player::onMobAggro( BNpcPtr pBNpc )
{
  hateListAdd( pBNpc );
  queuePacket( makeActorControl( getId(), ToggleAggro, 1 ) );
}

void Sapphire::Entity::Player::onMobDeaggro( BNpcPtr pBNpc )
{
  hateListRemove( pBNpc );
  if( m_actorIdTohateSlotMap.empty() )
    queuePacket( makeActorControl( getId(), ToggleAggro ) );
}

bool Sapphire::Entity::Player::isLogin() const
{
  return m_bIsLogin;
}

void Sapphire::Entity::Player::setIsLogin( bool bIsLogin )
{
  m_bIsLogin = bIsLogin;
}

uint8_t* Sapphire::Entity::Player::getTitleList()
{
  return m_titleList;
}

const uint8_t* Sapphire::Entity::Player::getTitleList() const
{
  return m_titleList;
}

uint16_t Sapphire::Entity::Player::getTitle() const
{
  return m_activeTitle;
}

void Sapphire::Entity::Player::addTitle( uint16_t titleId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( titleId, value, index );

  m_titleList[ index ] |= value;
}

void Sapphire::Entity::Player::setTitle( uint16_t titleId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( titleId, value, index );

  if( ( m_titleList[ index ] & value ) == 0 )   // Player doesn't have title - bail
    return;

  m_activeTitle = titleId;

  sendToInRangeSet( makeActorControl( getId(), SetTitle, titleId ), true );
}

void Sapphire::Entity::Player::setEquipDisplayFlags( uint8_t state )
{
  m_equipDisplayFlags = state;
  auto paramPacket = makeZonePacket< FFXIVIpcEquipDisplayFlags >( getId() );
  paramPacket->data().bitmask = m_equipDisplayFlags;
  sendToInRangeSet( paramPacket, true );
}

uint8_t Sapphire::Entity::Player::getEquipDisplayFlags() const
{
  return m_equipDisplayFlags;
}

void Sapphire::Entity::Player::mount( uint32_t id )
{
  m_mount = id;
  sendToInRangeSet( makeActorControl( getId(), ActorControlType::SetStatus,
                                         static_cast< uint8_t >( Common::ActorStatus::Mounted ) ), true );
  sendToInRangeSet( makeActorControlSelf( getId(), 0x39e, 12 ), true ); //?

  auto mountPacket = makeZonePacket< FFXIVIpcMount >( getId() );
  mountPacket->data().id = id;
  sendToInRangeSet( mountPacket, true );
}

void Sapphire::Entity::Player::dismount()
{
  sendToInRangeSet( makeActorControl( getId(), ActorControlType::SetStatus,
                                         static_cast< uint8_t >( Common::ActorStatus::Idle ) ), true );
  sendToInRangeSet( makeActorControlSelf( getId(), ActorControlType::Dismount, 1 ), true );
  m_mount = 0;
}

void Sapphire::Entity::Player::spawnCompanion( uint16_t id )
{
  if( id > 0 )
  {
    auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

    auto companion = exdData.get< Data::Companion >( id );
    if( !companion )
      return;
  }

  m_companionId = id;
  sendToInRangeSet( makeActorControl( getId(), ActorControlType::ToggleCompanion, id ), true );
}

uint16_t Sapphire::Entity::Player::getCurrentCompanion() const
{
  return m_companionId;
}

uint8_t Sapphire::Entity::Player::getCurrentMount() const
{
  return m_mount;
}

void Sapphire::Entity::Player::setPersistentEmote( uint32_t emoteId )
{
  m_emoteMode = emoteId;
}

uint32_t Sapphire::Entity::Player::getPersistentEmote() const
{
  return m_emoteMode;
}

void Sapphire::Entity::Player::autoAttack( CharaPtr pTarget )
{

  auto mainWeap = getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );

  pTarget->onActionHostile( getAsChara() );
  //uint64_t tick = Util::getTimeMs();
  //srand(static_cast< uint32_t >(tick));

  auto& RNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
  auto variation = static_cast< uint32_t >( RNGMgr.getRandGenerator< float >( 0, 3 ).next() );

  auto damage = Math::CalcStats::calcAutoAttackDamage( *this );

  if( getClass() == ClassJob::Machinist || getClass() == ClassJob::Bard || getClass() == ClassJob::Archer )
  {
    auto effectPacket = std::make_shared< Server::EffectPacket >( getId(), pTarget->getId(), 8 );
    effectPacket->setRotation( Util::floatToUInt16Rot( getRot() ) );

    Common::EffectEntry entry{};
    entry.value = damage.first;
    entry.effectType = Common::ActionEffectType::Damage;
    entry.param0 = static_cast< uint8_t >( damage.second );
    entry.param2 = 0x72;

    effectPacket->addEffect( entry );

    sendToInRangeSet( effectPacket, true );
  }
  else
  {
    auto effectPacket = std::make_shared< Server::EffectPacket >( getId(), pTarget->getId(), 7 );
    effectPacket->setRotation( Util::floatToUInt16Rot( getRot() ) );

    Common::EffectEntry entry{};
    entry.value = damage.first;
    entry.effectType = Common::ActionEffectType::Damage;
    entry.param0 = static_cast< uint8_t >( damage.second );
    entry.param2 = 0x73;

    effectPacket->addEffect( entry );

    sendToInRangeSet( effectPacket, true );

  }

  pTarget->takeDamage( damage.first );

}


/////////////////////////////
// Content Finder
/////////////////////////////
uint32_t Sapphire::Entity::Player::getCFPenaltyTimestamp() const
{
  return m_cfPenaltyUntil;
}

void Sapphire::Entity::Player::setCFPenaltyTimestamp( uint32_t timestamp )
{
  m_cfPenaltyUntil = timestamp;
}

uint32_t Sapphire::Entity::Player::getCFPenaltyMinutes() const
{
  auto currentTimestamp = Common::Util::getTimeSeconds();
  auto endTimestamp = getCFPenaltyTimestamp();

  // check if penalty timestamp already passed current time
  if( currentTimestamp > endTimestamp )
    return 0;

  auto deltaTime = endTimestamp - currentTimestamp;
  return static_cast< uint32_t > ( std::ceil( static_cast< float > (deltaTime) / 60 ) );
}

void Sapphire::Entity::Player::setCFPenaltyMinutes( uint32_t minutes )
{
  auto currentTimestamp = Common::Util::getTimeSeconds();
  setCFPenaltyTimestamp( currentTimestamp + minutes * 60 );
}

uint8_t Sapphire::Entity::Player::getOpeningSequence() const
{
  return m_openingSequence;
}

void Sapphire::Entity::Player::setOpeningSequence( uint8_t seq )
{
  m_openingSequence = seq;
}

uint16_t Sapphire::Entity::Player::getItemLevel() const
{
  return m_itemLevel;
}

/// Tells client to offset their eorzean time by given timestamp.
void Sapphire::Entity::Player::setEorzeaTimeOffset( uint64_t timestamp )
{
  // TODO: maybe change to persistent?
  auto packet = makeZonePacket< FFXIVIpcEorzeaTimeOffset >( getId() );
  packet->data().timestamp = timestamp;

  // Send to single player
  queuePacket( packet );
}

void Sapphire::Entity::Player::setTerritoryTypeId( uint32_t territoryTypeId )
{
  m_territoryTypeId = territoryTypeId;
}

uint32_t Sapphire::Entity::Player::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

void Sapphire::Entity::Player::sendZonePackets()
{
  if( isLogin() )
  {
    //Update player map in servermgr - in case player name has been changed
    auto& serverMgr = Common::Service< World::ServerMgr >::ref();
    serverMgr.updatePlayerName( getId(), getName() );
  }

  getCurrentTerritory()->onBeforePlayerZoneIn( *this );

  auto initPacket = makeZonePacket< FFXIVIpcInit >( getId() );
  initPacket->data().charId = getId();
  queuePacket( initPacket );

  sendInventory();

  if( isLogin() )
  {
    queuePacket( makeActorControlSelf( getId(), SetCharaGearParamUI, m_equipDisplayFlags, 1 ) );
  }

  // set flags, will be reset automatically by zoning ( only on client side though )
  //setStateFlag( PlayerStateFlag::BetweenAreas );
  //setStateFlag( PlayerStateFlag::BetweenAreas1 );

  if( isActionLearned( static_cast< uint8_t >( Common::UnlockEntry::HuntingLog ) ) )
    sendHuntingLog();

  sendStats();

  // only initialize the UI if the player in fact just logged in.
  if( isLogin() )
  {
    auto contentFinderList = makeZonePacket< FFXIVIpcCFAvailableContents >( getId() );

    for( auto i = 0; i < sizeof( contentFinderList->data().contents ); i++ )
    {
      // unlock all contents for now
      contentFinderList->data().contents[ i ] = 0xFF;
    }
    queuePacket( contentFinderList );

    queuePacket( std::make_shared< PlayerSetupPacket >( *this ) );

    auto classInfoPacket = makeZonePacket< FFXIVIpcPlayerClassInfo >( getId() );
    classInfoPacket->data().classId = static_cast< uint8_t >( getClass() );
    classInfoPacket->data().unknown = 1;
    classInfoPacket->data().syncedLevel = getLevel();
    classInfoPacket->data().classLevel = getLevel();
    queuePacket( classInfoPacket );

    m_itemLevel = calculateEquippedGearItemLevel();
    sendItemLevel();
  }

  auto& housingMgr = Common::Service< HousingMgr >::ref();
  if( Sapphire::LandPtr pLand = housingMgr.getLandByOwnerId( getId() ) )
  {
    uint32_t state = 0;

    if( pLand->getHouse() )
    {
      state |= EstateBuilt;

      // todo: remove this, debug for now
      state |= HasAetheryte;
    }

    setLandFlags( LandFlagsSlot::Private, state, pLand->getLandIdent() );
  }

  sendLandFlags();

  auto initZonePacket = makeZonePacket< FFXIVIpcInitZone >( getId() );
  initZonePacket->data().zoneId = getCurrentTerritory()->getTerritoryTypeId();
  initZonePacket->data().weatherId = static_cast< uint8_t >( getCurrentTerritory()->getCurrentWeather() );
  initZonePacket->data().bitmask = 0x1;
  initZonePacket->data().festivalId = getCurrentTerritory()->getCurrentFestival().first;
  initZonePacket->data().additionalFestivalId = getCurrentTerritory()->getCurrentFestival().second;
  initZonePacket->data().pos.x = getPos().x;
  initZonePacket->data().pos.y = getPos().y;
  initZonePacket->data().pos.z = getPos().z;
  queuePacket( initZonePacket );

  getCurrentTerritory()->onPlayerZoneIn( *this );

  if( isLogin() )
  {
    auto unk322 = makeZonePacket< FFXIVARR_IPC_UNK322 >( getId() );
    queuePacket( unk322 );

    auto unk320 = makeZonePacket< FFXIVARR_IPC_UNK320 >( getId() );
    queuePacket( unk320 );
  }

//  if( getLastPing() == 0 )
//    sendQuestInfo();

  m_bMarkedForZoning = false;
}

void Sapphire::Entity::Player::setDirectorInitialized( bool isInitialized )
{
  m_directorInitialized = isInitialized;
}

bool Sapphire::Entity::Player::isDirectorInitialized() const
{
  return m_directorInitialized;
}

void Sapphire::Entity::Player::sendTitleList()
{
  auto titleListPacket = makeZonePacket< FFXIVIpcPlayerTitleList >( getId() );
  memcpy( titleListPacket->data().titleList, getTitleList(), sizeof( titleListPacket->data().titleList ) );

  queuePacket( titleListPacket );
}

void
Sapphire::Entity::Player::sendZoneInPackets( uint32_t param1, uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0,
                                             bool shouldSetStatus = false )
{
  auto zoneInPacket = makeActorControlSelf( getId(), ZoneIn, param1, param2, param3, param4 );
  auto SetStatusPacket = makeActorControl( getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );

  if( !getGmInvis() )
    sendToInRangeSet( zoneInPacket );

  if( shouldSetStatus )
    sendToInRangeSet( SetStatusPacket, true );

  queuePacket( zoneInPacket );

  setZoningType( Common::ZoneingType::None );
  unsetStateFlag( PlayerStateFlag::BetweenAreas );
}

void Sapphire::Entity::Player::finishZoning()
{
  switch( getZoningType() )
  {
    case ZoneingType::None:
      sendZoneInPackets( 0x01 );
      break;

    case ZoneingType::Teleport:
      sendZoneInPackets( 0x01, 0, 0, 110 );
      break;

    case ZoneingType::Return:
    case ZoneingType::ReturnDead:
    {
      if( getStatus() == Common::ActorStatus::Dead )
      {
        resetHp();
        resetMp();
        setStatus( Common::ActorStatus::Idle );
        sendZoneInPackets( 0x01, 0x01, 0, 111, true );
      }
      else
        sendZoneInPackets( 0x01, 0x00, 0, 111 );
    }
      break;

    case ZoneingType::FadeIn:
      break;
  }
}

void Sapphire::Entity::Player::emote( uint32_t emoteId, uint64_t targetId, bool isSilent )
{
  sendToInRangeSet( makeActorControlTarget( getId(), ActorControlType::Emote,
                                         emoteId, 0, isSilent ? 1 : 0, 0, targetId ) );
}

void Sapphire::Entity::Player::emoteInterrupt()
{
  sendToInRangeSet( makeActorControl( getId(), ActorControlType::EmoteInterrupt ) );
}

void Sapphire::Entity::Player::teleportQuery( uint16_t aetheryteId )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  // TODO: only register this action if enough gil is in possession
  auto targetAetheryte = exdData.get< Sapphire::Data::Aetheryte >( aetheryteId );

  if( targetAetheryte )
  {
    auto fromAetheryte = exdData.get< Sapphire::Data::Aetheryte >(
      exdData.get< Sapphire::Data::TerritoryType >( getZoneId() )->aetheryte );

    // calculate cost - does not apply for favorite points or homepoints neither checks for aether tickets
    auto cost = static_cast< uint16_t > (
      ( std::sqrt( std::pow( fromAetheryte->aetherstreamX - targetAetheryte->aetherstreamX, 2 ) +
                   std::pow( fromAetheryte->aetherstreamY - targetAetheryte->aetherstreamY, 2 ) ) / 2 ) + 100 );

    // cap at 999 gil
    cost = std::min< uint16_t >( 999, cost );

    bool insufficientGil = getCurrency( Common::CurrencyType::Gil ) < cost;
    // TODO: figure out what param1 really does
    queuePacket( makeActorControlSelf( getId(), TeleportStart, insufficientGil ? 2 : 0, aetheryteId ) );

    if( !insufficientGil )
    {
      m_teleportQuery.targetAetheryte = aetheryteId;
      m_teleportQuery.cost = cost;
    }
    else
    {
      clearTeleportQuery();
    }
  }
}

Sapphire::Common::PlayerTeleportQuery Sapphire::Entity::Player::getTeleportQuery() const
{
  return m_teleportQuery;
}

void Sapphire::Entity::Player::clearTeleportQuery()
{
  memset( &m_teleportQuery, 0x0, sizeof( Common::PlayerTeleportQuery ) );
}

uint8_t Sapphire::Entity::Player::getNextObjSpawnIndexForActorId( uint32_t actorId )
{
  auto index = m_objSpawnIndexAllocator.getNextFreeSpawnIndex( actorId );

  if( index == m_objSpawnIndexAllocator.getAllocFailId() )
  {
    Logger::warn( "Failed to spawn EObj#{0} for Player#{1} - no remaining spawn indexes available. "
                  "Consider lowering InRangeDistance in world config.",
                  actorId, getId() );

    sendUrgent( "Failed to spawn EObj#{0} for you - no remaining spawn slots. See world log.", actorId );

    return index;
  }

  return index;
}

void Sapphire::Entity::Player::setDyeingInfo( uint32_t itemToDyeContainer, uint32_t itemToDyeSlot, uint32_t dyeBagContainer, uint32_t dyeBagSlot )
{
  m_dyeingInfo.itemToDyeContainer = itemToDyeContainer;
  m_dyeingInfo.itemToDyeSlot = itemToDyeSlot;
  m_dyeingInfo.dyeBagContainer = dyeBagContainer;
  m_dyeingInfo.dyeBagSlot = dyeBagSlot;
}

void Sapphire::Entity::Player::dyeItemFromDyeingInfo()
{
  uint32_t itemToDyeContainer = m_dyeingInfo.itemToDyeContainer;
  uint32_t itemToDyeSlot = m_dyeingInfo.itemToDyeSlot;
  uint32_t dyeBagContainer = m_dyeingInfo.dyeBagContainer;
  uint32_t dyeBagSlot = m_dyeingInfo.dyeBagSlot;

  sendStateFlags(); // Retail sends all 0s to unlock player after a dye? Possibly not setting a flag when the action is started in the backend..?
  auto itemToDye = getItemAt( itemToDyeContainer, itemToDyeSlot );
  auto dyeToUse = getItemAt( dyeBagContainer, dyeBagSlot );

  if ( !itemToDye || !dyeToUse ) return;

  uint32_t stainColorID = dyeToUse->getAdditionalData();
  itemToDye->setStain( stainColorID );

  // TODO: subtract/remove dye used

  insertInventoryItem( static_cast< Sapphire::Common::InventoryType >( itemToDyeContainer ), static_cast< uint16_t >( itemToDyeSlot ), itemToDye );
  updateItemDb( itemToDye );
}

void Sapphire::Entity::Player::resetObjSpawnIndex()
{
  m_objSpawnIndexAllocator.freeAllSpawnIndexes();
}

void Sapphire::Entity::Player::freeObjSpawnIndexForActorId( uint32_t actorId )
{
  auto spawnId = m_objSpawnIndexAllocator.freeUsedSpawnIndex( actorId );

  // obj was never spawned for this player
  if( spawnId == m_objSpawnIndexAllocator.getAllocFailId() )
    return;

  auto freeObjectSpawnPacket = makeZonePacket< FFXIVIpcObjectDespawn >( getId() );
  freeObjectSpawnPacket->data().spawnIndex = spawnId;
  queuePacket( freeObjectSpawnPacket );
}

bool Sapphire::Entity::Player::isObjSpawnIndexValid( uint8_t index )
{
  return m_objSpawnIndexAllocator.isSpawnIndexValid( index );
}

void Sapphire::Entity::Player::setOnEnterEventDone( bool isDone )
{
  m_onEnterEventDone = isDone;
}

bool Sapphire::Entity::Player::isOnEnterEventDone() const
{
  return m_onEnterEventDone;
}

void Sapphire::Entity::Player::setLandFlags( uint8_t flagSlot, uint32_t landFlags, Common::LandIdent ident )
{
  m_landFlags[ flagSlot ].landIdent = ident;
  // todo: leave this in for now but we really need to handle this world id shit properly
  m_landFlags[ flagSlot ].landIdent.worldId = 67;
  m_landFlags[ flagSlot ].landFlags = landFlags;
  m_landFlags[ flagSlot ].unkown1 = 0;
}

void Sapphire::Entity::Player::sendLandFlags()
{
  auto landFlags = makeZonePacket< FFXIVIpcHousingLandFlags >( getId() );

  landFlags->data().freeCompanyHouse = m_landFlags[ Common::LandFlagsSlot::FreeCompany ];
  landFlags->data().privateHouse = m_landFlags[ Common::LandFlagsSlot::Private ];
  landFlags->data().apartment = m_landFlags[ Common::LandFlagsSlot::Apartment ];
  landFlags->data().sharedHouse[ 0 ] = m_landFlags[ Common::LandFlagsSlot::SharedHouse1 ];
  landFlags->data().sharedHouse[ 1 ] = m_landFlags[ Common::LandFlagsSlot::SharedHouse2 ];

  queuePacket( landFlags );
}

void Sapphire::Entity::Player::sendLandFlagsSlot( Common::LandFlagsSlot slot )
{
  auto landFlags = makeZonePacket< FFXIVIpcHousingUpdateLandFlagsSlot >( getId() );

  uint32_t type = 0;

  switch( slot )
  {
    case LandFlagsSlot::Private:
      type = static_cast< uint32_t >( LandType::Private );
      break;

    case LandFlagsSlot::FreeCompany:
      type = static_cast< uint32_t >( LandType::FreeCompany );
      break;

    default:
      // todo: other/unsupported land types
      return;
  }

  landFlags->data().type = type;
  landFlags->data().flagSet = m_landFlags[ slot ];

  queuePacket( landFlags );
}

Sapphire::Common::HuntingLogEntry& Sapphire::Entity::Player::getHuntingLogEntry( uint8_t index )
{
  assert( index < m_huntingLogEntries.size() );
  return m_huntingLogEntries[ index ];
}

void Sapphire::Entity::Player::sendHuntingLog()
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t count = 0;
  for( const auto& entry : m_huntingLogEntries )
  {
    uint64_t completionFlag = 0;
    auto huntPacket = makeZonePacket< FFXIVIpcHuntingLogEntry >( getId() );

    huntPacket->data().u0 = -1;
    huntPacket->data().rank = entry.rank;
    huntPacket->data().index = count;

    for( int i = 1; i <= 10; ++i )
    {
      auto index0 = i - 1;
      bool allComplete = true;
      auto monsterNoteId = ( count + 1 ) * 10000 + entry.rank * 10 + i;

      auto monsterNote = exdData.get< Data::MonsterNote >( monsterNoteId );
      if( !monsterNote )
        continue;

      const auto huntEntry = entry.entries[ index0 ];
      for( int x = 0; x < 3; ++x )
      {
        if( ( huntEntry[ x ] == monsterNote->count[ x ] ) && monsterNote->count[ x ] != 0 )
          completionFlag |= ( 1ull << ( index0 * 5 + x ) );
        else if( monsterNote->count[ x ] != 0 )
          allComplete = false;
      }

      if( allComplete )
        completionFlag |= ( 1ull << ( index0 * 5 + 4 ) );

    }

    memcpy( huntPacket->data().entries, entry.entries, sizeof( entry.entries ) );
    huntPacket->data().completeFlags = completionFlag;
    ++count;
    queuePacket( huntPacket );
  }
}

void Sapphire::Entity::Player::updateHuntingLog( uint16_t id )
{
  std::vector< uint32_t > rankRewards{ 2500, 10000, 20000, 30000, 40000 };
  const auto maxRank = 4;
  auto& pExdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto& logEntry = m_huntingLogEntries[ static_cast< uint8_t >( getClass() ) - 1 ];

  bool logChanged = false;

  // make sure we get the matching base-class if a job is being used
  auto currentClass = static_cast< uint8_t >( getClass() );
  auto classJobInfo = pExdData.get< Sapphire::Data::ClassJob >( currentClass );
  if( !classJobInfo )
    return;

  bool allSectionsComplete = true;
  for( int i = 1; i <= 10; ++i )
  {
    bool sectionComplete = true;
    bool sectionChanged = false;
    uint32_t monsterNoteId = static_cast< uint32_t >( classJobInfo->classJobParent * 10000 + logEntry.rank * 10 + i );
    auto note = pExdData.get< Sapphire::Data::MonsterNote >( monsterNoteId );

    // for classes that don't have entries, if the first fails the rest will fail
    if( !note )
      break;

    for( auto x = 0; x < 4; ++x )
    {
      auto note1 = pExdData.get< Sapphire::Data::MonsterNoteTarget >( note->monsterNoteTarget[ x ] );
      if( note1->bNpcName == id && logEntry.entries[ i - 1 ][ x ] < note->count[ x ] )
      {
        logEntry.entries[ i - 1 ][ x ]++;
        queuePacket( makeActorControlSelf( getId(), HuntingLogEntryUpdate, monsterNoteId, x, logEntry.entries[ i - 1 ][ x ] ) );
        logChanged = true;
        sectionChanged = true;
      }
      if( logEntry.entries[ i - 1 ][ x ] != note->count[ x ] )
        sectionComplete = false;
    }
    if( logChanged && sectionComplete && sectionChanged )
    {
      queuePacket( makeActorControlSelf( getId(), HuntingLogSectionFinish, monsterNoteId, i, 0 ) );
      gainExp( note->reward );
    }
    if( !sectionComplete )
    {
      allSectionsComplete = false;
    }
  }
  if( logChanged && allSectionsComplete )
  {
    queuePacket( makeActorControlSelf( getId(), HuntingLogRankFinish, 4, 0, 0 ) );
    gainExp( rankRewards[ logEntry.rank ] );
    if( logEntry.rank < 4 )
    {
      logEntry.rank++;
      memset( logEntry.entries, 0, 40 );
      queuePacket( makeActorControlSelf( getId(), HuntingLogRankUnlock,
                                        static_cast< uint8_t >( getClass() ), logEntry.rank + 1, 0 ) );
    }
  }

  if( logChanged )
    sendHuntingLog();
}

Sapphire::World::SessionPtr Sapphire::Entity::Player::getSession()
{
  return m_pSession;
}

void Sapphire::Entity::Player::setActiveLand( uint8_t land, uint8_t ward )
{
  m_activeLand.plot = land;
  m_activeLand.ward = ward;
}

Sapphire::Common::ActiveLand Sapphire::Entity::Player::getActiveLand() const
{
  return m_activeLand;
}

bool Sapphire::Entity::Player::hasQueuedAction() const
{
  return m_pQueuedAction != nullptr;
}

void Sapphire::Entity::Player::setQueuedAction( Sapphire::World::Action::ActionPtr pAction )
{
  m_pQueuedAction = std::move( pAction ); // overwrite previous queued action if any
}

bool Sapphire::Entity::Player::checkAction()
{
  if( m_pCurrentAction == nullptr )
    return false;

  if( m_pCurrentAction->update() )
  {
    if( m_pCurrentAction->isInterrupted() && m_pCurrentAction->getInterruptType() != Common::ActionInterruptType::DamageInterrupt )
    {
      // we moved (or whatever not damage interrupt) so we don't want to execute queued cast
      m_pQueuedAction = nullptr;
    }
    m_pCurrentAction = nullptr;

    if( hasQueuedAction() )
    {
      sendDebug( "Queued skill start: {0}", m_pQueuedAction->getId() );
      if( m_pQueuedAction->hasCastTime() )
      {
        setCurrentAction( m_pQueuedAction );
      }
      m_pQueuedAction->start();
      m_pQueuedAction = nullptr;
    }
  }

  return true;
}

std::vector< Sapphire::Entity::ShopBuyBackEntry >& Sapphire::Entity::Player::getBuyBackListForShop( uint32_t shopId )
{
  return m_shopBuyBackMap[ shopId ];
}

void Sapphire::Entity::Player::addBuyBackItemForShop( uint32_t shopId, const Sapphire::Entity::ShopBuyBackEntry& entry )
{
  auto& list = m_shopBuyBackMap[ shopId ];
  list.insert( list.begin(), entry );
}

void Sapphire::Entity::Player::clearBuyBackMap()
{
  for( auto& list : m_shopBuyBackMap )
  {
    for( auto& entry : list.second )
    {
      deleteItemDb( entry.item );
    }
  }
  m_shopBuyBackMap.clear();
}

void Sapphire::Entity::Player::gaugeClear()
{
  std::memset( &m_gauge, 0, sizeof( m_gauge ) );
}

void Sapphire::Entity::Player::sendActorGauge()
{
  auto pPacket = makeZonePacket< FFXIVIpcActorGauge >( getId() );
  pPacket->data().classJobId = static_cast< uint8_t >( getClass() );
  std::memcpy( pPacket->data().data, &m_gauge, 15 );

  queuePacket( pPacket );
}

void Sapphire::Entity::Player::gaugeSetRaw( uint8_t* pData )
{
  std::memcpy( &m_gauge, pData, 15 );
  sendActorGauge();
}