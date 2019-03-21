#include <Common.h>
#include <Logging/Logger.h>
#include <Network/CommonActorControl.h>
#include <algorithm>

#include "Territory/Zone.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/UpdateInventorySlotPacket.h"

#include "Inventory/Item.h"
#include "Inventory/ItemContainer.h"


#include "Player.h"
#include "Framework.h"

#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>

#include "Actor/Player.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

#include "Manager/InventoryMgr.h"
#include "Manager/ItemMgr.h"

#include "Framework.h"
#include <Network/CommonActorControl.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;


void Sapphire::Entity::Player::initInventory()
{
  auto setupContainer = [ this ]( InventoryType type, uint8_t maxSize, const std::string& tableName,
                                  bool isMultiStorage, bool isPersistentStorage = true )
  { m_storageMap[ type ] = make_ItemContainer( type, maxSize, tableName, isMultiStorage, m_pFw, isPersistentStorage ); };

  // main bags
  setupContainer( Bag0, 34, "charaiteminventory", true );
  setupContainer( Bag1, 34, "charaiteminventory", true );
  setupContainer( Bag2, 34, "charaiteminventory", true );
  setupContainer( Bag3, 34, "charaiteminventory", true );

  // gear set
  setupContainer( GearSet0, 13, "charaitemgearset", true );

  // gil contianer
  setupContainer( Currency, 11, "charaiteminventory", true );

  // crystals??
  setupContainer( Crystal, 11, "charaiteminventory", true );

  // armory weapons - 0
  setupContainer( ArmoryMain, 34, "charaiteminventory", true );

  // armory offhand - 1
  setupContainer( ArmoryOff, 34, "charaiteminventory", true );

  //armory head - 2
  setupContainer( ArmoryHead, 34, "charaiteminventory", true );

  //armory body - 3
  setupContainer( ArmoryBody, 34, "charaiteminventory", true );

  //armory hand - 4
  setupContainer( ArmoryHand, 34, "charaiteminventory", true );

  //armory waist - 5
  setupContainer( ArmoryWaist, 34, "charaiteminventory", true );

  //armory legs - 6
  setupContainer( ArmoryLegs, 34, "charaiteminventory", true );

  //armory feet - 7
  setupContainer( ArmoryFeet, 34, "charaiteminventory", true );

  //neck
  setupContainer( ArmoryNeck, 34, "charaiteminventory", true );

  //earring
  setupContainer( ArmoryEar, 34, "charaiteminventory", true );

  //wrist
  setupContainer( ArmoryWrist, 34, "charaiteminventory", true );

  //armory rings - 11
  setupContainer( ArmoryRing, 34, "charaiteminventory", true );

  //soul crystals - 13
  setupContainer( ArmorySoulCrystal, 34, "charaiteminventory", true );

  // item hand in container
  // non-persistent container, will not save its contents
  setupContainer( HandIn, 10, "", true, false );

  loadInventory();

}

void Sapphire::Entity::Player::sendItemLevel()
{
  queuePacket( makeActorControl142( getId(), SetItemLevel, getItemLevel(), 0 ) );
}

void Sapphire::Entity::Player::equipWeapon( ItemPtr pItem, bool updateClass )
{
  auto exdData = m_pFw->get< Sapphire::Data::ExdDataGenerated >();
  if( !exdData )
    return;

  auto itemInfo = exdData->get< Sapphire::Data::Item >( pItem->getId() );
  auto itemClassJob = itemInfo->classJobUse;
  auto classJobInfo = exdData->get< Sapphire::Data::ClassJob >( static_cast< uint32_t >( getClass() ) );
  auto currentParentClass = static_cast< ClassJob >( classJobInfo->classJobParent );
  auto newClassJob = static_cast< ClassJob >( itemClassJob );

  if( ( isClassJobUnlocked( newClassJob ) ) && ( currentParentClass != newClassJob ) )
  {
    if ( updateClass )
      setClassJob( newClassJob );
    else
      return;
  }
}

