#include <Common.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Logging/Logger.h>
#include <Exd/ExdData.h>

#include <cmath>
#include <utility>
#include <Service.h>

#include "Session.h"
#include "Player.h"
#include "BNpc.h"

#include "Manager/TerritoryMgr.h"
#include "Manager/RNGMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/PartyMgr.h"
#include "Manager/WarpMgr.h"
#include "Manager/FreeCompanyMgr.h"
#include "Manager/MapMgr.h"
#include "Manager/MgrUtil.h"
#include "Manager/ActionMgr.h"

#include "Territory/InstanceContent.h"

#include "Network/GameConnection.h"
#include "Network/PacketContainer.h"
#include "Network/CommonActorControl.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "Network/PacketWrappers/PlayerSpawnPacket.h"
#include "Network/PacketWrappers/EffectPacket1.h"
#include "Network/PacketWrappers/InitZonePacket.h"

#include "Action/Action.h"

#include "Math/CalcStats.h"

#include "WorldServer.h"

#include <Manager/TaskMgr.h>
#include <Task/ActionIntegrityTask.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Entity;

using InventoryMap = std::map< uint16_t, Sapphire::ItemContainerPtr >;
using InvSlotPair = std::pair< uint16_t, int8_t >;
using InvSlotPairVec = std::vector< InvSlotPair >;

// player constructor
Player::Player() :
  Chara( ObjKind::Player ),
  m_lastDBWrite( 0 ),
  m_bIsLogin( false ),
  m_characterId( 0 ),
  m_modelMainWeapon( 0 ),
  m_modelSubWeapon( 0 ),
  m_homePoint( 0 ),
  m_startTown( 0 ),
  m_townWarpFstFlags( 0 ),
  m_playTime( 0 ),
  m_lastActionTick( 0 ),
  m_bInCombat( false ),
  m_bLoadingComplete( false ),
  m_bAutoattack( false ),
  m_markedForRemoval( false ),
  m_mount( 0 ),
  m_emoteMode( 0 ),
  m_directorInitialized( false ),
  m_onEnterEventDone( false ),
  m_falling( false ),
  m_pQueuedAction( nullptr ),
  m_partyId( 0 ),
  m_onlineStatusCustom( 0 ),
  m_onlineStatus( 0 ),
  m_bIsConnected( false )
{
  m_id = 0;
  m_currentStance = Stance::Passive;
  m_onlineStatus = 0;
  m_status = ActorStatus::Idle;
  m_invincibilityType = InvincibilityType::InvincibilityNone;
  m_radius = 1.f;

  memset( m_name, 0, sizeof( m_name ) );
  memset( m_searchMessage, 0, sizeof( m_searchMessage ) );
  std::fill( std::begin( m_questTracking ), std::end( m_questTracking ), 0 );
  std::fill( std::begin( m_condition ), std::end( m_condition ), 0 );
  std::fill( std::begin( m_classArray ), std::end( m_classArray ), 0 );
  std::fill( std::begin( m_expArray ), std::end( m_expArray ), 0 );

  for( uint8_t i = 0; i < 80; ++i )
  {
    m_recast[ i ] = 0.0f;
    m_recastMax[ i ] = 0.0f;
  }

  for( auto& i : m_charaLandData )
  {
    memset( &i, 0xFF, 8 );
    memset( &i.landFlags, 0, 8 );
  }

  m_objSpawnIndexAllocator.init( MAX_DISPLAYED_EOBJS );
  m_actorSpawnIndexAllocator.init( MAX_DISPLAYED_ACTORS, true );
  initHateSlotQueue();
  initSpawnIdQueue();
}

Player::~Player() = default;

void Player::unload()
{
  // do one last update to db
  updateSql();
  // reset isLogin and loading sequences just in case
  setIsLogin( false );
  setConnected( false );
  setLoadingComplete( false );
  // unset player for removal
  setMarkedForRemoval( false );

  syncLastDBWrite();
}

// TODO: add a proper calculation based on race / job / level / gear
uint32_t Player::getMaxHp()
{
  return m_maxHp;
}

uint32_t Player::getMaxMp()
{
  return m_maxMp;
}

uint32_t Player::getPrevTerritoryId() const
{
  return m_prevTerritoryId;
}

uint8_t Player::getGmRank() const
{
  return m_gmRank;
}

void Player::setGmRank( uint8_t rank )
{
  m_gmRank = rank;
}

bool Player::getGmInvis() const
{
  return m_gmInvis;
}

void Player::setGmInvis( bool invis )
{
  m_gmInvis = invis;
}

bool Player::isActingAsGm() const
{
  auto status = getOnlineStatus();
  return status == OnlineStatus::GameMaster || status == OnlineStatus::GameMaster1 || status == OnlineStatus::GameMaster2;
}

uint8_t Player::getMode() const
{
  return m_mode;
}

void Player::setMode( uint8_t mode )
{
  m_mode = mode;
}

uint8_t Player::getStartTown() const
{
  return m_startTown;
}

void Player::setMarkedForRemoval( bool removal )
{
  m_markedForRemoval = removal;
}

bool Player::isMarkedForRemoval() const
{
  return m_markedForRemoval;
}

Common::OnlineStatus Player::getOnlineStatus() const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  uint32_t statusDisplayOrder = 0xFF14;
  auto applicableStatus = isConnected() ? static_cast< uint32_t >( OnlineStatus::Online ) : static_cast< uint32_t >( OnlineStatus::Offline );


  for( uint32_t i = 0; i < std::numeric_limits< decltype( m_onlineStatus ) >::digits; ++i )
  {
    bool bit = ( getFullOnlineStatusMask() >> i ) & 1;

    if( !bit )
      continue;

    auto pOnlineStatus = exdData.getRow< Excel::OnlineStatus >( i );
    if( !pOnlineStatus )
      continue;

    if( pOnlineStatus->data().ListOrder < statusDisplayOrder )
    {
      // todo: also check that the status can actually be set here, otherwise we need to ignore it (and ban the player obv)
      statusDisplayOrder = pOnlineStatus->data().ListOrder;
      applicableStatus = i;
    }
  }

  return static_cast< OnlineStatus >( applicableStatus );
}

void Player::setOnlineStatusMask( uint64_t status )
{
  m_onlineStatus = status;
}

uint64_t Player::getOnlineStatusMask() const
{
  return m_onlineStatus;
}

uint64_t Player::getFullOnlineStatusMask() const
{
  return m_onlineStatus | m_onlineStatusCustom;
}

/*! sets the list of current online status */
void Player::setOnlineStatusCustomMask( uint64_t status )
{
  m_onlineStatusCustom = status;
}

uint64_t Player::getOnlineStatusCustomMask() const
{
  return m_onlineStatusCustom;
}

