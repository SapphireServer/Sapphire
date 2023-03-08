#include <Common.h>
#include <Logging/Logger.h>

#include <algorithm>

#include "Territory/Territory.h"

#include "Inventory/Item.h"
#include "Inventory/ItemContainer.h"

#include <Exd/ExdData.h>
#include <Database/DatabaseDef.h>

#include "Actor/Player.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/UpdateInventorySlotPacket.h"
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/Util/PacketUtil.h>

#include "Manager/InventoryMgr.h"
#include "Manager/ItemMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/MgrUtil.h"

#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::Entity;
using namespace Sapphire::World;
using namespace Sapphire::Common;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;


void Player::initInventory()
{
  const uint8_t inventorySize = 25;
  auto setupContainer = [ this ]( InventoryType type, uint8_t maxSize, const std::string& tableName,
                                  bool isMultiStorage, bool isPersistentStorage = true )
  { m_storageMap[ type ] = make_ItemContainer( type, maxSize, tableName, isMultiStorage, isPersistentStorage ); };

  // main bags
  setupContainer( Bag0, inventorySize, "charaiteminventory", true );
  setupContainer( Bag1, inventorySize, "charaiteminventory", true );
  setupContainer( Bag2, inventorySize, "charaiteminventory", true );
  setupContainer( Bag3, inventorySize, "charaiteminventory", true );

  // gear set
  setupContainer( GearSet0, 13, "charaitemgearset", true );

  // gil contianer
  setupContainer( Currency, 11, "charaiteminventory", true );

  // crystals??
  setupContainer( Crystal, 11, "charaiteminventory", true );

  // armory weapons - 0
  setupContainer( ArmoryMain, inventorySize, "charaiteminventory", true );

  // armory offhand - 1
  setupContainer( ArmoryOff, inventorySize, "charaiteminventory", true );

  //armory head - 2
  setupContainer( ArmoryHead, inventorySize, "charaiteminventory", true );

  //armory body - 3
  setupContainer( ArmoryBody, inventorySize, "charaiteminventory", true );

  //armory hand - 4
  setupContainer( ArmoryHand, inventorySize, "charaiteminventory", true );

  //armory waist - 5
  setupContainer( ArmoryWaist, inventorySize, "charaiteminventory", true );

  //armory legs - 6
  setupContainer( ArmoryLegs, inventorySize, "charaiteminventory", true );

  //armory feet - 7
  setupContainer( ArmoryFeet, inventorySize, "charaiteminventory", true );

  //neck
  setupContainer( ArmoryNeck, inventorySize, "charaiteminventory", true );

  //earring
  setupContainer( ArmoryEar, inventorySize, "charaiteminventory", true );

  //wrist
  setupContainer( ArmoryWrist, inventorySize, "charaiteminventory", true );

  //armory rings - 11
  setupContainer( ArmoryRing, inventorySize, "charaiteminventory", true );

  //soul crystals - 13
  setupContainer( ArmorySoulCrystal, inventorySize, "charaiteminventory", true );

  // item hand in container
  // non-persistent container, will not save its contents
  setupContainer( HandIn, 10, "", true, false );

  loadInventory();
  calculateItemLevel();
}

void Player::equipWeapon( const Item& item )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto itemInfo = exdData.getRow< Excel::Item >( item.getId() );
  auto itemClassJob = itemInfo->data().Class;
  auto classJobInfo = exdData.getRow< Excel::ClassJob >( static_cast< uint32_t >( getClass() ) );
  auto currentParentClass = static_cast< ClassJob >( classJobInfo->data().MainClass );
  auto newClassJob = static_cast< ClassJob >( itemClassJob );

  if( ( isClassJobUnlocked( newClassJob ) ) && ( currentParentClass != newClassJob ) )
  {
    setClassJob( newClassJob );
  }
}

void Player::equipSoulCrystal( const Item& item )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto itemInfo = exdData.getRow< Excel::Item >( item.getId() );
  auto itemClassJob = itemInfo->data().Class;
  auto newClassJob = static_cast< ClassJob >( itemClassJob );

  if( isClassJobUnlocked( newClassJob ) )
    setClassJob( newClassJob );
}

