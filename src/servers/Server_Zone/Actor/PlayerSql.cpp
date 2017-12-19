#include <Server_Common/Common.h>
#include <Server_Common/Network/GamePacket.h>
#include <Server_Common/Util/Util.h>
#include <Server_Common/Util/UtilMath.h>
#include <Server_Common/Config/XMLConfig.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Network/PacketContainer.h>
#include <Server_Common/Common.h>
#include <Server_Common/Database/DatabaseDef.h>

#include <set>
#include <stdio.h>

#include <time.h>

#include "Player.h"

#include "Zone/ZoneMgr.h"
#include "Zone/Zone.h"

#include "ServerZone.h"

#include "Forwards.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Inventory/Inventory.h"


extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;


using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

// load player from the db
bool Core::Entity::Player::load( uint32_t charId, SessionPtr pSession )
{
   const std::string char_id_str = std::to_string( charId );

   auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_SEL );

   stmt->setUInt( 1, charId );
   auto res = g_charaDb.query( stmt );
   
   if( !res->next() )
      return false;

   m_id = charId;

   auto name = res->getString( "Name" );
   strcpy( m_name, name.c_str() );

   auto zoneId = res->getUInt( "TerritoryId" );

   ZonePtr pCurrZone = g_zoneMgr.getZone( zoneId );
   m_zoneId = zoneId;

   // TODO: logic for instances needs to be added here
   // see if a valid zone could be found for the character
   if( !pCurrZone )
   {
      g_log.error( "[" + char_id_str + "] Zone " + std::to_string( zoneId ) + " not found!" );
      g_log.error( "[" + char_id_str + "] Setting default zone instead" );

      // default to new gridania
      // TODO: should probably just abort and mark character as corrupt
      pCurrZone = g_zoneMgr.getZone( 132 );

      m_pos.x = 0.0f;
      m_pos.y = 0.0f;
      m_pos.z = 0.0f;
      setRotation( 0.0f );
   }

   // Stats

   m_hp = res->getUInt( "Hp" );
   m_mp = res->getUInt( "Mp" );
   m_tp = 0;

   // Position

   m_pos.x = res->getFloat( "PosX" );
   m_pos.y = res->getFloat( "PosY" );
   m_pos.z = res->getFloat( "PosZ" );
   setRotation( res->getFloat( "PosR" ) );

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

   if( !loadActiveQuests() || !loadClassData() || !loadSearchInfo() )
      g_log.error( "Player id " + char_id_str + " data corrupt!" );

   m_maxHp = getMaxHp();
   m_maxMp = getMaxMp();

   m_mount = res->getUInt8( "Mount" );

   m_modelSubWeapon = 0;
   m_lastTickTime = 0;

   auto pPlayer = getAsPlayer();
   // TODO: remove Inventory and actually inline it in Player class
   m_pInventory = InventoryPtr( new Inventory( pPlayer.get() ) );

   pPlayer->calculateStats();

   // first login, run the script event
   if( m_bNewGame )
   {
      //g_scriptMgr.onPlayerFirstEnterWorld( pPlayer );
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

   m_pInventory->load();

   initHateSlotQueue();

   initSpawnIdQueue();

   if( !m_playerIdToSpawnIdMap.empty() )
      m_playerIdToSpawnIdMap.clear();

   return true;
}

bool Core::Entity::Player::loadActiveQuests()
{

   auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_QUEST_SEL );

   stmt->setUInt( 1, m_id );
   auto res = g_charaDb.query( stmt );

   while( res->next() )
   {

      auto slotId = res->getUInt8( 2 );

      boost::shared_ptr< QuestActive > pActiveQuest( new QuestActive() );
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
      m_activeQuests[slotId] = pActiveQuest;

      m_questIdToQuestIdx[pActiveQuest->c.questId] = slotId;
      m_questIdxToQuestId[slotId] = pActiveQuest->c.questId;


   }

   return true;

}