void Player::addOnlineStatus( OnlineStatus status )
{
  uint64_t statusValue = 1ull << static_cast< uint8_t >( status );
  uint64_t newFlags = ( getOnlineStatusMask() & getOnlineStatusCustomMask() ) | statusValue;

  setOnlineStatusMask( newFlags );

  Service< World::Manager::PlayerMgr >::ref().onOnlineStatusChanged( *this, false );
}

void Player::addOnlineStatus( const std::vector< Common::OnlineStatus >& status )
{
  uint64_t newFlags = getOnlineStatusMask();
  for( const auto& state : status )
  {
    uint64_t statusValue = 1ull << static_cast< uint8_t >( state );
    newFlags |= statusValue;
  }

  setOnlineStatusMask( newFlags );

  Service< World::Manager::PlayerMgr >::ref().onOnlineStatusChanged( *this, false );
}

void Player::removeOnlineStatus( OnlineStatus status )
{
  uint64_t statusValue = 1ull << static_cast< uint8_t >( status );
  uint64_t newFlags = getOnlineStatusMask();
  uint64_t newFlagsCustom = getOnlineStatusCustomMask();
  newFlags &= ~statusValue;
  newFlagsCustom &= ~statusValue;

  setOnlineStatusMask( newFlags );
  setOnlineStatusCustomMask( newFlagsCustom );

  Service< World::Manager::PlayerMgr >::ref().onOnlineStatusChanged( *this, false );
}

void Player::removeOnlineStatus( const std::vector< Common::OnlineStatus >& status )
{
  uint64_t newFlags = getOnlineStatusMask();
  uint64_t newFlagsCustom = getOnlineStatusCustomMask();
  for( const auto& state : status )
  {
    uint64_t statusValue = 1ull << static_cast< uint8_t >( state );
    newFlags &= ~statusValue;
    newFlagsCustom &= ~statusValue;
  }

  setOnlineStatusMask( newFlags );
  setOnlineStatusCustomMask( newFlagsCustom );

  Service< World::Manager::PlayerMgr >::ref().onOnlineStatusChanged( *this, false );
}

void Player::calculateStats()
{
  calculateBonusStats();

  uint8_t tribe = getLookAt( Common::CharaLook::Tribe );
  uint8_t level = getLevel();
  auto job = static_cast< uint8_t >( getClass() );
  auto deity = getGuardianDeity();

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto classInfo = exdData.getRow< Excel::ClassJob >( job );
  auto tribeInfo = exdData.getRow< Excel::Tribe >( tribe );
  auto deityInfo = exdData.getRow< Excel::GuardianDeity >( deity );
  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( level );

  float base = Math::CalcStats::calculateBaseStat( *this );

  auto str = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().STR ) / 100 ) ) + tribeInfo->data().STR;
  auto dex = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().DEX ) / 100 ) ) + tribeInfo->data().DEX;
  auto vit = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().VIT ) / 100 ) ) + tribeInfo->data().VIT;
  auto inte = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().INT_ ) / 100 ) ) + tribeInfo->data().INT_;
  auto mnd = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().MND ) / 100 ) ) + tribeInfo->data().MND;
  auto pie = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().PIE ) / 100 ) ) + tribeInfo->data().PIE;

  setStatValue( BaseParam::Strength, str );
  setStatValue( BaseParam::Dexterity, dex );
  setStatValue( BaseParam::Vitality, vit );
  setStatValue( BaseParam::Intelligence, inte );
  setStatValue( BaseParam::Mind, mnd );
  setStatValue( BaseParam::Piety, pie );

  auto determination = static_cast< uint32_t >( base );
  auto skillSpeed = paramGrowthInfo->data().ParamBase;
  auto spellSpeed = paramGrowthInfo->data().ParamBase;
  auto accuracy = paramGrowthInfo->data().ParamBase;
  auto critHitRate = paramGrowthInfo->data().ParamBase;
  auto parry = paramGrowthInfo->data().ParamBase;

  setStatValue( BaseParam::Determination, determination );
  setStatValue( BaseParam::SkillSpeed, skillSpeed );
  setStatValue( BaseParam::SpellSpeed, spellSpeed );
  setStatValue( BaseParam::CriticalHit, critHitRate );
  setStatValue( BaseParam::Accuracy, accuracy );
  setStatValue( BaseParam::Parry, parry );

  setStatValue( BaseParam::Haste, 100 );
  setStatValue( BaseParam::Defense, 0 );
  setStatValue( BaseParam::MagicDefense, 0 );

  setStatValue( BaseParam::FireResistance, classInfo->data().Element[0] );
  setStatValue( BaseParam::IceResistance, classInfo->data().Element[1] );
  setStatValue( BaseParam::WindResistance, classInfo->data().Element[2] );
  setStatValue( BaseParam::EarthResistance, classInfo->data().Element[3] );
  setStatValue( BaseParam::LightningResistance, classInfo->data().Element[4] );
  setStatValue( BaseParam::WaterResistance, classInfo->data().Element[5] );

  setStatValue( BaseParam::AttackPower, str );
  setStatValue( BaseParam::AttackMagicPotency, inte );
  setStatValue( BaseParam::HealingMagicPotency, mnd );

  setStatValue( BaseParam::PiercingResistance, 0 );

  m_maxMp = Math::CalcStats::calculateMaxMp( *this );

  m_maxHp = Math::CalcStats::calculateMaxHp( *this );

  if( m_mp > m_maxMp )
    m_mp = m_maxMp;

  if( m_hp > m_maxHp )
    m_hp = m_maxHp;
}


void Player::setAutoattack( bool mode )
{
  m_bAutoattack = mode;
}

bool Player::isAutoattackOn() const
{
  return m_bAutoattack;
}

void Player::sendStats()
{
  Service< World::Manager::PlayerMgr >::ref().onStatsChanged( *this );
}

bool Player::exitInstance()
{
  auto& warpMgr = Common::Service< WarpMgr >::ref();

  resetHp();
  resetMp();

  warpMgr.requestMoveTerritory( *this, WarpType::WARP_TYPE_CONTENT_END_RETURN, getPrevTerritoryId(), getPrevPos(), getPrevRot() );

  return true;
}

uint32_t Player::getPlayTime() const
{
  return m_playTime;
}

uint8_t Player::getRace() const
{
  return getLookAt( CharaLook::Race );
}

uint8_t Player::getGender() const
{
  return getLookAt( CharaLook::Gender );
}

void Player::initSpawnIdQueue()
{
  m_actorSpawnIndexAllocator.freeAllSpawnIndexes();
}

uint8_t Player::getSpawnIdForActorId( uint32_t actorId )
{
  auto index = m_actorSpawnIndexAllocator.getNextFreeSpawnIndex( actorId );

  if( index == m_actorSpawnIndexAllocator.getAllocFailId() )
  {
    Logger::warn( "Failed to spawn Chara#{0} for Player#{1} - no remaining spawn indexes available. "
                  "Consider lowering InRangeDistance in world config.",
                  actorId, getId() );

    PlayerMgr::sendUrgent( *this,  "Failed to spawn Chara#{0} for you - no remaining spawn slots. See world log.", actorId );
  }

  return index;
}