void Player::updateModels( GearSetSlot equipSlotId, const Sapphire::Item& item )
{
  uint64_t model = item.getModelId1();
  uint64_t model2 = item.getModelId2();
  uint64_t stain = item.getStain();

  switch( equipSlotId )
  {
    case MainHand:
      m_modelMainWeapon = model | ( stain << 48 );
      m_modelSubWeapon = model2;

      if( m_modelSubWeapon > 0 )
        m_modelSubWeapon = m_modelSubWeapon | ( stain << 48 );

      break;

    case OffHand:
      m_modelSubWeapon = model | ( stain << 48 );
      break;

    // these have no model
    case SoulCrystal:
    case Waist:
      break;

    default: // any other slot
      auto modelSlot = equipSlotToModelSlot( equipSlotId );
      if( modelSlot == GearModelSlot::ModelInvalid )
        break;

      model = model | stain << 24;
      m_modelEquip[ static_cast< uint8_t >( modelSlot ) ] = static_cast< uint32_t >( model );
      break;

  }
}

Common::GearModelSlot Player::equipSlotToModelSlot( Common::GearSetSlot slot )
{
  switch( slot )
  {
    case MainHand:
    case OffHand:
    case Waist:
    case SoulCrystal:
    default:
      return GearModelSlot::ModelInvalid;
    case Head:
      return GearModelSlot::ModelHead;
    case Body:
      return GearModelSlot::ModelBody;
    case Hands:
      return GearModelSlot::ModelHands;
    case Legs:
      return GearModelSlot::ModelLegs;
    case Feet:
      return GearModelSlot::ModelFeet;
    case Neck:
      return GearModelSlot::ModelNeck;
    case Ear:
      return GearModelSlot::ModelEar;
    case Wrist:
      return GearModelSlot::ModelWrist;
    case Ring1:
      return GearModelSlot::ModelRing1;
    case Ring2:
      return GearModelSlot::ModelRing2;
  }
}

// equip an item
void Player::equipItem( Common::GearSetSlot equipSlotId, Item& item, bool sendUpdate )
{
  switch( equipSlotId )
  {
    case MainHand:
      equipWeapon( item );
      break;

    case SoulCrystal:
      equipSoulCrystal( item );
      break;

    default:
      break;
  }

  updateModels( equipSlotId, item );

  calculateStats();
  calculateItemLevel();
  if( sendUpdate )
  {
    Network::Util::Packet::sendEquip( *this );
    Network::Util::Packet::sendActorControl( *this, SetItemLevel, getItemLevel() );
    Network::Util::Packet::sendBaseParams( *this );
    Network::Util::Packet::sendHudParam( *this );
  }
}


void Player::unequipItem( Common::GearSetSlot equipSlotId, Item& item, bool sendUpdate )
{
  auto modelSlot = equipSlotToModelSlot( equipSlotId );
  if( modelSlot != GearModelSlot::ModelInvalid )
    m_modelEquip[ static_cast< uint8_t >( modelSlot ) ] = 0;

  if ( equipSlotId == SoulCrystal )
    unequipSoulCrystal();

  calculateStats();
  calculateItemLevel();

  if( sendUpdate )
  {
    Network::Util::Packet::sendEquip( *this );
    Network::Util::Packet::sendActorControl( *this, SetItemLevel, getItemLevel() );
    Network::Util::Packet::sendBaseParams( *this );
    Network::Util::Packet::sendHudParam( *this );
  }
}

void Player::unequipSoulCrystal()
{
  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();

  auto currentClassJob = exdData.getRow< Excel::ClassJob >( static_cast< uint32_t >( getClass() ) );
  auto parentClass = static_cast< ClassJob >( currentClassJob->data().MainClass );
  setClassJob( parentClass );
}

uint32_t Player::currencyTypeToItem( Common::CurrencyType type ) const
{
  switch( type )
  {
    case Common::CurrencyType::Gil:
      return 1;
    case Common::CurrencyType::StormSeal:
      return 20;
    case Common::CurrencyType::SerpentSeal:
      return 21;
    case Common::CurrencyType::FlameSeal:
      return 22;
    case Common::CurrencyType::TomestonePhilo:
      return 23;
    case Common::CurrencyType::TomestoneMytho:
      return 24;
    case Common::CurrencyType::WolfMark:
      return 25;
    case Common::CurrencyType::TomestoneSold:
      return 26;
    case Common::CurrencyType::AlliedSeal:
      return 27;
    case Common::CurrencyType::Mgp:
      return 29;
    case Common::CurrencyType::TomestonePoet:
      return 28;
    case Common::CurrencyType::TomestoneLaw:
      return 30;
    case Common::CurrencyType::TomestoneEso:
      return 31;
    case Common::CurrencyType::TomestoneLore:
      return 32;
    default:
      return 0;
  }
}

