#include <set>
#include <string.h>

#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>
#include <Database/ZoneDbConnection.h>

#include "House.h"

#include <unordered_map>
#include "Framework.h"

Sapphire::House::House( uint32_t houseId, uint32_t landSetId, Common::LandIdent ident, FrameworkPtr pFw ) :
  m_houseId( houseId ),
  m_landSetId( landSetId ),
  m_landIdent( ident ),
  m_pFw( pFw )
{
  auto pDB = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  // todo: convert to prepared statement
  auto res = pDB->query( "SELECT * FROM house WHERE HouseId = " + std::to_string( houseId ) );

  if( !res->next() )
  {
    Logger::info( "Creating house House#" + std::to_string( houseId ) + " in LandSet#" + std::to_string( landSetId ) );

    auto stmt = pDB->getPreparedStatement( Db::HOUSING_HOUSE_INS );

    stmt->setUInt( 1, m_landSetId );
    stmt->setUInt( 2, m_houseId );

    pDB->execute( stmt );

    // todo: make this nicer/configurable?
    m_houseName = "Estate #" + std::to_string( m_landIdent.landId + 1 );
  }
  else
  {
    m_estateMessage = res->getString( "Comment" );
    m_houseName = res->getString( "HouseName" );

    auto housePartModels = res->getBlobVector( "HousePartModels" );
    auto housePartColours = res->getBlobVector( "HousePartColours" );

    auto models = reinterpret_cast< uint32_t* >( &housePartModels[ 0 ] );
    for( auto i = 0; i < 8; i++ )
    {
      m_houseParts[ i ] = { models[ i ], housePartColours[ i ] };
    }

    auto houseInteriorModels = res->getBlobVector( "HouseInteriorModels" );

    auto interiorModels = reinterpret_cast< uint32_t* >( &houseInteriorModels[ 0 ] );
    for( auto i = 0; i < 10; i++ )
    {
      m_houseInteriorParts[ i ] = interiorModels[ i ];
    }
  }
}

Sapphire::House::~House()
{
}

void Sapphire::House::updateHouseDb()
{
  auto pDB = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  // BuildTime = 1, Aetheryte = 2, Comment = 3, HouseName = 4, Endorsements = 5,
  // HousePartModels = 6, HousePartColours = 7, HouseId = 8
  auto stmt = pDB->getPreparedStatement( Db::HOUSING_HOUSE_UP );
  stmt->setUInt( 9, m_houseId );

  stmt->setInt64( 1, m_buildTime );
  stmt->setInt( 2, 0 );

  stmt->setString( 3, m_estateMessage );
  stmt->setString( 4, m_houseName );

  stmt->setUInt64( 5, 0 );

  std::vector< uint32_t > models;
  std::vector< uint8_t > colours;

  for( auto i = 0; i < 8; i++ )
  {
    auto& part = m_houseParts[ i ];
    models.push_back( part.first );
    colours.push_back( part.second );
  }

  // todo: this is shit
  std::vector< uint8_t > tmpModels( models.size() * 4 );
  memcpy( tmpModels.data(), models.data(), tmpModels.size() );

  stmt->setBinary( 6, tmpModels );
  stmt->setBinary( 7, colours );

  models.clear();

  for( auto i = 0; i < 10; i++ )
  {
    models.push_back( m_houseInteriorParts[ i ] );
  }

  std::vector< uint8_t > tmp2Models( models.size() * 4 );
  memcpy( tmp2Models.data(), models.data(), tmp2Models.size() );

  stmt->setBinary( 8, tmp2Models );

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

uint8_t Sapphire::House::getHousePartColor( Common::HousePartSlot slot ) const
{
  return m_houseParts[ slot ].second;
}

uint32_t Sapphire::House::getHouseInteriorPart( Common::HousingInteriorSlot slot ) const
{
  return m_houseInteriorParts[ slot ];
}

void Sapphire::House::setHousePart( Common::HousePartSlot slot, uint32_t id )
{
  m_houseParts[ slot ].first = id;
}

void Sapphire::House::setHousePartColor( Common::HousePartSlot slot, uint32_t id )
{
  m_houseParts[ slot ].second = id;
}

void Sapphire::House::setHouseInteriorPart( Common::HousingInteriorSlot slot, uint32_t id )
{
  m_houseInteriorParts[ slot ] = id;
}

uint32_t Sapphire::House::getHousePart( Common::HousePartSlot slot ) const
{
  return m_houseParts[ slot ].first;
}

Sapphire::House::HousePartsArray const& Sapphire::House::getHouseParts() const
{
  return m_houseParts;
}

const std::string& Sapphire::House::getHouseName() const
{
  return m_houseName;
}

const std::string& Sapphire::House::getHouseGreeting() const
{
  return m_estateMessage;
}

void Sapphire::House::setHouseGreeting( const std::string& greeting )
{
  m_estateMessage = greeting;

  updateHouseDb();
}

void Sapphire::House::setHouseName( const std::string& name )
{
  m_houseName = name;

  updateHouseDb();
}