bool Player::isActorSpawnIdValid( uint8_t spawnIndex )
{
  return m_actorSpawnIndexAllocator.isSpawnIndexValid( spawnIndex );
}

void Player::registerAetheryte( uint8_t aetheryteId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( aetheryteId, value, index );

  m_aetheryte[ index ] |= value;
  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), LearnTeleport, aetheryteId, 1 ) );
}

bool Player::isAetheryteRegistered( uint8_t aetheryteId ) const
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( aetheryteId, value, index );

  return ( m_aetheryte[ index ] & value ) != 0;
}

Player::Discovery& Player::getDiscoveryBitmask()
{
  return m_discovery;
}

void Player::discover( int16_t map_id, int16_t sub_id )
{
  // map.exd field 12 -> index in one of the two discovery sections, if field 15 is false, need to use 2nd section
  // section 1 starts at 0 - 2 bytes each
  // section to starts at 320 - 4 bytes long

  auto& exdData = Common::Service< Data::ExdData >::ref();

  int32_t offset;

  auto info = exdData.getRow< Excel::Map >( map_id );
  if( !info )
  {
    PlayerMgr::sendDebug( *this, "discover(): Could not obtain map data for map_id == {0}", map_id );
    return;
  }

  if( info->data().IsUint16Discovery )
    offset = 2 * info->data().DiscoveryIndex;
  else
    offset = 320 + 4 * info->data().DiscoveryIndex;

  int32_t index = offset + sub_id / 8;
  uint8_t bitIndex = sub_id % 8;

  uint8_t value = 1 << bitIndex;

  m_discovery[ index ] |= value;

  uint16_t level = getLevel();

  uint32_t exp = ( exdData.getRow< Excel::ParamGrow >( level )->data().NextExp * 5 / 100 );

  gainExp( exp );

  // gain 10x additional EXP if entire map is completed
  uint32_t mask = info->data().DiscoveryFlag;
  uint32_t discoveredAreas;
  if( info->data().IsUint16Discovery )
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

bool Player::isNewAdventurer() const
{
  return m_bNewAdventurer;
}

void Player::setNewAdventurer( bool state )
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

void Player::resetDiscovery()
{
  memset( m_discovery.data(), 0, m_discovery.size() );
}

void Player::setRewardFlag( Common::UnlockEntry unlockId )
{
  uint16_t index;
  uint8_t value;
  auto unlock = static_cast< uint16_t >( unlockId );
  Util::valueToFlagByteIndexValue( unlock, value, index );

  m_unlocks[ index ] |= value;

  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), SetRewardFlag, unlock, 1 ) );
}

void Player::learnSong( uint8_t songId, uint32_t itemId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( songId, value, index );

  m_orchestrion[ index ] |= value;
}

bool Player::hasReward( Common::UnlockEntry unlockId ) const
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( static_cast< uint16_t >( unlockId ), value, index );

  return ( m_unlocks[ index ] & value ) != 0;
}

bool Player::hasMount( uint32_t mountId ) const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto mount = exdData.getRow< Excel::Mount >( mountId );

  if( !mount || mount->data().MountOrder == -1 || mount->data().Model == 0 )
    return false;

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( mount->data().MountOrder, value, index );

  return m_mountGuide[ index ] & value;
}

void Player::gainExp( uint32_t amount )
{
  uint32_t currentExp = getExp();

  uint16_t level = getLevel();

  if( level >= Common::MAX_PLAYER_LEVEL )
  {
    setExp( 0 );
    if( currentExp != 0 )
      Service< World::Manager::PlayerMgr >::ref().onGainExp( *this, 0 );

    return;
  }

  auto& exdData = Common::Service< Data::ExdData >::ref();

  uint32_t neededExpToLevel = exdData.getRow< Excel::ParamGrow >( level )->data().NextExp;
  uint32_t neededExpToLevelPlus1 = exdData.getRow< Excel::ParamGrow >( level + 1 )->data().NextExp;

  if( ( currentExp + amount ) >= neededExpToLevel )
  {
    // levelup
    amount = ( currentExp + amount - neededExpToLevel ) > neededExpToLevelPlus1 ?
             neededExpToLevelPlus1 - 1 :
             ( currentExp + amount - neededExpToLevel );
    if( level + 1 >= Common::MAX_PLAYER_LEVEL )
      amount = 0;

    setExp( amount );
    Service< World::Manager::PlayerMgr >::ref().onGainExp( *this, amount );
    levelUp();
  }
  else
  {
    setExp( currentExp + amount );
    Service< World::Manager::PlayerMgr >::ref().onGainExp( *this, amount );
  }
}

void Player::levelUp()
{
  m_hp = getMaxHp();
  m_mp = getMaxMp();

  setLevel( getLevel() + 1 );

  Service< World::Manager::PlayerMgr >::ref().onLevelUp( *this );
  Service< World::Manager::MapMgr >::ref().updateQuests( *this );
}

void Player::sendHudParam()
{
  // todo: overrides are funky
  Service< World::Manager::PlayerMgr >::ref().onHudParamChanged( *this );
}

uint8_t Player::getLevel() const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( getClass() ) )->data().WorkIndex;
  return static_cast< uint8_t >( m_classArray[ classJobIndex ] );
}

uint8_t Player::getLevelSync() const
{
  // TODO: implement levelSync
  return getLevel();
}

uint8_t Player::getLevelForClass( Common::ClassJob pClass ) const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( pClass ) )->data().WorkIndex;
  return static_cast< uint8_t >( m_classArray[ classJobIndex ] );
}

Common::ClassJob Player::getFirstClass() const
{
  return m_firstClass;
}

bool Player::isClassJobUnlocked( Common::ClassJob classJob ) const
{
  // todo: need to properly check if a job is unlocked, at the moment we just check the class array which will return true for every job if the base class is unlocked
  return getLevelForClass( classJob ) != 0;
}

uint32_t Player::getExp() const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( getClass() ) )->data().WorkIndex;
  return m_expArray[ classJobIndex ];
}

void Player::setExp( uint32_t amount )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( getClass() ) )->data().WorkIndex;
  m_expArray[ classJobIndex ] = amount;
}

bool Player::isInCombat() const
{
  return m_bInCombat;
}

void Player::setInCombat( bool mode )
{
  //m_lastAttack = GetTickCount();
  m_bInCombat = mode;
}

void Player::setClassJob( Common::ClassJob classJob )
{
  m_class = classJob;

  if( getHp() > getMaxHp() )
    m_hp = getMaxHp();

  if( getMp() > getMaxMp() )
    m_mp = getMaxMp();

  m_tp = 0;

  Service< World::Manager::PlayerMgr >::ref().sendStatusUpdate( *this );
  Service< World::Manager::PlayerMgr >::ref().onClassChanged( *this );
  Service< World::Manager::MapMgr >::ref().updateQuests( *this );
}

