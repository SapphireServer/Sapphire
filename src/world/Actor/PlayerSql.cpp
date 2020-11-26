#include <set>

#include <Common.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Common.h>
#include <Database/DatabaseDef.h>
#include <Service.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/PlayerSetupPacket.h"

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"
#include "Inventory/Item.h"
#include "Inventory/ItemContainer.h"
#include "Manager/ItemMgr.h"

#include "ServerMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;

// load player from the db
bool Sapphire::Entity::Player::load( uint32_t charId, World::SessionPtr pSession )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  m_pSession = pSession;

  const std::string char_id_str = std::to_string( charId );

  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_SEL );

  stmt->setUInt( 1, charId );
  auto res = db.query( stmt );

  if( !res->next() )
    return false;

  m_id = charId;

  auto name = res->getString( "Name" );
  strcpy( m_name, name.c_str() );

  auto zoneId = res->getUInt( "TerritoryType" );
  m_territoryId = res->getUInt( "TerritoryId" );
  m_prevTerritoryTypeId = res->getUInt( "OTerritoryType" );
  m_prevTerritoryId = res->getUInt( "OTerritoryId" );

  // Position
  m_pos.x = res->getFloat( "PosX" );
  m_pos.y = res->getFloat( "PosY" );
  m_pos.z = res->getFloat( "PosZ" );
  setRot( res->getFloat( "PosR" ) );

  m_prevPos.x = res->getFloat( "OPosX" );
  m_prevPos.y = res->getFloat( "OPosY" );
  m_prevPos.z = res->getFloat( "OPosZ" );
  m_prevRot = res->getFloat( "OPosR" );

  TerritoryPtr pCurrZone = nullptr;

  // if the zone is an instanceContent zone, we need to actually find the instance
  if( teriMgr.isInstanceContentTerritory( zoneId ) )
  {
    // try to find an instance actually linked to this player
    pCurrZone = teriMgr.getLinkedInstance( m_id );
    // if none found, revert to previous zone and position
    if( !pCurrZone )
    {
      zoneId = m_prevTerritoryTypeId;
      m_pos.x = m_prevPos.x;
      m_pos.y = m_prevPos.y;
      m_pos.z = m_prevPos.z;
      setRot( m_prevRot );
      pCurrZone = teriMgr.getZoneByTerritoryTypeId( zoneId );
    }
  }
  else if( teriMgr.isInternalEstateTerritory( zoneId ) )
  {
    // todo: this needs to go to the area just outside of the plot door
    pCurrZone = teriMgr.getZoneByLandSetId( m_prevTerritoryId );

    zoneId = m_prevTerritoryTypeId;
    m_pos.x = m_prevPos.x;
    m_pos.y = m_prevPos.y;
    m_pos.z = m_prevPos.z;
    setRot( m_prevRot );
  }
  else if( teriMgr.isHousingTerritory( zoneId ) )
  {
    pCurrZone = teriMgr.getZoneByLandSetId( m_territoryId );
  }
  else
  {
    pCurrZone = teriMgr.getZoneByTerritoryTypeId( zoneId );
  }

  m_territoryTypeId = zoneId;

  // TODO: logic for instances needs to be added here
  // see if a valid zone could be found for the character
  if( !pCurrZone )
  {
    Logger::error( "[{0}] Territory #{1} not found!", char_id_str, zoneId );
    Logger::error( "[{0}] Setting default zone instead", char_id_str );

    // default to new gridania
    // TODO: should probably just abort and mark character as corrupt
    pCurrZone = teriMgr.getZoneByTerritoryTypeId( 132 );

    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    setRot( 0.0f );
  }

  // Model
  auto custom = res->getBlobVector( "Customize" );
  memcpy( reinterpret_cast< char* >( m_customize ), custom.data(), custom.size() );

  m_modelMainWeapon = res->getUInt64( "ModelMainWeapon" );

  auto modelEq = res->getBlobVector( "ModelEquip" );
  memcpy( reinterpret_cast< char* >( m_modelEquip ), modelEq.data(), modelEq.size() );

  // Minimal info

  m_guardianDeity = res->getUInt8( "GuardianDeity" );
  m_birthDay = res->getUInt8( "BirthDay" );
  m_birthMonth = res->getUInt8( "BirthMonth" );
  m_status = static_cast< ActorStatus >( res->getUInt( "Status" ) );
  m_emoteMode = res->getUInt( "EmoteModeType" );

  m_activeTitle = res->getUInt16( "ActiveTitle" );

  m_class = static_cast< ClassJob >( res->getUInt( "Class" ) );
  m_homePoint = res->getUInt8( "Homepoint" );

  // Additional data
  m_contentId = res->getUInt64( "ContentId" );
  m_voice = res->getUInt8( "Voice" );
  m_startTown = res->getUInt8( "StartTown" );
  m_playTime = res->getUInt( "TotalPlayTime" );

  m_bNewGame = res->getBoolean( "IsNewGame" );
  m_bNewAdventurer = res->getBoolean( "IsNewAdventurer" );
  m_openingSequence = res->getUInt8( "OpeningSequence" );

  m_gc = res->getUInt8( "GrandCompany" );
  m_cfPenaltyUntil = res->getUInt( "CFPenaltyUntil" );
  m_activeTitle = res->getUInt16( "ActiveTitle" );

  m_gmRank = res->getUInt8( "GMRank" );

  m_equipDisplayFlags = res->getUInt8( "EquipDisplayFlags" );

  m_pose = res->getUInt8( "Pose" );

  // Blobs

  auto howTo = res->getBlobVector( "HowTo" );
  memcpy( reinterpret_cast< char* >( m_howTo ), howTo.data(), howTo.size() );

  auto questCompleteFlags = res->getBlobVector( "QuestCompleteFlags" );
  memcpy( reinterpret_cast< char* >( m_questCompleteFlags ), questCompleteFlags.data(), questCompleteFlags.size() );

  auto questTracking = res->getBlobVector( "QuestTracking" );
  memcpy( reinterpret_cast< char* >( m_questTracking ), questTracking.data(), questTracking.size() );

  auto aetheryte = res->getBlobVector( "Aetheryte" );
  memcpy( reinterpret_cast< char* >( m_aetheryte ), aetheryte.data(), aetheryte.size() );

  auto unlocks = res->getBlobVector( "Unlocks" );
  memcpy( reinterpret_cast< char* >( m_unlocks ), unlocks.data(), unlocks.size() );

  auto discovery = res->getBlobVector( "Discovery" );
  memcpy( reinterpret_cast< char* >( m_discovery ), discovery.data(), discovery.size() );

  auto titleList = res->getBlobVector( "TitleList" );
  memcpy( reinterpret_cast< char* >( m_titleList ), titleList.data(), titleList.size() );

  auto mountGuide = res->getBlobVector( "Mounts" );
  memcpy( reinterpret_cast< char* >( m_mountGuide ), mountGuide.data(), mountGuide.size() );

  auto orchestrion = res->getBlobVector( "Orchestrion" );
  memcpy( reinterpret_cast< char* >( m_orchestrion ), orchestrion.data(), orchestrion.size() );

  auto gcRank = res->getBlobVector( "GrandCompanyRank" );
  memcpy( reinterpret_cast< char* >( m_gcRank ), gcRank.data(), gcRank.size() );

  res->free();

  m_pCell = nullptr;

  if( !loadActiveQuests() || !loadClassData() || !loadSearchInfo() || !loadHuntingLog() )
    Logger::error( "Player #{0}  data corrupt!", char_id_str );

  initInventory();
  calculateStats();

  // Stats
  m_hp = res->getUInt( "Hp" );
  m_mp = res->getUInt( "Mp" );
  m_tp = 0;
  m_maxHp = getMaxHp();
  m_maxMp = getMaxMp();

  m_mount = res->getUInt8( "Mount" );

  m_modelSubWeapon = 0;
  m_lastTickTime = 0;

  // first login, run the script event
  if( m_bNewGame )
  {
    //g_framework.getScriptMgr().onPlayerFirstEnterWorld( pPlayer );
    m_bNewGame = false;
    m_hp = getMaxHp();
    m_mp = getMaxMp();
  }

  if( m_hp > getMaxHp() )
    m_hp = getMaxHp();

  if( m_mp > getMaxMp() )
    m_mp = getMaxMp();

  if( m_hp == 0 )
    m_status = ActorStatus::Dead;

  //  if( m_bNewAdventurer )
  //     setStateFlag( PlayerStateFlag::NewAdventurer );

  setStateFlag( PlayerStateFlag::BetweenAreas );

  initHateSlotQueue();

  initSpawnIdQueue();

  if( !teriMgr.movePlayer( pCurrZone, getAsPlayer() ) )
    return false;

  return true;
}

