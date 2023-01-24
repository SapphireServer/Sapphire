#include "PlayerMinimal.h"

#include <Common.h>
#include <Exd/ExdData.h>

#include <Database/DatabaseDef.h>

#include <nlohmann/json.hpp>

extern Sapphire::Data::ExdData g_exdData;

namespace Sapphire::Api {

using namespace Common;

// player constructor
PlayerMinimal::PlayerMinimal() :
  m_characterId( 0 )
{


}

// load player from the db
// TODO change void CPlayer::load to bool, we want to know if something went wrong
void PlayerMinimal::load( uint64_t charId )
{

  auto stmt = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_SEL_MINIMAL );

  stmt->setUInt64( 1, charId );
  auto res = g_charaDb.query( stmt );

  if( !res->next() )
    return;

  m_characterId = charId;
  m_id = res->getUInt( "EntityId" );

  memset( m_name, 0, 32 );

  strcpy( m_name, res->getString( "Name" ).c_str() );

  auto customize = res->getBlobVector( "Customize" );
  memcpy( ( char* ) m_look, customize.data(), customize.size() );
  for( int32_t i = 0; i < 26; i++ )
  {
    m_lookMap[ i ] = m_look[ i ];
  }

  auto modelEquip = res->getBlobVector( "ModelEquip" );
  memcpy( ( char* ) m_modelEquip, modelEquip.data(), modelEquip.size() );

  m_modelMainWeapon = res->getUInt64( "ModelMainWeapon" );
  m_modelSubWeapon = res->getUInt64( "ModelSubWeapon" );
  m_equipDisplayFlags = res->getUInt8( "EquipDisplayFlags" );


  setBirthDay( res->getUInt8( "BirthDay" ), res->getUInt8( "BirthMonth" ) );
  m_guardianDeity = res->getUInt8( "GuardianDeity" );
  m_class = res->getUInt8( "Class" );
  m_territoryTypeId = res->getUInt16( "TerritoryType" );

  res.reset();

  // SELECT ClassIdx, Exp, Lvl
  auto stmtClass = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_CLASS_SEL );
  stmtClass->setUInt64( 1, m_characterId );

  auto resClass = g_charaDb.query( stmtClass );

  while( resClass->next() )
  {
    auto classIdx = resClass->getUInt( 1 );
    auto lvl = resClass->getUInt( 3 );

    m_classMap[ classIdx ] = lvl;
    m_classLevel = getClassLevel();
  }
}

std::string PlayerMinimal::getInfoJson()
{
  auto payload = nlohmann::json();
  auto& c = payload["content"];

  // DisplayName
  c.push_back( getName() );

  // class levels
  auto levelsArray = nlohmann::json();
  for( int i = 0; i < Common::CLASSJOB_SLOTS; ++i )
  {
    // these must be strings
    levelsArray.push_back( std::to_string( m_classMap[ i ] ) );
  }

  // ClassLv
  c.push_back( levelsArray );

  // Race
  c.push_back( "0" );
  // Tribe
  c.push_back( "0" );
  // Sex
  c.push_back( "0" );

  // BirthMonth
  c.push_back( std::to_string( getBirthMonth() ) );
  // Birthday
  c.push_back( std::to_string( getBirthDay() ) );
  // GuardianDeity
  c.push_back( std::to_string( getGuardianDeity() ) );

  // Class
  c.push_back( std::to_string( m_class ) );

  // ZoneId
  c.push_back( "0" );

  // TerritoryType
  c.push_back( std::to_string( getZoneId() ) );

  // ContentFinderCondition
  //c.push_back( "0" );

  // look map
  auto lookArray = nlohmann::json();
  for( auto& it : m_lookMap )
  {
    lookArray.push_back( std::to_string( it.second ) );
  }
  // Customize
  c.push_back( lookArray );

  // ModelMainWeapon
  c.push_back( std::to_string( m_modelMainWeapon ) );
  // ModelSubWeapon
  c.push_back( std::to_string( m_modelSubWeapon ) );

  // model
  auto modelArray = nlohmann::json();
  for( auto i : m_modelEquip )
  {
    modelArray.push_back( std::to_string( i ) );
  }
  // ModelEquip
  c.push_back( modelArray );

  // MainWeapon
  c.push_back( "1" );
  // SubWeapon
  c.push_back( "0" );
  // JobStone
  c.push_back( "0" );

  // RemakeFlag
  c.push_back( "0" );

  // ConfigFlags
  c.push_back( std::to_string( m_equipDisplayFlags ) );

  // Voice
  c.push_back( "0" );
  // WorldName
  c.push_back( "" );
  // LoginStatus
  c.push_back( "0" );
  // IsOutTerritory
  //c.push_back( "0" );


  payload["classname"] = "ClientSelectData";
  payload["classid"] = 116;

  return payload.dump();
}

