#include "PlayerMinimal.h"

#include <Server_Common/Util/Util.h>
#include <Server_Common/Database/Database.h>
#include <Server_Common/Common.h>
#include <Server_Common/Exd/ExdData.h>

#include <Server_Common/Database/DbLoader.h>
#include <Server_Common/Database/CharaDbConnection.h>
#include <Server_Common/Database/DbWorkerPool.h>
#include <Server_Common/Database/PreparedStatement.h>

#include "src/libraries/sapphire/mysqlConnector/MySqlConnector.h"

extern Core::Db::Database g_database;
extern Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;
extern Core::Data::ExdData g_exdData;

namespace Core {

   using namespace Common;

   // player constructor
   PlayerMinimal::PlayerMinimal( void ) : m_id( 0 )
   {


   }

   // deconstructor
   PlayerMinimal::~PlayerMinimal( void )
   {

   }

   // load player from the db
   // TODO change void CPlayer::load to bool, we want to know if something went wrong
   void PlayerMinimal::load( uint32_t charId )
   {

      auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_SEL_MINIMAL );

      stmt->setUInt( 1, charId );
      auto res = g_charaDb.query( stmt );

      if( !res->next() )
         return;

      m_id = charId;

      memset( m_name, 0, 32 );

      strcpy( m_name, res->getString( "Name" ).c_str() );

      auto customize = res->getBlobVector( "Customize" );
      memcpy( (char*)m_look, customize.data(), customize.size() );
      for( int32_t i = 0; i < 26; i++ )
      {
         m_lookMap[i] = m_look[i];
      }

      auto modelEquip = res->getBlobVector( "ModelEquip" );
      memcpy( (char*)m_modelEquip, modelEquip.data(), modelEquip.size() );


      setBirthDay( res->getUInt8( "BirthDay" ), res->getUInt8( "BirthMonth" ) );
      m_guardianDeity = res->getUInt8( "GuardianDeity" );
      m_class = res->getUInt8( "Class" );
      m_contentId = res->getUInt64( "ContentId" );
      m_zoneId = res->getUInt8( "TerritoryId" );