void Player::setLevel( uint8_t level )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( getClass() ) )->data().WorkIndex;
  m_classArray[ classJobIndex ] = level;
}

void Player::setLevelForClass( uint8_t level, Common::ClassJob classjob )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( classjob ) )->data().WorkIndex;

  if( m_classArray[ classJobIndex ] == 0 )
    insertDbClass( classJobIndex, level );

  m_classArray[ classJobIndex ] = level;

  Service< World::Manager::PlayerMgr >::ref().onSetLevelForClass( *this, classjob );
}

void Player::sendModel()
{
  Service< World::Manager::PlayerMgr >::ref().onGearChanged( *this );
}

uint32_t Player::getModelForSlot( Common::GearModelSlot slot )
{
  return m_modelEquip[ slot ];
}

uint64_t Player::getModelMainWeapon() const
{
  return m_modelMainWeapon;
}

uint64_t Player::getModelSubWeapon() const
{
  return m_modelSubWeapon;
}

uint64_t Player::getModelSystemWeapon() const
{
  return m_modelSystemWeapon;
}

uint8_t Player::getAetheryteMaskAt( uint8_t index ) const
{
  if( index > sizeof( m_aetheryte ) )
    return 0;
  return m_aetheryte[ index ];
}

uint8_t Player::getBirthDay() const
{
  return m_birthDay;
}

uint8_t Player::getBirthMonth() const
{
  return m_birthMonth;
}

uint8_t Player::getGuardianDeity() const
{
  return m_guardianDeity;
}

uint8_t Player::getLookAt( uint8_t index ) const
{
  return m_customize[ index ];
}

void Player::setLookAt( uint8_t index, uint8_t value )
{
  m_customize[ index ] = value;
}

// spawn this player for pTarget
void Player::spawn( Entity::PlayerPtr pTarget )
{
  Logger::debug( "Spawning {0} for {1}", getName(), pTarget->getName() );
  auto spawnPacket = std::make_shared< PlayerSpawnPacket >( *this, *pTarget );
  server().queueForPlayer( pTarget->getCharacterId(), spawnPacket );
}

// despawn
void Player::despawn( Entity::PlayerPtr pTarget )
{
  const auto& pPlayer = pTarget;
  Logger::debug( "Despawning {0} for {1}", getName(), pTarget->getName() );

  pPlayer->freePlayerSpawnId( getId() );
  server().queueForPlayer( pTarget->getCharacterId(), makeActorControlSelf( getId(), WarpStart, 0x04, getId(), 0x01 ) );
}

GameObjectPtr Player::lookupTargetById( uint64_t targetId )
{
  GameObjectPtr targetActor;
  auto inRange = getInRangeActors( true );
  for( const auto& actor : inRange )
  {
    if( actor->getId() == targetId )
      targetActor = actor;
  }
  return targetActor;
}

uint64_t Player::getLastDBWrite() const
{
  return m_lastDBWrite;
}

void Player::setVoiceId( uint8_t voiceId )
{
  m_voice = voiceId;
}

void Player::setGc( uint8_t gc )
{
  m_gc = gc;
}

void Player::setGcRankAt( uint8_t index, uint8_t rank )
{
  m_gcRank[ index ] = rank;
}

const Player::Condition& Player::getConditions() const
{
  return m_condition;
}

bool Player::hasCondition( Common::PlayerCondition flag ) const
{
  auto iFlag = static_cast< int32_t >( flag );

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( iFlag, value, index );

  return ( m_condition[ index ] & value ) != 0;
}

void Player::setCondition( Common::PlayerCondition flag )
{
  auto iFlag = static_cast< int32_t >( flag );

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( iFlag, value, index );

  m_condition[ index ] |= value;
}

void Player::removeCondition( Common::PlayerCondition flag )
{
  if( !hasCondition( flag ) )
    return;

  auto iFlag = static_cast< int32_t >( flag );

  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( iFlag, value, index );

  m_condition[ index ] ^= value;
}

void Player::update( uint64_t tickCount )
{
  // todo: better way to handle this override chara update
  Service< World::Manager::PlayerMgr >::ref().onUpdate( *this, tickCount );

  Chara::update( tickCount );
}

uint64_t Player::getLastAttack() const
{
  return m_lastAttack;
}

void Player::setLastAttack( uint64_t tickCount )
{
  m_lastAttack = tickCount;
}

void Player::freePlayerSpawnId( uint32_t actorId )
{
  auto spawnId = m_actorSpawnIndexAllocator.freeUsedSpawnIndex( actorId );

  // actor was never spawned for this player
  if( spawnId == m_actorSpawnIndexAllocator.getAllocFailId() )
    return;

  auto freeActorSpawnPacket = makeZonePacket< FFXIVIpcActorFreeSpawn >( getId() );
  freeActorSpawnPacket->data().actorId = actorId;
  freeActorSpawnPacket->data().spawnId = spawnId;
  server().queueForPlayer( getCharacterId(), freeActorSpawnPacket );
}

Player::AetheryteList& Player::getAetheryteArray()
{
  return m_aetheryte;
}

/*! set homepoint */
void Player::setHomepoint( uint8_t aetheryteId )
{
  m_homePoint = aetheryteId;
  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), SetHomepoint, aetheryteId ) );
}

/*! get homepoint */
uint8_t Player::getHomepoint() const
{
  return m_homePoint;
}

Player::ClassList& Player::getClassArray()
{
  return m_classArray;
}

Player::ExpList& Player::getExpArray()
{
  return m_expArray;
}

Player::HowToList& Player::getHowToArray()
{
  return m_howTo;
}

const Player::UnlockList& Player::getUnlockBitmask() const
{
  return m_unlocks;
}

const Player::OrchestrionList& Player::getOrchestrionBitmask() const
{
  return m_orchestrion;
}

void Player::setOrchestrionBitmask( const Player::OrchestrionList& orchestrion )
{
  m_orchestrion = orchestrion;
}

void Player::unlockMount( uint32_t mountId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto mount = exdData.getRow< Excel::Mount >( mountId );

  if( mount->data().MountOrder == -1 )
    return;

  m_mountGuide[ mount->data().MountOrder / 8 ] |= ( 1 << ( mount->data().MountOrder % 8 ) );

  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), Network::ActorControl::SetMountBitmask, mount->data().MountOrder, 1 ) );
}

void Player::unlockCompanion( uint32_t companionId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto companion = exdData.getRow< Excel::Companion >( companionId );

  //if( companion->data(). == -1 )
  //  return;
  
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( companionId, value, index );

  m_minionGuide[ index ] |= value;

  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), Network::ActorControl::LearnCompanion, companionId, 1 ) );
}

Player::MinionList& Player::getMinionGuideBitmask()
{
  return m_minionGuide;
}

Player::MountList& Player::getMountGuideBitmask()
{
  return m_mountGuide;
}