bool Sapphire::Entity::Player::loadActiveQuests()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_SEL_QUEST );

  stmt->setUInt( 1, m_id );
  auto res = db.query( stmt );

  while( res->next() )
  {

    auto slotId = res->getUInt8( 2 );

    std::shared_ptr< QuestActive > pActiveQuest( new QuestActive() );
    pActiveQuest->c.questId = res->getUInt16( 3 );
    pActiveQuest->c.sequence = res->getUInt8( 4 );
    pActiveQuest->c.flags = res->getUInt8( 5 );
    pActiveQuest->c.UI8A = res->getUInt8( 6 );
    pActiveQuest->c.UI8B = res->getUInt8( 7 );
    pActiveQuest->c.UI8C = res->getUInt8( 8 );
    pActiveQuest->c.UI8D = res->getUInt8( 9 );
    pActiveQuest->c.UI8E = res->getUInt8( 10 );
    pActiveQuest->c.UI8F = res->getUInt8( 11 );
    pActiveQuest->c.padding1 = res->getUInt8( 12 );
    m_activeQuests[ slotId ] = pActiveQuest;

    m_questIdToQuestIdx[ pActiveQuest->c.questId ] = slotId;
    m_questIdxToQuestId[ slotId ] = pActiveQuest->c.questId;


  }

  return true;

}