// TODO: these next functions are so similar that they could likely be simplified
void Player::addCurrency( CurrencyType type, uint32_t amount )
{
  auto slot = static_cast< uint8_t >( static_cast< uint8_t >( type ) - 1 );
  auto currItem = m_storageMap[ Currency ]->getItem( slot );

  if( !currItem )
  {
    currItem = createItem( currencyTypeToItem( type ) );
    m_storageMap[ Currency ]->setItem( slot, currItem );
  }

  uint32_t currentAmount = currItem->getStackSize();
  currItem->setStackSize( currentAmount + amount );
  writeCurrencyItem( type );

  updateContainer( Currency, slot, currItem );

  auto seq = getNextInventorySequence();

  auto invUpdate = makeZonePacket< FFXIVIpcItemOperation >( getId() );
  invUpdate->data().contextId = seq;
  invUpdate->data().srcStorageId = Common::InventoryType::Currency;
  invUpdate->data().srcStack = currItem->getStackSize();
  invUpdate->data().srcContainerIndex = static_cast< int16_t >( type ) - 1;
  invUpdate->data().srcEntity = getId();
  invUpdate->data().srcCatalogId = currItem->getId();
  invUpdate->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;

  server().queueForPlayer( getCharacterId(), invUpdate );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = seq;
  invTransFinPacket->data().operationId = seq;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;

  server().queueForPlayer( getCharacterId(), invTransFinPacket );
}

void Player::removeCurrency( Common::CurrencyType type, uint32_t amount )
{

  auto currItem = m_storageMap[ Currency ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return;

  uint32_t currentAmount = currItem->getStackSize();
  if( amount > currentAmount )
    currItem->setStackSize( 0 );
  else
    currItem->setStackSize( currentAmount - amount );
  writeCurrencyItem( type );

  auto seq = getNextInventorySequence();

  auto invUpdate = makeZonePacket< FFXIVIpcItemOperation >( getId() );
  invUpdate->data().contextId = seq;
  invUpdate->data().srcStorageId = Common::InventoryType::Currency;
  invUpdate->data().srcStack = currItem->getStackSize();
  invUpdate->data().srcContainerIndex = static_cast< int16_t >( type ) - 1;
  invUpdate->data().srcCatalogId = currItem->getId();
  invUpdate->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invUpdate );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = seq;
  invTransFinPacket->data().operationId = seq;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invTransFinPacket );
}


void Player::addCrystal( Common::CrystalType type, uint32_t amount )
{
  auto currItem = m_storageMap[ Crystal ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
  {
    // TODO: map currency type to itemid
    currItem = createItem( static_cast< uint8_t >( type ) + 1 );
    m_storageMap[ Crystal ]->setItem( static_cast< uint8_t >( type ) - 1, currItem );
  }

  uint32_t currentAmount = currItem->getStackSize();

  currItem->setStackSize( currentAmount + amount );

  writeItem( currItem );

  writeInventory( Crystal );

  auto seq = getNextInventorySequence();

  auto invUpdate = makeZonePacket< FFXIVIpcItemOperation >( getId() );
  invUpdate->data().contextId = seq;
  invUpdate->data().srcStorageId = Common::InventoryType::Currency;
  invUpdate->data().srcStack = currItem->getStackSize();
  invUpdate->data().srcContainerIndex = static_cast< int16_t >( type ) - 1;
  invUpdate->data().srcEntity = getId();
  invUpdate->data().srcCatalogId = currItem->getId();
  invUpdate->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invUpdate );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = seq;
  invTransFinPacket->data().operationId = seq;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invTransFinPacket );
  server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), ItemObtainIcon, static_cast< uint8_t >( type ) + 1, amount ) );
}

void Player::removeCrystal( Common::CrystalType type, uint32_t amount )
{
  auto currItem = m_storageMap[ Crystal ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return;

  uint32_t currentAmount = currItem->getStackSize();
  if( amount > currentAmount )
    currItem->setStackSize( 0 );
  else
    currItem->setStackSize( currentAmount - amount );

  writeItem( currItem );

  auto seq = getNextInventorySequence();

  auto invUpdate = makeZonePacket< FFXIVIpcItemOperation >( getId() );
  invUpdate->data().contextId = seq;
  invUpdate->data().srcStorageId = Common::InventoryType::Currency;
  invUpdate->data().srcStack = currItem->getStackSize();
  invUpdate->data().srcContainerIndex = static_cast< int16_t >( type ) - 1;
  invUpdate->data().srcEntity = getId();
  invUpdate->data().srcCatalogId = currItem->getId();
  invUpdate->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invUpdate );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = seq;
  invTransFinPacket->data().operationId = seq;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invTransFinPacket );
}

void Player::sendInventory()
{
  auto& invMgr = Common::Service< Manager::InventoryMgr >::ref();

  for( auto& it : m_storageMap )
  {
    invMgr.sendInventoryContainer( *this, it.second );
  }
}

