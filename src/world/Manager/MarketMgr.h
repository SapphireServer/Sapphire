#ifndef SAPPHIRE_MARKETMGR_H
#define SAPPHIRE_MARKETMGR_H

#include "ForwardsZone.h"

#include <vector>
#include <string_view>

namespace Sapphire::World::Manager
{
  class MarketMgr
  {
  public:
    MarketMgr() = default;

    bool init();

    void searchMarketboard( Entity::Player& player, uint8_t itemSearchCategory,
                                uint8_t maxEquipLevel, uint8_t classJob,
                                const std::string_view& searchStr, uint32_t requestId,
                                uint32_t startIdx );

    void requestItemListingInfo( Entity::Player& player, uint32_t catalogId, uint32_t requestId );

    void requestItemListings( Entity::Player& player, uint16_t catalogId );

  private:
    struct ItemSearchResult
    {
      uint32_t catalogId;
      uint16_t quantity;
    };

    struct MarketableItem
    {
      uint32_t catalogId;
      uint8_t itemSearchCategory;
      uint8_t maxEquipLevel;
      uint16_t itemLevel;
      uint8_t classJob;
      std::string name;
    };

    using ItemSearchResultList = std::vector< ItemSearchResult >;
    using MarketableItemCacheList = std::vector< MarketableItem >;

    MarketableItemCacheList m_marketItemCache;



    void findItems( const std::string_view& searchStr, uint8_t itemSearchCat, uint8_t maxEquipLevel, uint8_t classJob,
                    ItemSearchResultList& resultList );

  };
}


#endif //SAPPHIRE_MARKETMGR_H