void Sapphire::Entity::Player::equipSoulCrystal( ItemPtr pItem, bool updateJob )
{
  auto exdData = m_pFw->get< Sapphire::Data::ExdDataGenerated >();
  if ( !exdData )
    return;

  auto itemInfo = exdData->get< Sapphire::Data::Item >( pItem->getId() );
  auto itemClassJob = itemInfo->classJobUse;
  auto newClassJob = static_cast< ClassJob >( itemClassJob );

  if ( isClassJobUnlocked( newClassJob ) && updateJob )
    setClassJob( newClassJob );
}

void Sapphire::Entity::Player::updateModels( GearSetSlot equipSlotId, const Sapphire::ItemPtr& pItem, bool updateClass )
{
  uint64_t model = pItem->getModelId1();
  uint64_t model2 = pItem->getModelId2();

  switch( equipSlotId )
  {
    case MainHand:
      m_modelMainWeapon = model;
      m_modelSubWeapon = model2;
      equipWeapon( pItem, updateClass );
      break;

    case OffHand:
      m_modelSubWeapon = model;
      break;

    case SoulCrystal:
      equipSoulCrystal( pItem, updateClass );
      break;

    case Waist:
      break;

    default: // any other slot
      auto modelSlot = equipSlotToModelSlot( equipSlotId );
      if( modelSlot == GearModelSlot::ModelInvalid )
        break;
      m_modelEquip[ static_cast< uint8_t >( modelSlot ) ] = static_cast< uint32_t >( model );
      break;

  }
}

Sapphire::Common::GearModelSlot Sapphire::Entity::Player::equipSlotToModelSlot( Common::GearSetSlot slot )
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
void Sapphire::Entity::Player::equipItem( Common::GearSetSlot equipSlotId, ItemPtr pItem, bool sendUpdate )
{

  //g_framework.getLogger().debug( "Equipping into slot " + std::to_string( equipSlotId ) );
  if( sendUpdate )
  {
    updateModels( equipSlotId, pItem, true );
    sendModel();
    m_itemLevel = calculateEquippedGearItemLevel();
    sendItemLevel();
  }
  else
    updateModels( equipSlotId, pItem, false );

  auto baseParams = pItem->getBaseParams();
  for( auto i = 0; i < 6; ++i )
  {
    if( baseParams[ i ].baseParam != static_cast< uint8_t >( Common::BaseParam::None ) )
      m_bonusStats[ baseParams[ i ].baseParam ] += baseParams[ i ].value;
  }

  m_bonusStats[ static_cast< uint8_t >( Common::BaseParam::Defense ) ] += pItem->getDefense();
  m_bonusStats[ static_cast< uint8_t >( Common::BaseParam::MagicDefense ) ] += pItem->getDefenseMag();

  calculateStats();
  if( sendUpdate )
  {
    sendStats();
    sendStatusUpdate();
  }
}


void Sapphire::Entity::Player::unequipItem( Common::GearSetSlot equipSlotId, ItemPtr pItem, bool sendUpdate )
{
  auto modelSlot = equipSlotToModelSlot( equipSlotId );
  if( modelSlot != GearModelSlot::ModelInvalid )
    m_modelEquip[ static_cast< uint8_t >( modelSlot ) ] = 0;

  if( sendUpdate )
  {
    sendModel();

    m_itemLevel = calculateEquippedGearItemLevel();
    sendItemLevel();
  }

  if ( equipSlotId == SoulCrystal )
    unequipSoulCrystal( pItem );

  auto baseParams = pItem->getBaseParams();
  for( auto i = 0; i < 6; ++i )
  {
    if( baseParams[ i ].baseParam != static_cast< uint8_t >( Common::BaseParam::None ) )
      m_bonusStats[ baseParams[ i ].baseParam ] -= baseParams[ i ].value;
  }

  m_bonusStats[ static_cast< uint8_t >( Common::BaseParam::Defense ) ] -= pItem->getDefense();
  m_bonusStats[ static_cast< uint8_t >( Common::BaseParam::MagicDefense ) ] -= pItem->getDefenseMag();

  calculateStats();

  if( sendUpdate )
  {
    sendStats();
    sendStatusUpdate();
  }
}

