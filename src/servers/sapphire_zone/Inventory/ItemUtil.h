#ifndef SAPPHIRE_ITEMUTIL_H
#define SAPPHIRE_ITEMUTIL_H

#include <Common.h>
#include "ForwardsZone.h"

namespace Core {
namespace Items {
namespace Util {

ItemPtr loadItem( uint64_t uId );

/*! check if weapon category qualifies the weapon as onehanded */
bool isOneHandedWeapon( Common::ItemUICategory weaponCategory );

bool isArmory( uint16_t containerId );

bool isEquipment( uint16_t containerId );

uint16_t getCharaEquipSlotCategoryToArmoryId( uint8_t slotId );

Common::ContainerType getContainerType( uint32_t containerId );

uint32_t getNextUId();

}
}
}


#endif //SAPPHIRE_ITEMMGR_H