uint64_t Player::getCharacterId() const
{
  return m_characterId;
}

uint8_t Player::getVoiceId() const
{
  return m_voice;
}

uint8_t Player::getGc() const
{
  return m_gc;
}

const std::array< uint8_t, 3 >& Player::getGcRankArray() const
{
  return m_gcRank;
}

bool Player::isLoadingComplete() const
{
  return m_bLoadingComplete;
}

void Player::setLoadingComplete( bool bComplete )
{
  m_bLoadingComplete = bComplete;
}

void Player::setSearchInfo( uint8_t selectRegion, uint8_t selectClass, const char* searchMessage )
{
  m_searchSelectRegion = selectRegion;
  m_searchSelectClass = selectClass;
  memset( &m_searchMessage[ 0 ], 0, sizeof( searchMessage ) );
  strcpy( &m_searchMessage[ 0 ], searchMessage );
}

const char* Player::getSearchMessage() const
{
  return &m_searchMessage[ 0 ];
}

uint8_t Player::getSearchSelectRegion() const
{
  return m_searchSelectRegion;
}

uint8_t Player::getSearchSelectClass() const
{
  return m_searchSelectClass;
}

void Player::updateHowtosSeen( uint32_t howToId )
{
  uint8_t index = howToId / 8;
  uint8_t bitIndex = howToId % 8;

  uint8_t value = 1 << bitIndex;

  m_howTo[ index ] |= value;
}

void Player::initHateSlotQueue()
{
  m_freeHateSlotQueue = std::queue< uint8_t >();
  for( int32_t i = 1; i < 26; ++i )
    m_freeHateSlotQueue.push( i );
}

void Player::hateListAdd( const BNpc& bnpc )
{
  if( !m_freeHateSlotQueue.empty() )
  {
    uint8_t hateId = m_freeHateSlotQueue.front();
    m_freeHateSlotQueue.pop();
    m_actorIdTohateSlotMap[ bnpc.getId() ] = hateId;
    Service< World::Manager::PlayerMgr >::ref().onHateListChanged( *this );
  }
}

void Player::hateListRemove( const BNpc& bnpc )
{

  auto it = m_actorIdTohateSlotMap.begin();
  for( ; it != m_actorIdTohateSlotMap.end(); ++it )
  {
    if( it->first == bnpc.getId() )
    {
      uint8_t hateSlot = it->second;
      m_freeHateSlotQueue.push( hateSlot );
      m_actorIdTohateSlotMap.erase( it );
      Service< World::Manager::PlayerMgr >::ref().onHateListChanged( *this );

      return;
    }
  }
}

bool Player::hateListHasEntry( const BNpc& bnpc )
{
  return std::any_of( m_actorIdTohateSlotMap.begin(), m_actorIdTohateSlotMap.end(),
                     [ bnpc ]( const auto& entry ) { return entry.first == bnpc.getId(); } );
}

const std::map< uint32_t, uint8_t >& Player::getActorIdToHateSlotMap()
{
  return m_actorIdTohateSlotMap;
}

void Player::onMobAggro( const BNpc& bnpc )
{
  hateListAdd( bnpc );
  server().queueForPlayer( getCharacterId(), makeActorControl( getId(), SetBattle, 1, 0, 0 ) );
}

void Player::onMobDeaggro( const BNpc& bnpc )
{
  hateListRemove( bnpc );
  if( m_actorIdTohateSlotMap.empty() )
    server().queueForPlayer( getCharacterId(), makeActorControl( getId(), SetBattle, 0, 0, 0 ) );
}

bool Player::isLogin() const
{
  return m_bIsLogin;
}

void Player::setIsLogin( bool bIsLogin )
{
  m_bIsLogin = bIsLogin;
}

Player::TitleList& Player::getTitleList()
{
  return m_titleList;
}

uint16_t Player::getTitle() const
{
  return m_activeTitle;
}

void Player::addTitle( uint16_t titleId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( titleId, value, index );

  m_titleList[ index ] |= value;
}

void Player::setTitle( uint16_t titleId )
{
  uint16_t index;
  uint8_t value;
  Util::valueToFlagByteIndexValue( titleId, value, index );

  if( ( m_titleList[ index ] & value ) == 0 )   // Player doesn't have title - bail
    return;

  m_activeTitle = titleId;
  server().queueForPlayers( getInRangePlayerIds( true ), makeActorControl( getId(), SetTitle, titleId ) );
}

const Player::AchievementData& Player::getAchievementData() const
{
  return m_achievementData;
}

void Player::setAchievementData( const Player::AchievementData& achievementData )
{
  m_achievementData = achievementData;
}

void Player::setMaxGearSets( uint8_t amount )
{
  m_equippedMannequin = amount;

  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), SetMaxGearSets, m_equippedMannequin ) );
}

void Player::addGearSet()
{
  uint8_t amount = 1;

  if( getMaxGearSets() == 0 )
  {
    // unlock 5 gearsets the first time
    amount = 5;
    setRewardFlag( UnlockEntry::GearSets );
  }

  setMaxGearSets( getMaxGearSets() + amount );
}

uint8_t Player::getMaxGearSets() const
{
  return m_equippedMannequin;
}

void Player::setEquipDisplayFlags( uint16_t state )
{
  m_equipDisplayFlags = static_cast< uint8_t >( state );
}

uint8_t Player::getEquipDisplayFlags() const
{
  return m_equipDisplayFlags;
}

void Player::setMount( uint32_t mountId )
{
  m_mount = mountId;
}

void Player::setCompanion( uint8_t id )
{
  m_companionId = id;
}

uint8_t Player::getCurrentCompanion() const
{
  return m_companionId;
}

uint8_t Player::getCurrentMount() const
{
  return m_mount;
}

void Player::setPersistentEmote( uint32_t emoteId )
{
  m_emoteMode = emoteId;
}

uint32_t Player::getPersistentEmote() const
{
  return m_emoteMode;
}

void Player::autoAttack( CharaPtr pTarget )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto& actionMgr = Common::Service< World::Manager::ActionMgr >::ref();
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  auto mainWeap = getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );

  pTarget->onActionHostile( getAsChara() );

  auto& RNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
  auto variation = static_cast< uint32_t >( RNGMgr.getRandGenerator< float >( 0, 3 ).next() );

  //actionMgr.handleTargetedPlayerAction( *this, 7, exdData.getRow< Excel::Action >( 7 ), pTarget->getId(), 0 );

  auto damage = Math::CalcStats::calcAutoAttackDamage( *this );

  auto effectPacket = std::make_shared< EffectPacket1 >( getId(), pTarget->getId(), 7 );

  Common::CalcResultParam entry{};

  entry.Value = static_cast< int16_t >( damage.first );
  entry.Type = Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
  entry.Arg0 = 2;
  entry.Arg1 = 7;

  if( getClass() == ClassJob::Machinist || getClass() == ClassJob::Bard || getClass() == ClassJob::Archer )
    effectPacket->setActionId( 8 );

  auto resultId = pZone->getNextEffectResultId();
  effectPacket->setResultId( resultId );
  effectPacket->setRotation( Util::floatToUInt16Rot( getRot() ) );
  effectPacket->addTargetEffect( entry );

  server().queueForPlayers( getInRangePlayerIds( true ), effectPacket );

  pTarget->takeDamage( static_cast< uint32_t >( damage.first ) );

  auto& taskMgr = Common::Service< TaskMgr >::ref();
  taskMgr.queueTask( Sapphire::World::makeActionIntegrityTask( resultId, pTarget, 500 ) );
}


