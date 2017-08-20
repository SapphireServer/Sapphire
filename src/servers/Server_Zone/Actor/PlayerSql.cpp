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

#include "Player.h"

#include "src/servers/Server_Zone/Zone/ZoneMgr.h"
#include "src/servers/Server_Zone/Zone/Zone.h"

#include "src/servers/Server_Zone/ServerZone.h"

#include "src/servers/Server_Zone/Forwards.h"

#include "src/servers/Server_Zone/Network/GameConnection.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/InitUIPacket.h"
#include "src/servers/Server_Zone/StatusEffect/StatusEffectContainer.h"
#include "src/servers/Server_Zone/Inventory/Inventory.h"

extern Core::Logger g_log;
extern Core::Db::Database g_database;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

// load player from the db
bool Core::Entity::Player::load( uint32_t charId, Core::SessionPtr pSession )
{
   // TODO: can't help but think that the whole player loading could be handled better...
   const std::string char_id_str = std::to_string( charId );

   auto pQR = g_database.query( "SELECT "
      "c.Name, "
      "c.PrimaryTerritoryId, "
      "c.Hp, "
      "c.Mp, "
      "c.Gp, "
      "c.Mode, "
      "c.Pos_0_0, "
      "c.Pos_0_1, "
      "c.Pos_0_2, "
      "c.Pos_0_3, "
      "c.FirstLogin, " // 10
      "c.Customize, "
      "c.ModelMainWeapon, "
      "c.ModelSubWeapon, "
      "c.ModelEquip, "
      "cd.GuardianDeity, "
      "cd.BirthDay, "
      "cd.BirthMonth, "
      "cd.Status, "
      "cd.Class, "
      "cd.Homepoint, " // 20
      "cd.HowTo, "
      "c.ContentId, "
      "c.Voice, "
      "cd.QuestCompleteFlags, "
      "cd.QuestTracking, "
      "c.IsNewGame, "
      "cd.Aetheryte, "
      "cd.unlocks, "
      "cd.Discovery, "
      "cd.StartTown, " // 30
      "cd.TotalPlayTime, "
      "c.IsNewAdventurer, "
      "cd.GrandCompany, "
      "cd.GrandCompanyRank, "
      "cd.CFPenaltyUntil, "
      "cd.OpeningSequence "
      "FROM charabase AS c "
      " INNER JOIN charadetail AS cd "
      " ON c.CharacterId = cd.CharacterId "
      "WHERE c.CharacterId = " + char_id_str + ";" );

   if( !pQR )
   {
      g_log.error( "Player id " + char_id_str + " does not exist!" );
      return false;
   }

   m_updateFlags = PlayerSyncFlags::None;
   m_id = charId;

   Db::Field *field = pQR->fetch();

   strcpy( m_name, field[0].getString() );

   ZonePtr pCurrZone = g_zoneMgr.getZone( field[1].getInt32() );
   m_zoneId = field[1].getInt32();

   // see if a valid zone could be found for the character
   if( !pCurrZone )
   {
      g_log.error( "[" + char_id_str + "] Zone " + std::to_string( field[1].getInt32() ) + "not found!" );
      g_log.error( "[" + char_id_str + "] Setting default zone instead" );

      // default to new gridania
      // TODO: should probably just abort and mark character as corrupt
      pCurrZone = g_zoneMgr.getZone( 132 );

      m_pos.x = 0.0f;
      m_pos.y = 0.0f;
      m_pos.z = 0.0f;
      setRotation( 0.0f );
   }

   m_hp = field[2].getUInt32();

   m_mp = field[3].getUInt32();
   m_tp = 0;

   m_pos.x = field[6].getFloat();
   m_pos.y = field[7].getFloat();
   m_pos.z = field[8].getFloat();
   setRotation( field[9].getFloat() );

   m_bFirstLogin = field[10].getBool();

   field[11].getBinary( reinterpret_cast< char* >( m_customize ), 26 );

   m_modelMainWeapon = field[12].getUInt64();

   field[14].getBinary( reinterpret_cast< char* >( m_modelEquip ), 40 );

   m_guardianDeity = field[15].getUInt8();
   m_birthDay = field[16].getUInt8();
   m_birthMonth = field[17].getUInt8();
   m_status = static_cast< ActorStatus >( field[18].getUInt8() );
   m_class = static_cast< ClassJob >( field[19].getUInt8() );
   m_homePoint = field[20].getUInt8();

   field[21].getBinary( reinterpret_cast< char* >( m_howTo ), sizeof( m_howTo ) );

   m_contentId = field[22].getUInt64();

   m_voice = field[23].getUInt32();

   field[24].getBinary( reinterpret_cast< char* >( m_questCompleteFlags ), 200 );

   field[25].getBinary( reinterpret_cast< char* >( m_questTracking ), 10 );

   m_bNewGame = field[26].getBool();

   field[27].getBinary( reinterpret_cast< char* >( m_aetheryte ), sizeof( m_aetheryte ) );

   field[28].getBinary( reinterpret_cast< char* >( m_unlocks ), 64 );

   field[29].getBinary( reinterpret_cast< char* >( m_discovery ), sizeof( m_discovery ) );

   m_startTown = field[30].getInt8();
   m_playTime = field[31].getUInt32();

   m_bNewAdventurer = field[32].getBool();

   m_gc = field[33].getUInt8();
   field[34].getBinary( reinterpret_cast< char* >( m_gcRank ), 3 );

   m_cfPenaltyUntil = field[35].getUInt32();

   m_openingSequence = field[36].getUInt32();

   m_pCell = nullptr;

   if( !loadActiveQuests() || !loadClassData() || !loadSearchInfo() )
      g_log.error( "Player id " + char_id_str + " data corrupt!" );

   m_userLevel = 1;

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
      setSyncFlag( PlayerSyncFlags::NewGame );
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
      m_classArray[i] = field[index].getUInt8();
      m_expArray[i] = field[index + 1].getUInt32();
   }

   return true;
}

