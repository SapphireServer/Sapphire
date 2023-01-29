#include "MarketMgr.h"

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Actor/Player.h"

#include <algorithm>

#include <Service.h>
#include "WorldServer.h"
#include "Session.h"
#include "Network/GameConnection.h"

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

bool MarketMgr::init()
{
//  Logger::info( "MarketMgr: warming up marketable item cache..." );
//
//  // build item cache
//  auto& exdData = Common::Service< Sapphire::Data::ExdDataGenerated >::ref();
//  auto idList = exdData.getItemIdList();
//
//  for( auto id : idList )
//  {
//    if( id > 10000 )
//      break;
//
//    auto item = exdData.get< Sapphire::Data::Item >( id );
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

void MarketMgr::requestItemListingInfo( Entity::Player& player, uint32_t catalogId, uint32_t requestId )
{

  auto& server = Common::Service< World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );

  auto countPkt = makeZonePacket< FFFXIVIpcItemSearchResult >( player.getId() );
  countPkt->data().Count = 1 << 8;
  countPkt->data().CatalogID = catalogId;
  countPkt->data().Result = requestId;

  pSession->getZoneConnection()->queueOutPacket( countPkt );

  auto historyPkt = makeZonePacket< FFXIVIpcGetItemHistoryResult >( player.getId() );
  historyPkt->data().CatalogID = catalogId;

  std::string name = "fix game pls se :(((";

  for( int i = 0; i < 10; i++ )
  {
    auto& listing = historyPkt->data().ItemHistoryList[ i ];

    listing.CatalogID = catalogId;
    listing.Stack = i + 1;
    listing.BuyRealDate = Common::Util::getTimeSeconds();
    listing.SellPrice = 69420420;
    listing.SubQuality = 1;

    strcpy( listing.BuyCharacterName, name.c_str() );
  }

  pSession->getZoneConnection()->queueOutPacket( historyPkt );
}


void MarketMgr::searchMarketboard( Entity::Player& player, uint8_t itemSearchCategory,  uint8_t maxEquipLevel, uint8_t classJob,
                                   const std::string_view& searchStr, uint32_t requestId, uint32_t startIdx )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );

  ItemSearchResultList resultList;
  findItems( searchStr, itemSearchCategory, maxEquipLevel, classJob, resultList );

  auto numResults = resultList.size();

  if( startIdx > numResults )
    return;

  auto endIdx = std::min< size_t >( startIdx + 20, numResults );
  auto size = endIdx - startIdx;

  auto resultPkt = makeZonePacket< FFXIVIpcCatalogSearchResult >( player.getId() );
  resultPkt->data().Index = startIdx;
  resultPkt->data().RequestKey = requestId;

  for( auto i = 0; i < size; i++ )
  {
    auto& item = resultList.at( startIdx + i );
    auto& data = resultPkt->data().CatalogList[ i ];

    data.CatalogID = item.catalogId;
    data.StockCount = item.quantity;
    data.RequestItemCount = 420;
  }

  if( size < 20 )
    resultPkt->data().NextIndex = 0;
  else
    resultPkt->data().NextIndex = startIdx + 20;

  pSession->getZoneConnection()->queueOutPacket( resultPkt );
}

void MarketMgr::requestItemListings( Sapphire::Entity::Player& player, uint16_t catalogId )
{

}

void MarketMgr::findItems( const std::string_view& searchStr, uint8_t itemSearchCat, uint8_t maxEquipLevel, uint8_t classJob,
                           MarketMgr::ItemSearchResultList& resultList )
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
