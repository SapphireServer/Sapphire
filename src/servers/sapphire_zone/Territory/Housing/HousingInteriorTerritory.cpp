#include "HousingInteriorTerritory.h"
#include "Common.h"

using namespace Sapphire;
using namespace Sapphire::World::Territory;

Housing::HousingInteriorTerritory::HousingInteriorTerritory( uint64_t ident, uint16_t territoryTypeId,
                                                             uint32_t guId,
                                                             const std::string& internalName,
                                                             const std::string& contentName ) :
  Zone( territoryTypeId, guId, internalName, contentName ),
  m_landIdent( ident )
{

}

Housing::HousingInteriorTerritory::~HousingInteriorTerritory()
{

}

bool Housing::HousingInteriorTerritory::init()
{

}

void Housing::HousingInteriorTerritory::onPlayerZoneIn( Entity::Player& player )
{

}

void Housing::HousingInteriorTerritory::onUpdate( uint32_t currTime )
{

}