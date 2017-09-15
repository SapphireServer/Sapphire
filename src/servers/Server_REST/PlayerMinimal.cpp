#include "PlayerMinimal.h"

//#include "Core/Server_Game/CServerGame.h"
#include <src/servers/Server_Common/Util/Util.h>
#include <src/servers/Server_Common/Database/Database.h>
#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Exd/ExdData.h>


extern Core::Db::Database g_database;
extern Core::Data::ExdData g_exdData;

namespace Core {

   using namespace Common;

   // player constructor
   PlayerMinimal::PlayerMinimal( void ) : m_iD( 0 )
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

      boost::shared_ptr<Db::QueryResult> pQR = g_database.query( "SELECT c.Name, "
         " c.Customize, "
         " cpc.BirthDay, "
         " cpc.BirthMonth, "
         " cpc.GuardianDeity, "
         " cpc.Class, "
         " c.ModelEquip, "
         " c.ContentId, "
         " c.PrimaryTerritoryId "
         " FROM charabase AS c "
         " INNER JOIN charadetail AS cpc "
         " ON cpc.CharacterId = c.CharacterId "
         " WHERE c.CharacterId = " + std::to_string( charId ) + ";" );
      if( !pQR )
      {
         return;
      }

      m_iD = charId;

      Db::Field *field = pQR->fetch();

      memset( m_name, 0, 32 );

      strcpy( m_name, field[0].getString().c_str() );

      field[1].getBinary( (char*)m_look, 26 );

      field[6].getBinary( (char*)m_modelEquip, 40 );

      for( int32_t i = 0; i < 26; i++ )
      {
         m_lookMap[i] = m_look[i];
      }

      setBirthDay( field[2].get< int8_t >(), field[3].get< int8_t >() );
      m_guardianDeity = field[4].get< int8_t >();
      m_class = field[5].get< int8_t >();
      m_contentId = field[7].getUInt64();
      m_zoneId = field[8].get< uint16_t >();

      auto pQR2 = g_database.query( "SELECT * FROM characlass WHERE CharacterId = " + std::to_string( charId ) + ";" );

      Db::Field* field2 = pQR2->fetch();