void Sapphire::Entity::Player::unequipSoulCrystal( ItemPtr pItem )
{
  auto exdData = m_pFw->get< Sapphire::Data::ExdDataGenerated >();
  if ( !exdData )
    return;

  auto currentClassJob = exdData->get< Sapphire::Data::ClassJob >( static_cast< uint32_t >( getClass() ) );
  auto parentClass = static_cast< ClassJob >( currentClassJob->classJobParent );
  setClassJob( parentClass );
}

// TODO: these next functions are so similar that they could likely be simplified
void Sapphire::Entity::Player::addCurrency( CurrencyType type, uint32_t amount )
{
  auto slot = static_cast< uint8_t >( static_cast< uint8_t >( type ) - 1 );
  auto currItem = m_storageMap[ Currency ]->getItem( slot );

  if( !currItem )
  {
    // TODO: map currency type to itemid
    currItem = createItem( 1 );
    m_storageMap[ Currency ]->setItem( slot, currItem );
  }

  uint32_t currentAmount = currItem->getStackSize();
  currItem->setStackSize( currentAmount + amount );
  writeItem( currItem );

  updateContainer( Currency, slot, currItem );

  auto invUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(),
                                                                    static_cast< uint8_t >( type ) - 1,
                                                                    Common::InventoryType::Currency,
                                                                    *currItem );
  queuePacket( invUpdate );
}

void Sapphire::Entity::Player::removeCurrency( Common::CurrencyType type, uint32_t amount )
{

  auto currItem = m_storageMap[ Currency ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return;

  uint32_t currentAmount = currItem->getStackSize();
  if( amount > currentAmount )
    currItem->setStackSize( 0 );
  else
    currItem->setStackSize( currentAmount - amount );
  writeItem( currItem );

  auto invUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(),
                                                                    static_cast< uint8_t >( type ) - 1,
                                                                    Common::InventoryType::Currency,
                                                                    *currItem );
  queuePacket( invUpdate );
}


void Sapphire::Entity::Player::addCrystal( Common::CrystalType type, uint32_t amount )
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


  auto invUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(),
                                                                    static_cast< uint8_t >( type ) - 1,
                                                                    Common::InventoryType::Crystal,
                                                                    *currItem );
  queuePacket( invUpdate );
  queuePacket( makeActorControl143( getId(), ItemObtainIcon, static_cast< uint8_t >( type ) + 1, amount ) );
}

void Sapphire::Entity::Player::removeCrystal( Common::CrystalType type, uint32_t amount )
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

  auto invUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(),
                                                                    static_cast< uint8_t >( type ) - 1,
                                                                    Common::InventoryType::Crystal,
                                                                    *currItem );
  queuePacket( invUpdate );
}

void Sapphire::Entity::Player::sendInventory()
{
  auto pInvMgr = m_pFw->get< World::Manager::InventoryMgr >();

  for( auto it = m_storageMap.begin(); it != m_storageMap.end(); ++it )
  {
    pInvMgr->sendInventoryContainer( *this, it->second );
  }
}

Sapphire::Entity::Player::InvSlotPairVec Sapphire::Entity::Player::getSlotsOfItemsInInventory( uint32_t catalogId )
{
  InvSlotPairVec outVec;
  for( auto i : { Bag0, Bag1, Bag2, Bag3 } )
  {
    auto inv = m_storageMap[ i ];
    for( auto item : inv->getItemMap() )
    {
      if( item.second && item.second->getId() == catalogId )
        outVec.push_back( std::make_pair( i, static_cast< int8_t >( item.first ) ) );
    }
  }
  return outVec;
}