/////////////////////////////
// Content Finder
/////////////////////////////
uint32_t Player::getCFPenaltyTimestamp() const
{
  return m_cfPenaltyUntil;
}

void Player::setCFPenaltyTimestamp( uint32_t timestamp )
{
  m_cfPenaltyUntil = timestamp;
}

uint32_t Player::getCFPenaltyMinutes() const
{
  auto currentTimestamp = Common::Util::getTimeSeconds();
  auto endTimestamp = getCFPenaltyTimestamp();

  // check if penalty timestamp already passed current time
  if( currentTimestamp > endTimestamp )
    return 0;

  auto deltaTime = endTimestamp - currentTimestamp;
  return static_cast< uint32_t > ( std::ceil( static_cast< float > ( deltaTime ) / 60 ) );
}

void Player::setCFPenaltyMinutes( uint32_t minutes )
{
  auto currentTimestamp = Common::Util::getTimeSeconds();
  setCFPenaltyTimestamp( currentTimestamp + minutes * 60 );
}

uint8_t Player::getOpeningSequence() const
{
  return m_openingSequence;
}

void Player::setOpeningSequence( uint8_t seq )
{
  m_openingSequence = seq;
}

uint16_t Player::getItemLevel() const
{
  return m_itemLevel;
}

/// Tells client to offset their eorzean time by given timestamp.
void Player::setEorzeaTimeOffset( uint64_t timestamp )
{
  // TODO: maybe change to persistent?
  auto packet = makeZonePacket< FFXIVIpcEorzeaTimeOffset >( getId() );
  packet->data().timestamp = timestamp;

  // Send to single player
  server().queueForPlayer( getCharacterId(), packet );
}

uint32_t Player::getPrevTerritoryTypeId() const
{
  return m_prevTerritoryTypeId;
}

void Player::setDirectorInitialized( bool isInitialized )
{
  m_directorInitialized = isInitialized;
}

bool Player::isDirectorInitialized() const
{
  return m_directorInitialized;
}

void Player::sendTitleList()
{
  auto titleListPacket = makeZonePacket< FFXIVIpcTitleList >( getId() );
  memcpy( titleListPacket->data().TitleFlagsArray, getTitleList().data(), sizeof( titleListPacket->data().TitleFlagsArray ) );

  server().queueForPlayer( getCharacterId(), titleListPacket );
}

void Player::teleportQuery( uint16_t aetheryteId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  // TODO: only register this action if enough gil is in possession
  auto targetAetheryte = exdData.getRow< Excel::Aetheryte >( aetheryteId );

  if( targetAetheryte )
  {
    auto fromAetheryte = exdData.getRow< Excel::Aetheryte >(
      exdData.getRow< Excel::TerritoryType >( getTerritoryTypeId() )->data().Aetheryte );

    // calculate cost - does not apply for favorite points or homepoints neither checks for aether tickets
    auto cost = static_cast< uint16_t > (
      ( std::sqrt( std::pow( fromAetheryte->data().CostPosX - targetAetheryte->data().CostPosX, 2 ) +
                   std::pow( fromAetheryte->data().CostPosY - targetAetheryte->data().CostPosY, 2 ) ) / 2 ) + 100 );

    // cap at 999 gil
    cost = std::min< uint16_t >( 999, cost );

    bool insufficientGil = getCurrency( Common::CurrencyType::Gil ) < cost;
    server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), OnExecuteTelepo, insufficientGil ? 2 : 0, aetheryteId ) );

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

Sapphire::Common::PlayerTeleportQuery Player::getTeleportQuery() const
{
  return m_teleportQuery;
}

void Player::clearTeleportQuery()
{
  memset( &m_teleportQuery, 0x0, sizeof( Common::PlayerTeleportQuery ) );
}

uint8_t Player::getNextObjSpawnIndexForActorId( uint32_t actorId )
{
  auto index = m_objSpawnIndexAllocator.getNextFreeSpawnIndex( actorId );

  if( index == m_objSpawnIndexAllocator.getAllocFailId() )
  {
    Logger::warn( "Failed to spawn EObj#{0} for Player#{1} - no remaining spawn indexes available. "
                  "Consider lowering InRangeDistance in world config.",
                  actorId, getId() );

    PlayerMgr::sendUrgent( *this, "Failed to spawn EObj#{0} for you - no remaining spawn slots. See world log.", actorId );

    return index;
  }

  return index;
}

void Player::setDyeingInfo( uint32_t itemToDyeContainer, uint32_t itemToDyeSlot, uint32_t dyeBagContainer, uint32_t dyeBagSlot )
{
  m_dyeingInfo.itemToDyeContainer = itemToDyeContainer;
  m_dyeingInfo.itemToDyeSlot = itemToDyeSlot;
  m_dyeingInfo.dyeBagContainer = dyeBagContainer;
  m_dyeingInfo.dyeBagSlot = dyeBagSlot;
}

void Player::dyeItemFromDyeingInfo()
{
  uint32_t itemToDyeContainer = m_dyeingInfo.itemToDyeContainer;
  uint32_t itemToDyeSlot = m_dyeingInfo.itemToDyeSlot;
  uint32_t dyeBagContainer = m_dyeingInfo.dyeBagContainer;
  uint32_t dyeBagSlot = m_dyeingInfo.dyeBagSlot;

  Service< World::Manager::PlayerMgr >::ref().onConditionChanged( *this, true ); // Retail sends all 0s to unlock player after a dye? Possibly not setting a flag when the action is started in the backend..?

  auto itemToDye = getItemAt( itemToDyeContainer, itemToDyeSlot );
  auto dyeToUse = getItemAt( dyeBagContainer, dyeBagSlot );

  if( !itemToDye || !dyeToUse )
    return;

  if( !removeItem( dyeToUse->getId() ) )
    return;

  uint32_t stainColorID = dyeToUse->getAdditionalData();
  bool shouldDye = stainColorID != 0;
  bool invalidateGearSet = stainColorID != itemToDye->getStain();
  itemToDye->setStain( stainColorID );

  insertInventoryItem( static_cast< Sapphire::Common::InventoryType >( itemToDyeContainer ), static_cast< uint16_t >( itemToDyeSlot ), itemToDye );
  writeItem( itemToDye );

  auto dyePkt = makeActorControlSelf( getId(), DyeMsg, itemToDye->getId(), shouldDye, invalidateGearSet );
  server().queueForPlayer( getCharacterId(), dyePkt );
}

