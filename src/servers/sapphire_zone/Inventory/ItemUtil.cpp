#include "ItemUtil.h"

#include "ItemContainer.h"
#include "Item.h"
#include "Framework.h"
#include <Network/CommonActorControl.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>


extern Core::Framework g_fw;

bool Core::Items::Util::isArmory( uint16_t containerId )
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

uint16_t Core::Items::Util::getCharaEquipSlotCategoryToArmoryId( uint8_t slotId )
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


bool Core::Items::Util::isEquipment( uint16_t containerId )
{
  return containerId == Common::GearSet0;
}


bool Core::Items::Util::isOneHandedWeapon( Common::ItemUICategory weaponCategory )
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

Core::ItemPtr Core::Items::Util::loadItem( uint64_t uId )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  // load actual item
  auto itemRes = pDb->query(
    "SELECT catalogId, stack, flags FROM charaglobalitem WHERE itemId = " + std::to_string( uId ) + ";" );
  if( !itemRes->next() )
    return nullptr;

  try
  {
    auto itemInfo = pExdData->get< Core::Data::Item >( itemRes->getUInt( 1 ) );
    bool isHq = itemRes->getUInt( 3 ) == 1;

    ItemPtr pItem = make_Item( uId,
                               itemRes->getUInt( 1 ),
                               itemInfo->modelMain,
                               itemInfo->modelSub,
                               isHq );

    pItem->setStackSize( itemRes->getUInt( 2 ) );

    return pItem;
  }
  catch( ... )
  {
    return nullptr;
  }
}

Core::Common::ContainerType Core::Items::Util::getContainerType( uint32_t containerId )
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


uint32_t Core::Items::Util::getNextUId()
{
  uint32_t charId = 0;
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pQR = pDb->query( "SELECT MAX(ItemId) FROM charaglobalitem" );

  if( !pQR->next() )
    return 0x00500001;

  charId = pQR->getUInt( 1 ) + 1;
  if( charId < 0x00500001 )
    return 0x00500001;

  return charId;
}