bool Sapphire::Entity::Player::loadClassData()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  // ClassIdx, Exp, Lvl
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_CLASS_SEL );
  stmt->setUInt( 1, m_id );
  auto res = db.query( stmt );

  while( res->next() )
  {
    auto index = res->getUInt16( 1 );
    auto exp = res->getUInt( 2 );
    auto lvl = res->getUInt8( 3 );

    m_classArray[ index ] = lvl;
    m_expArray[ index ] = exp;
  }

  return true;
}

bool Sapphire::Entity::Player::loadSearchInfo()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_SEL_SEARCHINFO );
  stmt->setUInt( 1, m_id );
  auto res = db.query( stmt );

  if( !res->next() )
  {
    Logger::error( "Failed to load search info for character#{}", m_id );
    return false;
  }

  m_searchSelectClass = res->getUInt8( 2 );
  m_searchSelectRegion = res->getUInt8( 3 );

  // todo: internally use an std::string instead of a char[]
  auto searchMessage = res->getString( 4 );
  memset( m_searchMessage, 0, sizeof( m_searchMessage ) );
  std::copy( searchMessage.begin(), searchMessage.end(), m_searchMessage );

  return true;
}


bool Sapphire::Entity::Player::loadHuntingLog()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_MONSTERNOTE_SEL );
  stmt->setUInt( 1, m_id );
  auto res = db.query( stmt );

  if( !res->next() )
  {
    Logger::error( "Failed to load hunting log data for character#{}", m_id );
    return false;
  }

  for( auto i = 0; i < 12; ++i )
  {
    std::string catStr = fmt::format( "Category_{}", i );
    auto cat = res->getBlobVector( catStr );
    m_huntingLogEntries[i].rank = cat[0];
    memcpy( reinterpret_cast< char* >( m_huntingLogEntries[i].entries ), cat.data() + 1, cat.size() - 1 );
  }
  return true;
}