void Player::setGlamouringInfo( uint32_t itemToGlamourContainer, uint32_t itemToGlamourSlot, uint32_t glamourBagContainer, uint32_t glamourBagSlot, bool shouldGlamour )
{
  m_glamouringInfo.itemToGlamourContainer = itemToGlamourContainer;
  m_glamouringInfo.itemToGlamourSlot = itemToGlamourSlot;
  m_glamouringInfo.glamourBagContainer = glamourBagContainer;
  m_glamouringInfo.glamourBagSlot = glamourBagSlot;
  m_glamouringInfo.shouldGlamour = shouldGlamour;
}

void Player::glamourItemFromGlamouringInfo()
{
  auto& playerMgr = Service< World::Manager::PlayerMgr >::ref();

  uint32_t itemToGlamourContainer = m_glamouringInfo.itemToGlamourContainer;
  uint32_t itemToGlamourSlot = m_glamouringInfo.itemToGlamourSlot;
  uint32_t glamourBagContainer = m_glamouringInfo.glamourBagContainer;
  uint32_t glamourBagSlot = m_glamouringInfo.glamourBagSlot;
  bool shouldGlamour = m_glamouringInfo.shouldGlamour;

  playerMgr.onConditionChanged( *this, true );

  auto itemToGlamour = getItemAt( itemToGlamourContainer, itemToGlamourSlot );
  auto glamourToUse = getItemAt( glamourBagContainer, glamourBagSlot );
  //auto prismToUse = getItemAt( glamourBagContainer, glamourBagSlot );

  if( !itemToGlamour )
    return;

  //if( !removeItem( prismToUse->getId() ) )
  //  return;

  uint32_t patternID = itemToGlamour->getPattern();
  bool invalidateGearSet = shouldGlamour ? patternID != glamourToUse->getId() : true;

  if( shouldGlamour )
  {
    itemToGlamour->setPattern( glamourToUse->getId() );
    itemToGlamour->setStain( glamourToUse->getStain() );
  }
  else
  {
    itemToGlamour->setPattern( 0 );
    itemToGlamour->setStain( 0 );
  }

  itemToGlamour->setGlamModelIds();

  insertInventoryItem( static_cast< Sapphire::Common::InventoryType >( itemToGlamourContainer ), static_cast< uint16_t >( itemToGlamourSlot ), itemToGlamour );
  writeItem( itemToGlamour );

  if( shouldGlamour )
  {
    auto castGlamPkt = makeActorControlSelf( getId(), GlamourCastMsg, itemToGlamour->getId(), glamourToUse->getId(), invalidateGearSet );
    server().queueForPlayer( getCharacterId(), castGlamPkt );
  }
  else
  {
    auto dispelGlamPkt = makeActorControlSelf( getId(), GlamourRemoveMsg, itemToGlamour->getId(), invalidateGearSet );
    server().queueForPlayer( getCharacterId(), dispelGlamPkt );
  }
}

void Player::resetObjSpawnIndex()
{
  m_objSpawnIndexAllocator.freeAllSpawnIndexes();
}

void Player::freeObjSpawnIndexForActorId( uint32_t actorId )
{
  auto spawnId = m_objSpawnIndexAllocator.freeUsedSpawnIndex( actorId );

  // obj was never spawned for this player
  if( spawnId == m_objSpawnIndexAllocator.getAllocFailId() )
    return;

  auto freeObjectSpawnPacket = makeZonePacket< FFXIVIpcDeleteObject >( getId() );
  freeObjectSpawnPacket->data().Index = spawnId;
  server().queueForPlayer( getCharacterId(), freeObjectSpawnPacket );
}

bool Player::isObjSpawnIndexValid( uint8_t index )
{
  return m_objSpawnIndexAllocator.isSpawnIndexValid( index );
}

void Player::setOnEnterEventDone( bool isDone )
{
  m_onEnterEventDone = isDone;
}

bool Player::isOnEnterEventDone() const
{
  return m_onEnterEventDone;
}

void Player::setLandFlags( uint8_t flagSlot, uint32_t landFlags, Common::LandIdent ident )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  m_charaLandData[ flagSlot ].landId = ident;
  m_charaLandData[ flagSlot ].landId.worldId = static_cast< int16_t >( server.getWorldId() );
  m_charaLandData[ flagSlot ].landFlags = landFlags;
}

Sapphire::Common::HuntingLogEntry& Player::getHuntingLogEntry( uint8_t index )
{
  assert( index < m_huntingLogEntries.size() );
  return m_huntingLogEntries[ index ];
}

void Player::sendHuntingLog()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint8_t count = 0;
  for( const auto& entry : m_huntingLogEntries )
  {
    uint64_t completionFlag = 0;
    auto huntPacket = makeZonePacket< FFXIVIpcMonsterNoteCategory >( getId() );

    huntPacket->data().contextId = -1;
    huntPacket->data().currentRank = entry.rank;
    huntPacket->data().categoryIndex = count;

    for( int i = 1; i <= 10; ++i )
    {
      auto index0 = i - 1;
      bool allComplete = true;
      auto monsterNoteId = ( count + 1 ) * 10000 + entry.rank * 10 + i;

      auto monsterNote = exdData.getRow< Excel::MonsterNote >( monsterNoteId );
      if( !monsterNote )
        continue;

      const auto huntEntry = entry.entries[ index0 ];
      for( int x = 0; x < 3; ++x )
      {
        if( ( huntEntry[ x ] == monsterNote->data().NeededKills[ x ] ) && monsterNote->data().NeededKills[ x ] != 0 )
          completionFlag |= ( 1ull << ( index0 * 5 + x ) );
        else if( monsterNote->data().NeededKills[ x ] != 0 )
          allComplete = false;
      }

      if( allComplete )
        completionFlag |= ( 1ull << ( index0 * 5 + 4 ) );

    }

    memcpy( huntPacket->data().killCount, entry.entries, sizeof( entry.entries ) );
    huntPacket->data().completeFlags = completionFlag;
    ++count;
    server().queueForPlayer( getCharacterId(), huntPacket );
  }
}