bool Core::Entity::Player::loadClassData()
{

   // ClassIdx, Exp, Lvl
   auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_CLASS_SEL );
   stmt->setUInt( 1, m_id );
   auto res = g_charaDb.query( stmt );

   while( res->next() )
   {
      auto index = res->getUInt16( 1 );
      auto exp = res->getUInt( 2 );
      auto lvl = res->getUInt8( 3 );

      m_classArray[index] = lvl;
      m_expArray[index] = exp;
   }

   return true;
}

bool Core::Entity::Player::loadSearchInfo()
{
   auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_SEARCHINFO_SEL );
   stmt->setUInt( 1, m_id );
   auto res = g_charaDb.query( stmt );

   if( !res->next() )
      return false;

   m_searchSelectClass = res->getUInt8( 1 );
   m_searchSelectRegion = res->getUInt8( 2 );
   sprintf( m_searchMessage, res->getString( 3 ).c_str() );

   return true;
}


void Core::Entity::Player::updateSql()
{

           /*"Hp 1, Mp 2, Tp 3, Gp 4, Mode 5, Mount 6, InvincibleGM 7, Voice 8, "
           "Customize 9, ModelMainWeapon 10, ModelSubWeapon 11, ModelSystemWeapon 12, "
           "ModelEquip 13, EmoteModeType 14, Language 15, IsNewGame 16, IsNewAdventurer 17, "
           "TerritoryType 18, TerritoryId 19, PosX 20, PosY 21, PosZ 22, PosR 23, "
           "OTerritoryType 24, OTerritoryId 25, OPosX 26, OPosY 27, OPosZ 28, OPosR 29, "
           "Class 30, Status 31, TotalPlayTime 32, HomePoint 33, FavoritePoint 34, RestPoint 35, "
           "ActiveTitle 36, TitleList 37, Achievement 38, Aetheryte 39, HowTo 40, Minions 41, Mounts 42, Orchestrion 43, "
           "EquippedMannequin 44, ConfigFlags 45, QuestCompleteFlags 46, OpeningSequence 47, "
           "QuestTracking 48, GrandCompany 49, GrandCompanyRank 50, Discovery 51, GMRank 52, Unlocks 53, "
           "CFPenaltyUntil 54"*/
   auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_UP );

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

   stmt->setInt( 14, 0 ); // EmodeModeType
   stmt->setInt( 15, 0 ); // Language

   stmt->setInt( 16, static_cast< uint32_t >( m_bNewGame ) );
   stmt->setInt( 17, static_cast< uint32_t >( m_bNewAdventurer ) );

   stmt->setInt( 18, 0 ); // TerritoryType
   stmt->setInt( 19, m_zoneId ); // TerritoryId
   stmt->setDouble( 20, m_pos.x );
   stmt->setDouble( 21, m_pos.y );
   stmt->setDouble( 22, m_pos.z );
   stmt->setDouble( 23, getRotation() );

   stmt->setInt( 24, 0 ); // OTerritoryType
   stmt->setInt( 25, 0 ); // OTerritoryId
   stmt->setDouble( 26, 0.0f );
   stmt->setDouble( 27, 0.0f );
   stmt->setDouble( 28, 0.0f );
   stmt->setDouble( 29, 0.0f );

   stmt->setInt( 30, static_cast< uint8_t >( getClass() ) );
   stmt->setInt( 31, static_cast< uint8_t >( getStatus() ) );
   stmt->setInt( 32, m_playTime );
   stmt->setInt( 33, m_homePoint );

   stmt->setBinary( 34, { 0, 0, 0 } ); // FavoritePoint
   stmt->setInt( 35, 0 ); // RestPoint
   stmt->setInt( 36, 0 ); // ActiveTitle

   std::vector< uint8_t > titleListVec( sizeof ( m_titleList ) );
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

   stmt->setBinary( 50, { m_gcRank[0], m_gcRank[1], m_gcRank[2] } );

   std::vector< uint8_t > discoveryVec( sizeof( m_discovery ) );
   memcpy( discoveryVec.data(), m_discovery, sizeof( m_discovery ) );
   stmt->setBinary( 51, discoveryVec );

   stmt->setInt( 52, m_gmRank );

   std::vector< uint8_t > unlockVec( sizeof( m_unlocks ) );
   memcpy( unlockVec.data(), m_unlocks, sizeof( m_unlocks ) );
   stmt->setBinary( 53, unlockVec );

   stmt->setInt( 54, m_cfPenaltyUntil );

   stmt->setInt( 55, m_id );

   g_charaDb.execute( stmt );

   ////// Searchinfo
   updateDbSearchInfo();

   ////// QUESTS
   updateDbAllQuests();

   ////// Class
   updateDbClass();

}

