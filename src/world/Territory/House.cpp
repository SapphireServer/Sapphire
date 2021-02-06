#include <set>
#include <string.h>

#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>
#include <Database/ZoneDbConnection.h>

#include "House.h"

#include <unordered_map>
#include <Service.h>

Sapphire::House::House( uint32_t houseId, uint32_t landSetId, Common::LandIdent ident, const std::string& estateName,
                        const std::string& estateComment ) :
  m_houseId( houseId ),
  m_landSetId( landSetId ),
  m_landIdent( ident ),
  m_estateName( estateName ),
  m_estateComment( estateComment )
{
  m_interiorModelCache.fill( 0 );
  m_exteriorModelCache.fill( std::make_pair( 0, 0 ) );
}

Sapphire::House::~House() = default;

void Sapphire::House::updateHouseDb()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  // BuildTime = 1, Aetheryte = 2, Comment = 3, HouseName = 4, Endorsements = 5, HouseId = 6
  auto stmt = db.getPreparedStatement( Db::HOUSING_HOUSE_UP );
  stmt->setUInt( 6, m_houseId );

  stmt->setInt64( 1, static_cast< int64_t >( m_buildTime ) );
  stmt->setBool( 2, m_hasAetheryte );

  stmt->setString( 3, m_estateComment );
  stmt->setString( 4, m_estateName );

  stmt->setUInt64( 5, 0 );

  db.execute( stmt );
}

uint32_t Sapphire::House::getLandSetId() const
{
  return m_landSetId;
}

Sapphire::Common::LandIdent Sapphire::House::getLandIdent() const
{
  return m_landIdent;
}

uint32_t Sapphire::House::getId() const
{
  return m_houseId;
}

Sapphire::House::ExteriorModelsArray const& Sapphire::House::getHouseModels() const
{
  return m_exteriorModelCache;
}

void Sapphire::House::clearModelCache()
{
  m_exteriorModelCache.fill( std::make_pair( 0, 0 ) );
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

void Sapphire::House::setExteriorModel( Sapphire::Common::HouseExteriorSlot slot, uint32_t modelId, uint16_t stain )
{
  m_exteriorModelCache[ slot ] = std::make_pair( modelId, stain );
}

Sapphire::House::HousePart Sapphire::House::getExteriorModel( Sapphire::Common::HouseExteriorSlot slot )
{
  return m_exteriorModelCache[ slot ];
}

void Sapphire::House::setInteriorModel( Sapphire::Common::HouseInteriorSlot slot, uint32_t modelId )
{
  m_interiorModelCache[ slot ] = modelId;
}

uint32_t Sapphire::House::getInteriorModel( Sapphire::Common::HouseInteriorSlot slot )
{
  return m_interiorModelCache[ slot ];
}

bool Sapphire::House::getHasAetheryte() const
{
  return m_hasAetheryte;
}

void Sapphire::House::setHasAetheryte( bool hasAetheryte )
{
  m_hasAetheryte = hasAetheryte;
}