Sapphire::Entity::Player::InvSlotPair Sapphire::Entity::Player::getFreeBagSlot()
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

Sapphire::ItemPtr Sapphire::Entity::Player::getItemAt( uint16_t containerId, uint8_t slotId )
{
  return m_storageMap[ containerId ]->getItem( slotId );
}


uint32_t Sapphire::Entity::Player::getCurrency( CurrencyType type )
{

  auto currItem = m_storageMap[ Currency ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return 0;

  return currItem->getStackSize();

}

uint32_t Sapphire::Entity::Player::getCrystal( CrystalType type )
{

  auto currItem = m_storageMap[ Crystal ]->getItem( static_cast< uint8_t >( type ) - 1 );

  if( !currItem )
    return 0;

  return currItem->getStackSize();

}

void Sapphire::Entity::Player::writeInventory( InventoryType type )
{
  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto storage = m_storageMap[ type ];

  if( !storage->isPersistentStorage() )
    return;

  std::string query = "UPDATE " + storage->getTableName() + " SET ";

  for( int32_t i = 0; i <= storage->getMaxSize(); i++ )
  {
    auto currItem = storage->getItem( i );

    if( i > 0 )
      query += ", ";

    query += "container_" + std::to_string( i ) + " = " + std::to_string( currItem ? currItem->getUId() : 0 );
  }

  query += " WHERE CharacterId = " + std::to_string( getId() );

  if( storage->isMultiStorage() )
    query += " AND storageId = " + std::to_string( static_cast< uint16_t >( type ) );

  pDb->execute( query );
}

void Sapphire::Entity::Player::writeItem( Sapphire::ItemPtr pItem ) const
{
  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto stmt = pDb->getPreparedStatement( Db::CHARA_ITEMGLOBAL_UP );

  // todo: add more fields
  stmt->setInt( 1, pItem->getStackSize() );
  stmt->setInt( 2, pItem->getDurability() );
  stmt->setInt( 3, pItem->getStain() );

  stmt->setInt64( 4, pItem->getUId() );

  pDb->directExecute( stmt );
}

void Sapphire::Entity::Player::deleteItemDb( Sapphire::ItemPtr item ) const
{
  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto stmt = pDb->getPreparedStatement( Db::CHARA_ITEMGLOBAL_DELETE );

  stmt->setInt64( 1, item->getUId() );

  pDb->directExecute( stmt );
}


bool Sapphire::Entity::Player::isObtainable( uint32_t catalogId, uint8_t quantity )
{

  return true;
}


Sapphire::ItemPtr Sapphire::Entity::Player::addItem( uint32_t catalogId, uint32_t quantity, bool isHq, bool silent )
{
  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto itemInfo = pExdData->get< Sapphire::Data::Item >( catalogId );

  // if item data doesn't exist or it's a blank field
  if( !itemInfo || itemInfo->levelItem == 0 )
  {
    return nullptr;
  }

  quantity = std::min< uint32_t >( quantity, itemInfo->stackSize );

  // used for item obtain notification
  uint32_t originalQuantity = quantity;

  std::pair< uint16_t, uint8_t > freeBagSlot;
  bool foundFreeSlot = false;

  std::vector< uint16_t > bags = { Bag0, Bag1, Bag2, Bag3 };

  // add the related armoury bag to the applicable bags and try and fill a free slot there before falling back to regular inventory
  if( itemInfo->isEquippable && getEquipDisplayFlags() & StoreNewItemsInArmouryChest )
  {
    auto bag = World::Manager::ItemMgr::getCharaEquipSlotCategoryToArmoryId( itemInfo->equipSlotCategory );

    bags.insert( bags.begin(), bag );
  }

  for( auto bag : bags )
  {
    auto storage = m_storageMap[ bag ];

    for( uint8_t slot = 0; slot < storage->getMaxSize(); slot++ )
    {
      auto item = storage->getItem( slot );

      // add any items that are stackable
      if( item && !itemInfo->isEquippable && item->getId() == catalogId )
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

        item->setStackSize( newStackSize );
        writeItem( item );

        auto slotUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(), slot, bag, *item );
        queuePacket( slotUpdate );

        // return existing stack if we have no overflow - items fit into a preexisting stack
        if( quantity == 0 )
        {
          queuePacket( makeActorControl143( getId(), ItemObtainIcon, catalogId, originalQuantity ) );

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
    auto invUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(), freeBagSlot.second, freeBagSlot.first,
                                                                      *item );
    queuePacket( invUpdate );

    queuePacket( makeActorControl143( getId(), ItemObtainIcon, catalogId, originalQuantity ) );
  }

  return item;
}

void
Sapphire::Entity::Player::moveItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot )
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
    equipItem( static_cast< GearSetSlot >( toSlot ), tmpItem, true );

  if( static_cast< InventoryType >( fromInventoryId ) == GearSet0 )
    unequipItem( static_cast< GearSetSlot >( fromSlotId ), tmpItem, true );


}

