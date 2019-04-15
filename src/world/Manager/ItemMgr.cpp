#include "ItemMgr.h"

#include "Inventory/ItemContainer.h"
#include "Inventory/Item.h"
#include "Framework.h"
#include <Network/CommonActorControl.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>

Sapphire::World::Manager::ItemMgr::ItemMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

bool Sapphire::World::Manager::ItemMgr::isArmory( uint16_t containerId )
{
  return
    containerId == Common::ArmoryBody ||
    containerId == Common::ArmoryEar ||
    containerId == Common::ArmoryFeet ||
    containerId == Common::ArmoryHand ||
    containerId == Common::ArmoryHead ||
    containerId == Common::ArmoryLegs ||
    containerId == Common::ArmoryMain ||
    containerId == Common::ArmoryOff ||
    containerId == Common::ArmoryRing ||
    containerId == Common::ArmoryWaist ||
    containerId == Common::ArmoryWrist ||
    containerId == Common::ArmorySoulCrystal;
}


uint16_t Sapphire::World::Manager::ItemMgr::getCharaEquipSlotCategoryToArmoryId( uint8_t slotId )
{

  switch( slotId )
  {
    case Common::CharaHead:
      return Common::ArmoryHead;

    case Common::CharaBody:
    case Common::BodyDisallowHead:
    case Common::BodyDisallowHandsLegsFeet:
    case Common::BodyDisallowAll:
    case Common::BodyDisallowHands:
    case Common::BodyDisallowLegsFeet:
      return Common::ArmoryBody;

    case Common::CharaEars:
      return Common::ArmoryEar;

    case Common::CharaFeet:
      return Common::ArmoryFeet;

    case Common::CharaHands:
      return Common::ArmoryHand;

    case Common::CharaLegs:
    case Common::LegsDisallowFeet:
      return Common::ArmoryLegs;

    case Common::CharaMainHand:
    case Common::MainTwoHandedWeapon:
    case Common::MainOrOffHand:
      return Common::ArmoryMain;

    case Common::CharaOffHand:
      return Common::ArmoryOff;

    case Common::CharaRing:
      return Common::ArmoryRing;

    case Common::CharaWaist:
      return Common::ArmoryWaist;

    case Common::CharaWrist:
      return Common::ArmoryWrist;

    case Common::CharaNeck:
      return Common::ArmoryNeck;

    case Common::CharaSoulCrystal:
      return Common::ArmorySoulCrystal;

    default:
      return 0;
  }
}


bool Sapphire::World::Manager::ItemMgr::isEquipment( uint16_t containerId )
{
  return containerId == Common::GearSet0;
}

bool Sapphire::World::Manager::ItemMgr::isOneHandedWeapon( Common::ItemUICategory weaponCategory )
{
  switch( weaponCategory )
  {
    case Common::ItemUICategory::AlchemistsPrimaryTool:
    case Common::ItemUICategory::ArmorersPrimaryTool:
    case Common::ItemUICategory::BotanistsPrimaryTool:
    case Common::ItemUICategory::CulinariansPrimaryTool:
    case Common::ItemUICategory::OnehandedConjurersArm:
    case Common::ItemUICategory::CarpentersPrimaryTool:
    case Common::ItemUICategory::FishersPrimaryTool:
    case Common::ItemUICategory::GladiatorsArm:
    case Common::ItemUICategory::GoldsmithsPrimaryTool:
    case Common::ItemUICategory::LeatherworkersPrimaryTool:
    case Common::ItemUICategory::MinersPrimaryTool:
    case Common::ItemUICategory::OnehandedThaumaturgesArm:
    case Common::ItemUICategory::WeaversPrimaryTool:
    case Common::ItemUICategory::BlacksmithsPrimaryTool:
      return true;
    default:
      return false;
  }
}

Sapphire::ItemPtr Sapphire::World::Manager::ItemMgr::loadItem( uint64_t uId )
{
  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  //  1 catalogId, 2 stack, 3 reservedFlag, 4 signatureId, 5 flags, 6 durability, 7 refine, 8 materia_0, 9 materia_1,
  //  10 materia_2, 11 materia_3, 12 materia_4, 13 stain, 14 pattern, 15 buffer_0, 16 buffer_1, 17 buffer_2,
  //  18 buffer_3, 19 buffer_4
  auto query = pDb->getPreparedStatement( Db::CHARA_ITEMGLOBAL_SELECT );
  query->setUInt64( 1, uId );

  auto itemRes = pDb->query( query );
  if( !itemRes->next() )
    return nullptr;

  try
  {
    auto itemInfo = pExdData->get< Sapphire::Data::Item >( itemRes->getUInt( 1 ) );
    bool isHq = itemRes->getUInt( 3 ) == 1;

    ItemPtr pItem = make_Item( uId,
                               itemRes->getUInt( 1 ),
                               framework(),
                               isHq );

    pItem->setStackSize( itemRes->getUInt( 2 ) );
    pItem->setStain( itemRes->getUInt16( 13 ) );
    pItem->setDurability( itemRes->getInt16( 6 ) );

    return pItem;
  }
  catch( ... )
  {
    return nullptr;
  }
}


Sapphire::Common::ContainerType Sapphire::World::Manager::ItemMgr::getContainerType( uint32_t containerId )
{
  if( containerId < 5 )
  {
    return Common::Bag;
  }
  else if( containerId < 2000 )
  {
    return Common::GearSet;
  }
  else if( containerId < 3200 )
  {
    return Common::CurrencyCrystal;
  }
  else if( containerId < 3600 )
  {
    return Common::Armory;
  }
  else
  {
    return Common::Unknown;
  }
}

uint32_t Sapphire::World::Manager::ItemMgr::getNextUId()
{
  uint32_t charId = 0;
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pQR = pDb->query( "SELECT MAX(ItemId) FROM charaglobalitem" );

  if( !pQR->next() )
    return 0x00500001;

  charId = pQR->getUInt( 1 ) + 1;
  if( charId < 0x00500001 )
    return 0x00500001;

  return charId;
}