void Sapphire::Entity::Player::updateSql()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  /*"Hp 1, Mp 2, Tp 3, Gp 4, Mode 5, Mount 6, InvincibleGM 7, Voice 8, "
  "Customize 9, ModelMainWeapon 10, ModelSubWeapon 11, ModelSystemWeapon 12, "
  "ModelEquip 13, EmoteModeType 14, Language 15, IsNewGame 16, IsNewAdventurer 17, "
  "TerritoryType 18, TerritoryId 19, PosX 20, PosY 21, PosZ 22, PosR 23, "
  "OTerritoryType 24, OTerritoryId 25, OPosX 26, OPosY 27, OPosZ 28, OPosR 29, "
  "Class 30, Status 31, TotalPlayTime 32, HomePoint 33, FavoritePoint 34, RestPoint 35, "
  "ActiveTitle 36, TitleList 37, Achievement 38, Aetheryte 39, HowTo 40, Minions 41, Mounts 42, Orchestrion 43, "
  "EquippedMannequin 44, ConfigFlags 45, QuestCompleteFlags 46, OpeningSequence 47, "
  "QuestTracking 48, GrandCompany 49, GrandCompanyRank 50, Discovery 51, GMRank 52, Unlocks 53, "
  "CFPenaltyUntil 54, Pose 55"*/



  auto stmt = db.getPreparedStatement( Db::ZoneDbStatements::CHARA_UP );

  stmt->setInt( 1, getHp() );
  stmt->setInt( 2, getMp() );
  stmt->setInt( 3, 0 ); // TP
  stmt->setInt( 4, 0 ); // GP
  stmt->setInt( 5, 0 ); // Mode
  stmt->setInt( 6, m_mount ); // Mount
  stmt->setInt( 7, 0 ); // InvicibleGM
  stmt->setInt( 8, m_voice );

  std::vector< uint8_t > customVec( sizeof( m_customize ) );
  memcpy( customVec.data(), m_customize, sizeof( m_customize ) );
  stmt->setBinary( 9, customVec );

  stmt->setInt64( 10, m_modelMainWeapon );
  stmt->setInt64( 11, m_modelSubWeapon );
  stmt->setInt64( 12, m_modelSystemWeapon );

  std::vector< uint8_t > modelVec( sizeof( m_modelEquip ) );
  memcpy( modelVec.data(), m_modelEquip, sizeof( m_modelEquip ) );
  stmt->setBinary( 13, modelVec );

  stmt->setInt( 14, m_emoteMode ); // EmodeModeType
  stmt->setInt( 15, 0 ); // Language

  stmt->setInt( 16, static_cast< uint32_t >( m_bNewGame ) );
  stmt->setInt( 17, static_cast< uint32_t >( m_bNewAdventurer ) );

  stmt->setInt( 18, m_territoryTypeId ); // TerritoryType
  stmt->setInt( 19, m_territoryId ); // TerritoryId
  stmt->setDouble( 20, m_pos.x );
  stmt->setDouble( 21, m_pos.y );
  stmt->setDouble( 22, m_pos.z );
  stmt->setDouble( 23, getRot() );

  stmt->setInt( 24, m_prevTerritoryTypeId ); // OTerritoryType
  stmt->setInt( 25, m_prevTerritoryId ); // OTerritoryId
  stmt->setDouble( 26, m_prevPos.x );
  stmt->setDouble( 27, m_prevPos.y );
  stmt->setDouble( 28, m_prevPos.z );
  stmt->setDouble( 29, m_prevRot );

  stmt->setInt( 30, static_cast< uint8_t >( getClass() ) );
  stmt->setInt( 31, static_cast< uint8_t >( getStatus() ) );
  stmt->setInt( 32, m_playTime );
  stmt->setInt( 33, m_homePoint );

  stmt->setBinary( 34, { 0, 0, 0 } ); // FavoritePoint
  stmt->setInt( 35, 0 ); // RestPoint
  stmt->setInt( 36, m_activeTitle ); // ActiveTitle

  std::vector< uint8_t > titleListVec( sizeof( m_titleList ) );
  stmt->setBinary( 37, titleListVec );

  std::vector< uint8_t > achievementVec( 16 );
  stmt->setBinary( 38, achievementVec );

  std::vector< uint8_t > aetheryteVec( sizeof( m_aetheryte ) );
  memcpy( aetheryteVec.data(), m_aetheryte, sizeof( m_aetheryte ) );
  stmt->setBinary( 39, aetheryteVec );

  std::vector< uint8_t > howToVec( sizeof( m_howTo ) );
  memcpy( howToVec.data(), m_howTo, sizeof( m_howTo ) );
  stmt->setBinary( 40, howToVec );

  std::vector< uint8_t > minionsVec( sizeof( m_minions ) );
  memcpy( minionsVec.data(), m_minions, sizeof( m_minions ) );
  stmt->setBinary( 41, minionsVec );

  std::vector< uint8_t > mountsVec( sizeof( m_mountGuide ) );
  memcpy( mountsVec.data(), m_mountGuide, sizeof( m_mountGuide ) );
  stmt->setBinary( 42, mountsVec );

  std::vector< uint8_t > orchestrionVec( sizeof( m_orchestrion ) );
  memcpy( orchestrionVec.data(), m_orchestrion, sizeof( m_orchestrion ) );
  stmt->setBinary( 42, mountsVec );

  stmt->setInt( 44, 0 ); // EquippedMannequin

  stmt->setInt( 45, 0 ); // DisplayFlags
  std::vector< uint8_t > questCompleteVec( sizeof( m_questCompleteFlags ) );
  memcpy( questCompleteVec.data(), m_questCompleteFlags, sizeof( m_questCompleteFlags ) );
  stmt->setBinary( 46, questCompleteVec );

  stmt->setInt( 47, m_openingSequence );

  std::vector< uint8_t > questTrackerVec( sizeof( m_questTracking ) );
  memcpy( questTrackerVec.data(), m_questTracking, sizeof( m_questTracking ) );
  stmt->setBinary( 48, questTrackerVec );

  stmt->setInt( 49, m_gc ); // DisplayFlags

  stmt->setBinary( 50, { m_gcRank[ 0 ], m_gcRank[ 1 ], m_gcRank[ 2 ] } );

  std::vector< uint8_t > discoveryVec( sizeof( m_discovery ) );
  memcpy( discoveryVec.data(), m_discovery, sizeof( m_discovery ) );
  stmt->setBinary( 51, discoveryVec );

  stmt->setInt( 52, m_gmRank );

  stmt->setInt( 53, m_equipDisplayFlags );

  std::vector< uint8_t > unlockVec( sizeof( m_unlocks ) );
  memcpy( unlockVec.data(), m_unlocks, sizeof( m_unlocks ) );
  stmt->setBinary( 54, unlockVec );

  stmt->setInt( 55, m_cfPenaltyUntil );

  stmt->setInt( 56, m_pose );

  stmt->setInt( 57, m_id );

  db.execute( stmt );

  ////// Searchinfo
  updateDbSearchInfo();

  ////// QUESTS
  updateDbAllQuests();

  ////// Class
  updateDbClass();

  ////// MonterNote
  updateDbMonsterNote();

}