      for( uint8_t i = 0; i < 25; i++ )
      {
         uint8_t index = i * 2;
         m_classMap[i] = field2[index].get< uint8_t >();
         //m_expArray[i] = 
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

      char customize[32];
      char howTo[32];
      memset( howTo, 0, 32 );

      char aetherytes[12];
      memset( aetherytes, 0, 12 );

      char discovery[411];
      memset( discovery, 0, 411 );

      char questComplete[200];
      memset( questComplete, 0, 200 );

      char unlocks[64];
      memset( unlocks, 0, 64 );

      int16_t questTracking[5] = { -1, -1, -1, -1, -1 };

      uint16_t size = static_cast< uint16_t >( m_lookMap.size() );

      for( int32_t i = 0; i < m_lookMap.size(); i++ )
      {
         customize[i] = m_lookMap[i];
      }

      uint32_t equipModel[10];
      memset( equipModel, 0, 40 );

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

      g_database.execute( "INSERT INTO charabase "
         "(Hp, "
         " Mp, "
         " CharacterId, "
         " ContentId, "
         " Customize, "
         " Name, "
         " Voice, "
         " FirstLogin, "
         " IsNewGame, "
         " PrimaryTerritoryId, "
         " Pos_0_0, "
         " Pos_0_1, "
         " Pos_0_2, "
         " Pos_0_3, "
         " AccountId, "
         " ModelEquip, "
         " IsNewAdventurer, "
         " UPDATE_DATE ) "
         " VALUES (100, 100, " + std::to_string( m_iD ) + ", " + std::to_string( m_contentId ) + ", " +
         " UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)customize, size ) ) + "'), " +
         "'" + g_database.escapeString( std::string( m_name ) ) + "', " + std::to_string( m_voice ) + ", 1, 1, " +
         std::to_string( startZone ) + ", " + std::to_string( x ) + ", " +
         std::to_string( y ) + ", " + std::to_string( z ) + ", " + std::to_string( o ) + ", " +
         std::to_string( m_accountId ) + ", UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)equipModel, 40 ) ) + "'), 1, NOW());" );

      g_database.execute( "INSERT INTO charadetail "
         "(CharacterId, "
         " GuardianDeity, "
         " Birthday, "
         " BirthMonth, "
         " Class, "
         " CreateUnixTime, "
         " IsActive, "
         " Status, "
         " FirstClass, "
         " HomePoint, "
         " StartTown, "
         " Discovery, "
         " HowTo, "
         " QuestCompleteFlags, "
         " unlocks, "
         " QuestTracking, "
         " Aetheryte, "
         " GMRank, "
         " UPDATE_DATE ) "
         " VALUES (" + std::to_string( m_iD ) + ", "
         + std::to_string( m_guardianDeity ) + ", "
         + std::to_string( m_birthDay ) + ", "
         + std::to_string( m_birthMonth ) + ", "
         + std::to_string( m_class ) + ", UNIX_TIMESTAMP(NOW()), 1, 1, "
         + std::to_string( m_class ) + ", 2, "
         + std::to_string( startTown ) + ", "
         + "UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)discovery, 411 ) ) + "'), "
         + "UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)howTo, 32 ) ) + "'), "
         + "UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)questComplete, 200 ) ) + "'), "
         + "UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)unlocks, 64 ) ) + "'), "
         + "UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)questTracking, 10 ) ) + "'), "
         + "UNHEX('" + std::string( Util::binaryToHexString( (uint8_t*)aetherytes, 12 ) ) + "'),"
         + std::to_string( m_gmRank ) + ", NOW());" );


      g_database.execute( "INSERT INTO characlass  (CharacterId, Lv_" + std::to_string( g_exdData.m_classJobInfoMap[m_class].exp_idx ) + ", UPDATE_DATE ) "
         " VALUES (" + std::to_string( m_iD ) + ", 1, NOW());" );

      g_database.execute( "INSERT INTO charaquest (CharacterId, UPDATE_DATE ) "
         " VALUES (" + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charainfosearch (CharacterId, UPDATE_DATE ) "
         " VALUES (" + std::to_string( m_iD ) + ",  NOW());" );

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // SET UP INVENTORIES

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag0 ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag1 ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag2 ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Bag3 ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryOff ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryHead ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryBody ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryHand ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryWaist ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryLegs ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryFeet ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmotyNeck ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryEar ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE )"
         "VALUES ( " + std::to_string( InventoryType::ArmoryWrist ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryRing ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::ArmoryMain ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory  (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Currency ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

      g_database.execute( "INSERT INTO charaiteminventory  (storageId, CharacterId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::Crystal ) + ", " + std::to_string( m_iD ) + ",  NOW());" );

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

      g_database.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_iD ) + ", " + std::to_string( uniqueId ) + ", " +
         std::to_string( weaponId ) + ",  NOW());" );
      g_database.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_iD ) + ", " + std::to_string( bodyUid ) + ", " +
         std::to_string( body ) + ",  NOW());" );
      g_database.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_iD ) + ", " + std::to_string( handsUid ) + ", " +
         std::to_string( hands ) + ",  NOW());" );
      g_database.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_iD ) + ", " + std::to_string( legsUid ) + ", " +
         std::to_string( legs ) + ",  NOW());" );
      g_database.execute( "INSERT INTO charaglobalitem (CharacterId, ItemId, catalogId, UPDATE_DATE ) "
         "VALUES ( " + std::to_string( m_iD ) + ", " + std::to_string( feetUid ) + ", " +
         std::to_string( feet ) + ",  NOW());" );
      g_database.execute( "INSERT INTO charaitemgearset (storageId, CharacterId, "
         "container_" + std::to_string( EquipSlot::MainHand ) + ", "
         "container_" + std::to_string( EquipSlot::Body ) + ", "
         "container_" + std::to_string( EquipSlot::Hands ) + ", "
         "container_" + std::to_string( EquipSlot::Legs ) + ", "
         "container_" + std::to_string( EquipSlot::Feet ) + ", "
         "UPDATE_DATE ) "
         "VALUES ( " + std::to_string( InventoryType::GearSet0 ) + ", " + std::to_string( m_iD ) + ", " +
         std::to_string( uniqueId ) + ", " +
         std::to_string( bodyUid ) + ", " +
         std::to_string( handsUid ) + ", " +
         std::to_string( legsUid ) + ", " +
         std::to_string( feetUid ) + ", " +
         "NOW());" );



   }
}