void Core::Entity::Player::updateDbClass() const
{
   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( getClass() )].exp_idx;

   //Exp = ?, Lvl = ? WHERE CharacterId = ? AND ClassIdx = ?
   auto stmtS = g_charaDb.getPreparedStatement( Db::CHARA_CLASS_UP );
   stmtS->setInt( 1, getExp() );
   stmtS->setInt( 2, getLevel() );
   stmtS->setInt( 3, m_id );
   stmtS->setInt( 4, classJobIndex );
   g_charaDb.execute( stmtS );
}

void Core::Entity::Player::updateDbSearchInfo() const
{
   auto stmtS = g_charaDb.getPreparedStatement( Db::CHARA_SEARCHINFO_UP_SELECTCLASS );
   stmtS->setInt( 1, m_searchSelectClass );
   stmtS->setInt( 2, m_id );
   g_charaDb.execute( stmtS );

   auto stmtS1 = g_charaDb.getPreparedStatement( Db::CHARA_SEARCHINFO_UP_SELECTREGION );
   stmtS1->setInt( 1, m_searchSelectRegion );
   stmtS1->setInt( 2, m_id );
   g_charaDb.execute( stmtS1 );

   auto stmtS2 = g_charaDb.getPreparedStatement( Db::CHARA_SEARCHINFO_UP_SELECTREGION );
   stmtS2->setString( 1, string( m_searchMessage != nullptr ? m_searchMessage : "" ) );
   stmtS2->setInt( 2, m_id );
   g_charaDb.execute( stmtS2 );
}

void Core::Entity::Player::updateDbAllQuests() const
{

   for( int32_t i = 0; i < 30; i++ )
   {
      if( !m_activeQuests[i] )
         continue;

      auto stmtS3 = g_charaDb.getPreparedStatement( Db::CHARA_QUEST_UP );
      stmtS3->setInt( 1, m_activeQuests[i]->c.sequence );
      stmtS3->setInt( 2, m_activeQuests[i]->c.flags );
      stmtS3->setInt( 3, m_activeQuests[i]->c.UI8A );
      stmtS3->setInt( 4, m_activeQuests[i]->c.UI8B );
      stmtS3->setInt( 5, m_activeQuests[i]->c.UI8C );
      stmtS3->setInt( 6, m_activeQuests[i]->c.UI8D );
      stmtS3->setInt( 7, m_activeQuests[i]->c.UI8E );
      stmtS3->setInt( 8, m_activeQuests[i]->c.UI8F );
      stmtS3->setInt( 9, m_activeQuests[i]->c.padding1 );
      stmtS3->setInt( 10, m_id);
      stmtS3->setInt( 11, m_activeQuests[i]->c.questId );
      g_charaDb.execute( stmtS3 );

   }
}

void Core::Entity::Player::deleteQuest( uint16_t questId ) const
{
   auto stmt = g_charaDb.getPreparedStatement( Db::CHARA_QUEST_DEL );
   stmt->setInt( 1, m_id );
   stmt->setInt( 2, questId );
   g_charaDb.execute( stmt );
}

void Core::Entity::Player::insertQuest( uint16_t questId, uint8_t index, uint8_t seq ) const
{
   auto stmt = g_charaDb.getPreparedStatement( Db::CHARA_QUEST_INS );
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
   g_charaDb.execute( stmt );
}