void Sapphire::Entity::Player::updateDbClass() const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  uint8_t classJobIndex = exdData.get< Sapphire::Data::ClassJob >( static_cast<uint8_t>( getClass() ) )->expArrayIndex;

  //Exp = ?, Lvl = ? WHERE CharacterId = ? AND ClassIdx = ?
  auto stmtS = db.getPreparedStatement( Db::CHARA_CLASS_UP );
  stmtS->setInt( 1, getExp() );
  stmtS->setInt( 2, getLevel() );
  stmtS->setInt( 3, m_id );
  stmtS->setInt( 4, classJobIndex );
  db.execute( stmtS );
}

void Sapphire::Entity::Player::updateDbMonsterNote()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  // Category_0-11
  auto stmt = db.getPreparedStatement( Db::CHARA_MONSTERNOTE_UP );
  //std::array< std::vector< uint8_t >, 12 > vectors;
  std::vector< uint8_t > vector( 41 );
  for( std::size_t i = 0; i < m_huntingLogEntries.size(); ++i )
  {
    vector[ 0 ] = m_huntingLogEntries[ i ].rank;

    memcpy( &vector[ 1 ],
            reinterpret_cast< uint8_t* >( m_huntingLogEntries[ i ].entries ),
            40 );
    stmt->setBinary( i + 1, vector );
  }
  stmt->setInt( 13, m_id );
  db.execute( stmt );
}