      // SELECT ClassIdx, Exp, Lvl
      auto stmtClass = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_SEL_MINIMAL );
      stmtClass->setInt( 1, m_id );

      auto resClass = g_charaDb.query( stmt );

      while( resClass->next() )
      {
         m_classMap[resClass->getUInt( 1 )] = resClass->getUInt( 3 );
      }
   }


   std::string PlayerMinimal::getLookString()
   {

      auto it = m_lookMap.begin();

      std::string lookString;

      for( ; it != m_lookMap.end(); ++it )
      {

         std::string s = std::to_string( it->second );

         lookString += "\"" + s + "\"";
         if( it != m_lookMap.end() )
         {
            lookString += ",";
         }
      }

      return lookString.substr( 0, lookString.size() - 1 );
   }

   std::string PlayerMinimal::getModelString()
   {
      std::string modelString = "\""
         + std::to_string( m_modelEquip[2] ) + "\",\""
         + std::to_string( m_modelEquip[3] ) + "\",\""
         + std::to_string( m_modelEquip[4] ) + "\",\""
         + std::to_string( m_modelEquip[6] ) + "\",\""
         + std::to_string( m_modelEquip[7] ) + "\",\"5\",\"6\",\"7\",\"8\",\"9\"";
      return modelString;
   }

   std::string PlayerMinimal::getInfoJson()
   {
      std::string charDetails = "{\"content\":[\"" + std::string( getName() ) + "\"," +
         "[" + getClassString() + "]," +
         "\"0\",\"0\",\"0\",\"" + std::to_string( getBirthMonth() ) + "\",\"" + std::to_string( getBirthDay() ) + "\",\"" + std::to_string( getGuardianDeity() ) + "\",\"" + std::to_string( m_class ) + "\",\"0\",\"" + std::to_string( getZoneId() ) + "\"," +
         "[" + getLookString() + "]," +
         "\"0\",\"0\"," +
         "[" + getModelString() + "]," +
         "\"1\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\"]," +
         "\"classname\":\"ClientSelectData\",\"classid\":116}";
      return charDetails;
   }

   std::string PlayerMinimal::getClassString()
   {

      std::map<uint8_t, uint16_t>::iterator it;

      it = m_classMap.begin();

      std::string classString;

      for( ; it != m_classMap.end(); ++it )
      {

         std::string s = std::to_string( it->second );

         classString += "\"" + s + "\"";
         if( it != m_classMap.end() )
         {
            classString += ",";
         }
      }

      return classString.substr( 0, classString.size() - 1 );
   }

   void PlayerMinimal::saveAsNew()
   {

      std::vector< uint8_t > customize( 32 );
      std::vector< uint8_t > howTo( 32 );
      std::vector< uint8_t > aetherytes( 12 );
      std::vector< uint8_t > discovery( 411 );
      std::vector< uint8_t > questComplete( 200 );
      std::vector< uint8_t > unlocks( 64 );
      std::vector< uint8_t > modelEquip( 40 );
      std::vector< uint8_t > questTracking8(10);
      std::vector< int16_t > questTracking = { -1, -1, -1, -1, -1 };

      memset( questComplete.data(), 0, questComplete.size() );

      memcpy( questTracking8.data(), questTracking.data(), questTracking8.size() );

      uint16_t size = static_cast< uint16_t >( m_lookMap.size() );

      for( uint32_t i = 0; i < m_lookMap.size(); i++ )
      {
         customize[i] = m_lookMap[i];
      }

      uint32_t equipModel[10];
      memset( equipModel, 0, 40 );
      memcpy( modelEquip.data(), equipModel, modelEquip.size() );

      uint32_t startZone;
      float x, y, z, o;
      int32_t startTown = 0;

      switch( m_class )
      {
      case Core::Common::ClassJob::CLASS_CONJURER:
      case Core::Common::ClassJob::CLASS_LANCER:
      case Core::Common::ClassJob::CLASS_ARCHER:
         x = 127.0f;
         y = -13.0f;
         z = 147.0f;
         o = -2.1f;
         startZone = 183;
         startTown = 2;
         break;

      case Core::Common::ClassJob::CLASS_MARAUDER:
      case Core::Common::ClassJob::CLASS_ARCANIST:
         x = -53.0f;
         y = 18.0f;
         z = 0.0f;
         o = 1.5f;
         startTown = 1;
         startZone = 181;
         break;

      case Core::Common::ClassJob::CLASS_THAUMATURGE:
      case Core::Common::ClassJob::CLASS_PUGILIST:
      case Core::Common::ClassJob::CLASS_GLADIATOR:
         x = 42.0f;
         y = 4.0f;
         z = -157.6f;
         o = -0.3f;
         startTown = 3;
         startZone = 182;
         break;
      }

      //        "(AccountId, CharacterId, ContentId, Name, Hp, Mp, "
      //        "Customize, Voice, IsNewGame, TerritoryId, PosX, PosY, PosZ, PosR, ModelEquip, "
      //        "IsNewAdventurer, GuardianDeity, Birthday, BirthMonth, Class, Status, FirstClass, "
      //        "HomePoint, StartTown, Discovery, HowTo, QuestCompleteFlags, Unlocks, QuestTracking, "
      //        "Aetheryte, GMRank, UPDATE_DATE )

      // CharacterId, ClassIdx, Exp, Lvl
      auto stmtClass = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_CLASS_INS );
      stmtClass->setInt( 1, m_id );
      stmtClass->setInt( 2, g_exdData.m_classJobInfoMap[m_class].exp_idx );
      stmtClass->setInt( 3, 0 );
      stmtClass->setInt( 4, 1 );
      g_charaDb.directExecute( stmtClass );

      auto stmt = g_charaDb.getPreparedStatement( Db::CharaDbStatements::CHARA_INS );

      stmt->setInt( 1, m_accountId );
      stmt->setInt( 2, m_id );
      stmt->setInt64( 3, m_contentId );
      stmt->setString( 4, std::string( m_name ) );
      stmt->setInt( 5, 100 );
      stmt->setInt( 6, 100 );
      stmt->setBinary( 7, customize );
      stmt->setInt( 8, m_voice );
      stmt->setInt( 9, 1 );
      stmt->setInt( 10, startZone );
      stmt->setDouble( 11, x );
      stmt->setDouble( 12, y );
      stmt->setDouble( 13, z );
      stmt->setDouble( 14, o );
      stmt->setBinary( 15, modelEquip );
      stmt->setInt( 16, 1 );
      stmt->setInt( 17, m_guardianDeity );
      stmt->setInt( 18, m_birthDay );
      stmt->setInt( 19, m_birthMonth );
      stmt->setInt( 20, m_class );
      stmt->setInt( 21, 1 );
      stmt->setInt( 22, m_class );
      stmt->setInt( 23, 2 );
      stmt->setInt( 24, startTown );
      stmt->setBinary( 25, discovery );
      stmt->setBinary( 26, howTo );
      stmt->setBinary( 27, questComplete );
      stmt->setBinary( 28, unlocks );
      stmt->setBinary( 29, questTracking8 );
      stmt->setBinary( 30, aetherytes );
      stmt->setInt( 31, m_gmRank );
      g_charaDb.directExecute( stmt );



      g_charaDb.execute( "INSERT INTO charainfosearch (CharacterId, UPDATE_DATE ) VALUES (" + std::to_string( m_id ) + ", NOW());" );

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SET UP INVENTORIES

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag0 ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag1 ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag2 ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag3 ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryOff ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryHead ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryBody ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryHand ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryWaist ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryLegs ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryFeet ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmotyNeck ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryEar ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE )"
         "VALUES ( " + std::to_string( InventoryType::ArmoryWrist ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryRing ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryMain ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory  (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Currency ) + ", " + std::to_string( m_id ) + ", NOW());" );

      g_charaDb.execute( "INSERT INTO charaiteminventory  (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Crystal ) + ", " + std::to_string( m_id ) + ", NOW());" );

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SETUP EQUIPMENT / STARTING GEAR
      auto classJobInfo = g_exdData.m_classJobInfoMap[m_class];
      uint32_t weaponId = classJobInfo.start_weapon_id;
      uint64_t uniqueId = g_database.getNextUId();

      uint8_t race = customize[CharaLook::Race];
      uint8_t gender = customize[CharaLook::Gender];

      auto raceInfo = g_exdData.getRaceInfo( race );

      int32_t body;
      int32_t hands;
      int32_t legs;
      int32_t feet;
      uint64_t bodyUid = g_database.getNextUId();
      uint64_t handsUid = g_database.getNextUId();
      uint64_t legsUid = g_database.getNextUId();
      uint64_t feetUid = g_database.getNextUId();

      if( gender == 0 )
      {
         body = raceInfo->male_body;
         hands = raceInfo->male_hands;
         legs = raceInfo->male_legs;
         feet = raceInfo->male_feet;
      }
      else
      {
         body = raceInfo->female_body;
         hands = raceInfo->female_hands;
         legs = raceInfo->female_legs;
         feet = raceInfo->female_feet;
      }

      g_charaDb.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_id ) + ", " + std::to_string( uniqueId ) + ", " +
         std::to_string( weaponId ) + ", NOW());" );
      g_charaDb.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_id ) + ", " + std::to_string( bodyUid ) + ", " +
         std::to_string( body ) + ", NOW());" );
      g_charaDb.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_id ) + ", " + std::to_string( handsUid ) + ", " +
         std::to_string( hands ) + ", NOW());" );
      g_charaDb.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_id ) + ", " + std::to_string( legsUid ) + ", " +
         std::to_string( legs ) + ", NOW());" );
      g_charaDb.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_id ) + ", " + std::to_string( feetUid ) + ", " +
         std::to_string( feet ) + ", NOW());" );
      g_charaDb.execute( "INSERT INTO charaitemgearset (storageId, CharacterId, "
         "container_" + std::to_string( EquipSlot::MainHand ) + ", "
         "container_" + std::to_string( EquipSlot::Body ) + ", "
         "container_" + std::to_string( EquipSlot::Hands ) + ", "
         "container_" + std::to_string( EquipSlot::Legs ) + ", "
         "container_" + std::to_string( EquipSlot::Feet ) + ", "
         "UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::GearSet0 ) + ", " + std::to_string( m_id ) + ", " +
         std::to_string( uniqueId ) + ", " +
         std::to_string( bodyUid ) + ", " +
         std::to_string( handsUid ) + ", " +
         std::to_string( legsUid ) + ", " +
         std::to_string( feetUid ) + ", NOW());" );

   }
}