void Player::sendGearInventory()
{
  auto& invMgr = Common::Service< Manager::InventoryMgr >::ref();

  invMgr.sendInventoryContainer( *this, m_storageMap[ GearSet0 ] );
}

Player::InvSlotPairVec Player::getSlotsOfItemsInInventory( uint32_t catalogId )
{
  InvSlotPairVec outVec;
  for( auto i : { Bag0, Bag1, Bag2, Bag3 } )
  {
    auto inv = m_storageMap[ i ];
    for( const auto& item : inv->getItemMap() )
    {
      if( item.second && item.second->getId() == catalogId )
        outVec.push_back( std::make_pair( i, static_cast< int8_t >( item.first ) ) );
    }
  }
  return outVec;
}

Player::InvSlotPair Player::getFreeBagSlot()
{
  for( auto i : { Bag0, Bag1, Bag2, Bag3 } )
  {
    auto freeSlot = static_cast< int8_t >( m_storageMap[ i ]->getFreeSlot() );

    if( freeSlot != -1 )
      return std::make_pair( i, freeSlot );
  }
  // no room in inventory
  return std::make_pair( 0, -1 );
}

Player::InvSlotPair Player::getFreeContainerSlot( uint32_t containerId )
{
  auto freeSlot = static_cast< int8_t >( m_storageMap[ containerId ]->getFreeSlot() );

  if( freeSlot != -1 )
      return std::make_pair( containerId, freeSlot );

  // no room in inventory
  return std::make_pair( 0, -1 );
}

ItemPtr Player::getItemAt( uint16_t containerId, uint16_t slotId )
{
  return m_storageMap[ containerId ]->getItem( slotId );
}


uint32_t Player::getCurrency( CurrencyType type )
{

  auto currItem = m_storageMap[ Currency ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return 0;

  return currItem->getStackSize();

}

uint32_t Player::getCrystal( CrystalType type )
{

  auto currItem = m_storageMap[ Crystal ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return 0;

  return currItem->getStackSize();

}

void Player::writeInventory( InventoryType type )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto storage = m_storageMap[ type ];

  if( !storage->isPersistentStorage() )
    return;

  std::string query = "UPDATE " + storage->getTableName() + " SET ";

  for( int32_t i = 0; i <= storage->getMaxSize(); i++ )
  {
    auto currItem = storage->getItem( i );

    if( i > 0 )
      query += ", ";

    query += "container_" + std::to_string( i ) + " = " + std::to_string(  currItem ? currItem->getUId() : 0 );
  }

  query += " WHERE CharacterId = " + std::to_string( getCharacterId() );

  if( storage->isMultiStorage() )
    query += " AND storageId = " + std::to_string( static_cast< uint16_t >( type ) );

  db.execute( query );
}

void Player::writeItem( ItemPtr pItem ) const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::CHARA_ITEMGLOBAL_UP );

  // todo: add more fields
  stmt->setInt( 1, pItem->getStackSize() );
  stmt->setInt( 2, pItem->getDurability() );
  stmt->setInt( 3, pItem->getStain() );
  stmt->setInt( 4, pItem->getPattern() );

  stmt->setInt64( 5, pItem->getUId() );

  db.directExecute( stmt );
}

void Player::writeCurrencyItem( CurrencyType type )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto money = m_storageMap[ Currency ]->getItem( static_cast< uint16_t >( type ) - 1 )->getStackSize();

  std::string query = fmt::format(
    "UPDATE charaitemcurrency SET container_{0} = {1} WHERE CharacterId = {2};",
    std::to_string( static_cast< int16_t >( type ) - 1 ), std::to_string( money ), std::to_string( getCharacterId() ) );

  db.execute( query );
}

void Player::deleteItemDb( ItemPtr item ) const
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::CHARA_ITEMGLOBAL_DELETE );

  stmt->setInt64( 1, item->getUId() );

  db.directExecute( stmt );
}


bool Player::isObtainable( uint32_t catalogId, uint8_t quantity )
{

  return true;
}