uint8_t PlayerMinimal::getClassLevel()
{
  uint8_t classJobIndex = g_exdData.getRow< Excel::ClassJob >( m_class )->data().WorkIndex;
  return static_cast< uint8_t >( m_classMap[ classJobIndex ] );
}

void PlayerMinimal::saveAsNew()
{

  std::vector< uint8_t > customize( 26 );
  std::vector< uint8_t > howTo( 33 );
  std::vector< uint8_t > aetherytes( 16 );
  std::vector< uint8_t > discovery( 421 );
  std::vector< uint8_t > questComplete( 342 );
  std::vector< uint8_t > unlocks( 64 );
  std::vector< uint8_t > mountGuide( 15 );
  std::vector< uint8_t > orchestrion( 40 );
  std::vector< uint8_t > modelEquip( 40 );
  std::vector< uint8_t > questTracking8( 10 );
  std::vector< uint8_t > monsterNote( 41 );
  std::vector< int16_t > questTracking = { -1, -1, -1, -1, -1 };

  memset( questComplete.data(), 0, questComplete.size() );

  memcpy( questTracking8.data(), questTracking.data(), questTracking8.size() );

  for( uint32_t i = 0; i < m_lookMap.size(); i++ )
  {
    customize[ i ] = m_lookMap[ i ];
  }

  uint32_t equipModel[10];
  memset( equipModel, 0, 40 );

  uint32_t startZone;
  float x, y, z, o;
  int32_t startTown = 0;
  int32_t homePoint = 0;

  switch( static_cast< Sapphire::Common::ClassJob >( m_class ) )
  {
    case Sapphire::Common::ClassJob::Conjurer:
    case Sapphire::Common::ClassJob::Lancer:
    case Sapphire::Common::ClassJob::Archer:
      x = 127.0f;
      y = -13.0f;
      z = 147.0f;
      o = -2.1f;
      startZone = 183;
      startTown = 2;
      homePoint = 2;
      break;

    case Sapphire::Common::ClassJob::Marauder:
    case Sapphire::Common::ClassJob::Arcanist:
      x = -53.0f;
      y = 18.0f;
      z = 0.0f;
      o = 1.5f;
      startTown = 1;
      startZone = 181;
      homePoint = 8;
      break;

    case Sapphire::Common::ClassJob::Thaumaturge:
    case Sapphire::Common::ClassJob::Pugilist:
    case Sapphire::Common::ClassJob::Gladiator:
      x = 42.0f;
      y = 4.0f;
      z = -157.6f;
      o = -0.3f;
      startTown = 3;
      startZone = 182;
      homePoint = 9;
      break;

    default:
      break;
  }

  // CharacterId, ClassIdx, Exp, Lvl
  auto stmtClass = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_CLASS_INS );
  stmtClass->setUInt64( 1, m_characterId );
  stmtClass->setInt( 2, g_exdData.getRow< Excel::ClassJob >( m_class )->data().WorkIndex );
  stmtClass->setInt( 3, 0 );
  stmtClass->setInt( 4, 1 );
  g_charaDb.directExecute( stmtClass );

  auto stmtSearchInfo = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_SEARCHINFO_INS );
  stmtSearchInfo->setUInt64( 1, m_characterId );
  g_charaDb.directExecute( stmtSearchInfo );

  // Friend list related
  auto stmtFriendList = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_FRIENDLIST_INS );
  std::vector< uint8_t > friendIds( 1600, 0 );
  std::vector< uint8_t > inviteIds( 1600, 0 );

  stmtFriendList->setUInt64( 1, m_characterId );
  stmtFriendList->setBinary( 2, friendIds );
  stmtFriendList->setBinary( 3, inviteIds );
  g_charaDb.directExecute( stmtFriendList );

  // Blacklist related
  auto stmtBlacklist = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_BLACKLIST_INS );
  std::vector< uint8_t > blIds( 1600, 0 );

  stmtBlacklist->setUInt64( 1, m_characterId );
  stmtBlacklist->setBinary( 2, blIds );
  g_charaDb.directExecute( stmtBlacklist );

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// SET UP INVENTORIES
  createInvDbContainer( InventoryType::Bag0 );
  createInvDbContainer( InventoryType::Bag1 );
  createInvDbContainer( InventoryType::Bag2 );
  createInvDbContainer( InventoryType::Bag3 );

  createInvDbContainer( InventoryType::ArmoryOff );

  createInvDbContainer( InventoryType::ArmoryHead );
  createInvDbContainer( InventoryType::ArmoryBody );
  createInvDbContainer( InventoryType::ArmoryHand );
  createInvDbContainer( InventoryType::ArmoryWaist );
  createInvDbContainer( InventoryType::ArmoryLegs );
  createInvDbContainer( InventoryType::ArmoryFeet );

  createInvDbContainer( InventoryType::ArmoryNeck );
  createInvDbContainer( InventoryType::ArmoryEar );
  createInvDbContainer( InventoryType::ArmoryWrist );
  createInvDbContainer( InventoryType::ArmoryRing );
  createInvDbContainer( InventoryType::ArmoryMain );
  createInvDbContainer( InventoryType::ArmorySoulCrystal );

  createCurrencyDbContainer();
  createInvDbContainer( InventoryType::Crystal );

  auto stmtMonsterNote = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_MONSTERNOTE_INS );
  stmtMonsterNote->setUInt64( 1, m_characterId );
  for( uint8_t i = 1; i <= 12; ++i )
    stmtMonsterNote->setBinary( i + 1, monsterNote );
  g_charaDb.directExecute( stmtMonsterNote );

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// SETUP EQUIPMENT / STARTING GEAR
  auto classJobInfo = g_exdData.getRow< Excel::ClassJob >( m_class );
  uint32_t weaponId = classJobInfo->data().InitWeapon[ 0 ];
  uint64_t uniqueId = getNextUId64();

  uint8_t race = customize[ CharaLook::Race ];
  uint8_t gender = customize[ CharaLook::Gender ];

  auto raceInfo = g_exdData.getRow< Excel::Race >( race );

  uint32_t body;
  uint32_t hands;
  uint32_t legs;
  uint32_t feet;
  uint64_t bodyUid = getNextUId64();
  uint64_t handsUid = getNextUId64();
  uint64_t legsUid = getNextUId64();
  uint64_t feetUid = getNextUId64();

  body = raceInfo->data().Body[ gender ];
  hands = raceInfo->data().Hand[ gender ];
  legs = raceInfo->data().Leg[ gender ];
  feet = raceInfo->data().Foot[ gender ];

  auto mainWeaponInfo = g_exdData.getRow< Excel::Item >( weaponId );
  auto bodyInfo = g_exdData.getRow< Excel::Item >( body );
  auto handsInfo = g_exdData.getRow< Excel::Item >( hands );
  auto legsInfo = g_exdData.getRow< Excel::Item >( legs );
  auto feetInfo = g_exdData.getRow< Excel::Item >( feet );

  uint64_t modelMainWeapon = mainWeaponInfo->data().ModelId;

  equipModel[ GearModelSlot::ModelBody ] = static_cast< uint32_t >( bodyInfo->data().ModelId );
  equipModel[ GearModelSlot::ModelHands ] = static_cast< uint32_t >( handsInfo->data().ModelId );
  equipModel[ GearModelSlot::ModelLegs ] = static_cast< uint32_t >( legsInfo->data().ModelId );
  equipModel[ GearModelSlot::ModelFeet ] = static_cast< uint32_t >( feetInfo->data().ModelId );

  insertDbGlobalItem( weaponId, uniqueId );
  insertDbGlobalItem( body, bodyUid );
  insertDbGlobalItem( hands, handsUid );
  insertDbGlobalItem( legs, legsUid );
  insertDbGlobalItem( feet, feetUid );


  g_charaDb.execute( "INSERT INTO charaitemgearset (storageId, CharacterId, "
                     "container_" + std::to_string( GearSetSlot::MainHand ) + ", "
                     "container_" + std::to_string( GearSetSlot::Body ) + ", "
                     "container_" + std::to_string( GearSetSlot::Hands ) + ", "
                     "container_" + std::to_string( GearSetSlot::Legs ) + ", "
                     "container_" + std::to_string( GearSetSlot::Feet ) + ", "
                     "container_" + std::to_string( GearSetSlot::Neck ) + ", "
                     "container_" + std::to_string( GearSetSlot::Ear ) + ", "
                     "container_" + std::to_string( GearSetSlot::Wrist ) + ", "
                     "container_" + std::to_string( GearSetSlot::Ring1 ) + ", UPDATE_DATE ) "
                     "VALUES ( " +
                     std::to_string( InventoryType::GearSet0 ) + ", " +
                     std::to_string( m_characterId ) + ", " +
                     std::to_string( uniqueId ) + ", " +
                     std::to_string( bodyUid ) + ", " +
                     std::to_string( handsUid ) + ", " +
                     std::to_string( legsUid ) + ", " +
                     std::to_string( feetUid ) + ", " +
                     std::to_string( 0 ) + ", " +
                     std::to_string( 0 ) + ", " +
                     std::to_string( 0 ) + ", " +
                     std::to_string( 0 ) + ", NOW());" );

  //        "(AccountId, CharacterId, EntityId, Name, Hp, Mp, "
  //        "Customize, Voice, IsNewGame, TerritoryType, PosX, PosY, PosZ, PosR, ModelEquip, "
  //        "IsNewAdventurer, GuardianDeity, Birthday, BirthMonth, Class, Status, FirstClass, "
  //        "HomePoint, StartTown, Discovery, HowTo, QuestCompleteFlags, Unlocks, QuestTracking, "
  //        "Aetheryte, GMRank, UPDATE_DATE )



  memcpy( modelEquip.data(), equipModel, modelEquip.size() );
  auto stmt = g_charaDb.getPreparedStatement( Db::ZoneDbStatements::CHARA_INS );
  stmt->set( 1, m_accountId );
  stmt->set( 2, m_characterId );
  stmt->set( 3, m_id );

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
  stmt->setInt( 23, homePoint );
  stmt->setInt( 24, startTown );
  stmt->setBinary( 25, discovery );
  stmt->setBinary( 26, howTo );
  stmt->setBinary( 27, questComplete );
  stmt->setBinary( 28, unlocks );
  stmt->setBinary( 29, questTracking8 );
  stmt->setBinary( 30, aetherytes );
  stmt->setInt( 31, m_gmRank );
  stmt->setBinary( 32, mountGuide );
  stmt->setBinary( 33, orchestrion );
  stmt->set( 34, modelMainWeapon );
  g_charaDb.directExecute( stmt );

}