bool Sapphire::Entity::Player::updateContainer( uint16_t storageId, uint8_t slotId, ItemPtr pItem )
{
  auto containerType = World::Manager::ItemMgr::getContainerType( storageId );

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
          unequipItem( static_cast< GearSetSlot >( slotId ), pOldItem, false );
        equipItem( static_cast< GearSetSlot >( slotId ), pItem, true );
      }
      else
        unequipItem( static_cast< GearSetSlot >( slotId ), pItem, true );

      writeInventory( static_cast< InventoryType >( storageId ) );
      break;
    }
    default:
      break;
  }

  return true;
}

void Sapphire::Entity::Player::splitItem( uint16_t fromInventoryId, uint8_t fromSlotId,
                                          uint16_t toInventoryId, uint8_t toSlot, uint16_t itemCount )
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

  auto newItem = addItem( fromItem->getId(), itemCount, fromItem->isHq(), true );
  if( !newItem )
    return;

  fromItem->setStackSize( fromItem->getStackSize() - itemCount );

  updateContainer( fromInventoryId, fromSlotId, fromItem );
  updateContainer( toInventoryId, toSlot, newItem );

  writeItem( fromItem );
}

void Sapphire::Entity::Player::mergeItem( uint16_t fromInventoryId, uint8_t fromSlotId,
                                          uint16_t toInventoryId, uint8_t toSlot )
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

void Sapphire::Entity::Player::swapItem( uint16_t fromInventoryId, uint8_t fromSlotId,
                                         uint16_t toInventoryId, uint8_t toSlot )
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
    fromInventoryId = World::Manager::ItemMgr::getCharaEquipSlotCategoryToArmoryId( toSlot );
    fromSlotId = static_cast < uint8_t >( m_storageMap[ fromInventoryId ]->getFreeSlot() );
  }

  auto containerTypeFrom = World::Manager::ItemMgr::getContainerType( fromInventoryId );
  auto containerTypeTo = World::Manager::ItemMgr::getContainerType( toInventoryId );

  updateContainer( toInventoryId, toSlot, fromItem );
  updateContainer( fromInventoryId, fromSlotId, toItem );
}