ItemPtr Player::addItem( uint32_t catalogId, uint32_t quantity, bool isHq, bool silent, bool canMerge )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto itemInfo = exdData.getRow< Excel::Item >( catalogId );

  // if item data doesn't exist or it's a blank field
  if( !itemInfo || itemInfo->data().EquipLevel == 0 )
  {
    return nullptr;
  }

  quantity = std::min< uint32_t >( quantity, itemInfo->data().StackMax );

  // used for item obtain notification
  uint32_t originalQuantity = quantity;

  std::pair< uint16_t, uint8_t > freeBagSlot;
  bool foundFreeSlot = false;

  std::vector< uint16_t > bags = { Bag0, Bag1, Bag2, Bag3 };

  // add the related armoury bag to the applicable bags and try and fill a free slot there before falling back to regular inventory
  // EXD TODO: wtf...
  if( itemInfo->data().Slot > 0 && getConfigFlags() & StoreNewItemsInArmouryChest )
  {
    auto bag = World::Manager::ItemMgr::getCharaEquipSlotCategoryToArmoryId( itemInfo->data().Slot );

    bags.insert( bags.begin(), bag );
  }

  for( auto bag : bags )
  {
    auto storage = m_storageMap[ bag ];

    for( uint16_t slot = 0; slot < storage->getMaxSize(); slot++ )
    {
      if( !canMerge && foundFreeSlot )
        break;

      auto item = storage->getItem( slot );

      // add any items that are stackable
      if( canMerge && item && item->getMaxStackSize() > 0 && item->getId() == catalogId )
      {
        uint32_t count = item->getStackSize();
        uint32_t maxStack = item->getMaxStackSize();

        // if slot is full, skip it
        if( count >= maxStack )
          continue;

        // check slot is same quality
        if( item->isHq() != isHq )
          continue;

        // update stack
        uint32_t newStackSize = count + quantity;
        if( newStackSize > maxStack )
        {
          quantity = newStackSize - maxStack;
          newStackSize = maxStack;
        }
        else
          quantity = 0;

        item->setStackSize( newStackSize );
        writeItem( item );

        auto seq = getNextInventorySequence();

        auto slotUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(), slot, bag, *item, seq );
        server().queueForPlayer( getCharacterId(), slotUpdate );

        auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
        invTransFinPacket->data().contextId = seq;
        invTransFinPacket->data().operationId = seq;
        invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
        server().queueForPlayer( getCharacterId(), invTransFinPacket );

        // return existing stack if we have no overflow - items fit into a preexisting stack
        if( quantity == 0 )
        {
          server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), ItemObtainIcon, catalogId, originalQuantity ) );
          return item;
        }

      }
      else if( !item && !foundFreeSlot )
      {
        freeBagSlot = { bag, slot };
        foundFreeSlot = true;
      }
    }
  }

  // couldn't find a free slot and we still have some quantity of items left, shits fucked
  if( !foundFreeSlot )
    return nullptr;

  auto item = createItem( catalogId, quantity );
  item->setHq( isHq );

  auto storage = m_storageMap[ freeBagSlot.first ];
  storage->setItem( freeBagSlot.second, item );

  writeInventory( static_cast< InventoryType >( freeBagSlot.first ) );

  if( !silent )
  {
    auto seq = getNextInventorySequence();

    // send inv update
    auto invTransPacket = makeZonePacket< FFXIVIpcItemOperation >( getId() );
    invTransPacket->data().contextId = seq;
    invTransPacket->data().dstEntity = getId();
    invTransPacket->data().dstStorageId = freeBagSlot.first;
    invTransPacket->data().dstCatalogId = item->getId();
    invTransPacket->data().dstStack = item->getStackSize();
    invTransPacket->data().dstContainerIndex = freeBagSlot.second;
    invTransPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_CREATEITEM;
    server().queueForPlayer( getCharacterId(), invTransPacket );

    auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
    invTransFinPacket->data().contextId = seq;
    invTransFinPacket->data().operationId = seq;
    invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_CREATEITEM;
    server().queueForPlayer( getCharacterId(), invTransFinPacket );
    server().queueForPlayer( getCharacterId(), makeActorControlSelf( getId(), ItemObtainIcon, catalogId, originalQuantity ) );
  }

  return item;
}

bool Player::removeItem( uint32_t catalogId, uint32_t quantity, bool isHq )
{
  std::vector< uint16_t > bags = { Bag0, Bag1, Bag2, Bag3 };

  for( auto bag : bags )
  {
    auto storage = m_storageMap[ bag ];

    for( uint16_t slot = 0; slot < storage->getMaxSize(); slot++ )
    {
      if( quantity == 0 )
        break;

      auto item = storage->getItem( slot );

      // remove any matching items
      if( item && item->getId() == catalogId )
      {
        uint32_t count = item->getStackSize();
        uint32_t maxStack = item->getMaxStackSize();

        // check slot is same quality
        if( item->isHq() != isHq )
          continue;

        // update stack
        int32_t newStackSize = count - quantity;
        if( newStackSize <= 0 )
        {
          quantity = std::abs( newStackSize );
          discardItem( bag, slot );
        }
        else
        {
          quantity = 0;
          item->setStackSize( newStackSize );
          
          insertInventoryItem( static_cast< Sapphire::Common::InventoryType >( bag ), slot, item );

          writeItem( item );          
        }
      }
    }
  }

  return quantity == 0;
}