void PlayerMinimal::insertDbGlobalItem( uint32_t itemId, uint64_t uniqueId ) const
{
  auto stmtItemGlobal = g_charaDb.getPreparedStatement( Db::CHARA_ITEMGLOBAL_INS );
  stmtItemGlobal->setUInt64( 1, m_characterId );
  stmtItemGlobal->setInt64( 2, uniqueId );
  stmtItemGlobal->setInt( 3, itemId );
  stmtItemGlobal->setInt( 4, 1 ); // stack of 1
  g_charaDb.directExecute( stmtItemGlobal );
}

void PlayerMinimal::createInvDbContainer( uint16_t slot ) const
{
  auto stmtCreateInv = g_charaDb.getPreparedStatement( Db::CHARA_ITEMINV_INS );
  stmtCreateInv->setUInt64( 1, m_characterId );
  stmtCreateInv->setInt( 2, slot );
  g_charaDb.directExecute( stmtCreateInv );
}

void PlayerMinimal::createCurrencyDbContainer() const
{
  auto stmtCreateInv = g_charaDb.getPreparedStatement( Db::CHARA_CURRENCYINV_INS );
  stmtCreateInv->setUInt64( 1, m_characterId );
  g_charaDb.directExecute( stmtCreateInv );
}

uint64_t PlayerMinimal::getNextUId64() const
{
  g_charaDb.directExecute( std::string( "INSERT INTO uniqueiddata( IdName ) VALUES( 'NOT_SET' );" ) );
  auto res = g_charaDb.query( "SELECT LAST_INSERT_ID();" );

  if( !res->next() )
    return 0;

  return res->getUInt64( 1 );
}
}
