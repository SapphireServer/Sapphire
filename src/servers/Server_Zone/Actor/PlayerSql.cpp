#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Network/GamePacket.h>
#include <src/servers/Server_Common/Database/Database.h>
#include <src/servers/Server_Common/Util/Util.h>
#include <src/servers/Server_Common/Util/UtilMath.h>
#include <src/servers/Server_Common/Config/XMLConfig.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>

#include <set>
#include <stdio.h>

#include <time.h>

#include <Server_Common/Database/DbLoader.h>
#include <Server_Common/Database/CharaDbConnection.h>
#include <Server_Common/Database/DbWorkerPool.h>
#include <Server_Common/Database/PreparedStatement.h>

#include "Player.h"

#include "src/servers/Server_Zone/Zone/ZoneMgr.h"
#include "src/servers/Server_Zone/Zone/Zone.h"

#include "src/servers/Server_Zone/ServerZone.h"

#include "src/servers/Server_Zone/Forwards.h"

#include "src/servers/Server_Zone/Network/GameConnection.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/InitUIPacket.h"
#include "src/servers/Server_Zone/StatusEffect/StatusEffectContainer.h"
#include "src/servers/Server_Zone/Inventory/Inventory.h"

#include "src/libraries/sapphire/mysqlConnector/MySqlConnector.h"


extern Core::Logger g_log;
extern Core::Db::Database g_database;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