void
Player::moveItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot )
{

  auto tmpItem = m_storageMap[ fromInventoryId ]->getItem( fromSlotId );
  auto& itemMap = m_storageMap[ fromInventoryId ]->getItemMap();

  if( tmpItem == nullptr )
    return;

  itemMap[ fromSlotId ].reset();

  m_storageMap[ toInventoryId ]->setItem( toSlot, tmpItem );

  writeInventory( static_cast< InventoryType >( toInventoryId ) );

  if( fromInventoryId != toInventoryId )
    writeInventory( static_cast< InventoryType >( fromInventoryId ) );

  if( static_cast< InventoryType >( toInventoryId ) == GearSet0 )
    equipItem( static_cast< GearSetSlot >( toSlot ), *tmpItem, true );

  if( static_cast< InventoryType >( fromInventoryId ) == GearSet0 )
    unequipItem( static_cast< GearSetSlot >( fromSlotId ), *tmpItem, true );

  if( static_cast< InventoryType >( toInventoryId ) == GearSet0 ||
      static_cast< InventoryType >( fromInventoryId ) == GearSet0 )
    sendStatusEffectUpdate(); // send if any equip is changed
}

bool Player::updateContainer( uint16_t storageId, uint16_t slotId, ItemPtr pItem )
{
  auto containerType = Manager::ItemMgr::getContainerType( storageId );

  auto pOldItem = getItemAt( storageId, slotId );
  m_storageMap[ storageId ]->setItem( slotId, pItem );

  switch( containerType )
  {
    case Armory:
    case Bag:
    case CurrencyCrystal:
    {
      writeInventory( static_cast< InventoryType >( storageId ) );
      break;
    }

    case GearSet:
    {
      if( pItem )
      {
        if( pOldItem )
          unequipItem( static_cast< GearSetSlot >( slotId ), *pOldItem, false );
        equipItem( static_cast< GearSetSlot >( slotId ), *pItem, true );
      }
      else
        unequipItem( static_cast< GearSetSlot >( slotId ), *pItem, true );

      writeInventory( static_cast< InventoryType >( storageId ) );
      break;
    }
    default:
      break;
  }

  return true;
}

void Player::splitItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot, uint16_t itemCount )
{
  if( itemCount == 0 )
    return;

  auto fromItem = m_storageMap[ fromInventoryId ]->getItem( fromSlotId );
  if( !fromItem )
    return;

  // check we have enough items in the origin slot
  // nb: don't let the client 'split' a whole stack into another slot
  if( fromItem->getStackSize() < itemCount )
    // todo: correct the invalid item split? does retail do this or does it just ignore it?
    return;

  // make sure toInventoryId & toSlot are actually free so we don't orphan an item
  if( m_storageMap[ toInventoryId ]->getItem( toSlot ) )
    // todo: correct invalid move? again, not sure what retail does here
    return;

  auto newItem = addItem( fromItem->getId(), itemCount, fromItem->isHq(), true, false );
  if( !newItem )
    return;

  fromItem->setStackSize( fromItem->getStackSize() - itemCount );

  updateContainer( fromInventoryId, fromSlotId, fromItem );
  updateContainer( toInventoryId, toSlot, newItem );

  writeItem( fromItem );
}

void Player::mergeItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot )
{
  auto fromItem = m_storageMap[ fromInventoryId ]->getItem( fromSlotId );
  auto toItem = m_storageMap[ toInventoryId ]->getItem( toSlot );

  if( !fromItem || !toItem )
    return;

  if( fromItem->getId() != toItem->getId() )
    return;

  uint32_t stackSize = fromItem->getStackSize() + toItem->getStackSize();
  uint32_t stackOverflow = stackSize - std::min< uint32_t >( fromItem->getMaxStackSize(), stackSize );

  // we can destroy the original stack if there's no overflow
  if( stackOverflow == 0 )
  {
    m_storageMap[ fromInventoryId ]->removeItem( fromSlotId );
    deleteItemDb( fromItem );
  }
  else
  {
    fromItem->setStackSize( stackOverflow );
    writeItem( fromItem );
  }


  toItem->setStackSize( stackSize );
  writeItem( toItem );

  updateContainer( fromInventoryId, fromSlotId, fromItem );
  updateContainer( toInventoryId, toSlot, toItem );
}

