#include <set>
#include <string.h>

#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>
#include <Database/ZoneDbConnection.h>

#include "House.h"

#include <unordered_map>
#include "Framework.h"

extern Sapphire::Framework g_fw;

Sapphire::House::House( uint32_t houseId, uint32_t landSetId, Common::LandIdent ident, const std::string& estateName,
                        const std::string& estateComment ) :
  m_houseId( houseId ),
  m_landSetId( landSetId ),
  m_landIdent( ident ),
  m_estateName( estateName ),
  m_estateComment( estateComment )
{

}

Sapphire::House::~House() = default;

void Sapphire::House::updateHouseDb()
{
  auto pDB = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  // BuildTime = 1, Aetheryte = 2, Comment = 3, HouseName = 4, Endorsements = 5, HouseId = 6
  auto stmt = pDB->getPreparedStatement( Db::HOUSING_HOUSE_UP );
  stmt->setUInt( 6, m_houseId );

  stmt->setInt64( 1, m_buildTime );
  stmt->setInt( 2, 0 );

  stmt->setString( 3, m_estateComment );
  stmt->setString( 4, m_estateName );

  stmt->setUInt64( 5, 0 );

  pDB->execute( stmt );
}

uint32_t Sapphire::House::getLandSetId() const
{
  return m_landSetId;
}

Sapphire::Common::LandIdent Sapphire::House::getLandIdent() const
{
  return m_landIdent;
}

uint32_t Sapphire::House::getHouseId() const
{
  return m_houseId;
}

uint8_t Sapphire::House::getHouseModelColor( Common::HousePartSlot slot ) const
{
  return m_houseModelsCache[ slot ].second;
}

uint32_t Sapphire::House::getHouseInteriorModel( Common::HousingInteriorSlot slot ) const
{
  return m_houseInteriorModels[ slot ];
}

void Sapphire::House::setHouseModel( Common::HousePartSlot slot, uint32_t id )
{
  m_houseModelsCache[ slot ].first = id;
}

void Sapphire::House::setHouseModelColor( Common::HousePartSlot slot, uint32_t id )
{
  m_houseModelsCache[ slot ].second = id;
}

void Sapphire::House::setHouseInteriorModel( Common::HousingInteriorSlot slot, uint32_t id )
{
  m_houseInteriorModels[ slot ] = id;
}

uint32_t Sapphire::House::getHouseModel( Common::HousePartSlot slot ) const
{
  return m_houseModelsCache[ slot ].first;
}

Sapphire::House::HouseModelsArray const& Sapphire::House::getHouseModels() const
{
  return m_houseModelsCache;
}

const std::string& Sapphire::House::getHouseName() const
{
  return m_estateName;
}

const std::string& Sapphire::House::getHouseGreeting() const
{
  return m_estateComment;
}

void Sapphire::House::setHouseGreeting( const std::string& greeting )
{
  m_estateComment = greeting;

  updateHouseDb();
}

void Sapphire::House::setHouseName( const std::string& name )
{
  m_estateName = name;

  updateHouseDb();
}