void Sapphire::Entity::Player::discardItem( uint16_t fromInventoryId, uint8_t fromSlotId )
{
  // i am not entirely sure how this should be generated or if it even is important for us...
  uint32_t sequence = getNextInventorySequence();

  auto fromItem = m_storageMap[ fromInventoryId ]->getItem( fromSlotId );

  deleteItemDb( fromItem );

  m_storageMap[ fromInventoryId ]->removeItem( fromSlotId );
  updateContainer( fromInventoryId, fromSlotId, nullptr );

  auto invTransPacket = makeZonePacket< FFXIVIpcInventoryTransaction >( getId() );
  invTransPacket->data().sequence = sequence;
  invTransPacket->data().ownerId = getId();
  invTransPacket->data().storageId = fromInventoryId;
  invTransPacket->data().catalogId = fromItem->getId();
  invTransPacket->data().stackSize = fromItem->getStackSize();
  invTransPacket->data().slotId = fromSlotId;
  invTransPacket->data().type = 7;
  queuePacket( invTransPacket );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcInventoryTransactionFinish >( getId() );
  invTransFinPacket->data().sequenceId = sequence;
  invTransFinPacket->data().sequenceId1 = sequence;
  queuePacket( invTransFinPacket );
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

uint16_t Sapphire::Entity::Player::calculateEquippedGearItemLevel()
{
  uint32_t iLvlResult = 0;

  auto gearSetMap = m_storageMap[ GearSet0 ]->getItemMap();

  auto it = gearSetMap.begin();

  while( it != gearSetMap.end() )
  {
    auto currItem = it->second;

    if( currItem )
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

  return static_cast< uint16_t >( std::min( static_cast< int32_t >( iLvlResult / 13 ), 9999 ) );
}


uint8_t Sapphire::Entity::Player::getFreeSlotsInBags()
{
  uint8_t slots = 0;
  for( uint8_t container : { Bag0, Bag1, Bag2, Bag3 } )
  {
    const auto& storage = m_storageMap[ container ];
    slots += ( storage->getMaxSize() - storage->getEntryCount() );
  }
  return slots;
}

bool Sapphire::Entity::Player::collectHandInItems( std::vector< uint32_t > itemIds )
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

uint32_t Sapphire::Entity::Player::getNextInventorySequence()
{
  return m_inventorySequence++;
}

Sapphire::ItemPtr Sapphire::Entity::Player::dropInventoryItem( Sapphire::Common::InventoryType type, uint16_t slotId )
{
  auto& container = m_storageMap[ type ];

  auto item = container->getItem( slotId );
  if( !item )
    return nullptr;

  // unlink item
  container->removeItem( slotId, false );
  updateContainer( type, slotId, nullptr );

  auto seq = getNextInventorySequence();

  // send inv update
  auto invTransPacket = makeZonePacket< FFXIVIpcInventoryTransaction >( getId() );
  invTransPacket->data().sequence = seq;
  invTransPacket->data().ownerId = getId();
  invTransPacket->data().storageId = type;
  invTransPacket->data().catalogId = item->getId();
  invTransPacket->data().stackSize = item->getStackSize();
  invTransPacket->data().slotId = slotId;
  invTransPacket->data().type = 7;
  queuePacket( invTransPacket );

  auto invTransFinPacket = makeZonePacket< FFXIVIpcInventoryTransactionFinish >( getId() );
  invTransFinPacket->data().sequenceId = seq;
  invTransFinPacket->data().sequenceId1 = seq;
  queuePacket( invTransFinPacket );

  return item;
}

bool Sapphire::Entity::Player::getFreeInventoryContainerSlot( Inventory::InventoryContainerPair& containerPair ) const
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

void Sapphire::Entity::Player::insertInventoryItem( Sapphire::Common::InventoryType type, uint16_t slot,
                                                    const Sapphire::ItemPtr item )
{
  updateContainer( type, slot, item );

  auto slotUpdate = std::make_shared< UpdateInventorySlotPacket >( getId(), slot, type, *item );
  queuePacket( slotUpdate );

}

bool Sapphire::Entity::Player::findFirstItemWithId( uint32_t catalogId,
                                                    Inventory::InventoryContainerPair& location )
{
  for( auto bagId : { Bag0, Bag1, Bag2, Bag3 } )
  {
    auto& container = m_storageMap[ bagId ];

    for( const auto& item : container->getItemMap() )
    {
      if( item.second->getId() != catalogId )
        continue;

      location = std::make_pair( bagId, item.first );

      return true;
    }
  }

  return false;
}