void Player::swapItem( uint16_t fromInventoryId, uint16_t fromSlotId, uint16_t toInventoryId, uint16_t toSlot )
{
  auto fromItem = m_storageMap[ fromInventoryId ]->getItem( fromSlotId );
  auto toItem = m_storageMap[ toInventoryId ]->getItem( toSlot );
  auto& itemMap = m_storageMap[ fromInventoryId ]->getItemMap();

  if( fromItem == nullptr || toItem == nullptr )
    return;

  // An item is being moved from bag0-3 to equippment, meaning
  // the swapped out item will be placed in the matching armory.
  if( World::Manager::ItemMgr::isEquipment( toInventoryId )
      && !World::Manager::ItemMgr::isEquipment( fromInventoryId )
      && !World::Manager::ItemMgr::isArmory( fromInventoryId ) )
  {
    updateContainer( fromInventoryId, fromSlotId, nullptr );
    auto& exdData = Common::Service< Data::ExdData >::ref();
    auto itemInfo = exdData.getRow< Excel::Item >( toItem->getId() );
    fromInventoryId = World::Manager::ItemMgr::getCharaEquipSlotCategoryToArmoryId( static_cast< Common::EquipSlotCategory >( itemInfo->data().Slot ) );
    fromSlotId = static_cast < uint8_t >( m_storageMap[ fromInventoryId ]->getFreeSlot() );
  }

  auto containerTypeFrom = World::Manager::ItemMgr::getContainerType( fromInventoryId );
  auto containerTypeTo = World::Manager::ItemMgr::getContainerType( toInventoryId );

  updateContainer( toInventoryId, toSlot, fromItem );
  updateContainer( fromInventoryId, fromSlotId, toItem );

  if( static_cast< InventoryType >( toInventoryId ) == GearSet0 ||
    static_cast< InventoryType >( fromInventoryId ) == GearSet0 )
    sendStatusEffectUpdate(); // send if any equip is changed
}

void Player::discardItem( uint16_t fromInventoryId, uint16_t fromSlotId )
{
  // i am not entirely sure how this should be generated or if it even is important for us...
  uint32_t sequence = getNextInventorySequence();

  auto fromItem = m_storageMap[ fromInventoryId ]->getItem( fromSlotId );

  deleteItemDb( fromItem );

  m_storageMap[ fromInventoryId ]->removeItem( fromSlotId );
  updateContainer( fromInventoryId, fromSlotId, nullptr );

  auto invTransPacket = makeZonePacket< FFXIVIpcItemOperation >( getId() );
  invTransPacket->data().contextId = sequence;
  invTransPacket->data().srcEntity = getId();
  invTransPacket->data().srcStorageId = fromInventoryId;
  invTransPacket->data().srcCatalogId = fromItem->getId();
  invTransPacket->data().srcStack = fromItem->getStackSize();
  invTransPacket->data().srcContainerIndex = fromSlotId;
  invTransPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_DELETEITEM;
  server().queueForPlayer( getCharacterId(), invTransPacket );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = sequence;
  invTransFinPacket->data().operationId = sequence;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_DELETEITEM;
  server().queueForPlayer( getCharacterId(), invTransFinPacket );
}

uint16_t Player::calculateItemLevel()
{
  uint32_t iLvlResult = 0;

  auto gearSetMap = m_storageMap[ GearSet0 ]->getItemMap();

  auto it = gearSetMap.begin();

  while( it != gearSetMap.end() )
  {
    auto currItem = it->second;

    if( currItem && currItem->getCategory() != Common::ItemUICategory::SoulCrystal )
    {
      iLvlResult += currItem->getItemLevel();

      // If item is weapon and isn't one-handed
      if( currItem->isWeapon() && !World::Manager::ItemMgr::isOneHandedWeapon( currItem->getCategory() ) )
      {
        iLvlResult += currItem->getItemLevel();
      }
    }

    it++;
  }

  uint16_t ilvl = static_cast< uint16_t >( std::min( static_cast< int32_t >( iLvlResult / 13 ), 9999 ) );

  m_itemLevel = ilvl;
  return ilvl;
}

void Player::calculateBonusStats()
{
  m_bonusStats.fill( 0 );

  auto gearSetMap = m_storageMap[ GearSet0 ]->getItemMap();

  auto it = gearSetMap.begin();

  while( it != gearSetMap.end() )
  {
    auto pItem = it->second;

    if( pItem && pItem->getCategory() != Common::ItemUICategory::SoulCrystal )
    {
      auto baseParams = pItem->getBaseParams();
      for( auto i = 0; i < 6; ++i )
      {
        auto itemBaseParam = baseParams[ i ].baseParam;
        auto itemBaseVal = baseParams[ i ].value;
        if( itemBaseParam != static_cast< uint8_t >( Common::BaseParam::None ) )
          m_bonusStats[ itemBaseParam ] += itemBaseVal;
      }

      m_bonusStats[ static_cast< uint8_t >( Common::BaseParam::Defense ) ] += pItem->getDefense();
      m_bonusStats[ static_cast< uint8_t >( Common::BaseParam::MagicDefense ) ] += pItem->getDefenseMag();
    }

    it++;
  }
}