// load player from the db
bool Core::Entity::Player::load( uint32_t charId, Core::SessionPtr pSession )
{
   const std::string char_id_str = std::to_string( charId );

   boost::scoped_ptr< Core::Db::PreparedStatement > stmt( g_charaDb.getPreparedStatement( Core::Db::CharaDbStatements::CHAR_SEL_LOAD ) );
   stmt->setUInt( 1, charId );

   auto res = dynamic_cast< Mysql::PreparedResultSet* >( g_charaDb.query( stmt.get() ) );
   
   if( !res->next() )
      return false;

   m_id = charId;

   auto name = res->getString( "Name" );
   strcpy( m_name, name.c_str() );

   auto zoneId = res->getUInt( "PrimaryTerritoryId" );

   ZonePtr pCurrZone = g_zoneMgr.getZone( zoneId );
   m_zoneId = zoneId;

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

   m_hp = res->getUInt( "Hp" );
   m_mp = res->getUInt( "Mp" );
   m_tp = 0;

   m_pos.x = res->getFloat( "Pos_0_0" );
   m_pos.y = res->getFloat( "Pos_0_1" );
   m_pos.z = res->getFloat( "Pos_0_2" );
   setRotation( res->getFloat( "Pos_0_3" ) );

   auto custom = res->getBlobVector( "Customize" );
   memcpy( reinterpret_cast< char* >( m_customize ), custom.data(), custom.size() );

   m_modelMainWeapon = res->getUInt64( "ModelMainWeapon" );

   auto modelEq = res->getBlobVector( "ModelEquip" );
   memcpy( reinterpret_cast< char* >( m_modelEquip ), modelEq.data(), modelEq.size() );

   m_guardianDeity = res->getUInt( "GuardianDeity" );
   m_birthDay = res->getUInt( "BirthDay" );
   m_birthMonth = res->getUInt( "BirthMonth" );
   m_status = static_cast< ActorStatus >( res->getUInt( "Status" ) );
   m_class = static_cast< ClassJob >( res->getUInt( "Class" ) );
   m_homePoint = res->getUInt( "Homepoint" );

   auto howTo = res->getBlobVector( "HowTo" );
   memcpy( reinterpret_cast< char* >( m_howTo ), howTo.data(), howTo.size() );

   m_contentId = res->getUInt64( "ContentId" );

   m_voice = res->getUInt( "Voice" );

   auto questCompleteFlags = res->getBlobVector( "QuestCompleteFlags" );
   memcpy( reinterpret_cast< char* >( m_questCompleteFlags ), questCompleteFlags.data(), questCompleteFlags.size() );

   auto questTracking = res->getBlobVector( "QuestTracking" );
   memcpy( reinterpret_cast< char* >( m_questTracking ), questTracking.data(), questTracking.size() );

   m_bNewGame = res->getBoolean( "IsNewGame" );

   auto aetheryte = res->getBlobVector( "Aetheryte" );
   memcpy( reinterpret_cast< char* >( m_aetheryte ), aetheryte.data(), aetheryte.size() );

   auto unlocks = res->getBlobVector( "unlocks" );
   memcpy( reinterpret_cast< char* >( m_unlocks ), unlocks.data(), unlocks.size() );

   auto discovery = res->getBlobVector( "Discovery" );
   memcpy( reinterpret_cast< char* >( m_discovery ), discovery.data(), discovery.size() );

   m_startTown = res->getUInt( "StartTown" );
   m_playTime = res->getUInt( "TotalPlayTime" );

   m_bNewAdventurer = res->getBoolean( "IsNewAdventurer" );

   m_gc = res->getUInt( "GrandCompany" );
   auto gcRank = res->getBlobVector( "GrandCompanyRank" );
   memcpy( reinterpret_cast< char* >( m_gcRank ), gcRank.data(), gcRank.size() );

   m_cfPenaltyUntil = res->getUInt( "CFPenaltyUntil" );

   m_openingSequence = res->getUInt( "OpeningSequence" );

   m_gmRank = res->getUInt( "GMRank" );
   
   //auto pQR = g_database.query( "SELECT "
   //   "c.Name, "
   //   "c.PrimaryTerritoryId, "
   //   "c.Hp, "
   //   "c.Mp, "
   //   "c.Gp, "
   //   "c.Mode, "
   //   "c.Pos_0_0, "
   //   "c.Pos_0_1, "
   //   "c.Pos_0_2, "
   //   "c.Pos_0_3, "
   //   "c.FirstLogin, " // 10
   //   "c.Customize, "
   //   "c.ModelMainWeapon, "
   //   "c.ModelSubWeapon, "
   //   "c.ModelEquip, "
   //   "cd.GuardianDeity, "
   //   "cd.BirthDay, "
   //   "cd.BirthMonth, "
   //   "cd.Status, "
   //   "cd.Class, "
   //   "cd.Homepoint, " // 20
   //   "cd.HowTo, "
   //   "c.ContentId, "
   //   "c.Voice, "
   //   "cd.QuestCompleteFlags, "
   //   "cd.QuestTracking, "
   //   "c.IsNewGame, "
   //   "cd.Aetheryte, "
   //   "cd.unlocks, "
   //   "cd.Discovery, "
   //   "cd.StartTown, " // 30
   //   "cd.TotalPlayTime, "
   //   "c.IsNewAdventurer, "
   //   "cd.GrandCompany, "
   //   "cd.GrandCompanyRank, "
   //   "cd.CFPenaltyUntil, "
   //   "cd.OpeningSequence, "
   //   "cd.GMRank "
   //   "FROM charabase AS c "
   //   " INNER JOIN charadetail AS cd "
   //   " ON c.CharacterId = cd.CharacterId "
   //   "WHERE c.CharacterId = " + char_id_str + ";" );

   //if( !pQR )
   //{
   //   g_log.error( "Player id " + char_id_str + " does not exist!" );
   //   return false;
   //}
   // 

   //Db::Field *field = pQR->fetch();





   m_pCell = nullptr;

   if( !loadActiveQuests() || !loadClassData() || !loadSearchInfo() )
      g_log.error( "Player id " + char_id_str + " data corrupt!" );

   m_maxHp = getMaxHp();
   m_maxMp = getMaxMp();

   m_modelSubWeapon = 0;
   m_lastTickTime = 0;

   auto pPlayer = getAsPlayer();
   m_pInventory = InventoryPtr( new Inventory( pPlayer ) );

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

   m_pStatusEffectContainer = StatusEffect::StatusEffectContainerPtr( new StatusEffect::StatusEffectContainer( shared_from_this() ) );

   if( !m_playerIdToSpawnIdMap.empty() )
      m_playerIdToSpawnIdMap.clear();

   return true;
}