void Sapphire::Entity::Player::insertDbClass( const uint8_t classJobIndex ) const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmtClass = db.getPreparedStatement( Db::CHARA_CLASS_INS );
  stmtClass->setInt( 1, getId() );
  stmtClass->setInt( 2, classJobIndex );
  stmtClass->setInt( 3, 0 );
  stmtClass->setInt( 4, 1 );
  db.directExecute( stmtClass );
}

void Sapphire::Entity::Player::updateDbSearchInfo() const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmtS = db.getPreparedStatement( Db::CHARA_SEARCHINFO_UP_SELECTCLASS );
  stmtS->setInt( 1, m_searchSelectClass );
  stmtS->setInt( 2, m_id );
  db.execute( stmtS );

  auto stmtS1 = db.getPreparedStatement( Db::CHARA_SEARCHINFO_UP_SELECTREGION );
  stmtS1->setInt( 1, m_searchSelectRegion );
  stmtS1->setInt( 2, m_id );
  db.execute( stmtS1 );

  auto stmtS2 = db.getPreparedStatement( Db::CHARA_SEARCHINFO_UP_SEARCHCOMMENT );
  stmtS2->setString( 1, std::string( m_searchMessage ) );
  stmtS2->setInt( 2, m_id );
  db.execute( stmtS2 );
}

void Sapphire::Entity::Player::updateDbAllQuests() const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  for( int32_t i = 0; i < 30; i++ )
  {
    if( !m_activeQuests[ i ] )
      continue;

    auto stmtS3 = db.getPreparedStatement( Db::CHARA_QUEST_UP );
    stmtS3->setInt( 1, m_activeQuests[ i ]->c.sequence );
    stmtS3->setInt( 2, m_activeQuests[ i ]->c.flags );
    stmtS3->setInt( 3, m_activeQuests[ i ]->c.UI8A );
    stmtS3->setInt( 4, m_activeQuests[ i ]->c.UI8B );
    stmtS3->setInt( 5, m_activeQuests[ i ]->c.UI8C );
    stmtS3->setInt( 6, m_activeQuests[ i ]->c.UI8D );
    stmtS3->setInt( 7, m_activeQuests[ i ]->c.UI8E );
    stmtS3->setInt( 8, m_activeQuests[ i ]->c.UI8F );
    stmtS3->setInt( 9, m_activeQuests[ i ]->c.padding1 );
    stmtS3->setInt( 10, m_id );
    stmtS3->setInt( 11, m_activeQuests[ i ]->c.questId );
    db.execute( stmtS3 );

  }
}

void Sapphire::Entity::Player::deleteQuest( uint16_t questId ) const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::CHARA_QUEST_DEL );
  stmt->setInt( 1, m_id );
  stmt->setInt( 2, questId );
  db.execute( stmt );
}