ItemPtr Player::getEquippedWeapon()
{
  return m_storageMap[ GearSet0 ]->getItem( GearSetSlot::MainHand );
}

uint16_t Player::getFreeSlotsInBags()
{
  uint16_t slots = 0;
  for( uint8_t container : { Bag0, Bag1, Bag2, Bag3 } )
  {
    const auto& storage = m_storageMap[ container ];
    slots += ( storage->getMaxSize() - storage->getEntryCount() );
  }
  return slots;
}

bool Player::collectHandInItems( std::vector< uint32_t > itemIds )
{
  // todo: figure out how the game gets the required stack count
  const auto& container = m_storageMap[ HandIn ];

  std::vector< uint8_t > foundItems;

  auto itemMap = container->getItemMap();

  for( auto& item : itemMap )
  {
    for( auto needle : itemIds )
    {
      if( item.second->getId() == needle )
      {
        foundItems.push_back( item.first );
        break;
      }
    }
  }

  // couldn't find all the items required
  if( foundItems.size() != itemIds.size() )
    return false;

  // remove items
  for( auto item : foundItems )
  {
    container->removeItem( item );
  }

  return true;
}

uint32_t Player::getNextInventorySequence()
{
  return m_inventorySequence++;
}

ItemPtr Player::dropInventoryItem( Sapphire::Common::InventoryType storageId, uint8_t slotId )
{
  auto& container = m_storageMap[ storageId ];

  auto item = container->getItem( slotId );
  if( !item )
    return nullptr;

  // unlink item
  container->removeItem( slotId, false );
  updateContainer( storageId, slotId, nullptr );

  auto seq = getNextInventorySequence();

  // send inv update
  auto invTransPacket = makeZonePacket< FFXIVIpcItemOperation >( getId() );
  invTransPacket->data().contextId = seq;
  invTransPacket->data().dstEntity = getId();
  invTransPacket->data().dstStorageId = storageId;
  invTransPacket->data().dstCatalogId = item->getId();
  invTransPacket->data().dstStack = item->getStackSize();
  invTransPacket->data().dstContainerIndex = slotId;
  invTransPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_DELETEITEM;
  server().queueForPlayer( getCharacterId(), invTransPacket );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = seq;
  invTransFinPacket->data().operationId = seq;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_DELETEITEM;
  server().queueForPlayer( getCharacterId(), invTransFinPacket );

  return item;
}

void Player::addSoldItem( uint32_t itemId, uint8_t stackSize )
{
  if( m_soldItems.size() > 10 )
    m_soldItems.pop_back();
  m_soldItems.emplace_front( itemId, stackSize );
}

std::deque< std::pair< uint32_t, uint8_t > >* Player::getSoldItems()
{
  return &m_soldItems;
}

void Player::clearSoldItems()
{
  m_soldItems.clear();
}

bool Player::getFreeInventoryContainerSlot( Inventory::InventoryContainerPair& containerPair ) const
{
  for( auto bagId : { Bag0, Bag1, Bag2, Bag3 } )
  {
    auto needle = m_storageMap.find( bagId );
    if( needle == m_storageMap.end() )
      continue;

    auto& container = needle->second;

    for( uint16_t idx = 0; idx < container->getMaxSize(); idx++ )
    {
      auto item = container->getItem( idx );
      if( !item )
      {
        containerPair = std::make_pair( bagId, idx );
        return true;
      }
    }
  }

  return false;
}

void Player::insertInventoryItem( Common::InventoryType type, uint16_t slot, const ItemPtr item )
{
  updateContainer( type, slot, item );

  auto seq = getNextInventorySequence();

  auto slotUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(), slot, type, *item, seq );
  server().queueForPlayer( getCharacterId(), slotUpdate );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( getId() );
  invTransFinPacket->data().contextId = seq;
  invTransFinPacket->data().operationId = seq;
  invTransFinPacket->data().operationType = Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_UPDATEITEM;
  server().queueForPlayer( getCharacterId(), invTransFinPacket );
}

bool Player::findFirstItemWithId( uint32_t catalogId, Inventory::InventoryContainerPair& location, std::initializer_list< InventoryType > bags )
{
  for( auto bagId : bags )
  {
    auto& container = m_storageMap[ bagId ];

    for( const auto& item : container->getItemMap() )
    {
      if( ( item.second && item.second->getId() != catalogId ) || !item.second )
        continue;

      location = std::make_pair( bagId, item.first );

      return true;
    }
  }

  return false;
}