bool Core::Entity::Player::loadSearchInfo()
{
   auto pQR = g_database.query( "SELECT * FROM charainfosearch WHERE CharacterId = " + std::to_string( m_id ) + ";" );

   if( !pQR )
      return false;

   Db::Field* field = pQR->fetch();

   m_searchSelectClass = field[1].getUInt8();
   m_searchSelectRegion = field[2].getUInt8();
   sprintf( m_searchMessage, field[3].getString() );

   return true;
}


void Core::Entity::Player::createUpdateSql()
{

   // if nothing to update, don't bother.
   if( m_updateFlags == PlayerSyncFlags::None )
      return;

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

   if( m_updateFlags & PlayerSyncFlags::Position )
   {
      charaBaseSet.insert( " Pos_0_0 = " + std::to_string( m_pos.x ) );
      charaBaseSet.insert( " Pos_0_1 = " + std::to_string( m_pos.y ) );
      charaBaseSet.insert( " Pos_0_2 = " + std::to_string( m_pos.z ) );
      charaBaseSet.insert( " Pos_0_3 = " + std::to_string( getRotation() ) );
      charaBaseSet.insert( " PrimaryTerritoryId = " + std::to_string( m_zoneId ) );
   }

   if( m_updateFlags & PlayerSyncFlags::HomePoint )
      charaDetailSet.insert( " Homepoint = " + std::to_string( m_homePoint ) );

   if( m_updateFlags & PlayerSyncFlags::Discovery )
      charaDetailSet.insert( " Discovery = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_discovery ), sizeof( m_discovery ) ) ) + "')" );

   if( m_updateFlags & PlayerSyncFlags::PlayTime )
      charaDetailSet.insert( " TotalPlayTime = " + std::to_string( m_playTime ) );

   if( m_updateFlags & PlayerSyncFlags::Unlocks )
      charaDetailSet.insert( " unlocks = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_unlocks ), sizeof( m_unlocks ) ) ) + "')" );

   if( m_updateFlags & PlayerSyncFlags::QuestTracker )
      charaDetailSet.insert( " QuestTracking = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_questTracking ), sizeof( m_questTracking ) ) ) + "')" );

   if( m_updateFlags & PlayerSyncFlags::HowTo )
      charaDetailSet.insert( " HowTo = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_howTo ), sizeof( m_howTo ) ) ) + "')" );

   if( m_updateFlags & PlayerSyncFlags::Aetherytes )
      charaDetailSet.insert( " Aetheryte = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_aetheryte ), sizeof( m_aetheryte ) ) ) + "')" );


   if( m_updateFlags & PlayerSyncFlags::NewGame )
      charaBaseSet.insert( " IsNewGame = " + std::to_string( static_cast< uint32_t >( m_bNewGame ) ) );

   if( m_updateFlags & PlayerSyncFlags::FirstLogin )
      charaBaseSet.insert( " FirstLogin = 0 " );

   if( m_updateFlags & PlayerSyncFlags::NewAdventurer )
      charaBaseSet.insert( " IsNewAdventurer = " + std::to_string( static_cast< uint32_t >( m_bNewAdventurer ) ) );

   if( m_updateFlags & PlayerSyncFlags::GC )
   {
      charaDetailSet.insert( " GrandCompany = " + std::to_string( m_gc ) );
      charaDetailSet.insert( " GrandCompanyRank = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_gcRank ), sizeof( m_gcRank ) ) ) + "')" );
   }

   if( m_updateFlags & PlayerSyncFlags::CFPenaltyTime )
   {
      charaDetailSet.insert( " CFPenaltyUntil = " + std::to_string( m_cfPenaltyUntil ) );
   }

   if( m_updateFlags & PlayerSyncFlags::ExpLevel )
   {
      uint8_t classJobIndex = g_exdData.m_classJobInfoMap[static_cast< uint8_t >( getClass() )].exp_idx;
      charaClassSet.insert( " Lv_" + std::to_string( classJobIndex ) + " = " + std::to_string( static_cast< uint32_t >( getLevel() ) ) );
      charaClassSet.insert( " Exp_" + std::to_string( classJobIndex ) + " = " + std::to_string( getExp() ) );
   }

   if( m_updateFlags & PlayerSyncFlags::Status )
   {
      charaBaseSet.insert( " Hp = " + std::to_string( getHp() ) );
      charaBaseSet.insert( " Mp = " + std::to_string( getMp() ) );
      charaBaseSet.insert( " Mode = " + std::to_string( static_cast< uint32_t >( getStance() ) ) );
      charaBaseSet.insert( " ModelEquip = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_modelEquip ), 40 ) ) + "')" );
      charaDetailSet.insert( " Class = " + std::to_string( static_cast< uint32_t >( getClass() ) ) );
      charaDetailSet.insert( " Status = " + std::to_string( static_cast< uint8_t >( getStatus() ) ) );
   }

   if( m_updateFlags & PlayerSyncFlags::OpeningSeq )
   {
      charaDetailSet.insert( " OpeningSequence = " + std::to_string( static_cast< uint8_t >( getOpeningSequence() ) ) );
   }

   if( m_updateFlags & PlayerSyncFlags::Quests )
   {
      charaDetailSet.insert( " QuestCompleteFlags = UNHEX('" + std::string( Util::binaryToHexString( static_cast< uint8_t* >( m_questCompleteFlags ), 200 ) ) + "')" );

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
   }

   if( m_updateFlags & PlayerSyncFlags::SearchInfo )
   {
      charaInfoSearchSet.insert( " SelectClassId = " + std::to_string( m_searchSelectClass ) );
      charaInfoSearchSet.insert( " SelectRegion = " + std::to_string( m_searchSelectRegion ) );
      charaInfoSearchSet.insert( " SearchComment = UNHEX('" + std::string( Util::binaryToHexString( reinterpret_cast< uint8_t* >( m_searchMessage ), sizeof( m_searchMessage ) ) + "')" ) );
   }

   if( !charaInfoSearchSet.empty() )
   {
      for( auto entry : charaInfoSearchSet )
         updateCharaInfoSearch += entry + ", ";

      updateCharaInfoSearch += condition;
      g_database.execute( updateCharaInfoSearch.c_str() );
   }

   if( !charaBaseSet.empty() )
   {
      for( auto entry : charaBaseSet )
         updateCharaBase += entry + ", ";

      updateCharaBase += condition;
      g_database.execute( updateCharaBase.c_str() );
   }

   if( !charaDetailSet.empty() )
   {
      for( auto entry : charaDetailSet )
         updateCharaDetail += entry + ", ";

      updateCharaDetail += condition;
      g_database.execute( updateCharaDetail.c_str() );
   }

   if( !charaClassSet.empty() )
   {
      for( auto entry : charaClassSet )
         updateCharaClass += entry + ", ";

      updateCharaClass += condition;
      g_database.execute( updateCharaClass.c_str() );
   }

   if( !charaQuestSet.empty() )
   {
      for( auto entry : charaQuestSet )
         updateCharaQuest += entry + ", ";

      updateCharaQuest += condition;
      g_database.execute( updateCharaQuest.c_str() );
   }

   m_updateFlags = PlayerSyncFlags::None;

}