bool Core::Entity::Player::loadClassData()
{
   auto pQR = g_database.query( "SELECT * FROM characlass WHERE CharacterId = " + std::to_string( m_id ) + ";" );

   if( !pQR )
      return false;

   Db::Field* field = pQR->fetch();

   for( uint8_t i = 0; i < 25; i++ )
   {
      uint8_t index = i * 2;
      m_classArray[i] = field[index].get< uint8_t >();
      m_expArray[i] = field[index + 1].get< uint32_t >();
   }

   return true;
}

bool Core::Entity::Player::loadSearchInfo()
{
   auto pQR = g_database.query( "SELECT * FROM charainfosearch WHERE CharacterId = " + std::to_string( m_id ) + ";" );

   if( !pQR )
      return false;

   Db::Field* field = pQR->fetch();

   m_searchSelectClass = field[1].get< uint8_t >();
   m_searchSelectRegion = field[2].get< uint8_t >();
   sprintf( m_searchMessage, field[3].getString().c_str() );

   return true;
}


void Core::Entity::Player::updateSql()
{

   g_log.info( "Updating Player Data to SQL DB " );

   std::set< std::string > charaBaseSet;
   std::set< std::string > charaDetailSet;
   std::set< std::string > charaClassSet;
   std::set< std::string > charaQuestSet;
   std::set< std::string > charaInfoSearchSet;

   std::string dbName = g_serverZone.getConfig()->getValue< std::string >( "Settings.General.Mysql.Database", "sapphire" );
   std::string updateCharaBase = "UPDATE " + dbName + ".charabase SET ";
   std::string updateCharaDetail = "UPDATE " + dbName + ".charadetail SET ";
   std::string updateCharaClass = "UPDATE " + dbName + ".characlass SET ";
   std::string updateCharaQuest = "UPDATE " + dbName + ".charaquest SET ";
   std::string updateCharaInfoSearch = "UPDATE " + dbName + ".charainfosearch SET ";

   std::string condition = " UPDATE_DATE = NOW() WHERE CharacterId = " + std::to_string( m_id ) + ";";

   charaBaseSet.insert( " Pos_0_0 = " + std::to_string( m_pos.x ) );
   charaBaseSet.insert( " Pos_0_1 = " + std::to_string( m_pos.y ) );
   charaBaseSet.insert( " Pos_0_2 = " + std::to_string( m_pos.z ) );
   charaBaseSet.insert( " Pos_0_3 = " + std::to_string( getRotation() ) );
   charaBaseSet.insert( " PrimaryTerritoryId = " + std::to_string( m_zoneId ) );
   charaBaseSet.insert( " IsNewGame = " + std::to_string( static_cast< uint32_t >( m_bNewGame ) ) );
   charaBaseSet.insert( " IsNewAdventurer = " + std::to_string( static_cast< uint32_t >( m_bNewAdventurer ) ) );
   charaBaseSet.insert( " Hp = " + std::to_string( getHp() ) );
   charaBaseSet.insert( " Mp = " + std::to_string( getMp() ) );
   charaBaseSet.insert( " Mode = " + std::to_string( static_cast< uint32_t >( getStance() ) ) );
   charaBaseSet.insert( " ModelEquip = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_modelEquip ), 40 ) ) + "')" );

   charaDetailSet.insert( " Homepoint = " + std::to_string( m_homePoint ) );
   charaDetailSet.insert( " Discovery = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_discovery ), sizeof( m_discovery ) ) ) + "')" );
   charaDetailSet.insert( " TotalPlayTime = " + std::to_string( m_playTime ) );
   charaDetailSet.insert( " unlocks = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_unlocks ), sizeof( m_unlocks ) ) ) + "')" );
   charaDetailSet.insert( " QuestTracking = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_questTracking ), sizeof( m_questTracking ) ) ) + "')" );
   charaDetailSet.insert( " HowTo = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_howTo ), sizeof( m_howTo ) ) ) + "')" );
   charaDetailSet.insert( " Aetheryte = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_aetheryte ), sizeof( m_aetheryte ) ) ) + "')" );
   charaDetailSet.insert( " GrandCompany = " + std::to_string( m_gc ) );
   charaDetailSet.insert( " GrandCompanyRank = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_gcRank ), sizeof( m_gcRank ) ) ) + "')" );
   charaDetailSet.insert( " CFPenaltyUntil = " + std::to_string( m_cfPenaltyUntil ) );
   charaDetailSet.insert( " Class = " + std::to_string( static_cast< uint32_t >( getClass() ) ) );
   charaDetailSet.insert( " Status = " + std::to_string( static_cast< uint8_t >( getStatus() ) ) );
   charaDetailSet.insert( " OpeningSequence = " + std::to_string( static_cast< uint8_t >( getOpeningSequence() ) ) );
   charaDetailSet.insert( " QuestCompleteFlags = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_questCompleteFlags ), 200 ) ) + "')" );

   uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( getClass() )].exp_idx;
   charaClassSet.insert( " Lv_" + std::to_string( classJobIndex ) + " = " + std::to_string( static_cast< uint32_t >( getLevel() ) ) );
   charaClassSet.insert( " Exp_" + std::to_string( classJobIndex ) + " = " + std::to_string( getExp() ) );

   for( int32_t i = 0; i < 30; i++ )
   {
      if( m_activeQuests[i] != nullptr )
      {
         charaQuestSet.insert( " QuestId_" + std::to_string( i ) + " = " + std::to_string( m_activeQuests[i]->c.questId ) );
         charaQuestSet.insert( " Sequence_" + std::to_string( i ) + " = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.sequence ) ) );
         charaQuestSet.insert( " Flags_" + std::to_string( i ) + " = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.flags ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_0 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.UI8A ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_1 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.UI8B ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_2 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.UI8C ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_3 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.UI8D ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_4 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.UI8E ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_5 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.UI8F ) ) );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_6 = " + std::to_string( static_cast< uint32_t >( m_activeQuests[i]->c.padding1 ) ) );
      }
      else
      {
         charaQuestSet.insert( " QuestId_" + std::to_string( i ) + " = 0" );
         charaQuestSet.insert( " Sequence_" + std::to_string( i ) + " = 0" );
         charaQuestSet.insert( " Flags_" + std::to_string( i ) + " = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_0 = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_1 = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_2 = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_3 = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_4 = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_5 = 0" );
         charaQuestSet.insert( " Variables_" + std::to_string( i ) + "_6 = 0" );
      }
   }

   charaInfoSearchSet.insert( " SelectClassId = " + std::to_string( m_searchSelectClass ) );
   charaInfoSearchSet.insert( " SelectRegion = " + std::to_string( m_searchSelectRegion ) );
   charaInfoSearchSet.insert( " SearchComment = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_searchMessage ), sizeof( m_searchMessage ) ) + "')" ) );

   if( !charaInfoSearchSet.empty() )
   {
      for( auto entry : charaInfoSearchSet )
         updateCharaInfoSearch += entry + ", ";

      updateCharaInfoSearch += condition;
      g_database.execute( updateCharaInfoSearch );
   }

   if( !charaBaseSet.empty() )
   {
      for( auto entry : charaBaseSet )
         updateCharaBase += entry + ", ";

      updateCharaBase += condition;
      g_database.execute( updateCharaBase );
   }

   if( !charaDetailSet.empty() )
   {
      for( auto entry : charaDetailSet )
         updateCharaDetail += entry + ", ";

      updateCharaDetail += condition;
      g_database.execute( updateCharaDetail );
   }

   if( !charaClassSet.empty() )
   {
      for( auto entry : charaClassSet )
         updateCharaClass += entry + ", ";

      updateCharaClass += condition;
      g_database.execute( updateCharaClass );
   }

   if( !charaQuestSet.empty() )
   {
      for( auto entry : charaQuestSet )
         updateCharaQuest += entry + ", ";

      updateCharaQuest += condition;
      g_database.execute( updateCharaQuest );
   }

}

