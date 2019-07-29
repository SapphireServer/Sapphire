#include "MarketMgr.h"

#include <Exd/ExdDataGenerated.h>
#include <Framework.h>
#include <Logging/Logger.h>

#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Actor/Player.h"

#include <algorithm>

using namespace Sapphire::Network::Packets;

Sapphire::World::Manager::MarketMgr::MarketMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

bool Sapphire::World::Manager::MarketMgr::init()
{
//  Logger::info( "MarketMgr: warming up marketable item cache..." );
//
//  // build item cache
//  auto exdData = framework()->get< Sapphire::Data::ExdDataGenerated >();
//  auto idList = exdData->getItemIdList();
//
//  for( auto id : idList )
//  {
//    if( id > 10000 )
//      break;
//
//    auto item = exdData->get< Sapphire::Data::Item >( id );
//    if( !item )
//      continue;
//
//    if( item->isUntradable )
//      continue;
//
//    MarketableItem cacheEntry {};
//    cacheEntry.catalogId = id;
//    cacheEntry.itemSearchCategory = item->itemSearchCategory;
//    cacheEntry.maxEquipLevel = item->levelEquip;
//    cacheEntry.name = item->name;
//    cacheEntry.classJob = item->classJobUse;
//    cacheEntry.itemLevel = item->levelItem;
//
//    m_marketItemCache.push_back( std::move( cacheEntry ) );
//  }
//
//  std::sort( m_marketItemCache.begin(), m_marketItemCache.end(), []( const MarketableItem& a, const MarketableItem& b )
//  {
//    return a.itemLevel > b.itemLevel;
//  } );
//
//  Logger::info( "MarketMgr: Cached " + std::to_string( m_marketItemCache.size() ) + " marketable items" );

  return true;
}

void Sapphire::World::Manager::MarketMgr::requestItemListingInfo( Sapphire::Entity::Player& player, uint32_t catalogId,
                                                                  uint32_t requestId )
{
  auto countPkt = makeZonePacket< Server::FFFXIVIpcMarketBoardItemListingCount >( player.getId() );
  countPkt->data().quantity = 1 << 8;
  countPkt->data().itemCatalogId = catalogId;
  countPkt->data().requestId = requestId;

  player.queuePacket( countPkt );

  auto historyPkt = makeZonePacket< Server::FFXIVIpcMarketBoardItemListingHistory >( player.getId() );
  historyPkt->data().itemCatalogId = catalogId;
  historyPkt->data().itemCatalogId2 = catalogId;

  std::string name = "fix game pls se :(((";

  for( int i = 0; i < 10; i++ )
  {
    auto& listing = historyPkt->data().listing[ i ];

    listing.itemCatalogId = catalogId;
    listing.quantity = i + 1;
    listing.purchaseTime = Common::Util::getTimeSeconds();
    listing.salePrice = 69420420;
    listing.isHq = 1;
    listing.onMannequin = 1;

    strcpy( listing.buyerName, name.c_str() );
  }

  player.queuePacket( historyPkt );
}


void Sapphire::World::Manager::MarketMgr::searchMarketboard( Entity::Player& player, uint8_t itemSearchCategory,
                                                             uint8_t maxEquipLevel, uint8_t classJob,
                                                             const std::string_view& searchStr, uint32_t requestId,
                                                             uint32_t startIdx )
{
  ItemSearchResultList resultList;
  findItems( searchStr, itemSearchCategory, maxEquipLevel, classJob, resultList );

  auto numResults = resultList.size();

  if( startIdx > numResults )
    return;

  auto endIdx = std::min< size_t >( startIdx + 20, numResults );
  auto size = endIdx - startIdx;

  auto resultPkt = makeZonePacket< Server::FFXIVIpcMarketBoardSearchResult >( player.getId() );
  resultPkt->data().itemIndexStart = startIdx;
  resultPkt->data().requestId = requestId;

  for( auto i = 0; i < size; i++ )
  {
    auto& item = resultList.at( startIdx + i );
    auto& data = resultPkt->data().items[ i ];

    data.itemCatalogId = item.catalogId;
    data.quantity = item.quantity;
    data.demand = 420;
  }

  if( size < 20 )
    resultPkt->data().itemIndexEnd = 0;
  else
    resultPkt->data().itemIndexEnd = startIdx + 20;

  player.queuePacket( resultPkt );
}

void Sapphire::World::Manager::MarketMgr::requestItemListings( Sapphire::Entity::Player& player, uint16_t catalogId )
{

}

void Sapphire::World::Manager::MarketMgr::findItems( const std::string_view& searchStr, uint8_t itemSearchCat,
                                                     uint8_t maxEquipLevel, uint8_t classJob,
                                                     Sapphire::World::Manager::MarketMgr::ItemSearchResultList& resultList )
{
  for( const auto& item : m_marketItemCache )
  {
    if( item.itemSearchCategory != itemSearchCat )
      continue;

    if( maxEquipLevel > 0 && item.maxEquipLevel > maxEquipLevel )
      continue;

    if( classJob > 0 && item.classJob != classJob )
      continue;

    resultList.push_back( { item.catalogId, 1 } );
  }
}