void Sapphire::Entity::Player::insertQuest( uint16_t questId, uint8_t index, uint8_t seq ) const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::CHARA_QUEST_INS );
  stmt->setInt( 1, m_id );
  stmt->setInt( 2, index );
  stmt->setInt( 3, questId );
  stmt->setInt( 4, seq );
  stmt->setInt( 5, 0 );
  stmt->setInt( 6, 0 );
  stmt->setInt( 7, 0 );
  stmt->setInt( 8, 0 );
  stmt->setInt( 9, 0 );
  stmt->setInt( 10, 0 );
  stmt->setInt( 11, 0 );
  stmt->setInt( 12, 0 );
  db.execute( stmt );
}

Sapphire::ItemPtr Sapphire::Entity::Player::createTempItem( uint32_t catalogId, uint32_t quantity )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto itemInfo = exdData.get< Sapphire::Data::Item >( catalogId );

  if( !itemInfo )
    return nullptr;

  if( !itemInfo )
    return nullptr;

  ItemPtr pItem = make_Item( 0, catalogId );

  pItem->setStackSize( quantity );

  return pItem;
}

void Sapphire::Entity::Player::writeItemDb( Sapphire::ItemPtr pItem ) const
{
  if( pItem->getUId() == 0 )
  {
    auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
    auto& itemMgr = Common::Service< World::Manager::ItemMgr >::ref();

    uint8_t flags = 0;
    pItem->setUId( itemMgr.getNextUId() );
    std::string sql = "INSERT INTO charaglobalitem ( CharacterId, itemId, catalogId, stack, flags ) VALUES ( " +
                      std::to_string( getId() ) + ", " +
                      std::to_string( pItem->getUId() ) + ", " +
                      std::to_string( pItem->getId() ) + ", " +
                      std::to_string( pItem->getStackSize() ) + ", " +
                      std::to_string( flags ) + ");";
    db.directExecute( sql );
  }
}

bool Sapphire::Entity::Player::loadInventory()
{
  auto& itemMgr = Common::Service< World::Manager::ItemMgr >::ref();
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // load active gearset
  auto res = db.query( "SELECT storageId, container_0, container_1, container_2, container_3, "
                         "container_4, container_5, container_6, container_7, "
                         "container_8, container_9, container_10, container_11, "
                         "container_12, container_13 "
                         "FROM charaitemgearset " \
                               "WHERE CharacterId =  " + std::to_string( getId() ) + " " \
                               "ORDER BY storageId ASC;" );

  while( res->next() )
  {
    uint16_t storageId = res->getUInt16( 1 );

    for( uint32_t i = 1; i <= 14; i++ )
    {
      uint64_t uItemId = res->getUInt64( i + 1 );
      if( uItemId == 0 )
        continue;

      ItemPtr pItem = itemMgr.loadItem( uItemId );

      if( pItem == nullptr )
        continue;

      m_storageMap[ storageId ]->getItemMap()[ i - 1 ] = pItem;
      equipItem( static_cast< GearSetSlot >( i - 1 ), pItem, false );
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Load everything
  auto bagRes = db.query( "SELECT storageId, "
                            "container_0, container_1, container_2, container_3, container_4, "
                            "container_5, container_6, container_7, container_8, container_9, "
                            "container_10, container_11, container_12, container_13, container_14, "
                            "container_15, container_16, container_17, container_18, container_19, "
                            "container_20, container_21, container_22, container_23, container_24, "
                            "container_25, container_26, container_27, container_28, container_29, "
                            "container_30, container_31, container_32, container_33, container_34 "
                            "FROM charaiteminventory " \
                                  "WHERE CharacterId =  " + std::to_string( getId() ) + " " \
                                  "ORDER BY storageId ASC;" );

  while( bagRes->next() )
  {
    uint16_t storageId = bagRes->getUInt16( 1 );
    for( uint32_t i = 1; i <= m_storageMap[ storageId ]->getMaxSize(); i++ )
    {
      uint64_t uItemId = bagRes->getUInt64( i + 1 );
      if( uItemId == 0 )
        continue;

      ItemPtr pItem = itemMgr.loadItem( uItemId );

      if( pItem == nullptr )
        continue;

      m_storageMap[ storageId ]->getItemMap()[ i - 1 ] = pItem;
    }
  }

  return true;
}