void Player::updateHuntingLog( uint16_t id )
{
  std::vector< uint32_t > rankRewards{ 2500, 10000, 20000, 30000, 40000 };
  const auto maxRank = 4;
  auto& pExdData = Common::Service< Data::ExdData >::ref();

  // make sure we get the matching base-class if a job is being used
  auto classJobInfo = pExdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( getClass() ) );
  if( !classJobInfo )
    return;

  auto currentClassId = classJobInfo->data().MainClass;

  auto& logEntry = m_huntingLogEntries[ currentClassId - 1 ];

  bool logChanged = false;


  bool allSectionsComplete = true;
  for( int i = 1; i <= 10; ++i )
  {
    bool sectionComplete = true;
    bool sectionChanged = false;
    auto monsterNoteId = static_cast< uint32_t >( classJobInfo->data().MainClass * 10000 + logEntry.rank * 10 + i );
    auto note = pExdData.getRow< Excel::MonsterNote >( monsterNoteId );

    // for classes that don't have entries, if the first fails the rest will fail
    if( !note )
      break;

    for( auto x = 0; x < 4; ++x )
    {
      auto note1 = pExdData.getRow< Excel::MonsterNoteTarget >( note->data().Target[ x ] );
      if( note1->data().Monster == id && logEntry.entries[ i - 1 ][ x ] < note->data().NeededKills[ x ] )
      {
        logEntry.entries[ i - 1 ][ x ]++;
        server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), HuntingLogEntryUpdate, monsterNoteId, x, logEntry.entries[ i - 1 ][ x ] ) );
        logChanged = true;
        sectionChanged = true;
      }
      if( logEntry.entries[ i - 1 ][ x ] != note->data().NeededKills[ x ] )
        sectionComplete = false;
    }
    if( logChanged && sectionComplete && sectionChanged )
    {
      server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), HuntingLogSectionFinish, monsterNoteId, i, 0 ) );
      gainExp( note->data().RewardExp );
    }
    if( !sectionComplete )
    {
      allSectionsComplete = false;
    }
  }
  if( logChanged && allSectionsComplete )
  {
    server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), HuntingLogRankFinish, 4, 0, 0 ) );
    gainExp( rankRewards[ logEntry.rank ] );
    if( logEntry.rank < 4 )
    {
      logEntry.rank++;
      memset( logEntry.entries, 0, 40 );
      server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), HuntingLogRankUnlock, currentClassId, logEntry.rank + 1, 0 ) );
    }
  }

  if( logChanged )
    sendHuntingLog();
}

void Player::setActiveLand( uint8_t land, uint8_t ward )
{
  m_activeLand.plot = land;
  m_activeLand.ward = ward;
}

Sapphire::Common::ActiveLand Player::getActiveLand() const
{
  return m_activeLand;
}

bool Player::hasQueuedAction() const
{
  return m_pQueuedAction != nullptr;
}

void Player::setQueuedAction( Sapphire::World::Action::ActionPtr pAction )
{
  m_pQueuedAction = std::move( pAction ); // overwrite previous queued action if any
}

void Player::setLastActionTick( uint64_t tick )
{
  m_lastActionTick = tick;
}

uint64_t Player::getLastActionTick() const
{
  return m_lastActionTick;
}

void Player::setRecastGroup( uint8_t index, float time )
{
  m_recast[ index ] = time;
  if( time > m_recastMax[ index ] )
    m_recastMax[ index ] = time;
}

float Player::getRecastGroup( uint8_t index ) const
{
  return m_recast[ index ];
}

void Player::sendRecastGroups()
{
  auto recastGroupPaket = makeZonePacket< FFXIVIpcRecastGroup >( getId() );
  memcpy( &recastGroupPaket->data().Recast, &m_recast, sizeof( m_recast ) );
  memcpy( &recastGroupPaket->data().RecastMax, &m_recastMax, sizeof( m_recastMax ) );
  server().queueForPlayer( getCharacterId(), recastGroupPaket );
}

void Player::resetRecastGroups()
{
  for( size_t i = 0; i < 80; ++i )
  {
    m_recast[ i ] = 0.0f;
    m_recastMax[ i ] = 0.0f;
  }
  sendRecastGroups();
}

bool Player::checkAction()
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
      PlayerMgr::sendDebug( *this, "Queued skill start: {0}", m_pQueuedAction->getId() );
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

uint64_t Player::getPartyId() const
{
  return m_partyId;
}

void Player::setPartyId( uint64_t partyId )
{
  m_partyId = partyId;
}

Player::FriendListIDVec& Player::getFriendListId()
{
  return m_friendList;
}

Player::FriendListDataVec& Player::getFriendListData()
{
  return m_friendInviteList;
}

Player::FriendListIDVec& Player::getBlacklistId()
{
  return m_blacklist;
}

void Player::setFalling( bool state, const Common::FFXIVARR_POSITION3& pos, bool ignoreDamage )
{
  bool isFalling = m_falling;
  auto initialPos = m_initialFallPos;

  // update internal values - only use scoped values for old state
  m_falling = state;
  m_initialFallPos = pos;

  if( ignoreDamage )
    return;

  // if the player is currently falling and new state is grounded - calc and apply fall dmg
  if( isFalling && !state )
  {
    // calc height difference
    auto fallHeight = initialPos.y - pos.y;

    // if we've hit the breakpoint in fall damage (min: 10y)
    if( fallHeight >= 10.f )
    {
      // calculate how much damage to deal out (max. 30y : 100%)
      float deltaMax = std::min( fallHeight, 30.f );

      // get hp percentage starting from 0.1, increasing to 100% at max height
      float hpPer = std::min( 0.1f + ( deltaMax - 10.f ) / 20.f, 1.f );

      auto damage = static_cast< uint32_t >( getMaxHp() * hpPer );

      // check if player has aggro - if not, player should "live"
      if( m_actorIdTohateSlotMap.empty() )
      {
        // "trick" client into thinking we took more damage than internally passed to takeDamage, if > playerHp
        uint32_t surviveDamage = damage;

        if( surviveDamage >= getHp() )
        {
          surviveDamage = ( getHp() - 1 );
        }

        takeDamage( surviveDamage );
      }
      else
      {
        // no mercy on hated players
        takeDamage( damage );
      }

      server().queueForPlayers( getInRangePlayerIds( true ), makeActorControl( getId(), SetFallDamage, damage ) );
    }
  }
}

bool Player::isFalling() const
{
  return m_falling;
}

void Player::setLastPcSearchResult( std::vector< uint32_t > result )
{
  m_lastPcSearch = std::move( result );
}

std::vector< uint32_t >& Player::getLastPcSearchResult()
{
  return m_lastPcSearch;
}

const FFXIVARR_POSITION3& Player::getPrevPos() const
{
  return m_prevPos;
}

float Player::getPrevRot() const
{
  return m_prevRot;
}

bool Player::isConnected() const
{
  return m_bIsConnected;
}

void Player::setConnected( bool isConnected )
{
  m_bIsConnected = isConnected;
}

void Player::updatePrevTerritory()
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();

  if( teriMgr.isDefaultTerritory( getTerritoryTypeId() ) || teriMgr.isHousingTerritory( getTerritoryTypeId() ) )
  {
    m_prevTerritoryTypeId = getTerritoryTypeId();
    m_prevTerritoryId = getTerritoryId();
    m_prevPos = m_pos;
    m_prevRot = m_rot;
  }
}

const CharaLandData& Entity::Player::getCharaLandData( Common::LandFlagsSlot slot ) const
{
  return m_charaLandData[ slot ];
}
